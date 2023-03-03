/**
*   @note This class is inspired by a version written by Emily Dolson, which can be found here: https://github.com/emilydolson/map-elites-gp/blob/master/source/TestcaseSet.h
*/

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "../../third-party/json/json.hpp"
#include "emp/base/vector.hpp"

#include "readers/BaseProblemReader.hpp"

namespace psb {

class BaseTestCaseSet {
protected:
  BaseTestCaseSet() = default;
public:
  virtual ~BaseTestCaseSet() = default;
  virtual void Clear() = 0;
  virtual size_t GetSize() const = 0;
  virtual std::string GetProblemName() const = 0;
  virtual void LoadTests(const std::string& filename, bool overwrite) = 0;

};

/// @brief
/// @tparam TESTCASE_READER_T Should be derived from psb::reader::BaseProblemReader
template <typename TESTCASE_READER_T>
class TestCaseSet : public BaseTestCaseSet {
public:
  using reader_t = TESTCASE_READER_T;
  using input_t = typename reader_t::input_t;
  using output_t = typename reader_t::output_t;
  using test_case_t = std::pair< input_t, output_t >;

protected:
  emp::vector<test_case_t> test_cases;  ///< Maintains vector of testcases loaded into this test case set.
  reader_t test_case_reader;

public:

  TestCaseSet() { ; };
  TestCaseSet(const std::string& filename) {
    LoadTests(filename);
  }

  size_t GetSize() const override {
    return test_cases.size();
  }

  std::string GetProblemName() const override {
    return test_case_reader.name();
  }

  const input_t& GetInput(size_t id) const {
    return test_cases[id];
  }

  const output_t& GetOutput(size_t id) const {
    return test_cases[id];
  }

  const emp::vector<test_case_t>& GetTests() const {
    return test_cases;
  }

  void Clear() override {
    test_cases.clear();
  }

  void LoadTests(const std::string& filename, bool overwrite=true) {
    // If overwrite tests, clear old tests.
    if (overwrite) {
      Clear();
    }
    // Load test cases from file.
    std::ifstream data_ifstream(filename);
    nlohmann::json data_json;
    std::string line;
    while (std::getline(data_ifstream, line)) {
      test_cases.emplace_back(test_case_reader.ReadTestJSON(line));
    }
    data_ifstream.close();
  }

  void AddTest(const test_case_t& test) {
    test_cases.emplace_back(test);
  }

};

} // End psb namespace