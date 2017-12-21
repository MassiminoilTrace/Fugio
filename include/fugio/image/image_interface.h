#ifndef INTERFACE_IMAGE_BUFFER_H
#define INTERFACE_IMAGE_BUFFER_H

#include <fugio/global.h>

#include <QSize>
#include <QUuid>
#include <QByteArray>
#include <QImage>

FUGIO_NAMESPACE_BEGIN

class ImageInterface
{
public:
	typedef enum Format
	{
		FORMAT_UNKNOWN = -1,
		FORMAT_INTERNAL,
		FORMAT_RGB8,
		FORMAT_RGBA8,
		FORMAT_BGR8,
		FORMAT_BGRA8,
		FORMAT_YUYV422,
		FORMAT_GRAY16,
		FORMAT_GRAY8,
		FORMAT_RG32,
		FORMAT_DXT1,
		FORMAT_DXT5,
		FORMAT_YCoCg_DXT5,
		FORMAT_HSV8,
		FORMAT_YUV420P,
		FORMAT_UYVY422,
		FORMAT_R32S,
		FORMAT_R32F,
		FORMAT_YUVJ422P,
		FORMAT_NV12
	} Format;

	static int formatPixelByteCount( Format pFormat, int pBuffer = 0 )
	{
		switch( pFormat )
		{
			case FORMAT_RGB8:		return( 3 );
			case FORMAT_RGBA8:		return( 4 );
			case FORMAT_BGR8:		return( 3 );
			case FORMAT_BGRA8:		return( 4 );
			case FORMAT_YUV420P:	return( !pBuffer ? 2 : 1 );
			case FORMAT_YUYV422:	return( 2 );
			case FORMAT_UYVY422:	return( 2 );
			case FORMAT_GRAY16:		return( 2 );
			case FORMAT_GRAY8:		return( 1 );
			case FORMAT_RG32:		return( 4 );
			case FORMAT_HSV8:		return( 3 );
			case FORMAT_R32S:		return( 4 );
			case FORMAT_R32F:		return( 4 );
			case FORMAT_NV12:		return( 1 );

			default:			break;
		}

		return( 0 );
	}

	const static int PLANE_COUNT = 8;

	virtual ~ImageInterface( void ) {}

	virtual QSize size( void ) const = 0;

	virtual int width( void ) const = 0;
	virtual int height( void ) const = 0;

	virtual int lineSize( int pIndex ) const = 0;
	virtual const int *lineSizes( void ) const = 0;

	virtual quint8 *internalBuffer( int pIndex ) = 0;
	virtual quint8 *internalBuffer( int pIndex ) const = 0;

	virtual quint8 **internalBuffers( void ) = 0;
	virtual quint8 **internalBuffers( void ) const = 0;

	virtual const quint8 *buffer( int pIndex ) = 0;
	virtual const quint8 *buffer( int pIndex ) const = 0;

	//virtual const quint8 * const *buffers( void ) = 0;
	virtual const quint8 * const *buffers( void ) const = 0;

	virtual int bufferSize( int pIndex ) const = 0;

	virtual Format format( void ) const = 0;

	virtual int internalFormat( void ) const = 0;

	virtual void unsetBuffers( void ) = 0;

	virtual void setBuffer( int pIndex, const quint8 *pBuffer ) = 0;

	virtual void setBuffers( quint8 * const pBuffer[ PLANE_COUNT ] ) = 0;

	virtual void setSize( quint32 pWidth, quint32 pHeight ) = 0;

	virtual void setFormat( Format pFormat ) = 0;

	virtual void setInternalFormat( int pInternalFormat ) = 0;

	virtual void setLineSize( int pIndex, int pLineSize ) = 0;

	virtual void setLineSizes( const int pLineSize[ PLANE_COUNT ] ) = 0;

	virtual QImage image( void ) const = 0;

	virtual bool isValid( void ) const = 0;

	static QImage::Format toQImageFormat( Format pFormat )
	{
		switch( pFormat )
		{
			case FORMAT_RGB8:	return( QImage::Format_RGB888 );
			case FORMAT_RGBA8:	return( QImage::Format_ARGB32 );
			case FORMAT_BGRA8:	return( QImage::Format_ARGB32 );
#if QT_VERSION >= QT_VERSION_CHECK( 5, 5, 0 )
			case FORMAT_GRAY8:	return( QImage::Format_Grayscale8 );
#endif
			default:			break;
		}

		return( QImage::Format_Invalid );
	}

	static Format fromQImageFormat( QImage::Format pFormat )
	{
		switch( pFormat )
		{
			case QImage::Format_RGB888:					return( FORMAT_RGB8 );
			case QImage::Format_ARGB32:					return( FORMAT_RGBA8 );
			case QImage::Format_ARGB32_Premultiplied:	return( FORMAT_RGBA8 );
#if QT_VERSION >= QT_VERSION_CHECK( 5, 5, 0 )
			case QImage::Format_Grayscale8:				return( FORMAT_GRAY8 );
#endif
			default:									break;
		}

		return( FORMAT_UNKNOWN );
	}
};

FUGIO_NAMESPACE_END

Q_DECLARE_INTERFACE( fugio::ImageInterface, "com.bigfug.fugio.image/1.0" )

#endif // INTERFACE_IMAGE_BUFFER_H
