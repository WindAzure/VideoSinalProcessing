#ifndef ZIG_ZAG_MANAGER_H
#define ZIG_ZAG_MANAGER_H

#include <vector>
#include "ConstParameter.h"

using namespace std;

class ZigZagManager
{
private:
	static const int _zigZagArray[BLOCK_SIZE*BLOCK_SIZE];
	vector<pair<int, int>> _zigZagTable;

public:
	ZigZagManager();
	virtual ~ZigZagManager();
	void GetZigZagList(int matrix[BLOCK_SIZE][BLOCK_SIZE], vector<int> &zigZagList);
	void Inverse(vector<int> zigZagList, int matrix[BLOCK_SIZE][BLOCK_SIZE]);
};

#endif