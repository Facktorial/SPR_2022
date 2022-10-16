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


#define PRINT(s, x) std::cout << s << ": " << x << '\n';
#define FOR_PRINT(s, items) for (auto x : items) { PRINT(s, x) }
#define FOR_DICT_PRINT(s, items) for (auto x : items) { PRINT(s, x.first + ": " + x.second) }


#define BUFF_SIZE 128
#define ALPHABET_SIZE 5 // TODO 26
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
	MinedTrie(Words_type ws)
		: trie(new Trie())
	{
		for (const auto& word : ws) { insert_trie(trie, word); }
		lenghts = set_to_vec<unsigned int>(get_words_length(trie, 0));
		//print_trie(trie, 0, true);
	}
	
	~MinedTrie() { delete trie; }

	Trie* trie;
	std::unordered_map<unsigned int, Words_type> words;
	std::vector<unsigned int> lenghts;
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

static Alphabet& get_new_alphabet(Alphabet& dict, std::pair<char, char> change)
{
	dict[change.first] = change.second;
	FOR_DICT_PRINT(change.first + " -> " + change.second, dict)
	return dict;
}

static Alphabet swap_dict(Alphabet& parent, unsigned int i, unsigned int j)
{
	return get_new_alphabet(parent, { 'a' + i, 'a' + j });
}

static Encrypt_sol backtracking(
		unsigned int idx, unsigned int depth, Words_type words, Alphabet& dict,
		MinedTrie& root
)
{
	if (depth == words.size())
	{
		return { check_alphabet(root, dict, words), dict };
	}

	Encrypt_sol encrypt_sol = backtracking(idx + 1, depth + 1, words, dict, root);
	if (encrypt_sol.first) { return { true, encrypt_sol.second }; }
	
	for (unsigned int i = 0; i < depth - 1; i++)
	{
		dict = swap_dict(dict, depth - i - 1, depth - i);
		encrypt_sol = backtracking(idx + 1, depth + 1, words, dict, root);
		if (encrypt_sol.first) { return { true, encrypt_sol.second }; }
	}
	
	dict = swap_dict(dict, 0, 1);
	encrypt_sol = backtracking(idx + 1, depth + 1, words, dict, root);
	if (encrypt_sol.first) { return { true, encrypt_sol.second }; }

	return { check_alphabet(root, dict, words), dict };
}

static std::string solve(MinedTrie& root, Words_type words)
{
	std::stringstream ss;
	Words_type sorted_words (words.size());
	std::copy(words.begin(), words.end(), std::back_inserter(sorted_words));

	std::sort(sorted_words.begin(), sorted_words.end(),
		[](auto item1, auto item2) -> bool {
			return item1.size() > item2.size();
	});

	Alphabet default_dict, astrerix_dict;
	std::array<char, ALPHABET_SIZE> alp_arr;
	std::iota(alp_arr.begin(), alp_arr.end(), 'a');
	for (auto token : alp_arr) 
	{
		default_dict.insert({token, token});
		astrerix_dict.insert({token, '*'});
	}
	FOR_PRINT("alphabet", alp_arr)

	auto [is_valid, dict] = backtracking(0, 0, sorted_words, default_dict, root);

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

	MinedTrie root = MinedTrie(input.words);
	
	int lim = input.decrypt_inputs.size() - 1;
	int i = 0;
	for (auto line : input.decrypt_inputs)
	{
		std::cout << solve(root, line) << (i++ < lim ? "\n" : "");
	}
	
	return 0;
}

