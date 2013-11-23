#include "NeighborJoin.h"
#include <sstream>
#include <iostream>

#include <assert.h>



using namespace std;
using namespace Sequencing;

NeighborJoin::NeighborJoin(void) {
}


NeighborJoin::~NeighborJoin(void) {

}

string NeighborJoin::construct_tree(const std::vector< std::vector<double> >& distanceMatrix, const std::vector<std::string>& sequence_names) {
	int r = distanceMatrix.size();

	init_genetic_tree_list(r, sequence_names);

	neighbor_join(distanceMatrix, r);
	
	join_tree_nodes(0, 1);

	return genetic_tree_list.front()->to_newick();
}

GeneticTreeNode* NeighborJoin::construct_tree(const vector< vector<double> > &distanceMatrix, const vector< Sequence > &sequences) {
	int r = distanceMatrix.size();

	init_genetic_tree_list(sequences);

	neighbor_join(distanceMatrix, r);

	join_tree_nodes(0, 1);

	return genetic_tree_list.front();
}


void NeighborJoin::neighbor_join(const vector< vector<double> >& d, int r) {
	if (r <= 2) {
		return;
	} else {
		//compute q matrix (while keeping track of minimum q value)
		vector< vector<double> > q(r, vector<double>(r));
		double minQ=999999999;
		int minQA, minQB;
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < r; ++j) {
				if (i == j) {
					q[i][j] = 0;
				} else {
					q[i][j] = (r-2)*d[i][j] - sum_column(d, i) - sum_row(d, j);
					if (q[i][j] <= minQ) {
						minQ = q[i][j];
						minQA = i;
						minQB = j;
					}
				}
			}
		}

		//construct new distance matrix
		vector< vector<double> > newD = map_distance_matrix(d, minQA, minQB);
		
		//set new values
		for (int i = 0; i < r-1; ++i) {
			if (i != minQA && i != minQB) {
				int iMapper = 0;
				if (i > minQA || i > minQB) {
					iMapper = 1;
				}
				if (i > minQA && i > minQB) {
					iMapper = 2;
				}
				newD[newD.size()-1][i-iMapper] = 0.5*(d[minQA][i]+d[minQB][i]-d[minQA][minQB]);
				newD[i-iMapper][newD.size()-1] = newD[newD.size()-1][i-iMapper];
			}
		}

		//TODO: Record the two nodes that were joined
		join_tree_nodes(minQA, minQB);

		//recursively neighbor join the new distance matrix
		neighbor_join(newD, r-1);
	}

}
/* Sums over the second dimension of the given column in the matrix
 */
double NeighborJoin::sum_column(const vector< vector<double> >& matrix, int column) {
	if (column >= 0 && column < matrix.size()) {
		double sum = 0;
		for (vector< vector<int> >::size_type i = 0; i < matrix[column].size(); ++i) {
			sum += matrix[column][i];
		}
		return sum;
	} else {
		return 0;
	}
}
/* Sums over the first dimension of the given row in the matrix
 */
double NeighborJoin::sum_row(const vector< vector<double> >& matrix, int row) {
	double sum = 0;
	for (vector<int>::size_type i = 0; i < matrix.size(); ++i) {
		if (row >= 0 && row < matrix[i].size()) {
			sum += matrix[i][row];
		}
	}
	return sum;
}
/*  Constructs a new distance matrix with columns/rows rowA and rowB removed.
 */
vector< vector<double> > NeighborJoin::map_distance_matrix(const vector< vector<double> >& d, int rowA, int rowB) {
	vector< vector<double> > newD = d;
	if (rowA == rowB || rowA < 0 || rowB < 0 || rowA >= d.size() || rowB >= d.size()) {
		return newD;
	}
	int indexMapper = 0;
	if (rowA < rowB) { indexMapper = 1; }
	newD.erase(newD.begin()+rowA);
	newD.erase(newD.begin()+rowB-indexMapper);
	
	for (int i = 0; i < newD.size(); ++i) {
		newD[i].erase(newD[i].begin()+rowA);
		newD[i].erase(newD[i].begin()+rowB-indexMapper);
	}
	newD.push_back(vector<double>(newD.size(), 0));
	for (int i = 0; i < newD.size(); ++i) {
		newD[i].push_back(0);
	}

	return newD;
}

/* Creates a new node with nodes at index values provided as children and pushes it back on the list of nodes.
 *
 */
void NeighborJoin::join_tree_nodes(int a, int b) {
	//get nodes to join
	list<GeneticTreeNode*>::iterator aNodeItr, bNodeItr;
	aNodeItr = genetic_tree_list.begin();
	bNodeItr = genetic_tree_list.begin();
	advance(aNodeItr, a);
	advance(bNodeItr, b);
	GeneticTreeNode *aNode = *aNodeItr;
	GeneticTreeNode *bNode = *bNodeItr;

	//create new node
	GeneticTreeNode *newNode = new GeneticTreeNode("");
	newNode->add_child(aNode);
	newNode->add_child(bNode);

	//remove old nodes from list
	genetic_tree_list.erase(aNodeItr);
	genetic_tree_list.erase(bNodeItr);

	//add new node to list
	genetic_tree_list.push_front(newNode);
}
void NeighborJoin::init_genetic_tree_list(int r, const std::vector<std::string>& sequence_names) {
	genetic_tree_list.clear();
	for (int i = 0; i < r; ++i) {
		string s;
		stringstream out;
		out << sequence_names[i];
		s = out.str();
		genetic_tree_list.push_back(new GeneticTreeNode(s));
	}
}
void NeighborJoin::init_genetic_tree_list(const vector<Sequence> &sequences) {
	genetic_tree_list.clear();
	for (int i = 0; i < sequences.size(); ++i) {
		genetic_tree_list.push_back(new GeneticTreeNode(sequences[i]));
	}
}

