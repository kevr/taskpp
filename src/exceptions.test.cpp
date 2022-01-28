#include "exceptions.hpp"
#include <gtest/gtest.h>
using namespace taskpp;

TEST(exceptions, ASSERT_NOT_NULL)
{
    int *ptr = nullptr;
    ASSERT_THROW(
        {
            try {
                ASSERT_NOT_NULL(ptr);
            } catch (const ResourceError &e) {
                ASSERT_STREQ(e.what(), "ptr cannot be null");
                throw;
            }
        },
        ResourceError);
}

TEST(exceptions, ASSERT_NOT_NULL_ACTOR)
{
    int *ptr = nullptr;
    ASSERT_THROW(
        {
            try {
                ASSERT_NOT_NULL_ACTOR(ptr, "MyPointer");
            } catch (const ResourceError &e) {
                ASSERT_STREQ(e.what(), "MyPointer cannot be null");
                throw;
            }
        },
        ResourceError);
}

TEST(exceptions, ASSERT_NULL)
{
    int value;
    int *ptr = &value;
    ASSERT_THROW(
        {
            try {
                ASSERT_NULL(ptr);
            } catch (const ResourceError &e) {
                ASSERT_STREQ(e.what(), "ptr must be null");
                throw;
            }
        },
        ResourceError);
}

TEST(exceptions, ASSERT_NULL_ACTOR)
{
    int value;
    int *ptr = &value;
    ASSERT_THROW(
        {
            try {
                ASSERT_NULL_ACTOR(ptr, "MyPointer");
            } catch (const ResourceError &e) {
                ASSERT_STREQ(e.what(), "MyPointer must be null");
                throw;
            }
        },
        ResourceError);
}
