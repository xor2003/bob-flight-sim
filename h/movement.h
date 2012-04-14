//------------------------------------------------------------------------------
//Filename       movement.h
//System         
//Author         R. Hyde 
//Date           Mon 19 Feb 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MOVEMENT_Included
#define	MOVEMENT_Included

#define	DEFAULT_MOVEMENT 0


enum	BFieldWaypointActions
	{	
	wpacnoactionno			,
	wpatakeoffno			,
	wpacircleno				,//DeadCode RDH 11Oct96 	wpacruiseformno			,//DeadCode RDH 11Oct96 	wpaccombatformno		,
	wpalandingno,
	wpdisperseno,
	wpstartloopno			,					
	wpstoploopchkno 		,					
	wpreccyno				,						
	wpartspotno				,						
	wpengagetargetno		 ,					
	wpattackconvoyno		 ,					
	wpballoonbustno,											//MS 18Jul96
	wpbombno,													//MS 18Jul96
	wpdivebombstraffeno,										//MS 18Jul96
	wpsecondaryno,												//MS 18Jul96
	wpbreakloop,

	WP_waitfriendly,	 //using
	WP_spotterapproach,	//not using yet...
	WP_spottarget,		//not using yet...
	WP_fighterlimit,
	wp_start_cas,

	wp_threat_combfriendly,
	wp_threat_engfriendly,
	wp_threat_firing,
	wp_threat_weapon,
	wp_threat_danger,
	wp_threat_engage,
	wp_threat_any,

//ACCUMULATED GARBAGE
//DeadCode RDH 03Sep96 	wpajinkstartno			,
//DeadCode RDH 03Sep96 	wpajinkstoptno			,
//DeadCode JIM 02Aug96 	wpbarrelrollno			,		
//DeadCode JIM 02Aug96 	wpclimbrollno			,
//DeadCode RDH 03Sep96 	wplauncha2gno			,						
//DeadCode JIM 02Aug96 	wppickleno				,						
//DeadCode RDH 03Sep96 	wpswitchtoa2gcapableno	 ,					
//DeadCode RDH 03Sep96 	wpswitchtoa2acapableno	 ,					
//DeadCode JIM 02Aug96 	wpeyeballtargetno		 ,					
//DeadCode JIM 02Aug96 	wpbuzztargetno			 ,					
//DeadCode JIM 02Aug96 	wpwarntargetno			 ,					
//DeadCode RDH 03Sep96 	dumbshipfiremissileno	 ,					
//DeadCode RDH 03Sep96 	dumbshipescortno		 ,
//DeadCode RDH 03Sep96 	wpkillburnno,		
//DeadCode RDH 03Sep96 	wpkillbrkupno,		
//DeadCode RDH 03Sep96 	wpkillchuteno,


//NON-AIRCRAFT WAYPOINT ACTIONS:
	wpwaituntildeadno,
	wpdmbtrknoactno			,					
	wpdmbtrkstopno			,					
	wptruckbridge			 ,					
	wptruckescort			 ,					
	wpstopno,			
	wpteleportnext,
	wpfiregun,
	wpcheckfordamage,											//RJS 11Jan00

//PSEUDO WP ACTIONS GENERATED BY LEADER FOR FOLLOWERS
	wpforcebreakloop,		//
	wpretrywp, 				//try again next frame??
	wpforcelanding,			 //

	WPSAME=0xff,
	WPALIGN=0xff
	};


enum	MANOEUVRE	{											//JIM 16Jul96
	MANOEUVRE_SELECT=0,											//JIM 16Jul96
	MANOEUVRE_LOOKROUND,										//JIM 16Jul96
	MANOEUVRE_WELDEDWINGMAN,										//RDH 03Mar98
	MANOEUVRE_BAILOUT,										//RDH 03Mar98
	MANOEUVRE_TOPCOVER,											//JIM 16Jul96

//The manoeuvres above do not involve an unfriendly				//JIM 16Jul96
//TOPCOVER is tested against as the last such manoeuvre
//The manoeuvres below always involve an unfriendly				//JIM 16Jul96

