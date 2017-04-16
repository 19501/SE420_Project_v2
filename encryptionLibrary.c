// Magnus Bergman
// SE420 SQA

#ifndef ENCRYPTIONLIBRARY_C
#define ENCRYPTIONLIBRARY_C

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>

typedef struct {
	int Key;
	char Value;
} KeyValuePair;

int compare(const void* first, const void* second) {
	return ((KeyValuePair*)first)->Value - ((KeyValuePair*)second)->Value;
}

char** Create2DArray(int rowCount, int colCount) {
	char** rArray = (char**)malloc(sizeof(char*) * rowCount);

    int i;
	for (i = 0; i < rowCount; i++) {
		rArray[i] = (char*)malloc(sizeof(char) * colCount);
	}

	return rArray;
}

char* PadRight(char* str, int max, char padChar) {
	int strLen = strlen(str);
	char* output = (char*)malloc(sizeof(char*) * max);

	if (strLen < max) {
		//int padLen = max - strLen;
		int i;
		for (i = 0; i < max; ++i)
			output[i] = i < strLen ? str[i] : padChar;
	}

	//output[max] = '\0';
	return output;
}

int* GetShiftIndexes(char* key)
{
	int keyLength = strlen(key);
	int* indexes = (int*)malloc(sizeof(int) * keyLength);
	KeyValuePair* sortedKey = (KeyValuePair*)malloc(sizeof(KeyValuePair) * keyLength);
	int i;

	for (i = 0; i < keyLength; ++i)
    {
        //sortedKey[i] = {i, key[i]};
        sortedKey[i].Key = i;
        sortedKey[i].Value = key[i];
    }

	qsort(sortedKey, keyLength, sizeof(KeyValuePair), compare);
	for (i = 0; i < keyLength; ++i)
		indexes[sortedKey[i].Key] = i;

	return indexes;
}

char* EncipherTrans(char* input, char* key, char padChar)
{
    //  BELOW HERE IS 'LEGACY' CODE, UNMODIFIED
	int totalChars = strlen(input);
	int keyLength = strlen(key);
	input = (totalChars % keyLength == 0) ? input : PadRight(input, totalChars - (totalChars % keyLength) + keyLength, padChar);
	totalChars = strlen(input);
	char* output = (char*)malloc(sizeof(char) * totalChars);
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
		output[i] = sortedColChars[currentRow][currentColumn];
	}

	//output[totalChars] = '\0';
	return output;
}

char* DecipherTrans(char* input, char* key)
{
	int keyLength = strlen(key);
	int totalChars = strlen(input);
	char* output = (char*)malloc(sizeof(char*) * totalChars);
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
		output[i] = unsortedColChars[currentRow][currentColumn];
	}

	//output[totalChars] = '\0';
	return output;
}

bool CipherSub(char* input, char* oldAlphabet, char* newAlphabet, char* output)
{
	int inputLen = strlen(input);

	if (strlen(oldAlphabet) != strlen(newAlphabet))
		return false;

    int i;
	for (i = 0; i < inputLen; ++i)
	{
		const char* ptr = strchr(oldAlphabet, tolower(input[i]));
		int oldCharIndex = ptr - oldAlphabet;

		if (ptr && oldCharIndex >= 0)
			output[i] = isupper(input[i]) ? toupper(newAlphabet[oldCharIndex]) : newAlphabet[oldCharIndex];
		else
			output[i] = input[i];
	}

	//output[inputLen] = '\0';
	return true;
}

bool EncipherSub(char* input, char* cipherAlphabet, char* output)
{
	char* plainAlphabet = "abcdefghijklmnopqrstuvwxyz";
	return CipherSub(input, plainAlphabet, cipherAlphabet, output);
}

bool DecipherSub(char* input, char* cipherAlphabet, char* output)
{
	char* plainAlphabet = "abcdefghijklmnopqrstuvwxyz";
	return CipherSub(input, cipherAlphabet, plainAlphabet, output);
}

// Hash generation from string
// Copied from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = (*str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// A very simple "take the ASCII code of the input character and add the hashkey value
void hashEncrypt(char* input, unsigned long hashKey, char* output)
{
    int iterator;
    int stringLength = strlen(input);
    for(iterator = 0; iterator < stringLength; iterator++)
    {
        output[iterator] = input[iterator] + hashKey;
    }
}

// A very simple "take the ASCII code of the input character and subtract the hashkey value
void hashDecrypt(char* input, unsigned long hashKey, char* output)
{
    int iterator;
    int stringLength = strlen(input);
    for(iterator = 0; iterator < stringLength; iterator++)
    {
        output[iterator] = input[iterator] - hashKey;
    }
}

