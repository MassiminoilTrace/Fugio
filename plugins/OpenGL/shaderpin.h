#ifndef SHADERPIN_H
#define SHADERPIN_H

#include "opengl_includes.h"

#include <fugio/core/uuid.h>

#include <QObject>

#include <fugio/pin_interface.h>
#include <fugio/pin_control_interface.h>

#include <fugio/opengl/shader_interface.h>

#include <fugio/pincontrolbase.h>

class ShaderPin : public fugio::PinControlBase, public fugio::OpenGLShaderInterface
{
	Q_OBJECT
	Q_INTERFACES( fugio::OpenGLShaderInterface )

public:
	Q_INVOKABLE explicit ShaderPin( QSharedPointer<fugio::PinInterface> pPin );

	virtual ~ShaderPin( void ) {}

	void setParent( fugio::OpenGLShaderInterface *pShader )
	{
		mShader = pShader;
	}

	//-------------------------------------------------------------------------
	// fugio::PinControlInterface

	virtual QString toString( void ) const Q_DECL_OVERRIDE
	{
		return( QString() );
	}

	virtual QString description( void ) const Q_DECL_OVERRIDE
	{
		return( "Shader" );
	}

	//-------------------------------------------------------------------------
	// InterfaceOpenGLShader

	virtual bool isLinked( void ) const Q_DECL_OVERRIDE
	{
		return( mShader ? mShader->isLinked() : false );
	}

	virtual const fugio::ShaderUniformMap &uniformMap( void ) const Q_DECL_OVERRIDE
	{
		static const fugio::ShaderUniformMap	EmptyMap;

		return( mShader ? mShader->uniformMap() : EmptyMap );
	}

	virtual const fugio::ShaderUniformMap &attributeMap( void ) const Q_DECL_OVERRIDE
	{
		static const fugio::ShaderUniformMap	EmptyMap;

		return( mShader ? mShader->attributeMap() : EmptyMap );
	}

	virtual GLuint programId( void ) const Q_DECL_OVERRIDE
	{
		return( mShader ? mShader->programId() : 0 );
	}

	virtual QOpenGLShaderProgram *program( void ) Q_DECL_OVERRIDE
	{
		return( mShader ? mShader->program() : Q_NULLPTR );
	}

private:
	fugio::OpenGLShaderInterface		*mShader;
};

#endif // SHADERPIN_H
