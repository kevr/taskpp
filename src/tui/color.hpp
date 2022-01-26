/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef TUI_COLOR_HPP
#define TUI_COLOR_HPP

#include <map>

namespace taskpp
{

enum TermColor : short {
    COLOR_NONE = -1,
    COLOR_NORM = 100,
    COLOR_BAR,
    COLOR_ACCENT,
};

/**
 * @brief Singleton fixture class for set_pair and get_color
 *
 * This class maintains a static std::map of ids passed to set_pair,
 * where key = generic id and value = pair id generated by calling
 * ncurses' alloc_pair.
 *
 * Currently, it purely operates as a private implementation fixtures for the
 * free `set_pair(short, int, int) -> int` and `get_color(short) -> short`
 **/
class Color
{
private:
    std::map<TermColor, int> map;

private:
    void set(TermColor id, int pair);
    int get(TermColor id) const;
    void clear(void);

    static Color &instance(void);

    friend int set_pair(TermColor id, int fg, int bg);
    friend int get_color(TermColor id);
    friend void clear_colors(void);
};

/**
 * @brief Setup a color pair
 *
 * @param id Enum identifier
 * @param fg Foreground color (-1-255)
 * @param bg Background color (-1-255)
 * @return Pair identifier
 **/
int set_pair(TermColor id, int fg, int bg);

/**
 * @brief Get a color pair
 *
 * @param id Enum identifier
 * @return Pair identifier
 **/
int get_color(TermColor id);

void clear_colors(void);

}; // namespace taskpp

#endif /* TUI_COLOR_HPP */
