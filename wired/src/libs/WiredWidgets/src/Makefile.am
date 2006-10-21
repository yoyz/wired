LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../../../gui -I../../../plugins/WiredPluginApi/include -I../../../fileloader -I../../../sequencer -I../../../engine -I../../../mixer -I../../../midi -I../../../midi/portmidi/pm_common -I../../../midi/portmidi/porttime -I../../../asm -I../../../editmidi -I../../../undo

lib_LTLIBRARIES = libWiredWidgets.la

instdir = $(includedir)
inst_HEADERS = 					\
		../include/WiredWidgets.h	\
		../include/ChoiceButton.h	\
		../include/CycleKnob.h		\
		../include/DownButton.h		\
		../include/FaderCtrl.h		\
		../include/HintedFader.h	\
		../include/HintedKnob.h		\
		../include/Hint.h		\
		../include/HoldButton.h		\
		../include/IdButton.h		\
		../include/KnobCtrl.h		\
		../include/StaticBitmap.h	\
		../include/StaticPosKnob.h	\
		../include/VUMCtrl.h



libWiredWidgets_la_SOURCES = 		\
		ChoiceButton.cpp	\
		ChoiceButton.h		\
		DownButton.cpp		\
		DownButton.h		\
		FaderCtrl.cpp		\
		FaderCtrl.h		\
		HoldButton.cpp		\
		HoldButton.h		\
		IdButton.cpp		\
		IdButton.h		\
		KnobCtrl.cpp		\
		KnobCtrl.h		\
		StaticBitmap.cpp	\
		StaticBitmap.h		\
		VUMCtrl.cpp		\
		VUMCtrl.h		\
		Hint.cpp		\
		Hint.h			\
		HintedKnob.cpp		\
		HintedKnob.h		\
		StaticPosKnob.cpp	\
		StaticPosKnob.h		\
		CycleKnob.cpp		\
		CycleKnob.h
