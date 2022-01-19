taskpp
======

An open source command-line task management application written in C++.

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

First, configure `meson` for the project:

    $ meson builddir

Now that we have a build directory, we can compile the project:

    $ cd builddir
    $ ninja

Installation
------------

After [Building](#building), users can install the project to
their system:

    $ cd builddir
    $ ninja install

Community
---------

* Visit our IRC channel **#taskpp** on [Libera.chat](https://libera.chat)
    * Web client: https://web.libera.chat/?channel=#taskpp

* File an issue at https://github.com/kevr/taskpp

* For private inquiries, send me an email at kevr@0cost.org

Contributing
------------

Developers wishing to contribute to the project are absolutely welcome
to do so. Pull requests are welcomed at any time in our Github repository.

If you're looking to find issues to help with, visit
https://github.com/kevr/taskpp/issues to search for something
you'd like to work on.

When it comes to modifying existing code, we require 100% coverage
on any code that was touched (see [Testing](#testing)).

Testing
-------

_taskpp_ uses the [Google Test](https://github.com/google/googletest)
framework to perform tests against our source code.

Licensing
---------

_taskpp_ is developed under the GPLv2 public license.

**Copyright &copy; 2022 Kevin Morris<br />**
**Complete GPLv2 text can be found in [LICENSE](./LICENSE).**
