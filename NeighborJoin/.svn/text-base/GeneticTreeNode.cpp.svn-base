#include <string>
#include "GeneticTreeNode.h"

using namespace std;
using namespace Sequencing;

GeneticTreeNode::GeneticTreeNode(string label) {
	Sequence newSequence(label, "");
	alignment.addSequence(newSequence);
}
GeneticTreeNode::GeneticTreeNode(Sequence sequence) {
	alignment.addSequence(sequence);
}
GeneticTreeNode::~GeneticTreeNode(void) {
}

void GeneticTreeNode::add_child(GeneticTreeNode *child) {
	children.push_back(child);
}
void GeneticTreeNode::add_child(string label) {
	add_child(new GeneticTreeNode(label));
}
int GeneticTreeNode::num_children() {
	return children.size();
}
string GeneticTreeNode::to_newick() {
	if (num_children() == 0) {
		return alignment.getSequence(0).getName() + ":" + alignment.getSequence(0).getSequence();
	} else {
		string returnString = "(";
		for (int i = 0; i < children.size(); ++i) {
			returnString += children[i]->to_newick();
			if (i < children.size()-1) {
				returnString += ",";
			}
		}
		returnString += ")" + alignment.getSequence(0).getName();
		return returnString;
	}
}