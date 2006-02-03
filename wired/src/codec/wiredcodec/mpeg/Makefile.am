LDFLAGS = -g3 -ggdb -lefence

CPPFLAGS =  -fmessage-length=0 -funroll-all-loops -fomit-frame-pointer -falign-loops=2 -falign-jumps=2 -falign-functions=2 -ggdb

lib_LTLIBRARIES = libWiredMpeg.la

libWiredMpeg_la_SOURCES =		\
			WiredLibMpeg.cpp	

libWiredMpeg_la_LIBADD = $(DEPS_LIBS)
