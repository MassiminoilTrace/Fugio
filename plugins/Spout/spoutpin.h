#ifndef SPOUTPIN_H
#define SPOUTPIN_H

#include "opengl_includes.h"

#include <QObject>

#include <fugio/pin_control_interface.h>
#include <fugio/opengl/texture_interface.h>

#include <fugio/pincontrolbase.h>

#if defined( SPOUT_SUPPORTED )
#include <Spout.h>
#endif

using namespace fugio;

class SpoutPin : public fugio::PinControlBase, public fugio::OpenGLTextureInterface
{
	Q_OBJECT
	Q_INTERFACES( fugio::OpenGLTextureInterface )

public:
	Q_INVOKABLE explicit SpoutPin( QSharedPointer<fugio::PinInterface> pPin );

	virtual ~SpoutPin( void );

	bool receiveTexture( const QString &pName );

	const QVector<char> &name( void ) const
	{
		return( mName );
	}

	//-------------------------------------------------------------------------
	// fugio::PinControlInterface

	virtual QString toString( void ) const Q_DECL_OVERRIDE
	{
		return( QString( "%1: %2x%3" ).arg( QString( mName.data() ) ).arg( mWidth ).arg( mHeight ) );
	}

	virtual QString description( void ) const Q_DECL_OVERRIDE
	{
		return( "Spout" );
	}

	//-------------------------------------------------------------------------
	// InterfaceTexture

	virtual QVector3D textureSize( void ) const Q_DECL_OVERRIDE;

	virtual QVector3D size( void ) const Q_DECL_OVERRIDE;

	virtual quint32 srcTexId( void ) const Q_DECL_OVERRIDE;
	virtual quint32 dstTexId( void ) const Q_DECL_OVERRIDE;

	virtual QOpenGLTexture::Target target( void ) const Q_DECL_OVERRIDE;

	virtual QOpenGLTexture::PixelFormat format( void ) const Q_DECL_OVERRIDE;

	virtual QOpenGLTexture::TextureFormat internalFormat( void ) const Q_DECL_OVERRIDE;

	virtual QOpenGLTexture::PixelType type( void ) const Q_DECL_OVERRIDE;

	virtual QOpenGLTexture::Filter filterMin( void ) const Q_DECL_OVERRIDE;
	virtual QOpenGLTexture::Filter filterMag( void ) const Q_DECL_OVERRIDE;
	virtual QOpenGLTexture::WrapMode wrapS( void ) const Q_DECL_OVERRIDE;
	virtual QOpenGLTexture::WrapMode wrapT( void ) const Q_DECL_OVERRIDE;
	virtual QOpenGLTexture::WrapMode wrapR( void ) const Q_DECL_OVERRIDE;
	virtual bool genMipMaps( void ) const Q_DECL_OVERRIDE;

	virtual void setSize( qint32, qint32, qint32 ) Q_DECL_OVERRIDE {}

	virtual void setSize( const QVector3D & ) Q_DECL_OVERRIDE {}

	virtual void setTarget( QOpenGLTexture::Target ) Q_DECL_OVERRIDE {}

	virtual void setFormat( QOpenGLTexture::PixelFormat ) Q_DECL_OVERRIDE {}

	virtual void setType( QOpenGLTexture::PixelType ) Q_DECL_OVERRIDE {}

	virtual void setInternalFormat( QOpenGLTexture::TextureFormat ) Q_DECL_OVERRIDE {}

	virtual void update( void ) Q_DECL_OVERRIDE {}

	virtual void update( const unsigned char *, int, int, int ) Q_DECL_OVERRIDE {}

	virtual void setFilter( QOpenGLTexture::Filter, QOpenGLTexture::Filter ) Q_DECL_OVERRIDE {}

	virtual void setWrap( QOpenGLTexture::WrapMode, QOpenGLTexture::WrapMode, QOpenGLTexture::WrapMode ) Q_DECL_OVERRIDE {}

	virtual void setGenMipMaps( bool ) Q_DECL_OVERRIDE {}

	virtual void free( void ) Q_DECL_OVERRIDE;

	virtual QImage image( void ) Q_DECL_OVERRIDE;

	virtual void srcBind( void ) Q_DECL_OVERRIDE;
	virtual void dstBind( void ) Q_DECL_OVERRIDE {}

	virtual void release( void ) Q_DECL_OVERRIDE;

	virtual void swapTexture( void ) Q_DECL_OVERRIDE
	{

	}

	virtual void setDoubleBuffered( bool ) Q_DECL_OVERRIDE
	{
	}

	virtual bool isDoubleBuffered( void ) const Q_DECL_OVERRIDE
	{
		return( false );
	}

	virtual bool isDepthTexture( void ) const Q_DECL_OVERRIDE
	{
		return( false );
	}

	virtual QOpenGLTexture::ComparisonFunction compare() const Q_DECL_OVERRIDE
	{
		return( QOpenGLTexture::CompareLessEqual );
	}

	virtual void setCompare( QOpenGLTexture::ComparisonFunction pCompare) Q_DECL_OVERRIDE
	{
		Q_UNUSED( pCompare )
	}

	virtual OpenGLTextureDescription textureDescription() const Q_DECL_OVERRIDE
	{
		return( OpenGLTextureDescription() );
	}

	virtual void setTextureDescription( const OpenGLTextureDescription &pDescription ) Q_DECL_OVERRIDE
	{
		Q_UNUSED( pDescription )
	}

	virtual QOpenGLTexture *srcTex() Q_DECL_OVERRIDE
	{
		return( nullptr );
	}

	virtual QOpenGLTexture *dstTex() Q_DECL_OVERRIDE
	{
		return( nullptr );
	}

	virtual OpenGLTextureOrigin origin() const Q_DECL_OVERRIDE
	{
		return( OpenGLTextureOrigin::Unknown );
	}

	virtual void setOrigin(OpenGLTextureOrigin pOrigin) Q_DECL_OVERRIDE {}

	//-------------------------------------------------------------------------

private:
#if defined( SPOUT_SUPPORTED )
	SpoutReceiver			 mReceiver;
#endif

	QVector<char>			 mName;
	unsigned int			 mWidth;
	unsigned int			 mHeight;
};

#endif // SPOUTPIN_H
