//
//MODULE:	stub3d.cpp
//
//TASK:		manages the 3d thread
//
//ROUTINES:	presently about 5 routines:
//
//	MakeInteractive(WinMode,Coords)
//	WinMode(WinMode,Coords)
//	MakeResize(WinMode,Coords)
//	ToggleInteractive(bool)
//	TogglePaused(bool)
//	ToggleAccel(bool)
//	DeleteWorld()
//
//	WinMode:
//		FullScreen/Windowed/DualScreen
//							0x0000,0x1000,0x2000
//		Accelerated			0x000=no,0x100=yes,
//							0x10n=specific card
//							0x1m0=specific mode

#ifndef	STUB3d_defined
//#include	"stdafx.h"
//#include	<afxmt.h>
#include <dinput.h>

///////////////////////////////
class CLock
{
public:
    CLock()
    {
        InitializeCriticalSection(&m_CriticalSection);
    }
    ~CLock()
    {
        DeleteCriticalSection(&m_CriticalSection);
    }
    void Acquire()
    {
        EnterCriticalSection(&m_CriticalSection);
    }
    void Release()
    {
        LeaveCriticalSection(&m_CriticalSection);
    }
private:
    CLock(const CLock&);    // disabling copy constructor
    CRITICAL_SECTION m_CriticalSection;
};
 

// Using RAII to make unlocking cleaner and safer
class mCAutoLock
{
public:
    mCAutoLock(CLock& lock)
        : m_Lock(lock)
    {
        m_Lock.Acquire();
    }
    ~mCAutoLock()
    {
        m_Lock.Release();
    }
private:
    CLock &m_Lock;
};
 
#define CONCAT_MACRO1(var_name, counter) var_name##counter
#define CONCAT_MACRO2(var_name, counter) CONCAT_MACRO1(var_name, counter)
#define CONCAT_COUNTER(var_name) CONCAT_MACRO2(var_name, __COUNTER__)
// automatic name generation for the __auto_lock stack object
#define LOCK_SCOPE(var) mCAutoLock CONCAT_COUNTER(__auto_lock)(var)
///////////////////////////////

#ifdef __GNUC__
static inline long _rowan_InterlockedExchange(volatile long * const Target, const long Value)
{
	/* NOTE: __sync_lock_test_and_set would be an acquire barrier, so we force a full barrier */
	__sync_synchronize();
	return __sync_lock_test_and_set(Target, Value);
}
/* clang reserves the _InterlockedExchange builtin name; map the legacy name */
#define _InterlockedExchange _rowan_InterlockedExchange

#endif

inline	long LockExchange(volatile long* loc,long newval=0)
{
return _InterlockedExchange(loc, newval);
/*
	int rv;
    #ifndef    __BCPLUSPLUS__
	_asm	{	mov		eax,newval
				mov		ebx,loc
				xchg	ds:[ebx],eax
				mov		rv,eax
			}
    #else
    rv=0; 
    #endif
	return	rv;
*/
}
#define STUB3d_defined

class	WorldStuff;
class	WorldRef
{
	WorldStuff* w;
public:
	WorldStuff*  operator=(WorldStuff* W)	{return w=W;}
	operator	WorldStuff&	()				{return *w;}
	WorldStuff*	operator	&	()			{return w;}
	operator	WorldStuff*	()				{return w;}
};

struct	WinMode
{
	enum	Mode	{
		NONE=-1,
		FULL=0x0000,WIN=0x1000,DUAL=0x2000,
		SOFT=0x000,HARD=0x100,
		H_PRIM=0x101,H_SEC=0x102,H_TIRT=0x103,
		H_8P=0x110,H_8F=0x120,
		H_12_16=0x140,H_15_16=0x150,H_16=0x160,
		H_24=0x180,
		H_24_32=0x1C0,H_30_32=0x1D0,H_32=0x1E0
	};
	enum	Mask	{DISP=0xf000,HW=0x0f00,SLOT=0x01f0,DEPTH=0x010f};
};
inline WinMode::Mode operator | (WinMode::Mode a,WinMode::Mode b)
{return WinMode::Mode(int(a)|int(b));}

inline WinMode::Mode operator + (WinMode::Mode a,WinMode::Mode b)
{return a|b;}

inline WinMode::Mode operator & (WinMode::Mode a,WinMode::Mask b)
{return WinMode::Mode(int(a)&int(b));}
inline WinMode::Mode operator & (WinMode::Mask a,WinMode::Mode b)
{return WinMode::Mode(int(a)&int(b));}
class	View3d;
struct	KeyMap3d;
class	CEvent;
//DEADCODE PD 03/12/99 class	Display;
/* xor BAD code
#ifdef UNICODE
#define IID_IDirectInputDevice IID_IDirectInputDeviceW
#define IDirectInputDevice IDirectInputDeviceW
#define IDirectInputDeviceVtbl IDirectInputDeviceWVtbl
#else
#define IID_IDirectInputDevice IID_IDirectInputDeviceA
#define IDirectInputDevice IDirectInputDeviceA
#define IDirectInputDeviceVtbl IDirectInputDeviceAVtbl
#endif
*/
struct IDirectInputA;
typedef IDirectInputA *LPDIRECTINPUT;
#ifdef ROWAN_DINPUT_STUB // RERUN: shared dinput stub provides the canonical type
typedef IDirectInputDeviceA *LPDIRECTINPUTDEVICE;
#else
typedef struct IDirectInputDevice *LPDIRECTINPUTDEVICE;
#endif
struct	LiveList;

class	Inst3d;
class	CLib3D;

class	Mast3d
//#ifdef	DECLARE_HANDLE

{
//x0r #ifndef	_WINDEF_
//#define	HINSTANCE	HWND
//#endif

//x0r #ifdef	__AFXMT_H__

static void CALLBACK StaticTimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 );

