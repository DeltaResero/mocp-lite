// src/library/ratings.h
// SPDX-License-Identifier: GPL-3.0-or-later
//
// mocf - Music on Console Framebuffer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef RATINGS_H
#define RATINGS_H

#include "library/playlist.h"

#ifdef __cplusplus
extern "C" {
#endif

/* store ratings for a file */
bool ratings_write_file (const char *fn, int rating);

/* read ratings for a file */
void ratings_read_file (const char *fn, struct file_tags *tags);

#ifdef __cplusplus
}
#endif

#endif

// EOF
