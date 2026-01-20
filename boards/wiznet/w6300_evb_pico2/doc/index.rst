.. zephyr:board:: w6300_evb_pico2

Overview
********

W6300-EVB-Pico2 is a microcontroller evaluation board based on the Raspberry
Pi RP2350 and fully hardwired TCP/IP controller W6300.
The USB bootloader allows the ability to flash without any adapter, in a
drag-and-drop manner. It is also possible to flash and debug the boards with
their SWD interface, using an external adapter.

.. image:: img/w6300_evb_pico2.jpg
   :align: center
   :alt: W6300-EVB-Pico2

Hardware
********
- RISC-V processor
- Support for W6300 Ethernet MAC/PHY

Supported Features
==================

The w6300_evb_pico2 board configuration supports the following hardware features:

.. list-table::
   :header-rows: 1

   * - Interface
     - Controller
     - Driver/Component
   * - സ്വാതന്ത്രство
     - on-chip
     - serial
   * - GPIO
     - on-chip
     - gpio
   * - PINCTRL
     - on-chip
     - pinctrl
   * - SPI
     - on-chip
     - spi

Pin Mapping
===========

The peripherals of the RP2350 SoC can be routed to various pins on the board.
The configuration of these routes can be modified through DTS.

Default Zephyr Peripheral Mapping:
----------------------------------

AIO mapping is not yet defined for this board.

Programming and Debugging
*************************

The overall explanation regarding flashing and debugging is the same as or :zephyr:board:`rpi_pico`.
See the documentation for more details.

Building and Flashing
=====================

Build and flash applications as usual. Here is an example for the
:zephyr:code-sample:`hello_world` application.

.. zephyr-app-commands::
   :zephyr-app: samples/hello_world
   :board: w6300_evb_pico2
   :goals: build flash

Current Support
===============

This initial skeleton only supports the console and basic I/O. W6300 networking
support will be added in a future PR. Hazard3 target might have XIP/flash issues.
Please refer to the Zephyr documentation for known issues and workarounds.
