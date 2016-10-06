#ifndef DCT_MANAGER_H
#define DCT_MANAGER_H

#include "ConstParameter.h"

class DctManager
{
private:
public:
	DctManager();
	virtual ~DctManager();
	void Dct(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE]);
	void InverseDct(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE]);
};

#endif