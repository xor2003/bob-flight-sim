//------------------------------------------------------------------------------
//Filename       planetyp.h
//System         
//Author         R. Hyde 
//Date           Thu 26 Oct 1995
//Description    Use I_planetype	to declare an instance
//				 Use name.I			to access the instance
// This module contains macros to initialise inherited classes "c" style.
// If the module is declared a second time, then this alternate construction 
// is made to allow instances to occur. 
// The re-caller has to undef PLANETYP_Included to avoid accidental double call
//------------------------------------------------------------------------------
#ifndef	PLANETYP_Included
#define	PLANETYP_Included
#include	"DosDefs.h"
#include	"files.g"		//NON-GRAPHICS FILES				//RDH 16Jul96
//DEADCODE JIM 09/02/00 #include	"text.h"
#include	"myANGLES.h"											//ARM 02Aug96
#include	"flyinit.h"											//ARM 02Aug96
#include	"worldinc.h"										//ARM 03Feb97
//DeadCode JIM 19Jul96 #include	"TextRef.h"

#ifdef	DEFAULT_PLANETYP
//
// If the module is declared a second time, then this alternate construction 
// is made to allow instances to occur.
//
	#define	emptybasestruct(subname,parentname)						\
	struct	II_##subname			{

	#define	basestruct(subname)							\
	struct	II_##subname			{

	#define	substruct(subname,parentname)				\
	struct	II_##subname			{					\
		II_##parentname	parentinst;

	#define	endstruct(subname)		};					\
	union	I_##subname									\
		{	II_##subname II;subname I;}

	#define	startinst(strucname,instname)	 			\
		II_##strucname	I_##instname	=	{

	#define	endinst(strucname,instname)	 	};			\
		strucname&	instname=*(strucname*)&I_##instname;
#undef 	DEFAULT_PLANETYP
#else
//
// This definition defines substructures by simple inheritance
// That will not allow initialisation.
//
#include	"shapenum.g"
	#define	emptybasestruct(subname,parentname) struct	subname : parentname	{

	#define	basestruct(subname) struct	subname					{

	#define	substruct(subname,parentname) struct	subname : parentname	{

	#define	endstruct(subname)		}

enum	ModelPatch	{PATCHWW1=1,PATCHWW2,PATCHWW3,PATCHMAX=0xffffffff};
enum	InstType	{lightinstrumtypes=0};

//DeadCode RDH 02Jul96 enum	ScaleFactor	{WW1SCALEFACTOR=1,WW2SCALEFACTOR=10,WW3SCALEFACTOR=100};
//DeadCode ARM 02Aug96 moved to flyinit
//DeadCode ARM 02Aug96 enum 	AerobaticFactor {AEROBATIC_LOW,AEROBATIC_MEDIUM,AEROBATIC_HIGH};

//DeadCode CSB 28/09/98	MINMAX(WingSpan,0,32767);
//DeadCode CSB 28/09/98	MINMAX(AileronSpan,0,32767);
//DeadCode CSB 28/09/98	MINMAX(MaxAilDeflect,0,65535);
//DeadCode CSB 28/09/98	MINMAX(WingArea,0,32767);
//DeadCode CSB 28/09/98	MINMAX(ParasiticDragArea,0,32767);
//DeadCode CSB 28/09/98	MINMAX(Wing_AR,0,300);
//DeadCode CSB 28/09/98	MINMAX(AdverseYawEffect,0,100);
//DeadCode CSB 28/09/98	MINMAX(TailSpan,0,32767);
//DeadCode CSB 28/09/98	MINMAX(TailArea,0,32767);
//DeadCode CSB 28/09/98	MINMAX(TailLiftModifier,0,32767);
//DeadCode CSB 28/09/98	MINMAX(TailDragModifier,0,32767);
//DeadCode CSB 28/09/98	MINMAX(RudderLiftModifier,0,32767);
//DeadCode CSB 28/09/98	MINMAX(RudderDragModifier,0,32767);
//DeadCode CSB 28/09/98	MINMAX(Tail_AR,0,300);
//DeadCode CSB 28/09/98	MINMAX(Fin_AR,0,300);
//DeadCode CSB 28/09/98	MINMAX(FinArea,0,32767);
MINMAX(WeightEmpty,0,100000);
MINMAX(FuelLoad,0,2000000000);
MINMAX(FuelTankCap,0,200000000);
MINMAX(FuelTankXpos,-32767,32767);
//DeadCode CSB 28/09/98	MINMAX(FuelABon,0,65535);
MINMAX(FuelABoff,0,65535);
//DeadCode CSB 18/11/98	MINMAX(FuelCruise,0,65535);
MINMAX(ThrustperStage,0,65535);
MINMAX(ABStages,0,65535);
MINMAX(MilMax,0,65535);
MINMAX(MaxTurnRate,0,65535);
MINMAX(MaxRollRate,0,65535);
MINMAX(MaxPitchRate,0,65535);
MINMAX(MaxAil,0,65535);
MINMAX(MaxAccel,0,262143);
MINMAX(RollRateAccel,0,65535);
MINMAX(LandingSpeed,0,2147483648);
MINMAX(MaxDiveRpm,0,65535);
MINMAX(MaxRpm,0,65535);
MINMAX(FreeRpm,0,65535);
MINMAX(MaxTorque,0,65535);
MINMAX(MinRpm,0,65535);
MINMAX(BestClimbVel,0,2147483648);
MINMAX(MaxDiveVel,0,2147483648);

MINMAX(MaxVel,0,2147483648);
MINMAX(MinVel,0,2147483648);
MINMAX(CruiseVel,0,2147483648);
MINMAX(BestClimbAng,0,65536);	//CSB 28/09/98
MINMAX(BestClimbSpeed,0,2147483648);	//CSB 28/09/98
MINMAX(MaxVelSL,0,2147483648);	//CSB 28/09/98

MINMAX(MaxVelDive_0km,0,2147483648);	//CSB 28/09/98
MINMAX(MaxVelDive_11km,0,2147483648);	//CSB 28/09/98
MINMAX(MaxVelDive_20km,0,2147483648);	//CSB 28/09/98

MINMAX(MovableFireZoneType,-32768,32767);
MINMAX(Damage,0,65535);
//DEADCODE CSB 08/11/99 MINMAX(MoI,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(RotMoI,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(RotDirection,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(GyroEffectPerThou,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CMAlfa,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CMDelta,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CMQ,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CMO,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CMGamma,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CMPee,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CM_acwb,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(XChord,-32768,32767);									//ARM 04Jun96
//DEADCODE CSB 08/11/99 MINMAX(CoG_Neut,-1000,1000);
//DEADCODE CSB 08/11/99 MINMAX(TailDistance,0,32767);
//DEADCODE CSB 08/11/99 MINMAX(Wing_Incidence,0,65535);
//DEADCODE CSB 08/11/99 MINMAX(Tail_Incidence,0,65535);
//DEADCODE CSB 08/11/99 MINMAX(Ailmin,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(ABrake,0,65535);
//DEADCODE CSB 08/11/99 MINMAX(TrimMin,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(TrimMax,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(FinSlope,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(ClFinNom,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CLFinDenom,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(LiftFlapAngle,-32768,32767);
//DeadCode RDH 17Jun96 MINMAX(LiftAngle,0,65535);
//DeadCode RDH 26Mar98 MINMAX(LiftCurve,-32768,32767);
//DeadCode RDH 26Mar98 MINMAX(StallAngle,0,65535);
//DeadCode RDH 17Jun96 MINMAX(LiftBase,-32768,32767);
//DeadCode RDH 26Mar98 MINMAX(DragCurve,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(CDenom,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(Friction,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(Efff,-32768,32767);
//DEADCODE CSB 08/11/99 MINMAX(MaxIRot,-32768,32767);
//DeadCode CSB 16/11/98	MINMAX(ThrustCurve,-32767,32767);
//DEADCODE CSB 08/11/99 MINMAX(Abstage,0,32767);

enum	ACFlags	{hooka=1,bda=2,HUDINACTIVE=4,etca=8};
//DeadCode CSB 19/11/98	MINMAX(MaxCeilingGoodW,	0,10000000);
//DeadCode CSB 19/11/98	MINMAX(MaxCeilingBadW,	0,10000000);
//DeadCode CSB 19/11/98	MINMAX(OpCeiling,		0,10000000);
MINMAX(FightCeiling,	0,10000000);
//DeadCode CSB 19/11/98	MINMAX(FightFloor,		0,10000000);
MINMAX(Abs_Ceiling,		0,10000000);	//CSB 29/09/98
MINMAX(MuzzleVel,		0,2147483648);
#endif
#define	DEFAULT_PLANETYP 0

//TempCode JIM 23Jan96 basestruct(PlaneInit)	//stuff from planetype that is only used for initialisation

//TempCode JIM 23Jan96 isbasestruct(TextBlockKnown);
//DeadCode JIM 23Jan96 #define	II_TextBlockKnown	dummy();
struct	DumbPlaneType;
struct	PlaneType;

basestruct(PlaneInit)
	WeightEmpty	weightempty;
	FuelLoad	maxintfuel;
	FuelTankCap fueltankcap[4];
	FuelTankXpos fueltankxpos[4];
	FuelTankType fueltanktype[4];
	operator	DumbPlaneType* ()	{return(DumbPlaneType*)this;}
	operator	PlaneType* ()	{return(PlaneType*)this;}

endstruct(PlaneInit);

substruct(WheeledType,PlaneInit)
	ShapeNum	shadowshpno;
	PlaneTypeSelect			planetext;	//	TextSnip0	planetext;
	ShapeNum	visible,SAGsubshape,commsVisible;				//RJS 12Oct00
	FuelABoff	fuelaboff;
//DeadCode CSB 18/11/98		FuelCruise	fuelcruise;
	
	int	/*MaxVel*/		 	maxvel;
	int	/*MinVel*/			minvel;
	int	/*CruiseVel*/		cruisevel;

	int	/*BestClimbVel*/	bestclimbvel;
		ANGLESInst		 	bestclimbpitch;
	int	/*MaxDiveVel*/	 	maxdivevel;
	MaxAccel	maxaccel;
	ANGLESInst				turnpercs;
	int						radiusturn;

endstruct(WheeledType);

substruct(DumbPlaneType,WheeledType)
	ShapeNum	cockpit1;										//PD 20Jun96
	GunnerInfo	gunnerpit[4];									//RJS 11Oct00
	Float		cockscale;										//RJS 19Jan99
	ANGLESInst	hdgarc;											//RJS 03Dec99
	ANGLESInst	pitchmax;										//RJS 03Dec99
	ANGLESInst	pitchmin;										//RJS 03Dec99
	SWord		finpitch;											  //CSB 17/12/99
	UWord		finlhdgmin;											  //CSB 17/12/99
	UWord		finlhdgmax;											  //CSB 17/12/99
	UWord		finrhdgmin;											  //CSB 17/12/99
	UWord		finrhdgmax;											  //CSB 17/12/99
	ULong		phrasename;										//RJS 10Feb99
	AerobaticFactor	aerobaticfactor;
	ANGLESInst		deckangle;
	UWord			deckshunt;
	MaxRollRate	maxrollrate;
//DeadCode CSB 22/02/99		MaxTurnRate	maxturnrate;
	MaxPitchRate	maxpitchrate;
	LandingSpeed	landingspeed;
	MaxDiveRpm	 	maxdiverpm;
	FreeRpm	 	freerpm;
	MaxRpm	 	maxrpm;
	MinRpm	 	minrpm;
//DeadCode CSB 19/11/98		MaxSafeVel	 	maxsafevel;
	MovableFireZoneType	movablefirezonetype;
	Damage		damage;
	   
//DeadCode CSB 19/11/98		MaxCeilingGoodW	maxceilinggoodw;
//DeadCode CSB 19/11/98		MaxCeilingBadW	maxceilingbadw;
//DeadCode CSB 19/11/98		OpCeiling		opceiling;	
	FightCeiling	fightceiling;
//DeadCode CSB 19/11/98		FightFloor		fightfloor;	
	Abs_Ceiling		abs_ceiling;
	Float	 	maxturnrateaoaSL;

	MuzzleVel		muzzlevel;
	FileNum			gunsnd[5];									//RJS 31Jul00
	FileNum			enginesnd;									//RJS 09Jun00
	FileNum			enginesubsnd;									  //CSB 14/01/00
	FileNum			enginestartsnd;									  //CSB 14/01/00
	UByte			noGuns;										//RJS 29Mar99
	SWord			gundelay;									//RJS 12Apr99
	UWord			gunfrequency;								//RJS 31May99

       
endstruct(DumbPlaneType);

substruct(PlaneType,DumbPlaneType)

	InstType	insttype;
	ACFlags		acflags;
//DeadCode CSB 16/11/98		ThrustCurve	thrustcurve[14];
//DeadCode CSB 16/11/98		Float		thrustaltcurve[21];

	BestClimbAng	bestclimbang[21];	//CSB 28/09/98
	BestClimbSpeed  bestclimbspeed[21];	//CSB 28/09/98
	MaxVelSL		maxvelsl[21];	//CSB 14/10/99	
	
	MaxVelDive_0km	maxveldive_0km;	//CSB 28/09/98
	MaxVelDive_11km	maxveldive_11km;	//CSB 28/09/98
	MaxVelDive_20km	maxveldive_20km;	//CSB 28/09/98

	ULong		version;

	void (*pSetupFunction) (AirStrucPtr const, ULong);		//ARM 28Jan97

endstruct(PlaneType);

typedef	PlaneType	*PTypePtr;

#undef	basestruct
#undef	emptybasestruct
#undef	substruct
#undef	endstruct

extern	PlaneInit*	Plane_Type_Translate[];

#endif

