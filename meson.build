# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
project('taskpp', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

gtest = dependency('gtest', version : '>=1.11.0')
gtest_main = dependency('gtest_main', version : '>=1.11.0')

test_flags = ['--coverage', '-g']
subdir('src')
