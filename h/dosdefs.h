//------------------------------------------------------------------------------
//Filename       dosdefs.h
//System
//Author         Paul.
//Date           Tue 4 Jul 1995
//Description    PLEASE DON'T PUT INCLUDES IN HERE.
//				THIS SHOULD BE THE BAREST MINIMAL FILE!
//
//------------------------------------------------------------------------------
//I am told that this works... we shall see!
#ifndef	dosdefs_Included
#define	dosdefs_Included

#include <cstddef>

#define DIRECTINPUT_VERSION 0x0700

#ifdef _AFXDLL
 #include <afxwin.h>
#else
 #include <windows.h>
#endif

#if defined(__GNUC__) && !defined(_WIN32)
 // RERUN: Linux-only; under mingw _snprintf/_vsnprintf/_WINBASE_ are real CRT decls
 #define _WIN32_WINNT  0x0500
 #define _vsnprintf vsnprintf
 #define _snprintf snprintf
 #define _WINBASE_
#endif

#ifdef __GNUC__
#define MYCALL
#define MYPREFIX & //RERUN: GCC also needs & for member-fn-ptr qualification
#else

 #if     _MSC_VER >= 1300
  #define MYCALL __thiscall
  #define MYPREFIX &
 #else
  #define MYCALL __cdecl
  #define MYPREFIX 
 #endif

#endif

//#ifndef NDEBUG 
  #include <iostream>
  #define TRACING(x) std::clog<< x << std::endl;
/*
#else
  #define TRACING(x)
#endif	
*/

/*
typedef long LONG;
#ifndef _W64
#define _W64
#endif
typedef _W64 long LONG_PTR;
*/
//x0r TODO typedef long LONG_PTR; 
#if     _MSC_VER < 1300
//typedef _W64 long LONG_PTR;
typedef long LONG_PTR;
#endif

#ifdef __GNUC__
// RERUN: MSVC builtin __int64 -> macro so that
// "signed/unsigned __int64" still parse as signed/unsigned long long.
#include <stdint.h>
#define __int64 long long
#ifndef __fastcall
#define __fastcall __attribute__((fastcall))
#endif
#ifndef _fastcall
#define _fastcall __fastcall
#endif
#ifdef M_PI
#undef M_PI
#endif
#endif

#ifdef __BORLANDC__

#ifndef nullptr
#define nullptr 0
#endif

//#define M_PI 3.141592653589793238462
//typedef char * String;
#else
const double M_PI = 3.141592653589793238462;
#endif

#define _XSTR(x)         #x
#define TOSTR(x)        _XSTR(x)
//__HERE__ is a string describing the current source file and line!
#define __HERE__	__FILE__ "(" TOSTR(__LINE__) "): "
#define	warnmsg(text)	message(__HERE__ "          \t       " text)
#define TODO(msg)		message(__HERE__ "          \tTO DO: " msg)
//

#ifndef NDEBUG
    #ifndef	__BCPLUSPLUS__
    #undef new
	void* __cdecl operator new(size_t nSize, const char* lpszFileName, int nLine);
	void __cdecl operator delete(void* p, const char* lpszFileName, int nLine);
//	void* __cdecl operator new[](size_t nSize, const char* lpszFileName, int nLine);
//	void __cdecl operator delete[](void*, const char* lpszFileName, int nLine);
	#define DEBUG_NEW new(THIS_FILE, __LINE__)
	#define	DEBUG_NEW_MODE
	#ifndef	THIS_FILE_DEFINED
		#define	THIS_FILE	__FILE__
	#endif
    #endif
#ifndef DEBUG_NEW
	#define DEBUG_NEW new
#endif

#endif

//#define LOCAL_new(DEBUG_NEW_PARAMS)	new
//#define	DEBUG_NEW_PARAMS (__FILE__, __LINE__)

