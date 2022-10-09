#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <variant>


#define TEST_MODE 1


#if TEST_MODE
	#include "test_tools.cpp"
#endif


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


struct Input
{
	Input(int n, std::vector<int> vars) : n_cases(n), n_variables(vars) {}

	int n_cases;
	std::vector<int> n_variables;
};


template <typename ReturnType>
using PrintPascalFunctions = std::variant<
	std::function<ReturnType(int indent_lvl, std::vector<char> input)>,
	std::function<ReturnType(int indent_lvl, std::string input)>
>;


template <typename ReturnType>
using PrintClausuleFunctions = std::variant<
	std::function<ReturnType()>,
	std::function<ReturnType(std::string input)>,
	std::function<ReturnType(
		std::vector<Pascal_Fns> fns, int indent_lvl, std::variant<
			std::vector<char>, std::string
		> input		
	)>
>;


static std::string string_repeat(unsigned int count, char c)
{
	std::string out;
	for (unsigned int i = 0; i < count; i++) { out += c; }
	return out;
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


static std::string vars_unpacked(std::vector<char> vec)
{
	auto output = std::accumulate(
		vec.begin(), vec.end(), std::string(""),
		[](std::string acc, char c) -> std::string {
			return std::move(acc) + c + ", ";
	});
	output.pop_back();
	output.pop_back();

	return output;
}


static std::vector<char> make_vec_variables(unsigned int n)
{
	auto vec = std::vector<char>(n, 'a'); 
	std::iota(vec.begin(), vec.end(), 'a');
	return vec;
}


static std::vector<char> swap_var(std::vector<char> vec, unsigned int chidx, unsigned int pidx)
{
	auto tmp = vec[chidx];
	vec[chidx] = vec[pidx];
	vec[pidx] = tmp;

	return vec;
}


static int facktorial(int n) { int num = 1; int i = 1; while (i <= n){ num *= i; ++i; } return num; }


static PrintPascalFunctions<std::string> ps_funcitons_dictionary(Pascal_Fns fn)
{
	switch (fn)
	{
		case Pascal_Fns::READLN:
			return [](int indent_lvl, std::vector<char> vars) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "readln(" + vars_unpacked(vars) + ");\n";
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
			return [](int indent_lvl, [[maybe_unused]] std::string expr) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "else\n"; 
			};

		case Pascal_Fns::WRITELN:
			return [](int indent_lvl, std::vector<char> vars) -> std::string {
				return string_repeat(
					INDENT_REPEAT * static_cast<unsigned int>(indent_lvl), INDENT
				) + "writeln(" + vars_unpacked(vars) + ");\n";
			};
	}
}


static PrintClausuleFunctions<std::string> clausules_dictionary(Clausules clausule)
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
			std::variant<std::vector<char>, std::string> data
		) -> std::string {
			std::stringstream ss;

			for (auto fn : functions)
			{
				if (fn == Pascal_Fns::WRITELN or fn == Pascal_Fns::READLN)
				{
					ss << std::get<0>(ps_funcitons_dictionary(fn))(
						indent_lvl, std::get<0>(data)
					);	
				}
				else
				{
					ss << std::get<1>(ps_funcitons_dictionary(fn))(
						indent_lvl, std::get<1>(data)
					);	
				}
			}

			return ss.str();
		};
		case Clausules::END: return []() -> std::string { return "end.\n"; };
	}
}


