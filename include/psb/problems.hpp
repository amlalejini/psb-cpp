#pragma once
#ifndef PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE
#define PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE

#include "emp/base/vector.hpp" // Q: best way to handle library import to play friendly with other projects using custom versions of empirical?

namespace psb {

template<typename INPUT_T, typename OUTPUT_T>
struct ProblemBase {

  using input_t = INPUT_T;
  using output_t = OUTPUT_T;



  virtual std::string name() const = 0;

};

struct Basement : ProblemBase<emp::vector<int>, int> {



  std::string name() const override { return "Basement"; }

};



}

#endif // #ifndef PSB_PROBLEMS_PROBLEMS_HPP_INCLUDE
