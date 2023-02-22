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

// Bowling
struct Bowling : public BaseProblemReader<
  std::string,
  int
> {

  std::string name() const override { return "bowling"; }

};

} // end reader namespace

} // end psb namespace