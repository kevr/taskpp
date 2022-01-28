/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "library.hpp"
#include "iface/ncurses.hpp"
#include "iface/os.hpp"
#include <memory>
using namespace taskpp;

Library::Library(void)
{
    static OS os;
    set<OSInterface>("os", os);

    static Ncurses ncurses;
    set<NcursesInterface>("ncurses", ncurses);
}

Library &Library::instance(void)
{
    static Library instance;
    return instance;
}

Library &Library::restore(void)
{
    for (auto &kv : last)
        objects[kv.first] = kv.second;
    last.clear();
    return *this;
}

namespace taskpp
{

Library &restore_library(void)
{
    return Library::instance().restore();
}

}; // namespace taskpp
