#include "DctManager.h"
#include <math.h>

DctManager::DctManager()
{
}

DctManager::~DctManager()
{
}

void DctManager::Dct(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int u = 0; u < BLOCK_SIZE; u++)
	{
		for (int v = 0; v < BLOCK_SIZE; v++)
		{
			float Cu;
			float Cv;
			float sum = 0.0;
			for (int m = 0; m < BLOCK_SIZE; m++)
			{
				for (int n = 0; n < BLOCK_SIZE; n++)
				{
					sum += cos((2 * m + 1)*u*PI / 2.0 / BLOCK_SIZE)*cos((2 * n + 1)*v*PI / 2.0 / BLOCK_SIZE)*source[m][n];
				}
			}
			(u == 0) ? (Cu = 1.0 / sqrt(2.0)) : (Cu = 1.0);
			(v == 0) ? (Cv = 1.0 / sqrt(2.0)) : (Cv = 1.0);
			target[u][v] = round(2.0 / BLOCK_SIZE * Cu*Cv*sum);
		}
	}
}

void DctManager::InverseDct(int source[BLOCK_SIZE][BLOCK_SIZE], int target[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int m = 0; m < BLOCK_SIZE; m++)
	{
		for (int n = 0; n < BLOCK_SIZE; n++)
		{
			float sum = 0.0;
			for (int u = 0; u < BLOCK_SIZE; u++)
			{
				for (int v = 0; v < BLOCK_SIZE; v++)
				{
					float Cu;
					float Cv;
					(u == 0) ? (Cu = 1.0 / sqrt(2.0)) : (Cu = 1.0);
					(v == 0) ? (Cv = 1.0 / sqrt(2.0)) : (Cv = 1.0);
					sum += cos((2 * m + 1)*u*PI / 2.0 / BLOCK_SIZE)*cos((2 * n + 1)*v*PI / 2 / BLOCK_SIZE)*Cu*Cv*source[u][v];
				}
			}
			target[m][n] = round(2.0 / BLOCK_SIZE*sum);
		}
	}
}