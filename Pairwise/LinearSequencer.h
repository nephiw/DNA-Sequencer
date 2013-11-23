#include "PairwiseSequencer.h"

#ifndef ___LINEARSEQUENCER___
#define ___LINEARSEQUENCER___

/**
 * The pairwise namespace contains all of the data structures and
 * algorithms related to pairwise sequencing (The alignment of only
 * two nucleotide or protein sequences at a time)
 */
namespace Pairwise
{
	using Sequencing::Sequence;

	/**
	 * The LinearSequencer class implements the linear sequencing pairwise scoring scheme.
	 * The linear scoring scheme is defined by linearly penalizing gaps in the provided
	 * sequences.
	 */
	class LinearSequencer : public PairwiseSequencer
	{
	private:
		MatrixDataType gap_penalty;
		bool global;

		inline MatrixDataType max(const MatrixDataType x, const MatrixDataType y, const MatrixDataType z);
		inline MatrixDataType max(const MatrixDataType w, const MatrixDataType x, const MatrixDataType y, const MatrixDataType z);
		
		std::vector<std::vector<MatrixDataType> > sequence_matrix_create(const bool global, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2);
		void getHighestScore(std::vector<std::vector<MatrixDataType> >& sequence_matrix, int& i_index, int& j_index);
		PairwiseAlignment sequence_matrix_traceback(const bool global, std::vector<std::vector<MatrixDataType> >& sequence_matrix, const SubstitutionMatrix& substitution_matrix, const Sequence& sequence1, const Sequence& sequence2);
	
	protected:

	public:
		/** 
		 * Creates a new LinearSequencer based on the provided gap penalty. If no gap
		 * penalty is provided, the default is 0.
		 *
		 * @param new_gap_penalty The gap penalty that will be used in this LinearSequencer
		 */
		LinearSequencer(int new_gap_penalty = 0);

		/**
		 * Default Destructor.
		 */
		~LinearSequencer();


		/**
		 * This function sequences two sequences based on the linear scoring 
		 * scheme using a substitution matrix.
		 *
		 * @param gloabl If true the function with use the linear global 
		 * alignment algoirhthm to score the sequences. If this parameter is false
		 * the function will use the linear local alignment algorithm to score the sequences.
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