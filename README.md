# String operations

Library in C++ that implements operations over the STL string.

## Functions and files

[[File]](./src/str_extension.cc)

The main file that contains all functions.

[[Test file]](./src/test.cc)

File that contains the test functions to check if everything is working.

### Table of content

- [split](#split)
- [str_to_float](#str_to_float)
- [float_to_str](#float_to_str)
- [isInt](#isint)
- [isFloat](#isfloat)
- [capitalize](#capitalize)
- [check_regex_exp](#check_regex_exp)
- [trim](#trim)
- [split](#split-1)
- [find_full_words](#find_full_words)
- [find_replace_first](#find_replace_first)
- [find_replace_all](#find_replace_all)
- [find_term](#find_term)
- [reduce](#reduce)
- [mismatch_string](#mismatch_string)
- [vec_float_to_str](#vec_float_to_str)
- [vec_str_to_float](#vec_str_to_float)
- [indexOf](#indexof)
- [contains](#contains)
- [print](#print)

### split
---

[[Source]](./src/str_extension.cc#L49)

Aux function for split

Templates:

- Out, typename

`Return type`: void  
`Access`: private

Arguments:

- `Type`: std::string, `Name`: s
- `Type`: char, `Name`: delim
- `Type`: Out, `Name`: result

### str_to_float
---

[[Source]](./src/str_extension.cc#L58)

Cast std::string `val` to float

Templates:

- f, typename

`Return type`: f  
`Access`: private

Arguments:

- `Type`: std::string, `Name`: val

### float_to_str
---

[[Source]](./src/str_extension.cc#L64)

Cast float `val` to std::string.

Templates:

- f, typename

`Return type`: std::string  
`Access`: private

Arguments:

- `Type`: f, `Name`: val

### isInt
---

[[Source]](./src/str_extension.cc#L73)

Checks if `val` is a integer.

`Return type`: bool  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: val

### isFloat
---

[[Source]](./src/str_extension.cc#L77)

Checks if `val` is any kind of float.

`Return type`: bool  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: val

### capitalize
---

[[Source]](./src/str_extension.cc#L81)

Capitalize the first char of `str`.

`Return type`: std::string  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: str

### check_regex_exp
---

[[Source]](./src/str_extension.cc#L92)

Creates a regex expression using the string `exp` and checks if there is a match in `str`. If it throws an exception (problably because your `exp` was wrong), put the function call in a try/catch and do something like: `catch (std::exception &e) {print(e.what())}`

`Return type`: bool  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: str
- `Type`: std::string, `Name`: exp

### trim
---

[[Source]](./src/str_extension.cc#L103)

Returns the "trimmed" `str` (can be another char besides `whitespace`). `E.g.: "    trim me   " -> "trim me".`

`Return type`: std::string  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: str
- `Type`: std::string, `Name`: whitespace `Default value`: " "

### split
---

[[Source]](./src/str_extension.cc#L116)

Returns a vector with the split string `s` spliting at `delim` char.

`Return type`: std::vector<std::string>  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: s
- `Type`: char, `Name`: delim `Default value`: ' '

### find_full_words
---

[[Source]](./src/str_extension.cc#L124)

Checks if there is a full `word` in `s`.

`Return type`: bool  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: s
- `Type`: std::string, `Name`: word

### find_replace_first
---

[[Source]](./src/str_extension.cc#L133)

Replace the `first` occurrence of string `toReplace` with `replaceWith` in a copy of `s`. Returns the replaced string, if not replaced it'll return the copy of `s`.

`Return type`: std::string  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: s
- `Type`: std::string, `Name`: toReplace
- `Type`: std::string, `Name`: replaceWith

### find_replace_all
---

[[Source]](./src/str_extension.cc#L146)

Replace `all` occurrence of string `toReplace` with `replaceWith` in a copy of `s`. Returns the replaced string, if not replaced it'll return the copy of `s`.

`Return type`: std::string  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: s
- `Type`: std::string, `Name`: toReplace
- `Type`: std::string, `Name`: replaceWith

### find_term
---

[[Source]](./src/str_extension.cc#L161)

Checks if the `term` is in `s`.

`Return type`: bool  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: s
- `Type`: std::string, `Name`: term

### reduce
---

[[Source]](./src/str_extension.cc#L170)

Removes the `whitespace` (or another char) from `str` and fill the gap with `fill`. `E.g.: "   there     is too    much empty space" -> "there-is-too-much-empty-space" or "there is too much empty space"`.

`Return type`: std::string  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: str
- `Type`: std::string, `Name`: fill `Default value`: " "
- `Type`: std::string, `Name`: whitespace `Default value`: " "

### mismatch_string
---

[[Source]](./src/str_extension.cc#L193)

Removes the begin of `a` that matches `b`. Useful for handling paths. `E.g.: "/this/is/a/path/to/something.txt" - "/this/is/a/path/" = "to/something.txt"`

`Return type`: std::string  
`Access`: public

Arguments:

- `Type`: std::string, `Name`: a
- `Type`: std::string, `Name`: b

### vec_float_to_str
---

[[Source]](./src/str_extension.cc#L218)

Transforms a float (or double, or whatever float it is) vector `float_v` to a std::string vector.

Templates:

- f, typename

`Return type`: std::vector<std::string>  
`Access`: public

Arguments:

- `Type`: std::vector<f>, `Name`: float_v

### vec_str_to_float
---

[[Source]](./src/str_extension.cc#L230)

Transforms a std::string vector `str_v` to a float (or double, or whatever float it is). You need to specify the return type, `e.g.: vec_str_to_float<double>(string_vector)`

Templates:

- f, typename

`Return type`: std::vector<f>  
`Access`: public

Arguments:

- `Type`: std::vector<std::string>, `Name`: str_v

### indexOf
---

[[Source]](./src/str_extension.cc#L241)

Returns the index of first occurence of `val` inside of `vec`. If not found, returns -1.

Templates:

- T, typename

`Return type`: int  
`Access`: public

Arguments:

- `Type`: std::vector<T>, `Name`: vec
- `Type`: T, `Name`: val

### contains
---

[[Source]](./src/str_extension.cc#L252)

Uses `indexOf` to check if `val` is in `vec`.

Templates:

- T, typename

`Return type`: bool  
`Access`: public

Arguments:

- `Type`: std::vector<T>, `Name`: vec
- `Type`: T, `Name`: val

### print
---

[[Source]](./src/str_extension.cc#L258)

Python-like print.

Templates:

- T, typename
- TAIL, typename

`Return type`: void  
`Access`: public

Arguments:

- `Type`: T, `Name`: t
- `Type`: TAIL..., `Name`: tail
