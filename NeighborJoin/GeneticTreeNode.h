#pragma once
#include <string>
#include <vector>
#include "../Sequencing/Sequence.h"
#include "../Sequencing/Alignment.h"

class GeneticTreeNode
{
public:
	GeneticTreeNode(std::string label);
	GeneticTreeNode(Sequencing::Sequence);
	GeneticTreeNode(const GeneticTreeNode&);
	~GeneticTreeNode(void);

	void add_child(GeneticTreeNode *);
	void add_child(std::string label);
	
	int num_children();

	Sequencing::Alignment get_alignment() { return alignment; };
	std::vector<GeneticTreeNode*> get_children() { return children; };

	std::string to_newick();

private:
	Sequencing::Alignment alignment;

	std::vector<GeneticTreeNode*> children;
};

