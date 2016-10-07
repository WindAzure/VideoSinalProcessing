#include "ZigZagManager.h"
#include <limits>

const int ZigZagManager::_zigZagArray[BLOCK_SIZE*BLOCK_SIZE] =
{
	0, 1, 5, 6, 14, 15, 27, 28,
	2, 4, 7, 13, 16, 26, 29, 42,
	3, 8, 12, 17, 25, 30, 41, 43,
	9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63,
};

ZigZagManager::ZigZagManager()
{
	int len = BLOCK_SIZE*BLOCK_SIZE;
	_zigZagTable.resize(len);
	for (int i = 0; i < len; i++)
	{
		_zigZagTable[_zigZagArray[i]] = make_pair(i / BLOCK_SIZE, i%BLOCK_SIZE);
	}
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

void ZigZagManager::Inverse(vector<int> zigZagList, int matrix[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		memset(matrix[i], 0, sizeof(matrix[i]));
	}
	int len = BLOCK_SIZE*BLOCK_SIZE;
	for (int i = 0; i < zigZagList.size(); i++)
	{
		if (zigZagList[i] != numeric_limits<int>::max())
		{
			bool isContinue = true;
			for (int j = 0; j < len && isContinue; j++)
			{
				if (_zigZagArray[j] == i)
				{
					matrix[j / BLOCK_SIZE][j%BLOCK_SIZE] = zigZagList[i];
					isContinue = false;
				}
			}
		}
	}
}