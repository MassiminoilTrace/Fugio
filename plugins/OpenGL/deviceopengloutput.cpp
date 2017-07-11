#include "deviceopengloutput.h"

#include <QCoreApplication>
#include <QDebug>
#include <QResizeEvent>

#include <QGuiApplication>
#include <QScreen>

#include <fugio/render_interface.h>
#include <fugio/node_control_interface.h>

#include <fugio/context_interface.h>

#include <fugio/global_interface.h>

#include "openglplugin.h"
#include "windownode.h"

//#define OPENGL_DEBUG_ENABLE

QOpenGLDebugLogger			*DeviceOpenGLOutput::mDebugLogger = nullptr;

void DeviceOpenGLOutput::deviceInitialise()
{
}

void DeviceOpenGLOutput::deviceDeinitialise()
{
}

void DeviceOpenGLOutput::devicePacketStart( qint64 pTimeStamp )
{
	Q_UNUSED( pTimeStamp )
}

void DeviceOpenGLOutput::devicePacketEnd()
{
}

#include <QApplication>

QSharedPointer<DeviceOpenGLOutput> DeviceOpenGLOutput::newDevice( bool pContextOnly )
{
	QSharedPointer<DeviceOpenGLOutput>	NewDev;

	NewDev = QSharedPointer<DeviceOpenGLOutput>( new DeviceOpenGLOutput() );

	if( NewDev )
	{
		NewDev->setTitle( "Fugio OpenGL Output" );

		NewDev->setWidth( 640 );
		NewDev->setHeight( 480 );

		NewDev->show();

		if( !OpenGLPlugin::hasContextStatic() )
		{
//			QCoreApplication::processEvents();
		}

#if defined( OPENGL_DEBUG_ENABLE )
		if( !mDebugLogger )
		{
			if( ( mDebugLogger = new QOpenGLDebugLogger( NewDev.data() ) ) != nullptr )
			{
				if( mDebugLogger->initialize() )
				{
					connect( mDebugLogger, &QOpenGLDebugLogger::messageLogged, NewDev.data(), &DeviceOpenGLOutput::handleLoggedMessage );

					mDebugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
				}
			}
		}
#endif

		if( pContextOnly )
		{
			NewDev->hide();
		}
	}

	return( NewDev );
}

//-----------------------------------------------------------------------------
// Instance

DeviceOpenGLOutput::DeviceOpenGLOutput( void )
	: mInputEvents( nullptr ), mUpdatePending( false )
{
}

DeviceOpenGLOutput::~DeviceOpenGLOutput( void )
{
}

QSize DeviceOpenGLOutput::windowSize() const
{
	return( size() );
}

QSize DeviceOpenGLOutput::framebufferSize() const
{
	return( QSize( width() * devicePixelRatio(), height() * devicePixelRatio() ) );
}

void DeviceOpenGLOutput::initializeGL()
{
}

void DeviceOpenGLOutput::resizeGL( int w, int h )
{
	emit resized( QSize( w, h ) );

	update();
}

void DeviceOpenGLOutput::paintGL()
{
	renderNow();
}

void DeviceOpenGLOutput::setCurrentNode( QSharedPointer<fugio::NodeInterface> pNode )
{
	mNode = pNode;
}

void DeviceOpenGLOutput::unsetCurrentNode( QSharedPointer<NodeInterface> pNode )
{
	QSharedPointer<fugio::NodeInterface>	CurNod = mNode.toStrongRef();

	if( CurNod && CurNod != pNode )
	{
		return;
	}

	mNode.clear();

	mInputEvents = nullptr;
}

void DeviceOpenGLOutput::setGeometry( QRect pRect )
{

}

bool DeviceOpenGLOutput::event( QEvent *pEvent )
{
	if( QInputEvent *InputEvent = dynamic_cast<QInputEvent *>( pEvent ) )
	{
		if( mInputEvents )
		{
			mInputEvents->inputProcessEvent( InputEvent );
		}
	}

	return( QOpenGLWindow::event( pEvent ) );
}

void DeviceOpenGLOutput::renderNow()
{
	QSharedPointer<fugio::NodeInterface>	CurNod = mNode.toStrongRef();

	if( CurNod )
	{
		fugio::RenderInterface	*N = qobject_cast<fugio::RenderInterface *>( CurNod->control()->qobject() );

		if( N )
		{
			N->render( CurNod->context()->global()->timestamp() );
		}
	}

	mUpdatePending = false;
}

bool DeviceOpenGLOutput::renderInit()
{
	return( true );
}

void DeviceOpenGLOutput::renderStart()
{
}

void DeviceOpenGLOutput::renderEnd()
{
}

void DeviceOpenGLOutput::renderLater()
{
	mUpdatePending = true;

	update();
}

void DeviceOpenGLOutput::signalUpdate()
{
	QSharedPointer<fugio::NodeInterface>	CurNod = mNode.toStrongRef();

	if( CurNod )
	{
		CurNod->context()->updateNode( CurNod );
	}
}

