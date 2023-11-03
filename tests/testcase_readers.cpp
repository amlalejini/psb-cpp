#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include "psb/readers/TestCaseReaders.hpp"

TEST_CASE("Basement", "[problem][psb2]") {

  using problem_t = psb::readers::Basement;
  const std::string data_path("problem-data/basement/basement.json");

  problem_t problem;
  REQUIRE(problem.name() == "basement");

  SECTION("LOAD TESTS FROM JSON") {
    emp::vector<
      std::pair<problem_t::input_t, problem_t::output_t>
    > loaded_tests;

    std::ifstream data_ifstream(data_path);
    nlohmann::json data_json;

    std::string line;
    while (std::getline(data_ifstream, line)) {
      loaded_tests.emplace_back(problem.ReadTestJSON(line));
    }
    data_ifstream.close();

    REQUIRE(loaded_tests.size() == 3);

    std::pair<
      problem_t::input_t,
      problem_t::output_t
    > correct = {
      {55,-38,-3,-37,-25,-93},
      3
    };
    REQUIRE(loaded_tests[0]==correct);
  }
}

TEST_CASE("ForLoopIndex", "[problem][psb1]") {
  using problem_t = psb::readers::ForLoopIndex;
  const std::string data_path("problem-data/for-loop-index/for-loop-index.json");

  problem_t problem;
  REQUIRE(problem.name() == "for-loop-index");

  std::ifstream data_ifstream(data_path);
  nlohmann::json data_json;

  emp::vector<
    std::pair<problem_t::input_t, problem_t::output_t>
  > loaded_tests;


  std::string line;
  while (std::getline(data_ifstream, line)) {
    loaded_tests.emplace_back(problem.ReadTestJSON(line));
    std::cout << loaded_tests.back().second << std::endl;
  }
  data_ifstream.close();

  REQUIRE(loaded_tests.size() == 11);
}

// TEST_CASE("BouncingBalls", "[problem][psb2]") {
//   using problem_t = psb::BouncingBalls;
//   const std::string data_path("problem-data/bouncing-balls/bouncing-balls.json");

//   problem_t problem;
//   REQUIRE(problem.name() == "bouncing-balls");

//   SECTION("LOAD TESTS FROM JSON") {
//     emp::vector<
//       std::pair<problem_t::input_t, problem_t::output_t>
//     > loaded_tests;

//     std::ifstream data_ifstream(data_path);
//     nlohmann::json data_json;

//     std::string line;
//     while (std::getline(data_ifstream, line)) {
//       loaded_tests.emplace_back(problem.ReadTestJSON(line));
//     }
//     data_ifstream.close();

//     REQUIRE(loaded_tests.size() == 3);

//     std::pair<
//       problem_t::input_t,
//       problem_t::output_t
//     > correct = {
//       std::make_tuple(1.001, 1.0, 1),
//       2.001
//     };
//     REQUIRE(loaded_tests[0]==correct);

//     // for (size_t i = 0; i < loaded_tests.size(); ++i) {
//     //   std::cout << "test "<< i << ": "
//     //     << std::get<0>(loaded_tests[i].first) << ", "
//     //     << std::get<1>(loaded_tests[i].first) << ", "
//     //     << std::get<2>(loaded_tests[i].first) << ", "
//     //     << "| "
//     //     << loaded_tests[i].second
//     //     << std::endl;
//     // }
//   }
// }