/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#define main _main
// We use a trick here, where we force main.cpp to define _main
// instead of main(); that way, we can test _main and allow
// gtest_main's main() to link.
#include "main.cpp"
#undef main

#include "library.hpp"
#include "mocks/ncurses.hpp"
#include <gtest/gtest.h>
using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

class MainTest : public ::testing::Test
{
protected:
    NiceMock<MockNcurses> mock_ncurses;
    std::unique_ptr<Terminal> term;

public:
    void SetUp(void)
    {
        taskpp::set_library("ncurses", mock_ncurses);

        WINDOW *root = reinterpret_cast<WINDOW *>(1);
        WINDOW *win = reinterpret_cast<WINDOW *>(2);
        EXPECT_CALL(mock_ncurses, initscr())
            .Times(AtLeast(0))
            .WillRepeatedly(Return(root));
        EXPECT_CALL(mock_ncurses, subwin(_, _, _, _, _))
            .Times(AtLeast(0))
            .WillRepeatedly(Return(win));
        EXPECT_CALL(mock_ncurses, endwin())
            .Times(AtLeast(0))
            .WillRepeatedly(Return(OK));
    }

    void TearDown(void)
    {
        taskpp::restore_library();
    }
};

const char *arg0 = "taskpp";

TEST_F(MainTest, runs)
{
    auto rc = _main(1, const_cast<char **>(&arg0));
    ASSERT_EQ(rc, 0);
}

TEST(main, invalid_args)
{
    const char *argv[3] = { arg0, "invalid", nullptr };
    auto rc = _main(2, const_cast<char **>(argv));
    ASSERT_EQ(rc, 1);
}
