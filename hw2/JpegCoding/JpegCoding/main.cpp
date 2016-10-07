#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "DctManager.h"
#include "Quantizer.h"
#include "DifferenceCalculator.h"
#include "ZigZagManager.h"
#include "EntropyCodingManager.h"

string Encode(int X[BLOCK_SIZE][BLOCK_SIZE])
{
	int Y[BLOCK_SIZE][BLOCK_SIZE];
	DctManager dctManager;
	dctManager.Dct(X, Y);

	int Z[BLOCK_SIZE][BLOCK_SIZE];
	Quantizer quantizer;
	quantizer.Quantize(Y, Z);

	/*int InverseZ[8][8];
	quantizer.InverseQuantize(Z, InverseZ);
	DifferenceCalculator calculator;
	printf("MSE=%f PSNR=%f\n", calculator.CalculateMSE(Y, InverseZ), calculator.CalculatePSNR(Y, InverseZ));*/

	ZigZagManager zigZagManager;
	vector<int> zigZagList;
	zigZagManager.GetZigZagList(Z, zigZagList);
	printf("Encode Part:\nZig-Zag Result = ");
	for (int i = 0; i < zigZagList.size(); i++)
	{
		printf("%d ", zigZagList[i]);
	}
	printf("\n\n");

	EntropyCodingManager entropyCodingManager;
	vector<string> encodedList = entropyCodingManager.Encode(zigZagList, 52);

	int totalBits = 0;
	string encodeRsult;
	for (int i = 0; i < encodedList.size(); i++)
	{
		totalBits += encodedList[i].size();
	}
	printf("bit rate = %f bpp\n", (float)totalBits / BLOCK_SIZE / BLOCK_SIZE);
	printf("compression ratio = %f\n", (float)BLOCK_SIZE*BLOCK_SIZE * 8 / totalBits);
	for (int i = 0, j = 0; i < encodedList.size(); i++, j++)
	{
		while (zigZagList[j] == 0)
		{
			j++;
		}
		printf("%10d  ===> ", zigZagList[j]);
		cout << encodedList[i] << endl;
		encodeRsult += encodedList[i];
	}
	printf("\n");
	return encodeRsult;
}

void Decode(string encodeString, int decodeMatrix[BLOCK_SIZE][BLOCK_SIZE])
{
	EntropyCodingManager entropyCodingManager;
	vector<int> zigZagList = entropyCodingManager.Decode(encodeString, 52);

	printf("Decode Part:\nZig-Zag Result = ");
	for (int i = 0; i < zigZagList.size(); i++)
	{
		printf("%d ", zigZagList[i]);
	}
	printf("\n\n");
	int Z[BLOCK_SIZE][BLOCK_SIZE];
	ZigZagManager zigZagManager;
	zigZagManager.Inverse(zigZagList, Z);

	int Y[BLOCK_SIZE][BLOCK_SIZE];
	Quantizer quantizer;
	quantizer.InverseQuantize(Z, Y);

	DctManager dctManager;
	dctManager.InverseDct(Y, decodeMatrix);
}

int main()
{
	int X[BLOCK_SIZE][BLOCK_SIZE] =
	{
	{ 80, 80, 80, 80, 80, 80, 80, 80 },
	{ 80, 80, 80, 80, 80, 80, 80, 80 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 100, 100, 100, 100, 100, 100, 100, 100 },
	{ 120, 120, 120, 120, 120, 120, 120, 120, },
	{ 120, 120, 120, 120, 120, 120, 120, 120, }
	};

	string encodedString = Encode(X);
	int decodeMatrix[BLOCK_SIZE][BLOCK_SIZE];
	Decode(encodedString, decodeMatrix);

	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			printf("%d ", decodeMatrix[i][j]);
		}
		printf("\n");
	}

	DifferenceCalculator calculator;
	printf("MSE=%f PSNR=%f\n", calculator.CalculateMSE(X, decodeMatrix), calculator.CalculatePSNR(X, decodeMatrix)); 

	system("pause");
	return 0;
}