void DeviceOpenGLOutput::screengrab()
{
	QSharedPointer<fugio::NodeInterface>	CurNod = mNode.toStrongRef();

	if( CurNod )
	{
		OutputInterface		*Output = qobject_cast<OutputInterface *>( CurNod->control()->qobject() );

		if( Output != 0 )
		{
			Output->screengrab();
		}
	}
}

void DeviceOpenGLOutput::handleLoggedMessage( const QOpenGLDebugMessage &pDebugMessage )
{
	qDebug() << pDebugMessage;
}

#if 0
void DeviceOpenGLOutput::mousePressEvent( QMouseEvent *pEvent )
{
	if( pEvent->button() == Qt::LeftButton )
	{
		QSharedPointer<fugio::NodeInterface>	CurNod = mNode.toStrongRef();

		if( CurNod != 0 )
		{
			InterfaceOutput		*Output = qobject_cast<InterfaceOutput *>( CurNod->control()->object() );

			if( Output != 0 )
			{
				Output->buttonLeftPressed( true );
			}
		}
	}

	QWindow::mousePressEvent( pEvent );
}

void DeviceOpenGLOutput::mouseReleaseEvent( QMouseEvent *pEvent )
{
	if( pEvent->button() == Qt::LeftButton )
	{
		QSharedPointer<fugio::NodeInterface>	CurNod = mNode.toStrongRef();

		if( CurNod != 0 )
		{
			InterfaceOutput		*Output = qobject_cast<InterfaceOutput *>( CurNod->control()->object() );

			if( Output != 0 )
			{
				Output->buttonLeftPressed( false );
			}
		}
	}

	QWindow::mouseReleaseEvent( pEvent );
}

void DeviceOpenGLOutput::mouseMoveEvent( QMouseEvent *pEvent )
{
	QPointF		MouseCurrPosition = pEvent->pos();

	if( MouseCurrPosition != mMouseLastPosition )
	{
		QSharedPointer<fugio::NodeInterface>	CurNod = mNode.toStrongRef();

		if( CurNod != 0 )
		{
			InterfaceOutput		*Output = qobject_cast<InterfaceOutput *>( CurNod->control()->object() );

			if( Output != 0 )
			{
				Output->cursorPosition( MouseCurrPosition );
			}
		}

		mMouseLastPosition = MouseCurrPosition;

		emit cursorMove( MouseCurrPosition );
	}

	QWindow::mouseMoveEvent( pEvent );
}
#endif

void DeviceOpenGLOutput::keyReleaseEvent( QKeyEvent *pEvent )
{
	if( pEvent->key() == Qt::Key_Return && pEvent->modifiers().testFlag( Qt::AltModifier ) )
	{
		toggleFullScreen();

		pEvent->accept();
	}
	else if( pEvent->key() == Qt::Key_F10 )
	{
		screengrab();

		renderLater();

		pEvent->accept();
	}
	else
	{
		QWindow::keyReleaseEvent( pEvent );
	}
}

void DeviceOpenGLOutput::setFullScreen()
{
	showFullScreen();

	setCursor( Qt::BlankCursor );
}

void DeviceOpenGLOutput::toggleFullScreen()
{
	if( windowState() == Qt::WindowFullScreen )
	{
		showNormal();

		unsetCursor();

		setFlags( flags() & ~( Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint ) );
	}
	else
	{
		showFullScreen();

		bool		ShowCursor = false;

		setFlags( flags() | ( Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint ) );

		if( !ShowCursor )
		{
			setCursor( Qt::BlankCursor );
		}
	}
}

void DeviceOpenGLOutput::exposeEvent( QExposeEvent * )
{
	if( isExposed() && isValid() )
	{
		makeCurrent();

		if( glewExperimental == GL_FALSE )
		{
			glewExperimental = GL_TRUE;

			if( glewInit() != GLEW_OK )
			{
				qWarning() << "GLEW did not initialise";

				return;
			}

			qDebug() << "GL_VENDOR" << QString( (const char *)glGetString( GL_VENDOR ) );

			qDebug() << "GL_RENDERER" << QString( (const char *)glGetString( GL_RENDERER ) );

			qDebug() << "GL_VERSION" << QString( (const char *)glGetString( GL_VERSION ) );

			//qDebug() << context()->extensions();

			switch( context()->format().profile() )
			{
				case QSurfaceFormat::NoProfile:
					qInfo() << "Profile: None";
					break;

				case QSurfaceFormat::CoreProfile:
					qInfo() << "Profile: Core";
					break;

				case QSurfaceFormat::CompatibilityProfile:
					qInfo() << "Profile: Compatibility";
					break;
			}

			qInfo() << "Samples:" << context()->format().samples();
			qInfo() << "Alpha:" << context()->format().alphaBufferSize();
			qInfo() << "Depth:" << context()->format().depthBufferSize();
			qInfo() << "RGB:" << context()->format().redBufferSize() << context()->format().greenBufferSize() << context()->format().blueBufferSize();

			if( OpenGLPlugin::instance()->openWindowFullScreen() )
			{
				showFullScreen();
			}
		}

		raise();
	}
}
