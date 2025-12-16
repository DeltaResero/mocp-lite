// src/audio/decoders/mp3/xing.h
// SPDX-License-Identifier: GPL-3.0-or-later
//
// mocf - Music on Console Framebuffer
// mad - MPEG audio decoder
// Copyright (C) 2000-2001 Robert Leslie
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef XING_H
#define XING_H

#include "mad.h"

struct xing
{
  long flags;			/* valid fields (see below) */
  unsigned long frames;		/* total number of frames */
  unsigned long bytes;		/* total number of bytes */
  unsigned char toc[100];	/* 100-point seek table */
  long scale;			/* ?? */
};

enum
{
  XING_FRAMES = 0x00000001L,
  XING_BYTES  = 0x00000002L,
  XING_TOC    = 0x00000004L,
  XING_SCALE  = 0x00000008L
};

void xing_init (struct xing *);

#define xing_finish(xing)	/* nothing */

int xing_parse (struct xing *, struct mad_bitptr, unsigned int);

#endif

// EOF
