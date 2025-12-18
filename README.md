# Music on Console Framebuffer (mocf)

Music on Console Framebuffer (mocf) is a lightweight ncurses audio player
forked from Music on Console Player (mocp). Targeting minimal resource usage
for smoother playback on constrained systems, the project trims out
non-essential features to apply sane defaults for low-end, non-accelerated,
software-rendered environments like framebuffer consoles.

The interface features a dual-pane layout reminiscent of Midnight Commander.
Native directory handling allows you to simply select a file to begin playback
for the entire folder. While playlists are not required, complex queues can be
built, saved, and exported as m3u files.

### Key Features

*   Native PulseAudio backend and modern FFmpeg (> 4.0) support.
*   Integrated song rating system.
*   Inotify support for automatic directory refreshing.
*   Reworked audio formats with support for 32-bit samples and float processing.
*   Stripped non-essential features for a minimal default build.
*   Optimized defaults for software-rendered and terminal environments.

## Building and Installation

This project uses the **CMake** build system.

### Prerequisites

*   CMake 3.15 or later
*   C99 and C++17 compatible compilers
*   POSIX.1-2001 compatible system
*   **Required Libraries:** libltdl (libtool), libpopt, ncurses, pthreads.
*   **Optional Libraries:** PulseAudio, ALSA, JACK, OSS, SNDIO, libcurl,
    libsamplerate, libmagic, librcc, BerkeleyDB.
*   **Decoder Libraries:** libmad, libmpg123, libfaad2, libvorbis, opusfile,
    libflac, libmpcdec, libwavpack, libsndfile, libmodplug, ffmpeg/libav,
    libspeex, libtimidity, libsidplay2.

### Quick Start

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

### Build Options

You can configure the build by passing `-DOPTION=ON/OFF` to cmake.

#### General Options
| Option | Description | Default |
|--------|-------------|---------|
| `ENABLE_DEBUG` | Enable debugging code | `OFF` |
| `ENABLE_CACHE` | Enable tags caching code (requires BerkeleyDB) | `ON` |
| `ENABLE_INTERNAL_FLOAT` | Use float for internal processing | `OFF` |
| `ENABLE_RCC` | Enable LIBRCC support | `ON` |
| `ENABLE_CURL` | Enable network streams support | `ON` |
| `ENABLE_SAMPLERATE` | Enable libsamplerate | `ON` |
| `ENABLE_MAGIC` | Enable MIME magic support | `ON` |

#### Sound Output Options
| Option | Description | Default |
|--------|-------------|---------|
| `WITH_PULSE` | Enable PulseAudio support | `ON` |
| `WITH_ALSA` | Enable ALSA support | `ON` |
| `WITH_JACK` | Enable JACK support | `ON` |
| `WITH_OSS` | Enable OSS support | `ON` |
| `WITH_SNDIO` | Enable SNDIO support | `ON` |

#### Decoder Options
| Option | Description | Default |
|--------|-------------|---------|
| `WITH_MP3` | Enable MP3 support (libmad) | `ON` |
| `WITH_MPG123` | Enable MPG123 support | `ON` |
| `WITH_AAC` | Enable AAC support | `ON` |
| `WITH_VORBIS` | Enable Ogg Vorbis support | `ON` |
| `WITH_OPUS` | Enable Opus support | `ON` |
| `WITH_FLAC` | Enable FLAC support | `ON` |
| `WITH_MUSEPACK` | Enable Musepack support | `ON` |
| `WITH_WAVPACK` | Enable WavPack support | `ON` |
| `WITH_SNDFILE` | Enable libsndfile support | `ON` |
| `WITH_MODPLUG` | Enable libmodplug support | `ON` |
| `WITH_FFMPEG` | Enable ffmpeg/libav support | `ON` |
| `WITH_SPEEX` | Enable Speex support | `ON` |
| `WITH_TIMIDITY` | Enable libtimidity support | `ON` |
| `WITH_SIDPLAY2` | Enable libsidplay2 support | `ON` |

### Installation Directories

You can customize the installation location:

```bash
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
```

## Usage

Run the program with the `mocf` command.

```bash
mocf
```

If you need help, press `h` inside the program or read the manpage
(`man mocf`).

Configuration is stored in `~/.mocf/config`. An example configuration file is
installed to the documentation directory.

## Bug Reporting

This is a fork of the original MOC project. **Please do not report bugs for
MOCF to the original MOC developers.** This version deviates from the
original codebase and follows a different development philosophy.

## Acknowledgments

This software is a fork of the original Music on Console (MOC) project. For a
detailed history, a full list of attributions, and information on the community
forks this is based on, please see the [AUTHORS](AUTHORS) file.

## Disclaimer

This project is not affiliated with, endorsed by, nor sponsored by the
original authors of MOC.

This program is distributed under the terms of the GNU General Public
License version 3 (or later). You can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

This project is distributed in the hope that it will be useful, but
**WITHOUT ANY WARRANTY**; without even the implied warranty of
**MERCHANTABILITY** or **FITNESS FOR A PARTICULAR PURPOSE**. See the
[GNU General Public License](https://www.gnu.org/licenses/gpl-3.0.html)
for more details.
