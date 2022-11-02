#include <iostream>
#include <string.h>

#define MAX 30001

using INT = long long;

static INT dynamic_table[MAX];
static INT options[] = { 1, 5, 10, 25, 50 };
const int NUM_OPTIONS = sizeof(options)/sizeof(options[0]);

struct Solution
{
	Solution(INT c, INT v) : ways_count(c), value(v) {}
	INT ways_count;
	INT value;
};

static void print_sol(Solution sol)
{
	char buff [512];
	bool is_only = sol.ways_count == 1;
	sprintf(buff,
		"There %s %lld way%s to produce %lld cents change.\n",
		is_only ? "is only" : "are", sol.ways_count, is_only ? "" : "s", sol.value
	);
	printf("%s", buff);
}

static void calc_table(int n)
{
	memset(dynamic_table, 0, MAX * sizeof(INT));
	dynamic_table[0] = 1;
	for (int j = 0; j < NUM_OPTIONS; j++)
	{
		int c = options[j];
		for (int i = c; i <= n; i++)
		{
			dynamic_table[i] += dynamic_table[i - c];
		}
	}
}

static Solution solve(INT n)
{
	calc_table(n);
	return Solution(dynamic_table[n], n);
}

int main()
{
	INT n;
	while (std::cin >> n)
	{
		print_sol(solve(n));
		std::cin.get();
		if (std::cin.peek() == '\n') { break; }
	}
	return 0;
}
