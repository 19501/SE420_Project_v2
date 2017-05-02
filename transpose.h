//  Note: This module was written by modifying code found from:
//  https://www.programmingalgorithms.com/algorithm/transposition-cipher?lang=C%2B%2B

#include <iostream>
#include <list>
#include <cmath>

using namespace std;

typedef struct {
	int Key;
	char Value;
} KeyValuePair;

bool compare(const KeyValuePair &first, const KeyValuePair &second);

char** Create2DArray(int rowCount, int colCount);

string PadRight(string str, int max, char padChar);

int* GetShiftIndexes(string key);

string EncipherTrans(string input, string key, char padChar);

string DecipherTrans(string input, string key, char padChar);

