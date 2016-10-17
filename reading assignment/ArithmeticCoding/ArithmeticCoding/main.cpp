#include <stdlib.h>
#include <iostream>
#include "ArithmeticCodingFactory.h"

int main()
{
	ArithmeticCodingFactory factory;
	string encodeString = "WER";

	string encodedResult = factory.Encode(encodeString);
	cout << "Encode: " << encodeString << " ==> " << encodedResult << endl << "total bits= " << encodedResult.size() << endl << endl;

	string decodedResult = factory.Decode(encodedResult);
	cout << "Decode: " << encodedResult << " ==> " << decodedResult << endl;
	system("pause");
	return 0;
}