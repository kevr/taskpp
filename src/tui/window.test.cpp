/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "window.hpp"
#include "../exceptions.hpp"
#include "../library.hpp"
#include "../mocks/ncurses.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
using namespace taskpp;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

class WindowTest : public ::testing::Test
{
protected:
    NiceMock<MockNcurses> mock_ncurses;
    std::shared_ptr<Window> window;

public:
    void SetUp(void)
    {
        set_library("ncurses", mock_ncurses);

        WINDOW *parent = reinterpret_cast<WINDOW *>(1);
        WINDOW *win = reinterpret_cast<WINDOW *>(2);
        EXPECT_CALL(mock_ncurses, subwin(_, _, _, _, _))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(win));

        window = std::make_shared<Window>();
        window->set_parent(parent).init(1, 1, 1, 1);
    }

    void TearDown(void)
    {
        restore_library();
    }
};

TEST_F(WindowTest, works)
{
    ASSERT_TRUE(*window);

    // Copy construct
    auto win2 = std::make_shared<Window>(*window);
    ASSERT_EQ(win2->pointer(), window->pointer());

    *win2 = *window; // Copy assign
    ASSERT_EQ(win2->pointer(), window->pointer());

    // Move construct
    auto win3 = std::make_shared<Window>(std::move(*win2));
    *win2 = std::move(*win3); // Move assign
    *win3 = std::move(*win2);
    ASSERT_NE(win3->pointer(), nullptr);
    ASSERT_NE(win3->pointer(), win2->pointer());
    ASSERT_EQ(window->pointer(), win3->pointer());
}

TEST_F(WindowTest, double_initialization)
{
    ASSERT_THROW(window->init(1, 1, 1, 1), ResourceError);
}

TEST_F(WindowTest, pointer)
{
    auto ptr = reinterpret_cast<WINDOW *>(2);
    ASSERT_EQ(window->pointer(), ptr);
}

TEST_F(WindowTest, refresh)
{
    EXPECT_CALL(mock_ncurses, wrefresh(_)).Times(1).WillOnce(Return(OK));
    ASSERT_EQ(window->refresh(), OK);

    EXPECT_CALL(mock_ncurses, wrefresh(_)).Times(1).WillOnce(Return(ERR));
    ASSERT_EQ(window->refresh(), ERR);
}

TEST_F(WindowTest, box)
{
    ASSERT_NO_THROW(window->box());
}

TEST_F(WindowTest, draw)
{
    ASSERT_NO_THROW(window->draw());
}

TEST_F(WindowTest, children)
{
    auto child = std::make_shared<Window>();
    child->set_parent(*window);
    window->add_child(child);

    std::vector<std::shared_ptr<Window>> expected({ child });
    ASSERT_EQ(window->get_children(), expected);
}

TEST_F(WindowTest, color)
{
    window->color(get_color(COLOR_BAR), [](Window &window) {
        ncurses().mvwprintw(window.pointer(), 0, 0, "Test");
    });
}

// TODO: This test should be replaced by real usage of wmove
// down the road when it's supported. For now, this is employed
// so it's ready and we gain coverage over its mock.
TEST_F(WindowTest, mock_wmove)
{
    ASSERT_EQ(ncurses().wmove(*window, 0, 0), 0);
}

TEST(Window, nullptr)
{
    ASSERT_THROW(Window().init(1, 1, 1, 1), ResourceError);
}

TEST(Window, subwin_fail_throws_runtime_error)
{
    NiceMock<MockNcurses> mock_ncurses;
    set_library("ncurses", mock_ncurses);

    auto parent = reinterpret_cast<WINDOW *>(1);
    EXPECT_CALL(mock_ncurses, subwin(_, _, _, _, _))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(nullptr));

    ASSERT_THROW(Window().set_parent(parent).init(1, 1, 1, 1), ResourceError);

    restore_library();
}
