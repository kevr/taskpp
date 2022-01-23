/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "window.hpp"
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
    Window window { reinterpret_cast<WINDOW *>(1) };

public:
    void SetUp(void)
    {
        set_library("ncurses", mock_ncurses);

        WINDOW *parent = reinterpret_cast<WINDOW *>(1);
        WINDOW *win = reinterpret_cast<WINDOW *>(2);
        EXPECT_CALL(mock_ncurses, subwin(_, _, _, _, _))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(win));

        window.set_parent(parent).init(1, 1, 1, 1);
    }

    void TearDown(void)
    {
        restore_library();
    }
};

TEST_F(WindowTest, works)
{
    ASSERT_TRUE(window);
}

TEST_F(WindowTest, double_initialization)
{
    ASSERT_THROW(window.init(1, 1, 1, 1), std::runtime_error);
}

TEST_F(WindowTest, pointer)
{
    auto ptr = reinterpret_cast<WINDOW *>(2);
    ASSERT_EQ(window.pointer(), ptr);
}

TEST_F(WindowTest, refresh)
{
    EXPECT_CALL(mock_ncurses, wrefresh(_)).Times(1).WillOnce(Return(OK));
    ASSERT_EQ(window.refresh(), OK);

    EXPECT_CALL(mock_ncurses, wrefresh(_)).Times(1).WillOnce(Return(ERR));
    ASSERT_EQ(window.refresh(), ERR);
}

TEST(Window, nullptr)
{
    ASSERT_THROW(Window().init(1, 1, 1, 1), std::runtime_error);
}

TEST(Window, subwin_fail_throws_runtime_error)
{
    NiceMock<MockNcurses> mock_ncurses;
    set_library("ncurses", mock_ncurses);

    auto parent = reinterpret_cast<WINDOW *>(1);
    EXPECT_CALL(mock_ncurses, subwin(_, _, _, _, _))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(nullptr));

    ASSERT_THROW(Window(parent).init(1, 1, 1, 1), std::runtime_error);

    restore_library();
}
