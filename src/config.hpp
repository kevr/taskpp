/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <memory>

#define PROJECT_NAME "taskpp"
#define PROJECT_URL "https://gitlab.com/kevr2d2/taskpp"

namespace taskpp
{

class Config
{
private:
    // Program name
    std::string prog;

    // Configuration file path and error state
    std::string config_file;
    bool config_error = false;

    // Option descriptions.
    using options_description = boost::program_options::options_description;
    std::unique_ptr<options_description> desc;
    std::unique_ptr<options_description> config;

    // Storage used for parse results
    boost::program_options::variables_map vm;

private:
    //! Parse the config
    Config &parse(int argc, char **argv);

    //! Add internally implemented options to internal descriptions
    void add_options(void);

public:
    //! Construct a Config
    Config(const char *progname);

    //! Copy-construct a Config
    Config(const Config &other);

    //! Move-construct a Config
    Config(Config &&other);

    //! Copy assignment
    Config &operator=(const Config &other);

    //! Move assignment
    Config &operator=(Config &&other);

    //! Add a config option externally
    template <typename... Args>
    Config &add_config_option(Args &&...args)
    {
        config->add_options()(args...);
        return *this;
    }

    //! Parse program arguments
    int parse_args(int argc, char **argv);

    int usage(std::ostream &os, int return_code) const;

    //! Print help text to os
    int help(std::ostream &os, int return_code) const;

    //! Print config help text to os
    int config_help(std::ostream &os, int return_code) const;

    //! Check if this config was given an option
    bool has(const std::string &option) const;

    //! Get a config option value
    template <typename T>
    T get(const std::string &option)
    {
        return vm[option].as<T>();
    }

    //! Return config file path
    const std::string &path(void) const;
};

}; // namespace taskpp

#endif /* CONFIG_HPP */