/***************************************TESTS**************************************/

void NeighborJoin::run_tests() {
	test_sum_row();
	test_sum_column();
	test_map_distance_matrix();
	test_init_genetic_tree_list();
	test_join_tree_nodes();
	test_neighbor_join();
}
void NeighborJoin::print_array(vector< vector<double> > a) {
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < a[i].size(); ++j) {
			cout << a[j][i] << " ";
		}
		cout << endl;
	}


}
void NeighborJoin::print_tree(list<GeneticTreeNode *> tree) {
	for (list<GeneticTreeNode *>::iterator it = tree.begin(); it != tree.end(); it++) {
		cout << (*it)->to_newick() << endl;
	}
}
void  NeighborJoin::test_neighbor_join() {
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

	//NeighborJoin nj;
	//cout << nj.construct_tree(d) << endl;

}
void NeighborJoin::test_sum_row() {
	vector<double> d0;
	d0.push_back(1);
	d0.push_back(1);
	d0.push_back(1);
	d0.push_back(1);

	vector<double> d1;
	d1.push_back(2);
	d1.push_back(1);
	d1.push_back(1);
	d1.push_back(1);

	vector<double> d2;
	d2.push_back(3);
	d2.push_back(5);
	d2.push_back(6);
	d2.push_back(7);

	vector<double> d3;
	d3.push_back(4);
	d3.push_back(4);
	d3.push_back(4);
	d3.push_back(4);

	vector< vector<double> > d;
	d.push_back(d0);
	d.push_back(d1);
	d.push_back(d2);
	d.push_back(d3);


	NeighborJoin nj;

	assert(nj.sum_row(d, 0) == 10);
	assert(nj.sum_row(d, 1) == 11);
	assert(nj.sum_row(d, 2) == 12);
	assert(nj.sum_row(d, 3) == 13);

	assert(nj.sum_row(d, -1) == 0);
	assert(nj.sum_row(d, 4) == 0);
}

void NeighborJoin::test_sum_column() {
	vector<double> d0;
	d0.push_back(1);
	d0.push_back(1);
	d0.push_back(1);
	d0.push_back(1);

	vector<double> d1;
	d1.push_back(2);
	d1.push_back(1);
	d1.push_back(1);
	d1.push_back(1);

	vector<double> d2;
	d2.push_back(3);
	d2.push_back(5);
	d2.push_back(6);
	d2.push_back(7);

	vector<double> d3;
	d3.push_back(4);
	d3.push_back(4);
	d3.push_back(4);
	d3.push_back(4);

	vector< vector<double> > d;
	d.push_back(d0);
	d.push_back(d1);
	d.push_back(d2);
	d.push_back(d3);


	NeighborJoin nj;
	
	assert(nj.sum_column(d, 0) == 4);
	assert(nj.sum_column(d, 1) == 5);
	assert(nj.sum_column(d, 2) == 21);
	assert(nj.sum_column(d, 3) == 16);

	assert(nj.sum_column(d, -1) == 0);
	assert(nj.sum_column(d, 4) == 0);


}

void NeighborJoin::test_map_distance_matrix() {
	vector<double> d0;
	d0.push_back(1);
	d0.push_back(1);
	d0.push_back(1);
	d0.push_back(1);

	vector<double> d1;
	d1.push_back(2);
	d1.push_back(2);
	d1.push_back(2);
	d1.push_back(2);

	vector<double> d2;
	d2.push_back(3);
	d2.push_back(3);
	d2.push_back(3);
	d2.push_back(3);

	vector<double> d3;
	d3.push_back(4);
	d3.push_back(4);
	d3.push_back(4);
	d3.push_back(4);

	vector< vector<double> > d;
	d.push_back(d0);
	d.push_back(d1);
	d.push_back(d2);
	d.push_back(d3);

	NeighborJoin nj;
	
	vector< vector<double> > newD = nj.map_distance_matrix(d, 1, 2);
	print_array(d);
	print_array(newD);

	newD = nj.map_distance_matrix(d, 0, 1);
	print_array(d);
	print_array(newD);

	newD = nj.map_distance_matrix(d, 0, 2);
	print_array(d);
	print_array(newD);

	newD = nj.map_distance_matrix(d, 0, 3);
	print_array(d);
	print_array(newD);

	newD = nj.map_distance_matrix(d, 1, 3);
	print_array(d);
	print_array(newD);

}

void NeighborJoin::test_init_genetic_tree_list() {
	//init_genetic_tree_list(5);
	print_tree(genetic_tree_list);
}
void NeighborJoin::test_join_tree_nodes() {
	string s1 = "A";
	string s2 = "B";
	string s3 = "C";
	string s4 = "D";
	string s5 = "E";

	vector<string> s;
	s.push_back(s1);
	s.push_back(s2);
	s.push_back(s3);
	s.push_back(s4);
	s.push_back(s5);

	init_genetic_tree_list(5, s);

	join_tree_nodes(1, 2);

	print_tree(genetic_tree_list);
}