//#ifndef new
//extern void*  operator new(unsigned int nSize);
//
//extern void* __cdecl operator new(unsigned int nSize,const char* FileName, int nLine);
//#endif

//#ifndef DEBUG_NEW
//        #if !defined(NDEBUG) && !defined(__BCPLUSPLUS__)
//            #define DEBUG_NEW new DEBUG_NEW_PARAMS
//        #else
//            #define DEBUG_NEW new
//        #endif
//#endif

//#define	new DEBUG_NEW
//
//
//these 2 are done always to override any sys lib garbage
#ifdef	__WATCOMC__
#undef new
	#pragma warning	690	2
#endif

#ifndef __BORLANDC__
/* winemaker: #pragma pack (1) */
#include <pshpack1.h>
#endif

/*
#ifdef	__SW_OM
#ifdef	__SW_OA
	#ifdef	__SW_OR
	#ifdef	__SW_OL
		#ifndef	__SW_OD
				#define	NDEBUG
		#endif
	#endif
	#endif
#endif
#endif

#ifdef __QNX
	#undef	__QNX
#endif
*/
#ifdef	__NT__
	#define WIN95
#endif
//
// Fixes for 'useless' warnings:
#ifdef	_MSC_VER
#ifndef	__MSVC__
#define	__MSVC__
#endif
#ifndef	WIN95
#define	WIN95
#endif
#endif
#ifdef	__WATCOMC__
#pragma warning	389	9				// value may be truncated
#pragma warning	14	8				// defined but not referenced
#pragma warning	139	4				// enumeration not assigned from its enumeration
#pragma warning	7	7				// &array not intended result
#pragma warning	690	2				// Fix against "condition is always true"
#endif
#ifdef __MSVC__

#if   ( _MSC_VER >= 1300 && _MSC_VER < 1700 )
#ifndef nullptr
const                        // this is a const object...
class {
public:
  template<class T>          // convertible to any type
    operator T*() const      // of null non-member
    { return 0; }            // pointer...
  template<class C, class T> // or any type of null
    operator T C::*() const  // member pointer...
    { return 0; }
private:
  void operator&() const;    // whose address can't be taken
} nullptr = {};              // and whose name is nullptr
#endif
#else
#define nullptr NULL
#endif

//HAPPY TO LOSE THESE
//4097 class synonym;
//4510 union constructor;
//4610 nonstandard conversion;
//4725 inaccurate pentium;
//4201 nameless struct
//4200 zero-sized array
// // // #pragma warning( disable : 4097 4510 4610 4725 4201 4200 4482)
//4244 math truncation
//4103 alignment changed!
//4305 math truncation
//4003 not enough parameters for macro
//4309 conversion - truncation
//4514 unreferenced function removed
//4512 class default assignment operator not possible
//4201 nameless struct
//4230 obsolete procedure qualifiers
//4710 inline ignored

//x0r #pragma warning( disable : 4244 4103 4305 4003 4309 4514 4512 4201 4230 4710)
#pragma warning( disable : 4244 4305 4018)
//not happy losing these, but given time, we can fix them
//4100 unreferenced parameter
//4018 signed unsigned comparison
//4101 unreferenced local
//4127 constant conditional
//4245 signed/unsigned mismatch
//4310 cast truncates constant
//4701 poss unassigned
//x0r #pragma warning( disable : 4100 4239 4018 4127 4101 4245 4310)
#pragma warning( disable : 4101)
// 4701)

//Level 4 pointless warnings:
//4201 Nameless struct/union	- won't go away! HAS TO BE DONE INSIDE THE NAMELESS STRUCT/UNION?
//4505 Unreferenced local function
//4213 Cast on l-value: seems to be BOOL ==> bool
//4711 Automatic inline
//4238 R-value used as L-value
//4063 Not a valid case - used for shapes
//4189 Initialised but not used
//x0r #pragma warning( disable :4505 4213 4711 4238 4063 4189)
#pragma warning( disable :4996)
#endif
//-this can be included wherever you want it, but not as a blanket thing.
//#pragma warning	690	6

