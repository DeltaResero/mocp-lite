ACLOCAL_AMFLAGS = -I m4
SUBDIRS = assets/themes src/audio/decoders
AM_CPPFLAGS = -I$(top_srcdir)/src -DSYSTEM_THEMES_DIR=\"$(pkgdatadir)/themes\" \
	      -DPLUGIN_DIR=\"$(plugindir)/$(DECODER_PLUGIN_DIR)\"

bin_PROGRAMS = mocp
mocp_SOURCES = \
	src/core/log.c \
	src/core/log.h \
	src/core/protocol.h \
	src/core/protocol.c \
	src/core/server.c \
	src/core/server.h \
	src/core/main.c \
	src/core/common.c \
	src/core/common.h \
	src/core/compiler.h \
	src/library/playlist.c \
	src/library/playlist.h \
	src/utils/fifo_buf.c \
	src/utils/fifo_buf.h \
	src/audio/outputs/out_buf.c \
	src/audio/outputs/out_buf.h \
	src/audio/audio.c \
	src/audio/audio.h \
	src/audio/decoder.c \
	src/audio/decoder.h \
	src/ui/curses/interface.c \
	src/ui/curses/interface.h \
	src/ui/curses/interface_elements.c \
	src/ui/curses/interface_elements.h \
	src/ui/curses/menu.c \
	src/ui/curses/menu.h \
	src/library/files.c \
	src/library/files.h \
	src/core/options.c \
	src/core/options.h \
	src/library/player.c \
	src/library/player.h \
	src/library/playlist_file.c \
	src/library/playlist_file.h \
	src/ui/themes.c \
	src/ui/themes.h \
	src/ui/input/keys.c \
	src/ui/input/keys.h \
	src/io/io.c \
	src/io/io.h \
	src/core/compat.c \
	src/core/compat.h \
	src/audio/conversion/audio_conversion.c \
	src/audio/conversion/audio_conversion.h \
	src/utils/rbtree.c \
	src/utils/rbtree.h \
	src/library/tags_cache.c \
	src/library/tags_cache.h \
	src/utils/utf8.c \
	src/utils/utf8.h \
	src/library/rcc.c \
	src/library/rcc.h \
	src/audio/processing/softmixer.c \
	src/audio/processing/softmixer.h \
	src/ui/curses/lyrics.h \
	src/ui/curses/lyrics.c \
	src/utils/lists.h \
	src/utils/lists.c \
	src/audio/processing/equalizer.h \
	src/audio/processing/equalizer.c \
	src/library/ratings.h \
	src/library/ratings.c \

EXTRA_mocp_SOURCES = \
	src/utils/md5.c \
	src/utils/md5.h \
	src/audio/outputs/null_out.c \
	src/audio/outputs/null_out.h \
	src/audio/outputs/sndio_out.c \
	src/audio/outputs/sndio_out.h \
	src/audio/outputs/oss.c \
	src/audio/outputs/oss.h \
	src/audio/outputs/alsa.c \
	src/audio/outputs/alsa.h \
	src/io/io_curl.c \
	src/io/io_curl.h \
	src/audio/outputs/jack.c \
	src/audio/outputs/jack.h \

EXTRA_DIST = assets/doc/README_equalizer assets/man/mocp.1 THANKS assets/doc/keymap.example Doxyfile \
	         doxy_pages/decoder_api.doxy doxy_pages/main_page.doxy \
	         doxy_pages/sound_output_driver_api.doxy
EXTRA_DIST += @EXTRA_DISTS@
EXTRA_DIST += tools/README tools/md5check.sh tools/maketests.sh
noinst_DATA = tools/README
noinst_SCRIPTS = tools/md5check.sh tools/maketests.sh

doc_DATA = assets/doc/config.example THANKS README assets/doc/README_equalizer assets/doc/keymap.example

desktopdir = $(datadir)/applications
desktop_DATA = assets/desktop/mocp.desktop

icondir = $(datadir)/icons/hicolor/scalable/apps
icon_DATA = assets/desktop/mocp.svg