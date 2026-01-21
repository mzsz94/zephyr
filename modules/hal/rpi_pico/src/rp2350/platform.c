/*
 * Copyright (c) 2026 SUZINEE
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <soc.h>

static int rp2350_init(const struct device *dev)
{
	ARG_UNUSED(dev);
	/* Basic SoC initialization for RP2350 */
	return 0;
}

SYS_INIT(rp2350_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
