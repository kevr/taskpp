/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "config.hpp"
#include "environment.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <fmt/format.h>
#include <fstream>
#include <gtest/gtest.h>
namespace fs = boost::filesystem;
using namespace std::string_literals;
using namespace taskpp;

class ConfigTest : public ::testing::Test
{
protected:
    fs::path tmpdir;

public:
    void SetUp(void)
    {
        tmpdir = fs::temp_directory_path() / fs::unique_path();
        fs::create_directories(tmpdir);
    }

    fs::path make_tmpdir_config(const std::vector<std::string> &v)
    {
        auto config = tmpdir / "config";
        std::ofstream ofs(config, std::ios::out);
        for (auto &e : v)
            ofs << e << "\n";
        return config;
    }

    void TearDown(void)
    {
        fs::remove_all(tmpdir);
    }
};

Config make_config(int argc, const char **argv)
{
    Config config;
    if (auto rc = config.parse_args(argc, const_cast<char **>(argv)))
        throw std::runtime_error(
            fmt::format("Config::parse_args() returned {}", rc));
    return config;
}

TEST(Config, no_args)
{
    int argc = 1;
    const char *argv[] = { "taskpp", nullptr };
    Config config;
    config.parse_args(argc, const_cast<char **>(argv));

    // Check boolean options.
    ASSERT_FALSE(config.has("help"));
    ASSERT_FALSE(config.has("config-help"));
    ASSERT_FALSE(config.get<bool>("verbose"));

    // Check string options.
    auto config_file = config_file_path();
    ASSERT_EQ(config.get<std::string>("config"), config_file);
}

TEST(Config, usage)
{
    const char *argv[] = { "taskpp" };
    auto config = make_config(1, argv);

    std::stringstream ss;
    ASSERT_EQ(config.usage(ss, 0), 0);

    auto usage = ss.str();
    ASSERT_NE(usage.find("usage: taskpp [-hxcv]"), std::string::npos);
}

TEST(Config, help)
{
    const char *argv[] = { "taskpp" };
    auto config = make_config(1, argv);

    std::stringstream ss;
    ASSERT_EQ(config.help(ss, 0), 0);

    auto help = ss.str();
    // Assert program options are listed.
    ASSERT_NE(help.find("-h [ --help ]"), std::string::npos);
    ASSERT_NE(help.find("-x [ --config-help ]"), std::string::npos);
    ASSERT_NE(help.find("-c [ --config ]"), std::string::npos);
    ASSERT_NE(help.find("-v [ --verbose ]"), std::string::npos);

    // Assert the report bugs line.
    std::string expected("Report bugs by filing an issue on " PROJECT_URL);
    ASSERT_NE(help.find(expected), std::string::npos);
}

TEST(Config, config_help)
{
    namespace po = boost::program_options;

    const char *argv[] = { "taskpp" };
    auto config = make_config(1, argv);
    config.add_config_option("test", po::value<int>()->default_value(1),
                             "test description");

    std::stringstream ss;
    ASSERT_EQ(config.config_help(ss, 0), 0);

    auto str = ss.str();
    ASSERT_NE(str.find("verbose: enable verbose logging"), std::string::npos);

    // Test that our option with a po::value<int> lists the arg default.
    ASSERT_NE(str.find("test: test description"), std::string::npos);
    ASSERT_NE(str.find("  > arg (=1)"), std::string::npos);
}

TEST(Config, copy_and_move)
{
    const char *argv[] = { "taskpp", "--help" };
    auto config = make_config(2, argv);
    ASSERT_TRUE(config.has("help"));

    // Copy construction
    Config config2(config);
    ASSERT_TRUE(config2.has("help"));

    // Move construction
    Config config3(std::move(config2));
    ASSERT_TRUE(config3.has("help"));

    // Copy assignment
    config2 = config3;
    ASSERT_TRUE(config2.has("help"));

    // Move assignment
    config3 = std::move(config2);
    ASSERT_TRUE(config3.has("help"));
}

TEST(Config, invalid_option)
{
    const char *argv[] = { "taskpp", "--invalid" };
    ASSERT_THROW(make_config(2, argv), std::runtime_error);
}

TEST(Config, missing_config)
{
    const char *argv[] = { "taskpp", "--config", "/a/b" };
    ASSERT_THROW(make_config(3, argv), std::runtime_error);
}

TEST_F(ConfigTest, invalid_config)
{
    std::vector<std::string> options({ "fake = 1" });
    auto config = make_tmpdir_config(options);
    std::string path = fs::canonical(config).string();
    const char *argv[] = { "taskpp", "--config", path.c_str() };
    ASSERT_THROW(make_config(3, argv), std::runtime_error);
}

TEST_F(ConfigTest, config)
{
    std::vector<std::string> options({ "verbose = 1" });
    auto config = make_tmpdir_config(options);
    std::string path = fs::canonical(config).string();
    const char *argv[] = { "taskpp", "--config", path.c_str() };
    ASSERT_NO_THROW(make_config(3, argv));
}
