#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>
#include <vector>
#include <utility>
#include <numeric>
#include <limits>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <set>


#define WATCH(x) std::cout << (#x) << ": " << (x) << '\n';
#define PRINT(s, x) std::cout << s << ": " << x << '\n';
#define FOR_PRINT(s, items) for (auto x : items) { PRINT(s, x) }
#define FOR_DICT_PRINT(s, items) for (auto x : items) { PRINT(x.first, x.second) }


#define BUFF_SIZE 128
#define ALPHABET_SIZE 4 // TODO 26
#define FIRST_TOKEN 'a'
#define MAX_WORD_SIZE 16


using Words_type = std::vector<std::string>;
using Alphabet = std::unordered_map<char, char>;
using Encrypt_sol = std::pair<bool, Alphabet>;


template <typename T>
auto set_to_vec(std::set<T> s)
{
	std::vector<T> vec;
    vec.reserve(s.size());
    std::copy(s.begin(), s.end(), std::back_inserter (vec));
	std::sort(vec.begin(), vec.end(), std::greater<>());

	return vec;
}

struct Trie
{
	bool is_leaf;
	Trie(bool leaf = false)
		: is_leaf(leaf), childs(std::unordered_map<char, Trie*>())
	{}

	~Trie() { for (auto& [_, tr] : childs) { delete tr; } }

	std::unordered_map<char, Trie*> childs;
};

static void insert_trie(Trie* &head, std::string str)
{
	Trie* tmp = head;
	for (auto token : str)
	{
		if (tmp->childs.find(token) == tmp->childs.end())
		{
			tmp->childs[token] = new Trie(true);
			tmp->is_leaf = false;
		}
		tmp = tmp->childs[token];
	}
	tmp->is_leaf = true;
}

static bool search_trie(Trie* head, std::string pattern)
{
	Trie* tmp = head;
	for (auto token : pattern)
	{
		if (tmp->childs.find(token) == tmp->childs.end()) { return false; }

		tmp = tmp->childs[token];
	}
	return true;
}

static void print_trie(Trie* root, unsigned int depth, bool is_new_word)
{
	if (!root) { return; }
	
	if (depth == 0)
	{
		std::cout << "---------------------\nTRIE printing\n---------------------\n\n";
	}
	
	for (const auto [token, child] : root->childs)
	{
		if (is_new_word) { std::cout << std::string(5*depth, ' '); }
		std::cout << " -> " << token;
		print_trie(child, depth + 1, false);
		if (child->is_leaf) { puts(""); }
		is_new_word = true;
	}
}

static Words_type get_words_of_nlenght(
		Trie* root, std::string acc, unsigned int depth, unsigned int n)
{
	Words_type words;
	if (!root) { return {}; }
	if (depth > n) { return words; }
	if (root->is_leaf && depth == n) { words.push_back(acc); }

	for (auto [token, child] : root->childs)
	{	
		auto tmp = get_words_of_nlenght(child, acc + token, depth + 1, n);
		for (auto item : tmp) { words.push_back(item); }
	}

	return words;
}

static std::set<unsigned int> get_words_length(Trie* root, unsigned int depth)
{
	std::set<unsigned int> lenghts;
	if (!root) { return {}; }
	if (root->is_leaf) { lenghts.insert(depth); }

	for (auto [token, child] : root->childs)
	{	
		auto tmp = get_words_length(child, depth + 1);
		for (auto item : tmp) { lenghts.insert(item); }
	}

	return lenghts;
}

struct MinedTrie
{
	MinedTrie(Words_type&& ws)
		: words(std::move(ws)), trie(new Trie()), count_words(words.size())
	{
		for (const auto& word : words) { insert_trie(trie, word); }
		lenghts = set_to_vec<unsigned int>(get_words_length(trie, 0));
		//print_trie(trie, 0, true);
	}
	
	~MinedTrie() { delete trie; }

	Trie* trie;
	//std::unordered_map<unsigned int, Words_type> words;
	Words_type words;
	std::vector<unsigned int> lenghts;
	unsigned int count_words;
};


struct Input
{
	Input(Words_type&& ws, std::vector<Words_type>&& vec)
		: words(std::move(ws)), decrypt_inputs(std::move(vec)) {}

