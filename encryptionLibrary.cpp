#include "encryptionLibrary.h"

std::string encipherAllThree(std::string input, std::string givenHashKey, std::string givenCipherAlphabet, std::string givenTransKey, char padChar)
{
    std::string transposedString = EncipherTrans(input, givenTransKey, padChar);

    std::string subTransString = "";
    EncipherSub(transposedString, givenCipherAlphabet, subTransString);

    std::string output = hashEncrypt(subTransString, givenHashKey);

    return output;
}

std::string decipherAllThree(std::string input, std::string givenHashKey, std::string givenCipherAlphabet, std::string givenTransKey, char padChar)
{
    std::string subTransString = hashDecrypt(input, givenHashKey);

    std::string transString = "";
    DecipherSub(subTransString, givenCipherAlphabet, transString);

    std::string clearString = DecipherTrans(transString, givenTransKey, padChar);

    return clearString;
}
