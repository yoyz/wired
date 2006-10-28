SUBDIRS =				\
	gui 				\
	fileloader			\
	sequencer 			\
	audio				\
	editmidi			\
	engine 				\
	midi 				\
	mixer 				\
	undo 				\
	libs				\
	plugins				\
	data				\
	conf				\
	xml				\
	samplerate			\
	codec				\
	wiredvideo

DEPS_LIBS = plugins/WiredPluginApi/src/.libs/libWiredPluginApi.so libs/WiredWidgets/src/.libs/libWiredWidgets.so libs/WiredAkai/src/.libs/libWiredAkai.so libs/WiredAkai/src/.libs/libWiredAudioUtilities.so

wired_LDFLAGS = $(shell wx-config --libs) -lsndfile -lasound -Lmidi/portmidi $(DEPS_LIBS) -Lfileloader -lfileloader `xml2-config --libs` @SAMPLERATE_LIBS@ -lportaudio

wired_CPPFLAGS = $(shell wx-config --cflags) -Igui -Iplugins -Ifileloader -Isequencer -Iaudio -Iengine -Imixer -Imidi -Imidi/portmidi/pm_common -Imidi/portmidi/porttime -I. -Iasm -Ieditmidi -Iundo `xml2-config --cflags` @SAMPLERATE_CFLAGS@

if PORTAUDIO
wired_LDFLAGS += -Lportaudio/lib/.libs/
endif

bin_PROGRAMS = wired

wired_SOURCES =

wired_LDADD =					\
	gui/libgui.a				\
	sequencer/libsequencer.a		\
	audio/libaudio.a			\
	editmidi/libeditmidi.a			\
	engine/libengine.a			\
	fileloader/libfileloader.a		\
	midi/libmidi.a				\
	midi/portmidi/libportmidi.a		\
	midi/portmidi/porttime/libporttime.a	\
	mixer/libmixer.a			\
	undo/libundo.a				\
	xml/libwiredxml.a			\
	samplerate/libwiredsamplerate.a		\
	codec/libwiredCodec.a			\
	wiredvideo/libwiredvideo.a		\
	plugins/dssi/libwireddssi.a
