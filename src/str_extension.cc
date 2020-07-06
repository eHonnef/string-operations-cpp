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

#include <regex>
#include <string>
#include <vector>

/*
* Static class StrExt that extends the operations over strings.
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

public:
  /*
   * Checks if val is a integer.
   */
  static bool isInt(const std::string &val) { return std::regex_match(val, r_int); }
  /*
   * Checks if val is any kind of float.
   */
  static bool isFloat(const std::string &val) { return std::regex_match(val, r_float); }
  /*
   * Capitalize the first char of str.
   */
  static std::string capitalize(const std::string &str) {
    std::string a = str;
    a[0] = std::toupper(a[0]);
    return a;
  }
  /*
   * Creates a regex expression using the string exp and checks if there is a match in str.
   * If it throws an exception (problably because your exp was wrong),
   * put the function call in a try/catch and do something like:
   * catch (std::exception &e) {print(e.what())}
   */
  static bool check_regex_exp(const std::string &str, const std::string &exp) {
    try {
      return std::regex_match(str, std::regex(exp, std::regex::icase));
    } catch (std::regex_error &e) {
      throw e;
    }
  }
  /*
   * Returns the "trimmed" string (can be another char besides whitespace).
   * E.g.: "    trim me   " -> "trim me".
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
   * Returns a vector with the split string.
   */
  static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
  }
  /*
   * Checks if there is a full word in s.
   */
  static bool find_full_words(const std::string &s, const std::string &word) {
    std::vector<std::string> spl = split(s, ' ');

    return std::find(spl.begin(), spl.end(), word) != spl.end();
  }
  /*
   * Replace a string toReplace with replaceWith in a copy of s. Returns the replaced string, if not
   * replaced it'll return the copy of s.
   */
  static std::string find_replace(const std::string &s, const std::string &toReplace,
                                 const std::string &replaceWith) {
    std::string str(s);
    std::size_t index = str.find(toReplace);
    if (index != str.npos)
      str.replace(index, toReplace.length(), replaceWith);

    return str;
  }
  /*
   * Checks if the term is in s.
   */
  bool find_term(const std::string &s, const std::string &term) {
    std::size_t index = s.find(term);
    return (index != s.npos);
  }
  /*
   * Removes the whitespace (or another char) from str and fill the gap with fill.
   * E.g.: "   there     is too    much empty space" -> "there-is-too-much-empty-space"
   * or "there is too much empty space".
   */
  // static std::string reduce(const std::string &str, const std::string &fill,
  //                           const std::string &whitespace) {
  //   // trim first
  //   std::string result = trim(str, whitespace);

  //   // replace sub ranges
  //   auto beginSpace = result.find_first_of(whitespace);
  //   while (beginSpace != (int)std::string::npos) {
  //     const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
  //     const auto range = endSpace - beginSpace;

  //     result.replace(beginSpace, range, fill);

  //     const auto newStart = beginSpace + fill.length();
  //     beginSpace = result.find_first_of(whitespace, newStart);
  //   }

  //   return result;
  // }
};

#endif