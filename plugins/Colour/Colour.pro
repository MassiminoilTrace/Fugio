#-------------------------------------------------
#
# Project created by QtCreator 2013-04-16T09:48:22
#
#-------------------------------------------------

include( ../../FugioGlobal.pri )

QT += gui widgets

TARGET = $$qtLibraryTarget(fugio-colour)
TEMPLATE = lib
CONFIG += plugin
CONFIG += c++11

DESTDIR = $$DESTDIR/plugins

SOURCES += \
	colourbutton.cpp \
	colourpin.cpp \
	colourplugin.cpp \
	splitcolourhslanode.cpp \
	splitcolourrgbanode.cpp \
	joincolourrgbanode.cpp \
	joincolourhslanode.cpp \
	colourbuttonnode.cpp

HEADERS += \
	../../include/fugio/colour/uuid.h \
	../../include/fugio/colour/colour_interface.h \
	../../include/fugio/nodecontrolbase.h \
	../../include/fugio/pincontrolbase.h \
	colourbutton.h \
	colourpin.h \
	colourplugin.h \
	splitcolourhslanode.h \
	splitcolourrgbanode.h \
	joincolourrgbanode.h \
	joincolourhslanode.h \
	colourbuttonnode.h

RESOURCES += \
    resources.qrc

TRANSLATIONS = \
	translations/fugio_colour_de.ts \
	translations/fugio_colour_es.ts \
	translations/fugio_colour_fr.ts

#------------------------------------------------------------------------------
# OSX plugin bundle

macx {
	DEFINES += TARGET_OS_MAC
	CONFIG -= x86
	CONFIG += lib_bundle

	BUNDLEDIR    = $$DESTDIR/$$TARGET".bundle"
	INSTALLDEST  = $$INSTALLDATA/plugins
	INCLUDEDEST  = $$INSTALLDATA/include/fugio

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
