#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <random>


#define TESTING_SEQUENCE_SIZE 100
#define TEST_AMOUNT 15


std::string make_content(int n);


const std::filesystem::path cwd = std::filesystem::current_path();
const std::string OUT_DIR = "ps_files";
const std::string FILENAME = "united_free_pascal_codes";
const std::string SUFFIX = ".pas";


// FIXME FUJKY
struct Input_test
{
 	Input_test(int n, std::vector<int> vars) : n_cases(n), n_variables(vars) {}
 
 	int n_cases;
 	std::vector<int> n_variables;
};


struct Solution
{
	Solution(std::string f, std::string c, std::string t)
		: filename(f), content(c), testing_data(t) {}

	std::string filename;
	std::string content;
	std::string testing_data;
};


[[ maybe_unused ]] static void remove_files()
{
	for (const auto& entry : std::filesystem::directory_iterator(
			cwd.string() + "/" + OUT_DIR
		))
	{
		std::filesystem::remove_all(entry.path());
	}
}

static std::string make_filename(unsigned int n)
{
	return FILENAME + "_" + static_cast<char>(n + '0');
}


// FIXME
template<typename T, T... ints>
void print_sequence([[ maybe_unused ]]std::integer_sequence<T, ints...> int_seq)
{
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}


static std::string make_test_data([[ maybe_unused ]] int n)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(0, n);

	std::stringstream ss;
	auto seq = std::vector<unsigned int>(static_cast<unsigned int>(n));
	auto cp_seq = std::vector<unsigned int>(static_cast<unsigned int>(n));
	for (unsigned int i = 0; i < static_cast<unsigned int>(n); i++) { seq[i] = 1 + i; }

	std::string tmp;
	for (unsigned int j = 0; (j < static_cast<unsigned int>(n)) || (j < TEST_AMOUNT); j++)
	{
		random_shuffle(cp_seq.begin(), cp_seq.end(), [&](int idx){
			return distribution(gen) % idx; 
		});
	
		tmp = std::accumulate(
			cp_seq.begin(), cp_seq.end(), std::string(""),
			[](std::string acc, unsigned int num){
				return std::move(acc) + std::to_string(num) + ' ';
		});
		// for (auto i : cp_seq) { ss << i << ' '; }
		ss << tmp << '\n';
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(n); i++) { cp_seq[i] = 1 + i; }
	//auto seq = std::make_integer_sequence<int, TESTING_SEQUENCE_SIZE> {};
	//auto seq_cp = std::make_integer_sequence<int, TESTING_SEQUENCE_SIZE> {};
	//ss << print_sequence(shuffled_seq) << '\n' << print_sequence(seq);
	ss << '\n';
	for (auto i : seq) { ss << i << ' '; }

	return ss.str();
}


static Input_test read_input_test()
{
	int i, n_vars;
	std::cin >> i;
	std::vector<int> vars; // = std::vector<int>(static_cast<unsigned long>(i));

	std::string line;
	std::getline(std::cin, line); // reads "\n"
	std::getline(std::cin, line); // reads "\n"

	while(getline(std::cin, line))
	{
		sscanf(line.c_str(), "%d\n", &n_vars);
		vars.push_back(n_vars);
	}

	return { i, vars };
}


static std::vector<Solution> solve_with_tests(Input_test input)
{
	std::vector<Solution> solutions;
	solutions.reserve(static_cast<unsigned int>(input.n_cases));

	for (unsigned int i = 0; auto n_vars : input.n_variables)
	{
		std::string filename = make_filename(i);
		std::string content = make_content(n_vars);
		std::string testing_data = make_test_data(n_vars);

		solutions.push_back({ filename, content, testing_data });
		++i;
	}

	return solutions;
}


static void do_work(const std::vector<Solution>& solution)
{
	remove_files();

	for (const auto& [filename, content, testing_data] : solution)
	{
		std::fstream file (cwd.string() + '/' + OUT_DIR + '/' + filename + SUFFIX);
		file.open(cwd.string() + '/' + OUT_DIR + '/' + filename + SUFFIX, std::ios::out);
		if (file.is_open())
		{
			file << content << '\n';
			file.close();
		}

		std::fstream test_file (
			cwd.string() + '/' + OUT_DIR + '/' + filename + "_testing_data" + SUFFIX
		);
		test_file.open(
			cwd.string() + '/' + OUT_DIR + '/' + filename + "testing_data" + SUFFIX,
			std::ios::out
		);
		if (test_file.is_open())
		{
			test_file << testing_data << '\n';
			test_file.close();
		}
	}
}

