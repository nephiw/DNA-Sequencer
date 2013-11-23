#include "PairwiseSequencer.h"

#ifndef ___AFFINESEQUENCER___
#define ___AFFINESEQUENCER___

/**
 * The pairwise namespace contains all of the data structures and
 * algorithms related to pairwise sequencing (The alignment of only
 * two nucleotide or protein sequences at a time)
 */
namespace Pairwise
{
	using Sequencing::Sequence;

	/**
	 * The AffineSequencer class implements the affine sequencing pairwise scoring scheme.
	 * The affine scoring scheme is defined by penalizing not only the extention of a gap
	 * but also includes the penalty of opening a gap.
	 */
	class AffineSequencer : public PairwiseSequencer
	{
	private:
		const static int MATRIX_COUNT = 3;
		const static int MATRIX_A = 0;
		const static int MATRIX_B = 1;
		const static int MATRIX_C = 2;
		MatrixDataType open_gap_penalty;
		MatrixDataType extend_gap_penalty;
		bool global;

		inline MatrixDataType max(const MatrixDataType x, const MatrixDataType y);
		inline MatrixDataType max(const MatrixDataType x, const MatrixDataType y, const MatrixDataType z);

		std::vector<std::vector<std::vector<MatrixDataType> > > sequence_matrix_create(const bool global, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2);
		PairwiseAlignment sequence_matrix_traceback(const bool global, std::vector<std::vector<std::vector<MatrixDataType> > >& sequence_matrix, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2);

	protected:

	public:
		/**
		 * Creates a new affine sequencer based on the provided open gap penalty and
		 * the provided extend gap penalty.
		 *
		 * @param open_gap_penalty The numerical penalty used for scoring the opening
		 * of a gap in the sequence alignment.
		 * @param extend gap penalty The numerical penalty used for scoring the extension
		 * of a gap in the sequence alignment.
		 */
		AffineSequencer(int open_gap_penalty, int extend_gap_penalty);

		/**
		 * Default Destructor.
		 */
		~AffineSequencer();

		/**
		 * This function sequences two sequences based on the affine scoring 
		 * scheme using a substitution matrix.
		 *
		 * @param gloabl If true the function with use the affine global 
		 * alignment algoirhthm to score the sequences. If false the
		 * function will use the affine local alignment algorithm to score the sequences
		 * @param substitution_matrix The substitution matrix that will be used
		 * to find the scores between the included nucleotide or protein characters
		 * in the sequences.
		 * @param sequence1 The first sequence that will be scored against the second sequence
		 * @param sequence2 The second sequecne that will be scored against the first sequence
		 */
		PairwiseAlignment sequence(const bool global, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2);
	};
}

#endif