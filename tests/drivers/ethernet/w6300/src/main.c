/*
 * Copyright (c) 2026 SUZINEE
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/net_config.h>
#include <zephyr/net/socket.h>

LOG_MODULE_REGISTER(w6300_http_server, LOG_LEVEL_INF);

#define HTTP_PORT 80
#define RECV_BUF_SIZE 256

static const char http_response[] =
	"HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n"
	"Content-Length: 52\r\n"
	"\r\n"
	"<html><body><h1>W6300 HTTP Server</h1></body></html>";

static int start_http_server(void)
{
	int server_fd;
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(HTTP_PORT),
		.sin_addr = {
			.s_addr = htonl(INADDR_ANY),
		},
	};

	server_fd = zsock_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd < 0) {
		LOG_ERR("Failed to create socket: %d", errno);
		return -errno;
	}

	if (zsock_bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		LOG_ERR("Failed to bind socket: %d", errno);
		zsock_close(server_fd);
		return -errno;
	}

	if (zsock_listen(server_fd, 1) < 0) {
		LOG_ERR("Failed to listen: %d", errno);
		zsock_close(server_fd);
		return -errno;
	}

	LOG_INF("HTTP server listening on port %d", HTTP_PORT);

	while (true) {
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int client_fd = zsock_accept(server_fd, (struct sockaddr *)&client_addr,
						&client_addr_len);

		if (client_fd < 0) {
			LOG_ERR("Failed to accept connection: %d", errno);
			k_sleep(K_MSEC(100));
			continue;
		}

		LOG_INF("Client connected");

		char recv_buf[RECV_BUF_SIZE];
		ssize_t received = zsock_recv(client_fd, recv_buf, sizeof(recv_buf) - 1, 0);
		if (received > 0) {
			recv_buf[received] = '\0';
			LOG_INF("Request:\n%s", recv_buf);
		}

		ssize_t sent = zsock_send(client_fd, http_response, sizeof(http_response) - 1, 0);
		if (sent < 0) {
			LOG_ERR("Failed to send response: %d", errno);
		}

		zsock_close(client_fd);
		LOG_INF("Client disconnected");
	}

	return 0;
}

void main(void)
{
	LOG_INF("Starting W6300 HTTP server");

	(void)net_config_init_app(NULL, "Configuring network");

	if (start_http_server() < 0) {
		LOG_ERR("HTTP server failed to start");
	}
}
