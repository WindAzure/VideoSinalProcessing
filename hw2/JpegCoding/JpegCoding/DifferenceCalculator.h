#ifndef DIFFERENCE_CALCULATOR_H
#define DIFFERENCE_CALCULATOR_H

#include "ConstParameter.h"

class DifferenceCalculator
{
private:

public:
	DifferenceCalculator();
	virtual ~DifferenceCalculator();
	float CalculateMSE(int A[BLOCK_SIZE][BLOCK_SIZE], int B[BLOCK_SIZE][BLOCK_SIZE]);
	float CalculatePSNR(int A[BLOCK_SIZE][BLOCK_SIZE], int B[BLOCK_SIZE][BLOCK_SIZE]);
};

#endif