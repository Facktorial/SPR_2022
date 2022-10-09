#include <vector>
#include <tuple>
#include <iostream>
#include <sstream>
#include <math.h>
#include <memory>
#include <numeric>


static std::string check_the_check();
static std::string check_the_check(std::string data);
static std::string check_the_check(std::vector<std::string> data);

enum class Color
{
	Black,
	White
};

static Color oposite_color(Color c) { return (c == Color::White ? Color::Black : Color::White); }

struct Pair
{
	Pair(int xx, int yy) : x(xx), y(yy) {}

	int x;
	int y;
};

struct Figure
{
	Figure(int x, int y, Color color) : m_color(color), m_x(x), m_y(y) {}
	virtual ~Figure(){}

	bool is_king() { return false; }
	// FIXME m_horse
	bool is_horseman() { return m_horse; }
	//auto position() const { return std::make_tuple(m_x, m_y); }
	std::tuple<int, int> position() const { return std::make_tuple(m_x, m_y); }

	virtual bool can_check(int kingx, int kingy) = 0;

	Color m_color;
	int m_x;
	int m_y;
	bool m_horse = false;
};

struct King: public Figure
{
	King(int x, int y, Color color) : Figure(x, y, color) { }
	bool is_king() { return true; }
	bool can_check(int kingx, int kingy) override
	{
		return (abs(m_x - kingx) <= 1 && abs(m_y - kingy) <= 1);
	}
};

struct Knight: public Figure
{
	Knight(int x, int y, Color color) : Figure(x, y, color){}
	bool is_horseman() { return true; }
	bool can_check(int, int) override { return false; }
};

struct Bischop: public Figure
{
	Bischop(int x, int y, Color color) : Figure(x, y, color){}
	bool can_check(int kingx, int kingy) override
	{
		return (abs(m_x - kingx) == abs(m_y - kingy));
	}
};

struct Rook: public Figure
{
	Rook(int x, int y, Color color) : Figure(x, y, color){}
	bool can_check(int kingx, int kingy) override
	{
		return (m_x == kingx || m_y == kingy);
	}
};

struct Queen: public Figure
{
	Queen(int x, int y, Color color) : Figure(x, y, color){}
	bool can_check(int kingx, int kingy) override
	{
		return (abs(m_x - kingx) == abs(m_y - kingy) || m_x == kingx || m_y == kingy);
	}
};

struct Pawn: public Figure
{
	Pawn(int x, int y, Color color) : Figure(x, y, color){}
	bool can_check(int kingx, int kingy) override
	{
		if (m_color == Color::White && m_y < kingy) { return false; }
		if (m_color == Color::Black && m_y > kingy) { return false; }

		return (
			(kingx == m_x - 1 || kingx == m_x + 1) && (kingy == m_y - 1 or kingy == m_y + 1)
		);
	}
};


struct Board
{
	// FIXME
	Board(int x, int y) : stdin_input(true), m_game_counter(-1), m_size(x, y)
	{
		figures = std::vector<Figure*>(static_cast<unsigned int>(x*y), nullptr);
	}

	~Board() { for (auto& figure : figures) { delete figure; } }

	void Clean()
	{
		for (auto& figure : figures) { delete figure; }

		figures = std::vector<Figure*>(static_cast<unsigned int>(m_size.x * m_size.y), nullptr);
		wKing = nullptr;
		bKing = nullptr;
	}

	bool load(std::string data)
	{
		m_data = data;
		return load_nostdin();
	}

	// bool load(std::vector<std::string> data)
	// {
	// 	m_data = std::accumulate(data.begin(), data.end(), std::string(""));
	// 	return load_nostdin();
	// }


	bool load_nostdin()
	{
		stdin_input = false;
		return load();
	}

	// FIXME -fuj dvoji logika paralelne ss/cin
	bool load()
	{
		m_game_counter++;

		std::stringstream ss;
		if (!stdin_input) { ss.str(m_data); }

		if (stdin_input && std::cin.eof()) { return false; }

		figures = std::vector<Figure*>(
			static_cast<unsigned int>(m_size.x * m_size.y), nullptr
		);
		
		int j = 0;
		for (std::string line; std::getline(stdin_input ? std::cin : ss, line);)
		{
			if (stdin_input && std::cin.eof())
				return false;

			// client input, only one scenario (board)
			if (!stdin_input && line == "")
				return false;

			if (line == "")
				return true;

			int i = 0;
			for (auto x : line)
			{
				if (x != '\n' || x != '.')
				{
					Figure* figure = nullptr;
					switch (x)
					{
						case 'K': figure = new King(i, j, Color::White); wKing = figure; break;
					    case 'k': figure = new King(i, j, Color::Black); bKing = figure; break;
					    case 'Q': figure = new Queen(i, j, Color::White); break;
					    case 'q': figure = new Queen(i, j, Color::Black); break;
					    case 'R': figure = new Rook(i, j, Color::White); break;
					    case 'r': figure = new Rook(i, j, Color::Black); break;
					    case 'B': figure = new Bischop(i, j, Color::White); break;
					    case 'b': figure = new Bischop(i, j, Color::Black); break;
						// FIXME, i dont udenrstand OOP i guess
					    case 'N': figure = new Knight(i, j, Color::White); figure->m_horse = true; break;
					    case 'n': figure = new Knight(i, j, Color::Black); figure->m_horse = true; break;
					    case 'P': figure = new Pawn(i, j, Color::White); break;
					    case 'p': figure = new Pawn(i, j, Color::Black); break;
					}
					figures.at(static_cast<unsigned long>(j * m_size.x + i)) = figure;
				}
				i++;
			}
			j++;
		}
		return true;
	}