//
// Do we want a bit of publicity? Of course we do!
//
//#define	PUBLICVERSION	1	//Same as usual
//#ifdef		PUBLICVERSION
//	#define	DEBUGGING	0
//#else

	#define	DEBUGGING	1
//TempCode PD 25Jan96 	#define	SHAPE_VIEWER	TRUE								//PD 08Jan96

//#endif

//#ifndef NULL
#undef NULL
//#define	NULL	0
#define	NULL	0 //RERUN: literal 0 is a null-pointer-constant incl. member pointers; const-int variable is not since C++11
//#endif 

//#define	_	[0]

//#define ZEROLOCK 0,0
//#define LOWLOCK	1,3
//#define MIDLOCK 4,6
//#define HIGHLOCK 7,9
/*
#ifdef	TRUE
#undef	TRUE
#undef	FALSE
#endif

typedef	enum	Bool	{BOOL_TRUE=1,BOOL_FALSE=0,BOOL_Align=255} Bool;
#define	TRUE	BOOL_TRUE
#define	TRUEST	BOOL_TRUE
#define	FALSE	BOOL_FALSE
*/
#undef FALSE
#undef TRUE

/*
typedef	enum	Bool	{BOOL_TRUE=1,BOOL_FALSE=0,BOOL_Align=255} Bool;
#define	TRUE	BOOL_TRUE
#define	TRUEST	BOOL_TRUE
#define	FALSE	BOOL_FALSE
*/
enum	Bool	{BOOL_TRUE=1,BOOL_FALSE=0,BOOL_Align=255,TRUE=BOOL_TRUE,FALSE=BOOL_FALSE};

//DeadCode DAW 30Jun96 enum	Bool	{TRUE=1,FALSE=0,BOOL_Align=255};

typedef	signed	char	SByte,*SByteP;
typedef	unsigned char	UByte,*UByteP;

typedef	signed	short	SWord,*SWordP;
typedef	unsigned short	UWord,*UWordP;

typedef	signed	long	SLong,*SLongP;
typedef	unsigned long	ULong,*ULongP;
typedef double 	Float,*FloatP;							//PD 06Jan97

typedef	char	* string,	//pointer to a character array
				**strind;			//pointer to pointer
typedef union	ifshare
{
	SLong	i;
	float	f;															//RJS 26May00
}
IFShare,*IFShareP;

//struct	rminfo
//{
//	long EDI;
//	long ESI;
//	long EBP;
//	long reserved_by_systemESP;
//	long EBX;
//	long EDX;
//	long ECX;
//	long EAX;
//	short flags;
//	enum	flagbits	{	CF=1,PF=4,AF=16,ZF=64,SF=128,
//							TF=256,IF=512,DF=1024,OF=2048
//						};
//	short ES,DS,FS,GS,IP,CS,SP,SS;
//};


//
//virtual width's height's
//
const int	FULLW	=25600;
const int	FULLH	=19200;
const int	FULLW_2	=(FULLW/2);
const int	FULLH_2	=(FULLH/2);
const int	TAB		=(FULLW/32);
const int	VTAB	=(FULLH/8);
const int	PIXEL640 	=40;											//RDH 18Jan96

