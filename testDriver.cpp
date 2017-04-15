#include "encryptionLibrary.c"
#include <string>
#include <iostream>

int test3(int testnum, std::string testString, std::string hashKey, std::string alphabet, std::string transposeKey)
{
    std::cout << ""
}

int main()
{
    //  TEST CASE #1: SIMPLEST SINGLE STRING INPUT
    std::cout << "TEST CASE #1: SIMPLE EXAMPLE STRING\n\n";
    std::string hashKeyString = "Encrypt";
    std::string encipherAlphabet = "qwertyuiopasdfghjklzxcvbnm";
    std::string transposeKeyString = "Transpose";

    std::string inputMessage = "This is the first, simplest test case.";

    std::string encryptedMessage = encipherAllThree(inputMessage, hashKeyString, encipherAlphabet, transposeKeyString);
    std::string decryptedMessage = decipherAllThree(encryptedMessage, hashKeyString, encipherAlphabet, transposeKeyString);

    std::cout << "Ciphered: " << encryptedMessage << "\n\n";
    std::cout << "Decrypted: " << decryptedMessage << "\n";
    std::cout << "Original:  " << inputMessage << "\n\n";

    if (decryptedMessage.compare(inputMessage))
    {
        std::cout << "TEST #1:\tSUCCESS\n\n";
    }
    else
    {
        std::cout << "TEST #1:\tFAILURE\n\n";
    }
}