	MANOEUVRE_FORCETOPCOVER,											//CSB 09/03/00
	MANOEUVRE_LINEABREAST,										//RDH 27Mar98
//DEADCODE CB 18/11/99 	MANOEUVRE_SCATTER,											//RDH 27Mar98
	MANOEUVRE_PINCER,											//RDH 27Mar98
	MANOEUVRE_MULTIWAVE,										//RDH 27Mar98
	MANOEUVRE_DIVEANDZOOM,
	MANOEUVRE_LEADPURSUIT,
	MANOEUVRE_LAGPURSUIT,
//DEADCODE CB 18/11/99 	MANOEUVRE_CIRCUMVENT,										//RDH 27Mar98
//DEADCODE CB 18/11/99 	MANOEUVRE_ROUNDABOUT,										//RDH 27Mar98
	MANOEUVRE_SPLITMANOEUVRE,									//RDH 27Mar98
	MANOEUVRE_HEADON,
	MANOEUVRE_LINEASTERN,										//RDH 27Mar98
	MANOEUVRE_VICATTACK,												//CSB 15/03/00

//The manouevres above are considered to be first manoeuvres	//RDH 17Mar98
//They use the leader's unfriendly as reference 					//RDH 17Mar98
	
	MANOEUVRE_BARRELROLLATTACK,
	MANOEUVRE_SCISSORS,
	MANOEUVRE_MILDSCISSORS,
	MANOEUVRE_TURNINGFIGHT,
	MANOEUVRE_SPLITS,
	MANOEUVRE_ZOOMANDDROP,
	MANOEUVRE_STRAIGHTANDLEVEL,
	MANOEUVRE_SPINOUT,
	MANOEUVRE_DIVEFORHOME,
	MANOEUVRE_GOHOME,
	MANOEUVRE_MAKEFORFRIENDLY,
	MANOEUVRE_MOVEAWAY,
	MANOEUVRE_ACCIDENTALSPINOUT,
	MANOEUVRE_VERTICALLOOP,
	MANOEUVRE_IMMELMANNTURN,
//DEADCODE CB 18/11/99 	MANOEUVRE_HEADONOFFSET,
	MANOEUVRE_IMMELMANN,
	MANOEUVRE_STAYWITHPREY,
	MANOEUVRE_CLIMBFORHOME,
	MANOEUVRE_STRAIGHTDIVE,										//RDH 18Mar96
	MANOEUVRE_STANDONTAIL,										//RDH 18Mar96
	MANOEUVRE_SHOOTTOFRIGHTEN,									//RDH 18Mar96
	MANOEUVRE_SHOOTTOOEARLY,									//RDH 18Mar96
	MANOEUVRE_GAINHEIGHT,										//RDH 18Mar96
	MANOEUVRE_LAGROLL,											//RDH 30Mar98
	MANOEUVRE_EXTENSION,										//RDH 30Mar98
	MANOEUVRE_DIVINGSPIN,
	MANOEUVRE_REVERSETURN,										//RDH 30Mar98
	MANOEUVRE_SELFASBAIT,										//RDH 30Mar98
	MANOEUVRE_JINK,												//RDH 30Mar98
	MANOEUVRE_BREAKTURN,										//RDH 30Mar98
	MANOEUVRE_LAZYTURN,											//RDH 30Mar98
//DEADCODE CB 18/11/99 	MANOEUVRE_BREAK180,											//RDH 30Mar98
	MANOEUVRE_BREAKLOW,											//RDH 30Mar98
	MANOEUVRE_BREAKHIGH,										//RDH 30Mar98
	MANOEUVRE_BREAK90,											//RDH 30Mar98
	MANOEUVRE_HIGBARRELROLL,									//RDH 30Mar98
	MANOEUVRE_PANICTURN,										//RDH 30Mar98
	MANOEUVRE_UNBALANCEDFLIGHT,									//RDH 30Mar98
	MANOEUVRE_LOWALT,
//DEADCODE CB 18/11/99 	MANOEUVRE_SNAPSHOT,											//RDH 30Mar98
//DEADCODE CB 18/11/99 	MANOEUVRE_STAYONTAIL,										//RDH 30Mar98
	MANOEUVRE_TURNTOHDGANDPITCH,								//RDH 30Mar98
//DEADCODE CB 18/11/99 	MANOEUVRE_HOTSIDELAGPURSUITFIGHT,							//RDH 30Mar98
//DEADCODE CB 18/11/99 	MANOEUVRE_SANDWICHMANOEUVRES,								//RDH 30Mar98
//DEADCODE CB 18/11/99 	MANOEUVRE_SUSTAINEDTURN,									//RDH 30Mar98
//DeadCode CSB 7Sep00 	MANOEUVRE_HIGHYOYO,											//RDH 30Mar98
	MANOEUVRE_ZOOM,
//DeadCode CSB 7Sep00 	MANOEUVRE_LOWYOYO,
	MANOEUVRE_INTERCEPTHIGH,									//RDH 30Mar98
	MANOEUVRE_INTERCEPTLOW,												//CSB 7Sep00
//DEADCODE CB 18/11/99 	MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED,						//RDH 30Mar98
	MANOEUVRE_GAINSPEED,										//RDH 27Apr98
	MANOEUVRE_HEADONATTACK,											  //CSB 24/11/99
	MANOEUVRE_LUFBERRY,												  //CB 18/11/99
	MANOEUVRE_STEEPDIVE,											  //CB 18/11/99
	MANOEUVRE_UPANDUNDER,											  //CB 18/11/99
	MANOEUVRE_STALLTURN,											  //CB 18/11/99
	MANOEUVRE_SLASHINGATTACK,										  //CB 18/11/99
	MANOEUVRE_CLIMBTURN,											  //CB 18/11/99
	MANOEUVRE_ROLL360,												  //CB 18/11/99
	MANOEUVRE_STRAFFE,												  //CB 18/11/99
	MANOEUVRE_PEELOFF,
	MANOEUVRE_FLYTHROUGHCLOUD,										  //CSB 10/01/00
	MANOEUVRE_REGROUP,
	MANOEUVRE_DISENGAGED,												//CSB 25Aug00
	MANOEUVRE_SCREWYOUGUYSIMGOINGHOME,

//following manoeuvres not available for selection by system
	MANOEUVRE_SPINRECOVERY,											//RDH 21Aug96
	MANOEUVRE_COLLISIONAVOIDANCE,									  //CSB 03/02/00
	MANOEUVRE_COLLIDE,												  //CSB 03/02/00
//DeadCode RDH 05Jan99 	MANOEUVRE_BOUNCEFOLLOWER,			//used for training

