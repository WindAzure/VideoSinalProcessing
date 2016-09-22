#include <iostream>
#include "HuffmanTreeFactory.h"

void PrepareData(vector<HuffmanTreeNode> &codeTableData, vector<string> &encodeData)
{
	codeTableData.push_back(HuffmanTreeNode("A", 0.45));
	codeTableData.push_back(HuffmanTreeNode("B", 0.15));
	codeTableData.push_back(HuffmanTreeNode("C", 0.35));
	codeTableData.push_back(HuffmanTreeNode("STOP", 0.05));

	encodeData.push_back("A");
	encodeData.push_back("A");
	encodeData.push_back("C");
	encodeData.push_back("A");
	encodeData.push_back("B");
	encodeData.push_back("A");
	encodeData.push_back("A");
	encodeData.push_back("C");
	encodeData.push_back("A");
	encodeData.push_back("STOP");
}

vector<string> EncodePart(HuffmanTreeFactory &factory, vector<string>& encodeData)
{
	cout << "Encode" << endl;
	vector<string> encodedResult = factory.Encode(encodeData);
	for (int i = 0; i < encodedResult.size(); i++)
	{
		cout << encodeData[i] << " ===> " << encodedResult[i] << endl;
	}
	return encodedResult;
}

vector<string> DecodePart(HuffmanTreeFactory &factory, vector<string>& decodeData)
{
	cout << endl << "Decode" << endl;
	vector<string> decodedResult = factory.Decode(decodeData);
	for (int i = 0; i < decodedResult.size(); i++)
	{
		cout << decodeData[i] << " ===> " << decodedResult[i] << endl;
	}
	return decodedResult;
}

int main()
{
	vector<HuffmanTreeNode> codeTableData;
	vector<string> encodeData;
	PrepareData(codeTableData, encodeData);

	HuffmanTreeFactory factory;
	factory.MakeTree(codeTableData);

	vector<string> decodeData = EncodePart(factory, encodeData);
	DecodePart(factory, decodeData);

	system("pause");
	return 0;
}