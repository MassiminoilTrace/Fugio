#-------------------------------------------------
#
# Project created by QtCreator 2014-07-26T22:35:57
#
#-------------------------------------------------

include( ../../FugioGlobal.pri )

QT       += widgets

TARGET = $$qtLibraryTarget(fugio-midi)
TEMPLATE = lib
CONFIG += plugin
CONFIG += c++11

DESTDIR = $$DESTDIR/plugins

SOURCES += \
	midinotenode.cpp \
	midioutputhelpernode.cpp \
	midirotarynode.cpp \
	midiplugin.cpp \
	midiinputhelpernode.cpp \
	notetofrequencynode.cpp \
	frequencytonotenode.cpp \
	scalenode.cpp \
	intervalnode.cpp \
	channeloutputnode.cpp \
	channelinputnode.cpp \
	midiinputpin.cpp \
	midiinputsyncnode.cpp \
	midioutputnode.cpp \
	mididecodernode.cpp \
	midioutputpin.cpp \
	midifileloadnode.cpp \
    import/midifile.cpp \
    miditimelinenode.cpp

HEADERS += \
	../../include/fugio/nodecontrolbase.h \
	../../include/fugio/pincontrolbase.h \
	../../include/fugio/midi/midi_input_interface.h \
	../../include/fugio/midi/midi_interface.h \
	../../include/fugio/midi/uuid.h \
	midinotenode.h \
	midioutputhelpernode.h \
	midirotarynode.h \
	midiplugin.h \
	midiinputhelpernode.h \
	notetofrequencynode.h \
	frequencytonotenode.h \
	scalenode.h \
	intervalnode.h \
	channeloutputnode.h \
	channelinputnode.h \
	midiinputpin.h \
	midiinputsyncnode.h \
	midioutputnode.h \
	mididecodernode.h \
	midioutputpin.h \
	midifileloadnode.h \
    import/midifile.h \
    miditimelinenode.h

RESOURCES += \
    resources.qrc

TRANSLATIONS = \
	translations/fugio_midi_de.ts \
	translations/fugio_midi_es.ts \
	translations/fugio_midi_fr.ts

#------------------------------------------------------------------------------
# OSX plugin bundle

macx {
	DEFINES += TARGET_OS_MAC
	CONFIG -= x86
	CONFIG += lib_bundle

	BUNDLEDIR    = $$DESTDIR/$$TARGET".bundle"
	INSTALLDEST  = $$INSTALLDATA/plugins
	INCLUDEDEST  = $$INSTALLDATA/include/fugio
	FRAMEWORKDIR = $$BUNDLEDIR/Contents/Frameworks

	DESTDIR = $$BUNDLEDIR/Contents/MacOS
	DESTLIB = $$DESTDIR/"lib"$$TARGET".dylib"

	CONFIG(release,debug|release) {
		QMAKE_POST_LINK += echo

		LIBCHANGEDEST = $$DESTLIB

		QMAKE_POST_LINK += $$qtLibChange( QtWidgets )
		QMAKE_POST_LINK += $$qtLibChange( QtGui )
		QMAKE_POST_LINK += $$qtLibChange( QtCore )

		QMAKE_POST_LINK += && defaults write $$absolute_path( "Contents/Info", $$BUNDLEDIR ) CFBundleExecutable "lib"$$TARGET".dylib"

		QMAKE_POST_LINK += && macdeployqt $$BUNDLEDIR -always-overwrite -no-plugins

		plugin.path = $$INSTALLDEST
		plugin.files = $$BUNDLEDIR
		plugin.extra = rm -rf $$INSTALLDEST/$$TARGET".bundle"

		INSTALLS += plugin
	}
}

#------------------------------------------------------------------------------
# Windows Install

windows {
	plugin.path  = $$INSTALLDATA/plugins
	plugin.files = $$DESTDIR/$$TARGET".dll"

	INSTALLS += plugin
}

#------------------------------------------------------------------------------
# Linux

unix:!macx {
    target.path = $$INSTALLBASE/usr/lib/fugio

    INSTALLS += target
}

#------------------------------------------------------------------------------
# API

INCLUDEPATH += $$PWD/../../include