	MANOEUVRE_LAST,
	MANOEUVRE_ALIGNMENT=255
	};

//DeadCode RDH 30Mar98 enum ATTACKMANOEUVRE	{
//DeadCode RDH 30Mar98 	NO_ATTACKMANOEUVRE = 0,
//DeadCode RDH 30Mar98 	ATTACKMANOEUVRE_LOWGYOYO,
//DeadCode RDH 30Mar98 	ATTACKMANOEUVRE_HEADONOFFSET,
//DeadCode RDH 30Mar98 	ATTACKMANOEUVRE_STAYWITHPREY,
//DeadCode RDH 30Mar98 	ATTACKMANOEUVRE_DIVEANDZOOM,
//DeadCode RDH 30Mar98 	ATTACKMANOEUVRE_STANDONTAIL,
//DeadCode RDH 30Mar98 	ATTACKMANOEUVRE_SHOOTTOFRIGHTEN,
//DeadCode RDH 30Mar98 
//DeadCode RDH 30Mar98 	ATTACKMANOEUVRE_LAST
//DeadCode RDH 30Mar98 	};					

//DeadCode RDH 30Mar98 enum DEFENDMANOEUVRE	{
//DeadCode RDH 30Mar98 	NO_DEFENDMANOEUVRE = 0,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_BARRELROLL,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_SPLITS,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_SIDESLIP,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_ZOOMANDDROP,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_SPINOUT,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_DIVEFORHOME,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_GOHOME,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_SCISSORS,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_MAKEFORFRIENDLY,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_MOVEAWAY,
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_IMMELMANNTURN,
//DeadCode RDH 30Mar98 
//DeadCode RDH 30Mar98 	DEFENDMANOEUVRE_LAST
//DeadCode RDH 30Mar98 	};					



