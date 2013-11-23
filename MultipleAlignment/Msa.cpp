#include "msa.h"
#include "../NeighborJoin/NeighborJoin.h"
#include "../NeighborJoin/GeneticTreeNode.h"
#include <iostream>

using namespace std;
using namespace Pairwise;
using namespace Sequencing;
using namespace MultipleSequencing;

MultipleSequenceAlignment::MultipleSequenceAlignment(void)
{
	gapPenalty = -1;
}


MultipleSequenceAlignment::~MultipleSequenceAlignment(void)
{
}

/* Aligns multiple sequences using a distance matrix and the alignments of each pair of sequences.
 * Params:	
 *			distanceMatrix - Matrix containing the distances between each pair of sequences.
 *			pairwiseAlignments - Matrix containing each pair of aligned sequences.
 *			substitutionMatrix - The substitution matrix to be used.
 * Return: 
 *			A vector containing the aligned sequences.
 */
Alignment MultipleSequenceAlignment::align_sequences(	const vector< vector<double> > &distanceMatrix, 
														vector< Sequence > &sequences,
														const SubstitutionMatrix &substitutionMatrix)
{
	//construct guide tree
	NeighborJoin nj;
	GeneticTreeNode* guideTree = nj.construct_tree(distanceMatrix, sequences);

	//construct msa from guide tree
	Alignment finalAlignment = align_sequences_recursive(guideTree);


	//return msa
	return finalAlignment;
}

/* Traverses the given guide tree recursively aligning sequences to form a single alignment.
 * If a leaf node is found the alignment at that node is returned, otherwise the two children 
 * of the node are aligned.
 */
Alignment MultipleSequenceAlignment::align_sequences_recursive(GeneticTreeNode* head)
{
	if (head->num_children() > 2) {
		//error, unable to align more than two sequences/alignments 
		std::cerr << "Multiiple sequence alignment failed.  Guide tree contains node with more than two children" << endl;
	} else if (head->num_children() == 0) {
		//leaf node, return alignment
		return head->get_alignment();
	} else {
		//align children's sequences/alignments
		vector<GeneticTreeNode *> children = head->get_children();
		Alignment a1 = align_sequences_recursive(children[0]);
		Alignment a2 = align_sequences_recursive(children[1]);
		return align(a1, a2);
	}
}

Alignment MultipleSequenceAlignment::align(Alignment &a1, Alignment &a2) 
{
	int a1length = a1.getSequence(0).length();
	int a2length = a2.getSequence(0).length();

	vector< vector<double> > v(a1length, vector<double>(a2length));

	v[0][0] = 0;
	for (int i = 1; i < a1length; ++i) {
		v[i][0] = v[i-1][0] + gapPenalty;
	}
	for (int j = 1; j < a2length; ++j) {
		v[0][j] = v[0][j-1] + gapPenalty;
	}
	for (int i = 1; i < a1length; ++i) {
		for (int j = 1; j < a2length; ++j)
		{
			double Match = v[i-1][j-1] + psp(a1, a2, i, j);
			double Delete = v[i-1][j] + gapPenalty;
			double Insert = v[i][j-1] + gapPenalty;
			v[i][j] = max(Match, max(Insert, Delete));
		}
	}
	//TODO construct alignment
	vector<string> aA(a1.size());
	vector<string> aB(a2.size());

	int i = a1.getSequence(0).length()-1;
	int j = a2.getSequence(0).length()-1;

	while (i > 0 && j > 0)
	{
		double Score = v[i][j];
		double ScoreDiag = v[i - 1][j - 1];
		double ScoreUp = v[i][j - 1];
		double ScoreLeft = v[i - 1][j];
		if (Score == ScoreDiag + psp(a1, a2, i, j))
		{
			prepend(a1, i, aA); 
			prepend(a2, j, aB);
			i = i - 1;
			j = j - 1;
		}
		if (Score == ScoreLeft + gapPenalty)
		{
			prepend(a1, i, aA); 
			prepend(substitutionMatrix.getGapCharacter(), aB);
			i = i - 1;
		}
		else if (Score == ScoreUp + gapPenalty)
		{
			prepend(substitutionMatrix.getGapCharacter(), aA); 
			prepend(a2, j, aB);
			j = j - 1;
		}
	}
	while (i > 0)
	{
		prepend(a1, i, aA); 
		prepend(substitutionMatrix.getGapCharacter(), aB);
		i = i - 1;
	}
	while (j > 0)
	{
		prepend(substitutionMatrix.getGapCharacter(), aA); 
		prepend(a2, j, aB);
		j = j - 1;
	}
	Alignment returnAlignment;
	for (int i = 0; i < a1.size(); ++i) {
		Sequence s(a1.getSequence(i).getName(), aA[i]);
		returnAlignment.addSequence(s);
	}
	for (int i = 0; i < a2.size(); ++i) {
		Sequence s(a2.getSequence(i).getName(), aB[i]);
		returnAlignment.addSequence(s);
	}
	return returnAlignment;
}

