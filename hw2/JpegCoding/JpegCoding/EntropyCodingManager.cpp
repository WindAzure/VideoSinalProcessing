#include "EntropyCodingManager.h"
#include "ConstParameter.h"
#include <iostream>

EntropyCodingManager::EntropyCodingManager()
{
	_huffmanTable["0/0"] = "1010";
	_huffmanTable["0/1"] = "00";
	_huffmanTable["0/2"] = "01";
	_huffmanTable["0/3"] = "100";
	_huffmanTable["0/4"] = "1011";
	_huffmanTable["0/5"] = "11010";
	_huffmanTable["0/6"] = "1111000";
	_huffmanTable["1/1"] = "1100";
	_huffmanTable["1/2"] = "11011";
	_huffmanTable["1/3"] = "1111001";
	_huffmanTable["1/4"] = "111110110";
	_huffmanTable["1/5"] = "11111110110";
	_huffmanTable["1/6"] = "1111111110000100";
	_huffmanTable["5/1"] = "1111010";
	_huffmanTable["6/2"] = "111111110110";
	_huffmanTable["10/1"] = "111111010";

	_dcTable["0"] = "00";
	_dcTable["1"] = "010";
	_dcTable["2"] = "011";
	_dcTable["3"] = "100";
	_dcTable["4"] = "101";
	_dcTable["5"] = "110";
	_dcTable["6"] = "1110";
	_dcTable["7"] = "11110";
	_dcTable["8"] = "111110";
	_dcTable["9"] = "1111110";
	_dcTable["10"] = "11111110";
	_dcTable["11"] = "111111110";
}

EntropyCodingManager::~EntropyCodingManager()
{
}

string EntropyCodingManager::AmplitudeCompression(int number)
{
	bool isNeg = false;
	if (number < 0)
	{
		isNeg = true;
		number *= -1;
	}

	string result = "";
	while (number > 0)
	{
		int digit = number % 2;
		if (isNeg)
		{
			digit = 1 - digit;
		}
		result = to_string(digit) + result;
		number /= 2;
	}
	return result;
}

int EntropyCodingManager::AmplitudeDeCompression(string numberString)
{
	int isNeg = false;
	if (numberString[0] == '0')
	{
		for (int i = numberString.size() - 1; i >= 0; i--)
		{
			numberString[i] = ('1' - numberString[i]) + '0';
		}
		isNeg = true;
	}

	int sum = 0;
	int base = 1;
	for (int i = numberString.size() - 1; i >= 0; i--, base *= 2)
	{
		sum += (numberString[i] - '0')*base;
	}

	if (isNeg)
	{
		return sum*-1;
	}
	return sum;
}

string EntropyCodingManager::LookupTable(string currentString, map<string, string>& table)
{
	for (map<string, string>::iterator it = table.begin(); it != table.end(); it++)
	{
		if (it->second == currentString)
		{
			return it->first;
		}
	}
	return "";
}

vector<string> EntropyCodingManager::Encode(vector<int> zigZagList, int previousDC)
{
	vector<string> encodedList;
	string dcAmpString = AmplitudeCompression(zigZagList[0] - previousDC);
	encodedList.push_back(_dcTable[to_string(dcAmpString.size())] + dcAmpString);

	for (int i = 1; i < zigZagList.size(); i++)
	{
		if (zigZagList[i] == numeric_limits<int>::max())
		{
			encodedList.push_back(_huffmanTable["0/0"]);
		}
		else if (zigZagList[i] != 0)
		{
			int zeroQuantity = 0;
			int st = i - 1;
			while (st >= 0 && zigZagList[st] == 0)
			{
				zeroQuantity++;
				st--;
			}
			int lastBlockAC = 0;
			string acAmpString = AmplitudeCompression(zigZagList[i] - lastBlockAC);
			string runSizeString = to_string(zeroQuantity) + "/" + to_string(acAmpString.size());
			if (_huffmanTable.find(runSizeString) == _huffmanTable.end())
			{
				printf("%s huffmanTable not found!!\n", runSizeString.c_str());
			}
			else
			{
				encodedList.push_back(_huffmanTable[runSizeString] + acAmpString);
			}
		}
	}
	return encodedList;
}

string ReadNumber(string &encodeString, string &currentString, int &currentPos, string digit)
{
	string number = "";
	if (digit != "")
	{
		int len = atoi(digit.c_str());
		number = encodeString.substr(currentPos + 1, len);
		currentPos += len;
		currentString = "";
	}
	return number;
}

vector<int> EntropyCodingManager::Decode(string encodeString, int previousDC)
{
	bool isDcDone = false;
	vector <int> zigZagList;
	string currentString = "";
	for (int i = 0; i < encodeString.size(); i++)
	{
		currentString = currentString + encodeString[i];
		if (!isDcDone)
		{
			string digit = LookupTable(currentString, _dcTable);
			if (digit != "")
			{
				string number = ReadNumber(encodeString, currentString, i, digit);
				zigZagList.push_back(AmplitudeDeCompression(number) + previousDC);
				isDcDone = true;
			}
		}
		else
		{
			string huffmanResult = LookupTable(currentString, _huffmanTable);
			if (huffmanResult != "")
			{
				int pos = huffmanResult.find("/");
				string digit = huffmanResult.substr(pos + 1, huffmanResult.size() - pos);
				string number = ReadNumber(encodeString, currentString, i, digit);
				string runLength = huffmanResult.substr(0, pos);

				if (digit != "0")
				{
					for (int i = 0; i < atoi(runLength.c_str()); i++)
					{
						zigZagList.push_back(0);
					}
					zigZagList.push_back(AmplitudeDeCompression(number));
				}
				else
				{
					zigZagList.push_back(numeric_limits<int>::max());
				}
			}
		}
	}
	return zigZagList;

}