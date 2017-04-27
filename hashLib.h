#include <string>
#include <functional>
#include <limits.h>

using namespace std;

// Hash generation from string
// Modified from http://www.cse.yorku.ca/~oz/hash.html
//unsigned long hash(string input);

// A very simple "take the ASCII code of the input character and add the hashkey value
string hashEncrypt(string input, string hashStr);

// A very simple "take the ASCII code of the input character and subtract the hashkey value
string hashDecrypt(string input, string hashStr);