//cludge for fact that Paul encoded yards instead of metres in map scaling!
const double MAPSCALE = 1.1;
#include <cassert>
#define INT3 {assert(false);}
/*
#ifdef	__WATCOMC__
	#pragma	aux	INT3	= 0xCC		// breakpoint

#endif
#ifdef	__MSVC__
//	#include <stdio.h>
//	#include <stdlib.h>
//	extern FILE*	debugfile;

    #ifndef 	NDEBUG
	#ifndef	_IHATEINT3_
		#define	INT3 _asm {int 3}
	#else
		#define	INT3 _asm {nop}
	#endif
    #else
	#define	INT3	_asm	{}
    #endif

  #ifndef 	NDEBUG
	#define	NOP _asm {nop}
  #else
	#define	NOP	{}
  #endif

//	#define	INT3 {fprintf(debugfile,"%s INT3()\n",__FILE__);fflush(debugfile);}
//	#define	INT3 {;}
	#ifdef	LOG__CON
		static struct SSS{SSS(char*);} s_s_s(__HERE__ __DATE__ " " __TIME__);
	#endif
#endif
#ifdef	__GNUC__
    #ifndef     NDEBUG
        #ifndef _IHATEINT3_
          #include <signal.h>
          #define INT3 raise(SIGINT)
        #else
                #define INT3 {}
        #endif
    #else
        #define INT3    {}
    #endif
        #define NOP   {}

        #ifdef  LOG__CON
                static struct SSS{SSS(char*);} s_s_s(__HERE__ __DATE__ " " __TIME__);
        #endif


#endif

#ifdef __BCPLUSPLUS__
	#define	INT3	{}
	#define	NOP		{}
#endif
*/
        #define NOP   {}

