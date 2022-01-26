#!/bin/bash
set -eou pipefail
cd "${MESON_SOURCE_ROOT}"
exec doxygen
