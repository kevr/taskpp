/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef STRING_HPP
#define STRING_HPP

#include <boost/any.hpp>
#include <string>
#include <type_traits>
#include <vector>

namespace taskpp
{

/**
 * @brief Split a subject string into a vector based on delim
 *
 * @param subject String to split
 * @param delim Delimiter to split on
 * @return Vector containing split parts
 **/
std::vector<std::string> split(const std::string &subject,
                               const std::string &delim);

/**
 * @brief Join a vector into a string with delim
 *
 * @param delim Delimiter used between each element
 * @param vec Vector of strings to be joined
 * @return Joined string
 **/
std::string join(const std::string &delim,
                 const std::vector<std::string> &vec);

/**
 * @brief Replace a substring in target with repl
 *
 * @param target Original string
 * @param sub Substring to replace
 * @param repl Replacement to substitute
 * @return Modified target
 **/
std::string replace(std::string target, const std::string &sub,
                    const std::string &repl);

}; // namespace taskpp

#endif /* STRING_HPP */
