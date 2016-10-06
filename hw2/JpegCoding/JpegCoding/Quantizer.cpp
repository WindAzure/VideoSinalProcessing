#include "Quantizer.h"
#include <math.h>

const int Quantizer::quantizationTable[BLOCK_SIZE][BLOCK_SIZE] =
{
	{ 16, 11, 10, 16, 24, 40, 51, 61 },
	{ 12, 12, 14, 19, 26, 58, 60, 55 },
	{ 14, 13, 16, 24, 40, 57, 69, 56 },
	{ 14, 17, 22, 29, 51, 87, 80, 62 },
	{ 18, 22, 37, 56, 68, 109, 103, 77 },
	{ 24, 35, 55, 64, 81, 104, 113, 92 },
	{ 49, 64, 78, 87, 103, 121, 120, 101 },
	{ 72, 92, 95, 98, 112, 100, 103, 99 }
};

Quantizer::Quantizer()
{
}

Quantizer::~Quantizer()
{
}

void Quantizer::Quantize(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			target[i][j] = round((float)source[i][j] / quantizationTable[i][j]);
		}
	}
}

void Quantizer::InverseQuantize(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			target[i][j] = source[i][j] * quantizationTable[i][j];
		}
	}
}