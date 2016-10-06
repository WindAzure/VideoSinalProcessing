#include <stdio.h>
#include <stdlib.h>

#include "DctManager.h"
#include "Quantizer.h"
#include "DifferenceCalculator.h"
#include "ZigZagManager.h"

int main()
{
	int X[8][8] =
	{
		{ 79, 75, 79, 82, 82, 86, 94, 94 },
		{ 76, 78, 76, 82, 83, 86, 85, 94 },
		{ 72, 75, 67, 78, 80, 78, 74, 82 },
		{ 74, 76, 75, 75, 86, 80, 81, 79 },
		{ 73, 70, 75, 67, 78, 78, 79, 85 },
		{ 69, 63, 68, 69, 75, 78, 82, 80 },
		{ 76, 76, 71, 71, 67, 79, 80, 83 },
		{ 72, 77, 78, 69, 75, 75, 78, 78 }
	};

	/*int X[8][8] =
	{
	{ 80, 80, 80, 80, 80, 80, 80, 80 },
	{ 80, 80, 80, 80, 80, 80, 80, 80 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 120, 120, 120, 120, 120, 120, 120, 120, },
	{ 120, 120, 120, 120, 120, 120, 120, 120, }
	};*/

	int Y[8][8];
	DctManager dctManager;
	dctManager.Dct(X, Y);

	int Z[8][8];
	Quantizer quantizer;
	quantizer.Quantize(Y, Z);

	ZigZagManager zigZagManager;
	vector<int> zigZagList;
	zigZagManager.GetZigZagList(Z, zigZagList);



	for (int i = 0; i < zigZagList.size(); i++)
	{
		printf("%d ", zigZagList[i]); 
	}

	printf("\n");
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%4d ", Z[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/

		//DifferenceCalculator calculator;
		//printf("MSE=%f PSNR=%f\n", calculator.CalculateMSE(Y, InverseZ), calculator.CalculatePSNR(Y, InverseZ));

		system("pause");
	return 0;
}