#define	MINMAX(typename,minval,maxval)				\
	enum	typename	{typename##MIN=minval,typename##MAX=maxval}

//Constructor/destructor standouts
#define	CON	/*CON*/
#define	DES	/*DES*/

//external reference of structures
#define structptr(name)	struct	name;typedef name	*name##Ptr;
//#define classptr(name)	class	name;typedef name	*name##Ptr;

//standard "C" syntax extensions and standouts
#define	breakif(cond)	{if	(cond)	break;}
//#define	elser			/*else for returned if*/
#define	elseif			else if
#define	forever			for(;;)
#define	RETURN(p)		return(p)
//#define repeat			do
//#define	until(x)		while(!(x))
//x0r leads to bug #define	proc			void
//#define	NULLREF(t)		*(t*)NULL
#define	limitscope		/*followed by opening curley bracket*/
/*#ifndef NDEBUG
#define	default_neverreferenced	default:	assert(false)
#else*/
#define	default_neverreferenced	default:	bobassert(false,"Just referenced never-reference default");break
//#endif

typedef	struct	COORDS3D
{	SLong	X,Y,Z;
//x0r	COORDS3D&	operator = (const COORDS3D& src)	{X=src.X;Y=src.Y;Z=src.Z;return(*this);}
} Coords3D;


typedef	struct	fpCOORDS3D										//PD 02Apr97
{																//PD 02Apr97
	IFShare	X,Y,Z;												//PD 02Apr97
}																//PD 02Apr97
fpCOORDS3D;														//PD 02Apr97

	struct _DDSURFACEDESC;

//	struct _DDCAPS;												//JIM 25Jul96
struct _MDI_DRIVER;
typedef _MDI_DRIVER          // Handle to digital audio driver
MDI_DRIVER;
struct _DIG_DRIVER;
typedef _DIG_DRIVER          // Handle to digital audio driver
DIG_DRIVER;
struct _SEQUENCE;

#ifdef __WATCOMC__
//This protects BX from library screwups						//JIM 25Jul96
     #pragma aux __cdecl "_*"		\
                parm caller []		\
				value struct float struct routine [eax] \
                modify [eax ebx ecx edx]
#endif

#ifdef	__MSVC__
//struct	_iobuf;
//typedef	_iobuf	FILE;
#include <cstdio>

//#else
//#ifndef __GNUC__
//struct	__iobuf;
//typedef	__iobuf	FILE;
//#endif
#endif


struct _GUID;
typedef struct _GUID GUID;
typedef GUID *LPGUID;

//DeadCode DAW 17Nov97 struct _DPSESSIONDESC;
//DeadCode DAW 17Nov97 typedef struct _DPSESSIONDESC DPSESSIONDESC;
//DeadCode DAW 17Nov97 typedef DPSESSIONDESC* LPDPSESSIONDESC;
//DeadCode DAW 17Nov97 struct IDirectDraw2;
//DeadCode DAW 17Nov97 typedef struct IDirectDraw2			*LPDIRECTDRAW2;				//ARM 25Nov96
//DeadCode DAW 17Nov97
//DeadCode DAW 17Nov97 struct IDirectDraw        ;
//DeadCode DAW 17Nov97 struct IDirectDraw2        ;
//DeadCode DAW 17Nov97 struct IDirectDrawSurface 	;
//DeadCode DAW 17Nov97 struct IDirectDrawSurface2	 ;
//DeadCode DAW 17Nov97 							  ;
//DeadCode DAW 17Nov97 struct IDirectDrawPalette 	   ;
//DeadCode DAW 17Nov97 struct IDirectDrawClipper 		;
//DeadCode DAW 17Nov97 								 ;
//DeadCode DAW 17Nov97 struct _DDFXROP           		  ;
//DeadCode DAW 17Nov97 struct _DDSURFACEDESC     		   ;
//DeadCode DAW 17Nov97 struct IDirect3D					;
//DeadCode DAW 17Nov97
//DeadCode DAW 17Nov97
//DeadCode DAW 17Nov97 typedef struct IDirectDraw             *LPDIRECTDRAW;
//DeadCode DAW 17Nov97 typedef struct IDirectDraw2            *LPDIRECTDRAW2;
//DeadCode DAW 17Nov97 typedef struct IDirectDrawSurface      *LPDIRECTDRAWSURFACE;
//DeadCode DAW 17Nov97 typedef struct IDirectDrawSurface2     *LPDIRECTDRAWSURFACE2;
//DeadCode DAW 17Nov97
//DeadCode DAW 17Nov97 typedef struct IDirectDrawPalette      *LPDIRECTDRAWPALETTE;
//DeadCode DAW 17Nov97 typedef struct IDirectDrawClipper      *LPDIRECTDRAWCLIPPER;
//DeadCode DAW 17Nov97
//DeadCode DAW 17Nov97 typedef struct _DDFXROP                *LPDDFXROP;
//DeadCode DAW 17Nov97 typedef struct _DDSURFACEDESC          *LPDDSURFACEDESC;
//DeadCode DAW 17Nov97 typedef struct IDirect3D			*LPDIRECT3D;				//PD 03Feb97

template	<class	enumtype,int minval,int maxval> class	MakeField;
#define	MAKEFIELD(src,minval,maxval)		\
	typedef	MakeField<src,minval,maxval>	src##Field

#ifdef	__SW_EP
	extern "C" void ASM_TogglePrologCode(ULong,void*);
#endif

#ifdef __WATCOMC__
#define	DLLExport	_export
#define	__FAR		__far
#define	__NEAR		__near
#else
#ifdef __MSVC__
#define DLLExport	__declspec( dllexport )
#define __FAR
#define	__NEAR
//#define db(p1)	__asm _emit p1
//#define dw(p1)	__asm _emit p1/0x100 __asm _emit p1&0xFF
#else

#ifdef __GNUC__
#define DLLExport	__declspec( dllexport )
#define __FAR
#define	__NEAR
#endif

#endif
#endif

#endif  // dosdefs_Included


/* RERUN: pack(1) must be re-asserted on EVERY inclusion of this file.
   With precompiled headers the dosdefs_Included guard above is already
   defined (set during PCH generation), so a TU's own #include "dosdefs.h"
   would skip this whole file and never see pshpack1.h -- leaving the TU at
   default alignment while the PCH froze pack(1) types.  That split-layout
   broke nodebob.h's dual-pass II_/inherited struct pairs (detailbattlefield
   read 4 bytes early -> bogus FileNum -> "Battlefield didn't start with
   BFSAVE!").  Leaking the push here restores the pre-PCH invariant. */
#include <pshpack1.h>
