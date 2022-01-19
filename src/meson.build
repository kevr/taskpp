# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
exe = executable('taskpp', 'main.cpp',
  install : true)

exe_test = executable('main.test', 'main.test.cpp',
  dependencies : [gtest, gtest_main])

test('basic', exe)
