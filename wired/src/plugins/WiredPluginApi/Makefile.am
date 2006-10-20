LDFLAGS = $(shell wx-config --libs) -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAkai/src/.libs/ -lWiredAkai -L../../libs/WiredAkai/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../../libs/WiredWidgets/src -I../../libs/WiredAkai/include -I../../libs/WiredAudioUtilities/src -I../../gui -I../../plugins -I../../fileloader -I../../audio -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo

if PORTAUDIO
CPPFLAGS += -I../../portaudio/include
endif


lib_LTLIBRARIES = libWiredPluginApi.la

libWiredPluginApi_la_SOURCES =				\
		src/WiredCorePlugins.h			\
		src/WiredCorePlugins.cpp		\
		src/WiredPluginStartInfo.h		\
		src/WiredPluginStartInfo.cpp		\
		src/WiredPluginGui.h			\
		src/WiredPluginGui.cpp			\
		src/WiredPluginAudio.h			\
		src/WiredPluginAudio.cpp		\
		src/WiredPluginData.h			\
		src/WiredPluginData.cpp			\
		src/WiredPlugin.h			\
		src/WiredPlugin.cpp			\
		src/WiredPluginInstaller.h



libWiredPluginApi_la_LIBADD = $(DEPS_LIBS)
