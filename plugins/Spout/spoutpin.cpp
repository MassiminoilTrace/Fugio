#include "spoutpin.h"

#include <QSettings>
#include <QImage>

#include <QSet>
#include <QByteArray>

SpoutPin::SpoutPin( QSharedPointer<fugio::PinInterface> pPin )
	: PinControlBase( pPin ), mWidth( 0 ), mHeight( 0 )
{
	mName.resize( 256 );
}

SpoutPin::~SpoutPin( void )
{
#if defined( SPOUT_SUPPORTED )
	mReceiver.ReleaseReceiver();
#endif
}

bool SpoutPin::receiveTexture( const QString &pName )
{
#if defined( SPOUT_SUPPORTED )
	if( pName.isEmpty() )
	{
		mName[ 0 ] = 0x00;
	}
	else if( strcmp( mName.data(), pName.toLatin1().constData() ) != 0 )
	{
		mReceiver.ReleaseReceiver();

		strcpy( mName.data(), pName.toLatin1().constData() );
	}

	return( mReceiver.ReceiveTexture( mName.data(), mWidth, mHeight ) );
#else
	Q_UNUSED( pName )

	return( false );
#endif
}

QVector3D SpoutPin::textureSize() const
{
	return( QVector3D( mWidth, mHeight, 0 ) );
}

QVector3D SpoutPin::size() const
{
	return( QVector3D( mWidth, mHeight, 0 ) );
}

quint32 SpoutPin::srcTexId( void ) const
{
#if defined( SPOUT_SUPPORTED )
	return( -1 );
#else
	return( 0 );
#endif
}

quint32 SpoutPin::dstTexId( void ) const
{
	return( 0 );
}

quint32 SpoutPin::target() const
{
	return( GL_TEXTURE_2D );
}

quint32 SpoutPin::format() const
{
#if defined( SPOUT_SUPPORTED )
	return( GL_BGRA );
#else
	return( 0 );
#endif
}

quint32 SpoutPin::internalFormat() const
{
#if defined( SPOUT_SUPPORTED )
	return( GL_RGBA8 );
#else
	return( 0 );
#endif
}

quint32 SpoutPin::type() const
{
	return( QOpenGLTexture::UInt8 );
}

int SpoutPin::filterMin( void ) const
{
	return( GL_LINEAR );
}

int SpoutPin::filterMag( void ) const
{
#if defined( SPOUT_SUPPORTED )
	return( GL_LINEAR );
#else
	return( 0 );
#endif
}

int SpoutPin::wrapS( void ) const
{
#if defined( SPOUT_SUPPORTED )
	return( GL_CLAMP );
#else
	return( 0 );
#endif
}

int SpoutPin::wrapT( void ) const
{
#if defined( SPOUT_SUPPORTED )
	return( GL_CLAMP );
#else
	return( 0 );
#endif
}

int SpoutPin::wrapR( void ) const
{
#if defined( SPOUT_SUPPORTED )
	return( GL_CLAMP );
#else
	return( 0 );
#endif
}

bool SpoutPin::genMipMaps( void ) const
{
	return( false );
}

void SpoutPin::setSize( qint32, qint32, qint32 )
{

}

void SpoutPin::setSize( const QVector3D & )
{

}

void SpoutPin::setTarget( quint32 )
{
}

void SpoutPin::setFormat( quint32 )
{
}

void SpoutPin::setType( quint32 )
{
}

void SpoutPin::setInternalFormat( quint32 )
{
}

void SpoutPin::update()
{

}

void SpoutPin::update( const unsigned char *, int, int, int )
{
}

void SpoutPin::setFilter( quint32, quint32 )
{
}

void SpoutPin::setWrap( quint32, quint32, quint32 )
{
}

void SpoutPin::setGenMipMaps( bool )
{
}

void SpoutPin::free()
{
#if defined( SPOUT_SUPPORTED )
	mReceiver.ReleaseReceiver();
#endif
}

QImage SpoutPin::image()
{
	QImage		Image;

	return( Image );
}

void SpoutPin::srcBind()
{
#if defined( SPOUT_SUPPORTED )
	mReceiver.BindSharedTexture();
#endif
}

void SpoutPin::dstBind()
{

}

void SpoutPin::release()
{
#if defined( SPOUT_SUPPORTED )
	mReceiver.UnBindSharedTexture();
#endif
}

