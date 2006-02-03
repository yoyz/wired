CPPFLAGS = $(shell wx-config --cflags) @SAMPLERATE_CFLAGS@ -Wall -Wunused -g3

LDFLAGS = $(shell wx-config --libs) -lm @SAMPLERATE_LIBS@ -lefence

noinst_LIBRARIES = libwiredsamplerate.a

libwiredsamplerate_a_SOURCES =		\
		WiredSampleRate.cpp	\
		WiredSampleRate.h	\
		WiredSampleRateTypes.cpp