void TimeProc(UINT uID, UINT uMsg, DWORD dw1, DWORD dw2 );
//#endif
	friend	class	fileman;
	friend	class	CMIGApp;
	friend	class	View3d;
	friend	class	Inst3d;
	friend	class	DPlay;
	friend	class	COverlay;

	enum	{EVENT_KEYS=0,EVENT_MOUSE,EVENT_AGGREGATOR,NUM_EVENTS=3};
	HANDLE				htable[NUM_EVENTS];
	HINSTANCE			hinst;
	int				uTimerID;
	int				ticknum;
	int				loopticks;
public:
	HWND				winst;
	LPDIRECTINPUT		g_lpDI;
	LPDIRECTINPUTDEVICE	g_lpDIDevice;
	CLib3D				*g_lpLib3d;
	Inst3d*	currinst;
	Mast3d();
	void	Init(HINSTANCE			hinst,HWND				hwind);
	~Mast3d();
	void	MainInit(void);
//DeadCode AMM 24Aug00 	void	QuitGame(void );
	void	Stop();
	void	SmallWin();
	void	BigWin();

}
//#endif
;
extern	Mast3d	Master_3d;


class	Inst3d
{	//master control for ongoing 3d world instances
	friend	class	CMIGApp;
	friend	class	View3d;
	friend	class	Mast3d;
	friend	class	Replay;
	friend	class	Persons2;
	friend	class	Persons3;
	friend	class	DPlay;

	enum {
		MAX_ACCEL_FRAME=100,
#ifndef	NDEBUG
		MAX_NORMAL_FRAME=7
#else
		MAX_NORMAL_FRAME=20
#endif
	};
	int	accelframes;
	bool		accel,paused,interactive;
	View3d*		viewedwin;
	Inst3d*		nextinst;
//	static char		lastkeys[256];
	static	KeyMap3d*	commonkeymaps;
	WorldRef	world;
	LiveList*	livelist;
	long		blocktick,blockticks;
	void	BlockTick(Bool setit);
	bool	mapview;
	int		timeofday;

public:
	Inst3d();
	Inst3d(bool);
	~Inst3d();
	View3d* Interactive(View3d* newwin);
	bool Paused(bool newmode);
	bool Accel(bool newmode);
	View3d* Drawing(View3d* newwin);
	View3d* Interactive();
	bool Paused();
	bool Accel();
	View3d* Drawing();
	static	bool	InThe3D();//	{return !currinst->Paused();}
	static	void	ReleaseDirectX();
	static	void	RestoreDirectX();

void	DoMoveCycle();
//DeadCode AMM 12May99 void	MoveCycle(int timeofday,WorldStuff* worldref);
void	MoveCycle(WorldStuff* worldref);						//AMM 11May99

//DeadCode AMM 06Oct98 void	SkipCycles(ULong num);									//AMM 16Sep98


	static void	OnKeyDown(int key);
	static void	OnKeyUp(int key);
private:
	static void OnKeyInput();
};
class	RDialog;
class	ViewPoint;
#ifdef __AFXWIN_H__
class	View3d
{
	friend	class	CMIGApp;
	friend	class	Inst3d;
	friend	class	Mast3d;

	typedef	WinMode::Mode	WinMode;
 	ViewPoint*	View_Point;
	HWND		window;
	CWnd*	mfcwin;
	CRect		coords;
	WinMode		mode;
	Inst3d*		inst;
	View3d*		nextview;
	CEvent*		E;
	KeyMap3d*	keymap;
//DEADCODE PD 03/12/99 	Display*	Whole_Screen;
	enum	DrawState {D_NO=0,D_YES,D_SWITCH,D_CLOSE}
			drawing;
	static UINT AFX_CDECL drawloop(LPVOID);
	void	SetEndDraw(DrawState d);
	int		doneframe,frametime,lastframetime,timeSinceLastMove;
	int		realframetime,lastrealframetime;
	void	DoneFrame();
	void	CloseWindow(const ULong id=IDOK);
public:
	void	BlockTick(Bool setit);
	int	PeekFrameTime();
	int	LastFrameTime();
	int	RealFrameTime()	{return lastrealframetime;}
	int TimeSinceLastMove();
	int TimeOfDay()		{return inst->timeofday;}
	void SetTimeOfDay(int time) {inst->timeofday=time;}			//AMM 12May99
	int	MakeInteractive	(WinMode	v=WinMode::FULL,const CRect& pos=*(CRect*)NULL,bool flag=false,bool flag2=false);
	int	MakePassive		(WinMode	v=WinMode::FULL,const CRect& pos=*(CRect*)NULL,bool flag=false,bool flag2=false);
	int	MakeResize		(WinMode	v=WinMode::FULL,const CRect& pos=*(CRect*)NULL);
	bool Interactive(bool newmode)
	{	return (this==inst->Interactive(
						newmode	?this
								:(inst->viewedwin==this)
									?NULL
									:inst->viewedwin));
	}
	bool Paused(bool newmode)		{return inst->Paused(newmode);}
	bool Accel(bool newmode)		{return inst->Accel(newmode);}
	bool Drawing(bool newmode);
	bool Interactive()				{return (this==inst->Interactive());}
	bool Paused()					{return inst->Paused();}
	bool Accel()					{return inst->Accel();}
	bool Drawing()					{return drawing==D_YES;}


	int	WaitEndDraw(DrawState d,int timeoutmilisec=INFINITE);

	bool InThe3D()	{return Drawing();}

//DeadCode AMM 06Oct98 	void	SkipCycles(ULong num);								//AMM 16Sep98

	View3d(Inst3d* i,HWND,CWnd*);
	~View3d();
};
#endif




#endif
