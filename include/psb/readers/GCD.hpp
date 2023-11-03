#pragma once

#include <utility>
#include <string>
#include <functional>

#include "../../../third-party/json/json.hpp"

#include "emp/base/vector.hpp"
#include "emp/base/array.hpp"

#include "BaseProblemReader.hpp"

namespace psb {

namespace readers {

// GCD (greatest common divisor)
struct GCD : public BaseProblemReader<
  emp::array<int, 2>,
  int
> {

  GCD() {
    SetInterpretJSON(
      [](const json& j) {
        return std::make_pair<input_t, output_t>(
          input_t{j["input1"], j["input2"]},
          j["output1"]
        );
      }
    );
  }

  std::string name() const override { return "gcd"; }

};

} // end reader namespace

} // end psb namespace