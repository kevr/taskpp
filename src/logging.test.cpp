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
        : logger("test", out, err)
    {
    }

    void SetUp(void)
    {
        logger.set_level(DEBUG);
    }

    void TearDown(void)
    {
        logger.set_level(INFO);
    }
};

TEST(Logging, constructors)
{
    {
        std::stringstream ss;
        Logger logger("test", ss);
        logger.info(0, "Test");
        ASSERT_EQ(ss.str(), "[INFO] test#L0: Test\n");
    }

    {
        std::stringstream ss;
        Logger logger("test", ss);
        logger.set_level(WARN);
        log_debug(0, "Test");
        logger.set_level(INFO);
        ASSERT_EQ(ss.str(), std::string());
    }
}

TEST_F(LoggingTest, configure_streams)
{
    std::stringstream out, err;

    logger.output_stream(out);
    logger.info(0, "Test");
    ASSERT_EQ(out.str(), "[INFO] test#L0: Test\n");

    logger.error_stream(err);
    logger.error(1, "Test");
    ASSERT_EQ(err.str(), "[ERROR] test#L1: Test\n");
}

TEST_F(LoggingTest, move_constructor_and_assignment)
{
    Logger moved(std::move(logger));
    logger = std::move(moved);
    logger.info(0, "Test");
    ASSERT_EQ(out.str(), "[INFO] test#L0: Test\n");
}

TEST_F(LoggingTest, set_level)
{
    logger.set_level(INFO);
    log_warn("Test");
    ASSERT_EQ(err.str(), std::string());
}

TEST_F(LoggingTest, error)
{
    logger.error(0, "Test");
    ASSERT_EQ(err.str(), "[ERROR] test#L0: Test\n");
}

TEST_F(LoggingTest, info)
{
    logger.info(1, "Test");
    ASSERT_EQ(out.str(), "[INFO] test#L1: Test\n");
}

TEST_F(LoggingTest, warn)
{
    logger.warn(2, "Test");
    ASSERT_EQ(err.str(), "[WARN] test#L2: Test\n");
}

TEST_F(LoggingTest, debug)
{
    logger.debug(3, "Test");
    ASSERT_EQ(out.str(), "[DEBUG] test#L3: Test\n");
}

TEST(logging, get_filename)
{
    std::string expected("logging.test.cpp");
    ASSERT_EQ(taskpp::get_filename(__FILE__), expected);
}