/* Calculates the similarity between two specific columns of two alignments.  
 * Uses the formula:
 *			PSP(A1[i], A2[j]) = SUM over x,y that exist in A { gxi*gyj*s(x,y) }
 * Where:
 *			A1, A2 are the alignments being compared
 *			A is the alphabet of possible sequence elements
 *			gxi is the frequency of symbol x in column i of A1
 *			gyj is the frequency of symbol y in column j of A2
 *			s(x, y) is the substitution value for x and y
 */
double MultipleSequenceAlignment::psp(Alignment &a1, Alignment &a2, int i, int j) 
{
	double sum = 0;

	for (int x = 0; x < substitutionMatrix.getColumnCount(); ++x) {
		for (int y = 0; y < substitutionMatrix.getColumnCount(); ++y) {
			sum += column_symbol_count(a1, i, (char)substitutionMatrix.get(x, 0))*column_symbol_count(a2, j, (char)substitutionMatrix.get(y, 0))*substitutionMatrix.score(i,j);
		}
	}
	return sum;
}

int MultipleSequenceAlignment::column_symbol_count(Alignment &a, int index, char symbol) 
{
	int count = 0;
	for (int i = 0; i < a.size(); ++i) {
		if (a.getSequence(i)[index] == symbol) {
			++count;
		}
	}
	return count;
}
void MultipleSequenceAlignment::prepend(Alignment &original, int index, vector<string> &a) {
	for (int i = 0; i < a.size(); ++i) {
		a[i] = original.getSequence(i)[index] + a[i];
	}
	
}
void MultipleSequenceAlignment::prepend(char c, vector<string> &a) {
	for (int i = 0; i < a.size(); ++i) {
		a[i] = c + a[i];
	}
	
}


void MultipleSequenceAlignment::run_tests() {
	test_align_sequences();
}
void MultipleSequenceAlignment::test_align_sequences() {
	//construct distance matrix
	vector<double> d0;
	d0.push_back(0);
	d0.push_back(5);
	d0.push_back(4);
	d0.push_back(7);
	d0.push_back(6);
	d0.push_back(8);

	vector<double> d1;
	d1.push_back(5);
	d1.push_back(0);
	d1.push_back(7);
	d1.push_back(10);
	d1.push_back(9);
	d1.push_back(11);

	vector<double> d2;
	d2.push_back(4);
	d2.push_back(7);
	d2.push_back(0);
	d2.push_back(7);
	d2.push_back(6);
	d2.push_back(8);

	vector<double> d3;
	d3.push_back(7);
	d3.push_back(10);
	d3.push_back(7);
	d3.push_back(0);
	d3.push_back(5);
	d3.push_back(9);

	vector<double> d4;
	d4.push_back(6);
	d4.push_back(9);
	d4.push_back(6);
	d4.push_back(5);
	d4.push_back(0);
	d4.push_back(8);

	vector<double> d5;
	d5.push_back(8);
	d5.push_back(11);
	d5.push_back(8);
	d5.push_back(9);
	d5.push_back(8);
	d5.push_back(0);

	vector< vector<double> > d;
	d.push_back(d0);
	d.push_back(d1);
	d.push_back(d2);
	d.push_back(d3);
	d.push_back(d4);
	d.push_back(d5);

	//construct sequences
	Sequence s1("A", "ACGTACGACT");
	Sequence s2("B", "AGCATCAGC");
	Sequence s3("C", "GACTAGCG");
	Sequence s4("D", "GACTACGATCG");
	Sequence s5("E", "GATCAGCTACTGACG");
	Sequence s6("F", "GACTACGATCAGCTA");
	
	vector<Sequence> sequences;
	sequences.push_back(s1);
	sequences.push_back(s2);
	sequences.push_back(s3);
	sequences.push_back(s4);
	sequences.push_back(s5);
	sequences.push_back(s6);

	SubstitutionMatrix subMatrix;
	subMatrix.load("C:\\Users\\Jon\\Documents\\Visual Studio 2010\\Projects\\NeighborJoinTest\\NeighborJoinTest\\Debug\\BLOSUM62.txt");

	MultipleSequenceAlignment msa;
	Alignment returnAlignment = msa.align_sequences(d, sequences, subMatrix);

	cout << "ALIGNMENT:" << endl;
	for (int i = 0; i < returnAlignment.size(); ++i) {
		cout << "Name: " << returnAlignment.getSequence(i).getName() << " Sequence: " << returnAlignment.getSequence(i).getSequence() << endl;
	}
}
