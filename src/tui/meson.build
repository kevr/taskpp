# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
tui_terminal_test = executable('tui.terminal.test',
  'terminal.test.cpp',
  link_with: [test_lib],
  dependencies : [gtest, gtest_main])
test('basic', tui_terminal_test)
