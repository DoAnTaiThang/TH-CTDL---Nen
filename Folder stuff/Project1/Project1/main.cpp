//
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void main()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;


	hFind = FindFirstFile("FF", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		printf(TEXT("The first file found is %s\n"),
			FindFileData.cFileName);

		vector<string> s = get_all_files_names_within_folder(FindFileData.cFileName);

		for (int i = 0; i < s.size(); i++) {

			string name = "Tests/" + s[i];
			cout << name << "\n";
			string nameout = "Test/" + s[i];
			ifstream f_read(name, ios::binary | ios::in);
			ofstream f_write(nameout, ios::binary | ios::out);

			char x;
			f_read.unsetf(ios::skipws);

			while (f_read >> x)
			{
				f_write << x;
			}

			f_read.close();
			f_write.close();
		}
		FindClose(hFind);
	}
}