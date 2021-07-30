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

  using fun_interpret_json_t = std::function< std::pair<input_t,output_t>(const nlohmann::json &) >;

  /// Interpret JSON object into input/output pair.
  /// Base implementation naively assumes a single-input, single-output test.
  fun_interpret_json_t fun_interpret_json =
    [](const nlohmann::json & j) {
      // return {j["input1"], j["output1"]};
      return std::make_pair(j["input1"], j["output1"]);
    };

  virtual std::string name() const = 0;
  virtual std::pair<input_t,output_t> ReadTestJSON(const std::string & s) const = 0;
  virtual std::pair<input_t,output_t> ReadTestJSON(const json & j) const = 0;

  void SetInterpretJSON(const fun_interpret_json_t & interpret_fun) {
    fun_interpret_json = interpret_fun;
  }

};

struct Basement :
  ProblemBase<
    /*INPUT_T=*/emp::vector<int>,
    /*OUTPUT_T=*/int
  >
{

  /// Interpet a single test stored as a string but following JSON.
  std::pair<input_t,output_t> ReadTestJSON(const std::string & test_json_str) const override {
      return ReadTestJSON(json::parse(test_json_str));
  }

  /// Interpret a single test stored as a JSON object.
  std::pair<input_t,output_t> ReadTestJSON(const json & test_json) const override {
    return fun_interpret_json(test_json);
  }

  std::string name() const override { return "Basement"; }

};



}

#endif // #ifndef PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE
