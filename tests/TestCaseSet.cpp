#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "psb/TestCaseSet.hpp"
#include "psb/readers/TestCaseReaders.hpp"

TEST_CASE("Basement", "[psb2][TestCaseSet]") {

  using reader_t = psb::readers::Basement;

  psb::TestCaseSet<reader_t> test_case_set;

  REQUIRE(test_case_set.GetSize() == 0);

  test_case_set.LoadTests("problem-data/basement/basement.json");

  REQUIRE(test_case_set.GetSize() == 3);

  test_case_set.LoadTests("problem-data/basement/basement.json", false);

  REQUIRE(test_case_set.GetSize() == 6);

}