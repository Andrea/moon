AC_INIT([moonlight], [3.99.0.2.99])

AC_DEFINE([PREVIEW_VERSION], ["3"], "")

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR(README)
AC_CANONICAL_SYSTEM

AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([1.9 dist-bzip2 tar-ustar no-dist-gzip foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_MAINTAINER_MODE

AC_SUBST([ACLOCAL_AMFLAGS], ["-I m4 \${ACLOCAL_FLAGS}"])

AC_PROG_CXX
AC_PROG_OBJC
AC_HEADER_STDC
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
DOLT
PKG_PROG_PKG_CONFIG

AC_DEFINE(__STDC_CONSTANT_MACROS, [], [To make avformat work with C++])
AC_DEFINE(__STDC_LIMIT_MACROS, [], [To get limits of specified-width integer types])

AC_SEARCH_LIBS(clock_gettime,rt)
AC_CHECK_HEADERS(sys/time.h malloc.h)

dnl ********************************************************
dnl *** libiberty.h (included by demangle.h) will define ***
dnl *** basename() unless HAVE_DECL_BASENAME is defined  ***
dnl *** to 1, so check if libc defines it.               ***
dnl ***                                                  ***
dnl *** Note: g++ defines _GNU_SOURCE                    ***
dnl ********************************************************
CFLAGS_save="$CFLAGS"
CFLAGS="$CFLAGS -D_GNU_SOURCE"
AC_CHECK_DECLS([basename])
CFLAGS="$CFLAGS_save"

changequote(,)dnl
dnl LIBTOOL="${LIBTOOL} \$(shell echo \"\$(MFLAGS)\" | awk '/^[^ ]*s/ { print \"--silent\" }')"
changequote([,])dnl

AC_CHECK_FUNCS([sigisemptyset])
AC_CHECK_FUNCS([posix_memalign])
AC_CHECK_FUNCS([pthread_rwlock_rdlock])

dnl
dnl Dependencies
dnl

PTHREAD_CHECK

MOONLIGHT_CHECK_C_COMPILER
MOONLIGHT_CHECK_LARGE_FILE
MOONLIGHT_CHECK_ZLIB
MOONLIGHT_CHECK_EXECINFO
MOONLIGHT_CHECK_EXPAT

MOONLIGHT_CHECK_MONO
MOONLIGHT_CHECK_PAL

MOONLIGHT_CHECK_FFMPEG
MOONLIGHT_CHECK_VDA
MOONLIGHT_CHECK_CODECS
MOONLIGHT_CHECK_SOUND

MOONLIGHT_CHECK_CAIRO
MOONLIGHT_CHECK_LLVM
MOONLIGHT_CHECK_GALLIUM
MOONLIGHT_CHECK_GL

MOONLIGHT_CHECK_MOZILLA

MOONLIGHT_CHECK_TESTING
MOONLIGHT_CHECK_EXAMPLES
MOONLIGHT_CHECK_BUILD_CONFIGURATION
MOONLIGHT_CHECK_FIREFOX_XPI
MOONLIGHT_CHECK_CURL
dnl the chrome check must come after curl
MOONLIGHT_CHECK_CHROME_CRX

MOONLIGHT_CHECK_UNWIND

dnl
dnl The silverlight TargetRuntime versions we claim to support

SILVERLIGHT_1_0_TARGETRUNTIME="1.0.30401.0"
SILVERLIGHT_2_0_TARGETRUNTIME="2.0.31005.0"
SILVERLIGHT_3_0_TARGETRUNTIME="3.0.50106.0"
SILVERLIGHT_4_0_TARGETRUNTIME="4.0.51204.0"
AC_SUBST(SILVERLIGHT_1_0_TARGETRUNTIME)
AC_SUBST(SILVERLIGHT_2_0_TARGETRUNTIME)
AC_SUBST(SILVERLIGHT_3_0_TARGETRUNTIME)
AC_SUBST(SILVERLIGHT_4_0_TARGETRUNTIME)

dnl
dnl Export Variables
dnl

GMCS="mono \$(abs_top_builddir)/class/lib/mcs.exe \$(CSCFLAGS) -sdk:2 -lib:\$(abs_top_builddir)/class/lib/moonlight,\$(abs_top_builddir)/class/lib/moonlight-bootstrap -d:NET_3_0"
SMCS="mono \$(abs_top_builddir)/class/lib/mcs.exe \$(CSCFLAGS) -nostdlib -lib:\$(abs_top_builddir)/class/lib/2.1 -r:mscorlib.dll -r:System.Net"
MCS="mono \$(abs_top_builddir)/class/lib/mcs.exe \$(CSCFLAGS) -lib:\$(abs_top_builddir)/class/lib/moonlight,\$(abs_top_builddir)/class/lib/moonlight-bootstrap"
AC_SUBST(GMCS)
AC_SUBST(SMCS)
AC_SUBST(MCS)

AC_PATH_PROG(GACUTIL, gacutil)
AC_SUBST([MOONLIGHT_MONO], [$MONO_PATH/mono/mini/mono])
AC_SUBST([SYSTEM_MONO], mono)
AC_PATH_PROG(ZIP, zip, no)
if test "x$ZIP" = "xno" ; then
        AC_MSG_ERROR([No zip tool found])
fi

PERF_TOOL_CFLAGS="$MONO_CFLAGS $GTK_CFLAGS $XULRUNNER_CFLAGS"
PERF_TOOL_LIBS="$MONO_LIBS $GTK_LIBS $XULRUNNER_LIBS"
AC_SUBST(PERF_TOOL_CFLAGS)
AC_SUBST(PERF_TOOL_LIBS)

MONO_LIBS="-lmono-moon -L$MONO_PATH/mono/mini -L$MONO_PATH/mono/mini/.libs"
MONO_STATIC_LIBS="$MONO_PATH/mono/mini/libmono-moon.la"
MOON_CFLAGS="$GLIB_CFLAGS $CAIRO_CFLAGS $FREETYPE2_CFLAGS $FONTCONFIG_CFLAGS $GTK_CFLAGS $ALSA_CFLAGS $PULSEAUDIO_CFLAGS $FFMPEG_CFLAGS $MONO_CFLAGS $DBUS_CFLAGS $CURL_CFLAGS"
dnl MOON_LIBS is partially defined above for the user-plugin build
MOON_LIBS="$MOON_LIBS $GLIB_LIBS $FFMPEG_LIBS $CAIRO_LIBS $FREETYPE2_LIBS $FONTCONFIG_LIBS $GTK_LIBS $ZLIB $PTHREAD_LIBS $EXPAT_LIBS $UNWIND_LIBS $DBUS_LIBS $CURL_LIBS $CODECS_LIBS"

dnl For MOON_XPI_LIBS, only link against libs which will be on all systems
MOON_XPI_LIBS="$CAIRO_LIBS $FREETYPE2_LIBS $FONTCONFIG_LIBS $GTK_LIBS $ZLIB $PTHREAD_LIBS $EXPAT_LIBS" 

# Remove glitz from the link flags (fixes Bug 338506)
MOON_LIBS="$(echo $MOON_LIBS | sed -e s/-lglitz//g)"
MOON_XPI_LIBS="$(echo $MOON_XPI_LIBS | sed -e s/-lglitz//g)"

AC_SUBST(MOON_CFLAGS)
AC_SUBST(MOON_LIBS)
AC_SUBST(MOON_XPI_LIBS)

MOON_PROG_CFLAGS="$CAIRO_CFLAGS $GTK_CFLAGS $ALSA_CFLAGS $FFMPEG_CFLAGS $PULSEAUDIO_CFLAGS $MONO_CFLAGS $DBUS_CFLAGS -I\$(top_srcdir)/src/ -I\$(top_srcdir)/src/pal"
MOON_PROG_LIBS="$GTK_LIBS $FFMPEG_LIBS $UNWIND_LIBS \$(top_builddir)/src/libmoon.la $MONO_LIBS $DBUS_LIBS $GLX_LIBS $GALLIUM_LIBS $LLVM_LIBS"
AC_SUBST(MOON_PROG_CFLAGS)
AC_SUBST(MOON_PROG_LIBS)

PLUGIN_CFLAGS="$CAIRO_CFLAGS $GTK_CFLAGS $MONO_CFLAGS -DPLUGIN_DIR=\\\"\$(pkglibdir)\\\""
PLUGIN_LIBS="$GTK_LIBS $MONO_STATIC_LIBS $GLX_LIBS $GALLIUM_LIBS $LLVM_LIBS $FFMPEG_LIBS"
PLUGIN_XPI_LIBS="$GTK_LIBS $MONO_STATIC_LIBS $GLX_LIBS $GALLIUM_LIBS $LLVM_LIBS $FFMPEG_LIBS"

AC_SUBST(PLUGIN_CFLAGS)
AC_SUBST(PLUGIN_LIBS)
AC_SUBST(PLUGIN_XPI_LIBS)

LOADER_LIBS="$GLIB_LIBS"
AC_SUBST(LOADER_LIBS)

DOCDIR=$(pkg-config --variable=sourcesdir monodoc)

if test x$with_ff4 = xyes; then
   MOZILLA_CFLAGS=$FF4_CFLAGS
elif test x$with_ff3 = xyes; then
   MOZILLA_CFLAGS=$FF3_CFLAGS
else
   MOZILLA_CFLAGS=$FF2_CFLAGS
fi

SHOCKER_CFLAGS="$MOON_PROG_CFLAGS $MOZILLA_CFLAGS $IMAGEMAGICK_CFLAGS $XTST_CFLAGS"
SHOCKER_LIBS="$IMAGEMAGICK_LIBS $XTST_LIBS"
AC_SUBST(SHOCKER_CFLAGS)
AC_SUBST(SHOCKER_LIBS)

LUNAR_LAUNCHER_CFLAGS="$CAIRO_CFLAGS $GTK_CFLAGS $MONO_CFLAGS -DPLUGIN_DIR=\\\"\$(pkglibdir)\\\""
LUNAR_LAUNCHER_LIBS="$GTK_LIBS"
AC_SUBST(LUNAR_LAUNCHER_CFLAGS)
AC_SUBST(LUNAR_LAUNCHER_LIBS)

AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)

AC_OUTPUT([
moon.pc
moonlight.spec
Makefile
m4/Makefile
src/Makefile
runtime/Makefile
gallium/Makefile
class/Makefile
class/tuning/Makefile
class/SecurityAttributes/Makefile
class/System.Windows/Makefile
class/System.Windows.Browser/Makefile
class/System.Windows.Controls/Makefile
class/System.Windows.Controls.Data/Makefile
class/Moon.Windows.Desktop/Makefile
scripts/Makefile
scripts/smcs
gtk/Makefile
man/Makefile
data/Makefile
test/Makefile
test/2.0/Makefile
test/2.0/FakeA11yBridge/Makefile
test/2.0/moon-unit/Makefile
test/2.0/Mono.Moonlight.UnitTesting/Makefile
test/2.0/Microsoft.Silverlight.Testing/Makefile
test/2.0/Microsoft.VisualStudio.QualityTools.UnitTesting.Silverlight/Makefile
test/2.0/Microsoft.SilverlightControls/Makefile
test/2.0/Microsoft.SilverlightControls/Controls.Test.Common/Makefile
test/2.0/Microsoft.SilverlightControls/Controls.Data.Test/Makefile
test/2.0/Microsoft.SilverlightControls/Controls.Extended.Test/Makefile
test/2.0/Microsoft.SilverlightControls/site/Makefile
test/harness/Makefile
test/harness/shocker/Makefile
test/leak/Makefile
tools/Makefile
tools/mopen/Makefile
tools/mxap/Makefile
tools/munxap/Makefile
tools/unsign/Makefile
tools/xamlg/Makefile
tools/xaml2html/Makefile
tools/respack/Makefile
tools/moonvisi/Makefile
tools/sockpol/Makefile
examples/Makefile
examples/desklet/Makefile
examples/desklet/calculator/Makefile
examples/desklet/cpumonitor/Makefile
examples/desklet/glassyclock/Makefile
examples/desklet/glassymonitor/Makefile
examples/desklet/glassyslides/Makefile
examples/desklet/ruler/Makefile
examples/desklet/simpleclock/Makefile
plugin/Makefile
plugin/silverlight-versions.h
plugin/firefox/Makefile
plugin/firefox/ff2/Makefile
plugin/firefox/ff3/Makefile
plugin/install/Makefile
plugin/install/install.rdf
plugin/install/manifest.json
plugin/test/Makefile
plugin/samples/Makefile
plugin/lunar-launcher/Makefile
sdk/Makefile
generators/Makefile
])

# general configuration info
cat <<EOF
Moonlight configuration
=======================

  General configuration:
	Using cairo: $with_cairo
	Using LLVM: $enable_llvm
	Using GLX: $with_glx
	Using EGL: $with_egl
	Using CGL: $with_cgl
	OpenGL Support: $with_gl
	Test Harness: $with_testing $testing_reason
	Performance Suite: $with_performance $performance_reason
	MonoDevelop SDK: $enable_sdk $sdk_reason
EOF

if test x$with_manual_mono = xyes; then
cat <<EOF
	Building mono: no
		For manual and build only modes, make sure mono is configured with --with-moonlight=yes
		Warning: you'll need to build mono yourself. Check the README for more information

EOF
elif test x$with_manual_mono = xbuild; then
cat <<EOF
	Building mono: yes, build only
		For manual and build only modes, make sure mono is configured with --with-moonlight=yes
		Check the README for more information

EOF
else
cat <<EOF
	Building mono: yes
EOF
fi

if test x$with_gallium_path = xno; then
cat <<EOF
	Building gallium: no
		Warning: pixel shader support disabled. Check the README for more information
EOF
elif test x$with_manual_gallium = xyes; then
cat <<EOF
	Building gallium: no
                Warning: you'll need to build gallium yourself. Check the README for more information
EOF
elif test x$with_manual_gallium = xbuild; then
cat <<EOF
	Building gallium: yes, build only
EOF
else
cat <<EOF
	Building gallium: yes
EOF
fi

dnl debug info
cat <<EOF

  Debug configuration: $with_debug
	Sanity checks: $with_sanity_checks
	Object tracking: $with_object_tracking
	Heap Visualization: $with_heap_visualization
	Logging support with MOONLIGHT_DEBUG: $with_logging
	libunwind available for logging: $with_unwind
EOF

# media info
cat <<EOF

  Media Support: $media_warning
	FFmpeg: $with_ffmpeg $ffmpeg_reason
	VDA: $with_vda
	ALSA: $with_alsa $alsa_reason
	PulseAudio: $with_pulseaudio $pulseaudio_reason
	OpenSLES: $with_opensles $opensles_reason
EOF

# silverlight version info
cat <<EOF

  Silverlight Support:
EOF

cat <<EOF
          Browser plugin assemblies: $browser_support $browser_reason
EOF
if test x$browser_support = xyes; then
cat <<EOF
            Path to mcs tree: $with_mcs_path
            Path to mono tree: $with_mono_path
            Path to mono-basic tree: $with_mono_basic_path
EOF
fi

# codec support
cat <<EOF
            Path to codecs: $codec_message
EOF
if test x$MOONLIGHT_CODEC_ARCH = xunknown; then
cat << EOF
                The codec pack has not been ported to this architecture yet
EOF
fi
if test x$MOONLIGHT_CODEC_OSTYPE = xunknown; then
cat << EOF
                The codec pack has not been ported to this operating system yet
EOF
fi

cat <<EOF
          Desktop application assemblies: $desktop_support $desktop_reason
EOF

# plugin installer/bridge info
cat <<EOF

  Browser Support:
	Firefox: $with_mozilla
EOF

if test x$with_mozilla = xyes; then
cat <<EOF
          Plugin Installer (.xpi): $user_plugin
          Gecko 1.8 (Firefox 2): $with_ff2 $ff2_reason
          Gecko 1.9 (Firefox 3): $with_ff3 $ff3_reason
          Gecko 2.0 (Firefox 4): $with_ff4 $ff4_reason
EOF
fi

cat <<EOF
	Fallback bridge support:
          Curl bridge: $with_curl $curl_reason
EOF

cat <<EOF
        Chrome (.crx): $chrome_extension $chrome_reason
EOF

# PAL support
cat <<EOF

  Platform abstraction layer:
	Windowing system: $pal_windowing
	Messaging layer: $pal_messaging
	NetworkAvailability layer: $pal_networking
        Capture Service: $pal_capture
	    Video capture backends: $pal_video_capture
	    Audio capture backends: $pal_audio_capture
        Font Service: $pal_font_service
EOF

# blank line
cat <<EOF

EOF
