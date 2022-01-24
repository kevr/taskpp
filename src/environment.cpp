/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "environment.hpp"
#include "iface/os.hpp"
#include "library.hpp"
#include "logging.hpp"
#include <stdexcept>

#ifdef _WIN32
static const char *const PATHSEP = "\\"; // LCOV_EXCL_LINE
#else
static const char *const PATHSEP = "/";
#endif

namespace taskpp
{

std::string config_root(void)
{
    auto &os = os();

    const char *xdg_config_home = os.getenv("XDG_CONFIG_HOME");
    if (xdg_config_home)
        // $XDG_CONFIG_HOME/taskpp
        return std::string(xdg_config_home) + PATHSEP + "taskpp";

    const char *home = os.getenv("HOME");
    if (!home)
        throw std::runtime_error("unable to gather required environment "
                                 "variables XDG_CONFIG_HOME or HOME");

    // $HOME/.config/taskpp
    return std::string(home) + PATHSEP + ".config" + PATHSEP + "taskpp";
}

std::string config_file_path(void)
{
    // <config_root>/config
    return config_root() + PATHSEP + "config";
}

}; // namespace taskpp