//
//	Since rod didn't comment this, I'd better!
//	The bit after AUTO_COMBAT must map to the ACM list above.
//	Put any ordinary movecodes in groups 
//	between AUTO_FOLLOWWP and AUTO_COMBAT, thanks!
//
enum	AutoMoveCodeTypeSelect	{
	AutoMoveCodeMask=63,

//Aircraft movecodes
	AUTO_FOLLOWWP=0,
	AUTO_NOPPILOT,
	AUTO_WAIT4TIME,
	AUTO_TAXI,
	AUTO_TAKEOFF,
	GROUND_TAXI,
	AUTO_TELLLEADER,											//JIM 25Jun96
	AUTO_FOLLOWTHELEADER,											  //CSB 03/02/00

	AUTO_SPIRAL2GROUND,											//PD 01May96
	AUTO_RESURRECT,												//ARM 05Dec96
	AUTO_DEATHSEQUENCE,											//RJS 08Aug96
	AUTO_DEATHGLIDE,													//CSB 15Aug00
//DEADCODE CSB 16/02/00 	AUTO_TRAININGPREMERGE,										//RDH 09Sep96
//DEADCODE CSB 16/02/00 	AUTO_TRAININGACM,											//RDH 09Sep96
	AUTO_TRAININGTAKEOFF,											  //CSB 16/02/00
	AUTO_TRAININGLANDING,											  //CSB 16/02/00
	AUTO_TRAININGFORMATION,											  //CSB 16/02/00
	GROUND_CORNERUPTO,
	GROUND_CORNERTURN,
	AUTO_CRASHSKID,												//RDH 12Sep96
	AUTO_CRASHROLL,												//RDH 12Sep96
	AUTO_CRASHONEWHEEL,												  //CSB 21/12/99
	AUTO_CRASHNOSE,													  //CSB 21/12/99
	AUTO_CRASHFLIP,													  //CSB 21/12/99
	AUTO_CRASHTUMBLE,												  //CSB 21/12/99

	AUTO_BOMB,
	AUTO_COVER,
	AUTO_STRAFFE,
	AUTO_BALLOON,
	AUTO_RECONN,
	AUTO_ARTSPOT,
	AUTO_HITWATER,												//RJS 24Aug98

	AUTO_TRACKINGBOGIE,											//RDH 27Mar98
	AUTO_TRACKINGBANDIT,										//RDH 27Mar98
	AUTO_PRECOMBAT,												//JIM 03Jul96
	AUTO_LANDING,
	AUTO_FAC,
	AUTO_CAS,
	AUTO_ACCELERATE,
	AUTO_MISSIONDICETHROW,
	AUTO_COMMSACCEL,											//AMM 11Jun99
	AUTO_SPAREAC,														//CSB 14Aug00
	GROUND_TOGLOBREF,
	GROUND_BLOKE,												//RJS 10Jan00
	GROUND_EMERGENCY,											//RJS 10Jan00
	GROUND_HALTTRUCK,											//RJS 10Jan00
	GROUND_BLOKEFREAK,											//RJS 22May00
	AUTO_LAST,

//SAG Movecodes
	AUTOSAG_FIRST,
	AUTOSAG_FOLLOWWPHOME	,
	AUTOSAG_REFUELLING		,
	AUTOSAG_COMBATCIRCLES	,
	AUTOSAG_POSTCOMBAT		,
	AUTOSAG_BOMBAPPROACH	,
	AUTOSAG_DESTROYED		,
	AUTOSAG_TRACKEXPFOLLOW	=0x3C,
	AUTOSAG_TRACKEXPCOMBAT	,
	AUTOSAG_LAST			,

