#ifndef ENTROPY_CODING_MANAGER_H
#define ENTORPY_CODING_MANAGER_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class EntropyCodingManager
{
private:
	map<string, string> _huffmanTable;
	map<string, string> _dcTable;
	string AmplitudeCompression(int number);
	int AmplitudeDeCompression(string numberString);
	string LookupTable(string encodedString, map<string, string>& table);

public:
	EntropyCodingManager();
	virtual ~EntropyCodingManager();
	vector<string> Encode(vector<int> zigZagList, int previousDC);
	vector<int> Decode(string encodeString, int previousDC);
};

#endif