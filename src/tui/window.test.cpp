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
    std::unique_ptr<Window> window;

public:
    void SetUp(void)
    {
        set_library("ncurses", mock_ncurses);

        WINDOW *win = reinterpret_cast<WINDOW *>(1);
        EXPECT_CALL(mock_ncurses, newwin(_, _, _, _))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(win));

        window = std::make_unique<Window>(1, 1, 1, 1);
    }

    void TearDown(void)
    {
        restore_library();
    }
};

TEST(Window, nullptr)
{
    ASSERT_THROW(Window(1, 1, 1, 1), std::runtime_error);
}

TEST_F(WindowTest, pointer)
{
    auto ptr = reinterpret_cast<WINDOW *>(1);
    ASSERT_EQ(window->pointer(), ptr);
}

TEST_F(WindowTest, refresh)
{
    EXPECT_CALL(mock_ncurses, wrefresh(_)).Times(1).WillOnce(Return(OK));
    ASSERT_EQ(window->refresh(), OK);

    EXPECT_CALL(mock_ncurses, wrefresh(_)).Times(1).WillOnce(Return(ERR));
    ASSERT_EQ(window->refresh(), ERR);
}
