#define CATCH_CONFIG_MAIN
#include "str_extension.cc"
#include <catch.hpp>

void print(std::string s) {
  std::cout << s << std::endl;
}

TEST_CASE("Is int", "Is int") {
  std::vector<std::string> strs_true({"1", "-1", "0", "189237e10123", "-12e00001", "-0", "+1238"});
  std::vector<std::string> strs_false({"123.123", "123e-891237", "-1.3", "-123e-2", "akjshd"});

  for (auto i = strs_true.size(); i-- > 0;)
    REQUIRE_FALSE(!StrExt::isInt(strs_true[i]));
  for (auto i = strs_false.size(); i-- > 0;)
    REQUIRE_FALSE(StrExt::isInt(strs_false[i]));
}
TEST_CASE("is float", "is float") {
  std::vector<std::string> strs_true({"1", "-1", "0", "189237e10123", "-12e00001", 
  "-0", "12.123","-123.123", "+123.", "-123.", "+1.4e52", "-12.45e-123", "1.4e-12.45"});
  for (auto i = strs_true.size(); i-- > 0;)
    REQUIRE_FALSE(!StrExt::isFloat(strs_true[i]));
}
TEST_CASE("capitalize", "capitalize") {
  std::string s = "this";
  REQUIRE(StrExt::capitalize(s) == "This");
}
TEST_CASE("check_regex_exp", "check_regex_exp") {
  REQUIRE_THROWS(StrExt::check_regex_exp("string", "[1-9)(\\d+)"));
  REQUIRE_FALSE(!StrExt::check_regex_exp("string with", "str.*"));
  REQUIRE_FALSE(StrExt::check_regex_exp("string with", "123.*"));
}
TEST_CASE("trim", "trim") {
  std::string s = "    trim me   ";
  REQUIRE(StrExt::trim(s) == "trim me");

  s = "---trim me-------";
  REQUIRE(StrExt::trim(s, "-") == "trim me");
}
TEST_CASE("split", "split") {
  std::string s = "split this string";
  std::vector<std::string> v = StrExt::split(s);

  REQUIRE(v[0] == "split");
  REQUIRE(v[1] == "this");
  REQUIRE(v[2] == "string");
}
TEST_CASE("findFullWords", "findFullWords") {}
TEST_CASE("findreplace", "findreplace") {}
TEST_CASE("findTerm", "findTerm") {}
TEST_CASE("reduce", "reduce") {}
