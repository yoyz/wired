CPPFLAGS = $(shell wx-config --cflags) @SAMPLERATE_CFLAGS@ -Wall -Wunused -I ../xml/ -I ../save/ -I/usr/pkg/include `xml2-config --cflags `

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


LDFLAGS = $(shell wx-config --libs) -lm @SAMPLERATE_LIBS@

noinst_LIBRARIES = libwiredsamplerate.a

libwiredsamplerate_a_SOURCES =		\
		WiredSampleRate.cpp	\
		WiredSampleRate.h	\
		WiredSampleRateTypes.cpp