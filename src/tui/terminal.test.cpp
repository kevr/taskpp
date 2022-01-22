/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "terminal.hpp"
#include "../library.hpp"
#include "../mocks/ncurses.hpp"
#include <gtest/gtest.h>
#include <memory>
using namespace taskpp;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

class TerminalTest : public ::testing::Test
{

protected:
    NiceMock<MockNcurses> mock_ncurses;
    std::unique_ptr<Terminal> term;

public:
    void SetUp(void)
    {
        set_library("ncurses", mock_ncurses);

        WINDOW *win = reinterpret_cast<WINDOW *>(1);
        EXPECT_CALL(mock_ncurses, initscr())
            .Times(AtLeast(1))
            .WillRepeatedly(Return(win));
        EXPECT_CALL(mock_ncurses, newwin(_, _, _, _))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(win));
        EXPECT_CALL(mock_ncurses, endwin())
            .Times(AtLeast(0))
            .WillRepeatedly(Return(OK));

        term = std::make_unique<Terminal>();
    }

    void TearDown(void)
    {
        restore_library();
    }
};

TEST_F(TerminalTest, fails_second_construction)
{
    ASSERT_THROW(Terminal(), std::domain_error);
}

TEST_F(TerminalTest, refreshes)
{
    term->refresh();
}
