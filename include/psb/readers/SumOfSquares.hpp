#pragma once

#include <utility>
#include <string>
#include <functional>

#include "json/json.hpp"

#include "emp/base/vector.hpp"
#include "emp/base/array.hpp"

#include "BaseProblemReader.hpp"

namespace psb {

namespace readers {

// Sum of squares
struct SumOfSquares : public BaseProblemReader<
  int,
  int
> {

  std::string name() const override { return "sum-of-squares"; }

};

} // end reader namespace

} // end psb namespace