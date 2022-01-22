#!/bin/bash
set -eou pipefail
exec cat "${MESON_BUILD_ROOT}/meson-logs/coverage.txt"
