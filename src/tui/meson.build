# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
if build_tests
  tui_window_test = executable('tui.window.test',
    'window.test.cpp',
    dependencies : [test_dep])
  test('basic', tui_window_test)

  tui_terminal_test = executable('tui.terminal.test',
    'terminal.test.cpp',
    dependencies : [test_dep])
  test('basic', tui_terminal_test)

  tui_color_test = executable('tui.color.test',
    'color.test.cpp',
    dependencies : [test_dep])
  test('basic', tui_color_test)
endif
