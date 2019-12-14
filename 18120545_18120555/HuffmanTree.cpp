#include "HuffmanTree.h"

//#define _CRT_SECURE_NO_WARNINGS

HuffmanTree::HuffmanTree(const string& data)
{
	init(data);
}

void HuffmanTree::init(const string& data)
{
	auto symbols_dictionary = create_dictionary(data);
	auto symbols_vec = move_to_vector(symbols_dictionary);

	create_binary_tree(symbols_vec);// tao cay va tra ve con tro root cho binary_tree
	create_hash_table(symbols_dictionary);// tao bang kieu map chua ki tu va ma binary tuong ung sau khi dung thuat toan huffman xu li
}

map<char, SymbolPtr> HuffmanTree::create_dictionary(const string& data) const
{
	map<char, SymbolPtr> symbols_dict;// map gom ki tu va con tro den node mang ki tu do
	for (const auto& c : data)// con tro c tro vao du lieu
	{
		auto pos = symbols_dict.find(c);// tim ki tu c trong map. neu ko tim thay tra ve con tro o cuoi file
		if (pos != symbols_dict.end())// neu co ki tu trong map
		{
			++(*pos->second);// tan so (so lan lap lai) + 1
			continue; // chuyen con tro den ki tu tiep theo
		}
		symbols_dict.insert(make_pair(c, static_pointer_cast<Symbol>(make_shared<Symbol>(c))));// them vao map
	}
	return symbols_dict;
}

vector<SymbolPtr> HuffmanTree::move_to_vector(map<char, SymbolPtr>& dictionary) const// chuyen tat ca cac node vao 1 vector
{
	vector<SymbolPtr> symbols;
	symbols.reserve(dictionary.size());
	for_each(dictionary.begin(), dictionary.end(), [&symbols](pair<const char, SymbolPtr>& symbol) {
		symbols.push_back(move(symbol.second));
	});
	return symbols;
}

void HuffmanTree::create_binary_tree(vector<SymbolPtr>& vec)
{
	auto symbol_comparator = [](const SymbolPtr a, const SymbolPtr b) {
		return a->get_count() < b->get_count();
	};
	while (vec.size() > 1)
	{
		std::sort(vec.begin(), vec.end(), symbol_comparator);// sap xep theo chieu tang dan tan so xuat hien

		auto left = vec.front(), right = (*++vec.begin());
		auto node = new Node<char>(
			left->get_count() + right->get_count(),
			left,
			right);// conbine 2 node la lai thanh 1 node

		vec.erase(vec.begin(), vec.begin() + 2);
		vec.push_back(SymbolPtr(node));
	}
	binary_tree = vec.front();
}

void HuffmanTree::create_hash_table(map<char, SymbolPtr> dictionary)
{
	for (const auto& sym : dictionary)
	{
		auto exists = false;
		auto path = find_path(*binary_tree, sym.first, exists);

		if (!exists) throw exception("Exception: Invalid dictionary for given data.");

		hash_table.insert(pair<char, string>(sym.first, path));
	}
}

string HuffmanTree::find_path(Symbol& node, const char& c, bool& flag, const string& path)
{
	if (flag) return path;

	auto result(path);
	if (node.has_left()) result = find_path(*node.get_left(), c, flag, path + "0");
	if (node.has_right() && !flag) result = find_path(*node.get_right(), c, flag, path + "1");
	if (!node.has_left() && !node.has_right() && node.get_value() == c) flag = true;

	return result;
}

string HuffmanTree::encode(const string& data) const
{
	const short byte_size = 8;
	stringstream encoded_stream;
	for (const auto& c : data)
		encoded_stream << hash_table.at(c);

	auto result_str = encoded_stream.str();
	for (auto i = 0; i < 8 - result_str.size() % byte_size; i++)
		result_str += "0";// sau khi ma hoa neu tong so bit ko chia het cho 8 thi them 0 vao den khi nao chia het

	return result_str;
}

string HuffmanTree::decode(const string& binary_data_str) const
{
	stringstream decoded_data;
	const char* const binary_str = binary_data_str.c_str();
	unsigned long i = 0;
	while (strstr(binary_str + i, "1"))
	{
		decoded_data << find_symbol(*binary_tree, binary_str + i, i);
	}
	return decoded_data.str();
}

char HuffmanTree::find_symbol(Symbol& node, const char* const path, unsigned long& i) const
{
	if (!node.has_left() && !node.has_right())
		return node.get_value();

	if (*path == '0' && node.has_left()) return find_symbol(*node.get_left(), path + 1, ++i);
	if (*path == '1' && node.has_right()) return find_symbol(*node.get_right(), path + 1, ++i);

	return 0;
}


