// src/ui/curses/lyrics.h
// SPDX-License-Identifier: GPL-3.0-or-later
//
// mocf - Music on Console Framebuffer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef LYRICS_H
#define LYRICS_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef lists_t_strs *lyrics_t_formatter(lists_t_strs *lines, int height,
                                           int width, void *data);
  typedef void lyrics_t_reaper(void *data);

  lists_t_strs *lyrics_lines_get(void);
  void lyrics_lines_set(lists_t_strs *lines);
  lists_t_strs *lyrics_load_file(const char *filename);
  void lyrics_autoload(const char *filename);
  void lyrics_use_formatter(lyrics_t_formatter, lyrics_t_reaper, void *data);
  lists_t_strs *lyrics_format(int height, int width);
  void lyrics_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif

// EOF
