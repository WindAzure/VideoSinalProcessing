#include "ArithmeticCodingFactory.h"
#include <iostream>
#include <stdexcept>

ArithmeticCodingFactory::ArithmeticCodingFactory()
{
}

ArithmeticCodingFactory::~ArithmeticCodingFactory()
{
}

string ArithmeticCodingFactory::MappingAlphabets(float probability)
{
	for (map<string, pair<float, float>>::iterator it = _cumulativeTable.begin(); it != _cumulativeTable.end(); it++)
	{
		if (it->second.first <= probability && probability < it->second.second)
		{
			return it->first;
		}
	}
	return "";
}

void ArithmeticCodingFactory::SetCodeTable(vector<pair<string, float>> codeTable)
{
	float st = 0;
	for (int i = 0; i < codeTable.size(); i++)
	{
		_cumulativeTable[codeTable[i].first] = make_pair(st, st + codeTable[i].second);
		st += codeTable[i].second;
	}
}

float ArithmeticCodingFactory::Encode(vector<string> alphabets)
{
	try
	{
		map<string, pair<float, float>>::iterator it = _cumulativeTable.find(alphabets[0]);
		float st = it->second.first;
		float ed = it->second.second;
		cout << alphabets[0] << " ====> ";
		printf("lower= %f upper= %f range= %f log2= %f\n", st, ed, ed - st, log2(1.0 / (ed - st)));
		for (int i = 1; i < alphabets.size(); i++)
		{
			float range = ed - st;
			float newSt = st + range*_cumulativeTable[alphabets[i]].first;
			float newEd = st + range*_cumulativeTable[alphabets[i]].second;
			st = newSt;
			ed = newEd;
			cout << alphabets[i]<<" ====> ";
			printf("lower= %f upper= %f range= %f log2= %f\n", st, ed, ed - st, log2(1.0/(ed - st)));
		}
		return (st + ed) / 2.0;
	}
	catch (exception e)
	{
		throw runtime_error("Encoded Text Not Found");
	}
}

vector<string> ArithmeticCodingFactory::Decode(float arithmeticNumber)
{
	vector<string> result;
	string alphabets = "";
	do
	{
		alphabets = MappingAlphabets(arithmeticNumber);
		result.push_back(alphabets);
		float range = _cumulativeTable[alphabets].second - _cumulativeTable[alphabets].first;
		arithmeticNumber = (arithmeticNumber - _cumulativeTable[alphabets].first) / range;
	} while (alphabets != "!");
	return result;
}