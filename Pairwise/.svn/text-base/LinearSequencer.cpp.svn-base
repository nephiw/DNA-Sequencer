#include <algorithm>
#include "LinearSequencer.h"

namespace Pairwise
{
	using Sequencing::Sequence;

	LinearSequencer::LinearSequencer(int new_gap_penalty)
	{
		this->gap_penalty = new_gap_penalty;
	}

	LinearSequencer::~LinearSequencer() {}

	inline MatrixDataType LinearSequencer::max(const MatrixDataType x, const MatrixDataType y, const MatrixDataType z)
	{
		MatrixDataType w = std::max(x, y);
		return std::max(w, z);
	}

	inline MatrixDataType LinearSequencer::max(const MatrixDataType w, const MatrixDataType x, const MatrixDataType y, const MatrixDataType z)
	{
		MatrixDataType a = std::max(w, x);
		MatrixDataType b = std::max(y, z);
		return std::max(a, b);
	}

	std::vector<std::vector<MatrixDataType> > LinearSequencer::sequence_matrix_create(const bool global, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2)
	{
		int sequence1Length = sequence1.length();
		int sequence2Length = sequence2.length();

		std::vector<std::vector<MatrixDataType> > sequence_matrix = std::vector<std::vector<MatrixDataType> >(sequence1Length + 1, std::vector<MatrixDataType>(sequence2Length + 1, 0));

		for ( int i = 1; i < sequence1Length + 1; i++ )
			global ? sequence_matrix[i][0] = this->gap_penalty * i : sequence_matrix[i][0] = 0;
		for ( int j = 1; j < sequence2Length + 1; j++ )
			global ? sequence_matrix[0][j] = this->gap_penalty * j : sequence_matrix[0][j] = 0;

		for ( int i = 1; i < sequence1Length + 1; i++ )
		{
			for ( int j = 1; j < sequence2Length + 1; j++ )
			{
				int match = sequence_matrix[i-1][j-1] + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1]));
				int remove = sequence_matrix[i-1][j] + this->gap_penalty;
				int insert = sequence_matrix[i][j-1] + this->gap_penalty;
				if ( global == true )
					sequence_matrix[i][j] = this->max(match, remove, insert);
				else
					sequence_matrix[i][j] = this->max(match, remove, insert, 0);
			}
		}
		
		return sequence_matrix;
	}

	PairwiseAlignment LinearSequencer::sequence_matrix_traceback(const bool global, std::vector<std::vector<MatrixDataType> >& sequence_matrix, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2)
	{
		std::string aligned_sequence1;
		std::string aligned_sequence2;

		int i = 0;
		int j = 0;
		MatrixDataType highest_score = 0;

		if ( global == true )
		{
			i = sequence1.length();
			j = sequence2.length();
		}
		else
			this->getHighestScore(sequence_matrix, i, j);

		highest_score = sequence_matrix[i][j];

		while ( i > 0 && j > 0 )
		{
			MatrixDataType score = sequence_matrix[i][j];
			if ( global == false && score == 0 ) break;

			MatrixDataType diag = sequence_matrix[i-1][j-1];
			MatrixDataType up = sequence_matrix[i][j-1];
			MatrixDataType left = sequence_matrix[i-1][j];

			if ( score == diag + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1])) )
			{
				aligned_sequence1 += sequence1[i-1];
				aligned_sequence2 += sequence2[j-1];
				i--;
				j--;
			}
			else if ( score == left + this->gap_penalty )
			{
				aligned_sequence1 += sequence1[i-1];
				aligned_sequence2 += substitution_matrix.getGapCharacter();
				i--;
			}
			else
			{
				aligned_sequence1 += substitution_matrix.getGapCharacter();
				aligned_sequence2 += sequence2[j-1];
				j--;
			}
		}

		if ( global == true )
		{
			while ( i > 0 )
			{
				aligned_sequence1 += sequence1[i-1];
				aligned_sequence2 += substitution_matrix.getGapCharacter();
				i--;
			}

			while ( j > 0 )
			{
				aligned_sequence1 += substitution_matrix.getGapCharacter();
				aligned_sequence2 += sequence1[j-1];
				j--;
			}
		}
		

		std::string aligned_sequence1Reverse(aligned_sequence1.begin(), aligned_sequence1.end());
		std::reverse(aligned_sequence1Reverse.begin(), aligned_sequence1Reverse.end());

		std::string aligned_sequence2Reverse(aligned_sequence2.begin(), aligned_sequence2.end());
		std::reverse(aligned_sequence2Reverse.begin(), aligned_sequence2Reverse.end());

		PairwiseAlignment alignment = PairwiseAlignment(aligned_sequence1Reverse, aligned_sequence2Reverse, highest_score);
		return alignment;
	}

	void LinearSequencer::getHighestScore(std::vector<std::vector<MatrixDataType> >& sequence_matrix, int& i_index, int& j_index)
	{
		MatrixDataType highest_i_score = 0;
		MatrixDataType highest_j_score = 0;
		MatrixDataType highest_score = 0;

		for ( unsigned int i = 0; i < sequence_matrix.size(); i++ )
		{
			for ( unsigned int j = 0; j < sequence_matrix[i].size(); j++ )
			{
				if ( sequence_matrix[i][j] > highest_score )
				{
					highest_score = sequence_matrix[i][j];
					highest_i_score = i;
					highest_j_score = j;
				}
			}
		}

		i_index = highest_i_score;
		j_index = highest_j_score;
	}

	PairwiseAlignment LinearSequencer::sequence(const bool global, const Pairwise::SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2)
	{
		if ( sequence1.length() == 0 && sequence2.length() == 0 )
		{
			std::cout << "[Error] Cannot apply linear scoring to sequences of length 0" << std::endl;
			return PairwiseAlignment(Sequence("Sequence 1 Not Defined"), Sequence("Sequence 2 Not Defined"), 0);
		}
		else if ( sequence1.length() == 0 )
		{
			std::cout << "[Error] Cannot apply linear scoring to sequence-1 with length 0" << std::endl;
			return PairwiseAlignment(Sequence("Sequence 1 Not Defined"), sequence2, 0);
		}
		else if ( sequence2.length() == 0 )
		{
			std::cout << "[Error] Cannot apply linear scoring to sequence-2 with length 0" << std::endl;
			return PairwiseAlignment(sequence1, Sequence("Sequence 2 Not Defined"), 0);
		}

		if ( substitution_matrix.getColumnCount() == 0 || substitution_matrix.getRowCount() == 0 )
			return PairwiseAlignment(Sequence("Sequence must be evaluated against a valid matrix"), Sequence("Sequence must be evaluated against a valid matrix"), 0);

		std::vector<std::vector<MatrixDataType> > sequence_matrix = this->sequence_matrix_create(global, substitution_matrix, sequence1, sequence2);
		return this->sequence_matrix_traceback(global, sequence_matrix, substitution_matrix, sequence1, sequence2);
	}
}