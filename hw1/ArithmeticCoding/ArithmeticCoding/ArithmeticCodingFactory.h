#ifndef ARITHMETIC_CODING_FACTORY_H
#define ARITHMETIC_CODING_FACTORY_H

#include <vector>
#include <map>
#include <string>

using namespace std;

class ArithmeticCodingFactory
{
private:
	map<string, pair<float, float>> _cumulativeTable;
	string MappingAlphabets(float probability);

public:
	ArithmeticCodingFactory();
	virtual ~ArithmeticCodingFactory();
	void SetCodeTable(vector<pair<string, float>> codeTable);
	float Encode(vector<string> alphabets);
	vector<string> Decode(float arithmeticNumber);
};

#endif