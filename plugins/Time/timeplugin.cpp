#include "timeplugin.h"

#include <QTranslator>
#include <QCoreApplication>

#include <fugio/global_interface.h>
#include <fugio/global_signals.h>

#include <fugio/nodecontrolbase.h>

#include <fugio/time/uuid.h>

#include "clocknode.h"
#include "cronnode.h"
#include "delaynode.h"
#include "everynode.h"
#include "beattapnode.h"
#include "playheadnode.h"
#include "playheadcontrolnode.h"
#include "timenode.h"
#include "datenode.h"
#include "playheadframesnode.h"
#include "universetimenode.h"

#include "inertianode.h"

TimePlugin		*TimePlugin::mInstance = nullptr;

QList<QUuid>	NodeControlBase::PID_UUID;

ClassEntry	NodeClasses[] =
{
	ClassEntry( "Beat Tap",			"Time", NID_BEAT_TAP, &BeatTapNode::staticMetaObject ),
	ClassEntry( "Clock",			"Time", NID_CLOCK, &ClockNode::staticMetaObject ),
	ClassEntry( "Cron",				"Time", NID_CRON, &CronNode::staticMetaObject ),
	ClassEntry( "Date",				"Time", NID_DATE, &DateNode::staticMetaObject ),
	ClassEntry( "Delay",			"Time", NID_TIME_DELAY, &DelayNode::staticMetaObject ),
	ClassEntry( "Every",			"Time", NID_EVERY, &EveryNode::staticMetaObject ),
	ClassEntry( "Inertia",			"Time", NID_INERTIA, &InertiaNode::staticMetaObject ),
	ClassEntry( "Playhead",			"Time", NID_PLAYHEAD, &PlayheadNode::staticMetaObject ),
	ClassEntry( "Playhead Control",	"Time", NID_PLAYHEAD_CONTROL, &PlayheadControlNode::staticMetaObject ),
	ClassEntry( "Playhead Frames",	"Time", NID_PLAYHEAD_FRAMES, &PlayheadFramesNode::staticMetaObject ),
	ClassEntry( "Time",				"Time", NID_TIME, &TimeNode::staticMetaObject ),
	ClassEntry( "Universe Time",	"Time", NID_UNIVERSE_TIME, &UniverseTimeNode::staticMetaObject ),
	ClassEntry()
};

ClassEntry PinClasses[] =
{
	ClassEntry()
};

TimePlugin::TimePlugin() : mApp( 0 )
{
	mInstance = this;

	//-------------------------------------------------------------------------
	// Install translator

	static QTranslator		Translator;

	if( Translator.load( QLocale(), QLatin1String( "fugio_time" ), QLatin1String( "_" ), ":/translations" ) )
	{
		qApp->installTranslator( &Translator );
	}
}

PluginInterface::InitResult TimePlugin::initialise( fugio::GlobalInterface *pApp, bool pLastChance )
{
	Q_UNUSED( pLastChance )

	mApp = pApp;

	mApp->registerNodeClasses( NodeClasses );

	mApp->registerPinClasses( PinClasses );

	return( INIT_OK );
}

void TimePlugin::deinitialise( void )
{
	mApp->unregisterPinClasses( PinClasses );

	mApp->unregisterNodeClasses( NodeClasses );

	mApp = 0;
}
