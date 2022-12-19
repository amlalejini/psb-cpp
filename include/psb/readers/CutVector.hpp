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

// CutVector problem
struct CutVector : public BaseProblemReader<
  emp::vector<int>,
  emp::array<emp::vector<int>, 2>
> {

  CutVector() {
    SetInterpretJSON(
      [](const json& j) {
        return std::make_pair(
          j["input1"],
          emp::array<emp::vector<int>, 2>{j["output1"], j["output2"]}
        );
      }
    );
  }

  std::string name() const override { return "cut-vector"; }

};

} // end reader namespace

} // end psb namespace