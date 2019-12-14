#pragma once
#include <vector>
#include <bitset>

#define _CRT_SECURE_NO_WARNINGS

using std::string;
using std::vector;
using std::bitset;

class TransformUtils
{
public:
	static vector<unsigned char> transform_string_to_bytes(const string&);
	static string transform_byte_to_string(const unsigned char&);

private:
	TransformUtils();
};

