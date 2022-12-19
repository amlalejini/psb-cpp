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

// Grade
struct Grade : public BaseProblemReader<
  emp::array<int, 5>,
  std::string
> {

  static std::string SimplifyOutput(const std::string& output) {
    if (output == "Student has a A grade.") {
      return "A";
    } else if (output == "Student has a B grade.") {
      return "B";
    } else if (output == "Student has a C grade.") {
      return "C";
    } else if (output == "Student has a D grade.") {
      return "D";
    } else if (output == "Student has a F grade.") {
      return "F";
    } else {
      return "UNKNOWN";
    }
  }

  Grade() {
    SetInterpretJSON(
      [](const json& j) {
        std::string output = j["output1"];
        return std::make_pair<input_t, output_t>(
          input_t{
            j["input1"],
            j["input2"],
            j["input3"],
            j["input4"],
            j["input5"]
          },
          Grade::SimplifyOutput(output)
        );
      }
    );
  }

  std::string name() const override { return "grade"; }

};

} // end reader namespace

} // end psb namespace