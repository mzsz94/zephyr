# Copyright (c) 2026 SUZINEE
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(.)

# Define the SoC as a library
target_sources(soc PUBLIC
  platform.c
)

set(SOC_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld CACHE INTERNAL "")
