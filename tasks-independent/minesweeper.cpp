#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>


using Board = std::vector<std::vector<int>>;


template <typename Stream>
bool load(Board& board, Stream& ss)
{
	std::string line;
	//for (std::string line; std::getline(std::cin, line);)
	for (int j = 0; j < board.size(); j++)
	{
		ss >> line;

		if (ss.eof()) { return false; }
		if (line == "") { return true; }

		for (int i = 0; i < board[j].size(); i++)
		{
			if (line[i] == '\0') { puts("Somethings is wrong!"); return false; }
			if (line[i] == '*')
			{
				board[j][i] = -1;
				if (i > 0 && j > 0 && board[j-1][i-1] != -1)										{ board[j - 1][i - 1] += 1; }
				if (i > 0 && board[j][i-1] != -1)													{ board[j][i - 1] += 1; }
				if (j > 0 && board[j-1][i] != -1)													{ board[j - 1][i] += 1; }
				
				if (i > 0  && j < (board.size() - 1) && board[j+1][i-1] != -1)						{ board[j + 1][i - 1] += 1; }
				if (i < (board[j].size() - 1) && j > 0 && board[j-1][i+1] != -1)					{ board[j - 1][i + 1] += 1; }
				
				if (i < (board[j].size() - 1) && board[j][i+1] != -1)								{ board[j][i + 1] += 1; }
				if (i < (board[j].size() - 1) && j < (board.size() - 1) && board[j+1][i+1] != -1)	{ board[j + 1][i + 1] += 1; }
				if (j < (board.size() - 1) && board[j+1][i] != -1)									{ board[j + 1][i] += 1; }
			}
		}
	}

	return true;
}

static std::string pretty_print(Board board)
{
	std::string output;
	for (auto line : board)
	{
		output += std::accumulate(
				line.begin(), line.end(), std::string(""),
				[](std::string acc, int x) -> std::string {
					return acc + (x == -1 ? '*' : (char)(x + '0'));
				}
		) + '\n';
	}
	//output += '\n';

	return output;
}


static void solve()
{
	int count = 1;
	int x; int y;
	std::cin >> y >> x;

	while (x && y)
	{
		Board board = std::vector<std::vector<int>>(y, std::vector<int>(x, 0));
		bool a = load<std::istream>(board, std::cin);

		std::cout << "Field #" << count << ":\n";
		++count;

		std::cout << pretty_print(board);;

		std::cin >> y >> x;
		if ( x && y ) { std::cout << '\n'; }
	}
}

static std::string solve(std::string data)
{
	std::string output;
	int count = 1;
	int x; int y;
	std::stringstream ss(data);
	ss >> y >> x;

	while (x && y)
	{
		Board board = std::vector<std::vector<int>>(y, std::vector<int>(x, 0));
		bool a = load<std::stringstream>(board, ss);

		output += std::string("Field #") + std::to_string(count) + std::string(":\n");
		++count;

		output += pretty_print(board) + '\n';

		ss >> y >> x;
	}

	return output;
}


int main(void)
{
	solve();
	return 0;
}
