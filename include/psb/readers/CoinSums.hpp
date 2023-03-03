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

// Coin sums
struct CoinSums : public BaseProblemReader<
  int,
  emp::array<int, 4>
> {

  CoinSums() {
    SetInterpretJSON(
      [](const json& j) {
        return std::make_pair(
          j["input1"],
          emp::array<int, 4>{
            j["output1"],
            j["output2"],
            j["output3"],
            j["output4"]
          }
        );
      }
    );
  }

  std::string name() const override { return "coin-sums"; }

};

} // end reader namespace

} // end psb namespace