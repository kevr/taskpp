# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
FROM archlinux:base-devel
VOLUME ["/var/cache/pacman/pkg"]
RUN pacman-key --init
RUN pacman -Sy --noconfirm --noprogressbar  archlinux-keyring
RUN pacman -Syu --noconfirm --noprogressbar \
    meson gcc gcovr gtest boost fmt clang git curl sudo python cppcheck
