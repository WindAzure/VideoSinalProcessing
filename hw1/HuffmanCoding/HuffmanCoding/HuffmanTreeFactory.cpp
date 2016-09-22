#include "HuffmanTreeFactory.h"
#include <queue>

void HuffmanTreeFactory::CombineNode(HuffmanTreeNode *leftNode, HuffmanTreeNode *rightNode)
{
	float probability = leftNode->Probability + rightNode->Probability;
	HuffmanTreeNode *node = new HuffmanTreeNode("", probability);
	node->LeftLink = leftNode;
	node->RightLink = rightNode;
	_tree = node;
	_sortedData.push(node);
}

string HuffmanTreeFactory::TraversalTree(HuffmanTreeNode *currentNode, string targetAlphabet, string& alphabetList)
{
	if (currentNode == NULL)
	{
		return "";
	}
	else if (currentNode->Alphabet == targetAlphabet)
	{
		string result = alphabetList;
		return result;
	}

	alphabetList.push_back('0');
	string leftResult = TraversalTree(currentNode->LeftLink, targetAlphabet, alphabetList);
	alphabetList.pop_back();
	if (leftResult != "")
	{
		return leftResult;
	}

	alphabetList.push_back('1');
	string rightResult = TraversalTree(currentNode->RightLink, targetAlphabet, alphabetList);
	alphabetList.pop_back();
	return rightResult;
}

void HuffmanTreeFactory::DeleteTree(HuffmanTreeNode *currentNode)
{
	if (currentNode == NULL)
	{
		return;
	}

	DeleteTree(currentNode->LeftLink);
	DeleteTree(currentNode->RightLink);
	delete currentNode;
}

HuffmanTreeFactory::HuffmanTreeFactory()
{
}

HuffmanTreeFactory::~HuffmanTreeFactory()
{
	DeleteTree(_tree);
}

void HuffmanTreeFactory::MakeTree(vector<HuffmanTreeNode> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		HuffmanTreeNode * node = new HuffmanTreeNode(data[i].Alphabet, data[i].Probability);
		_sortedData.push(node);
	}

	while (_sortedData.size() > 1)
	{
		HuffmanTreeNode *leftNode = _sortedData.top();
		_sortedData.pop();

		HuffmanTreeNode *rightNode = _sortedData.top();
		_sortedData.pop();

		CombineNode(leftNode, rightNode);
	}
	_sortedData.pop();

	for (int i = 0; i < data.size(); i++)
	{
		string temp = "";
		string encodedText = TraversalTree(_tree, data[i].Alphabet, temp);
		_codeTable[data[i].Alphabet] = encodedText;
	}
}

vector<string> HuffmanTreeFactory::Encode(vector<string> alphabets)
{
	vector<string> results;
	for (int i = 0; i < alphabets.size(); i++)
	{
		map<string, string>::iterator it = _codeTable.find(alphabets[i]);
		if (it != _codeTable.end())
		{
			results.push_back(it->second);
		}
		else
		{
			results.push_back("Encoded Text Not Found");
		}
	}
	return results;
}

vector<string> HuffmanTreeFactory::Decode(vector<string> alphabets)
{
	vector<string> results;
	for (int i = 0; i < alphabets.size(); i++)
	{
		bool isFounded = false;
		for (map<string, string>::iterator it = _codeTable.begin(); it != _codeTable.end(); it++)
		{
			if (it->second == alphabets[i])
			{
				results.push_back(it->first);
				isFounded = true;
				break;
			}
		}
		if (!isFounded)
		{
			results.push_back("Decoded Text Not Found");
		}
	}
	return results;
}