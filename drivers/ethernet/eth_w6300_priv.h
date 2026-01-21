/* W6300 Stand-alone Ethernet Controller with SPI
 *
 * Copyright (c) 2020 Linumiz
 * Author: Parthiban Nallathambi <parthiban@linumiz.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/net/phy.h>

#ifndef _W6300_
#define _W6300_

/*
 * W6300 common registers
 */
#define W6300_COMMON_REGS	0x0000
#define W6300_MR		0x0000 /* Mode Register */
#define W6300_GW		0x0001
#define MR_RST			0x80 /* S/W reset */
#define MR_PB			0x10 /* Ping block */
#define MR_AI			0x02 /* Address Auto-Increment */
#define MR_IND			0x01 /* Indirect mode */
#define W6300_SHAR		0x0009 /* Source MAC address */
#define W6300_IR		0x0015 /* Interrupt Register */
#define W6300_COMMON_REGS_LEN	0x0040
#define W6300_PHYCFGR		0x002E /* PHY Configuration register */

#define W6300_PHYCFGR_LNK_BIT	0 /* Link status */
#define W6300_PHYCFGR_SPD_BIT	1 /* Speed status */
#define W6300_PHYCFGR_DPX_BIT	2 /* Duplex status */
#define W6300_PHYCFGR_LNK	BIT(W6300_PHYCFGR_LNK_BIT) /* Link status */
#define W6300_PHYCFGR_SPD	BIT(W6300_PHYCFGR_SPD_BIT) /* Speed status */
#define W6300_PHYCFGR_DPX	BIT(W6300_PHYCFGR_DPX_BIT) /* Duplex status */

#define W6300_Sn_MR		0x0000 /* Sn Mode Register */
#define W6300_Sn_CR		0x0001 /* Sn Command Register */
#define W6300_Sn_IR		0x0002 /* Sn Interrupt Register */
#define W6300_Sn_SR		0x0003 /* Sn Status Register */
#define W6300_Sn_TX_FSR		0x0020 /* Sn Transmit free memory size */
#define W6300_Sn_TX_RD		0x0022 /* Sn Transmit memory read pointer */
#define W6300_Sn_TX_WR		0x0024 /* Sn Transmit memory write pointer */
#define W6300_Sn_RX_RSR		0x0026 /* Sn Receive free memory size */
#define W6300_Sn_RX_RD		0x0028 /* Sn Receive memory read pointer */

#define W6300_S0_REGS		0x10000

#define W6300_S0_MR		(W6300_S0_REGS + W6300_Sn_MR)
#define S0_MR_MACRAW		0x04 /* MAC RAW mode */
#define S0_MR_MF		0x40 /* MAC Filter for W6300 */
#define W6300_S0_CR		(W6300_S0_REGS + W6300_Sn_CR)
#define S0_CR_OPEN		0x01 /* OPEN command */
#define S0_CR_CLOSE		0x10 /* CLOSE command */
#define S0_CR_SEND		0x20 /* SEND command */
#define S0_CR_RECV		0x40 /* RECV command */
#define W6300_S0_IR		(W6300_S0_REGS + W6300_Sn_IR)
#define S0_IR_SENDOK		0x10 /* complete sending */
#define S0_IR_RECV		0x04 /* receiving data */
#define W6300_S0_SR		(W6300_S0_REGS + W6300_Sn_SR)
#define S0_SR_MACRAW		0x42 /* mac raw mode */
#define W6300_S0_TX_FSR		(W6300_S0_REGS + W6300_Sn_TX_FSR)
#define W6300_S0_TX_RD		(W6300_S0_REGS + W6300_Sn_TX_RD)
#define W6300_S0_TX_WR		(W6300_S0_REGS + W6300_Sn_TX_WR)
#define W6300_S0_RX_RSR		(W6300_S0_REGS + W6300_Sn_RX_RSR)
#define W6300_S0_RX_RD		(W6300_S0_REGS + W6300_Sn_RX_RD)
#define W6300_S0_IMR		(W6300_S0_REGS + W6300_Sn_IMR)

#define W6300_S0_MR_MF		7 /* MAC Filter for W6300 */
#define W6300_Sn_REGS_LEN	0x0040
#define W6300_SIMR		0x0018 /* Socket Interrupt Mask Register */
#define IR_S0			0x01
#define RTR_DEFAULT		2000
#define W6300_RTR		0x0019 /* Retry Time-value Register */


#define W6300_Sn_RXMEM_SIZE(n)	\
		(0x1001e + (n) * 0x40000) /* Sn RX Memory Size */
#define W6300_Sn_TXMEM_SIZE(n)	\
		(0x1001f + (n) * 0x40000) /* Sn TX Memory Size */

#define W6300_Sn_TX_MEM_START	0x20000
#define W6300_TX_MEM_SIZE	0x04000
#define W6300_Sn_RX_MEM_START	0x30000
#define W6300_RX_MEM_SIZE	0x04000

/* Delay for PHY write/read operations (25.6 us) */
#define W6300_PHY_ACCESS_DELAY		26U
struct w6300_config {
	struct spi_dt_spec spi;
	struct gpio_dt_spec interrupt;
	struct gpio_dt_spec reset;
	struct net_eth_mac_config mac_cfg;
	const struct device *phy_dev;
};

struct w6300_runtime {
	struct net_if *iface;

	K_KERNEL_STACK_MEMBER(thread_stack,
			      CONFIG_ETH_W6300_RX_THREAD_STACK_SIZE);
	struct k_thread thread;
	uint8_t mac_addr[6];
	struct gpio_callback gpio_cb;
	struct k_sem tx_sem;
	struct k_sem int_sem;
	struct phy_link_state state;
	uint8_t buf[NET_ETH_MAX_FRAME_SIZE];
};

#endif /*_W6300_*/
