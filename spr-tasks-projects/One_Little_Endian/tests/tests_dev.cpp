// This tells doctest to provide a main() function
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../tests/doctest.h"
#include "../endians_dev.cpp"
#include <iostream>
#include <vector>

#undef SUBCASE
#define SUBCASE(...) DOCTEST_SUBCASE(std::string(__VA_ARGS__).c_str())

// TEST_SUITE("with a funny name,") {
//     
// 	TEST_CASE("with a funnier name\\:") {
//         SUBCASE("with the funniest name\\,") {
//             MESSAGE("Yes!");
//         }
//         SUBCASE("with a slightly funny name :") {
//             MESSAGE("Yep!");
//         }
//         SUBCASE("without a funny name") {
//             MESSAGE("NO!");
//         }
//     }
// 
//     TEST_CASE("without a funny name:") {
//         MESSAGE("Nooo");
//     }
// }

// SCENARIO("vectors can be sized and resized") {
//     GIVEN("A vector with some items") {
//         std::vector<int> v(5);
// 
//         REQUIRE(v.size() == 5);
//         REQUIRE(v.capacity() >= 5);
// 
//         WHEN("the size is increased") {
//             v.resize(10);
// 
//             THEN("the size and capacity change") {
//                 CHECK(v.size() == 20);
//                 CHECK(v.capacity() >= 10);
//             }
//         }
//         WHEN("the size is reduced") {
//             v.resize(0);
// 
//             THEN("the size changes but not capacity") {
//                 CHECK(v.size() == 0);
//                 CHECK(v.capacity() >= 5);
//             }
//         }
//         WHEN("more capacity is reserved") {
//             v.reserve(10);
// 
//             THEN("the capacity changes but not the size") {
//                 CHECK(v.size() == 5);
//                 CHECK(v.capacity() >= 10);
//             }
//         }
//         WHEN("less capacity is reserved") {
//             v.reserve(0);
// 
//             THEN("neither size nor capacity are changed") {
//                 CHECK(v.size() == 10);
//                 CHECK(v.capacity() >= 5);
//             }
//         }
//     }
// }

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

