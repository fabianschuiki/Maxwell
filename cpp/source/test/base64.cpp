/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This program tests the base64 encoding/decoding through
 * common/base64.hpp.
 */

#include <iostream>
#include <string>
#include <common/base64.hpp>

using std::cout;
using std::string;

int main()
{
	// Test cases.
	struct { const char* raw; const char* b64; } tests[] = {
		{"Hello World", "SGVsbG8gV29ybGQ="},
		{"Maxwell Programming Language", "TWF4d2VsbCBQcm9ncmFtbWluZyBMYW5ndWFnZQ=="},
		{"C++ is... a lot of boilerplate.", "QysrIGlzLi4uIGEgbG90IG9mIGJvaWxlcnBsYXRlLg=="},
		{NULL, NULL}
	};

	// Run the test.
	int fails = 0;
	for (int i = 0; i < 100000; i++) {
		if (!tests[i].raw || !tests[i].b64)
			break;
		string raw(tests[i].raw);
		string b64(tests[i].b64);
		cout << "Testing \033[36m" << raw << "\033[0m <-> " << b64 << "... ";
		string encoded = base64::encode(raw);
		string decoded = base64::decode(b64);
		if (encoded == b64) {
			cout << "\033[32mok\033[0m";
		} else {
			cout << "\033[31;1m" << encoded << "\033[0m";
			fails++;
		}
		cout << ", ";
		if (decoded == raw) {
			cout << "\033[32mok\033[0m";
		} else {
			cout << "\033[31;1m" << decoded << "\033[0m";
			fails++;
		}
		cout << "\n";
	}

	return (fails > 0 ? 1 : 0);
}