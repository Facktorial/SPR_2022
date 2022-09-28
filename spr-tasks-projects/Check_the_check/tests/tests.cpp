// This tells doctest to provide a main() function
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../tests/doctest.h"
#include "../check_the_check.cpp"
#include <iostream>
#include <vector>

#undef SUBCASE
#define SUBCASE(...) DOCTEST_SUBCASE(std::string(__VA_ARGS__).c_str())


void test_cases_by_sets(std::vector<std::string> inputs, std::vector<std::string> outcomes)
{
	for (auto i = 0; i < inputs.size(); i++) 
	{
		SUBCASE("SUBCASE: " + std::to_string(i)) {
			std::string tmp = check_the_check(inputs[i] + '\n');
			if (tmp == "") { continue; }
			//std::cout << "Game #1: " + outcomes[i] + " king is in check.\n";
			//std::cout << tmp;
			REQUIRE(tmp == "Game #1: " + outcomes[i] + " king is in check.\n");
		}	
	}
}


TEST_SUITE("Endians") {

	TEST_CASE("Basic input") {
		std::vector<std::string> inputs = {
			"..k.....\n"
			"ppp.pppp\n"
			"........\n"
			".R...B..\n"
			"........\n"
			"........\n"
			"PPPPPPPP\n"
			"K.......\n",

			"rnbqkbnr\n"
			"pppppppp\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"PPPPPPPP\n"
			"RNBQKBNR\n",

			"rnbqk.nr\n"
			"ppp..ppp\n"
			"....p...\n"
			"...p....\n"
			".bPP....\n"
			".....N..\n"
			"PP..PPPP\n"
			"RNBQKB.R\n",

			"........\n"
			"........\n"
			"........\n"
			"........\n"
			".b......\n"
			"........\n"
			"........\n"
			"....K...\n",

			"........\n"
			"........\n"
			"........\n"
			"........\n"
			".q......\n"
			"........\n"
			"........\n"
			"....K...\n",

			"....r...\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"....K...\n",

			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"...p....\n"
			"....K...\n",

			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
		};

		std::vector<std::string> outcomes = {
			"black",
			"no",
			"white",
			"white",
			"white",
			"white",
			"white",
			""
		};

		test_cases_by_sets(inputs, outcomes);
	}

	TEST_CASE("Second input set") {
		std::vector<std::string> inputs = {
			"....r...\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"....P...\n"
			"....K...\n",

			".....k..\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"....K...\n",

			"...k....\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"....K...\n",

			"........\n"
			"....K...\n"
			".....p..\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n",

			"........\n"
			"....P...\n"
			".....k..\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n",

			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
		};

		std::vector<std::string> outcomes = {
			"no",
			"no",
			"no",
			"no",
			"no",
			""
		};

		test_cases_by_sets(inputs, outcomes);
	}
}

