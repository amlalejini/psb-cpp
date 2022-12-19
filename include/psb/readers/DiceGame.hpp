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

// Dice game
struct DiceGame : BaseProblemReader<
  emp::array<int, 2>,
  double
> {

  DiceGame() {
    SetInterpretJSON(
      [](const json& j) {
        return std::make_pair(
          emp::array<int, 2>{
            j["input1"],
            j["input2"]
          },
          j["output1"]
        );
      }
    );
  }

  std::string name() const override { return "dice-game"; }

};

} // end reader namespace

} // end psb namespace