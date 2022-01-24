/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "os.hpp"
#include <cstdlib>
using namespace taskpp;

const char *OS::getenv(const char *name) const
{
    return ::getenv(name);
}
