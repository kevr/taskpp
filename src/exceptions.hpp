/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <boost/exception/all.hpp>
#include <boost/stacktrace.hpp>
#include <stdexcept>

namespace taskpp
{

class ResourceError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

typedef boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace>
    traced;

template <class E>
void throw_with_trace(const E &e)
{
    throw boost::enable_error_info(e)
        << traced(boost::stacktrace::stacktrace());
}

}; // namespace taskpp

#define ASSERT_NOT_NULL(x)                                                    \
    if (x == nullptr)                                                         \
    throw ResourceError(#x " cannot be null")

#define ASSERT_NOT_NULL_ACTOR(x, actor)                                       \
    if (x == nullptr)                                                         \
    throw ResourceError(actor " cannot be null")

#define ASSERT_NULL(x)                                                        \
    if (x != nullptr)                                                         \
    throw ResourceError(#x " must be null")

#define ASSERT_NULL_ACTOR(x, actor)                                           \
    if (x != nullptr)                                                         \
    throw ResourceError(actor " must be null")

#endif /* EXCEPTIONS_HPP */
