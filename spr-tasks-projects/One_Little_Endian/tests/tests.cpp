// This tells doctest to provide a main() function
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../tests/doctest.h"
#include "../endians.cpp"
#include <iostream>
#include <vector>

#undef SUBCASE
#define SUBCASE(...) DOCTEST_SUBCASE(std::string(__VA_ARGS__).c_str())

TEST_SUITE("Endians") {

	TEST_CASE("Basic inputs") {
		std::vector<std::string> inputs = {
			"123456789",
			"-123456789",
			"1",
			"5",
			"16777216",
			"20034556"
		};

		std::vector<std::string> outcomes = {
			"123456789 converts to 365779719\n", 
			"-123456789 converts to -349002504\n",
			"1 converts to 16777216\n",
			"5 converts to 83886080\n",
			"16777216 converts to 1\n",
			"20034556 converts to -55365375\n"
		};

		for (auto i = 0; i < inputs.size(); i++) 
		{
			SUBCASE("SUBCASE: " + inputs[i]) {
				REQUIRE(handle_input<int32_t>(inputs[i]) == outcomes[i]);
			}	
		}
	}
}

