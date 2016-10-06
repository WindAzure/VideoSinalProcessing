#include "DifferenceCalculator.h"
#include <math.h>

DifferenceCalculator::DifferenceCalculator()
{
}

DifferenceCalculator::~DifferenceCalculator()
{
}

float DifferenceCalculator::CalculateMSE(int A[BLOCK_SIZE][BLOCK_SIZE], int B[BLOCK_SIZE][BLOCK_SIZE])
{
	float sum = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			float Q = A[i][j] - B[i][j];
			sum += Q*Q;
		}
	}
	return sum / BLOCK_SIZE / BLOCK_SIZE;
}

float DifferenceCalculator::CalculatePSNR(int A[BLOCK_SIZE][BLOCK_SIZE], int B[BLOCK_SIZE][BLOCK_SIZE])
{
	return 10 * log10(255 * 255 / CalculateMSE(A, B));
}