// src/library/rcc.h
// SPDX-License-Identifier: GPL-3.0-or-later
//
// mocf - Music on Console Framebuffer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef RCC_H
#define RCC_H

#ifdef __cplusplus
extern "C"
{
#endif

  char *rcc_reencode(char *);
  void rcc_init();
  void rcc_cleanup();

#ifdef __cplusplus
}
#endif

#endif

// EOF
