This is fork of MOC (Music on Console) which tries to follow closely upstream development but includes several experimental features.

# List of major changes in master branch

## General changes

1. Reworked audio formats including support for 32 bit samples, higher configurability of allowed formats and configure time restriction of float computing for machines w/o FPU
1. Song ratings pulled from https://github.com/hilgenberg/moc.
1. MPRIS support: possibility to control MOC by outside apps or widgets
1. Better multichannel support, including downmixing 5.1 -> 2.0 and decoder support
1. Resampling changes - tri-valued option EnableResample replacing ForceResample
1. Possibility to use "~" in some options in config file
1. Playlist behaviour changes - possibility to automatically enable shuffle for playlist and exporting relative playlists
1. Inotify support: refresh directory on content change
1. Lyrics option changes - AutoloadLyrics does what it would be expected to do - preload lyrics

## Backend changes

1. Pulseaudio backend pulled from https://github.com/xdch47/moc
1. Logarithmic audio scaling both in ALSA and in softmixer

## Decoder changes

1. mp3 decoder using libmpg123
1. Native Opus decoder using libopusfile
1. Upgraded sndfile decoder - support for other sample formats and partial BPS reporting
1. FFmpeg > 4 support pulled from https://github.com/xdch47/moc (along with other minor fixes)
1. multichannel output from Wavpack and FFmpeg decoders

# Branches

There are several even more experimental branches (often outdated), including:
* speex - introduces two new resampling methods: one is using speex and the other soxr.

# Contact

Prefered method of contact for reporting bugs or requesting some features is to create at https://gitlab.com/tomaszg/mocp/-/issues. You can also use my email from Gitlab profile.

Do not submit a bug at https://moc.daper.net/ unless you are positive that the problem is not related to changes introduced in this fork.
