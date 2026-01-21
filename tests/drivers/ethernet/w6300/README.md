# W6300 Ethernet Driver Test

This test application verifies the functionality of the W6300 Ethernet driver on the `w6300_evb_pico2_rp2350a_hazard3` board.

## Building and Running

To build and run the test, use the `west` command:

```bash
west build -b w6300_evb_pico2_rp2350a_hazard3 tests/drivers/ethernet/w6300
west flash
```

## Expected Output

The test will attempt to initialize the network interface and acquire an IP address via DHCP.
If successful, you will see a log message indicating that the test has passed:
```
Test passed: Ethernet link is up and IP address is assigned.
```
If the test fails to acquire an IP address within 10 seconds, it will report a failure:
```
Test failed: Could not acquire IP address.
```
