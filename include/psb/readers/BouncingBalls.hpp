#pragma once

#include <utility>
#include <string>
#include <functional>

#include "../../../third-party/json/json.hpp"
#include "emp/base/vector.hpp"

#include "BaseProblemReader.hpp"

namespace psb {

namespace readers {

// Bouncing balls
struct BouncingBalls : public BaseProblemReader<
  std::tuple<double, double, int>,
  double
> {

  BouncingBalls() {
    SetInterpretJSON(
      [](const json& j) {
        return std::make_pair(
          std::make_tuple(j["input1"], j["input2"], j["input3"]),
          j["output1"]
        );
      }
    );
  }

  std::string name() const override { return "bouncing-balls"; }

};

}

}