#include <algorithm>
#include <limits>
#include "AffineSequencer.h"

namespace Pairwise
{
	using Sequencing::Sequence;

	AffineSequencer::AffineSequencer(int open_gap_penalty, int extend_gap_penalty)
	{
		this->open_gap_penalty = open_gap_penalty;
		this->extend_gap_penalty = extend_gap_penalty;
	}

	AffineSequencer::~AffineSequencer() {}

	inline MatrixDataType AffineSequencer::max(const MatrixDataType x, const MatrixDataType y)
	{
		return std::max(x, y);
	}

	inline MatrixDataType AffineSequencer::max(const MatrixDataType x, const MatrixDataType y, const MatrixDataType z)
	{
		MatrixDataType w = std::max(x, y);
		return std::max(w, z);
	}

	std::vector<std::vector<std::vector<MatrixDataType> > > AffineSequencer::sequence_matrix_create(const bool global, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2)
	{
		int sequence1Length = sequence1.length();
		int sequence2Length = sequence2.length();

		MatrixDataType negative_infinity = -std::numeric_limits<MatrixDataType>::infinity();

		std::vector<std::vector<std::vector<MatrixDataType> > > sequence_matrix = std::vector<std::vector<std::vector<MatrixDataType> > >(MATRIX_COUNT, std::vector<std::vector<MatrixDataType> >(sequence1Length + 1, std::vector<MatrixDataType>(sequence2Length + 1, 0)));
		
		sequence_matrix[MATRIX_B][0][0] = negative_infinity;
		sequence_matrix[MATRIX_C][0][0] = negative_infinity;

		for ( int i = 1; i < sequence1Length + 1; i++ )
		{
			sequence_matrix[MATRIX_A][i][0] = negative_infinity;
			sequence_matrix[MATRIX_B][i][0] = this->open_gap_penalty + (i - 1) * this->extend_gap_penalty;
			sequence_matrix[MATRIX_C][i][0] = negative_infinity;
		}

		for ( int j = 1; j < sequence2Length + 1; j++ )
		{
			sequence_matrix[MATRIX_A][0][j] = negative_infinity;
			sequence_matrix[MATRIX_B][0][j] = negative_infinity;
			sequence_matrix[MATRIX_C][0][j] = this->open_gap_penalty + (j - 1) * this->extend_gap_penalty;
		}

		for ( int i = 1; i < sequence1Length + 1; i++ )
		{
			for ( int j = 1; j < sequence2Length + 1; j++ )
			{
				sequence_matrix[MATRIX_A][i][j] = this->max(sequence_matrix[MATRIX_A][i-1][j-1] + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1])),
															sequence_matrix[MATRIX_B][i-1][j-1] + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1])),
															sequence_matrix[MATRIX_C][i-1][j-1] + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1])));
				sequence_matrix[MATRIX_B][i][j] = this->max(sequence_matrix[MATRIX_A][i-1][j] + this->open_gap_penalty,
															sequence_matrix[MATRIX_B][i-1][j] + this->extend_gap_penalty,
															sequence_matrix[MATRIX_C][i-1][j] + this->open_gap_penalty);
				sequence_matrix[MATRIX_C][i][j] = this->max(sequence_matrix[MATRIX_A][i][j-1] + this->open_gap_penalty,
															sequence_matrix[MATRIX_B][i][j-1] + this->open_gap_penalty,
															sequence_matrix[MATRIX_C][i][j-1] + this->extend_gap_penalty);
			}
		}

		return sequence_matrix;
	}

	PairwiseAlignment AffineSequencer::sequence_matrix_traceback(const bool global, std::vector<std::vector<std::vector<MatrixDataType> > >& sequence_matrix, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2)
	{
		std::string aligned_sequence1;
		std::string aligned_sequence2;

		int i = sequence1.length();
		int j = sequence2.length();
		MatrixDataType highest_score = this->max(sequence_matrix[MATRIX_A][i][j], sequence_matrix[MATRIX_B][i][j], sequence_matrix[MATRIX_C][i][j]);

		while ( i > 0 && j > 0 )
		{
			MatrixDataType score = this->max(sequence_matrix[MATRIX_A][i][j],
									   sequence_matrix[MATRIX_B][i][j],
									   sequence_matrix[MATRIX_C][i][j]);

			if ( score == sequence_matrix[MATRIX_A][i-1][j-1] + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1])) ||
				 score == sequence_matrix[MATRIX_B][i-1][j-1] + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1])) ||
				 score == sequence_matrix[MATRIX_C][i-1][j-1] + substitution_matrix.score(toupper(sequence1[i-1]), toupper(sequence2[j-1])) )
			{
				aligned_sequence1 += sequence1[i-1];
				aligned_sequence2 += sequence2[j-1];
				i--;
				j--;
			}
			else if ( score == sequence_matrix[MATRIX_A][i-1][j] + this->open_gap_penalty ||
					  score == sequence_matrix[MATRIX_B][i-1][j] + this->open_gap_penalty ||
					  score == sequence_matrix[MATRIX_C][i-1][j] + this->open_gap_penalty ||
					  score == sequence_matrix[MATRIX_A][i-1][j] + this->extend_gap_penalty ||
					  score == sequence_matrix[MATRIX_B][i-1][j] + this->extend_gap_penalty ||
					  score == sequence_matrix[MATRIX_C][i-1][j] + this->extend_gap_penalty )
			{
				aligned_sequence1 += sequence1[i-1];
				aligned_sequence2 += substitution_matrix.getGapCharacter();
				i--;
			}
			else if ( score == sequence_matrix[MATRIX_A][i][j-1] + this->open_gap_penalty ||
					  score == sequence_matrix[MATRIX_B][i][j-1] + this->open_gap_penalty ||
					  score == sequence_matrix[MATRIX_C][i][j-1] + this->open_gap_penalty ||
					  score == sequence_matrix[MATRIX_A][i][j-1] + this->extend_gap_penalty ||
					  score == sequence_matrix[MATRIX_B][i][j-1] + this->extend_gap_penalty ||
					  score == sequence_matrix[MATRIX_C][i][j-1] + this->extend_gap_penalty )
			{
				aligned_sequence1 += substitution_matrix.getGapCharacter();
				aligned_sequence2 += sequence2[j-1];
				j--;
			}
		}

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

		std::string aligned_sequence1Reverse(aligned_sequence1.begin(), aligned_sequence1.end());
		std::reverse(aligned_sequence1Reverse.begin(), aligned_sequence1Reverse.end());

		std::string aligned_sequence2Reverse(aligned_sequence2.begin(), aligned_sequence2.end());
		std::reverse(aligned_sequence2Reverse.begin(), aligned_sequence2Reverse.end());

		PairwiseAlignment alignment = PairwiseAlignment(aligned_sequence1Reverse, aligned_sequence2Reverse, highest_score);
		return alignment;
	}

	PairwiseAlignment AffineSequencer::sequence(const bool global, const Pairwise::SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2)
	{
		if ( sequence1.length() == 0 && sequence2.length() == 0 )
		{
			std::cout << "[Error] Cannot apply affine scoring to sequences of length 0" << std::endl;
			return PairwiseAlignment(Sequence("Sequence 1 Not Defined"), Sequence("Sequence 2 Not Defined"), 0);
		}
		else if ( sequence1.length() == 0 )
		{
			std::cout << "[Error] Cannot apply affine scoring to sequence-1 with length 0" << std::endl;
			return PairwiseAlignment(Sequence("Sequence 1 Not Defined"), sequence2, 0);
		}
		else if ( sequence2.length() == 0 )
		{
			std::cout << "[Error] Cannot apply affine scoring to sequence-2 with length 0" << std::endl;
			return PairwiseAlignment(sequence1, Sequence("Sequence 2 Not Defined"), 0);
		}
		
		if ( substitution_matrix.getColumnCount() == 0 || substitution_matrix.getRowCount() == 0 )
			return PairwiseAlignment(Sequence("Sequence must be evaluated against a valid matrix"), Sequence("Sequence must be evaluated against a valid matrix"), 0);

		std::vector<std::vector<std::vector<MatrixDataType> > > sequence_matrix = this->sequence_matrix_create(global, substitution_matrix, sequence1, sequence2);
		return this->sequence_matrix_traceback(global, sequence_matrix, substitution_matrix, sequence1, sequence2);
	}
}