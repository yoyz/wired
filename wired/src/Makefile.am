SUBDIRS =				\
	save				\
	gui 				\
	fileloader			\
	sequencer 			\
	audio				\
	editmidi			\
	engine 				\
	midi 				\
	mixer 				\
	redist 				\
	undo 				\
	libs				\
	plugins				\
	data				\
	conf				\
	xml				\
	samplerate			\
	codec				\
	dssi

if VIDEO
SUBDIRS+=\
	wiredvideo
endif

DEPS_LIBS = libs/WiredWidgets/src/.libs/libWiredWidgets.so \
	    libs/WiredAkai/src/.libs/libWiredAkai.so

WIRED_SYSTEM_LIBS = $(shell wx-config --libs) \
	$(shell pkg-config portaudio-2.0 --libs) \
	$(shell xml2-config --libs) \
	@SAMPLERATE_LIBS@ \
	-lsndfile

LIBS += $(WIRED_SYSTEM_LIBS) $(DEPS_LIBS)

wired_LDFLAGS = -rpath ${libdir}/wired -Wl,--no-as-needed

wired_CPPFLAGS = $(shell wx-config --cflags) \
		 $(shell xml2-config --cflags) \
		@SAMPLERATE_CFLAGS@ \
		-Igui -Iplugins -Ifileloader -Isequencer -Iredist \
		-Iaudio -Iengine -Imixer -Iundo \
		-Imidi -Ieditmidi

bin_PROGRAMS = wired

CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(wired_LDFLAGS) $(LDFLAGS) -o $@
wired_LINK = $(CXXLINK)

wired_SOURCES =

wired_LDADD =					\
	save/libsave.la				\
	gui/libgui.a				\
	sequencer/libsequencer.a		\
	audio/libaudio.a			\
	editmidi/libeditmidi.a			\
	engine/libengine.a			\
	fileloader/libfileloader.a		\
	midi/libmidi.a				\
	mixer/libmixer.a			\
	plugins/libplugins.a			\
	redist/libredist.a			\
	undo/libundo.a				\
	xml/libwiredxml.a			\
	samplerate/libwiredsamplerate.a		\
	codec/libwiredCodec.a			\
	dssi/libwireddssi.a
if VIDEO
wired_LDADD +=\
	wiredvideo/libwiredvideo.a
endif

if PORTMIDI
wired_CPPFLAGS += -Imidi/portmidi/pm_common -Imidi/portmidi/porttime
wired_LDADD +=\
	midi/portmidi/libportmidi.a		\
	midi/portmidi/porttime/libporttime.a	\
	-lasound -Lmidi/portmidi
else
wired_LDADD += -lportmidi -lporttime
endif
