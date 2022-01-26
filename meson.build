# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
project('taskpp', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

boost = dependency('boost', version : '>=1.78.0',
  modules : ['program_options', 'filesystem'])
ncurses = dependency('ncurses', version : '>=6.3')
fmt = dependency('fmt', version : '>=8.1.0')

flags = [
  '-Warith-conversion',
  '-Werror',
  '-DPROJECT_ROOT="{}/src/"'.format(meson.source_root()),
]
test_flags = [
  '--coverage',
  '-g',
  '-DBUILD_TEST',
]
subdir('src')

run_target('cov', command: ['scripts/coverage.sh', '--xml'])

if get_option('build_doc')
  find_program('doxygen')
  find_program('dot')
  run_target('doc', command: ['scripts/doc.sh'])
endif
