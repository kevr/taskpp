/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "../iface/os.hpp"
#include <gmock/gmock.h>

namespace taskpp
{

class MockOS : public OSInterface
{
public:
    MOCK_METHOD(const char *, getenv, (const char *), (const, override));
};

}; // namespace taskpp