	Words_type words;
	std::vector<Words_type> decrypt_inputs;
};

static Input read_input()
{
	unsigned int i;
	std::string line;
	char tmp_line[BUFF_SIZE];

	std::cin >> i;
	Words_type words( i );

	std::getchar();
	unsigned int k = 0;
	while (k < words.size() && std::getline(std::cin, line))
	{
		words[k] = line;
		++k;
	}

	std::vector<Words_type> tmp;
	unsigned int j = 0;
	while (std::getline(std::cin, line))
	{
		tmp.push_back({});
		std::stringstream ss(line);

		while (ss >> tmp_line) { tmp[j].push_back(tmp_line); }
		++j;
	}

	return { std::move(words), std::move(tmp) };
}

static std::string decrypt_word(Alphabet new_alphabet, std::string word)
{
	std::string output(word.size(), ' ');
	for (int i = 0; auto token : word)
	{
		output[i] = new_alphabet[token];
		++i;
	}
	return output;
}

static bool check_alphabet(MinedTrie& root, Alphabet alphabet, Words_type words)
{
	for (auto word : words)
	{
		if (!search_trie(root.trie, decrypt_word(alphabet, word))) { return false; }
	}
	return true;
}

static Alphabet get_alternated_dict(MinedTrie* root, std::string word, Alphabet dict)
{
	for (auto token : )

	return new_dict;
}

static Encrypt_sol backtracking(
		MinedTrie* root, Words_type words, Alphabet dict, unsigned int depth)
{
	bool is_valid = check_alphabet(root, dict, words);
	if (depth == words.size()) { return { is_valid, dict }; }

	if (is_valid) { return { true, dict }; }

 	dict = swap_dict(dict, 0, 1); // TODO
	std::vector<bool> options (root.count_words);
	// TODO

	for (unsigned int i = 0; i < root.count_words; i++)
	{
		if (!options[i]) { continue; } // FIXME
		if (!is_valid(i, depth)) { continue; } // FIXME

		std::vector<int> indices(....);
		set_in_table(i, depth, indices, ...);

		if (!inconsistent())
		{
			auto encrypt_sol = backtracking(root, words, dict, depth + 1);
			is_valid = encrypt_sol.first;
			dict = encrypt_sol.second;
			break;
		}
		remove_from_table(indices, number);
	}
 
	return { is_valid, dict };
}

static Alphabet get_default_dict()
{
	Alphabet default_dict;
	std::array<char, ALPHABET_SIZE> alp_arr;
	std::iota(alp_arr.begin(), alp_arr.end(), 'a');

	for (auto token : alp_arr) { default_dict.insert({token, ' '}); }

	return default_dict;
}

static std::string solve(MinedTrie& root, Words_type words)
{
	std::stringstream ss;
	Words_type sorted_words;
	sorted_words.reserve(words.size());
	std::copy(words.begin(), words.end(), std::back_inserter(sorted_words));

	std::sort(sorted_words.begin(), sorted_words.end(),
		[](auto item1, auto item2) -> bool { return item1.size() > item2.size(); }
	);

	Alphabet astrerix_dict = get_default_dict;
	Alphabet default_dict = get_default_dict();
	for (auto& item : astrerix_dict) { item = '*'; }
	FOR_DICT_PRINT("alphabet", default_dict)
	FOR_PRINT("sorted_words", sorted_words)

	/////////////////////// backtracking called //////////////////////////////////
	auto [is_valid, dict] = backtracking(root, sorted_words, default_dict, 0);
	/////////////////////// backtracking called //////////////////////////////////

	for (auto i = 0; auto word : words)
	{
		ss << decrypt_word(is_valid ? dict : astrerix_dict, word);
		if (i < words.size() - 1) { ss << ' '; }
		++i;
	}

	return ss.str(); 
}

int main()
{
	auto input = read_input();
	MinedTrie root = MinedTrie(std::mover(input.words));
	
	int lim = input.decrypt_inputs.size() - 1;
	int i = 0;
	for (auto line : input.decrypt_inputs)
	{
		std::cout << solve(root, line) << (i++ < lim ? "\n" : "");
	}
	
	return 0;
}

