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


#define TEST_MODE 0

#define TESTING_SEQUENCE_SIZE 100


const std::filesystem::path cwd = std::filesystem::current_path();
const std::string OUT_DIR = "ps_files";
const std::string FILENAME = "united_free_pascal_codes";


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


static std::function<std::string(int, std::string)> ps_funcitons_dictionary(Pascal_Fns fn)
{
	switch (fn)
	{

		case Pascal_Fns::READLN:
			return [](int indent_lvl, std::string vars) -> std::string {
				return std::string(static_cast<unsigned int>(indent_lvl), '\t')
					+ "readln(" + vars + ")\n";
			};
		case Pascal_Fns::IF:
			return [](int indent_lvl, std::string expr) -> std::string {
				return std::string(static_cast<unsigned int>(indent_lvl), '\t')
					+ "if " + expr + " then\n"; 
			};
		case Pascal_Fns::ELSE_IF:
			return [](int indent_lvl, std::string expr) -> std::string {
				return std::string(static_cast<unsigned int>(indent_lvl), '\t')
					+ "else if " + expr + " then\n"; 
			};
		case Pascal_Fns::ELSE:
			return [](int indent_lvl, std::string expr) -> std::string {
				return std::string(static_cast<unsigned int>(indent_lvl), '\t')
					+ "else " + expr + " then\n"; 
			};
		case Pascal_Fns::WRITELN:
			return [](int indent_lvl, std::string vars) -> std::string {
				return std::string(static_cast<unsigned int>(indent_lvl), '\t')
					+ "writeln(" + vars + ")\n";
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
	std::vector<int> vars = std::vector<int>(static_cast<unsigned long>(i));

	std::string line;
	std::getline(std::cin, line); // reads "\n"
	std::getline(std::cin, line); // reads "\n"

	int count = 0;
	while(getline(std::cin, line))
	{
		sscanf(line.c_str(), "%d\n", &n_vars);
		vars[static_cast<unsigned int>(i)] = n_vars;
		++count;
	}

	return { i, vars };
}

static std::string make_filename([[maybe_unused]] unsigned int n)
{
#if TEST_MODE
	return FILENAME + "_" + (char) (n + '0');
#else
	return "";
#endif
}

static std::string make_vars_string(unsigned int n)
{
	std::string output;
	for (unsigned int i = 0; i < n; i++)
	{
		output += 'a' + static_cast<char>(i) + ',';
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
	ss << std::get<2>(clausules_dictionary(Clausules::BODY))({ Pascal_Fns::WRITELN }, 1, "\"" + vars + "\"\n");

	ss << std::get<0>(clausules_dictionary(Clausules::END))();

	return ss.str();
}

#if TEST_MODE

template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
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
	std::uniform_int_distribution<> distribution(0, 6);

	std::stringstream ss;
	auto seq = std::make_integer_sequence<int, TESTING_SEQUENCE_SIZE> {};
	auto seq_cp = std::make_integer_sequence<int, TESTING_SEQUENCE_SIZE> {};

	auto shuffled_seq = random_shuffle(seq_cp.begin(), seq_cp.end(), [](int n){
		return distribution(gen) % TESTING_SEQUENCE_SIZE; 
	})
	
	ss << print_sequence(shuffled_seq) << '\n' << print_sequence(seq);
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

		solutions[i] = { filename, content, testing_data };

		++i;
	}

	return solutions;
}


int main()
{
#if TEST_MODE
	std::string cwd = get_remove_files()
#endif

	auto input = read_input();
	const auto solution = solve(input);

	for (const auto& [filename, content, testing_data] : solution)
	{
#if TEST_MODE
		std::fstream file (cwd + '/' + OUT_DIR + '/' + filename);
		if (file.is_open())
		{
			file << content << '\n';
			file.close();
		}

		std::fstream file (cwd + '/' + OUT_DIR + '/' + filename + "testing_data");
		if (file.is_open())
		{
			file << testing_data << '\n';
			file.close();
		}
#else
		std::cout << content << '\n';
#endif
	}

	return 0;
}
