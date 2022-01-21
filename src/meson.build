# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.

build_tests = get_option('build_tests')

# Non-main source files.
sources = ['tui/terminal.cpp', 'tui/window.cpp', 'logging.cpp']

if build_tests
  # Create a test version of `lib` with stubbed symbols.
  # We'll link this one to tests to avoid using thid-party
  # libraries or syscalls.
  subdir('stubs')
  test_lib = static_library('taskpp_test_impl',
    sources: sources,
    cpp_args: test_flags,
    link_args: test_flags,
    link_with: [stubs],
    dependencies: [gtest, gtest_main, fmt])
  test_dep = declare_dependency(
    compile_args: test_flags,
    link_args: test_flags,
    link_with: [test_lib])

  exe_test = executable('main.test',
    'main.test.cpp',
    dependencies : [test_dep])
  test('basic', exe_test)
  logging_test = executable('logging.test',
    'logging.test.cpp',
    dependencies : [test_dep])
  test('basic', logging_test)
endif

# Build text user interface.
subdir('tui')

# Main executable linked to lib.
exec = executable('taskpp',
  sources: sources + ['main.cpp'],
  dependencies: [ncurses, fmt],
  install : true)
run_target('run', command: [exec])
