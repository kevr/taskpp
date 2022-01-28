/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "window.hpp"
#include "../logging.hpp"
#include "../macros.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <stdexcept>
using namespace taskpp;

static Logger logger(__FILENAME__);

Window::Window(WINDOW *ptr)
    : ptr(ptr)
{
}

Window::Window(const Window &other)
    : parent(other.parent)
    , prev(other.prev)
    , ptr(other.ptr)
    , node(other.node)
    , children(other.children)
{
}

Window::Window(Window &&other)
    : parent(other.parent)
    , prev(std::move(other.prev))
    , ptr(other.ptr)
    , node(std::move(other.node))
    , children(std::move(other.children))
{
    other.parent = other.ptr = nullptr; // Reset other's raw pointers
}

Window::~Window(void)
{
    teardown();
}

Window &Window::operator=(const Window &other)
{
    parent = other.parent;
    prev = other.prev;
    ptr = other.ptr;
    node = other.node;
    children = other.children;
    return *this;
}

Window &Window::operator=(Window &&other)
{
    parent = other.parent;
    prev = std::move(other.prev);
    ptr = other.ptr;
    node = std::move(other.node);
    children = std::move(other.children);
    other.parent = other.ptr = nullptr; // Reset other's raw pointers
    return *this;
}

Window &Window::set_parent(WINDOW *ptr)
{
    parent = ptr;
    prev = std::make_shared<Window>(parent);
    if (node) {
        node->set_parent(parent);
    }
    return *this;
}

Window &Window::init(int x, int y, int w, int h)
{
    ASSERT_NOT_NULL_ACTOR(parent, "Window::parent");
    prev = std::make_shared<Window>(parent);

    ASSERT_NULL_ACTOR(ptr, "Window::ptr");
    ptr = ncurses().subwin(parent, h, w, y, x);
    ASSERT_NOT_NULL_ACTOR(ptr, "Window::ptr");

    node = std::make_shared<Window>(ptr);
    node->set_parent(parent);

    refresh();
    return *this;
}

Window &Window::set_color(chtype color_pair)
{
    ncurses().wbkgd(ptr, color_pair);
    return *this;
}

Window::operator WINDOW *(void) const
{
    return ptr;
}

Window::operator bool(void) const
{
    return ptr;
}

WINDOW *Window::pointer(void) const
{
    return ptr;
}

Window &Window::add_child(std::shared_ptr<Window> child)
{
    if (std::find(children.begin(), children.end(), child) == children.end()) {
        children.push_back(child);
    }
    return *this;
}

int Window::refresh(void) const
{
    for (auto &child : children)
        child->refresh();
    return ncurses().wrefresh(ptr);
}

const Window &Window::box(void) const
{
    ncurses().wborder(ptr, VLINE, VLINE, HLINE, HLINE, ULCORNER, URCORNER,
                      LLCORNER, LRCORNER); // LCOV_EXCL_LINE
    return *this;
}

const Window &Window::teardown(void)
{
    children.clear();

    if (ptr) {
        if (!parent) {
            ncurses().endwin();
        } else {
            ncurses().delwin(ptr);
        }
    }

    return *this;
}

std::vector<std::shared_ptr<Window>> Window::get_children(void) const
{
    return children;
}

void Window::draw(void)
{
    // noop
}