	AUTOSAG_WAITTAKEOFF		= AUTO_WAIT4TIME,
	AUTOSAG_TAKEOFF			= AUTO_TAKEOFF,								//CSB 22/03/00
	AUTOSAG_FOLLOWWP		= AUTO_FOLLOWWP,							//CSB 22/03/00
	AUTOSAG_LANDING			= AUTO_LANDING,								//CSB 22/03/00
	AUTOSAG_PRECOMBAT		= AUTO_PRECOMBAT,							//CSB 22/03/00
//DEADCODE CSB 22/03/00 	AUTOSAG_COMBAT			= AUTO_COMBAT,
	AUTOSAG_BOMB			= AUTO_BOMB,								//CSB 22/03/00
	AUTOSAG_DEATHGLIDE		= AUTO_DEATHGLIDE,							//CSB 15Aug00


//Transient item movecodes
	MOBILE_BURNIT=0,											//RJS 18Nov98
	MOBILE_NOPPILOT,											//RJS 19Nov98
	MOBILE_CRATER,
	MOBILE_BULLET,
	MOBILE_PAC,													  //CSB 10/01/00	Parachute and Chain 
	MOBILE_DEADACPART,
	MOBILE_SMOKETRAIL,											//PD 30Apr96
	MOBILE_GANDF,												//PD 30Apr96
	MOBILE_GROUNDEXP,											//PD 01May96
	MOBILE_DEBRIS,												//RJS 21Jun96
	MOBILE_FIRE,												//RJS 01Jul96
	MOBILE_TROOP,												//RJS 01Jul96
	MOBILE_PARACHUTE,											//RJS 02Jul96
	MOBILE_BARAGE,												//RJS 02Jul96
	MOBILE_DELEXP,												//RJS 02Jul96
	MOBILE_FLAK,												//RJS 02Jul96
	MOBILE_RICOCHET,											//RJS 05Jul96
	MOBILE_ATEAM,												//RJS 10Jul96
	MOBILE_BOMBDROP,
	MOBILE_BIGEXP,												//RJS 12Aug96
	MOBILE_MOVSMK,												//RJS 02Sep96
	MOBILE_STATIONARY,											//RJS 20Apr98
	MOBILE_PUFFTRAVEL,												//RJS 05Sep96
	MOBILE_SINK,												//RJS 13May99
	MOBILE_BIRD,												//RJS 17Oct96
	MOBILE_AMMODEATH,											//RJS 17Oct96
	MOBILE_MUSHROOM,											//RJS 06Nov96
	MOBILE_ROCKET,												//RJS 04Jun97
	MOBILE_CLONEGUN,											//RJS 01Oct97
	MOBILE_TIMEREXPLOSION,										//RJS 22Jan98
	MOBILE_NAPALM,												//RJS 22Jan98
	MOBILE_DODAMAGE,											//RJS 18Feb98
	MOBILE_THUG,												//RJS 02Mar98
	MOBILE_SMALLTHUG,											//RJS 03Dec98
	MOBILE_FUELDROP,											//RJS 28May98
	MOBILE_DEADBRIDGE,											//RJS 30Oct98
	MOBILE_COLLAPSE,											//RJS 18Nov98
//DeadCode RJS 15Dec99 	MOBILE_CARPETBOMB,											//RJS 31May99
	MOBILE_SCALEFIST,											//RJS 10Feb99
	MOBILE_CANOPY,												//RJS 23Mar99
	MOBILE_FLARE,												//RJS 17May99
	MOBILE_SUPERBOMB,											//RJS 23Nov99
	MOBILE_DEADAC,												//RJS 25Nov99
	MOBILE_FUELFIRE,											//RJS 13Dec99
	MOBILE_FIRESMOKE,											//RJS 14Dec99
	MOBILE_DEADBALLOON,											//RJS 15Dec99
	MOBILE_ENGINESTART,											//RJS 22Feb00
	MOBILE_BOMB1STFRAME,												//RJS 3Oct00

