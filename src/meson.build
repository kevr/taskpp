# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.

build_tests = get_option('build_tests')

# Non-main source files.
sources = [
  'tui/terminal.cpp',
  'tui/window.cpp',
  'tui/color.cpp',
  'library.cpp',
  'iface/ncurses.cpp',
  'logging.cpp',
  'config.cpp',
  'environment.cpp',
  'iface/os.cpp',
  'string.cpp',
]

if build_tests
  # Include test libraries.
  gtest = dependency('gtest', version : '>=1.11.0')
  gtest_main = dependency('gtest_main', version : '>=1.11.0')
  gmock = dependency('gmock', version : '>=1.11.0')
endif

if build_tests
  # Create a test version of `lib` with stubbed symbols.
  # We'll link this one to tests to avoid using thid-party
  # libraries or syscalls.
  subdir('stubs')
  test_lib = static_library('taskpp_test_impl',
    sources: sources,
    cpp_args: flags + test_flags,
    link_args: test_flags,
    link_with: [stubs],
    dependencies: [gtest, gtest_main, gmock, boost, fmt])
  test_dep = declare_dependency(
    compile_args: flags + test_flags,
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
  config_test = executable('config.test',
    'config.test.cpp',
    dependencies : [test_dep])
  test('basic', config_test)
  env_test = executable('environment.test',
    'environment.test.cpp',
    dependencies : [test_dep])
  test('basic', env_test)
  string_test = executable('string.test',
    'string.test.cpp',
    dependencies : [test_dep])
  test('basic', string_test)
endif

# Build text user interface.
subdir('tui')

if not build_tests
  # Main binary executable `taskpp`.
  exec = executable('taskpp',
    sources: sources + ['main.cpp'],
    cpp_args: flags,
    dependencies: [boost, ncurses, fmt],
    install : true)
  run_target('run', command: [exec])
endif
