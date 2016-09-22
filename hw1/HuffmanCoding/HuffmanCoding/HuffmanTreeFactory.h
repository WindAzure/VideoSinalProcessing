#ifndef HUFFMAN_TREE_FACTORY_H
#define HUFFMAN_TREE_FACTORY_H

#include <queue>
#include <map>
#include "HuffmanTreeNode.h"

class HuffmanTreeFactory
{
private:
	HuffmanTreeNode *_tree = NULL;
	map<string, string> _codeTable;
	priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, HuffmanTreeNodeComparor> _sortedData;

	void CombineNode(HuffmanTreeNode *leftNode, HuffmanTreeNode *rightNode);
	string TraversalTree(HuffmanTreeNode *currentNode, string targetAlphabet, string& alphabetList);
	void DeleteTree(HuffmanTreeNode *currentNode);

public:
	HuffmanTreeFactory();
	virtual ~HuffmanTreeFactory();
	void MakeTree(vector<HuffmanTreeNode> data);
	vector<string> Encode(vector<string> alphabets);
	vector<string> Decode(vector<string> alphabets);
};

#endif