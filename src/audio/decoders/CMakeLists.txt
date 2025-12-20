set(DECODER_PLUGINS "")

# Helper function to create decoder plugin
function(add_decoder_plugin NAME)
  set(options "")
  set(oneValueArgs "")
  set(multiValueArgs SOURCES LIBRARIES INCLUDE_DIRS COMPILE_DEFINITIONS)
  cmake_parse_arguments(PLUGIN "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN})

  add_library(${NAME}_decoder MODULE ${PLUGIN_SOURCES})
  target_include_directories(${NAME}_decoder PRIVATE ${CMAKE_SOURCE_DIR}/src
                                                     ${PLUGIN_INCLUDE_DIRS})
  target_link_libraries(${NAME}_decoder PRIVATE ${PLUGIN_LIBRARIES})
  if(PLUGIN_COMPILE_DEFINITIONS)
    target_compile_definitions(${NAME}_decoder
                               PRIVATE ${PLUGIN_COMPILE_DEFINITIONS})
  endif()

  set_target_properties(${NAME}_decoder
                        PROPERTIES PREFIX "lib" OUTPUT_NAME "${NAME}_decoder")

  install(TARGETS ${NAME}_decoder
          LIBRARY DESTINATION ${PLUGIN_DIR}/${DECODER_PLUGIN_DIR})

  list(APPEND DECODER_PLUGINS ${NAME})
  set(DECODER_PLUGINS
      ${DECODER_PLUGINS}
      PARENT_SCOPE)
endfunction()

# Check for id3tag (needed by mp3 and aac)
find_package(PkgConfig)
check_library_exists(z gzopen "" HAVE_ZLIB)
check_library_exists(id3tag id3_file_open "" HAVE_LIBID3TAG)
check_include_file(id3tag.h HAVE_ID3TAG_H)

if(HAVE_ZLIB
   AND HAVE_LIBID3TAG
   AND HAVE_ID3TAG_H)
  set(HAVE_ID3TAG TRUE)
endif()

# MP3 decoder (libmad)
if(WITH_MP3)
  check_library_exists(mad mad_stream_init "" HAVE_LIBMAD)
  check_include_file(mad.h HAVE_MAD_H)

  if(HAVE_LIBMAD
     AND HAVE_MAD_H
     AND HAVE_ID3TAG)
    add_decoder_plugin(
      mp3
      SOURCES
      mp3/mp3.c
      mp3/xing.c
      mp3/xing.h
      LIBRARIES
      mad
      id3tag
      z)
  endif()
endif()

# MPG123 decoder
if(WITH_MPG123)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(MPG123 libmpg123>=1.14)
    if(MPG123_FOUND)
      add_decoder_plugin(
        mpg123
        SOURCES
        mpg123/mpg123.c
        LIBRARIES
        ${MPG123_LIBRARIES}
        INCLUDE_DIRS
        ${MPG123_INCLUDE_DIRS})
    endif()
  endif()
endif()

# AAC decoder (libfaad2)
if(WITH_AAC)
  check_library_exists(faad NeAACDecInit "" HAVE_LIBFAAD)
  check_include_file(neaacdec.h HAVE_NEAACDEC_H)

  if(HAVE_LIBFAAD
     AND HAVE_NEAACDEC_H
     AND HAVE_ID3TAG)
    add_decoder_plugin(
      aac
      SOURCES
      aac/aac.c
      LIBRARIES
      faad
      id3tag
      z)
  endif()
endif()

# Vorbis decoder
if(WITH_VORBIS)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(VORBIS ogg>=1.0 vorbis>=1.0 vorbisfile>=1.0)
    if(VORBIS_FOUND)
      add_decoder_plugin(
        vorbis
        SOURCES
        vorbis/vorbis.c
        LIBRARIES
        ${VORBIS_LIBRARIES}
        INCLUDE_DIRS
        ${VORBIS_INCLUDE_DIRS})
    endif()
  endif()
endif()

# Opus decoder
if(WITH_OPUS)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(OPUS opusfile>=0.1)
    if(OPUS_FOUND)
      check_library_exists(opusfile op_read_float "" HAVE_OPUSFILE_FLOAT)
      set(OPUS_DEFS "")
      if(HAVE_OPUSFILE_FLOAT)
        list(APPEND OPUS_DEFS HAVE_OPUSFILE_FLOAT=1)
      endif()
      add_decoder_plugin(
        opus
        SOURCES
        opus/opus.c
        LIBRARIES
        ${OPUS_LIBRARIES}
        INCLUDE_DIRS
        ${OPUS_INCLUDE_DIRS}
        COMPILE_DEFINITIONS
        ${OPUS_DEFS})
    endif()
  endif()
endif()

# FLAC decoder
if(WITH_FLAC)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(FLAC flac>=1.1.3)
    if(FLAC_FOUND)
      add_decoder_plugin(
        flac
        SOURCES
        flac/flac.c
        LIBRARIES
        ${FLAC_LIBRARIES}
        INCLUDE_DIRS
        ${FLAC_INCLUDE_DIRS})
    endif()
  endif()
endif()

# Musepack decoder
if(WITH_MUSEPACK)
  check_include_file(mpc/mpcdec.h HAVE_MPC_MPCDEC_H)
  if(NOT HAVE_MPC_MPCDEC_H)
    check_include_file(mpcdec/mpcdec.h HAVE_MPCDEC_MPCDEC_H)
  endif()

  if(HAVE_MPC_MPCDEC_H OR HAVE_MPCDEC_MPCDEC_H)
    find_program(TAGLIB_CONFIG taglib-config)
    if(TAGLIB_CONFIG)
      execute_process(
        COMMAND ${TAGLIB_CONFIG} --version
        OUTPUT_VARIABLE TAGLIB_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE)
      execute_process(
        COMMAND ${TAGLIB_CONFIG} --cflags
        OUTPUT_VARIABLE TAGLIB_CFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      if(TAGLIB_VERSION VERSION_GREATER_EQUAL "1.3.1")
        # FIX: Apply taglib cflags to the check environment so tag_c.h can be
        # found
        set(CMAKE_REQUIRED_FLAGS "${TAGLIB_CFLAGS}")
        check_include_file(tag_c.h HAVE_TAG_C_H)
        unset(CMAKE_REQUIRED_FLAGS)

        if(HAVE_TAG_C_H)
          set(MPC_DEFS "")
          if(HAVE_MPCDEC_MPCDEC_H)
            list(APPEND MPC_DEFS MPC_IS_OLD_API=1)
          endif()

          # Parse include dirs from cflags for the target
          string(REPLACE "-I" ";" TAGLIB_INC_LIST "${TAGLIB_CFLAGS}")

          add_decoder_plugin(
            musepack
            SOURCES
            musepack/musepack.c
            LIBRARIES
            mpcdec
            tag_c
            INCLUDE_DIRS
            ${TAGLIB_INC_LIST}
            COMPILE_DEFINITIONS
            ${MPC_DEFS})
        endif()
      endif()
    endif()
  endif()
endif()

# WavPack decoder
if(WITH_WAVPACK)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(WAVPACK wavpack>=4.31)
    if(WAVPACK_FOUND)
      add_decoder_plugin(
        wavpack
        SOURCES
        wavpack/wavpack.c
        LIBRARIES
        ${WAVPACK_LIBRARIES}
        INCLUDE_DIRS
        ${WAVPACK_INCLUDE_DIRS})
    endif()
  endif()
endif()

# libsndfile decoder
if(WITH_SNDFILE)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(SNDFILE sndfile>=1.0.0)
    if(SNDFILE_FOUND)
      check_library_exists(sndfile sf_current_byterate "" HAVE_SNDFILE_BYTERATE)
      set(SNDFILE_DEFS "")
      if(HAVE_SNDFILE_BYTERATE)
        list(APPEND SNDFILE_DEFS HAVE_SNDFILE_BYTERATE=1)
      endif()
      add_decoder_plugin(
        sndfile
        SOURCES
        sndfile/sndfile.c
        LIBRARIES
        ${SNDFILE_LIBRARIES}
        INCLUDE_DIRS
        ${SNDFILE_INCLUDE_DIRS}
        COMPILE_DEFINITIONS
        ${SNDFILE_DEFS})
    endif()
  endif()
endif()

# ModPlug decoder
if(WITH_MODPLUG)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(MODPLUG libmodplug>=0.7)
    if(MODPLUG_FOUND)
      add_decoder_plugin(
        modplug
        SOURCES
        modplug/modplug.c
        LIBRARIES
        ${MODPLUG_LIBRARIES}
        INCLUDE_DIRS
        ${MODPLUG_INCLUDE_DIRS})
    endif()
  endif()
endif()

# Speex decoder
if(WITH_SPEEX)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(SPEEX ogg>=1.0 speex>=1.0.0)
    if(SPEEX_FOUND)
      add_decoder_plugin(
        speex
        SOURCES
        speex/speex.c
        LIBRARIES
        ${SPEEX_LIBRARIES}
        INCLUDE_DIRS
        ${SPEEX_INCLUDE_DIRS})
    endif()
  endif()
endif()

# Timidity decoder
if(WITH_TIMIDITY)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(TIMIDITY libtimidity>=0.1.0)
    if(TIMIDITY_FOUND)
      add_decoder_plugin(
        timidity
        SOURCES
        timidity/timidity.c
        LIBRARIES
        ${TIMIDITY_LIBRARIES}
        INCLUDE_DIRS
        ${TIMIDITY_INCLUDE_DIRS})
    endif()
  endif()
endif()

# SIDPlay2 decoder
if(WITH_SIDPLAY2)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(SIDPLAY2 libsidplay2>=2.1.1)
    pkg_check_modules(SIDUTILS libsidutils>=1.0.4)

    if(SIDPLAY2_FOUND AND SIDUTILS_FOUND)
      execute_process(
        COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=builders libsidplay2
        OUTPUT_VARIABLE SIDPLAY2_BUILDERS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      if(SIDPLAY2_BUILDERS)
        check_include_file(sidplay/builders/resid.h HAVE_RESID_H)
        if(HAVE_RESID_H)
          add_decoder_plugin(
            sidplay2
            SOURCES
            sidplay2/sidplay2.cc
            sidplay2/sidplay2.h
            LIBRARIES
            ${SIDPLAY2_LIBRARIES}
            ${SIDUTILS_LIBRARIES}
            resid-builder
            INCLUDE_DIRS
            ${SIDPLAY2_INCLUDE_DIRS}
            ${SIDUTILS_INCLUDE_DIRS})
          target_link_directories(sidplay2_decoder PRIVATE ${SIDPLAY2_BUILDERS})
        endif()
      endif()
    endif()
  endif()
endif()

# FFmpeg/LibAV decoder
if(WITH_FFMPEG)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(FFMPEG libavutil libavcodec libavformat)
    if(FFMPEG_FOUND)
      # Check if it's FFmpeg or LibAV
      execute_process(
        COMMAND ${PKG_CONFIG_EXECUTABLE} --modversion libavcodec
        OUTPUT_VARIABLE AVCODEC_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      string(REGEX MATCH "^[0-9]+" AVCODEC_MAJOR "${AVCODEC_VERSION}")
      string(REGEX MATCH "\\.[0-9]+" AVCODEC_MINOR_MATCH "${AVCODEC_VERSION}")
      string(REGEX REPLACE "^\\." "" AVCODEC_MINOR "${AVCODEC_MINOR_MATCH}")

      if(AVCODEC_MAJOR GREATER 53 OR (AVCODEC_MAJOR EQUAL 53 AND AVCODEC_MINOR
                                                                 GREATER 47))
        set(FFMPEG_DEFS "")

        # Detect FFmpeg vs LibAV
        string(REGEX MATCH "\\.([0-9]+)$" AVCODEC_PATCH_MATCH
                     "${AVCODEC_VERSION}")
        string(REGEX REPLACE "^\\." "" AVCODEC_PATCH "${AVCODEC_PATCH_MATCH}")

        if(AVCODEC_PATCH GREATER 99)
          list(APPEND FFMPEG_DEFS HAVE_FFMPEG=1)
        else()
          list(APPEND FFMPEG_DEFS HAVE_LIBAV=1)
        endif()

        # Feature detection
        include(CheckStructHasMember)
        set(CMAKE_REQUIRED_INCLUDES ${FFMPEG_INCLUDE_DIRS})
        set(CMAKE_REQUIRED_LIBRARIES ${FFMPEG_LIBRARIES})

        check_symbol_exists(av_packet_alloc "libavcodec/avcodec.h"
                            HAVE_AV_PACKET_FNS)
        check_symbol_exists(av_frame_alloc "libavutil/frame.h"
                            HAVE_AV_FRAME_FNS)
        check_symbol_exists(avcodec_free_context "libavcodec/avcodec.h"
                            HAVE_AVCODEC_FREE_CONTEXT)
        check_symbol_exists(avcodec_receive_frame "libavcodec/avcodec.h"
                            HAVE_AVCODEC_RECEIVE_FRAME)
        check_include_file(libavutil/channel_layout.h
                           HAVE_LIBAVUTIL_CHANNEL_LAYOUT_H)

        # Critical checks for modern FFmpeg API
        check_struct_has_member(
          "struct AVStream" codecpar "libavformat/avformat.h"
          HAVE_STRUCT_AVSTREAM_CODECPAR)
        check_struct_has_member(
          "struct AVProbeData" mime_type "libavformat/avformat.h"
          HAVE_STRUCT_AVPROBEDATA_MIME_TYPE)

        if(HAVE_AV_PACKET_FNS)
          list(APPEND FFMPEG_DEFS HAVE_AV_PACKET_FNS=1)
        endif()
        if(HAVE_AV_FRAME_FNS)
          list(APPEND FFMPEG_DEFS HAVE_AV_FRAME_FNS=1)
        endif()
        if(HAVE_AVCODEC_FREE_CONTEXT)
          list(APPEND FFMPEG_DEFS HAVE_AVCODEC_FREE_CONTEXT=1)
        endif()
        if(HAVE_AVCODEC_RECEIVE_FRAME)
          list(APPEND FFMPEG_DEFS HAVE_AVCODEC_RECEIVE_FRAME=1)
        endif()
        if(HAVE_LIBAVUTIL_CHANNEL_LAYOUT_H)
          list(APPEND FFMPEG_DEFS HAVE_LIBAVUTIL_CHANNEL_LAYOUT_H=1)
        endif()
        if(HAVE_STRUCT_AVSTREAM_CODECPAR)
          list(APPEND FFMPEG_DEFS HAVE_STRUCT_AVSTREAM_CODECPAR=1)
        endif()
        if(HAVE_STRUCT_AVPROBEDATA_MIME_TYPE)
          list(APPEND FFMPEG_DEFS HAVE_STRUCT_AVPROBEDATA_MIME_TYPE=1)
        endif()

        add_decoder_plugin(
          ffmpeg
          SOURCES
          ffmpeg/ffmpeg.c
          LIBRARIES
          ${FFMPEG_LIBRARIES}
          INCLUDE_DIRS
          ${FFMPEG_INCLUDE_DIRS}
          COMPILE_DEFINITIONS
          ${FFMPEG_DEFS})
      endif()
    endif()
  endif()
endif()

# Set parent scope variable
set(DECODER_PLUGINS
    ${DECODER_PLUGINS}
    PARENT_SCOPE)
