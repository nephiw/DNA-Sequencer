#include "PairwiseAlignment.h"

namespace Pairwise
{
	PairwiseAlignment::PairwiseAlignment()
	{
		this->sequences = std::vector<Sequencing::Sequence>();
		this->score = 0;
	}

	PairwiseAlignment::~PairwiseAlignment() {}

	PairwiseAlignment::PairwiseAlignment(Sequence sequence1, Sequence sequence2, MatrixDataType new_score)
	{
		this->score = new_score;

		if ( sequence1.length() == 0 )
			this->sequences.push_back(Sequence("No-Sequence"));
		else
			this->sequences.push_back(sequence1);

		if ( sequence2.length() == 0 )
			this->sequences.push_back(Sequence("No-Sequence"));
		else
			this->sequences.push_back(sequence2);
	}

	PairwiseAlignment::PairwiseAlignment(const PairwiseAlignment& pairwise_alignment)
	{
		this->sequences = pairwise_alignment.sequences;
		this->score = pairwise_alignment.score;
	}

	void PairwiseAlignment::setScore(MatrixDataType score)
	{
		this->score = score;
	}

	MatrixDataType PairwiseAlignment::getScore() const
	{
		return this->score;
	}
}