# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
project('taskpp', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

gtest = dependency('gtest', version : '>=1.11.0')
gtest_main = dependency('gtest_main', version : '>=1.11.0')
gmock = dependency('gmock', version : '>=1.11.0')

ncurses = dependency('ncurses', version : '>=6.3')
fmt = dependency('fmt', version : '>= 8.1.0')

flags = [
  '-DPROJECT_ROOT="{}/src/"'.format(meson.source_root())
]
test_flags = [
  '--coverage',
  '-g',
  '-DBUILD_TEST',
]
subdir('src')

# This needs to be at the tail end, in case we want to group
# operations together. Coverage should always be last :)
run_target('show-coverage', command: ['scripts/coverage.sh'])
