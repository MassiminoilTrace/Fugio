#include "raspberrypiplugin.h"

#include <QTranslator>
#include <QCoreApplication>

#include <fugio/global_interface.h>
#include <fugio/global_signals.h>

#include <fugio/nodecontrolbase.h>

#include <fugio/raspberrypi/uuid.h>

#if defined( Q_OS_RASPBERRY_PI )
#include <bcm_host.h>
#include <unistd.h>
#endif

#if defined( PIGPIO_SUPPORTED )
#include <pigpiod_if2.h>
#endif

QList<QUuid>	NodeControlBase::PID_UUID;

ClassEntry	NodeClasses[] =
{
	ClassEntry()
};

ClassEntry PinClasses[] =
{
	ClassEntry()
};

RasperryPiPlugin::RasperryPiPlugin() : mApp( 0 )
{
	//-------------------------------------------------------------------------
	// Install translator

	static QTranslator		Translator;

	if( Translator.load( QLocale(), QLatin1String( "fugio_raspberrypi" ), QLatin1String( "_" ), ":/translations" ) )
	{
		qApp->installTranslator( &Translator );
	}
}

PluginInterface::InitResult RasperryPiPlugin::initialise( fugio::GlobalInterface *pApp, bool pLastChance )
{
	Q_UNUSED( pLastChance )

	//qDebug() << QString( aiGetLegalString() );

	mApp = pApp;

	mApp->registerNodeClasses( NodeClasses );

	mApp->registerPinClasses( PinClasses );

	//-------------------------------------------------------------------------

#if defined( PIGPIO_SUPPORTED )
	mPigPioInit = pigpio_start( NULL, NULL );

	if( mPigPioInit >= 0 )
	{
#if defined( QT_DEBUG )
		for( unsigned p = 0 ; p <= 53 ; p++ )
		{
			qDebug() << p << get_mode( mPigPioInit, p );
		}
#endif
	}
	else
	{
		qWarning() << "pigpio didn't start";
	}
#endif

	return( INIT_OK );
}

void RasperryPiPlugin::deinitialise( void )
{
#if defined( PIGPIO_SUPPORTED )
	if( mPigPioInit >= 0 )
	{
		pigpio_stop( mPigPioInit );
	}
#endif

	mApp->unregisterPinClasses( PinClasses );

	mApp->unregisterNodeClasses( NodeClasses );

	mApp = 0;
}
