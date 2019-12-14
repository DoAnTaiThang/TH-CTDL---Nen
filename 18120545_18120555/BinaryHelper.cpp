#include "BinaryFileHelper.h"

//#define _CRT_SECURE_NO_WARNINGS

BinaryFileHelper::BinaryFileHelper() {}

void BinaryFileHelper::write(const string& filename, const vector<unsigned char>& data)
{
	ofstream output(filename, ios::binary);
	if (!output.is_open())
		throw exception("Exception: Unable to open file.");

	copy(
		data.begin(),
		data.end(),
		ostream_iterator<unsigned char>(output));

	output.close();
}
string BinaryFileHelper::read(const string& filename, const int max_per_cycle)
{
	ifstream input(filename, ios::binary);
	if (!input.is_open())
		throw exception("Exception: Unable to open file.");

	vector<unsigned char> container;
	container.reserve(max_per_cycle);

	stringstream byte_stream;
	const auto transform_to_string = [&byte_stream](unsigned char byte)
	{
		byte_stream << TransformUtils::transform_byte_to_string(byte);
	};

	char* const buffer = new char[max_per_cycle];
	while (!input.eof())
	{
		input.read(buffer, max_per_cycle);

		const auto count = input.gcount();
		container.insert(container.begin(), buffer, buffer + count);
		for_each(container.begin(), container.begin() + count, transform_to_string);

		memset(buffer, 0, max_per_cycle);
	}
	delete[] buffer;

	input.close();
	return byte_stream.str();
}

streampos BinaryFileHelper::get_file_size(const string& filename)
{
	ifstream file(filename, ios::binary | ios::ate);// mo file va dua con tro den vi tri cuoi cua file
	return file.tellg();// vi tri hien tai cua con tro
}
vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}