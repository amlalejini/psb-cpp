#pragma once

#include <utility>
#include <string>
#include <functional>

#include "../../../third-party/json/json.hpp"
#include "emp/tools/string_utils.hpp"

#include "emp/base/vector.hpp"
#include "emp/base/array.hpp"

#include "BaseProblemReader.hpp"

namespace psb {

namespace readers {

// ForLoopIndex
struct ForLoopIndex : public BaseProblemReader<
  emp::array<int, 3>,
  emp::vector<int>
> {

  ForLoopIndex() {
    SetInterpretJSON(
      [](const json& j) {
        emp::array<int, 3> input = {
          j["input1"],
          j["input2"],
          j["input3"]
        };

        emp::vector<int> output;
        auto output_str  = emp::slice(
          (std::string)j["output1"],
          '\n'
        );
        for (size_t i = 0; i < output_str.size(); ++i) {
          output.emplace_back(emp::from_string<int>(output_str[i]));
        }
        return std::make_pair(input, output);
      }
    );
  }

  std::string name() const override { return "for-loop-index"; }

};

}

}