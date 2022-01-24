/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "config.hpp"
#include "environment.hpp"
#include "logging.hpp"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <map>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
namespace po = boost::program_options;
using namespace taskpp;

static const std::string DEFAULT_CONFIG = config_file_path();
static const size_t HELP_OPTION_WIDTH = 32;

Config::Config(const char *progname)
    : prog(progname)
    , desc(std::make_unique<po::options_description>("Program options"))
    , config(std::make_unique<po::options_description>("Configuration"))
{
    add_options();
}

Config::Config(const Config &other)
    : Config(other.prog.c_str())
{
    config_file = other.config_file;
    config_error = other.config_error;
    vm = other.vm;
}

Config::Config(Config &&other)
    : prog(std::move(other.prog))
    , config_file(std::move(other.config_file))
    , config_error(other.config_error)
    , desc(std::move(other.desc))
    , config(std::move(other.config))
    , vm(std::move(other.vm))
{
}

Config &Config::operator=(const Config &other)
{
    prog = other.prog;
    config_file = other.config_file;
    config_error = other.config_error;
    desc = std::make_unique<po::options_description>("Program options");
    config = std::make_unique<po::options_description>("Configuration");
    add_options();
    vm = other.vm;
    return *this;
}

Config &Config::operator=(Config &&other)
{
    prog = std::move(other.prog);
    config_file = std::move(other.config_file);
    config_error = other.config_error;
    desc = std::move(other.desc);
    config = std::move(other.config);
    vm = std::move(other.vm);
    return *this;
}

Config &Config::parse(int argc, char **argv)
{
    // Merged options for the command line.
    po::options_description cmdline;
    cmdline.add(*desc).add(*config);

    // Parse command line options.
    po::store(po::parse_command_line(argc, argv, cmdline), vm);
    po::notify(vm);

    // Get command line's config argument, defaulted to `config_file_path`.
    config_file = get<std::string>("config");
    auto exists = access(config_file.c_str(), F_OK) != -1;
    if (exists) {
        // If the config file was found, parse it.
        try {
            po::store(po::parse_config_file(config_file.c_str(), *config), vm);
        } catch (const po::unknown_option &e) {
            // If the config throws an unknown option, flip config_error on
            // and continue to throw.
            config_error = true;
            throw;
        }
        po::notify(vm);
    } else if (config_file != DEFAULT_CONFIG) {
        // In this case, a custom --config was passed, but we were
        // unable to find it.
        throw std::runtime_error(
            fmt::format("unable to read config '{}'", config_file));
    }

    return *this;
}

void Config::add_options(void)
{
    desc->add_options()("help,h", "print help message")(
        "config-help,x", "print config help text")(
        "config,c", po::value<std::string>()->default_value(DEFAULT_CONFIG),
        "use a custom configuration");
    config->add_options()("verbose,v", po::bool_switch()->default_value(false),
                          "enable verbose logging");
}

int Config::parse_args(int argc, char **argv)
{
    try {
        parse(argc, argv);
    } catch (const po::unknown_option &e) {
        if (config_error)
            return raw_error_log("{} found in '{}'", e.what(), config_file);
        return raw_error_log("{}", e.what());
    } catch (const std::exception &e) {
        return raw_error_log("{}", e.what(), path());
    }
    return 0;
}

void print_options(std::ostream &os, po::options_description &desc)
{
    for (auto &opt : desc.options()) {
        auto option = opt->format_name();

        os << "  " << option
           << std::string(HELP_OPTION_WIDTH - option.size(), ' ')
           << opt->description() << '\n';
        opt->format_name();
        auto fmt = opt->format_parameter();
        if (fmt.size())
            os << "      " << fmt << '\n';
    }
}

int Config::usage(std::ostream &os, int return_code) const
{
    po::options_description merged;
    merged.add(*desc).add(*config);
    std::string params;
    for (auto &opt : merged.options()) {
        auto fmt = opt->format_name();
        auto second_char = fmt.substr(1, 1)[0];
        if (second_char != '-')
            // If the second character is a -, there's no short-hand.
            // Otherwise, there is; append it.
            params.push_back(second_char);
    }
    os << "usage: " << prog << " [-" << params << "]\n";
    return return_code;
}

int Config::help(std::ostream &os, int return_code) const
{
    usage(os, 0);

    os << "\nProgram options:\n";
    print_options(os, *desc);
    print_options(os, *config);
    os << "\nReport bugs by filing an issue on " << PROJECT_URL << '\n';

    return return_code;
}

int Config::config_help(std::ostream &os, int return_code) const
{
    os << "Configuration options\n";
    os << "---------------------\n";
    for (auto &opt : config->options()) {
        os << opt->long_name() << ": " << opt->description() << std::endl;
        auto param = opt->format_parameter();
        if (param.size())
            os << "  > " << param << std::endl;
    }
    return return_code;
}

bool Config::has(const std::string &option) const
{
    return vm.count(option);
}

const std::string &Config::path(void) const
{
    return config_file;
}
