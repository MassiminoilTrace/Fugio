#ifndef OPENGL_INCLUDES_H
#define OPENGL_INCLUDES_H

#if defined( Q_OS_RASPBERRY_PI )
#include <QObject>
#include <QDataStream>
#include <QTextStream>

#include <GLES3/gl31.h>
#include <GLES3/gl3.h>
//#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#undef Bool
#undef None
#undef Unsorted
#undef CursorShape
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef Expose

#else

#include <GL/glew.h>

#endif

#endif // OPENGL_INCLUDES_H
