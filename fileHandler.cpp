#include "fileHandler.h"

int encipherFromFile(std::string inputFileName, std::string outputFileName, std::string hashKey, std::string cipherAlphabet, std::string transpositionKey, char padChar = '-')
{
    std::ifstream input;
    std::ofstream output;
    std::string inputLine, outputLine;

    input.open(inputFileName);
    output.open(outputFileName);

    if(input.is_open())
    {
        while(getline(input, inputLine))
        {
            outputLine = encipherAllThree(inputLine, hashKey, cipherAlphabet, transpositionKey, padChar);
            output << outputLine << endl;
        }
        input.close();
        output.close();
    }

    return 1;
}

int decipherFromFile(std::string inputFileName, std::string outputFileName, std::string hashKey, std::string cipherAlphabet, std::string transpositionKey, char padChar = '-')
{
    std::ifstream input (inputFileName);
    std::ofstream output (outputFileName);
    std::string inputLine, outputLine;

    if(input.is_open())
    {
        while(getline(input, inputLine))
        {
            outputLine = decipherAllThree(inputLine, hashKey, cipherAlphabet, transpositionKey, padChar);
            output << outputLine << endl;
        }
        input.close();
        output.close();
    }
    return 1;
}
