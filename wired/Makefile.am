if PORTAUDIO
SUBDIRS = src/portaudio
endif

SUBDIRS += intl po src

if PLUGINS
SUBDIRS += plugins
endif

ACLOCAL_AMFLAGS = -I config/m4

EXTRA_DIST = config/config.rpath config/m4/ChangeLog config/mkinstalldirs
