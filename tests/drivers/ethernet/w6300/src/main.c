/*
 * Copyright (c) 2026 SUZINEE
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/net_core.h>
#include <zephyr/net/net_context.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(net_test, LOG_LEVEL_DBG);

static struct net_mgmt_event_callback mgmt_cb;
static bool test_passed;

static void net_event_handler(struct net_mgmt_event_callback *cb,
			   uint32_t mgmt_event,
			   struct net_if *iface)
{
	if (mgmt_event == NET_EVENT_IPV4_ADDR_ADD) {
		LOG_INF("DHCP IP address acquired");
		test_passed = true;
		k_sleep(K_SECONDS(1));
	}
}

void main(void)
{
	LOG_INF("Starting W6300 Ethernet driver test");

	net_mgmt_init_event_callback(&mgmt_cb, net_event_handler, NET_EVENT_IPV4_ADDR_ADD);
	net_mgmt_add_event_callback(&mgmt_cb);

	struct net_if *iface = net_if_get_default();
	if (!iface) {
		LOG_ERR("No default network interface");
		return;
	}

	net_dhcpv4_start(iface);

	k_sleep(K_SECONDS(10));

	if (test_passed) {
		LOG_INF("Test passed: Ethernet link is up and IP address is assigned.");
	} else {
		LOG_ERR("Test failed: Could not acquire IP address.");
	}
}
