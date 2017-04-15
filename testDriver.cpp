#include "encryptionLibrary.c"
#include <string>
#include <iostream>

#define NUM_TESTS 1000000

/////////////////////////////////////////////////////////////////////////////////
//  These are for generating random strings for testing.
static const char acceptableChars[] =
"`1234567890-="
"~!@#$%^&*()_+"
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"[]\;',./"
"{}|:\"<>?"
"\t ";

int numOptions = sizeof(acceptableChars) - 1;

std::string generateRandomString(int stringLength)
{
    std::string output;
    for(int counter = 0; counter < (stringLength - 1); counter++)
        output += acceptableChars[rand() % numOptions];
    return output;
}

int test3(int testnum, std::string inputMessage, std::string hashKeyString, std::string encipherAlphabet, std::string transposeKeyString)
{
    std::cout << "\n\nTEST #" << testnum << ":";

    std::string encryptedMessage = encipherAllThree(inputMessage, hashKeyString, encipherAlphabet, transposeKeyString);
    std::string decryptedMessage = decipherAllThree(encryptedMessage, hashKeyString, encipherAlphabet, transposeKeyString);

    //std::cout << "\n\nCiphered: " << encryptedMessage;
    //std::cout << "\nDecrypted: " << decryptedMessage;
    //std::cout << "\nOriginal:  " << inputMessage;

    if (decryptedMessage.compare(inputMessage))
    {
        std::cout << "\n\n\tSUCCESS\n\n";
        return 1;
    }
    else
    {
        std::cout << "\n\n\tFAILURE\n\n";
        return 0;
    }
}

int main()
{
    std::cout << "Initializing Test Driver...\n\n";
    int testsCompleted = 0;
    int passed = 0, failed = 0;
    while (testsCompleted < NUM_TESTS)
    {
        std::string randomMessage = generateRandomString(1000);
        std::string randomHashString = generateRandomString(1000);
        std::string randomAlphabet = generateRandomString(1000);
        std::string randomTransKey = generateRandomString(1000);

        if (test3(testsCompleted, randomMessage, randomHashString, randomAlphabet, randomTransKey) == 1)
            passed++;
        else
            failed++;

        testsCompleted++;
    }
    std::cout << "\n\nTests Passed: " << passed;
    std::cout << "\nTests Failed: " << failed;
    /*
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
    */
}
