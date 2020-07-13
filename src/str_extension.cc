/********************************************************************************
MIT License

Copyright (c) 2020 Honnef

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/
#ifndef STREXT_H
#define STREXT_H

#include <iostream>
#include <regex>
#include <string>
#include <vector>

/*
 * Static class StrExt that extends the operations over strings and vector.
 */
class StrExt {
private:
  // regex for float
  inline static std::regex r_float = std::regex(
      "[\\+-]?(((\\d*\\.\\d+)|(\\d+(\\.(0*))?))(e[\\+-]?((\\d*\\.\\d+)|(\\d+(\\.(0*))?)))?)",
      std::regex::icase);

  // regex for integers
  inline static std::regex r_int =
      std::regex("[\\+-]?((\\d+(\\.(0*))?)(e[\\+]?\\d+)?)", std::regex::icase);

  /*
   * Aux function for split
   */
  template <typename Out> static void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
      *(result++) = trim(item);
  }
  /*
   * Cast std::string `val` to float
   */
  template <typename f> static f str_to_float(const std::string &val) {
    return std::atof(val.c_str());
  }
  /*
   * Cast float `val` to std::string.
   */
  template <typename f> static std::string float_to_str(const f &val) {
    return std::to_string(val);
  }
  static void print() { std::cout << std::endl; }

public:
  /*
   * Checks if `val` is a integer.
   */
  static bool isInt(const std::string &val) { return std::regex_match(val, r_int); }
  /*
   * Checks if `val` is any kind of float.
   */
  static bool isFloat(const std::string &val) { return std::regex_match(val, r_float); }
  /*
   * Capitalize the first char of `str`.
   */
  static std::string capitalize(const std::string &str) {
    std::string a = str;
    a[0] = std::toupper(a[0]);
    return a;
  }
  /*
   * Creates a regex expression using the string `exp` and checks if there is a match in `str`.
   * If it throws an exception (problably because your `exp` was wrong),
   * put the function call in a try/catch and do something like:
   * `catch (std::exception &e) {print(e.what())}`
   */
  static bool check_regex_exp(const std::string &str, const std::string &exp) {
    try {
      return std::regex_match(str, std::regex(exp, std::regex::icase));
    } catch (std::regex_error &e) {
      throw e;
    }
  }
  /*
   * Returns the "trimmed" `str` (can be another char besides `whitespace`).
   * `E.g.: "    trim me   " -> "trim me".`
   */
  static std::string trim(const std::string &str, const std::string &whitespace = " ") {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
      return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
  }
  /*
   * Returns a vector with the split string `s` spliting at `delim` char.
   */
  static std::vector<std::string> split(const std::string &s, char delim = ' ') {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
  }
  /*
   * Checks if there is a full `word` in `s`.
   */
  static bool find_full_words(const std::string &s, const std::string &word) {
    std::vector<std::string> spl = split(s, ' ');

    return std::find(spl.begin(), spl.end(), word) != spl.end();
  }
  /*
   * Replace the `first` occurrence of string `toReplace` with `replaceWith` in a copy of `s`.
   * Returns the replaced string, if not replaced it'll return the copy of `s`.
   */
  static std::string find_replace_first(const std::string &s, const std::string &toReplace,
                                        const std::string &replaceWith) {
    std::string str(s);
    std::size_t index = str.find(toReplace);
    if (index != str.npos)
      str.replace(index, toReplace.length(), replaceWith);

    return str;
  }
  /*
   * Replace `all` occurrence of string `toReplace` with `replaceWith` in a copy of `s`. Returns the
   * replaced string, if not replaced it'll return the copy of `s`.
   */
  static std::string find_replace_all(const std::string &s, const std::string &toReplace,
                                      const std::string &replaceWith) {
    std::string str(s);
    std::size_t index = str.find(toReplace);

    while (index != str.npos) {
      str.replace(index, toReplace.length(), replaceWith);
      index = str.find(toReplace, index);
    }

    return str;
  }
  /*
   * Checks if the `term` is in `s`.
   */
  static bool find_term(const std::string &s, const std::string &term) {
    std::size_t index = s.find(term);
    return (index != s.npos);
  }
  /*
   * Removes the `whitespace` (or another char) from `str` and fill the gap with `fill`.
   * `E.g.: "   there     is too    much empty space" -> "there-is-too-much-empty-space"
   * or "there is too much empty space"`.
   */
  static std::string reduce(const std::string &str, const std::string &fill = " ",
                            const std::string &whitespace = " ") {
    // trim first
    std::string result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos) {
      const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
      const auto range = endSpace - beginSpace;

      result.replace(beginSpace, range, fill);

      const auto newStart = beginSpace + fill.length();
      beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
  }
  /*
   * Removes the begin of `a` that matches `b`. Useful for handling paths.
   * `E.g.: "/this/is/a/path/to/something.txt" - "/this/is/a/path/" = "to/something.txt"`
   */
  static std::string mismatch_string(std::string const &a, std::string const &b) {

    std::pair<std::string::const_iterator, std::string::const_iterator> mismatch_pair;

    std::string::const_iterator longBegin, longEnd, shortBegin;

    if (a.length() >= b.length()) {
      longBegin = a.begin();
      longEnd = a.end();
      shortBegin = b.begin();
    } else {
      longBegin = b.begin();
      longEnd = b.end();
      shortBegin = a.begin();
    }

    mismatch_pair = mismatch(longBegin, longEnd, shortBegin);
    return std::string(mismatch_pair.first, longEnd);
  }

  /*
   * Transforms a float (or double, or whatever float it is) vector `float_v` to a std::string
   * vector.
   */
  template <typename f>
  static std::vector<std::string> vec_float_to_str(const std::vector<f> &float_v) {
    std::vector<std::string> strVec(float_v.size());

    std::transform(float_v.begin(), float_v.end(), strVec.begin(), float_to_str<f>);

    return strVec;
  }
  /*
   * Transforms a std::string vector `str_v` to a float (or double, or whatever float it is).
   * You need to specify the return type, `e.g.: vec_str_to_float<double>(string_vector)`
   */
  template <typename f>
  static std::vector<f> vec_str_to_float(const std::vector<std::string> &str_v) {
    std::vector<f> float_v(str_v.size());

    std::transform(str_v.begin(), str_v.end(), float_v.begin(), str_to_float<f>);

    return float_v;
  }
  /*
   * Returns the index of first occurence of `val` inside of `vec`.
   * If not found, returns -1.
   */
  template <typename T> static int indexOf(const std::vector<T> &vec, const T &val) {
    auto it = std::find(vec.begin(), vec.end(), val);

    if (it == vec.end())
      return -1;

    return std::distance(vec.begin(), it);
  }
  /*
   * Uses `indexOf` to check if `val` is in `vec`.
   */
  template <typename T> static bool contains(const std::vector<T> &vec, const T &val) {
    return indexOf(vec, val) != -1;
  }
  /*
   * Python-like print.
   */
  template <typename T, typename... TAIL> static void print(const T &t, TAIL... tail) {
    std::cout << t << " ";
    print(tail...);
  }
};

#endif