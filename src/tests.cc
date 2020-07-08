#define CATCH_CONFIG_MAIN
#include "str_extension.cc"
#include <catch.hpp>

void print(std::string s) { std::cout << s << std::endl; }

TEST_CASE("Is int", "Is int") {
  std::vector<std::string> strs_true({"1", "-1", "0", "189237e10123", "-12e00001", "-0", "+1238"});
  std::vector<std::string> strs_false({"123.123", "123e-891237", "-1.3", "-123e-2", "akjshd"});

  for (auto i = strs_true.size(); i-- > 0;)
    REQUIRE_FALSE(!StrExt::isInt(strs_true[i]));
  for (auto i = strs_false.size(); i-- > 0;)
    REQUIRE_FALSE(StrExt::isInt(strs_false[i]));
}

TEST_CASE("is float", "is float") {
  std::vector<std::string> strs_true({"1", "-1", "0", "189237e10123", "-12e00001", "-0", "12.123",
                                      "-123.123", "+123.", "-123.", "+1.4e52", "-12.45e-123",
                                      "1.4e-12.45"});
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

  s = "split-this-string";
  v = StrExt::split(s, '-');

  REQUIRE(v[0] == "split");
  REQUIRE(v[1] == "this");
  REQUIRE(v[2] == "string");
}

TEST_CASE("findFullWords", "findFullWords") {
  std::string s = "find a word inside in this, yeah does not make sense but ok";

  REQUIRE_FALSE(!StrExt::find_full_words(s, "in"));
  REQUIRE_FALSE(StrExt::find_full_words(s, "no"));
}

TEST_CASE("find_replace_first", "find_replace_first") {
  std::string s = "replace the replace word in this";
  s = StrExt::find_replace_first(s, "replace", "k");

  std::string expected = "k the replace word in this";
  REQUIRE(s == expected);
}

TEST_CASE("find_replace_all", "find_replace_all") {
  std::string s = "replace the replace replace replace word in this";
  s = StrExt::find_replace_all(s, "replace", "x");

  std::string expected = "x the x x x word in this";
  REQUIRE(s == expected);
}

TEST_CASE("findTerm", "findTerm") {
  std::string a = "check if the term AAA is in this string";

  REQUIRE_FALSE(!StrExt::find_term(a, "AAA"));
  REQUIRE_FALSE(!StrExt::find_term(a, "str"));
}

TEST_CASE("reduce", "reduce") {
  std::string a = "   there     is too    much empty space";
  std::string b = "----there-------is too----much of this----------";

  REQUIRE(StrExt::reduce(a) == "there is too much empty space");
  REQUIRE(StrExt::reduce(a, "-") == "there-is-too-much-empty-space");
  REQUIRE(StrExt::reduce(b, " ", "-") == "there is too much of this");
}

TEST_CASE("mismatch_string", "mismatch_string") {
  std::string a = "/this/is/a/path/to/something.txt";
  std::string b = "/this/is/a/path/";

  REQUIRE(StrExt::mismatch_string(a, b) == "to/something.txt");
}

TEST_CASE("vec_float_to_str", "vec_float_to_str") {
  std::vector<double> d({0.00001, 7e-5, -9123.1e5});
  std::vector<std::string> s = StrExt::vec_float_to_str(d);

  REQUIRE(s[0] == "0.000010");
  REQUIRE(s[1] == "0.000070");
  REQUIRE(s[2] == "-912310000.000000");
}

TEST_CASE("vec_str_to_float", "vec_str_to_float") {
  std::vector<std::string> s({"0.0005", "17e-8", "-89e10"});
  std::vector<double> d = StrExt::vec_str_to_float<double>(s);

  REQUIRE(d[0] == 0.0005);
  REQUIRE(d[1] == 0.00000017);
  REQUIRE(d[2] == -890000000000.0);
}

TEST_CASE("indexOf and contains", "indexOf and contains") {
  std::vector<std::string> s({"aa", "aaaaa", "aaaaaaaaaaa", "a", "arg"});

  REQUIRE(StrExt::indexOf(s, std::string("a")) == 3);
  REQUIRE(StrExt::indexOf(s, std::string("aaa")) == -1);

  REQUIRE_FALSE(!StrExt::contains(s, std::string("a")));
  REQUIRE_FALSE(StrExt::contains(s, std::string("aaa")));

  std::vector<int> x({3, 7, 4, 0, 3, 10, 10, 20, 30});

  REQUIRE(StrExt::indexOf(x, 10) == 5);
  REQUIRE(StrExt::indexOf(x, 31) == -1);

  REQUIRE_FALSE(!StrExt::contains(x, 10));
  REQUIRE_FALSE(StrExt::contains(x, 31));
}

TEST_CASE("Python-like print", "Python-like print") { StrExt::print("test with a teest"); }
