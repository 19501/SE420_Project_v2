//  Note: This module was written by modifying code from:
//  https://www.programmingalgorithms.com/algorithm/simple-substitution-cipher?lang=C%2B%2B

#include <string>

using namespace std;

bool CipherSub(string input, string oldAlphabet, string newAlphabet, string &output);

bool EncipherSub(string input, string cipherAlphabet, string &output);

bool DecipherSub(string input, string cipherAlphabet, string &output);
