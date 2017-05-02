#include "encryptionLibrary.h"

#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <time.h>
#include <stdlib.h>

#define NUM_TESTS 100000

/////////////////////////////////////////////////////////////////////////////////
std::string generateRandomString(int stringLength)
{
    //  These are for generating random strings for testing.
    static const char acceptableChars[] =
    "`1234567890-="
    "~!@#$%^&*()_+"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "[]\\;',./"
    "{}|:\"<>?"
    "\t ";

    //  "-1" ???
    int numOptions = sizeof(acceptableChars) - 1;

    std::string output;
    for(int counter = 0; counter < (stringLength - 1); counter++)
        output += acceptableChars[rand() % numOptions];
    return output;
}

int test3(int testnum, std::string inputMessage, std::string hashKeyString, std::string encipherAlphabet, std::string transposeKeyString, char givenPadChar, bool disp = true)
{
    srand(time(0));
    if(disp)
        std::cout << "\n\nTEST #" << testnum << ":";

    std::string encryptedMessage = encipherAllThree(inputMessage, hashKeyString, encipherAlphabet, transposeKeyString, givenPadChar);
    std::string decryptedMessage = decipherAllThree(encryptedMessage, hashKeyString, encipherAlphabet, transposeKeyString, givenPadChar);

    if (testnum < 0)
    {
        std::cout << "\n\nCiphered:\t" << encryptedMessage;
        std::cout << "\nDecrypted:\t" << decryptedMessage;
        std::cout << "\nOriginal:\t" << inputMessage;
    }

    if (decryptedMessage.compare(inputMessage) == 0)
    {
        if (disp)
            std::cout << "\n\n\tSUCCESS\n\n";
        return 1;
    }
    else
    {
        if(disp)
        {
            std::cout << "\n\n\tFAILURE:\n\n";
            std::cout << "\n\nInput: " << inputMessage;
            std::cout << "\n\nEncrypted: " << encryptedMessage;
            std::cout << "\n\nOutput: " << decryptedMessage;
        }

        return 0;
    }
}

int main()
{
    std::cout << "Initializing Test Driver...\n\n";

    char commandChar;

    std::string testMessage = "`1234567890-=~!@#$%^&*()_+abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]\;',./{}|:<>?";
    std::string testHash = generateRandomString(10);

    //  Note that the alphabet key must not have any repeated characters
    std::string testAlphabet = "qwertyuiopasdfghjklzxcvbnm";
    std::string testTransKey = generateRandomString(10);
    char testPadChar = '-';

    std::cout << "\nTest message: " << testMessage;
    std::cout << "\nTest Hash: " << testHash;
    std::cout << "\nTest alphabet: " << testAlphabet;
    std::cout << "\nTest Transpose Key: " << testTransKey;

    //////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\n\nStarting with: Unit Tests:";

    std::string testOutput, testCiphered;

    /////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\n\nTesting Transposition Cipher:------------------------------------";
    std::cout << "\nTransposition key: " << testTransKey;

    testCiphered = EncipherTrans(testMessage, testTransKey, testPadChar);
    testOutput = DecipherTrans(testCiphered, testTransKey, testPadChar);

    std::cout << "\nTransposition Ciphered:\n" << testCiphered;
    std::cout << "\n\nTransposition Deciphered:\n" << testOutput;
    std::cout << "\nMessage:\n" << testMessage;

    if(testMessage.compare(testOutput) == 0)
        std::cout << "\n\n\tSUCCESS";

    std::cout << "\n\nContinue? (y/n) ";
    std::cin >> commandChar;
    if (commandChar == 'n')
        return 1;

    ////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\nTesting Substitution Cipher:--------------------------------------";
    std::cout << "\nSubstitution Alphabet: " << testAlphabet;

    EncipherSub(testMessage, testAlphabet, testCiphered);
    DecipherSub(testCiphered, testAlphabet, testOutput);

    std::cout << "\nSubstitution Ciphered:" << testCiphered;
    std::cout << "\n\nSubstitution Deciphered:\n" << testOutput;
    std::cout << "\nMessage:\n" << testMessage;

    if(testMessage.compare(testOutput) == 0)
        std::cout << "\n\n\tSUCCESS";

    std::cout << "\n\nContinue? (y/n) ";
    std::cin >> commandChar;
    if (commandChar == 'n')
        return 1;

    ////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\nTesting Hash Cipher:----------------------------------------------";
    std::cout << "\nHash (numerical value): " << hash<string>{}(testHash);

    testCiphered = hashEncrypt(testMessage, testHash);
    testOutput = hashDecrypt(testCiphered, testHash);

    std::cout << "\n\nHash Ciphered:" << testCiphered;
    std::cout << "\n\nHash Deciphered:\n" << testOutput;
    std::cout << "\nMessage:\n" << testMessage;

    if(testMessage.compare(testOutput) == 0)
        std::cout << "\n\n\tSUCCESS";

    std::cout << "\n\nContinue? (y/n) ";
    std::cin >> commandChar;
    if (commandChar == 'n')
        return 1;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\n\nStarting Integration Testing:";
    if (test3(-1, "This is an example of the test." , testHash, testAlphabet, testTransKey, testPadChar) == 0)
    {
        std::cout << "\n\nContinue? (y/n) ";
        std::cin >> commandChar;

        if (commandChar == 'n')
            return 1;
    }

    std::cout << "\n\nBeginning Automated Tests: (This may take a while...) ";
    int testsCompleted = 0;
    int passed = 0, failed = 0;
    std::string randomMessage;
    while (testsCompleted < NUM_TESTS)
    {
        randomMessage = generateRandomString(1000);

        //  Remove the 'pad character' from the end of the string, if present
        while (randomMessage.back() == testPadChar)
            randomMessage.pop_back();

        if (test3(testsCompleted, randomMessage, testHash, testAlphabet, testTransKey, testPadChar, false) == 1)
            passed++;
        else
            failed++;

        testsCompleted++;
    }
    std::cout << "\n\nAutomated Tests Passed: " << passed;
    std::cout << "\nAutomated Tests Failed: " << failed;

    std::cout << "\n\nContinue on to file I/O testing? (y/n): ";
    std::cin >> commandChar;
    if (commandChar == 'n')
        return 1;

    //  BEGIN FILE INPUT TESTING
    std::cout << "\n\nBEGINNING FILE INPUT TESTING:------------------------------------------------";

    std::string inputFileName =         "testInput.txt";
    std::string cipheredFileName =      "testCiphered.txt";
    std::string decipheredFileName =    "testDecoded.txt";

    encipherFromFile(inputFileName, cipheredFileName, testHash, testAlphabet, testTransKey, testPadChar);

    decipherFromFile(cipheredFileName, decipheredFileName, testHash, testAlphabet, testTransKey, testPadChar);

    std::cout << "\nFile ciphering & deciphering tested. Please manually inspect the relevant files.";
}
