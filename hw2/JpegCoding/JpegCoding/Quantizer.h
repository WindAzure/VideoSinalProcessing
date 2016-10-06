#ifndef QUANTIZER_H
#define QUANTIZER_H

#include "ConstParameter.h"

class Quantizer
{
private:
	const static int quantizationTable[BLOCK_SIZE][BLOCK_SIZE];


public:
	Quantizer();
	virtual ~Quantizer();
	void Quantize(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE]);
	void InverseQuantize(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE]);
};

#endif