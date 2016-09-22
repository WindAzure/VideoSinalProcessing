#ifndef HUFFMAN_TREE_NODE_H
#define HUFFMAN_TREE_NODE_H

#include <string>

using namespace std;

class HuffmanTreeNode
{
	friend class HuffmanTreeFactory;

private:
	HuffmanTreeNode *LeftLink = NULL;
	HuffmanTreeNode *RightLink = NULL;

public:
	string Alphabet;
	float Probability;

	HuffmanTreeNode(string alphabet, float probability)
	{
		Alphabet = alphabet;
		Probability = probability;
	}
};

struct HuffmanTreeNodeComparor
{
	HuffmanTreeNodeComparor(){}
	bool operator()(const HuffmanTreeNode* node1, const HuffmanTreeNode* node2) const
	{
		return node1->Probability > node2->Probability;
	};
};

#endif