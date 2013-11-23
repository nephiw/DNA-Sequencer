#include <string>
#include <vector>
#include "../NeighborJoin/GeneticTreeNode.h"
#include "../Sequencing/Sequence.h"
#include "../Sequencing/Alignment.h"
#include "../Pairwise/SubstitutionMatrix.h"

#ifndef ___MSA___
#define ___MSA___

/**
 * The MultipleSequencing namespace contains all algorithms relating to multiple sequencing.
 **/
namespace MultipleSequencing {

	class MultipleSequenceAlignment
	{
	public:
		MultipleSequenceAlignment(void);
		~MultipleSequenceAlignment(void);

		Sequencing::Alignment align_sequences(	const std::vector< std::vector<double> > &distanceMatrix, 
												std::vector< Sequencing::Sequence > &sequences,
												const Pairwise::SubstitutionMatrix &substitutionMatrix);


		//testing
		void run_tests();
		

	private:
		double psp(Sequencing::Alignment &a1, Sequencing::Alignment &a2, int i, int j);
		int column_symbol_count( Sequencing::Alignment &a, int index, char symbol);
		Sequencing::Alignment align_sequences_recursive(GeneticTreeNode* head);
		Sequencing::Alignment align(Sequencing::Alignment &a1, Sequencing::Alignment &a2);
		void prepend(Sequencing::Alignment &original, int index, std::vector<std::string> &a);
		void prepend(char c, std::vector<std::string> &a);

		int gapPenalty;
		Pairwise::SubstitutionMatrix substitutionMatrix;
		
		//testing
		void test_align_sequences();
	};

}

#endif
