# W6300 Ethernet Driver Test

This test application verifies the functionality of the W6300 Ethernet driver on the
`w6300_evb_pico2_rp2350a_hazard3` board by running a minimal HTTP server.

## Building and Running

To build and run the test, use the `west` command:

```bash
west build -b w6300_evb_pico2_rp2350a_hazard3 tests/drivers/ethernet/w6300
west flash
```

## Expected Output

The test initializes the network interface and starts an HTTP server on port 80.
When a client connects, it logs the request and replies with a simple HTML page.
Typical log output looks like this:

```
Starting W6300 HTTP server
HTTP server listening on port 80
Client connected
Request:
GET / HTTP/1.1
Host: 192.168.0.200
```
