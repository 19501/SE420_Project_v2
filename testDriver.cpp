#include "encryptionLibrary.c"
#include "cppHelpers.h"

#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

#define NUM_TESTS 1000

/////////////////////////////////////////////////////////////////////////////////
//  These are for generating random strings for testing.
static const char acceptableChars[] =
"`1234567890-="
"~!@#$%^&*()_+"
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"[]\\;',./"
"{}|:\"<>?"
"    ";

int numOptions = sizeof(acceptableChars) - 1;

std::string generateRandomString(int stringLength)
{
    srand(time(0));
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

    if (testnum < 0)
    {
        std::cout << "\n\nCiphered: " << encryptedMessage;
        std::cout << "\nDecrypted: " << decryptedMessage;
        std::cout << "\nOriginal:  " << inputMessage;
    }

    if (decryptedMessage.compare(inputMessage) == 0)
    {
        std::cout << "\n\n\tSUCCESS\n\n";
        return 1;
    }
    else
    {
        std::cout << "\n\n\tFAILURE:\n\n";
        std::cout << "\n\nInput: " << inputMessage;
        std::cout << "\n\nEncrypted: " << encryptedMessage;
        std::cout << "\n\nOutput: " << decryptedMessage;
        return 0;
    }
}

int main()
{
    std::cout << "Initializing Test Driver...\n\n";

    char commandChar;

    std::string testMessage = "`1234567890-=~!@#$%^&*()_+abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[];',./{}|:<>?";
    std::string testHash = generateRandomString(10);
    std::string testAlphabet = "qwertyuiopasdfghjklzxcvbnm";
    std::string testTransKey = generateRandomString(10);

    std::cout << "\nTest message: " << testMessage;
    std::cout << "\nTest Hash: " << testHash;
    std::cout << "\nTest alphabet: " << testAlphabet;
    std::cout << "\nTest Transpose Key: " << testTransKey;
    if (test3(-1, testMessage, testHash, testAlphabet, testTransKey) == 0)
    {
        std::cout << "\n\nContinue? (y/n) ";
        std::cin >> commandChar;

        if (commandChar == 'n')
            return 1;
    }

    std::cout << "\n\nBeginning Automated Tests:";
    int testsCompleted = 0;
    int passed = 0, failed = 0;
    while (testsCompleted < NUM_TESTS)
    {
        std::string randomMessage = generateRandomString(1000);
        //std::string randomHashString = generateRandomString(10);
        //std::string randomAlphabet = "abcdefghijklmnopqrstuvwxyz";
        //std::string randomTransKey = generateRandomString(100);

        if (test3(testsCompleted, randomMessage, testHash, testAlphabet, testTransKey) == 1)
            passed++;
        else
            failed++;

        testsCompleted++;
    }
    std::cout << "\n\nAutomated Tests Passed: " << passed;
    std::cout << "\nAutomated Tests Failed: " << failed;

    //  BEGIN FILE INPUT TESTING
    std::cout << "\n\nBEGINNING FILE INPUT TESTING:------------------------------------------------";

    encipherFromFile("testInput.txt", "testCiphered.txt", testHash, testAlphabet, testTransKey);

    decipherFromFile("testCiphered.txt", "testDecoded.txt", testHash, testAlphabet, testTransKey);
}
