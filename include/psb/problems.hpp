#pragma once
#ifndef PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE
#define PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE

#include <utility>
#include <string>
#include <functional>

#include "json/json.hpp"
#include "emp/base/vector.hpp" // Q: best way to handle library import to play friendly with other projects using custom versions of empirical?

namespace psb {

template<typename INPUT_T, typename OUTPUT_T>
struct ProblemBase {

  using input_t = INPUT_T;
  using output_t = OUTPUT_T;
  using json = nlohmann::json;

  using fun_interpret_json_t = std::function< std::pair<input_t,output_t>(const json &) >;

  /// Interpret JSON object into input/output pair.
  /// Base implementation naively assumes a single-input, single-output test.
  /// @NOTE: this might need to get changed to be more generic down the line...
  fun_interpret_json_t fun_interpret_json =
    [](const json & j) {
      return std::make_pair(j["input1"], j["output1"]);
    };

  virtual std::string name() const = 0;

  /// Interpet a single test stored as a string but following JSON.
  virtual std::pair<input_t,output_t> ReadTestJSON(const std::string & s) const {
    return ReadTestJSON(json::parse(s));
  }

  /// Interpret a single test stored as a JSON object.
  virtual std::pair<input_t,output_t> ReadTestJSON(const json & j) const {
    return fun_interpret_json(j);
  }

  virtual void SetInterpretJSON(const fun_interpret_json_t & f) {
    fun_interpret_json = f;
  }

};

// basement
struct Basement :
  ProblemBase<
    /*INPUT_T=*/emp::vector<int>,
    /*OUTPUT_T=*/int
  >
{

  std::string name() const override { return "basement"; }

};

// bouncing-balls
struct BouncingBalls :
  ProblemBase<
    /*INPUT_T=*/std::tuple<double,double,int>,
    /*OUTPUT_T=*/double
  >
{

  BouncingBalls() {
    SetInterpretJSON(
      [](const json & j) {
        return std::make_pair(
          std::make_tuple(j["input1"], j["input2"], j["input3"]),
          j["output1"]
        );
      }
    );
  }

  std::string name() const override { return "bouncing-balls"; }

};

// bowling
struct Bowling :
  ProblemBase<
    /*INPUT_T=*/std::string,
    /*OUTPUT_T=*/int
  >
{

  std::string name() const override { return "bowling"; }

};

// camel-case
struct CamelCase:
  ProblemBase<
    /*INPUT_T=*/std::string,
    /*OUTPUT_T=*/std::string
  >
{

  std::string name() const override { return "camel-case"; }

};

// coin-sums
struct CoinSums:
  ProblemBase<
    /*INPUT_T=*/int,
    /*OUTPUT_T=*/emp::array<int, 4>
  >
{
  CoinSums() {
    SetInterpretJSON(
      [](const json & j) {
        return std::make_pair(
          j["input1"],
          {j["output1"],j["output2"],j["output3"],j["output4"]}
        );
      }
    );
  }

  std::string name() const override { return "coin-sums"; }
};

// cut-vector
struct CutVector:
  ProblemBase<
    /*INPUT_T=*/emp::vector<int>,
    /*OUTPUT_T=*/emp::array<emp::vector<int>,2>
  >
{
  CutVector() {
    SetInterpretJSON(
      [](const json & j) {
        return std::make_pair(
          j["input1"],
          {j["output1"],j["output2"]}
        );
      }
    );
  }
  std::string name() const override { return "cut-vector"; }
};

// dice-game
struct DiceGame:
  ProblemBase<
    /*INPUT_T=*/emp::array<int,2>,
    /*OUTPUT_T=*/double
  >
{
  CutVector() {
    SetInterpretJSON(
      [](const json & j) {
        return std::make_pair(
          {j["input1"],j["input2"]},
          j["output1"]
        );
      }
    );
  }
  std::string name() const override { return "dice-game"; }
};

// // find-pair
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "find-pair"; }
// };

// // fizz-buzz
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "fizz-buzz"; }
// };

// // final-cost
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "final-cost"; }
// };

// // greatest-common-divisor
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "greatest-common-divisor"; }
// };

// // indices-of-substring
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "indices-of-substring"; }
// };

// // leaders
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "leaders"; }
// };

// // luhn
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "luhn"; }
// };

// // mastermind
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "mastermind"; }
// };

// // middle-character
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "middle-character"; }
// };

// // paired-digits
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "paired-digits"; }
// };

// // shopping-list
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "shopping-list"; }
// };

// // snow-day
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "snow-day"; }
// };

// // solve-boolean
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "solve-boolean"; }
// };

// // spin-words
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "spin-words"; }
// };

// // square-digits
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "square-digits"; }
// };

// // substitution-cipher
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "substitution-cipher"; }
// };

// // twitter
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "twitter"; }
// };

// // vector-distance
// struct :
//   ProblemBase<
//     /*INPUT_T=*/
//     /*OUTPUT_T=*/
//   >
// {
//   std::string name() const override { return "vector-distance"; }
// };



}

#endif // #ifndef PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE
