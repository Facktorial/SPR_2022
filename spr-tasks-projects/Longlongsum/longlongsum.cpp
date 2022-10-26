#include <iostream>
#include <vector>
#include <cstring>
#include <functional>

#define BUFF_SIZE 10000001
#define TYPE_SIZE 4 //data in format "x y\n"
#define WATCH(X) std::cout << (#X) << ": " << X << '\n';
#define iWATCH(X, idx) std::cout << (#X) << "[" << idx << "]: " << X << '\n';
#define WATCH_VECTOR(vec) for (auto item : vec) { WATCH(item) }

struct Input
{
	Input(char* b, size_t n) : buff(b), m(n) {}
	char* buff; // FIXME dangerous, but fast
	size_t m;
};

static std::vector<Input> read_input(
		std::function<void(char*, size_t,size_t, size_t)> handle_output)
{
	//std::vector<Input> inputs;
	char buffer[TYPE_SIZE * BUFF_SIZE];
	size_t n;
	std::cin >> n;
	std::cin.get();
	for (size_t i = 0; i < n; i++)
	{
		size_t m;
		std::cin >> m;
		std::cin.get();
		fread(buffer, TYPE_SIZE * m, 1, stdin);
		//inputs.push_back({ buffer, m });
		handle_output(buffer, m, i, n);
		memset(buffer, 0, strlen(buffer) + 1);
		std::cin.get();
	}
	//return inputs;
	return {};
}

static void handle_input(char* buffer, size_t m)
{
	char outcome[BUFF_SIZE];
	memset(outcome, 0, m + 1);
	char* line = TYPE_SIZE * (m - 1) + buffer;
	int carry = 0;
	for (int j = m - 1; j >= 0; j--, p -= TYPE_SIZE)
	{
		int x = line[0] + line[2] - '0' + carry;
		carry = (x > '9');
		if (carry) { x -= 10; }
		outcome[j] = static_cast<char>(x);
	}
	outcome[m] = '\n';
	fwrite(outcome, m + 1, 1, stdout);
}

int main()
{
	[[ maybe_unused ]] auto inputs = read_input(
		[](char* buff, size_t m, size_t i, size_t n) -> void {
			handle_input(buff, m);
			fwrite((i < n - 1) ? "\n" : "", 1, 1, stdout);
	});
	return 0;
}
