taskpp
======

An open source command-line task management application written in C++.

![pipeline](https://gitlab.com/kevr2d2/taskpp/badges/master/pipeline.svg?style=flat-square&key_text=master) ![coverage](https://gitlab.com/kevr2d2/taskpp/badges/master/coverage.svg?style=flat-square)

With inspiration from [taskell](https://github.com/smallhadroncollider/taskell),
_taskpp_ is intended to support JSON imports and exports to integrate with
[Github](https://github.com) and [Gitlab](https://about.gitlab.com) APIs.

**Q:** Why isn't this being written in Rust?<br />
**A:** I'm just beginning to learn Rust and I believe I can get more done
in a cleaner fashion with C++, given my familiarity with it.

**Q:** C++ is old, what the hell?<br />
**A:** Yes, it is. However, new standards in recent years have modernized
C++ quite a bit; we'll be using C++20-supported compilers and stdlibs in
this project.

Building
--------

Some dependencies are required to build _taskpp_:

    meson
    ninja
    gcc, clang (with C++ frontend, support for C++20)

First, configure `meson` for the project:

    $ meson builddir

Now that we have a build directory, we can compile the project:

    $ ninja -C builddir

Installation
------------

After [Building](#building), users can install the project to
their system:

    $ ninja -C builddir install

Testing
-------

_taskpp_ uses the [Google Test](https://github.com/google/googletest)
framework to perform tests against our source code.

Code coverage is controlled by passing `-Db_coverage=true` to `meson`.
`-Dbuild_tests=true` must be set to run tests:

    $ meson -Db_coverage=true -Dbuild_tests=true builddir

First, [Build](#building) the project. Next, run tests:

    $ ninja -C builddir test

After running tests, produce coverage reports:

    $ ninja -C builddir coverage-text
    $ ninja -C builddir coverage-xml

**Note:** `meson` does not currently have a way to exclude source
files from the coverage report. To cleanup coverage reports,
[kevr's meson patch](https://github.com/kevr/meson/commit/73b04379fdd990ccb75c5b1b36600ead6445346e)
can be used to add support for the `GCOV_ARGS` environment variable.
We can then pass `--exclude` to `gcovr` via the new variable:

    ## with kevr's meson patch
    ## define GCOV_ARGS to exclude sources ending in .test.cpp
    $ export GCOV_ARGS="--exclude '.*\.test\.cpp'"
    $ ninja coverage-text -C builddir

Going out of our way to exclude `.test.cpp` files is a bit too
cumbersome without the aforementioned patch merged into `meson`
upstream. We would primarily like to do this because branch
coverage in `.test.cpp` files can be sporadic and we care about
it being properly exercised within real application source code.

Community
---------

* Visit our IRC channel **#taskpp** on [Libera.chat](https://libera.chat)
    * Web client: https://web.libera.chat/?channel=#taskpp

* File an issue at https://gitlab.com/kevr2d2/taskpp

* For private inquiries, send me an email at kevr@0cost.org

Contributing
------------

Developers wishing to contribute to the project are absolutely welcome
to do so. Merge requests are welcomed at any time in our Gitlab repository.

If you're looking to find issues to help with, visit
https://gitlab.com/kevr2d2/taskpp/issues to search for something
you'd like to work on.

When it comes to modifying existing code, we require 100% coverage
on any code that was touched (see [Testing](#testing)).

Licensing
---------

_taskpp_ is developed under the GPLv2 public license.

**Copyright &copy; 2022 Kevin Morris<br />**
**Complete GPLv2 text can be found in [LICENSE](./LICENSE).**
