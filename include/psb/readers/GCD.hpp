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

// GCD (greatest common divisor)
struct GCD : public BaseProblemReader<
  int,
  int
> {

  std::string name() const override { return "gcd"; }

};

} // end reader namespace

} // end psb namespace