#include "fileHandler.h"
#include "transpose.h"
#include "substitute.h"
#include "hashLib.h"

#include <string>

std::string encipherAllThree(std::string input, std::string givenHashKey, std::string givenCipherAlphabet, std::string givenTransKey, char padChar);

std::string decipherAllThree(std::string input, std::string givenHashKey, std::string givenCipherAlphabet, std::string givenTransKey, char padChar);
