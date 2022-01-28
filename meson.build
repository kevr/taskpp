# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
project('taskpp', 'cpp',
  version : run_command('git', 'describe', '--abbrev=0',
    check: false).stdout().strip() + '-' + run_command('bash', '-c',
      'git rev-list --count $(git describe --abbrev=0)..HEAD',
      check: false).stdout().strip(),
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

# Application version, defaulted to 0.0.0
desc = run_command('git', 'describe', '--abbrev=0', check: true)
desc = desc.stdout().strip()
if desc == ''
  desc = '0.0.0'
endif

patch = run_command('git', 'rev-list', '--count', desc + '..HEAD',
  check: true)
patch = patch.stdout().strip()

boost = dependency('boost', version : '>=1.78.0',
  modules : ['program_options', 'filesystem', 'system'])
ncurses = dependency('ncurses', version : '>=6.3')
fmt = dependency('fmt', version : '>=8.1.0')

cxx = meson.get_compiler('cpp')
dl = cxx.find_library('dl')

flags = [
  '-Warith-conversion',
  '-Werror',
  '-DPROJECT_ROOT="{}/src/"'.format(meson.source_root()),
  '-DVERSION="' + desc + '-' + patch + '"'.format(desc),
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
