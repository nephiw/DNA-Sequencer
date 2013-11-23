#include <iostream>
#include <fstream>
#include "Pairwise/SubstitutionMatrix.h"
#include "Pairwise/LinearSequencer.h"
#include "Pairwise/AffineSequencer.h"
#include "NeighborJoin/NeighborJoin.h"
#include "NeighborJoin/GeneticTreeNode.h"
#include "MultipleAlignment/Msa.h"

int main()
{
	using Sequencing::Sequence;
	using Pairwise::PairwiseAlignment;
	using Pairwise::SubstitutionMatrix;
	using Pairwise::LinearSequencer;
	using Pairwise::AffineSequencer;
	using MultipleSequencing::MultipleSequenceAlignment;

	/*
	SubstitutionMatrix sm = SubstitutionMatrix();
	sm.load("BLOSUM62.txt");
	
	LinearSequencer ds = LinearSequencer(0);
	PairwiseAlignment alignment = ds.sequence(true, sm, Sequence("ACAGCTAGCTC"), Sequence("ACGATC"));

	for ( int i = 0; i < alignment.size(); i++ )
		std::cout << alignment.getSequence(i) << std::endl;

	std::cout << "Final Score: " << alignment.getScore();

	std::cout << std::endl;
	std::cout << std::endl;
	
	AffineSequencer as = AffineSequencer(-10, -1);
	PairwiseAlignment alignment1 = as.sequence(true, sm, Sequence("ACRACTA"), Sequence("ACRTCRA"));

	for ( int i = 0; i < alignment1.size(); i++ )
		std::cout << alignment1.getSequence(i) << std::endl;

	std::cout << "Final Score: " << alignment1.getScore();
	*/
	std::cin.get();
	
}