#pragma once

#include <utility>
#include <string>
#include <functional>

#include "../../../third-party/json/json.hpp"
#include "emp/base/vector.hpp"

#include "BaseProblemReader.hpp"

namespace psb {

namespace readers {

// basement
struct Basement : public BaseProblemReader<
  emp::vector<int>, /* INPUT_T */
  int               /* OUTPUT_T */
> {

  std::string name() const override { return "basement"; }

};

}

}