	bool in_board(int x, int y)
	{
		return (x < m_size.x && x >= 0) && (y < m_size.y && y >= 0);
	}
	
	bool check_check(Color color, bool* empty)
	{
		if (color == Color::White && wKing == nullptr) { *empty = true; return false; }
		if (color == Color::Black && bKing == nullptr) { *empty = true; return false; }
		
	    return false || check_horsemen(color) || check_in_directions(color); 
	}

	bool check_horsemen(Color color)
	{
	    auto f = color == Color::White ? wKing : bKing;
		//auto [x, y] = f->position();
		auto x = f->m_x; // std::get<0>(f->position());
		auto y = f->m_y; // std::get<1>(f->position());

	    std::vector<std::tuple<int, int>> shifts = {
	        {-2, -1}, {-1, -2},
	        {-2, 1}, {-1, 2},
	        {2, -1}, {1, -2},
	        {2, 1}, {1, 2},
	    };

	    for (unsigned int i = 0; i < 8; i++)
	    {
			//auto [x1, y1] = shifts[i];
			auto x1 = std::get<0>(shifts[i]);
			auto y1 = std::get<1>(shifts[i]);
	        if (in_board(x + x1, y + y1))
	        {
				Figure* figure = figures.at((static_cast<unsigned long>((y + y1) * m_size.x) + static_cast<unsigned int>(x + x1)));
	            if (figure != nullptr)
				{
	                if ((figure->m_color == oposite_color(color)) && figure->is_horseman())
					{
						return true;
					}	
				}
			}
		}
	    return false;
	}
	
	bool check_in_directions(Color color)
	{
	    bool ret = false;
	    for (int i = -1; i < 2; i++)
	    {
	        for (int j = - 1; j < 2; j++)
	        {
	            if (i || j)
	            {
	                ret = ret || check_in_direction(color, i, j);			
	            }
	        }
	    }
	    return ret;
	}

	bool check_in_direction(Color color, int i, int j)
	{
	    auto f = color == Color::White ? wKing : bKing;
		//auto [x, y] = f->position();
		auto x = std::get<0>(f->position());
		auto y = std::get<1>(f->position());

	    bool keep_finding = true;
	    while (keep_finding)
	    {
			Figure* figure = figures.at(static_cast<unsigned int>(y * (m_size.y)) + static_cast<unsigned int>(x));

	        if (figure != nullptr && (x != f->m_x || y != f->m_y))
	        {
	            if (figure->can_check(f->m_x, f->m_y) && (figure->m_color == (color == Color::White ? Color::Black : Color::White)))
				{
	                return true;
				}
				return false;
	        }
	        x += i;
	        y += j;
	        keep_finding = in_board(x, y);
	    }
	    return  false;
	}
	
	bool stdin_input;
	int m_game_counter;
	Pair m_size;
	std::vector<Figure*> figures;
	std::string m_data;
	Figure* wKing = nullptr;
	Figure* bKing = nullptr;
};

static std::string solve_problem(Board& board)
{
	std::string output;

	bool wEmpty = false;
	bool bEmpty = false;
	bool a = true;
	while (a)
	{
		bool white = board.check_check(Color::White, &wEmpty);
		bool black = board.check_check(Color::Black, &bEmpty);

		if (!wEmpty || !bEmpty)
		{
			output += "Game #" + std::to_string(board.m_game_counter + 1) + ": ";

			if (white) { output += "white"; }
			if (black) { output += "black"; }
			if (!white && !black) { output += "no"; }

			output += " king is in check.\n";
		}

		board.Clean();
		a = board.load();
		wEmpty = false;
		bEmpty = false;
	}

	//std::cout << "DEBUG:\n" << output << '\n';

	return output;
}

static std::string check_the_check()
{
	Board board = Board(8, 8);
	[[maybe_unused]]  bool a = board.load();

	std::string out = solve_problem(board);
	std::cout << out; // << '\n';
	return out;
}

static std::string check_the_check(std::string data)
{
	Board board = Board(8, 8);
	[[maybe_unused]]  bool a = board.load(data);

	return solve_problem(board);
}

// static std::string check_the_check(std::vector<std::string> data)
// {
// 	Board board = Board(8, 8);
// 	[[maybe_unused]]  bool a = board.load(data);
// 
// 	return solve_problem(board);
// }

int main()
{
	check_the_check();
	return 0;
}