static void backtracking_sorting(
	std::stringstream& ss, std::vector<char> parent, unsigned int idx, int depth
)
{
	// -1 bc indexing from 0, -1 bc (n-1) states
	//unsigned int if_index = idx - 1 - 1;
	idx -= 1 + 1;

	if (depth == parent.size())
	{
		ss << std::get<2>(clausules_dictionary(Clausules::BODY))(
			{ Pascal_Fns::WRITELN }, depth, parent
		);
		return;
	}

	std::cout << "\nidx: " << idx << " parent: " << vars_unpacked(parent) << '\n';
	std::cout << "depth: " << depth << " parent: " << vars_unpacked(parent) << "\n\n";

	ss << std::get<2>(clausules_dictionary(Clausules::BODY))(
		{ Pascal_Fns::IF }, depth,
		std::string(parent[idx] + std::string(" < ") + parent[depth])
	);

	backtracking_sorting(ss, parent, idx, depth + 1);

	auto child = swap_var(parent, idx, depth);

	ss << std::get<2>(clausules_dictionary(Clausules::BODY))(
		{ Pascal_Fns::ELSE }, depth,
		std::string("")
		//std::string(child[depth] + std::string(" > ") + parent[if_index])
	);

	backtracking_sorting(ss, child, idx, depth + 1);

}

	// if (depth == 2)
	// {
	// 	ss << std::get<2>(clausules_dictionary(Clausules::BODY))({ Pascal_Fns::IF }, depth, vars);
	// 	//ss << std::get<2>(clausules_dictionary(Clausules::BODY))({ Pascal_Fns::WRITELN }, depth + 1, vars);
	// 	ss << std::get<2>(clausules_dictionary(Clausules::BODY))({ Pascal_Fns::ELSE }, depth , vars);
	// 	//ss << std::get<2>(clausules_dictionary(Clausules::BODY))({ Pascal_Fns::WRITELN }, depth + 1, s_vars);
	// }

	// while (if_index >= 0)
	// while (if_index >= 0)
	// while (if_index >= 0)
	// {
	// 	if (!if_index && var_size > 1)
	// 	{
	// 		ss << std::get<2>(clausules_dictionary(Clausules::BODY))(
	// 			{ Pascal_Fns::WRITELN },
	// 			depth + 1,
	// 			vars
	// 		);
	// 	}

	// 	// TODO
	// 	//std::string expr = make_expr_string(......);
	// 	// TODO
	// 	// int indent_lvl = get_indentation ???
	// 	ss << std::get<2>(clausules_dictionary(Clausules::BODY))({ Pascal_Fns::WRITELN }, depth + 1, vars);
	// }
//}


static void backtracking_sorting_initial(std::stringstream& ss, unsigned int var_size)
{
	if (var_size == 0) { return; }

	std::vector<char> vars = make_vec_variables(var_size);
	
	int depth = 1;

	if (var_size == 1) 
	{
		ss << std::get<2>(
				clausules_dictionary(Clausules::BODY)
			)({ Pascal_Fns::READLN, Pascal_Fns::WRITELN }, depth, vars);
		return;
	}

	backtracking_sorting(ss, vars, var_size, depth);
}


std::string make_content(int n)
{
	std::stringstream ss;

	ss << std::get<0>(clausules_dictionary(Clausules::PROGRAM))();

	std::string vars = make_vars_string(static_cast<unsigned int>(n));
	ss << std::get<1>(clausules_dictionary(Clausules::VAR))(vars);

	ss << std::get<0>(clausules_dictionary(Clausules::BEGIN))();

	backtracking_sorting_initial(ss, static_cast<unsigned int>(n));

	ss << std::get<0>(clausules_dictionary(Clausules::END))();

	return ss.str();
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


static std::vector<std::string> solve(Input input)
{
	std::vector<std::string> solutions;
	solutions.reserve(static_cast<unsigned int>(input.n_cases));

	for (auto n_vars : input.n_variables)
	{
		std::string content = make_content(n_vars);

		solutions.push_back( content );
	}

	return solutions;
}


int main()
{
#if TEST_MODE
	auto input = read_input_test();
	const auto solution = solve_with_tests(input);

	do_work(solution);
#else
	auto input = read_input();
	const auto solution = solve(input);

	for (const auto& content : solution)
	{
		std::cout << content << '\n';
	}
#endif

	return 0;
}

