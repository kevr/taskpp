/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "app.hpp"
#include "logging.hpp"
#include "tui/bar.hpp"
#include "tui/board.hpp"
#include "tui/screen.hpp"
#include <iostream>
#include <stdexcept>
using namespace taskpp;

static Logger logger(__FILENAME__);

int App::init(int argc, char **argv)
{
    auto parse_error = config.parse_args(argc, argv);
    if (parse_error)
        return parse_error;

    if (config.has("help")) {
        return config.help(std::cout, RETURN_HELP);
    } else if (config.has("config-help")) {
        return config.config_help(std::cout, RETURN_HELP);
    } else if (config.has("version")) {
        return !(std::cout << VERSION << std::endl);
    } else if (config.get<bool>("verbose")) {
        logger.set_level(DEBUG);
        log_debug("Debug logging enabled.");
    }

    return 0;
}

int App::run(void)
{
    term.start();
    screen.init(term.stdscr(), term.root());

    // Build our interface on the root handle
    auto root = screen.window(ROOT);

    auto header = std::make_shared<Bar>(root, 0);
    header->content(fmt::format("{} - v{}", PROJECT_NAME, VERSION)).draw();
    screen.emplace(ROOT, HEADER_BAR, header);

    screen.emplace(ROOT, BOARD, std::make_shared<Board>(root, 1));

    auto footer = std::make_shared<Bar>(root, term.rows() - 1);
    std::string url(PROJECT_URL);
    footer->content(PROJECT_URL).draw();
    screen.emplace(ROOT, FOOTER_BAR, footer);

    root->refresh();
    return 0;
}
