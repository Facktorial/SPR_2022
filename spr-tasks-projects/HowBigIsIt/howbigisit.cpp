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


#define PRINT(s, x) std::cout << s << ": " << x << '\n';
#define PRINT_LINE(x) std::cout << x << ' ';
#define FOR_PRINT(s, items) for (auto x : items) { PRINT(s, x) }
#define FOR_FOR_PRINT(s, vecvec) for (auto items : vecvec){ for (auto x : items) { PRINT_LINE(x) } PRINT("", "") }


#define BUFF_SIZE 128


struct Input
{
	Input(std::vector<std::pair<double, std::vector<double>>>&& vec) : data(std::move(vec)){}
	std::vector<std::pair<double, std::vector<double>>> data;
};


static Input read_input()
{
	unsigned int i;
	std::string line;
	char tmp_line[BUFF_SIZE];

	std::cin >> i;
	std::vector<std::pair<double, std::vector<double>>> input_vec( i );

	std::getchar();
	unsigned int k = 0;
	while (std::getline(std::cin, line) && k < i)
	{
		//if (line == "\n") { continue; }
		unsigned int count;
		sscanf(line.c_str(), "%d %[^\n]s", &count, tmp_line);

		std::vector<double> tmp( count );
		for (int j = 0; j < count; j++) 
		{
			sscanf(tmp_line, "%lf %[^\n]s", &tmp[j], tmp_line);
		}

		input_vec[k] = std::make_pair( count, tmp );
		++k;
	}

	return { std::move(input_vec) };
}

static double x_distance(double radius_1, double radius_2)
{
	return 2.0 * std::sqrt(radius_1 * radius_2);
}

template <typename T>
static std::vector<T> swap(std::vector<T> parent, unsigned int i, unsigned int j)
{
	auto tmp = parent[i];
	parent[i] = parent[j];
	parent[j] = tmp;

	return parent;
}

static double backtracking(int idx, int depth, std::vector<double> circles, const std::vector<std::vector<double>>& precompute_distances, std::vector<unsigned int> index_map)
{
	double output = std::numeric_limits<double>::max();

	if (depth == circles.size())
	{
		std::vector<double> tmp ( circles.size(), 0 );
		tmp[0] = circles[0];
		for (int i = 1; i < circles.size(); i++)
		{
			double local_tmp;
			for (int j = 0; j < i; j++)
			{
				local_tmp = std::max(
					local_tmp,
					std::max(
						circles[i],
						//tmp[j] + x_distance(circles[i], circles[j])
						tmp[j] + precompute_distances[index_map[j]][index_map[i]]
					)
				);
				//PRINT("local", local_tmp)
			}
			tmp[i] = std::max(circles[i], local_tmp);
		}
		//FOR_PRINT("tmp", tmp)

		std::vector<double> out;
		std::transform(
			tmp.begin(), tmp.end(), circles.begin(), std::back_inserter(out),
				[](double x, double r_i) -> double {
					return x + r_i;
				}
		);

		//FOR_PRINT("out", out)
		//PRINT("bottom", *(std::max_element(out.begin(), out.end())))
		return *(std::max_element(out.begin(), out.end()));
	}

	output = std::min(output, backtracking(idx + 1, depth + 1, circles, precompute_distances, index_map));
	
	for (int i = 0; i < depth - 1; i++)
	{
		circles = swap<double>(circles, depth - i - 1, depth - i);
		index_map = swap<unsigned int>(index_map, depth - i - 1, depth - i);
		output = std::min(output, backtracking(idx + 1, depth + 1, circles, precompute_distances, index_map));
	}
	
	circles = swap<double>(circles, 0, 1);
	index_map = swap<unsigned int>(index_map, 0, 1);
	output = std::min(output, backtracking(idx + 1, depth + 1, circles, precompute_distances, index_map));

	return output;
}

static double solve(std::vector<double> vec)
{
	std::vector<std::vector<double>> precompute_distances = std::vector(vec.size(), std::vector<double>(vec.size(), 0));
	//std::vector<std::vector<double>> precompute_distances = std::vector(vec.size(), std::vector<double>(vec.size(), std::numeric_limits<double>::max()));

	for (unsigned int j = 0; j < vec.size(); j++)
	{
		for (unsigned int i = 0; i < j; i++)
		{
			precompute_distances[j][i] = x_distance(vec[j], vec[i]);
			precompute_distances[i][j] = x_distance(vec[j], vec[i]);
		}
	}

	std::vector<unsigned int> index_map(vec.size());
	std::iota(index_map.begin(), index_map.end(), 0);

	return backtracking(0, 1, vec, precompute_distances, index_map); 
}

int main()
{
	auto input = read_input();
	std::cout.precision(3);
	std::cout << std::fixed;

	int lim = input.data.size() - 1;
	int i = 0;
	for (auto [_, line] : input.data)
	{
		std::cout << solve(line) << '\n'; //(i++ < lim ? "\n" : "");
	}

	return 0;
}

