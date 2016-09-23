#include <iostream>
#include "ArithmeticCodingFactory.h"

void PrepareData(vector<pair<string, float>> &codeTableData, vector<string> &encodeData)
{
	codeTableData.push_back(make_pair("a", 0.1));
	codeTableData.push_back(make_pair("e", 0.2));
	codeTableData.push_back(make_pair("h", 0.2));
	codeTableData.push_back(make_pair("l", 0.3));
	codeTableData.push_back(make_pair("o", 0.1));
	codeTableData.push_back(make_pair("!", 0.1));

	encodeData.push_back("h");
	encodeData.push_back("e");
	encodeData.push_back("l");
	encodeData.push_back("l");
	encodeData.push_back("o");
	encodeData.push_back("!");
}

float EncodePart(ArithmeticCodingFactory &factory, vector<string>& encodeData)
{
	cout << "Encode" << endl;
	float encodedResult = factory.Encode(encodeData);
	for (int i = 0; i < encodeData.size(); i++)
	{
		cout << encodeData[i];
	}
	cout << " ===> " << encodedResult << endl;
	return encodedResult;
}

vector<string> DecodePart(ArithmeticCodingFactory &factory, float decodeData)
{
	cout << endl << "Decode" << endl;
	vector<string> decodedResult = factory.Decode(decodeData);
	cout << decodeData << " ===> ";
	for (int i = 0; i < decodedResult.size(); i++)
	{
		cout << decodedResult[i];
	}
	cout << endl;
	return decodedResult;
}

int main()
{
	vector<pair<string, float>> codeTableData;
	vector<string> encodeData;
	PrepareData(codeTableData, encodeData);

	ArithmeticCodingFactory factory;
	factory.SetCodeTable(codeTableData);

	float decodeData = EncodePart(factory, encodeData);
	DecodePart(factory, decodeData);

	system("pause");
	return 0;
}