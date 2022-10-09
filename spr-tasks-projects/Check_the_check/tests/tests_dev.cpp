// This tells doctest to provide a main() function
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../tests/doctest.h"
#include "../check_the_check_dev.cpp"
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

void test_cases_by_debug(std::vector<std::string> inputs, std::vector<std::string> outcomes)
{
	for (auto i = 0; i < inputs.size(); i++) 
	{
		SUBCASE("SUBCASE: " + std::to_string(i + 1)) {
			std::cout << inputs[i] << '\n';
			std::string tmp = check_the_check(inputs[i] + '\n');
			if (tmp == "") { continue; }
			REQUIRE(tmp == outcomes[i] + "\n");
			std::cout << "=================\n";
		}	
	}
}


TEST_SUITE("Check the checks") {

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

	TEST_CASE("Debug input set") {
		std::vector<std::string> inputs = {
"......K.\n"
"........\n"
"........\n"
"........\n"
".....n..\n"
"k.......\n"
"........\n"
"........\n",
"K......k\n"
"........\n"
"........\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n", 
"K......k\n" // 3rd
"........\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"Kp.....k\n" // 4th
"prn.....\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"K..R...k\n"
"........\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"K.pr...k\n" // 6th
"b....q..\n"
"..p..nn.\n"
"........\n"
"..b.....\n"
"........\n"
"........\n"
"bq.....b\n",
"K..RB..k\n" // 7th
".....R.P\n"
"..p.....\n"
".......Q\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"......B.\n"
"........\n"
"..p.....\n"
"........\n"
"..Kpk..r\n"
"........\n"
"........\n"
".......b\n",
"......P.\n"
"...K.k..\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"........\n"
"...K....\n"
"pppppppp\n"
"..n.n...\n"
"........\n"
"........\n"
".k......\n"
".......b\n",
"........\n"
"...K....\n"
"pppppppp\n"
"........\n"
"........\n"
"........\n"
"k.......\n"
".......b\n",
"........\n"
"...k....\n"
"....P...\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"..P.....\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
"........\n"
"........\n"
"...R....\n"
".....K..\n"
"........\n",
"........\n"
"...k..R.\n"
"........\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"R..k....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"...R....\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
".....B..\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n" // 19th
"...k....\n"
"........\n"
".B......\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
".....B..\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
".B......\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
"...p....\n"
"........\n"
"...R....\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"..r.....\n"
".B......\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
"..N.....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"...pp...\n"
"....N...\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"....p...\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"..pk....\n"
".N......\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"...k.q..\n"
".....N..\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"..N.....\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"....N...\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
".....N..\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
".N......\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"q.......\n"
"........\n"
"...k....\n"
"........\n"
"....P...\n"
".....K..\n"
"........\n",
"........\n"
"q.......\n"
"........\n"
"...k....\n"
"........\n"
"....P.p.\n"
".....K..\n"
"........\n",
".....r..\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".r...K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"...b....\n",
"r......r\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"...n....\n"
".....K..\n"
"........\n",
"K......k\n"
"........\n"
"........\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"K......k\n"
"........\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"Kp.....k\n"
"prn.....\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"K..R...k\n"
"........\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"K.pr...k\n"
"b....q..\n"
"..p..nn.\n"
"........\n"
"..b.....\n"
"........\n"
"........\n"
"bq.....b\n",
"K..RB..k\n"
".....R.P\n"
"..p.....\n"
".......Q\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"......B.\n"
"........\n"
"..p.....\n"
"........\n"
"..Kpk..r\n"
"........\n"
"........\n"
".......b\n",
"......P.\n"
"...K.k..\n"
"..p.....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".......b\n",
"........\n"
"...K....\n"
"pppppppp\n"
"..n.n...\n"
"........\n"
"........\n"
".k......\n"
".......b\n",
"........\n"
"...K....\n"
"pppppppp\n"
"........\n"
"........\n"
"........\n"
"k.......\n"
".......b\n",
"........\n"
"........\n"
"...k....\n"
"........\n"
".B.R....\n"
"........\n"
"........\n"
".K......\n",
"..k.....\n"
"ppp.pppp\n"
"........\n"
".R...B..\n"
"........\n"
"........\n"
"PPPPPPPP\n"
"K.......\n",
"rnbqk.nr\n"
"ppp..ppp\n"
"....p...\n"
"...p....\n"
".bPP....\n"
".....N..\n"
"PP..PPPP\n"
"RNBQKB.R\n",
"........\n"
"...k....\n"
"....P...\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"..P.....\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
"........\n"
"........\n"
"...R....\n"
".....K..\n"
"........\n",
"........\n"
"...k..R.\n"
"........\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"R..k....\n"
"........\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"...R....\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
".....B..\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
".B......\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
".....B..\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
".B......\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
"...p....\n"
"........\n"
"...R....\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"..r.....\n"
".B......\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"........\n"
"..N.....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"...k....\n"
"...pp...\n"
"....N...\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"..pk....\n"
".N......\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"...k.q..\n"
".....N..\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"..N.....\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"....N...\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
".....N..\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"........\n"
".N......\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"........\n",
"........\n"
"q.......\n"
"........\n"
"...k....\n"
"........\n"
"....P...\n"
".....K..\n"
"........\n",
"........\n"
"q.......\n"
"........\n"
"...k....\n"
"........\n"
"....P.p.\n"
".....K..\n"
"........\n",
".....r..\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".r...K..\n"
"........\n",
"........\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"........\n"
".....K..\n"
"...b....\n",
"r......r\n"
"........\n"
"........\n"
"...k....\n"
"........\n"
"...n....\n"
".....K..\n"
"........\n",
"k......K\n"
"........\n"
"pppppppp\n"
"pppppppp\n"
"pppppppp\n"
"pppppppp\n"
"pppppppp\n"
"pppppppp\n",
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
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: black king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: no king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: white king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: white king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: white king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: black king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: no king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: white king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: no king is in check.",
			"Game #1: no king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: no king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: black king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: white king is in check.",
			"Game #1: no king is in check.",
			"Game #1: white king is in check.",
			"Game #1: no king is in check.",
		};

		test_cases_by_debug(inputs, outcomes);
	}

	TEST_CASE("Sawa's insight") {
		std::vector<std::string> inputs = {
			"K.......\n"
			"........\n"
			".k......\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
			"........\n"
		};

		std::vector<std::string> outcomes = {
			"no",
		};

		auto x = "\n" + inputs[0];

		MESSAGE(x);
		
		test_cases_by_sets(inputs, outcomes);
	}
}

