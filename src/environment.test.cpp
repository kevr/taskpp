/**
 * Copyright (C) 2022 Kevin Morris
 * Complete GPLv2 text can be found in LICENSE.
 **/
#include "environment.hpp"
#include "library.hpp"
#include "mocks/os.hpp"
#include <gtest/gtest.h>
using namespace taskpp;
using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

class EnvTest : public ::testing::Test
{
protected:
    NiceMock<MockOS> mock_os;

public:
    void SetUp(void)
    {
        set_library("os", mock_os);
    }

    void TearDown(void)
    {
        restore_library();
    }
};

TEST_F(EnvTest, xdg_config_home)
{
    EXPECT_CALL(mock_os, getenv(_)).Times(1).WillOnce(Return("test"));
    ASSERT_EQ(config_root(), "test/taskpp");
}

TEST_F(EnvTest, home)
{
    EXPECT_CALL(mock_os, getenv(_))
        .Times(2)
        .WillOnce(Return(nullptr))
        .WillOnce(Return("test"));
    ASSERT_EQ(config_root(), "test/.config/taskpp");
}

TEST_F(EnvTest, variable_missing)
{
    EXPECT_CALL(mock_os, getenv(_)).Times(2).WillRepeatedly(Return(nullptr));
    ASSERT_THROW(config_root(), std::runtime_error);
}
