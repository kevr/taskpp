/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "logging.hpp"
#include <bitset>
#include <gtest/gtest.h>
using namespace taskpp;

class LoggingTest : public ::testing::Test
{
protected:
    std::stringstream out, err;
    Logger logger;

public:
    LoggingTest(void)
        : logger("test", DEBUG, out, err)
    {
    }
};

TEST(Logging, constructors)
{
    {
        std::stringstream ss;
        Logger logger("test", INFO, ss);
        logger.info("Test");
        ASSERT_EQ(ss.str(), "[INFO] test: Test\n");
    }

    {
        std::stringstream ss;
        Logger logger("test", WARN, ss);
        logger.debug("Test");
        ASSERT_EQ(ss.str(), std::string());
    }
}

TEST_F(LoggingTest, configure_streams)
{
    std::stringstream out, err;

    logger.output_stream(out);
    logger.info("Test");
    ASSERT_EQ(out.str(), "[INFO] test: Test\n");

    logger.error_stream(err);
    logger.error("Test");
    ASSERT_EQ(err.str(), "[ERROR] test: Test\n");
}

TEST_F(LoggingTest, move_constructor_and_assignment)
{
    Logger moved(std::move(logger));
    logger = std::move(moved);
    logger.info("Test");
    ASSERT_EQ(out.str(), "[INFO] test: Test\n");
}

TEST_F(LoggingTest, set_level)
{
    logger.set_level(INFO);
    logger.warn("Test");
    ASSERT_EQ(err.str(), std::string());
}

TEST_F(LoggingTest, error)
{
    logger.error("Test");
    ASSERT_EQ(err.str(), "[ERROR] test: Test\n");
}

TEST_F(LoggingTest, info)
{
    logger.info("Test");
    ASSERT_EQ(out.str(), "[INFO] test: Test\n");
}

TEST_F(LoggingTest, warn)
{
    logger.warn("Test");
    ASSERT_EQ(err.str(), "[WARN] test: Test\n");
}

TEST_F(LoggingTest, debug)
{
    logger.debug("Test");
    ASSERT_EQ(out.str(), "[DEBUG] test: Test\n");
}

TEST(logging, get_filename)
{
    std::string expected("logging.test.cpp");
    ASSERT_EQ(taskpp::get_filename(__FILE__), expected);
}
