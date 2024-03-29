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

// CamelCase problem
struct CamelCase : public BaseProblemReader<
  std::string,
  std::string
> {

  std::string name() const override { return "camel-case"; }

};

} // end reader namespace

} // end psb namespace