	MOBILE_TRANSIENT_LAST,

//
// Auto combat is the highest numbered movecode
//
	AUTO_COMBAT=AutoMoveCodeMask,
	AUTOSAG_COMBAT			= AUTO_COMBAT,								//CSB 22/03/00
// The codes below could once be used in the battlefield system to generate
// ACM actions on entry to the 3d
		ACM_LOOKROUND,
		ACM_WELDEDWINGMAN,										//RDH 03Mar98
		ACM_BAILOUT,										//RDH 03Mar98
		ACM_TOPCOVER,
		ACM_FORCETOPCOVER,												//CSB 29/03/00
		ACM_LINEABREAST,										//RDH 27Mar98
//DEADCODE CSB 29/03/00 		ACM_SCATTER,											//RDH 27Mar98
		ACM_PINCER,												//RDH 27Mar98
		ACM_MULTIWAVE,											//RDH 27Mar98
		ACM_DIVEANDZOOM,										//RDH 27Mar98
		ACM_LEADPURSUIT,
		ACM_LAGPURSUIT,
//DEADCODE CSB 29/03/00 		ACM_CIRCUMVENT,										//RDH 27Mar98
//rdh		ACM_DECOYACTIVE,										//RDH 27Mar98
//		ACM_DECOYPASSIVE,										//RDH 27Mar98
//DEADCODE CSB 29/03/00 		ACM_ROUNDABOUT,											//RDH 27Mar98
		ACM_SPLITMANOEUVRE,									//RDH 27Mar98
		ACM_HEADON,	
		ACM_LINEASTERN,											//RDH 27Mar98
		ACM_VICATTACK,													//CSB 29/03/00
		ACM_BARRELROLLATTACK,
		ACM_SCISSORS,
		ACM_MILDSCISSORS,
		ACM_TURNINGFIGHT,
		ACM_SPLITS,
		ACM_ZOOMANDDROP,
		ACM_STRAIGHTANDLEVEL,
		ACM_SPINOUT,
		ACM_DIVEFORHOME,
		ACM_GOHOME,
		ACM_MAKEFORFRIENDLY,
		ACM_MOVEAWAY,
		ACM_ACCIDENTALSPINOUT,
		ACM_VERTICALLOOP,
		ACM_IMMELMANNTURN,
//DEADCODE CSB 29/03/00 		ACM_HEADONOFFSET,
		ACM_IMMELMANN,											//RDH 30Mar98
		ACM_STAYWITHPREY,
		ACM_CLIMBFORHOME,
		ACM_STRAIGHTDIVE,										//RDH 18Mar96
		ACM_STANDONTAIL,										//RDH 18Mar96
		ACM_SHOOTTOFRIGHTEN,									//RDH 18Mar96
		ACM_SHOOTTOOEARLY,									//RDH 18Mar96
		ACM_GAINHEIGHT,
		ACM_LAGROLL,											//RDH 30Mar98
		ACM_EXTENSION,										//RDH 30Mar98
		ACM_DIVINGSPIN,
		ACM_REVERSETURN,										//RDH 30Mar98
		ACM_SELFASBAIT,										//RDH 30Mar98
		ACM_JINK,												//RDH 30Mar98
		ACM_BREAKTURN,										//RDH 30Mar98
		ACM_LAZYTURN,											//RDH 30Mar98
		ACM_BREAKLOW,											//RDH 30Mar98
		ACM_BREAKHIGH,										//RDH 30Mar98
		ACM_BREAK90,											//RDH 30Mar98
		ACM_HIGBARRELROLL,									//RDH 30Mar98
		ACM_PANICTURN,
		ACM_UNBALANCEDFLIGHT,
		ACM_LOWALT,
		ACM_TURNTOHDGANDPITCH,
		ACM_HIGHYOYO,
		ACM_ZOOM,
		ACM_LOWYOYO,
		ACM_INTERCEPTHIGH,
		ACM_GAINSPEED,
		ACM_HEADONATTACK,
		ACM_LUFBERRY,
		ACM_STEEPDIVE,
		ACM_UPANDUNDER,
		ACM_STALLTURN,
		ACM_SLASHINGATTACK,
		ACM_CLIMBTURN,
		ACM_ROLL360,
		ACM_STRAFFE,
		ACM_FLYTHROUGHCLOUD,
		ACM_SPINRECOVERY,
		ACM_COLLISIONAVOIDANCE,
		ACM_COLLIDE,

	AutoMoveCodeTypeSelect_ALIGN=255							//RJS 24Nov97
		};


enum PhaseNumber	{
	PHASE0 = 0,PHASESTEP = 1,
	PHASE1 = 1, 
	PHASE2 = 2, 
	PHASE3 = 3, 
	PHASE4 = 4, 
	PHASE5 = 5, 
	PHASE6 = 6,
	PHASE7 = 7, 												//ARM 02Jun97
	PHASE8 = 8, 												//ARM 02Jun97
	PHASE9 = 9, 												//ARM 02Jun97
	PHASE10 = 10, 												//ARM 02Jun97
	PHASE11 = 11, 												//ARM 02Jun97
	PHASE12 = 12,												//ARM 02Jun97
	PHASE13 = 13, 												//ARM 02Jun97
	PHASE14 = 14,												//ARM 02Jun97
	PHASERESET = 15	
	};

