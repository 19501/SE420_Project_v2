#include "hashLib.h"

/*
unsigned long hash(string str)
{
    unsigned long hash = 5381;
    int c;

    while (c = (str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}
*/

// A very simple "take the ASCII code of the input character and add the hashkey value
string hashEncrypt(string input, string hashStr)
{
    string output = input;
    int hashVal = (hash<string>{}(hashStr)) % INT_MAX;
    int counter;
    int stringLength = input.size();
    for(counter = 0; counter < stringLength; counter++)
    {
        output[counter] = input[counter] + hashVal;
    }
    return output;
}

// A very simple "take the ASCII code of the input character and subtract the hashkey value
string hashDecrypt(string input, string hashStr)
{
    string output = input;
    int hashVal = (hash<string>{}(hashStr)) % INT_MAX;
    int iterator;
    int stringLength = input.size();
    for(iterator = 0; iterator < stringLength; iterator++)
    {
        output[iterator] = input[iterator] - hashVal;
    }
    return output;
}
