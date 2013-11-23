#include "../Sequencing/Sequence.h"
#include "../Sequencing/Alignment.h"
#include "SubstitutionMatrix.h"

#ifndef ___PAIRWISEALIGNMENT___
#define ___PAIRWISEALIGNMENT___

namespace Pairwise
{
	using Sequencing::Sequence;

	class PairwiseAlignment : public Sequencing::Alignment
	{
	private:
		MatrixDataType score;

	protected:

	public:
		PairwiseAlignment();
		PairwiseAlignment(Sequence sequence1, Sequence sequence2, MatrixDataType new_score);
		PairwiseAlignment(const PairwiseAlignment& pairwise_alignment);
		~PairwiseAlignment();

		void setScore(MatrixDataType score);
		MatrixDataType getScore() const;
	};
}

#endif