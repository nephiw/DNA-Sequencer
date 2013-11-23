#pragma once
#include <vector>
#include <list>
#include "../NeighborJoin/GeneticTreeNode.h"
#include "../Sequencing/Sequence.h"

#ifndef ___NEIGHBORJOIN___
#define ___NEIGHBORJOIN___

class NeighborJoin
{
private:
	//members
	std::list<GeneticTreeNode*> genetic_tree_list;

	//methods
	void neighbor_join( const std::vector< std::vector<double> >&, int);
	double sum_column(const std::vector< std::vector<double> >&, int);
	double sum_row(const std::vector< std::vector<double> >&, int);
	std::vector< std::vector<double> > map_distance_matrix(const std::vector< std::vector<double> >&, int, int);
	void join_tree_nodes(int, int);
	void init_genetic_tree_list(int, const std::vector<std::string>& sequence_names);
	void init_genetic_tree_list(const std::vector<Sequencing::Sequence> &sequences);

	//tests
	void test_sum_row();
	void test_sum_column();
	void test_neighbor_join();
	void test_map_distance_matrix();
	void test_join_tree_nodes();
	void test_init_genetic_tree_list();

	void print_array(std::vector< std::vector<double> > a);
	void print_tree(std::list<GeneticTreeNode *>);

public:
	//constructors
	NeighborJoin(void);
	~NeighborJoin(void);

	//public interfaces
	std::string construct_tree(const std::vector< std::vector<double> >&, const std::vector<std::string>& sequence_names);
	GeneticTreeNode* construct_tree(const std::vector< std::vector<double> > &distanceMatrix, const std::vector< Sequencing::Sequence > &sequences);

	//tests
	void run_tests();
};


#endif