char* encipherAllThree(std::string input, std::string givenHashKey, std::string givenCipherAlphabet, std::string givenTransKey)
{
    givenTransKey.resize(input.size()); //  Extend the transposition key to avoid needing 'pad' characters.

    const char* inputCStringC = input.c_str();
    const char* hashKeyCStringC = givenHashKey.c_str();
    const char* givenCipherAlphabetCStringC = givenCipherAlphabet.c_str();
    const char* givenTransKeyCStringC = givenTransKey.c_str();

    char* inputCString = (char*) malloc(strlen(inputCStringC));
    char* hashKeyCString = (char*) malloc(strlen(hashKeyCStringC));
    char* givenCipherAlphabetCString = (char*) malloc(strlen(givenCipherAlphabetCStringC));
    char* givenTransKeyCString = (char*) malloc(strlen(givenTransKeyCStringC));

    strcpy(inputCString, inputCStringC);
    strcpy(hashKeyCString, hashKeyCStringC);
    strcpy(givenCipherAlphabetCString, givenCipherAlphabetCStringC);
    strcpy(givenTransKeyCString, givenTransKeyCStringC);

    char* subText = (char*)malloc(strlen(inputCString));

    // Set the hash for the hash-substitution cypher
    unsigned long testHash;
    testHash = hash(hashKeyCString);

    // substitution-cypher
    // input: inputText
    // output: subText
    EncipherSub(inputCString, givenCipherAlphabetCString, subText);

    // Transposition-cypher
    // input: subText
    // output: transText
    char* transText = EncipherTrans(subText, givenTransKeyCString, ' ');

    // Hash-Substitution cypher
    // input: transText
    // output: hashSubText

    char* hashSubText = (char*)malloc(strlen(transText));
    hashEncrypt(transText, testHash, hashSubText);

    return hashSubText;
}

char* decipherAllThree(std::string input, std::string givenHashKey, std::string givenCipherAlphabet, std::string givenTransKey)
{
    givenTransKey.resize(input.size()); //  Extend the transposition key to avoid needing 'pad' characters.

    const char* inputCStringC = input.c_str();
    const char* hashKeyCStringC = givenHashKey.c_str();
    const char* givenCipherAlphabetCStringC = givenCipherAlphabet.c_str();
    const char* givenTransKeyCStringC = givenTransKey.c_str();

    char* inputCString = (char*) malloc(strlen(inputCStringC));
    char* hashKeyCString = (char*) malloc(strlen(hashKeyCStringC));
    char* givenCipherAlphabetCString = (char*) malloc(strlen(givenCipherAlphabetCStringC));
    char* givenTransKeyCString = (char*) malloc(strlen(givenTransKeyCStringC));

    strcpy(inputCString, inputCStringC);
    strcpy(hashKeyCString, hashKeyCStringC);
    strcpy(givenCipherAlphabetCString, givenCipherAlphabetCStringC);
    strcpy(givenTransKeyCString, givenTransKeyCStringC);

    unsigned long testHash = hash(hashKeyCString);

    char* outputText = (char*) malloc(strlen(inputCString));

    // un-hash-Sub-cypher
    // input: hashSubText
    // output: unHashSubText
    char* unHashSubText = (char*)malloc(strlen(inputCString));
    hashDecrypt(inputCString, testHash, unHashSubText);

    // un-Transposition-cypher
    // input: unHashSubText
    // output: unTransText
    char* unTransText = DecipherTrans(unHashSubText, givenTransKeyCString);

    // Un-substitution-cypher
    // input: unTransText
    // output: outputText
    DecipherSub(unTransText, givenCipherAlphabetCString, outputText);

    return outputText;
}

int encipherFromFile(std::string inputFileName, std::string outputFileName, std::string hashKey, std::string cipherAlphabet, std::string transpositionKey)
{
    std::string fileInputLine;
    std::ifstream inputFile (inputFileName);
    std::ofstream outputFile (outputFileName);

    if ((inputFile.is_open()) && (outputFile.is_open()))
    {
        while (getline(inputFile, fileInputLine))
        {
            outputFile << encipherAllThree(fileInputLine, hashKey, cipherAlphabet, transpositionKey) << "\n";
        }
        inputFile.close();
        outputFile.close();
        return 1;
    }
    else
        return 0;
}

int decipherFromFile(std::string inputFileName, std::string outputFileName, std::string hashKey, std::string cipherAlphabet, std::string transpositionKey)
{
    std::string fileInputLine;
    std::ifstream inputFile (inputFileName);
    std::ofstream outputFile (outputFileName);

    if ((inputFile.is_open()) && (outputFile.is_open()))
    {
        while (getline(inputFile, fileInputLine))
        {
            outputFile << decipherAllThree(fileInputLine, hashKey, cipherAlphabet, transpositionKey) << "\n";
        }
        inputFile.close();
        outputFile.close();
        return 1;
    }
    else
        return 0;
}

#endif // ENCRYPTIONLIBRARY_C
