/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef IFACE_OS_HPP
#define IFACE_OS_HPP

namespace taskpp
{

class OSInterface
{
public:
    virtual ~OSInterface(void) = default;
    virtual const char *getenv(const char *name) const = 0;
};

class OS : public OSInterface
{
public:
    ~OS(void) = default;
    const char *getenv(const char *name) const;
};

}; // namespace taskpp

#endif /* IFACE_OS_HPP */
