#pragma once
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <exception>
#include <vector>
#include <sstream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "TransformUtils.h"

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class BinaryFileHelper
{
public:
	static void write(const string&, const vector<unsigned char>&);
	static string read(const string&, const int = 1000);
	static streampos get_file_size(const string& filename);
private:
	BinaryFileHelper();
};
vector<string> get_all_files_names_within_folder(string folder);

