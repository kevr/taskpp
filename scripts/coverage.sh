#!/bin/bash
# Copyright (C) 2022 Kevin Morris
# Complete GPLv2 text can be found in LICENSE.
set -eou pipefail

ninja coverage-text

if [ $# -gt 0 ] && [ "$1" = "--xml" ]; then
    ninja coverage-xml
fi

exec cat "${MESON_BUILD_ROOT}/meson-logs/coverage.txt"
