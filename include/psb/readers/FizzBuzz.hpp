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

// FizzBuzz
struct FizzBuzz : public BaseProblemReader<
  int,
  std::string
> {

  std::string name() const override { return "fizz-buzz"; }

};

} // end reader namespace

} // end psb namespace