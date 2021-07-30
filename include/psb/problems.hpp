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
// coin-sums
// cut-vector
// dice-game
// find-pair
// fizz-buzz
// final-cost
// greatest-common-divisor
// indices-of-substring
// leaders
// luhn
// mastermind
// middle-character
// paired-digits
// shopping-list
// snow-day
// solve-boolean
// spin-words
// square-digits
// substitution-cipher
// twitter
// vector-distance


}

#endif // #ifndef PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE
