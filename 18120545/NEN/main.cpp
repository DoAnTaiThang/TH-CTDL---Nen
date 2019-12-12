#include <iostream>
#include "HuffmanTree.h"
#include "TransformUtils.h"
#include "BinaryFileHelper.h"
using std::string;
using std::cin;
using std::cout;
int main()
{
	try
	{

		const auto input = "SH.txt";
		const auto output = "SH.bin";
		const auto decompress = "SH_decode.txt";
		ifstream file(input, ios::in | ios::binary);
		if (!file.is_open()) throw exception("Exception: Unable to open file.");

		stringstream stream;
		stream << file.rdbuf();
		file.close();

		const auto file_content = stream.str();
		const auto file_size = BinaryFileHelper::get_file_size(input);
		cout << "Before compression: " << file_size << " bytes" << endl;

		HuffmanTree huffman_tree(file_content);
		const auto encoded = huffman_tree.encode(file_content);
		const auto bytes = TransformUtils::transform_string_to_bytes(encoded);

		BinaryFileHelper::write(output, bytes);
		const auto after_size = BinaryFileHelper::get_file_size(output);
		const auto delta = file_size - after_size;
		cout << "Compress complete!" << endl;

		cout << "After compression: " << after_size << " bytes" << endl;
		cout << "Delta: " << delta << " (" << static_cast<double>(delta) / file_size << ")" << endl;

		const auto output_data = BinaryFileHelper::read(output);
		//cout<<huffman_tree.decode(output_data);
		ofstream outfile;
		outfile.open(decompress, ios::out | ios::binary);
		outfile << huffman_tree.decode(output_data);
		outfile.close();
		cout << "Decompress complete!" << endl;
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
	/*cin.get();
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;


	hFind = FindFirstFile("FF", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return 0;
	}
	else
	{
		printf(TEXT("The first file found is %s\n"),
			FindFileData.cFileName);

		vector<string> s = get_all_files_names_within_folder(FindFileData.cFileName);

		for (int i = 0; i < s.size(); i++) {

			string name = "FF/" + s[i];
			cout << name << "\n";
			
			const auto input = name;
			const auto output = name + ".bin";
			const auto decompress = name + "(decode)";
			ifstream file(name, ios::in | ios::binary);
			if (!file.is_open()) throw exception("Exception: Unable to open file.");

			stringstream stream;
			stream << file.rdbuf();
			file.close();

			const auto file_content = stream.str();
			const auto file_size = BinaryFileHelper::get_file_size(name);
			cout << "Before compression: " << file_size << " bytes" << endl;

			HuffmanTree huffman_tree(file_content);
			const auto encoded = huffman_tree.encode(file_content);
			const auto bytes = TransformUtils::transform_string_to_bytes(encoded);

			BinaryFileHelper::write(output, bytes);
			const auto after_size = BinaryFileHelper::get_file_size(output);
			const auto delta = file_size - after_size;
			//cout << "Compress complete!" << endl;

			cout << "After compression: " << after_size << " bytes" << endl;
			cout << "Delta: " << delta << " (" << static_cast<double>(delta) / file_size << ")" << endl;
			const auto output_data = BinaryFileHelper::read(output);
			ofstream outfile;
			outfile.open(decompress, ios::out | ios::binary);
			outfile << huffman_tree.decode(output_data);
			outfile.close();
			//cout << "Decompress complete!" << endl;
		}
		FindClose(hFind);
	}*/
	system("pause");
	return 0;
}