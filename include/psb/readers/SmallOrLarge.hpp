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

// Small or large
struct SmallOrLarge : public BaseProblemReader<
  int,
  std::string
> {

  std::string name() const override { return "small-or-large"; }

};

} // end reader namespace

} // end psb namespace