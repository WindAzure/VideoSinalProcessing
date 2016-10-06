#include "ZigZagManager.h"
#include <limits>

ZigZagManager::ZigZagManager()
{
	_zigZagTable.push_back(make_pair(0, 0));
	_zigZagTable.push_back(make_pair(0, 1));
	_zigZagTable.push_back(make_pair(1, 0));
	_zigZagTable.push_back(make_pair(2, 0));
	_zigZagTable.push_back(make_pair(1, 1));
	_zigZagTable.push_back(make_pair(0, 2));
	_zigZagTable.push_back(make_pair(0, 3));
	_zigZagTable.push_back(make_pair(1, 2));
	_zigZagTable.push_back(make_pair(2, 1));
	_zigZagTable.push_back(make_pair(3, 0));
	_zigZagTable.push_back(make_pair(4, 0));
	_zigZagTable.push_back(make_pair(3, 1));
	_zigZagTable.push_back(make_pair(2, 2));
	_zigZagTable.push_back(make_pair(1, 3));
	_zigZagTable.push_back(make_pair(0, 4));
	_zigZagTable.push_back(make_pair(0, 5));
	_zigZagTable.push_back(make_pair(1, 4));
	_zigZagTable.push_back(make_pair(2, 3));
	_zigZagTable.push_back(make_pair(3, 2));
	_zigZagTable.push_back(make_pair(4, 1));
	_zigZagTable.push_back(make_pair(5, 0));
	_zigZagTable.push_back(make_pair(6, 0));
	_zigZagTable.push_back(make_pair(5, 1));
	_zigZagTable.push_back(make_pair(4, 2));
	_zigZagTable.push_back(make_pair(3, 3));
	_zigZagTable.push_back(make_pair(2, 4));
	_zigZagTable.push_back(make_pair(1, 5));
	_zigZagTable.push_back(make_pair(0, 6));
	_zigZagTable.push_back(make_pair(0, 7));
	_zigZagTable.push_back(make_pair(1, 6));
	_zigZagTable.push_back(make_pair(2, 5));
	_zigZagTable.push_back(make_pair(3, 4));
	_zigZagTable.push_back(make_pair(4, 3));
	_zigZagTable.push_back(make_pair(5, 2));
	_zigZagTable.push_back(make_pair(6, 1));
	_zigZagTable.push_back(make_pair(7, 0));
	_zigZagTable.push_back(make_pair(7, 1));
	_zigZagTable.push_back(make_pair(6, 2));
	_zigZagTable.push_back(make_pair(5, 3));
	_zigZagTable.push_back(make_pair(4, 4));
	_zigZagTable.push_back(make_pair(3, 5));
	_zigZagTable.push_back(make_pair(2, 6));
	_zigZagTable.push_back(make_pair(1, 7));
	_zigZagTable.push_back(make_pair(2, 7));
	_zigZagTable.push_back(make_pair(3, 6));
	_zigZagTable.push_back(make_pair(4, 5));
	_zigZagTable.push_back(make_pair(5, 4));
	_zigZagTable.push_back(make_pair(6, 3));
	_zigZagTable.push_back(make_pair(7, 2));
	_zigZagTable.push_back(make_pair(7, 3));
	_zigZagTable.push_back(make_pair(6, 4));
	_zigZagTable.push_back(make_pair(5, 5));
	_zigZagTable.push_back(make_pair(4, 6));
	_zigZagTable.push_back(make_pair(3, 7));
	_zigZagTable.push_back(make_pair(4, 7));
	_zigZagTable.push_back(make_pair(5, 6));
	_zigZagTable.push_back(make_pair(6, 5));
	_zigZagTable.push_back(make_pair(7, 4));
	_zigZagTable.push_back(make_pair(7, 5));
	_zigZagTable.push_back(make_pair(6, 6));
	_zigZagTable.push_back(make_pair(5, 7));
	_zigZagTable.push_back(make_pair(6, 7));
	_zigZagTable.push_back(make_pair(7, 6));
	_zigZagTable.push_back(make_pair(7, 7));
}

ZigZagManager::~ZigZagManager()
{
}

void ZigZagManager::GetZigZagList(int matrix[BLOCK_SIZE][BLOCK_SIZE], vector<int> &zigZagList)
{
	for (int i = 0; i < _zigZagTable.size(); i++)
	{
		zigZagList.push_back(matrix[_zigZagTable[i].first][_zigZagTable[i].second]);
	}

	int zeroIndex = -1;
	for (int i = zigZagList.size() - 1; i >= 0; i--)
	{
		if (zigZagList[i] == 0)
		{
			zeroIndex = i;
		}
		else
		{
			break;
		}
	}
	if (zeroIndex != -1)
	{
		zigZagList.erase(zigZagList.begin() + zeroIndex, zigZagList.end());
		zigZagList.push_back(numeric_limits<int>::max());
	}
}