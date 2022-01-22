/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <map>
#include <string>

namespace taskpp
{

/**
 * @brief Centralized library manager
 *
 * This class stores type-erased library interfaces which can
 * then be invoked via `get<T>`.
 *
 * Each instance of Library shall initialize library-linked
 * interfaces. These can then be overridden with `set`. This
 * comes in particularly useful for testing against code which
 * utilizes third party library code that may intrude on the
 * testing environment.
 *
 * The `set_library` and `library` helper functions are made
 * available to allow easy use of Library's singleton instance().
 **/
class Library
{
private:
    //! Internal type-erased interface objects
    std::map<std::string, void *> objects;

    //! Storage for most recent interface object
    std::map<std::string, void *> last;

public:
    //! Construct a Library
    Library(void);

    //! Set a library interface by key and reference to the interface
    template <typename T>
    Library &set(const char *key, T &interface)
    {
        if (objects.find(key) != objects.end())
            last[key] = objects.at(key);
        objects[key] = reinterpret_cast<void *>(&interface);
        return *this;
    }

    //! Get a Library interface by key
    template <typename T>
    T &get(const char *key) const
    {
        return *reinterpret_cast<T *>(objects.at(key));
    }

    //! Restore all interfaces which were overridden to the most recent pointer
    Library &restore(void);

public:
    //! Singleton.
    static Library &instance(void);
};

//! Set a library interface through Library::instance()
template <typename T>
Library &set_library(const char *key, T &interface)
{
    return Library::instance().set<T>(key, interface);
}

//! Get a library interface through Library::instance()
template <typename T>
T &library(const char *key)
{
    return Library::instance().get<T>(key);
}

//! Restore overridden library interfaces
Library &restore_library(void);

}; // namespace taskpp

// Global access macros.
#define ncurses() taskpp::library<NcursesInterface>("ncurses")

#endif /* LIBRARY_HPP */
