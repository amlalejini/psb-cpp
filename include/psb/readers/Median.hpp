#pragma once

#include <utility>
#include <string>
#include <functional>

#include "json/json.hpp"

#include "emp/base/vector.hpp"
#include "emp/base/array.hpp"

#include "BaseProblemReader.hpp"

namespace psb {

namespace reader {

// Median
struct Median : public BaseProblemReader<
  emp::array<int, 3>,
  int
> {

  Median() {
    SetInterpretJSON(
      [](const json& j) {
        return std::make_pair<input_t, output_t>(
          input_t{j["input1"], j["input2"], j["input3"]},
          j["output1"]
        );
      }
    );
  }

  std::string name() const override { return "median"; }

};

} // end reader namespace

} // end psb namespace