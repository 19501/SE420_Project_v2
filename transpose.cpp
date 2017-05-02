#include "transpose.h"

using namespace std;

bool compare(const KeyValuePair &first, const KeyValuePair &second) {
	return first.Value < second.Value;
}

char** Create2DArray(int rowCount, int colCount) {
	char** arr = new char*[rowCount];

	for (int i = 0; i < rowCount; ++i)
		arr[i] = new char[colCount];

	return arr;
}

string PadRight(string str, int max, char padChar) {
	int strLen = str.length();

	if (strLen < max) {
		int padLen = max - strLen;
		for (int i = 0; i < padLen; ++i) str += padChar;
	}

	return str;
}

int* GetShiftIndexes(string key)
{
	int keyLength = key.length();
	int* indexes = new int[keyLength];
	list<KeyValuePair> sortedKey;
	int i;

	for (i = 0; i < keyLength; ++i)
		sortedKey.push_back({ i, key[i] });

	sortedKey.sort(compare);
	i = 0;

    /*
    //  This came with the legacy code, but doesn't compile. I attempted to replicate it below.
	for each (KeyValuePair pairName in sortedKey) {
		indexes[pairName.Key] = i;
		++i;
	}
	*/

	for (KeyValuePair pairName : sortedKey)
    {
        indexes[pairName.Key] = i;
        i++;
    }

	return indexes;
}

string EncipherTrans(string input, string key, char padChar = '-')
{
	string output = "";
	int totalChars = input.length();
	int keyLength = key.length();

	//  Extend the input string to match the required length, adding 'padChar' as needed to the end of input
	input = (totalChars % keyLength == 0) ? input : PadRight(input, totalChars - (totalChars % keyLength) + keyLength, padChar);
	totalChars = input.length();
	int totalColumns = keyLength;
	int totalRows = (int)ceil((double)totalChars / totalColumns);
	char** rowChars = Create2DArray(totalRows, totalColumns);
	char** colChars = Create2DArray(totalColumns, totalRows);
	char** sortedColChars = Create2DArray(totalColumns, totalRows);
	int currentRow, currentColumn, i, j;
	int* shiftIndexes = GetShiftIndexes(key);

	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalColumns;
		currentColumn = i % totalColumns;
		rowChars[currentRow][currentColumn] = input[i];
	}

	for (i = 0; i < totalRows; ++i)
		for (j = 0; j < totalColumns; ++j)
			colChars[j][i] = rowChars[i][j];

	for (i = 0; i < totalColumns; ++i)
		for (j = 0; j < totalRows; ++j)
			sortedColChars[shiftIndexes[i]][j] = colChars[i][j];

	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalRows;
		currentColumn = i % totalRows;
		output += sortedColChars[currentRow][currentColumn];
	}

	return output;
}

string DecipherTrans(string input, string key, char padChar = '-')
{
	string output = "";
	int keyLength = key.length();
	int totalChars = input.length();
	int totalColumns = (int)ceil((double)totalChars / keyLength);
	int totalRows = keyLength;
	char** rowChars = Create2DArray(totalRows, totalColumns);
	char** colChars = Create2DArray(totalColumns, totalRows);
	char** unsortedColChars = Create2DArray(totalColumns, totalRows);
	int currentRow, currentColumn, i, j;
	int* shiftIndexes = GetShiftIndexes(key);

	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalColumns;
		currentColumn = i % totalColumns;
		rowChars[currentRow][currentColumn] = input[i];
	}

	for (i = 0; i < totalRows; ++i)
		for (j = 0; j < totalColumns; ++j)
			colChars[j][i] = rowChars[i][j];

	for (i = 0; i < totalColumns; ++i)
		for (j = 0; j < totalRows; ++j)
			unsortedColChars[i][j] = colChars[i][shiftIndexes[j]];

	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalRows;
		currentColumn = i % totalRows;
		output += unsortedColChars[currentRow][currentColumn];
	}

    //  Remove the extra pad characters that had been added as part of the initial encryption
	while (output.back() == padChar)
        output.pop_back();

	return output;
}
