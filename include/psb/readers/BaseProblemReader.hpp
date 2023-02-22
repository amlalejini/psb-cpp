#pragma once

#include <utility>
#include <string>
#include <functional>

#include "json/json.hpp"
#include "emp/base/vector.hpp"

namespace psb {

namespace readers {

template<typename INPUT_T, typename OUTPUT_T>
struct BaseProblemReader {

  using input_t = INPUT_T;
  using output_t = OUTPUT_T;
  using json = nlohmann::json;

  using fun_interpret_json_t = std::function< std::pair<input_t,output_t>(const json&) >;

  /// Interpret JSON object into input/output pair.
  /// Base implementation naively assumes a single-input, single-output test.
  /// @NOTE: this might need to get changed to be more generic down the line...
  fun_interpret_json_t fun_interpret_json = [](const json& j) {
    return std::make_pair(j["input1"], j["output1"]);
  };

  virtual std::string name() const = 0;

  /// Interpet a single test stored as a string but following JSON.
  virtual std::pair<input_t,output_t> ReadTestJSON(const std::string& s) const {
    return ReadTestJSON(json::parse(s));
  }

  /// Interpret a single test stored as a JSON object.
  virtual std::pair<input_t,output_t> ReadTestJSON(const json& j) const {
    return fun_interpret_json(j);
  }

  virtual void SetInterpretJSON(const fun_interpret_json_t& f) {
    fun_interpret_json = f;
  }

};

}

}