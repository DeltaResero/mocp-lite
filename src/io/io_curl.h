// src/io/io_curl.h
// SPDX-License-Identifier: GPL-3.0-or-later
//
// mocf - Music on Console Framebuffer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef IO_CURL_H
#define IO_CURL_H

#include "io/io.h"

#ifdef __cplusplus
extern "C" {
#endif

void io_curl_init ();
void io_curl_cleanup ();
void io_curl_open (struct io_stream *s, const char *url);
void io_curl_close (struct io_stream *s);
ssize_t io_curl_read (struct io_stream *s, char *buf, size_t count);
void io_curl_strerror (struct io_stream *s);
void io_curl_wake_up (struct io_stream *s);

#ifdef __cplusplus
}
#endif

#endif

// EOF
