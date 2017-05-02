#include <string>
#include <iostream>
#include <fstream>
#include "encryptionLibrary.h"

int encipherFromFile(std::string inputFileName, std::string outputFileName, std::string hashKey, std::string cipherAlphabet, std::string transpositionKey, char);

int decipherFromFile(std::string inputFileName, std::string outputFileName, std::string hashKey, std::string cipherAlphabet, std::string transpositionKey, char);

void encryptImage(std::string inputImageName, std::string outputImageName, std::string hashKey, std::string cipherAlphabet, std::string transposeKey, char padChar);

void decryptImage(std::string inputImageName, std::string outputImageName, std::string hashKey, std::string cipherAlphabet, std::string transposeKey, char padChar);
