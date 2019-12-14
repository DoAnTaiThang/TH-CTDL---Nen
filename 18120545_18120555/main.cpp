#include <iostream>
#include "HuffmanTree.h"
#include "TransformUtils.h"
#include "BinaryFileHelper.h"

//#define _CRT_SECURE_NO_WARNINGS

using std::string;
using std::cin;
using std::cout;
int main()
{

	try
	{

		string input, output, decompress;
		char* tail = new char;
		cout << "------- Nhap ten file can nen: ";
		getline(cin, input);
		output = input;
		output.erase(output.begin() + output.find('.'), output.end());
		decompress = output;
		output += "_compressed.bin";
		ifstream file(input, ios::in | ios::binary);
		if (!file.is_open()) throw exception("Khong the mo file!");

		stringstream stream;
		stream << file.rdbuf();// copy du lieu tu file ra stream de xu li (tro vao dau file)
		file.close();

		const auto file_content = stream.str();// copy du lieu tu stream sang string file_content
		const auto file_size = BinaryFileHelper::get_file_size(input);// do lon du lieu (byte)
		cout << "Kich thuoc file: " << file_size << " bytes" << endl;

		HuffmanTree huffman_tree(file_content);
		const auto encoded = huffman_tree.encode(file_content);// ma hoa cac ki tu
		const auto bytes = TransformUtils::transform_string_to_bytes(encoded);// chuyen chuoi da ma hoa thanh byte(char)

		BinaryFileHelper::write(output, bytes);// tao file moi va viet vao
		const auto after_size = BinaryFileHelper::get_file_size(output);
		cout << "Nen file thanh cong!" << endl;
		cout << endl;
		cout << "-> Ten file nen: " << output << endl;
		cout << endl;
		cout << "Kich thuoc file sau khi nen: " << after_size << " bytes" << endl;
		cout << endl;
		
		int lcgn;
		cout << "------- Ban co muon giai nen? -------" << endl;
		cout << "1. Co" << endl;
		cout << "2. Khong" << endl;
		cin >> lcgn;
		if (lcgn == 1)
		{
			std::size_t length = input.copy(tail, input.size() - input.find('.'), (int)input.find('.'));
			tail[length] = '\0';
			decompress += "_decode";
			decompress += tail;
			const auto output_data = BinaryFileHelper::read(output);
			//cout<<huffman_tree.decode(output_data);
			ofstream outfile;
			outfile.open(decompress, ios::out | ios::binary);
			outfile << huffman_tree.decode(output_data);
			outfile.close();
			cout << "Giai nen file thanh cong!" << endl;
			cout << endl;
			cout << "-> Ten file da giai nen: " << decompress << endl;
			cout << endl;
		}
		if (lcgn == 2)
		{
			return 0;
		}
		
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
	
	cout << "------- Ban co muon nen va giai nen folder? -------" << endl;
	cout << "1. Co" << endl;
	cout << "2. Khong" << endl;
	int lc;
	cin >> lc;
	
	if (lc == 1)
	{
		cin.ignore();
		string folder;
		cout << "Nhap ten folder: ";
		getline(cin, folder);
		int templength = folder.size();
		char* temp = new char;
		for (int i = 0; i < folder.size(); i++)
		{
			temp[i] = folder[i];
		}
		temp[folder.size()] = '\0';
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;



		hFind = FindFirstFile(temp, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			cout << "Khong co du lieu trong folder!" << endl;
			return 0;
		}
		else
		{
			cout << endl;
			
			vector<string> s = get_all_files_names_within_folder(FindFileData.cFileName);

			for (int i = 0; i < s.size(); i++) {

				string name = folder + "/" + s[i];
				cout << "------- " << name << " -------" << "\n";
				cout << endl;
				char* tail = new char;
				const auto input = name;
				auto output = input;
				output.erase(output.begin() + output.find('.'), output.end());
				auto decompress = output;
				output += "_compressed.bin";
				std::size_t length = input.copy(tail, input.size() - input.find('.'), (int)input.find('.'));
				tail[length] = '\0';
				decompress += "_decode";
				decompress += tail;
				ifstream file(name, ios::in | ios::binary);
				if (!file.is_open()) throw exception("Khong the mo file.");

				stringstream stream;
				stream << file.rdbuf();
				file.close();

				const auto file_content = stream.str();
				const auto file_size = BinaryFileHelper::get_file_size(name);
				cout << "Kich thuoc file: " << file_size << " bytes" << endl;

				HuffmanTree huffman_tree(file_content);
				const auto encoded = huffman_tree.encode(file_content);
				const auto bytes = TransformUtils::transform_string_to_bytes(encoded);

				BinaryFileHelper::write(output, bytes);
				const auto after_size = BinaryFileHelper::get_file_size(output);

				cout << "Nen file thanh cong!" << endl;
				cout << "-> Ten file nen: " << output << endl;
				cout << "Kich thuoc file sau khi nen: " << after_size << " bytes" << endl;
				cout << endl;

				const auto output_data = BinaryFileHelper::read(output);
				ofstream outfile;
				outfile.open(decompress, ios::out | ios::binary);
				outfile << huffman_tree.decode(output_data);
				outfile.close();
				cout << "Giai nen file thanh cong!" << endl;
				cout << "-> Ten file da giai nen: " << decompress << endl;
				cout << endl;
			}
			FindClose(hFind);
		}
	}
	if (lc == 2)
	{
		return 0;
	}
	system("pause");
	return 0;
}