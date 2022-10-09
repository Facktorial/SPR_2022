
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <functional>
#include <variant>


#define TEST_MODE 1

#define TESTING_SEQUENCE_SIZE 100


const std::filesystem::path cwd = std::filesystem::current_path();
const std::string OUT_DIR = "ps_files";
const std::string FILENAME = "united_free_pascal_codes";
const char INDENT = ' ';
const unsigned int INDENT_REPEAT = 2;


enum class Clausules
{
	PROGRAM,
	VAR,
	BEGIN,
	BODY,
	END
};


enum class Pascal_Fns
{
	READLN,
	IF,
	ELSE_IF,
	ELSE,
	WRITELN
};


static std::string string_repeat(unsigned int count, char c)
{
	std::string out;
	for (unsigned int i = 0; i < count; i++) { out += c; }
	return out;
}


static std::function<std::string(int, std::string)> ps_funcitons_dictionary(Pascal_Fns fn)
{
	switch (fn)
	{

		case Pascal_Fns::READLN:
			return [](int indent_lvl, std::string vars) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "readln(" + vars + ");\n";
			};
		case Pascal_Fns::IF:
			return [](int indent_lvl, std::string expr) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "if " + expr + " then\n"; 
			};
		case Pascal_Fns::ELSE_IF:
			return [](int indent_lvl, std::string expr) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "else if " + expr + " then\n"; 
			};
		case Pascal_Fns::ELSE:
			return [](int indent_lvl, std::string expr) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "else " + expr + " then\n"; 
			};
		case Pascal_Fns::WRITELN:
			return [](int indent_lvl, std::string vars) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "writeln(" + vars + ");\n";
			};
	}
}

template <typename ReturnType>
using TypeReturningFunctions = std::variant<
	std::function<ReturnType()>,
	std::function<ReturnType(std::string input)>,
	std::function<ReturnType(std::vector<Pascal_Fns> fns, int indent_lvl, std::string input)>
>;


static TypeReturningFunctions<std::string> clausules_dictionary(Clausules clausule)
{
	switch (clausule)
	{
		case Clausules::PROGRAM:
			return []() -> std::string {
				return "program sort(input, output);\n";
			};
		case Clausules::VAR:
			return [](std::string vars) -> std::string {
				return "var\n" + vars + " : integer;\n";
			};
		case Clausules::BEGIN: return []() -> std::string { return "begin\n"; };
		case Clausules::BODY: return [](
			std::vector<Pascal_Fns> functions,
			int indent_lvl,
			std::string expr
		) -> std::string {
			std::stringstream ss;

			for (auto fn : functions)
			{
				ss << ps_funcitons_dictionary(fn)(indent_lvl, expr);
			}

			return ss.str();
		};
		case Clausules::END: return []() -> std::string { return "end.\n"; };
	}
}

struct Input
{
	Input(int n, std::vector<int> vars) : n_cases(n), n_variables(vars) {}

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
	for (const auto& entry : std::filesystem::directory_iterator(cwd.string()))
	{
		std::filesystem::remove_all(entry.path());
	}
}


static Input read_input()
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

static std::string make_filename([[maybe_unused]] unsigned int n)
{
#if TEST_MODE
	return FILENAME + "_" + static_cast<char>(n + '0');
#else
	return "";
#endif
}

static std::string make_vars_string(unsigned int n)
{
	std::string output;
	for (unsigned int i = 0; i < n; i++)
	{
		output += ('a' + static_cast<char>(i));
		output += ",";
	}
	output.pop_back();
	return output;
}

static std::string make_content(int n)
{
	std::stringstream ss;

	ss << std::get<0>(clausules_dictionary(Clausules::PROGRAM))();

	std::string vars = make_vars_string(static_cast<unsigned int>(n));
	ss << std::get<1>(clausules_dictionary(Clausules::VAR))(vars);

	ss << std::get<0>(clausules_dictionary(Clausules::BEGIN))();

	// TODO
	//std::string expr = make_expr_string(......);
	// TODO
	// int indent_lvl = get_indentation ???
	ss << std::get<2>(clausules_dictionary(Clausules::BODY))({ Pascal_Fns::WRITELN }, 1, "\"" + vars + "\"");

	ss << std::get<0>(clausules_dictionary(Clausules::END))();

	return ss.str();
}

#if TEST_MODE

// FIXME
template<typename T, T... ints>
void print_sequence([[ maybe_unused ]]std::integer_sequence<T, ints...> int_seq)
{
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}

#endif

static std::string make_test_data([[ maybe_unused ]] int n)
{
#if TEST_MODE
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(0, TESTING_SEQUENCE_SIZE);

	std::stringstream ss;
	auto seq = std::vector<unsigned int>(TESTING_SEQUENCE_SIZE);
	auto cp_seq = std::vector<unsigned int>(TESTING_SEQUENCE_SIZE);
	for (unsigned int i = 0; i < TESTING_SEQUENCE_SIZE; i++) { seq[i] = 1 + i; }
	for (unsigned int i = 0; i < TESTING_SEQUENCE_SIZE; i++) { cp_seq[i] = 1 + i; }
	//auto seq = std::make_integer_sequence<int, TESTING_SEQUENCE_SIZE> {};
	//auto seq_cp = std::make_integer_sequence<int, TESTING_SEQUENCE_SIZE> {};

	random_shuffle(cp_seq.begin(), cp_seq.end(), [&](int idx){
		return distribution(gen) % idx; 
	});
	
	//ss << print_sequence(shuffled_seq) << '\n' << print_sequence(seq);
	for (auto i : cp_seq) { ss << i << ' '; }
	ss << '\n';
	for (auto i : seq) { ss << i << ' '; }

	return ss.str();
#else
	return "";
#endif
}

static std::vector<Solution> solve(Input input)
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


int main()
{
#if TEST_MODE
	remove_files();
#endif

	auto input = read_input();
	const auto solution = solve(input);

	for (const auto& [filename, content, testing_data] : solution)
	{
#if TEST_MODE
		std::fstream file (cwd.string() + '/' + OUT_DIR + '/' + filename);
		if (file.is_open())
		{
			file << content << '\n';
			file.close();
		}

		std::fstream test_file (cwd.string() + '/' + OUT_DIR + '/' + filename + "testing_data");
		if (test_file.is_open())
		{
			test_file << testing_data << '\n';
			test_file.close();
		}
#else
		std::cout << content << '\n';
#endif
	}

	return 0;
}
