/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "string.hpp"
#include <iostream>

namespace taskpp
{

std::vector<std::string> split(const std::string &subject,
                               const std::string &delim)
{
    std::vector<std::string> output;
    size_t last = 0, i;
    while ((i = subject.find(delim, last))) {
        output.emplace_back(subject.substr(last, i - last));
        if (i == std::string::npos)
            break;
        last = i + 1;
    }
    return output;
}

std::string join(const std::string &delim, const std::vector<std::string> &vec)
{
    std::string output;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        output.append(*it);
        if ((it + 1) != vec.end())
            output.append(delim);
    }
    return output;
}

std::string replace(std::string target, const std::string &sub,
                    const std::string &repl)
{
    size_t last = 0, i;
    while ((i = target.find(sub, last)) != std::string::npos) {
        // While we still find a substring, replace it by splitting the
        // string in half and gluing it back together with repl delimiting.
        target = target.substr(0, i) + repl + target.substr(i + sub.size());
        last = i + repl.size();
    }
    return target;
}

std::string strip(const std::string &target, const std::string &substr)
{
    return replace(target, substr, "");
}

}; // namespace taskpp
