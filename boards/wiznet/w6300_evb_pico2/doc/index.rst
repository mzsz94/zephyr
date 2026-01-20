.. zephyr:board:: w6300_evb_pico2

Overview
********

W6300-EVB-Pico2 is a microcontroller evaluation board based on the Raspberry
Pi RP2350A and Wiznet W6300 Ethernet controller. This initial Zephyr board
support targets the RP2350A Hazard3 (RISC-V) core and is intended as a minimal
skeleton for bring-up. The USB bootloader allows the ability to flash without
any adapter, in a drag-and-drop manner. It is also possible to flash and debug
with the SWD interface, using an external adapter.

Hardware
********

- Dual core Arm Cortex-M33 or Hazard3 processor running up to 133MHz
- 520KB on-chip SRAM
- 16MB on-board QSPI flash with XIP capabilities
- 26 GPIO pins
- 3 Analog inputs
- 2 UART peripherals
- 2 SPI controllers
- 2 I2C controllers
- 16 PWM channels
- USB 1.1 controller (host/device)
- 3 Programmable I/O (PIO) for custom peripherals
- On-board LED
- 1 Watchdog timer peripheral
- Wiznet W6300 Ethernet controller

Supported Features
==================

.. zephyr:board-supported-hw::

Pin Mapping
===========

The peripherals of the RP2350A SoC can be routed to various pins on the board.
The configuration of these routes can be modified through DTS. Please refer to
the datasheet to see the possible routings for each peripheral.

External pin mapping on the W6300-EVB-Pico2 is intended to follow the Raspberry
Pi Pico2 header layout. This skeleton uses the same pin defaults as other
RP2350A Pico2-style boards. The W6300 SPI/IRQ/RST wiring is intentionally
omitted in DTS until a dedicated binding and driver support land.

Default Zephyr Peripheral Mapping:
----------------------------------

.. rst-class:: rst-columns

- UART0_TX : P0
- UART0_RX : P1
- I2C0_SDA : P4
- I2C0_SCL : P5
- I2C1_SDA : P6
- I2C1_SCL : P7
- SPI0_RX : P16
- SPI0_CSN : P17
- SPI0_SCK : P18
- SPI0_TX : P19
- ADC_CH0 : P26
- ADC_CH1 : P27
- ADC_CH2 : P28
- ADC_CH3 : P29

Programming and Debugging
*************************

.. zephyr:board-supported-runners::

The overall explanation regarding flashing and debugging is the same as or :zephyr:board:`rpi_pico`.
See :ref:`rpi_pico_programming_and_debugging` in :zephyr:board:`rpi_pico` documentation. N.b. OpenOCD support requires using Raspberry Pi's forked version of OpenOCD.

Below is an example of building and flashing the :zephyr:code-sample:`hello_world` application.

.. zephyr-app-commands::
   :zephyr-app: samples/hello_world
   :board: w6300_evb_pico2/rp2350a/hazard3
   :goals: build flash
   :flash-args: --openocd /usr/local/bin/openocd

Notes and Limitations
=====================

- This initial skeleton supports console UART, GPIO, and basic peripherals only.
  W6300 networking support will be added in a follow-up change once a driver
  and devicetree binding are available.
- Hazard3 XIP/flash behavior follows the upstream RP2350A RISC-V defaults.
  If you encounter flash/XIP issues, start with SRAM-only builds or the
  defaults used by other RP2350 Hazard3 boards while tooling matures.
