#include "substitute.h"

bool Cipher(string input, string oldAlphabet, string newAlphabet, string &output)
{
	output = "";
	int inputLen = input.size();

	if (oldAlphabet.size() != newAlphabet.size())
		return false;

	for (int i = 0; i < inputLen; ++i)
	{
		int oldCharIndex = oldAlphabet.find(tolower(input[i]));

		if (oldCharIndex >= 0)
			output += isupper(input[i]) ? toupper(newAlphabet[oldCharIndex]) : newAlphabet[oldCharIndex];
		else
			output += input[i];
	}

	return true;
}

bool EncipherSub(string input, string cipherAlphabet, string &output)
{
	string plainAlphabet = "abcdefghijklmnopqrstuvwxyz";
	return Cipher(input, plainAlphabet, cipherAlphabet, output);
}

bool DecipherSub(string input, string cipherAlphabet, string &output)
{
	string plainAlphabet = "abcdefghijklmnopqrstuvwxyz";
	return Cipher(input, cipherAlphabet, plainAlphabet, output);
}
