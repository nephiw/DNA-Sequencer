#include <vector>
#include "SubstitutionMatrix.h"
#include "PairwiseAlignment.h"
#include "../Sequencing/Sequence.h"

#ifndef ___PAIRWISESEQUENCER___
#define ___PAIRWISESEQUENCER___

/**
 * The pairwise namespace contains all of the data structures and
 * algorithms related to pairwise sequencing (The alignment of only
 * two nucleotide or protein sequences at a time)
 */
namespace Pairwise
{
	/**
	 * The PairwiseSequencer abstract class provides an interface for all potential pairwise
	 * sequencing scoring schemes. To create a custom scoring scheme, this class can be extended
	 * and the provided sequence function must be implmented.
	 */
	class PairwiseSequencer
	{
	private:

	protected:
		
	public:
		/**
		 * This function provides the interface for sequencing two nucleotide or protien sequences
		 * based on global alignment, local alignment, and a provided substitution matrix.
		 */
		virtual Pairwise::PairwiseAlignment sequence(const bool global, const SubstitutionMatrix& substitution_matrix, const Sequencing::Sequence& sequence1, const Sequencing::Sequence& sequence2) = 0;
	};
}

#endif