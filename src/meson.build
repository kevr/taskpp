# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.

sources = ['tui/terminal.cpp']

lib = static_library('taskpp_impl',
  sources: sources,
  cpp_args: test_flags,
  link_args: test_flags,
  dependencies: [ncurses])

exe = executable('taskpp',
  'main.cpp',
  cpp_args: test_flags,
  link_args: test_flags,
  link_with: [lib],
  install : true)

subdir('stubs')

test_lib = static_library('taskpp_test_impl',
  sources: sources,
  cpp_args: test_flags,
  link_args: test_flags,
  link_with: [stubs])

subdir('tui')

# Tests.
exe_test = executable('main.test',
  'main.test.cpp',
  link_with: [test_lib],
  dependencies : [gtest, gtest_main])
test('basic', exe_test)
