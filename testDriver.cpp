#include "encryptionLibrary.c"
#include <string>
#include <iostream>
#include <ctime>

#define NUM_TESTS 1000

/////////////////////////////////////////////////////////////////////////////////
//  These are for generating random strings for testing.
static const char acceptableChars[] =
"`1234567890-="
"~!@#$%^&*()_+"
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"[];',./"
"{}|:<>?"
"\t ";

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

    //std::cout << "\n\nCiphered: " << encryptedMessage;
    //std::cout << "\nDecrypted: " << decryptedMessage;
    //std::cout << "\nOriginal:  " << inputMessage;

    if (decryptedMessage.compare(inputMessage) == 0)
    {
        std::cout << "\n\n\tSUCCESS\n\n";
        return 1;
    }
    else
    {
        std::cout << "\n\n\tFAILURE:\n\n";
        std::cout << "\nInput: " << inputMessage;
        std::cout << "\nOutput: " << decryptedMessage;
        return 0;
    }
}

int main()
{
    std::cout << "Initializing Test Driver...\n\n";

    /*
    std::cout << "\n\nSimple test covering all required inputs:";
    std::string firstTestString = "`1234567890-=~!@#$%^&*()_+[]{}|;':,./<>?";
    std::cout << "\nFirst test string: " << firstTestString;
    std::cout << "\nPassed = ";
    if (test3(0, firstTestString, "hashTest", "alphabet", "tranposeThisToALongerKey") == 1)
        std::cout << "PASS";
    else
        std::cout << "FAIL";

    */

    std::cout << "\n\nBeginning Automated Tests:";
    int testsCompleted = 0;
    int passed = 0, failed = 0;
    while (testsCompleted < NUM_TESTS)
    {
        std::string randomMessage = generateRandomString(1000);
        std::string randomHashString = generateRandomString(10);
        std::string randomAlphabet = "abcdefghijklmnopqrstuvwxyz";  //generateRandomString(1000);
        std::string randomTransKey = generateRandomString(1000);

        if (test3(testsCompleted, randomMessage, randomHashString, randomAlphabet, randomTransKey) == 1)
            passed++;
        else
            failed++;

        testsCompleted++;
    }
    std::cout << "\n\nAutomated Tests Passed: " << passed;
    std::cout << "\nAutomated Tests Failed: " << failed;
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
