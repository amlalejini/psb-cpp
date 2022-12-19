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

// SnowDay
struct SnowDay : public BaseProblemReader<
  std::tuple<int, double, double, double>,
  double
> {

  //{"input1":16,"input2":4.384363116353098,"input3":5.697558146930427,"input4":0.2740347412429017,"output1":20.693719263020586}
  SnowDay() {
    SetInterpretJSON(
        [](const json& j) {
          return std::make_pair(
            input_t{j["input1"], j["input2"], j["input3"], j["input4"]},
            j["output1"]
          );
        }
    );
  }

  std::string name() const override { return "snow-day"; }

};

} // end reader namespace

} // end psb namespace