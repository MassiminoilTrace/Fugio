#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T11:12:52
#
#-------------------------------------------------

include( ../../FugioGlobal.pri )

QT       += widgets

TARGET = $$qtLibraryTarget(fugio-videocapture)
TEMPLATE = lib
CONFIG += plugin c++11

DESTDIR = $$DESTDIR/plugins

SOURCES += videocaptureplugin.cpp \
	videocapturenode.cpp \
	devicedialog.cpp

HEADERS += videocaptureplugin.h \
	../../include/fugio/nodecontrolbase.h \
	../../include/fugio/pincontrolbase.h \
	../../include/fugio/videocapture/uuid.h \
	videocapturenode.h \
	devicedialog.h

FORMS += \
	devicedialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS = \
	translations/fugio_videocapture_de.ts \
	translations/fugio_videocapture_es.ts \
	translations/fugio_videocapture_fr.ts

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

	CONFIG(debug,debug|release) {
		QMAKE_POST_LINK += echo

		LIBCHANGEDEST = $$DESTLIB
	}

	CONFIG(release,debug|release) {
		QMAKE_POST_LINK += echo

		LIBCHANGEDEST = $$DESTLIB

		QMAKE_POST_LINK += $$qtLibChange( QtWidgets )
		QMAKE_POST_LINK += $$qtLibChange( QtGui )
		QMAKE_POST_LINK += $$qtLibChange( QtCore )

		QMAKE_POST_LINK += && defaults write $$absolute_path( "Contents/Info", $$BUNDLEDIR ) CFBundleExecutable "lib"$$TARGET".dylib"

		isEmpty( CASKBASE ) {
			QMAKE_POST_LINK += && macdeployqt $$BUNDLEDIR -always-overwrite -no-plugins

#			QMAKE_POST_LINK += && $$FUGIO_ROOT/Fugio/mac_fix_libs.sh $$FRAMEWORKDIR
			QMAKE_POST_LINK += && $$FUGIO_ROOT/Fugio/mac_fix_libs.sh $$BUNDLEDIR/Contents/MacOS
		}

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
# video_capture

macx:exists( $$(LIBS)/video_capture/install/mac-clang-x86_64/include/videocapture/Capture.h ) {
	INCLUDEPATH += $$(LIBS)/video_capture/install/mac-clang-x86_64/include

	LIBS += -L$$(LIBS)/video_capture/install/mac-clang-x86_64/lib -lvideocapture

	LIBS += -framework Cocoa -framework Carbon -framework CoreMedia -framework CoreVideo -framework AVFoundation

	DEFINES += VIDEOCAPTURE_SUPPORTED
}

windows:contains( QT_ARCH, i386 ):exists( $$(LIBS)/video_capture/build ) {
	INCLUDEPATH += $$(LIBS)/video_capture/include

	CONFIG(debug,debug|release) {
		LIBS += -L$$(LIBS)/video_capture/build/Debug
	} else {
		LIBS += -L$$(LIBS)/video_capture/build/Release
	}

	LIBS += -lvideocapture

	LIBS += -lShlwapi -lOle32 -lMfplat -lMf -lMfuuid -lMfreadwrite

	DEFINES += VIDEOCAPTURE_SUPPORTED
}

linux:!macx:exists( $$(LIBS)/video_capture/install/linux-gcc-x86_64/include/videocapture/Capture.h ) {
	INCLUDEPATH += $$(LIBS)/video_capture/install/linux-gcc-x86_64/include

	LIBS += -L$$(LIBS)/video_capture/install/linux-gcc-x86_64/lib -lvideocapture

#	LIBS += -framework Cocoa -framework Carbon -framework CoreMedia -framework CoreVideo -framework AVFoundation

	DEFINES += VIDEOCAPTURE_SUPPORTED
}

!contains( DEFINES, VIDEOCAPTURE_SUPPORTED ) {
	warning( "videocapture not supported" )
}

#------------------------------------------------------------------------------
# API

INCLUDEPATH += $$PWD/../../include