enum	TakeOffEnum	//Goes into manstep
{
	TO_LATERGROUPTIMER,			//0
	TO_LATERGROUPPLAYER,		//1
	TO_LATERGROUPTAXI,			//2
	TO_LATERFLIGHTPLAYER,		//3
	TO_LATERFLIGHTSLIPWAY,		//4
	TO_LATERGROUPSLIPWAY,		//5
	TO_RUNWAYTURN,				//6
	TO_RUNWAYTAXI,				//7
	TO_PLAYERPLAYER,			//8
	TO_RUNWAYPOWER,				//9
	TO_RUNWAYCLIMB,				//10
	TO_CLIMBTURN,				//11
	TO_DIRTYAFWPW,				//12	//CSB 19/04/99	//Dirty AutoFollowWPWing

	TO_SIMPLEHOLDDELAY=14,
	TO_SIMPLEHOLDINDEFINITE=15,

	TO_MINCLIMBTIME=20*100,		//20 seconds	 //shortest time anyone spends in straight climb
	TO_NORMCLIMBTIME=30*100,	//30 sec
	TO_WINGCLIMBTIME=25*100,
	TO_TURNCLIMBTIME=120*100	//120 seconds	//CSB 19/04/99	
};

//DEADCODE DAW 22/11/99 enum	PhaseFAC	{	FAC_WAIT=0,			FAC_WAITRECONNECT,			FAC_WELCOME_LONGRANGE,		FAC_WINGWAGGLE,
//DEADCODE DAW 22/11/99 							FAC_WAITCLOSER,	FAC_WELCOME_CLOSE,			FAC_WAITTOUCHING,			
//DEADCODE DAW 22/11/99 						FAC_TARGETAREA=16,	FAC_TARGETAREARECONNECT,	FAC_NEXTTARGASBOMBERCLIMBS,	FAC_DESCRIBETARGETS,	
//DEADCODE DAW 22/11/99 							FAC_FLYTOAREA,	FAC_HOMEFORCES,				FAC_TARGETBMBCLOSER,		FAC_TARGETTOOCLOSE,
//DEADCODE DAW 22/11/99 							FAC_WATCHROCKETS,
//DEADCODE DAW 22/11/99 						FAC_ROCKETEER=32,	FAC_ROCKETEERRECONNECT,		FAC_GOINGIN,				FAC_SEEMYSMOKE,	
//DEADCODE DAW 22/11/99 							FAC_CLIMBTOOBSERVE,	FAC_ADVISEATTACK,		FAC_OBSERVING,				FAC_MISSTIMEOUT,
//DEADCODE DAW 22/11/99 							FAC_ENOUGHHITS,	FAC_HIT,					FAC_DAMAGE,					FAC_HITFRIENDS,
//DEADCODE DAW 22/11/99 						FAC_EXTRAS=48,		FAC_REQUEST_LONGRANGE,		FAC_GOINGHOME,				FAC_MORETARGETS,	
//DEADCODE DAW 22/11/99 							FAC_NOMORETARGETS,
//DEADCODE DAW 22/11/99 						FAC_STAGEMASK=-16,FAC_SUBSTAGEMASK=15
//DEADCODE DAW 22/11/99 					};
enum	WPNames
{	//these are indexed by WPP index
	WPNAME_None,
	WPNAME_TakeOff,
	WPNAME_BombRendezvous,
	WPNAME_EscRendezvous,
	WPNAME_Dogleg,
	WPNAME_IP,
	WPNAME_EstPoint,
	WPNAME_Target,
	WPNAME_Egress,
	WPNAME_EscDisperse,
	WPNAME_BombDisperse,
	WPNAME_Landing,
	
	//these are seperately indexed by WPP
	WPNAME_Msg0,
	WPNAME_Msg1,
	WPNAME_Msg2,
	WPNAME_Msg3,
	WPNAME_Msg4,
	WPNAME_Msg5,
	WPNAME_Msg6,
	WPNAME_Msg7,
	WPNAME_Msg8,
	WPNAME_Msg9,

	//these are translated from WPC, and can be in any order.
	WPNAME_PatrolS,
	WPNAME_PatrolE,
	WPNAME_109Break,
	WPNAME_HomeEscort,

};

#endif
