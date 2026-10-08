/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1
 	Subject to the provisions of this Agreement we now grant to you the
 	following rights in respect of the Source Code:
  2.1.1
  	the non-exclusive right to Exploit  the Source Code and Executable
  	Code on any medium; and
  2.1.2
  	the non-exclusive right to create and distribute Derivative Works.
 2.2
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5
	not to place any restrictions on the operability of the Source
	Code;
  3.1.6
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

//------------------------------------------------------------------------------
//Filename       lib3d.cpp
//System
//Author         Paul.
//Date           Mon 8 Nov 1999
//				 Maintained by Jon
//Description
//------------------------------------------------------------------------------
//#define _NOT_IN_SAMPLE
#ifdef _NOT_IN_SAMPLE
//TempCode JON 20Oct00 #define _DEBUG
//TempCode JON 20Oct00 #define	_MSC_VER 6000
//TempCode JON 20Oct00 #define	__MSVC__
//TempCode JON 20Oct00 #define WIN32
//TempCode JON 20Oct00 #define _DEBUG
//TempCode JON 20Oct00 #define _WINDOWS
//TempCode JON 20Oct00 #define _MBCS
//TempCode JON 20Oct00 #define _USRDLL
//TempCode JON 20Oct00 #define LIB3D_EXPORTS
//TempCode JON 20Oct00 #undef __WATCOMC__
//xor #include "math.h"
#endif

//#include "afxwin.h"
#include <math.h>
//DEADCODE MS 02/02/00 typedef	bool	GUID;
//xor #include "dosdefs.h"
#include <objbase.h>
#include <stdio.h>


//DEADCODE MS 02/02/00 #include <initguid.h>
#include <ddraw.h>
//DeadCode JON 27Sep00 //#define LINEAR_Z_FIX
//DeadCode JON 27Sep00 //#define NON_LIN_Z_FIX
//DeadCode JON 27Sep00 #define NON_LIN_Z_ADD
#define _INSIDE_LIB3D_

#include "lib3d.h"
#include "radix.h"
#include "alloc.h"
#include "macs.h"
/*
#ifndef	NDEBUG
#ifndef _NOT_IN_SAMPLE
#include "monotxt.h"
#endif
#undef	new
void * __cdecl operator new(unsigned int i,char const *,int)
{
    return operator new(i);
}
void  __cdecl operator delete(void* v,char const *,int)
{
    operator delete(v);
}
//void * __cdecl operator new[](unsigned int i,char const *,int)	{return operator new[](i);}
//void  __cdecl operator delete[](void* v,char const *,int)	{ operator delete[](v);}
#define	new	DEBUG_NEW
#endif
*/

//using namespace std;

//TEMPCODE JON 5/19/00 R3DVERTEX& R3DVERTEX::operator = ( const R3DVERTEX &source ) // 1/2 save...
//TEMPCODE JON 5/19/00 {
//TEMPCODE JON 5/19/00 	memcopy( this, &source, sizeof( R3DVERTEX ) );
//TEMPCODE JON 5/19/00 	return *this;
//TEMPCODE JON 5/19/00 }

//#include "d3dxcore.h"
//#ifndef __GNUC__
//void GetErrorDesc( HRESULT err, char* &desc );
//#else
void GetErrorDesc( HRESULT err, char* &desc ) {}
//#endif

extern VOID GetDXVersion( DWORD* pdwDXVersion, DWORD* pdwDXPlatform );

//#define WRITE_DEBUG_FILE

//#define FORCE_TNL_EMULATION
#define NO_HARD_TNL
//#define NO_TNL_LIGHTING // only do ambient lighting in t&l version.
//#define SOFT_MIPMAP
//#define _NOBBLE_BRIGHTER
//#define _NOBBLE_BRIGHTERSHAPE
#define PER_POINT_SPECULAR
//#define NO_LANDSCAPE_SPECULAR
//#define LIGHT_ALL_SPECULAR
//#define _INVERT_SHAPE_NORMALS
//#define _INVERT_LAND_NORMALS
#define _NO_LANDSCAPE_MIPMAPS
#ifdef _NO_VERTEX_SHARING_HDR
#define _NO_VERTEX_SHARING
#endif

//#define _NO_D3D_DEV_RELEASE // needed for the radeon for some reason when windowed

#ifndef	NDEBUG
//#define _FORCE_16BIT_Z // doesn't work on all cards
//#define _NO_DYNAMIC_TEXT_UPLOAD
//#define LIGHT_ALL_SPECULAR
//#define _DRAW_AXIS
//#define _NODOTS_
//#define MONO_DEBUG
//#define _WIPE_BACKGROUND
//#define _DRAWNORMALS
//#define _DRAWLIGHTVEC
#ifndef PER_POINT_SPECULAR
//#define _DRAW_SPEC_H
#endif
//#define _NOTEXTURES_
//#define _NO_FOG_
//#define _FORCE_SW_FOG_
//#define	_SHAPE_DEBUG_
//#define	_WBUFFERTEST_
//#define	_ZBUFFERTEST_
//#define _NO_GUARDBAND_CLIPPING_
//#define NO_CLEVER_FAN_CLIP
//#define _NO_VERTEX_SHARING
//#define _TEST_VERTEX_SHARING
//#define	_INVISIBLE_
//#define _NO_CLIPPING_RESIZE
//#define _ONLY_ONE_LANSDCAPE_TEXTURE
//#define _THROW_AWAY_CLIPPED
//#define _NO_ALPHA
const float CLIP_RESIZE_FACTOR = 4.0f;

#endif

#ifndef _NO_VERTEX_SHARING
//	#define DO_INDEXED_VB
#endif

//TempCode JON 26Oct00 #ifndef NDEBUG
//TempCode JON 26Oct00 // use the debug memcopy
//TempCode JON 26Oct00 inline void memcopy( void* t, const void* s, ULong size )
//TempCode JON 26Oct00 {
//TempCode JON 26Oct00 	UByte *targ = (UByte*)t;
//TempCode JON 26Oct00 	UByte *src = (UByte*)s;
//TempCode JON 26Oct00 	for ( ULong i = 0; i<size; i++ )
//TempCode JON 26Oct00 	{
//TempCode JON 26Oct00 		*targ++=*src++;
//TempCode JON 26Oct00 	}
//TempCode JON 26Oct00 }
//TempCode JON 26Oct00 #else
inline void memcopy( void* t, const void* s, size_t size )
{
    memcpy( t, s, size );
}
//TempCode JON 26Oct00 #endif




extern "C" {
    extern double   pow( double __x, double __y );
}

#ifdef	_SHAPE_DEBUG_
static	int	noPolysDebug;
#endif

// cheat to include
//#include "flagsw.cpp"

//DeadCode JON 21Aug00 D3DVALUE SPolygon::zFiddle=0.0;

ULong Lib3D::refCnt=0;

D3DDEVICEDESC7 Lib3D::selectedDevice= {0};
WORD Lib3D::polyVerts[MAX_VERTICES];
//DEADCODE JON 5/19/00 DWORD Lib3D::polyVertCount=0xFFFFFFFF;
DWORD Lib3D::vertexType;
//DEADCODE JON 5/19/00 R3DVERTEX *Lib3D::polyVertArray;
//DEADCODE JON 5/24/00 R3DTLVERTEX *Lib3D::polyVertArrayTL;
VPDESC Lib3D::vpDesc;

R3DMATRIX Lib3D::IDENTITY(	1.f, 0.f, 0.f, 0.f,
                            0.f, 1.f, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            0.f, 0.f, 0.f, 1.f);

//DeadCode JON 13Oct00 ULong Lib3D::fastSqrtTable[0x10000];

HRESULT Lib3D::lastError=S_OK;

//DEADCODE JON 5/25/00 R3DVERTEX	Lib3D::vertArray[MAX_VERTICES];
//DEADCODE JON 5/25/00 R3DVERTEX2	Lib3D::vertArray2[MAX_VERTICES];
//DEADCODE JON 5/25/00 R3DVERTEX3	Lib3D::vertArray3[MAX_VERTICES];
//DEADCODE JON 5/24/00 R3DTLVERTEX	Lib3D::tlVertArray[MAX_VERTICES];
UByte Lib3D::fogTable[1024];
R3DCOLOUR Lib3D::lightingTable[256];
R3DCOLOUR Lib3D::specularTable[256];
ULong Lib3D::gMemCheck;
ULong Lib3D::gRenderDepths;
Lib3D::DDMode Lib3D::selectedMode;
Lib3D::DDDriver Lib3D::selectedDriver;
bool Lib3D::fixZbuffer = false;
//D3DVALUE Lib3D::zFactor;
D3DVALUE SPolygon::zFactor;// = Lib3D::zFactor;
DWORD Lib3D::texturesTotalRAM;									//RJS 24Mar00   xor ULong -> DWORD
AlphaBlendTypes	Lib3D::lastBlendType;
D3DZBUFFERTYPE	Lib3D::prefZType;								//RJS 17May00


//DeadCode JON 7Sep00 Lib3D::NaffDriverID Lib3D::naffDriverTable[]=
//DeadCode JON 7Sep00 {
//DeadCode JON 7Sep00 	{Lib3D::ND_FireGL1KPro,	{0xD7B71EAC,0x7E47,0x11CF,{0x15,0x7A,0x27,0x21,0xA4,0xC2,0xC9,0x35}}},
//DeadCode JON 7Sep00 	{Lib3D::ND_ATIRagePro,	{0xD7B71EE2,0x0402,0x11CF,{0x87,0x6A,0x01,0x20,0xA5,0xC2,0xC9,0x35}}},
//DeadCode JON 7Sep00 	{Lib3D::ND_FireGL1KPro	,{0xD7B71EAC,0x7E47,0x11CF,{0x15,0x7A,0x27,0x21,0xA4,0xC2,0xC9,0x35}}},
//DeadCode JON 7Sep00 	{Lib3D::ND_RivaTNT		,{0xD7B71E3E,0x4360,0x11CF,{0x65,0x72,0x40,0x07,0xA7,0xC2,0xC9,0x35}}},
//DeadCode JON 7Sep00 	{Lib3D::ND_RivaTNT		,{0xD7B71E3E,0x4360,0x11CF,{0x80,0x63,0x01,0x20,0xA5,0xC2,0xC9,0x35}}},
//DeadCode JON 7Sep00 	{Lib3D::ND_GeoForce256	,{0xD7B71E3E,0x4240,0x11CF,{0xD1,0x62,0x01,0x20,0xB3,0xC2,0xC9,0x35}}},
//DeadCode JON 7Sep00 	{Lib3D::ND_GeoForce256	,{0xD7B71E3E,0x4240,0x11CF,{0xC0,0x62,0x01,0x20,0xB3,0xC2,0xC9,0x35}}},
//DeadCode JON 7Sep00 	{Lib3D::ND_SavagePro3	,{0xD7B75DD3,0xC962,0x11CF,{0xC1,0x2F,0x23,0xAA,0xA6,0xC2,0xC9,0x35}}}
//DeadCode JON 7Sep00 };
//DeadCode JON 7Sep00
//DeadCode JON 7Sep00 int Lib3D::ND_Max = sizeof( Lib3D::naffDriverTable )/sizeof( Lib3D::NaffDriverID );

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SineCosine
//Author		Paul.
//Date			Fri 26 Nov 1999
//
//------------------------------------------------------------------------------
inline void SineCosine(const UWord rowanAngle,D3DVALUE* sineAngle,D3DVALUE* cosineAngle)
{
    D3DVALUE radianAngle=D3DVALUE(SWord(rowanAngle))*ROWANANG_TO_RADANG;
//#ifdef __GNUC__
    *cosineAngle=cos(radianAngle);
    *sineAngle=sin(radianAngle);
    /*#else
    	__asm	push	edx;
    	__asm	push	ebx;
    	__asm	mov		edx,sineAngle;
    	__asm	fld		radianAngle;
    	__asm	fsincos;
    	__asm	mov		ebx,cosineAngle;
    	__asm	fstp	[dword ptr ebx];
    	__asm	fstp	[dword ptr edx];
    	__asm	pop		ebx;
    	__asm	pop		edx;
    #endif*/
}

inline void SineCosine_Radian(const D3DVALUE radianAngle,D3DVALUE* sineAngle,D3DVALUE* cosineAngle)
{
//#ifdef __GNUC__
    *cosineAngle=cos(radianAngle);
    *sineAngle=sin(radianAngle);
    /*#else
    	__asm	push	edx;
    	__asm	push	ebx;
    	__asm	mov		edx,sineAngle;
    	__asm	fld		radianAngle;
    	__asm	fsincos;
    	__asm	mov		ebx,cosineAngle;
    	__asm	fstp	[dword ptr ebx];
    	__asm	fstp	[dword ptr edx];
    	__asm	pop		ebx;
    	__asm	pop		edx;
    #endif*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		COUNT_BITS
//Author		Paul.
//Date			Fri 26 Nov 1999
//
//------------------------------------------------------------------------------
inline DWORD COUNT_BITS(DWORD bitField)
{
    DWORD bitCount=0;
    for (int i=0; i<32 && bitField!=0; i++,bitField>>=1)
        bitCount+=(bitField&1);
    return bitCount;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GET_BIT_POS
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
inline SWord GET_BIT_POS(UWord bitField)
{
    SWord pos;
    UWord mask;
    for (pos=15,mask=0x8000; (mask&bitField)==0 && pos>=0; --pos,mask>>=1);
    return pos;
}
inline SWord GET_BIT_POS32(DWORD bitField)
{
    SWord pos;
    DWORD mask;
    for (pos=31,mask=0x80000000; (mask&bitField)==0 && pos>=0; --pos,mask>>=1);
    return pos;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		fpSqrt
//Author		Paul.
//Date			Fri 26 Nov 1999
//
//------------------------------------------------------------------------------
inline D3DVALUE fpSqrt(D3DVALUE num)
{
//#ifdef __GNUC__
    return(sqrt(num));
    /*#else
       	__asm	fld 	num;
    	__asm	fsqrt;
    	__asm	fstp	num;
    	return num;
    #endif*/
}

//#pragma message (__HERE__ "inline me" )
inline ULong Lib3D::ClipCodeFBLRTB(D3DTLVERTEX *pV)
{
    ULong clipCode;
    D3DVALUE sz;
    if (pV->rhw < nearZPlane)		clipCode=CLIP_FRONT;
    else if (pV->rhw > farZPlane)	clipCode=CLIP_BACK;
    else							clipCode=0UL;

    FP_BITS(sz)=FP_ABS_BITS(pV->rhw);

    if ( pV->sx < -sz )				clipCode+=CLIP_LEFT;
    else if ( pV->sx > sz )			clipCode+=CLIP_RIGHT;
    if ( pV->sy < -sz )				clipCode+=CLIP_BOTTOM;
    else if ( pV->sy > sz )			clipCode+=CLIP_TOP;
    return clipCode;
}

//#pragma message (__HERE__ "inline me" )
inline ULong Lib3D::ClipCodeFBLRTB(SVertex *pV)
{
    ULong clipCode;
    D3DVALUE sz;
    if (pV->hw < nearZPlane)			clipCode=CLIP_FRONT;
    else if (pV->hw > farZPlane)		clipCode=CLIP_BACK;
    else								clipCode=0UL;

    FP_BITS(sz)=FP_ABS_BITS(pV->hw);

    if (pV->sx < -sz)			clipCode+=CLIP_LEFT;
    else if (pV->sx > sz)		clipCode+=CLIP_RIGHT;
    if (pV->sy < -sz)			clipCode+=CLIP_BOTTOM;
    else if ( pV->sy > sz )		clipCode+=CLIP_TOP;
    return clipCode;
}


inline ULong Lib3D::ClipCode2D(SVertex *pV)
{
    ULong clipCode=0UL;
    if ( pV->sx < -clipVal2D )		clipCode+=CLIP_LEFT;
    else if ( pV->sx > clipVal2D )	clipCode+=CLIP_RIGHT;

    if (pV->sy < -clipVal2D)		clipCode+=CLIP_BOTTOM;
    else if ( pV->sy > clipVal2D )	clipCode+=CLIP_TOP;

    return clipCode;
}
// is inlined from the inline version..  (see flagsw.cpp)
//#pragma warnmsg ( "inline me" )
inline ULong Lib3D::GenGuardBandClipCode( const SVertex* pV, const D3DVALUE sz, const ULong prevFlags )
{
    //inlined .. remove stupids at no cost but makes smaller..
    if (
        (prevFlags&CLIP_LEFT) && (prevFlags&CLIP_RIGHT) ||
        (prevFlags&CLIP_TOP) && (CLIP_BOTTOM&prevFlags)
    )
    {
//		INT3;
        return 0;
    }

    ULong clipCode=0UL;

    if ( (prevFlags&CLIP_LEFT) && (pV->sx < -(sz*guardBandModLeft)) )
        clipCode+=CLIP_LEFT;
    if ( (prevFlags&CLIP_RIGHT) && (pV->sx > (sz*guardBandModRight)) )
        clipCode+=CLIP_RIGHT;
    if ( (prevFlags&CLIP_BOTTOM) && (pV->sy < -(sz*guardBandModBottom)) )
        clipCode+=CLIP_BOTTOM;
    if ( (prevFlags&CLIP_TOP) && ( pV->sy > (sz*guardBandModTop) ) )
        clipCode+=CLIP_TOP;

//DeadCode JON 12Jun00 	if (pV->sx < -sz)			clipCode+=CLIP_LEFT;
//DeadCode JON 12Jun00 	else if (pV->sx > sz)		clipCode+=CLIP_RIGHT;
//DeadCode JON 12Jun00 	if (pV->sy < -sz)			clipCode+=CLIP_BOTTOM;
//DeadCode JON 12Jun00 	else if ( pV->sy > sz )		clipCode+=CLIP_TOP;

    return clipCode;
}

//#pragma warnmsg ( "inline me" )
// returns true if the thing need proper clipping...
inline bool Lib3D::GuardBandClipTest(SPolygon *poly)
{
    if ( hwClip && (poly->orcode&(CLIP_FRONT|CLIP_BACK))==0 )
    {
        SVertex* pV = poly->pVertexList;
        ULong polyCode = 0;

        for ( int i = poly->vertexcount; i!=0; i-- )
        {
            D3DVALUE sz;
            FP_BITS(sz)=FP_ABS_BITS(pV->hw);
//DeadCode  28Oct00 			sz*=guardBandMod;

            polyCode |= InlineGenGuardBandClipCode( pV, sz, (pV->clipcode&CLIP_LRTB) );

            pV=pV->pNext;
        }
        return (polyCode!=0);
//TempCode JON 12Jun00 		if ( polyCode== 0 )
//TempCode JON 12Jun00 		{
//TempCode JON 12Jun00 			return false;
//TempCode JON 12Jun00 		} else
//TempCode JON 12Jun00 		{
//TempCode JON 12Jun00 			return true;
//TempCode JON 12Jun00 		}
    }
    else
    {
        return true;
    }
}

inline ULong Lib3D::ClipCodeLRTB(SVertex *pV)
{
    ULong clipCode;
    D3DVALUE sz;
    FP_BITS(sz)=FP_ABS_BITS(pV->hw);
    if (pV->sx < -sz)		clipCode=CLIP_LEFT;
    else if (pV->sx > sz)	clipCode=CLIP_RIGHT;
    else					clipCode=0UL;
    if (pV->sy < -sz)		clipCode+=CLIP_BOTTOM;
    else if (pV->sy > sz)	clipCode+=CLIP_TOP;
    return clipCode;
}

inline ULong Lib3D::ClipCodeTB(SVertex *pV)
{
    ULong clipCode;
    D3DVALUE sz;
    FP_BITS(sz)=FP_ABS_BITS(pV->hw);
    if (pV->sy<-sz)		clipCode=CLIP_BOTTOM;
    else if (pV->sy>sz)	clipCode=CLIP_TOP;
    else				clipCode=0UL;
    return clipCode;
}

inline ULong Lib3D::ClipCodeTB2D(SVertex *pV)
{
    ULong clipCode;
    if (pV->sy < -clipVal2D)		clipCode=CLIP_BOTTOM;
    else if ( pV->sy > clipVal2D )	clipCode=CLIP_TOP;
    else							clipCode=0UL;
    return clipCode;
}

inline void Lib3D::Transform(const R3DVERTEX *pV,D3DTLVERTEX *pTV,R3DMATRIX *pM)
{
    pTV->sx=pM->_11*pV->x+pM->_21*pV->y+pM->_31*pV->z+pM->_41;
    pTV->sy=pM->_12*pV->x+pM->_22*pV->y+pM->_32*pV->z+pM->_42;
    pTV->sz=pM->_13*pV->x+pM->_23*pV->y+pM->_33*pV->z+pM->_43;
    pTV->rhw=pM->_14*pV->x+pM->_24*pV->y+pM->_34*pV->z+pM->_44;
}

inline void Lib3D::CALC_FOG(SPolygon *p1)
{
    if (flags&F_VERTEXFOG)
    {
        SVertex *pp=p1->pVertexList;
        for (int q=p1->vertexcount; q>0; q--)
        {
            pp->specular &= 0x00FFFFFF;
            SetColAlpha( pp->specular, fogTable[ (0x3FF&F2UL_Round( pp->hw*fogMul )) ] );
            pp=pp->pNext;
        }
    }
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure
//Procedure		BuildSqrtTable
//Author		Paul.
//Date			Fri 26 Nov 1999
//
//------------------------------------------------------------------------------
inline void Lib3D::BuildSqrtTable()
{
#ifdef _NOT_IN_SAMPLE
    INT3;
#else
    typedef union FastSqrtUnion
    {
        D3DVALUE 	f;
        ULong		i;
    }
    FastSqrtUnion;
    ULong i;
    FastSqrtUnion s;
    for (i=0; i<=0x7FFF; i++)
    {
        // Build a float with the bit pattern i as mantissa
        // and an exponent of 0, stored as 127
        s.i=(i<<8)|(0x7F<<23);
        s.f=(D3DVALUE)fpSqrt(s.f);

        // Take the square root then strip the first 7 bits of
        // the mantissa into the table
        fastSqrtTable[i+0x8000]=(s.i&0x7FFFFF);

        // Repeat the process, this time with an exponent of 1,
        // stored as 128
        s.i=(i<<8)|(0x80<<23);
        s.f=(D3DVALUE)fpSqrt(s.f);
        fastSqrtTable[i]=(s.i&0x7FFFFF);
    }
#endif
}

void Lib3D::SetNoRenderToTexture( void )
{
    if ( pDDS7MirrorZB != pDDSZ7 )
        DeRefAndNULL( IUnknownPtrRef( pDDS7MirrorZB ) );

    if ( pDDS7MirrorRT != pDDSB7 )
        DeRefAndNULL( IUnknownPtrRef( pDDS7MirrorRT ) );

    if ( pDDS7LandZB != pDDSZ7 )
        DeRefAndNULL( IUnknownPtrRef( pDDS7LandZB ) );

    if ( pDDS7MirrorRT != pDDSB7 )
        DeRefAndNULL( IUnknownPtrRef( pDDS7LandRT ) );

    pDDS7LandRT = pDDS7MirrorRT = pDDSB7;
    pDDS7MirrorZB = pDDS7LandZB = pDDSZ7;

    flags=Flags(flags&~F_TEXTURECANBERENDERTARGET);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckIfTextureCanBeRenderTarget
//Author		Paul.
//Date			Mon 29 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT	Lib3D::CheckIfTextureCanBeRenderTarget()
{
    HRESULT hr;
    DDSURFACEDESC2 ddsd;
    pDDS7LandRT=pDDS7MirrorRT=NULL;
    pDDS7LandZB=pDDS7MirrorZB=NULL;
    mirrorRect.left=mirrorRect.top=0;
    ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
    ddsd.dwWidth=ddsd.dwHeight=
                     mirrorRect.bottom=mirrorRect.right=128;
    ddsd.ddpfPixelFormat=texFmt[TF_LANDINIT];
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_3DDEVICE|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
    if ((hr=pDD7->CreateSurface(&ddsd,&pDDS7MirrorRT,NULL))!=DD_OK)
    {
        pDDS7LandRT=pDDS7MirrorRT=pDDSB7;
        pDDS7LandZB=pDDS7MirrorZB=pDDSZ7;
        return hr;
    }
    if ((selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_ZBUFFERLESSHSR)==0)
    {
        DDSURFACEDESC2 zbsd;
        zbsd.dwSize=sizeof(zbsd);
        if ((hr=pDDSZ7->GetSurfaceDesc(&zbsd))!=DD_OK)
        {
            pDDS7MirrorRT->Release();
            pDDS7LandRT=pDDS7MirrorRT=pDDSB7;
            pDDS7LandZB=pDDS7MirrorZB=pDDSZ7;
            return hr;
        }
        zbsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
        zbsd.ddsCaps.dwCaps=DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
        zbsd.dwWidth=ddsd.dwWidth;
        zbsd.dwHeight=ddsd.dwHeight;
        if ((hr=pDD7->CreateSurface(&zbsd,&pDDS7MirrorZB,NULL))!=DD_OK)
        {
            pDDS7MirrorRT->Release();
            pDDS7LandRT=pDDS7MirrorRT=pDDSB7;
            pDDS7LandZB=pDDS7MirrorZB=pDDSZ7;
            return hr;
        }
        if ((hr=pDDS7MirrorRT->AddAttachedSurface(pDDS7MirrorZB))!=DD_OK)
        {
            pDDS7MirrorZB->Release();
            pDDS7MirrorRT->Release();
            pDDS7LandRT=pDDS7MirrorRT=pDDSB7;
            pDDS7LandZB=pDDS7MirrorZB=pDDSZ7;
            return hr;
        }
    }
    pDDS7MirrorZB->Release();
    pDDS7MirrorRT->Release();
    pDDS7LandRT=pDDS7MirrorRT=NULL;
    pDDS7LandZB=pDDS7MirrorZB=NULL;

    return S_OK;
}
//
// Check to see if blitting from vidmem to vidmem is supported
// and find out if the blit can handle color conversion
//
HRESULT Lib3D::IsSlowCopyRequired()
{
    DDCAPS ddcaps;
    DDSURFACEDESC2 ddsd;
    LPDDPIXELFORMAT spf,dpf;

    // Assume slow copy is needed to begin with

    flags=Flags(flags|F_SLOWCOPY);

    // First get DD caps info

    ZeroMemory(&ddcaps,sizeof(ddcaps));
    ddcaps.dwSize=sizeof(ddcaps);
    pDD7->GetCaps(&ddcaps,NULL);

    if ((ddcaps.dwCaps&DDCAPS_BLTFOURCC)==0)
    {
        // Blit can't do color space conversion so slow copy
        // will be required if src & dst surfaces do not have
        // the same pixel format

        ZeroMemory(&ddsd,sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        pDDSB7->GetSurfaceDesc(&ddsd);
        dpf=&ddsd.ddpfPixelFormat;
        spf=texFmt+TF_LANDINIT;

        if (spf->dwRBitMask==dpf->dwRBitMask &&
                spf->dwGBitMask==dpf->dwGBitMask &&
                spf->dwBBitMask==dpf->dwBBitMask)
        {
            flags=Flags(flags&~F_SLOWCOPY);
        }
        return S_OK;
    }
    flags=Flags(flags&~F_SLOWCOPY);
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PerformVSlowCopy
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
HRESULT Lib3D::PerformVSlowCopy(LPDIRECTDRAWSURFACE7 dst,LPDIRECTDRAWSURFACE7 src,LPRECT rect)
{
    DDSURFACEDESC2 ddsdDst;
    LPDIRECTDRAWSURFACE7 intermediate;
    ZeroMemory(&ddsdDst,sizeof(ddsdDst));
    ddsdDst.dwSize=sizeof(ddsdDst);
    dst->GetSurfaceDesc(&ddsdDst);
    ddsdDst.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
    ddsdDst.ddsCaps.dwCaps=DDSCAPS_SYSTEMMEMORY|DDSCAPS_OFFSCREENPLAIN;
    ddsdDst.ddsCaps.dwCaps2=ddsdDst.ddsCaps.dwCaps3=ddsdDst.ddsCaps.dwCaps4=0;
    pDD7->CreateSurface(&ddsdDst,&intermediate,NULL);
    PerformSlowCopy(intermediate,src,rect);
    dst->Blt(NULL,intermediate,NULL,DDBLT_WAIT,NULL);
    intermediate->Release();
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		calcMWordRot
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
inline UWord calcMWordRot( SWord shift )
{
//	if ( shift < 0 )
//		return 32+shift;
//	else
//		return shift;
//	return UByte( SWord(32)+shift );//&UByte(31);
    return UByte( shift );
}
//#pragma optimize("y",off)
//#pragma optimize("tag",on)

inline ULong __fastcall  MagicRotate(UByte shift, ULong val )
{
    ULong rv;
//#ifdef __GNUC__
    shift &= 0x1f;
    if (!shift) return(val);

    return (val << shift) | (val >> (32 - shift));
/*#else
	
    __asm
    {
        mov edx, val
        mov cl, shift

        rol edx, cl

        mov rv, edx
    }
    return rv;
	return __ROL__(val, shift);

#endif
	*/
}

ULong __fastcall	MaskAndRot(ULong value,UByte sh1,UByte sh2,UByte sh3,ULong mask1,ULong mask2,ULong mask3)
{
    return ((MagicRotate(sh1,value)&mask1) |
            (MagicRotate(sh2,value)&mask2) |
            (MagicRotate(sh3,value)&mask3));
/*    __asm
    {
        mov	edx,value
        mov	eax,edx
        mov	cl,sh1
        mov	ebx,eax
        rol	eax,cl
        mov	cl,sh2
        and	eax,mask1
        rol	ebx,cl
        mov	cl,sh3
        and	ebx,mask2
        rol	edx,cl
        or	eax,ebx
        and	edx,mask3
        or	eax,edx
    }
*/
}

#define _DOINLINE inline
//#pragma optimize( "", off )
_DOINLINE void DoLocks( LPDIRECTDRAWSURFACE7 pDst,LPDIRECTDRAWSURFACE7 pSrc, DDSURFACEDESC2* ddsdSrc, DDSURFACEDESC2* ddsdDst)
{
    pSrc->Lock(NULL,ddsdSrc,DDLOCK_READONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
    pDst->Lock(NULL,ddsdDst,DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//	UWord *lpSrc=(UWord*)ddsdSrc->lpSurface;
//	UWord j = *lpSrc;
}
//#pragma optimize( "", on )

_DOINLINE void DoUnlocks(  LPDIRECTDRAWSURFACE7 pDst,LPDIRECTDRAWSURFACE7 pSrc )
{
    pDst->Unlock(NULL);
    pSrc->Unlock(NULL);
}

_DOINLINE ULong getULValue( ULong* src )
{
    return *src;
}

_DOINLINE void setUWValue( ULong src, UWord* trg )
{
    *trg=src;
}

inline HRESULT Lib3D::PerformSlowCopy(LPDIRECTDRAWSURFACE7 pDst,LPDIRECTDRAWSURFACE7 pSrc,LPRECT rect)
{
    DDSURFACEDESC2 ddsdSrc,ddsdDst;
    ddsdSrc.dwSize= ddsdDst.dwSize= sizeof(ddsdSrc);
    pSrc->GetSurfaceDesc(&ddsdSrc);
    pDst->GetSurfaceDesc(&ddsdDst);
    // Copy from the system surface to the destination surface with color conversion (dest is always 16 bit)
    // also scale at the same time
    SWord redShift,greenShift,blueShift;

    redShift=	GET_BIT_POS32(ddsdDst.ddpfPixelFormat.dwRBitMask)-GET_BIT_POS32(ddsdSrc.ddpfPixelFormat.dwRBitMask);
    greenShift=	GET_BIT_POS32(ddsdDst.ddpfPixelFormat.dwGBitMask)-GET_BIT_POS32(ddsdSrc.ddpfPixelFormat.dwGBitMask);
    blueShift=	GET_BIT_POS32(ddsdDst.ddpfPixelFormat.dwBBitMask)-GET_BIT_POS32(ddsdSrc.ddpfPixelFormat.dwBBitMask);

    UByte rMShift = calcMWordRot( redShift );
    UByte gMShift = calcMWordRot( greenShift );
    UByte bMShift = calcMWordRot( blueShift );

    ULong rmask=ddsdDst.ddpfPixelFormat.dwRBitMask&MagicRotate(rMShift,ddsdSrc.ddpfPixelFormat.dwRBitMask);
    ULong gmask=ddsdDst.ddpfPixelFormat.dwGBitMask&MagicRotate(gMShift,ddsdSrc.ddpfPixelFormat.dwGBitMask);
    ULong bmask=ddsdDst.ddpfPixelFormat.dwBBitMask&MagicRotate(bMShift,ddsdSrc.ddpfPixelFormat.dwBBitMask);

    // Alpha was never copied: a source without an alpha channel must land
    // opaque in an alpha destination (what a real DD Blt does), otherwise
    // every ARGB4444 texture loads fully transparent.
    ULong srcAMask=ddsdSrc.ddpfPixelFormat.dwRGBAlphaBitMask;
    ULong dstAMask=ddsdDst.ddpfPixelFormat.dwRGBAlphaBitMask;
    UByte aMShift=calcMWordRot(GET_BIT_POS32(dstAMask)-GET_BIT_POS32(srcAMask));
    ULong amask=dstAMask&MagicRotate(aMShift,srcAMask);

    DWORD swidth=rect==NULL?ddsdSrc.dwWidth:rect->right-rect->left;
    DWORD scale=1;  //xor it was strange
    for (scale; swidth!=ddsdDst.dwWidth; scale<<=1,swidth>>=1);

    DWORD lPitch=ddsdSrc.lPitch*scale; // this does the y scaling

    DoLocks( pDst, pSrc, &ddsdSrc, &ddsdDst );

//	pSrc->Lock(NULL,&ddsdSrc,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//	pDst->Lock(NULL,&ddsdDst,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);

    switch (ddsdSrc.ddpfPixelFormat.dwRGBBitCount)
    {
    case 16:
    {
        UWord *lpSrc=(UWord*)ddsdSrc.lpSurface;
        lpSrc=(UWord*)(ULong(lpSrc)+(lPitch*rect->top));			//JON 16Oct00
        lpSrc+=rect->left;
        UWord *lpDst=(UWord*)ddsdDst.lpSurface;
        for (DWORD y=ddsdDst.dwHeight; y>0;
                y--) // for each y in the destination
        {
            UWord *lpSrc2=lpSrc;
            UWord *lpDst2=lpDst;
            for (DWORD x=ddsdDst.dwWidth; x>0; x--) // for each x in the destination
            {
                //UWord a,r,g,b;

                *lpDst2++=MaskAndRot(*lpSrc2,rMShift,gMShift,bMShift,rmask,gmask,bmask)
                |UWord(dstAMask?(amask?UWord(MagicRotate(aMShift,*lpSrc2)&amask):dstAMask):0);

//DEADCODE JON 5/11/00 					r=redShift==0?r:redShift<0?r>>-redShift:r<<redShift;							//JON 5/11/00
//DEADCODE JON 5/11/00 					INT3;																								//JON 5/11/00
//DEADCODE JON 5/11/00 					r=MagicRotate( rMShift, a&ddsdSrc.ddpfPixelFormat.dwRBitMask)&ddsdDst.ddpfPixelFormat.dwRBitMask;	//JON 5/11/00
//DEADCODE JON 5/11/00 					INT3;																								//JON 5/11/00
//DEADCODE JON 5/11/00 					g=a&ddsdSrc.ddpfPixelFormat.dwGBitMask;																//JON 5/11/00
//DEADCODE JON 5/11/00 //					g=greenShift==0?g:greenShift<0?g>>-greenShift:g<<greenShift;										//JON 5/11/00
//DEADCODE JON 5/11/00 					g=MagicRotate( gMShift, g );																		//JON 5/11/00
//DEADCODE JON 5/11/00 					g=g&ddsdDst.ddpfPixelFormat.dwGBitMask;																//JON 5/11/00
//DEADCODE JON 5/11/00 					b=a&ddsdSrc.ddpfPixelFormat.dwBBitMask;																//JON 5/11/00
//DEADCODE JON 5/11/00 //					b=blueShift==0?b:blueShift<0?b>>-blueShift:b<<blueShift;											//JON 5/11/00
//DEADCODE JON 5/11/00 					b=MagicRotate( bMShift, b );																		//JON 5/11/00
//DEADCODE JON 5/11/00 					b=b&ddsdDst.ddpfPixelFormat.dwBBitMask;																//JON 5/11/00
//DEADCODE JON 5/11/00 					*lpDst2++=r|g|b;																					//JON 5/11/00
//DEADCODE JON 5/11/00
                lpSrc2+=scale; // this does the x scaling down if needed... - skip the unwanted pixels
            }
            lpSrc=(UWord*)(ULong(lpSrc)+lPitch);
            lpDst=(UWord*)(ULong(lpDst)+ddsdDst.lPitch);
        }
    }
    break;
    case 32:
    {
        ULong *lpSrc=(ULong*)ddsdSrc.lpSurface;
        lpSrc=(ULong*)(ULong(lpSrc)+(lPitch*rect->top));			//JON 16Oct00
        lpSrc+=rect->left;
        UWord *lpDst=(UWord*)ddsdDst.lpSurface;
        for (DWORD y=ddsdDst.dwHeight; y>0; y--) // for each y in the destination
        {
            ULong *lpSrc2=lpSrc;
            UWord *lpDst2=lpDst;
            for (DWORD x=ddsdDst.dwWidth; x>0; x--) // for each x in the destination
            {

                *lpDst2++=MaskAndRot(*lpSrc2,rMShift,gMShift,bMShift,rmask,gmask,bmask)
                |UWord(dstAMask?(amask?UWord(MagicRotate(aMShift,*lpSrc2)&amask):dstAMask):0);
//setUWValue(	MaskAndRot(getULValue(lpSrc2),rMShift,gMShift,bMShift,rmask,gmask,bmask), lpDst2++ );
//DEADCODE JON 5/11/00 					ULong a,r,g,b;
//DEADCODE JON 5/11/00 					a=*lpSrc2;
//DEADCODE JON 5/11/00 //					r=redShift==0?r:redShift<0?r>>-redShift:r<<redShift;
//DEADCODE JON 5/11/00 					INT3;
//DEADCODE JON 5/11/00 					r=MagicRotate( rMShift,a&ddsdSrc.ddpfPixelFormat.dwRBitMask)&ddsdDst.ddpfPixelFormat.dwRBitMask;
//DEADCODE JON 5/11/00 					INT3;
//DEADCODE JON 5/11/00 //					g=greenShift==0?g:greenShift<0?g>>-greenShift:g<<greenShift;
//DEADCODE JON 5/11/00 					g=MagicRotate( gMShift, a&ddsdSrc.ddpfPixelFormat.dwGBitMask )&ddsdDst.ddpfPixelFormat.dwGBitMask;
//DEADCODE JON 5/11/00 //					b=blueShift==0?b:blueShift<0?b>>-blueShift:b<<blueShift;
//DEADCODE JON 5/11/00 					b=MagicRotate( bMShift, a&ddsdSrc.ddpfPixelFormat.dwBBitMask)&ddsdDst.ddpfPixelFormat.dwBBitMask;
//DEADCODE JON 5/11/00 					*lpDst2++=UWord(r|g|b);
                lpSrc2+=scale; // this does the x scaling down if needed... - skip the unwanted pixels
            }
            lpSrc=(ULong*)(ULong(lpSrc)+lPitch);
            lpDst=(UWord*)(ULong(lpDst)+ddsdDst.lPitch);
        }
    }
    break;
    NODEFAULT;
    }
//	pDst->Unlock(NULL);
//	pSrc->Unlock(NULL);
    DoUnlocks( pDst, pSrc );

    return S_OK;
}


//DEADCODE JON 5/11/00 HRESULT Lib3D::PerformSlowCopy(LPDIRECTDRAWSURFACE7 pDst,LPDIRECTDRAWSURFACE7 pSrc,LPRECT rect)
//DEADCODE JON 5/11/00 {
//DEADCODE JON 5/11/00 	// Create a system memory surface with the same dimensions as the destination surface
//DEADCODE JON 5/11/00 	// but with the same pixel format as the source surface
//DEADCODE JON 5/11/00 	DDSURFACEDESC2 ddsdSrc,ddsdDst,ddsdSys;
//DEADCODE JON 5/11/00 	LPDIRECTDRAWSURFACE7 pSys;
//DEADCODE JON 5/11/00 	ZeroMemory(&ddsdSys,sizeof(ddsdSys));
//DEADCODE JON 5/11/00 	ddsdSrc.dwSize=
//DEADCODE JON 5/11/00 		ddsdDst.dwSize=
//DEADCODE JON 5/11/00 		ddsdSys.dwSize=sizeof(ddsdSrc);
//DEADCODE JON 5/11/00 	pSrc->GetSurfaceDesc(&ddsdSrc);
//DEADCODE JON 5/11/00 	pDst->GetSurfaceDesc(&ddsdDst);
//DEADCODE JON 5/11/00 	ddsdSys.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
//DEADCODE JON 5/11/00 	ddsdSys.ddsCaps.dwCaps=DDSCAPS_SYSTEMMEMORY|DDSCAPS_OFFSCREENPLAIN;
//DEADCODE JON 5/11/00 	ddsdSys.dwWidth=ddsdDst.dwWidth;
//DEADCODE JON 5/11/00 	ddsdSys.dwHeight=ddsdDst.dwHeight;
//DEADCODE JON 5/11/00 	ddsdSys.ddpfPixelFormat=ddsdSrc.ddpfPixelFormat;
//DEADCODE JON 5/11/00 	pDD7->CreateSurface(&ddsdSys,&pSys,NULL);
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	// Copy from the source surface to the destination surface with scaling
//DEADCODE JON 5/11/00 	pSys->Lock(NULL,&ddsdSys,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//DEADCODE JON 5/11/00 	pSrc->Lock(NULL,&ddsdSrc,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 //tempcode
//DEADCODE JON 5/11/00 //tempcode	pSrc->Unlock(NULL);
//DEADCODE JON 5/11/00 //tempcode	pSys->Unlock(NULL);
//DEADCODE JON 5/11/00 //tempcode
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	DWORD swidth=rect==NULL?ddsdSrc.dwWidth:rect->right-rect->left;
//DEADCODE JON 5/11/00 	for (DWORD scale(1);swidth!=ddsdSys.dwWidth;scale<<=1,swidth>>=1);
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	DWORD lPitch=ddsdSrc.lPitch*scale;
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	switch (ddsdSys.ddpfPixelFormat.dwRGBBitCount)
//DEADCODE JON 5/11/00 	{
//DEADCODE JON 5/11/00 	case 16:
//DEADCODE JON 5/11/00 		{
//DEADCODE JON 5/11/00 			UWord *lpSrc=(UWord*)ddsdSrc.lpSurface;
//DEADCODE JON 5/11/00 			UWord *lpSys=(UWord*)ddsdSys.lpSurface;
//DEADCODE JON 5/11/00 			for (DWORD y=ddsdSys.dwHeight;y>0;y--)
//DEADCODE JON 5/11/00 			{
//DEADCODE JON 5/11/00 				UWord *lpSrc2=lpSrc;
//DEADCODE JON 5/11/00 				UWord *lpSys2=lpSys;
//DEADCODE JON 5/11/00 				for (DWORD x=ddsdSys.dwWidth;x>0;x--)
//DEADCODE JON 5/11/00 				{
//DEADCODE JON 5/11/00 					*lpSys2++=*lpSrc2;
//DEADCODE JON 5/11/00 					lpSrc2+=scale;
//DEADCODE JON 5/11/00 				}
//DEADCODE JON 5/11/00 				lpSrc=(UWord*)(ULong(lpSrc)+lPitch);
//DEADCODE JON 5/11/00 				lpSys=(UWord*)(ULong(lpSys)+ddsdSys.lPitch);
//DEADCODE JON 5/11/00 			}
//DEADCODE JON 5/11/00 		}
//DEADCODE JON 5/11/00 		break;
//DEADCODE JON 5/11/00 	case 32:
//DEADCODE JON 5/11/00 		{
//DEADCODE JON 5/11/00 			ULong *lpSrc=(ULong*)ddsdSrc.lpSurface;
//DEADCODE JON 5/11/00 			ULong *lpSys=(ULong*)ddsdSys.lpSurface;
//DEADCODE JON 5/11/00 			for (DWORD y=ddsdSys.dwHeight;y>0;y--)
//DEADCODE JON 5/11/00 			{
//DEADCODE JON 5/11/00 				ULong *lpSrc2=lpSrc;
//DEADCODE JON 5/11/00 				ULong *lpSys2=lpSys;
//DEADCODE JON 5/11/00 				for (DWORD x=ddsdSys.dwWidth;x>0;x--)
//DEADCODE JON 5/11/00 				{
//DEADCODE JON 5/11/00 					*lpSys2++=*lpSrc2;
//DEADCODE JON 5/11/00 					lpSrc2+=scale;
//DEADCODE JON 5/11/00 				}
//DEADCODE JON 5/11/00 				lpSrc=(ULong*)(ULong(lpSrc)+lPitch);
//DEADCODE JON 5/11/00 				lpSys=(ULong*)(ULong(lpSys)+ddsdSys.lPitch);
//DEADCODE JON 5/11/00 			}
//DEADCODE JON 5/11/00 		}
//DEADCODE JON 5/11/00 		break;
//DEADCODE JON 5/11/00 	}
//DEADCODE JON 5/11/00 //tempcode
//DEADCODE JON 5/11/00 	pSrc->Unlock(NULL);
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	// Copy from the system surface to the destination surface with color conversion (dest is always 16 bit)
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	SWord redShift,greenShift,blueShift;
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	redShift=	GET_BIT_POS32(ddsdDst.ddpfPixelFormat.dwRBitMask)-GET_BIT_POS32(ddsdSys.ddpfPixelFormat.dwRBitMask);
//DEADCODE JON 5/11/00 	greenShift=	GET_BIT_POS32(ddsdDst.ddpfPixelFormat.dwGBitMask)-GET_BIT_POS32(ddsdSys.ddpfPixelFormat.dwGBitMask);
//DEADCODE JON 5/11/00 	blueShift=	GET_BIT_POS32(ddsdDst.ddpfPixelFormat.dwBBitMask)-GET_BIT_POS32(ddsdSys.ddpfPixelFormat.dwBBitMask);
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	pDst->Lock(NULL,&ddsdDst,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//DEADCODE JON 5/11/00 //tempcode
//DEADCODE JON 5/11/00 //tempcode	pDst->Unlock(NULL);
//DEADCODE JON 5/11/00 //tempcode
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	switch (ddsdSys.ddpfPixelFormat.dwRGBBitCount)
//DEADCODE JON 5/11/00 	{
//DEADCODE JON 5/11/00 	case 16:
//DEADCODE JON 5/11/00 		{
//DEADCODE JON 5/11/00 			UWord *lpSys=(UWord*)ddsdSys.lpSurface;
//DEADCODE JON 5/11/00 			UWord *lpDst=(UWord*)ddsdDst.lpSurface;
//DEADCODE JON 5/11/00 			for (DWORD y=ddsdDst.dwHeight;y>0;y--)
//DEADCODE JON 5/11/00 			{
//DEADCODE JON 5/11/00 				UWord *lpSys2=lpSys;
//DEADCODE JON 5/11/00 				UWord *lpDst2=lpDst;
//DEADCODE JON 5/11/00 				for (DWORD x=ddsdDst.dwWidth;x>0;x--)
//DEADCODE JON 5/11/00 				{
//DEADCODE JON 5/11/00 					UWord a,r,g,b;
//DEADCODE JON 5/11/00 					a=*lpSys2++;
//DEADCODE JON 5/11/00 					r=a&ddsdSys.ddpfPixelFormat.dwRBitMask;
//DEADCODE JON 5/11/00 					r=redShift==0?r:redShift<0?r>>-redShift:r<<redShift;
//DEADCODE JON 5/11/00 					r=r&ddsdDst.ddpfPixelFormat.dwRBitMask;
//DEADCODE JON 5/11/00 					g=a&ddsdSys.ddpfPixelFormat.dwGBitMask;
//DEADCODE JON 5/11/00 					g=greenShift==0?g:greenShift<0?g>>-greenShift:g<<greenShift;
//DEADCODE JON 5/11/00 					g=g&ddsdDst.ddpfPixelFormat.dwGBitMask;
//DEADCODE JON 5/11/00 					b=a&ddsdSys.ddpfPixelFormat.dwBBitMask;
//DEADCODE JON 5/11/00 					b=blueShift==0?b:blueShift<0?b>>-blueShift:b<<blueShift;
//DEADCODE JON 5/11/00 					b=b&ddsdDst.ddpfPixelFormat.dwBBitMask;
//DEADCODE JON 5/11/00 					*lpDst2++=r|g|b;
//DEADCODE JON 5/11/00 				}
//DEADCODE JON 5/11/00 				lpSys=(UWord*)(ULong(lpSys)+ddsdSys.lPitch);
//DEADCODE JON 5/11/00 				lpDst=(UWord*)(ULong(lpDst)+ddsdDst.lPitch);
//DEADCODE JON 5/11/00 			}
//DEADCODE JON 5/11/00 		}
//DEADCODE JON 5/11/00 		break;
//DEADCODE JON 5/11/00 	case 32:
//DEADCODE JON 5/11/00 		{
//DEADCODE JON 5/11/00 			ULong *lpSys=(ULong*)ddsdSys.lpSurface;
//DEADCODE JON 5/11/00 			UWord *lpDst=(UWord*)ddsdDst.lpSurface;
//DEADCODE JON 5/11/00 			for (DWORD y=ddsdDst.dwHeight;y>0;y--)
//DEADCODE JON 5/11/00 			{
//DEADCODE JON 5/11/00 				ULong *lpSys2=lpSys;
//DEADCODE JON 5/11/00 				UWord *lpDst2=lpDst;
//DEADCODE JON 5/11/00 				for (DWORD x=ddsdDst.dwWidth;x>0;x--)
//DEADCODE JON 5/11/00 				{
//DEADCODE JON 5/11/00 					ULong a,r,g,b;
//DEADCODE JON 5/11/00 					a=*lpSys2++;
//DEADCODE JON 5/11/00 					r=a&ddsdSys.ddpfPixelFormat.dwRBitMask;
//DEADCODE JON 5/11/00 					r=redShift==0?r:redShift<0?r>>-redShift:r<<redShift;
//DEADCODE JON 5/11/00 					r=r&ddsdDst.ddpfPixelFormat.dwRBitMask;
//DEADCODE JON 5/11/00 					g=a&ddsdSys.ddpfPixelFormat.dwGBitMask;
//DEADCODE JON 5/11/00 					g=greenShift==0?g:greenShift<0?g>>-greenShift:g<<greenShift;
//DEADCODE JON 5/11/00 					g=g&ddsdDst.ddpfPixelFormat.dwGBitMask;
//DEADCODE JON 5/11/00 					b=a&ddsdSys.ddpfPixelFormat.dwBBitMask;
//DEADCODE JON 5/11/00 					b=blueShift==0?b:blueShift<0?b>>-blueShift:b<<blueShift;
//DEADCODE JON 5/11/00 					b=b&ddsdDst.ddpfPixelFormat.dwBBitMask;
//DEADCODE JON 5/11/00 					*lpDst2++=UWord(r|g|b);
//DEADCODE JON 5/11/00 				}
//DEADCODE JON 5/11/00 				lpSys=(ULong*)(ULong(lpSys)+ddsdSys.lPitch);
//DEADCODE JON 5/11/00 				lpDst=(UWord*)(ULong(lpDst)+ddsdDst.lPitch);
//DEADCODE JON 5/11/00 			}
//DEADCODE JON 5/11/00 		}
//DEADCODE JON 5/11/00 		break;
//DEADCODE JON 5/11/00 	}
//DEADCODE JON 5/11/00 //tempcode
//DEADCODE JON 5/11/00 	pDst->Unlock(NULL);
//DEADCODE JON 5/11/00 //tempcode
//DEADCODE JON 5/11/00 	pSys->Unlock(NULL);
//DEADCODE JON 5/11/00 	pSys->Release();
//DEADCODE JON 5/11/00
//DEADCODE JON 5/11/00 	return S_OK;
//DEADCODE JON 5/11/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Lib3D
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//------------------------------------------------------------------------------
Lib3D::Lib3D()
//DeadCode JON 18Jul00 :	num1024Textures( *landTextureBandSize ),
//DeadCode JON 18Jul00 	num512Textures( *(landTextureBandSize+1) ),
//DeadCode JON 18Jul00 	num256Textures( *(landTextureBandSize+2*sizeof(SLong)) ),
//DeadCode JON 18Jul00 	num128Textures( *(landTextureBandSize+3*sizeof(SLong)) ),
//DeadCode JON 18Jul00 	num64Textures( *(landTextureBandSize+4*sizeof(SLong)) ),
//DeadCode JON 18Jul00 	num32Textures( *(landTextureBandSize+5*sizeof(SLong)) ),
//DeadCode JON 18Jul00 	num16Textures( *(landTextureBandSize+6*sizeof(SLong)) ),
//DeadCode JON 18Jul00 	num8Textures( *(landTextureBandSize+7*sizeof(SLong)) )
    :zFactor(SPolygon::zFactor)
{
    bufferPass = 0;														//JON 30Oct00
    hwClip = false;
#ifndef NDEBUG
    insidePoly = false;
#endif
    doDeviceDiags = false;
    frameTimeBuff = NULL;
    tickCountBuff = NULL;
    curFrameTimeI = 0;
    frameTimeBuffSize = 0;
    diagString=NULL;
    pDrivers=NULL;
    pDD7=NULL;
    pDDSP7=NULL;
    pDDSB7=NULL;
    pDDSZ7=NULL;
    pD3D7=NULL;
    pD3DDEV7=NULL;
    gpD3DVB7=NULL;
    gpD3DVBL7=NULL;													//RJS 17Apr00
    lpD3DVB7=NULL;
    pDDS7LandRT=NULL;                                               //JON 15Jun00
    int i;
    for (i=MAX_VERTICES-1; i>=0; polyVerts[i]=i,i--);
    for (i=NUM_PALETTES-1; i>=0; normPalLookUp[i]=NULL,i--);
    for (i=NUM_PALETTES-1; i>=0; maskPalLookUp[i]=NULL,i--);
    for (i=NUM_PALETTES-1; i>=0; trnsPalLookUp[i]=NULL,i--);
    textureQuality=HINT_FULL_RES_TEXTURE;
    textureBlending=HINT_TRILINEAR;
//TempCode JON 13Oct00 	BuildSqrtTable();
    // fill the last vertex table with the dummy vertex.
    for (i=0; i<=MAX_DOPOINTS; i++ )
    {
        lastDoPoint[ i ] = &dummyVertex;
    }
    // clear the texture table;
    for (i=MAX_TEXTURES-1; i>=0; i-- )
    {
        textureTable[i]=NULL;
    }
    lightflag=LF_DUMMY;
    supportedTextFmt = NULL; // shouldn't be needed, but just incase...
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		~Lib3D
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//------------------------------------------------------------------------------
Lib3D::~Lib3D()
{
    CloseDown(true);
    for (DDDriver *pDriver=pDrivers; pDriver!=NULL;)
    {
        for (DDMode *pMode=pDriver->pModes; pMode!=NULL;)
        {
            DDMode *tmp=pMode->pNext;
            delete pMode;
            pMode=tmp;
        }
        DDDriver *tmp=pDriver->pNext;
        delete pDriver;
        pDriver=tmp;
    }
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		QueryInterface
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::QueryInterface(REFIID riid,LPVOID *ppvObj)
{
    if (memcmp(&riid,&IID_IUnknown,sizeof(GUID)) || memcmp(&riid,&IID_ILib3D,sizeof(GUID)))
    {
        *ppvObj=(LPVOID)this;
        AddRef();
        return NOERROR;
    }
    *ppvObj=NULL;
    return lastError=E_NOINTERFACE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddRef
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//------------------------------------------------------------------------------
ULong Lib3D::AddRef()
{
    return ++refCnt;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Release
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//------------------------------------------------------------------------------
ULong Lib3D::Release()
{
    if (--refCnt==0)
    {
        delete this;
        return 0;
    }
    return refCnt;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DDEnumCallbackEx
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
BOOL WINAPI Lib3D::DDEnumCallbackEx(GUID FAR *pGuid,LPSTR szDesc,LPSTR szName,LPVOID pContext,HMONITOR hm)
{
    Lib3D *This=(Lib3D*)pContext;
    DDDriver *pNewDriver=new DDDriver;
    if (pNewDriver==NULL)
        return FALSE;
    strcpy((char*)pNewDriver->name,szName);
    strcpy((char*)pNewDriver->desc,szDesc);
    if (pGuid!=NULL)
    {
        memcopy(&pNewDriver->guid,pGuid,sizeof(GUID));
        pNewDriver->pGUID=&pNewDriver->guid;
    }
    else
    {
        pNewDriver->pGUID=pGuid;
    }
    pNewDriver->hm=hm;
    pNewDriver->pModes=NULL;
    pNewDriver->pNext=NULL;

    DDDriver *pIns=This->pDrivers;
    if (pIns==NULL) This->pDrivers=pNewDriver;
    else
    {
        while (pIns->pNext!=NULL) pIns=pIns->pNext;
        pIns->pNext=pNewDriver;
    }
    return TRUE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumModesCallback2
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT WINAPI Lib3D::EnumModesCallback2(LPDDSURFACEDESC2 pDDSD,LPVOID pContext)
{
//DeadCode JON 6Oct00 	if (pDDSD->dwWidth<512 ||
//DeadCode JON 6Oct00 		pDDSD->dwWidth*3!=pDDSD->dwHeight*4)
//DeadCode JON 6Oct00 		return DDENUMRET_OK;							//abort if display mode not 4x3 >= 512x384
    if (pDDSD->dwWidth<512 || pDDSD->dwHeight<384 )
        return DDENUMRET_OK;							//abort if display mode not >= 512x384


    if ((pDDSD->ddpfPixelFormat.dwFlags&DDPF_RGB)==0 ||
            pDDSD->ddpfPixelFormat.dwRGBBitCount<16)
        return DDENUMRET_OK;							//abort if display mode not RGB >= 16bit

    if (pDDSD->ddpfPixelFormat.dwRGBBitCount==16 && (gRenderDepths&DDBD_16)==0)
        return DDENUMRET_OK;

    if (pDDSD->ddpfPixelFormat.dwRGBBitCount==24 && (gRenderDepths&DDBD_24)==0)
        return DDENUMRET_OK;

    if (pDDSD->ddpfPixelFormat.dwRGBBitCount==32 && (gRenderDepths&DDBD_32)==0)
        return DDENUMRET_OK;

    //ram required for display
    ULong whMul=pDDSD->dwWidth*pDDSD->dwHeight;
//DeadCode JON 6Sep00 	ULong scrnMem=(2*1024*1024)+((whMul*pDDSD->ddpfPixelFormat.dwRGBBitCount)>>2);
    ULong scrnMem=pDDSD->lPitch*pDDSD->dwHeight;
    ULong zb16Mem=(scrnMem<<1)+(whMul<<1)+MINIMUM_TEXTURE_RAM_REQUIRED;
    ULong zb24Mem=(scrnMem<<1)+(whMul*3)+MINIMUM_TEXTURE_RAM_REQUIRED;
    ULong zb32Mem=(scrnMem<<1)+(whMul<<2)+MINIMUM_TEXTURE_RAM_REQUIRED;
    ULong flags;



    if (zb16Mem>gMemCheck)			return DDENUMRET_OK;
    else if (zb24Mem>gMemCheck)		flags=DDMode::MF_16BITZBUFFER;
    else if (zb32Mem>gMemCheck)		flags=DDMode::MF_24BITZBUFFER;
    else							flags=DDMode::MF_32BITZBUFFER;

    DDMode *pNewMode=new DDMode;
    DDDriver *pDriver=(DDDriver*)pContext;

    if (pNewMode==NULL)
        return DDENUMRET_CANCEL;

    memcopy(&pNewMode->ddsd,pDDSD,sizeof(DDSURFACEDESC2));
    pNewMode->flags=DDMode::ModeFlags(flags);
    pNewMode->pNext=NULL;

    DDMode *pIns=pDriver->pModes;
    if (pIns==NULL) pDriver->pModes=pNewMode;
    else
    {
        while (pIns->pNext!=NULL) pIns=pIns->pNext;
        pIns->pNext=pNewMode;
    }
    return DDENUMRET_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumDevicesCallback
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT CALLBACK Lib3D::EnumRenderBitDepthsCallback(LPSTR szDesc,LPSTR szName,LPD3DDEVICEDESC7 pDevDesc,LPVOID pContext)
{
    ULong *v=(ULong*)pContext;
#ifndef NO_HARD_TNL
    if (pDevDesc->deviceGUID==IID_IDirect3DTnLHalDevice)
    {
        *v=pDevDesc->dwDeviceRenderBitDepth;
        return D3DENUMRET_CANCEL;
    }
    else
#endif
        if (pDevDesc->deviceGUID==IID_IDirect3DHALDevice)
            *v=pDevDesc->dwDeviceRenderBitDepth;
    return D3DENUMRET_OK;
}
HRESULT CALLBACK Lib3D::EnumDevicesCallback(LPSTR szDesc,LPSTR szName,LPD3DDEVICEDESC7 pDevDesc,LPVOID pContext)
{
#ifndef NO_HARD_TNL
    if (pDevDesc->deviceGUID==IID_IDirect3DTnLHalDevice)
    {
        memcopy(pContext,&IID_IDirect3DTnLHalDevice,sizeof(GUID));
        memcopy(&selectedDevice,pDevDesc,sizeof(selectedDevice));
        return D3DENUMRET_CANCEL;
    }
    else
#endif
        if (pDevDesc->deviceGUID==IID_IDirect3DHALDevice)
        {
            memcopy(pContext,&IID_IDirect3DHALDevice,sizeof(GUID));
            memcopy(&selectedDevice,pDevDesc,sizeof(selectedDevice));
        }
    return D3DENUMRET_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumZBufferCallback
//Author		//JIM 22Jun100
//Date			Wed 10 Nov 1999
//				Returns a list of all formats ordered by Z depth
//				15/16, 24, 31/32 bit are each grouped seperately
//------------------------------------------------------------------------------
struct	ZBufferEntry
{
    DWORD	dwFlags;
    DWORD	dwZBufferBitDepth;
    DWORD	dwStencilBitDepth;
    DWORD	dwZBitMask;
    DWORD	dwStencilBitMask;
    void operator=(LPDDPIXELFORMAT pf)
    {
        dwFlags=pf->dwFlags;
        dwZBufferBitDepth=pf->dwZBufferBitDepth;
        dwZBitMask=pf->dwZBitMask;
        dwStencilBitDepth=pf->dwStencilBitDepth;
        dwStencilBitMask=pf->dwStencilBitMask;
    }
    ZBufferEntry()
    {
        dwZBufferBitDepth=0;
    }
};
struct	ZBufferList
{
    enum	{PER_LEVEL=4,LEVELS=3,LISTMAX=11};
    ZBufferEntry	list[PER_LEVEL*LEVELS];
};

HRESULT CALLBACK Lib3D::EnumZBufferCallback(LPDDPIXELFORMAT pddpf,LPVOID pContext)
{
//DeadCode JON 4Jul00 	LPDDPIXELFORMAT pospf;
//DeadCode JON 4Jul00 	ULong flags;

    if (pddpf->dwFlags&DDPF_ZBUFFER)
    {
        ZBufferList* zbl=(ZBufferList*)pContext;
        int zdepth=pddpf->dwZBufferBitDepth-pddpf->dwStencilBitDepth;
        int	zdl=(zdepth+1)/8-2;	//there may be a claimed 15 bit z depth out there!
        if (zdl>=0)
        {
            if (zdl>=ZBufferList::LEVELS)
                zdl=ZBufferList::LEVELS-1;
            for (int i=0; i<ZBufferList::PER_LEVEL; i++)
                if (zbl->list[zdl*ZBufferList::PER_LEVEL+i].dwZBufferBitDepth==0)
                {
                    zbl->list[zdl*ZBufferList::PER_LEVEL+i]=pddpf;
                    /****/	break;
                }
        }
    }
    return 	DDENUMRET_OK;
}
//DeadCode JIM 22Jun100 HRESULT CALLBACK Lib3D::EnumZBufferCallback(LPDDPIXELFORMAT pddpf,LPVOID pContext)
//DeadCode JIM 22Jun100 {
//DeadCode JIM 22Jun100 	LPDDPIXELFORMAT pospf;
//DeadCode JIM 22Jun100 	ULong flags;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 	if ( fixZbuffer != true )
//DeadCode JIM 22Jun100 		flags = selectedMode.flags;
//DeadCode JIM 22Jun100 	else
//DeadCode JIM 22Jun100 		flags = DDMode::MF_16BITZBUFFER;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 	if (pddpf->dwFlags==DDPF_ZBUFFER)
//DeadCode JIM 22Jun100 	{
//DeadCode JIM 22Jun100 		pospf=(LPDDPIXELFORMAT)pContext;
//DeadCode JIM 22Jun100 		switch (flags)
//DeadCode JIM 22Jun100 		{
//DeadCode JIM 22Jun100 		case DDMode::MF_16BITZBUFFER:
//DeadCode JIM 22Jun100 			if (pddpf->dwZBufferBitDepth==16)
//DeadCode JIM 22Jun100 			{
//DeadCode JIM 22Jun100 				*pospf=*pddpf;
//DeadCode JIM 22Jun100 				return D3DENUMRET_CANCEL;
//DeadCode JIM 22Jun100 			}
//DeadCode JIM 22Jun100 			break;
//DeadCode JIM 22Jun100 		case DDMode::MF_24BITZBUFFER:
//DeadCode JIM 22Jun100 			if (pddpf->dwZBufferBitDepth==24)
//DeadCode JIM 22Jun100 			{
//DeadCode JIM 22Jun100 				*pospf=*pddpf;
//DeadCode JIM 22Jun100 				return D3DENUMRET_CANCEL;
//DeadCode JIM 22Jun100 			}
//DeadCode JIM 22Jun100 			else if (pddpf->dwZBufferBitDepth==16)
//DeadCode JIM 22Jun100 			{
//DeadCode JIM 22Jun100 				*pospf=*pddpf;
//DeadCode JIM 22Jun100 			}
//DeadCode JIM 22Jun100 			break;
//DeadCode JIM 22Jun100 		case DDMode::MF_32BITZBUFFER:
//DeadCode JIM 22Jun100 			if (pddpf->dwZBufferBitDepth==32)
//DeadCode JIM 22Jun100 			{
//DeadCode JIM 22Jun100 				*pospf=*pddpf;
//DeadCode JIM 22Jun100 				return D3DENUMRET_CANCEL;
//DeadCode JIM 22Jun100 			}
//DeadCode JIM 22Jun100 			else if (pospf->dwSize==0)
//DeadCode JIM 22Jun100 			{
//DeadCode JIM 22Jun100 				if (pddpf->dwZBufferBitDepth>=16)
//DeadCode JIM 22Jun100 					*pospf=*pddpf;
//DeadCode JIM 22Jun100 			}
//DeadCode JIM 22Jun100 			else
//DeadCode JIM 22Jun100 			{
//DeadCode JIM 22Jun100 				if (pddpf->dwZBufferBitDepth<32 &&
//DeadCode JIM 22Jun100 					pddpf->dwZBufferBitDepth>=16 &&
//DeadCode JIM 22Jun100 					pddpf->dwZBufferBitDepth>pospf->dwZBufferBitDepth)
//DeadCode JIM 22Jun100 					*pospf=*pddpf;
//DeadCode JIM 22Jun100 			}
//DeadCode JIM 22Jun100 			break;
//DeadCode JIM 22Jun100 		}
//DeadCode JIM 22Jun100 	}
//DeadCode JIM 22Jun100 	return D3DENUMRET_OK;
//DeadCode JIM 22Jun100 }

//////////////////////////////////////////////////////////////////////
//
// Function:    MakeListTextureFormatsCallback

// Date:		05/09/00
// Author:		JON
//
//Description:  Fills in the linked list of available texture formats...
//
//////////////////////////////////////////////////////////////////////
HRESULT CALLBACK Lib3D::MakeListTextureFormatsCallback(LPDDPIXELFORMAT pddpf,LPVOID pContext)
{
    Lib3D *This=(Lib3D*)pContext;
    DDTextureFormat *lastEnd = This->supportedTextFmt;
    This->supportedTextFmt = new DDTextureFormat();
    *(This->supportedTextFmt) = *pddpf; // copy in the format from the callback...
    This->supportedTextFmt->next = lastEnd;
    return DDENUMRET_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumTextureFormatsCallback
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT CALLBACK Lib3D::EnumTextureFormatsCallback(LPDDPIXELFORMAT pddpf,LPVOID pContext)
{
    Lib3D *This=(Lib3D*)pContext;

    LPDDPIXELFORMAT tf=This->texFmt+This->texFmtReq; // the current one

    switch (This->texFmtReq)
    {
    case TF_NORM:
        if ((pddpf->dwFlags&DDPF_FOURCC)!=0 &&
                (pddpf->dwFourCC==DXT1))
        {
            *tf=*pddpf;
            return DDENUMRET_CANCEL;
        }
        else if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                 (tf->dwFlags&DDPF_PALETTEINDEXED8)==0 &&
                 (pddpf->dwFlags&DDPF_ALPHAPIXELS)==0 &&
                 (pddpf->dwRGBBitCount==16))
        {
            *tf=*pddpf;
        }
        break;
    case TF_NORMINIT:
        if ((tf[-1].dwFlags&DDPF_FOURCC)!=0)
        {
            if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                    (pddpf->dwFlags&DDPF_ALPHAPIXELS)==0 &&
                    (pddpf->dwRGBBitCount==16))
            {
                *tf=*pddpf;
                return DDENUMRET_CANCEL;
            }
        }
        else
        {
            tf[0]=tf[-1];
            return DDENUMRET_CANCEL;
        }
        break;
    case TF_MASK:
        if ((pddpf->dwFlags&DDPF_FOURCC)!=0 &&
                (pddpf->dwFourCC==DXT1))
        {
            *tf=*pddpf;
            return DDENUMRET_CANCEL;
        }
        else if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                 (pddpf->dwFlags&DDPF_ALPHAPIXELS)!=0 &&
                 (pddpf->dwRGBBitCount==16))
        {
            if ((tf->dwFlags&DDPF_RGB)==0)
                *tf=*pddpf;
            else if (COUNT_BITS(tf->dwRGBAlphaBitMask)>COUNT_BITS(pddpf->dwRGBAlphaBitMask))
                *tf=*pddpf;
        }
        break;
    case TF_MASKINIT:
        if ((tf[-1].dwFlags&DDPF_FOURCC)!=0)
        {
            if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                    (pddpf->dwFlags&DDPF_ALPHAPIXELS)!=0 &&
                    (pddpf->dwRGBBitCount==16))
            {
                if ((tf->dwFlags&DDPF_RGB)==0)
                    *tf=*pddpf;
                else if (COUNT_BITS(tf->dwRGBAlphaBitMask)>COUNT_BITS(pddpf->dwRGBAlphaBitMask))
                    *tf=*pddpf;
            }
        }
        else
        {
            tf[0]=tf[-1];
            return DDENUMRET_CANCEL;
        }
        break;
    case TF_TRNS:
        if ((pddpf->dwFlags&DDPF_FOURCC)!=0 &&
                (pddpf->dwFourCC==DXT3))
        {
            *tf=*pddpf;
            return DDENUMRET_CANCEL;
        }
        else if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                 (pddpf->dwFlags&DDPF_ALPHAPIXELS)!=0 &&
                 (pddpf->dwRGBBitCount==16))
        {
//DeadCode JON 15Nov00 			if ((tf->dwFlags&DDPF_RGB)==0)
//DeadCode JON 15Nov00 				*tf=*pddpf;
//DeadCode JON 15Nov00 			else if (COUNT_BITS(tf->dwRGBAlphaBitMask)<COUNT_BITS(pddpf->dwRGBAlphaBitMask))
//DeadCode JON 15Nov00 				*tf=*pddpf;
            if ((tf->dwFlags&DDPF_RGB)==0)
            {
                *tf=*pddpf; // this is the first slightly suitable one available...
            }
            else   // pick the one with the closest to 4 bits of alpha...	//JON 15Nov00
            {
                if ( abs(int(COUNT_BITS(tf->dwRGBAlphaBitMask)-4))>abs(int(COUNT_BITS(pddpf->dwRGBAlphaBitMask)-4)) )
                    *tf=*pddpf;
            }

        }
        break;
    case TF_TRNSINIT:
        if ((tf[-1].dwFlags&DDPF_FOURCC)!=0)
        {
            if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                    (pddpf->dwFlags&DDPF_ALPHAPIXELS)!=0 &&
                    (pddpf->dwRGBBitCount==16))
            {
//DeadCode JON 15Nov00 				if ((tf->dwFlags&DDPF_RGB)==0)
//DeadCode JON 15Nov00 					*tf=*pddpf;
//DeadCode JON 15Nov00 				else if (COUNT_BITS(tf->dwRGBAlphaBitMask)<COUNT_BITS(pddpf->dwRGBAlphaBitMask))
//DeadCode JON 15Nov00 					*tf=*pddpf;
                if ((tf->dwFlags&DDPF_RGB)==0)
                {
                    *tf=*pddpf; // this is the first slightly suitable one available...
                }
                else   // pick the one with the closest to 4 bits of alpha...	//JON 15Nov00
                {
                    if ( abs(int(COUNT_BITS(tf->dwRGBAlphaBitMask)-4))>abs(int(COUNT_BITS(pddpf->dwRGBAlphaBitMask)-4)) )
                        *tf=*pddpf;
                }
            }
        }
        else
        {
            tf[0]=tf[-1];
            return DDENUMRET_CANCEL;
        }
        break;
    case TF_LAND:
        if ((pddpf->dwFlags&DDPF_FOURCC)!=0 &&
                (pddpf->dwFourCC==DXT1))
        {
            *tf=*pddpf;
            return DDENUMRET_CANCEL;
        }
        else if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                 (tf->dwFlags&DDPF_PALETTEINDEXED8)==0 &&
                 (pddpf->dwFlags&DDPF_ALPHAPIXELS)==0 &&
                 (pddpf->dwRGBBitCount==16))
        {
            *tf=*pddpf;
        }
        break;
    case TF_LANDINIT:
        if ((tf[-1].dwFlags&DDPF_FOURCC)!=0)
        {
            if ((pddpf->dwFlags&DDPF_RGB)!=0 &&
                    (pddpf->dwFlags&DDPF_ALPHAPIXELS)==0 &&
                    (pddpf->dwRGBBitCount==16))
            {
                *tf=*pddpf;
                return DDENUMRET_CANCEL;
            }
        }
        else
        {
            tf[0]=tf[-1];
            return DDENUMRET_CANCEL;
        }
        break;
    }
    return DDENUMRET_OK;
}
HRESULT Lib3D::GetRenderBitDepths(LPDIRECTDRAW7 pDD,ULong &renderBitDepths)
{
    HRESULT hr;
    LPDIRECT3D7 pD3D;
    LPDIRECT3DDEVICE7 pD3DDev;
    renderBitDepths=0;
    hr=pDD->QueryInterface(IID_IDirect3D7,(LPVOID*)&pD3D);
    if (hr!=DD_OK)	return hr;
    hr=pD3D->EnumDevices(EnumRenderBitDepthsCallback,(LPVOID)&renderBitDepths);
    pD3D->Release();

    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnumerateDriverModes
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
void Lib3D::EnumerateDriverModes(DDDriver& ddDriver)
{
    LPDIRECTDRAW7 pDD;
    DWORD totalRAM,freeRAM;
    DDSCAPS2 ddscaps;
    ZeroMemory(&ddscaps,sizeof(ddscaps));
    ddscaps.dwCaps=DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM|DDSCAPS_3DDEVICE;

    lastError=DirectDrawCreateEx(ddDriver.pGUID,(VOID**)&pDD,IID_IDirectDraw7,NULL);
    if (lastError==DD_OK)
    {
        // get the driver name to put in the descripion...
        DDDEVICEIDENTIFIER2 devID;
        lastError=pDD->GetDeviceIdentifier(&devID,0);
        if( lastError !=DD_OK )
        {
            INT3;
        }
        else
        {
            memcopy( ddDriver.desc, devID.szDescription, MAX_TEXT_LENGTH );
            ddDriver.desc[MAX_TEXT_LENGTH-1]=0;
//DeadCode JON 6Sep00 		printf("Three Dee info\n\nDriver Name: ");
//DeadCode JON 6Sep00 		printf( devID.szDriver );
//DeadCode JON 6Sep00 		printf( "\nDriver Description: " );
//DeadCode JON 6Sep00 		printf( devID.szDescription );
//DeadCode JON 6Sep00 		printf( "\n" );
//DeadCode JON 6Sep00 		printf( "Driver Version: %i (Product %i, Version %i, SubVer %i, Build %i \n",
//DeadCode JON 6Sep00 				devID.liDriverVersion,
//DeadCode JON 6Sep00 				HIWORD(devID.liDriverVersion.HighPart),
//DeadCode JON 6Sep00 				LOWORD(devID.liDriverVersion.HighPart),
//DeadCode JON 6Sep00 				HIWORD(devID.liDriverVersion.LowPart),
//DeadCode JON 6Sep00 				LOWORD(devID.liDriverVersion.LowPart)
//DeadCode JON 6Sep00 				);
//DeadCode JON 6Sep00 		printf( "VendorID   : %x\n", devID.dwVendorId );
//DeadCode JON 6Sep00 		printf( "DeviceID   : %x\n", devID.dwDeviceId );
//DeadCode JON 6Sep00 		printf( "SubSysID   : %x\n", devID.dwSubSysId );
//DeadCode JON 6Sep00 		printf( "Revision ID: %x\n", devID.dwRevision );
//DeadCode JON 6Sep00
//DeadCode JON 6Sep00 		GUID tD = devID.guidDeviceIdentifier;
//DeadCode JON 6Sep00
//DeadCode JON 6Sep00 		printf( "GUID       : %x-%x-%x-{%x-%x-%x-%x-%x-%x-%x-%x}\n",
//DeadCode JON 6Sep00 				tD.Data1, tD.Data2, tD.Data3,
//DeadCode JON 6Sep00 				tD.Data4[0], tD.Data4[1], tD.Data4[2], tD.Data4[3],
//DeadCode JON 6Sep00 				tD.Data4[4], tD.Data4[5], tD.Data4[6], tD.Data4[7]
//DeadCode JON 6Sep00 				);
//DeadCode JON 6Sep00
//DeadCode JON 6Sep00 		printf( "HWQuality  : %i\n", devID.dwWHQLLevel );

        }
        //get available video memory to decide whether a mode should be allowed
        if (pDD->GetAvailableVidMem(&ddscaps,&totalRAM,&freeRAM)==DD_OK &&
                GetRenderBitDepths(pDD,gRenderDepths)==DD_OK)
        {
            gMemCheck=totalRAM;
            lastError=pDD->EnumDisplayModes(NULL,NULL,(LPVOID)&ddDriver,EnumModesCallback2);
        }
        pDD->Release();
    }
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Initialise
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//Description	Library interface initialisation code
//
//Inputs		HWND application top level window handle
//
//------------------------------------------------------------------------------
HRESULT Lib3D::Initialise(const HWND& hWnd, const ULong* sqrtTable)
{
    fastSqrtTable = (ULong*)sqrtTable;
    DWORD dxVer, dxPlat;

    GetDXVersion( &dxVer, &dxPlat );
    if ( dxVer != 0x0700 || dxPlat == 0 )
    {
        return lastError=S_FALSE;
    }

    CpuInfo();

    if (pDD7!=NULL)
        return lastError=DDERR_ALREADYINITIALIZED;

    hwTop=hWnd;

    if (pDrivers==NULL)
    {
        lastError=DirectDrawEnumerateEx(DDEnumCallbackEx,this,DDENUM_ATTACHEDSECONDARYDEVICES|
                                        DDENUM_DETACHEDSECONDARYDEVICES|
                                        DDENUM_NONDISPLAYDEVICES);
        if (lastError!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
        DDDriver *pPrevDriver = NULL;
        DDDriver *pNextDriver = pDrivers->pNext;
        for (DDDriver *pDriver=pDrivers; pDriver!=NULL; pDriver=pNextDriver)
        {
            EnumerateDriverModes(*pDriver);
            pNextDriver = pDriver->pNext;
            if ( pDriver->pModes == NULL )
            {
                // the driver supports no modes we can use...
                if ( pPrevDriver == NULL )
                {
                    // ok, this is the first driver..
                    pDrivers = pNextDriver;
                    delete pDriver;
//					pPrevDriver = NULL; // already the case..
                }
                else
                {
                    pPrevDriver->pNext = pNextDriver;
                    delete pDriver;
                }
            }
            else
            {
                pPrevDriver = pDriver;
            }
        }
    }

    if ( pDrivers==NULL )
        return DDERR_NODRIVERSUPPORT;

    return lastError=S_OK;
}
HRESULT Lib3D::GetDefaultDriverAndMode(HDRIVER& hDriver,HMODE& hMode)
{
    DDDriver *pdriver;
    DDMode *pmode;
    ULong width=0;
    hDriver=HDRIVER(0);
    hMode=HMODE(0);

    HDRIVER potentialDriver=HDRIVER(0);
    HMODE potentialMode;

    if (pDrivers!=NULL)
    {
        for (pdriver=pDrivers; pdriver!=NULL; pdriver=pdriver->pNext)
        {
            potentialMode=HMODE(0);
            for (pmode=pdriver->pModes; pmode!=NULL; pmode=pmode->pNext)
            {
                if ( pmode->ddsd.dwWidth>width &&
                        pmode->ddsd.dwWidth <= DEFAULT_SCREEN_WIDTH &&
                        pmode->ddsd.ddpfPixelFormat.dwRGBBitCount <= DEFAULT_SCREEN_DEPTH )
                {
                    width=pmode->ddsd.dwWidth;
                    hDriver=potentialDriver;
                    hMode=potentialMode;
                }
                potentialMode=HMODE(potentialMode+1);
            }
            potentialDriver=HDRIVER(potentialDriver+1);
        }
    }
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDrivers
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT	Lib3D::GetDrivers(UIDrivers& uiDrivers)
{
    if (uiDrivers.size!=sizeof(UIDrivers))
        return lastError=DDERR_INVALIDPARAMS;
    if (pDrivers==NULL)
        return lastError=DDERR_GENERIC;

    uiDrivers.numDrivers=0;
    for (DDDriver *pDriver=pDrivers; pDriver!=NULL && uiDrivers.numDrivers<MAX_DRIVERS; pDriver=pDriver->pNext)
    {
//TempCode JON 26Sep00 		if (pDriver->pModes != NULL) // do we support any modes on this driver?
//TempCode JON 26Sep00 		{
        strcpy((char*)uiDrivers.driver[uiDrivers.numDrivers].name,(char*)pDriver->desc);
        uiDrivers.driver[uiDrivers.numDrivers].hDriver=uiDrivers.numDrivers;
        uiDrivers.numDrivers++;
//TempCode JON 26Sep00 		}
    }
    return lastError=S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetModes
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT	Lib3D::GetModes(const HDRIVER& hDriver,UIModes& uiModes)
{
    if (uiModes.size!=sizeof(UIModes))
        return lastError=DDERR_INVALIDPARAMS;
    if (pDrivers==NULL)
        return lastError=DDERR_GENERIC;

    uiModes.numModes=0;

    SLong i=SLong(hDriver);
    DDDriver *pDriver=pDrivers;
    while (i>0 && pDriver!=NULL)
    {i--;pDriver=pDriver->pNext;

        /*search for the driver required*/
    };

    if (pDriver==NULL)
        return lastError=DDERR_GENERIC;

    DDMode *pMode=pDriver->pModes;

    if (pMode==NULL)
        return lastError=DDERR_GENERIC;

    for (; pMode!=NULL && uiModes.numModes<MAX_MODES; pMode=pMode->pNext)
    {
        // check to see if there is enough memory on the card to support this mode with a
        // z-buffer...
        uiModes.mode[uiModes.numModes].width=pMode->ddsd.dwWidth;
        uiModes.mode[uiModes.numModes].height=pMode->ddsd.dwHeight;
        uiModes.mode[uiModes.numModes].bpp=pMode->ddsd.ddpfPixelFormat.dwRGBBitCount;
        uiModes.mode[uiModes.numModes].hMode=uiModes.numModes;
        uiModes.numModes++;
    }
    return lastError=S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDriverAndMode
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT	Lib3D::SetDriverAndMode(const HDRIVER& hDriver,const HMODE& hMode,const HWND& hWnd )
{
    masterLightFlag = LF_SPECULAR;
    masterTextureBlending = textureBlending = HINT_TRILINEAR;
    masterTextureQuality  = textureQuality = HINT_FULL_RES_TEXTURE;

    lastFogStart = -10000.0;
    lastFogEnd = -10000.0;
    clipVal2D = 1.0;

    fixZbuffer = false;
    HRESULT err;
#ifndef _FORCE_16BIT_Z
    if( (err=_SetDriverAndMode( hDriver, hMode, hWnd )) != S_OK )
#endif
    {
        lastError = S_OK;
        fixZbuffer = true;
        err=_SetDriverAndMode( hDriver, hMode, hWnd );
    }

//	logically the line is this:	zSMALL=1.0/double(ULong(1<<currentZBufferDepth)-1);
//	however when 32bit z buffers are used things go wrong (plain coloured landscape for example!!!)
//	also some cards don't seem to quite manage the full resolution they claim hence the test...
    if ( currentZBufferDepth < 20 )
        zSMALL=0.25/double(ULong(1<<(currentZBufferDepth-2))-1);
    else
        zSMALL=0.25/double(ULong(1<<18)-1);

//DeadCode JON 21Aug00 	if ( prefZType == D3DZB_USEW )
//DeadCode JON 21Aug00 		zSMALL*=4;

    FillFogTable(1.9,2.0);

    return err;
}

HRESULT	Lib3D::_SetDriverAndMode(const HDRIVER& hDriver,const HMODE& hMode,const HWND& hWnd )
{
    supportedTextFmt = NULL;
    hwOther=hWnd;

    flags=Flags(0);

    SLong i=SLong(hDriver);
    DDDriver *pDriver=pDrivers;
    while (i>0 && pDriver!=NULL)
    {
     i--;pDriver=pDriver->pNext;
    };
    if (pDriver==NULL)
        return lastError=DDERR_INVALIDPARAMS;

    i=SLong(hMode);
    DDMode *pMode=pDriver->pModes;
    while (i>0 && pMode!=NULL){i--;pMode=pMode->pNext;};
    if (pMode==NULL)
        return lastError=DDERR_INVALIDPARAMS;

    selectedDriver=*pDriver;
    selectedMode=*pMode;

    CloseDown(true);

    lastError=DirectDrawCreateEx(selectedDriver.pGUID,(VOID**)&pDD7,IID_IDirectDraw7,NULL);
    if (lastError!=DD_OK)
        return lastError;

    ULong dwRenderWidth,dwRenderHeight;

    if (hwOther==NULL)
    {
        flags=Flags(flags&~F_WINDOWED);  // full screen mode
        dwRenderWidth=selectedMode.ddsd.dwWidth;
        dwRenderHeight=selectedMode.ddsd.dwHeight;


        if ((lastError=pDD7->SetCooperativeLevel(hwTop,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
        lastError=pDD7->SetDisplayMode(dwRenderWidth,
                                       dwRenderHeight,
                                       selectedMode.ddsd.ddpfPixelFormat.dwRGBBitCount,
                                       0,0);
        if (lastError!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
        DDSURFACEDESC2 ddsd;
        ZeroMemory(&ddsd,sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
        ddsd.ddsCaps.dwCaps=DDSCAPS_COMPLEX|DDSCAPS_FLIP|DDSCAPS_PRIMARYSURFACE|DDSCAPS_3DDEVICE|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
        ddsd.dwBackBufferCount=1;
        if ((lastError=pDD7->CreateSurface(&ddsd,&pDDSP7,NULL))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
        DDSCAPS2 ddsc;
        ddsc.dwCaps=DDSCAPS_BACKBUFFER;
        ddsc.dwCaps2=ddsc.dwCaps3=ddsc.dwCaps4=0;
        if ((lastError=pDDSP7->GetAttachedSurface(&ddsc,&pDDSB7))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
    }
    else
    {
        flags=Flags(flags|F_WINDOWED); //we are windowed
        GetWindowRect(hwOther,&windowRect);

        dwRenderWidth=windowRect.right-windowRect.left;
        dwRenderHeight=windowRect.bottom-windowRect.top;

        lastError=pDD7->SetCooperativeLevel(hwTop,DDSCL_NORMAL);
        if (lastError!=DD_OK)
            return lastError;


        //create primary surface
        DDSURFACEDESC2 ddsd;
        ZeroMemory(&ddsd,sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags=DDSD_CAPS;
        ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
        if ((lastError=pDD7->CreateSurface(&ddsd,&pDDSP7,NULL))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
        ZeroMemory(&ddsd,sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_CAPS;
        ddsd.dwWidth=dwRenderWidth;
        ddsd.dwHeight=dwRenderHeight;
        ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|DDSCAPS_3DDEVICE|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
        if ((lastError=pDD7->CreateSurface(&ddsd,&pDDSB7,NULL))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
    }

    aspectRatio = D3DVALUE(dwRenderWidth)/D3DVALUE(dwRenderHeight);

    if ((lastError=pDD7->QueryInterface(IID_IDirect3D7,(LPVOID*)&pD3D7))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    GUID deviceGUID;
    ZeroMemory(&selectedDevice,sizeof(selectedDevice));
    if ((lastError=pD3D7->EnumDevices(EnumDevicesCallback,(LPVOID)&deviceGUID))!=D3D_OK)
    {
        CloseDown();
        return lastError;
    }
    if ((selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_ZBUFFERLESSHSR)==0)
    {
        ZBufferList enumresult;
        if ((pD3D7->EnumZBufferFormats(selectedDevice.deviceGUID,EnumZBufferCallback,(LPVOID)&enumresult))!=D3D_OK)
        {
            CloseDown();
            return lastError=DDERR_GENERIC;
        }
        currentZBufferDepth =0;
        DDSURFACEDESC2 ddsd;
        ZeroMemory(&ddsd,sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
        ddsd.ddsCaps.dwCaps=DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
        ddsd.ddpfPixelFormat.dwSize=sizeof(DDPIXELFORMAT);
        ddsd.dwWidth=dwRenderWidth;
        ddsd.dwHeight=dwRenderHeight;

        int i=ZBufferList::LISTMAX;
        if (fixZbuffer)	i=3; // only check zbuffer depths of <=16 bit
        for (; i>=0; i--) // search for a suitable zbuffer format
        {
            if (enumresult.list[i].dwZBufferBitDepth
//DeadCode JON 28Sep00 					&& ( !fixZbuffer || enumresult.list[i].dwZBufferBitDepth <=16 )	// if fix zbuffer use a lower one
               )
            {
                ddsd.ddpfPixelFormat.dwFlags=enumresult.list[i].dwFlags;
                ddsd.ddpfPixelFormat.dwZBufferBitDepth=enumresult.list[i].dwZBufferBitDepth;
                ddsd.ddpfPixelFormat.dwStencilBitDepth=enumresult.list[i].dwStencilBitDepth;
                ddsd.ddpfPixelFormat.dwZBitMask=enumresult.list[i].dwZBitMask;
                ddsd.ddpfPixelFormat.dwStencilBitMask=enumresult.list[i].dwStencilBitMask;

                if ((lastError=pDD7->CreateSurface(&ddsd,&pDDSZ7,NULL))==DD_OK)
                {
                    if ((lastError=pDDSB7->AddAttachedSurface(pDDSZ7))!=DD_OK)
                    {
                        CloseDown();
                        return lastError;
                    }
                    else
                    {
                        currentZBufferDepth = enumresult.list[i].dwZBufferBitDepth - enumresult.list[i].dwStencilBitDepth;
                        break;
                    }
                }
            }
        }

        if (lastError!=DD_OK || currentZBufferDepth ==0)
        {
            CloseDown();
            return lastError=DDERR_GENERIC;
        }

//		#pragma warnmsg ( "3DFX are a pain ---- this shouldn't be needed..." )
        // start of poo
        {
            DDSURFACEDESC2 ddsd;
            ZeroMemory(&ddsd,sizeof(ddsd));
            ddsd.dwSize=sizeof(ddsd);
            pDDSZ7->GetSurfaceDesc(&ddsd);
            currentZBufferDepth = ddsd.ddpfPixelFormat.dwZBufferBitDepth - ddsd.ddpfPixelFormat.dwStencilBitDepth;
        } //end of poo

        if (	(selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_WBUFFER) // we support w buffers
                &&	(currentZBufferDepth > 16)	)
            prefZType = D3DZB_USEW;
        else
            prefZType = D3DZB_TRUE;

    }

    if ( flags&F_WINDOWED ) // we are windowed..
    {
        LPDIRECTDRAWCLIPPER pcClipper;
        if ((lastError=pDD7->CreateClipper(0,&pcClipper,NULL))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
        pcClipper->SetHWnd(0,hwOther);
        pDDSP7->SetClipper(pcClipper);
        pcClipper->Release();
    }


    if ((lastError=pD3D7->CreateDevice(deviceGUID,pDDSB7,&pD3DDEV7))!=D3D_OK)
    {
        //Sometimes this can fail even though the zbuffer was created.
        CloseDown( !fixZbuffer );
        return lastError;
    }


//DeadCode JON 28Sep00 	ULong dwRenderWidth=selectedMode.ddsd.dwWidth;
//DeadCode JON 28Sep00 	ULong dwRenderHeight=selectedMode.ddsd.dwHeight;
    D3DVIEWPORT7 vp= {0,0,dwRenderWidth,dwRenderHeight,0.0f,1.0f};
    if ((lastError=pD3DDEV7->SetViewport(&vp))!=D3D_OK)
    {
        CloseDown();
        return lastError;
    }
    if (deviceGUID==IID_IDirect3DTnLHalDevice)	flags=Flags(flags|F_TNL);
    else										flags=Flags(flags&~F_TNL);
#ifdef FORCE_TNL_EMULATION
    flags=Flags(flags|F_TNL_EMULATION);
#else
    flags=Flags(flags&~F_TNL_EMULATION);
#endif //FORCE_TNL_EMULATION

    if ( flags&F_WINDOWED )
        lastError=pD3DDEV7->SetRenderTarget(pDDSB7,0);

    hCurrentRenderTarget=RENDERTARGET_PRIMARY;

    DDCAPS ddc;
    ZeroMemory(&ddc,sizeof(ddc));
    ddc.dwSize=sizeof(ddc);
    if ((lastError=pDD7->GetCaps(&ddc,NULL))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }

    if ((ddc.dwCaps2&DDCAPS2_NOPAGELOCKREQUIRED)==0)	flags=Flags(flags|F_PAGELOCK);
    else												flags=Flags(flags&~F_PAGELOCK);

//deadcode	if ((ddc.dwCaps2&DDCAPS2_CANMANAGETEXTURE)==0 ||
//deadcode		(ddc.dwCaps2&DDCAPS2_TEXMANINNONLOCALVIDMEM)==0)
//deadcode		flags=Flags(flags|F_CANTMANAGETEXTURES);
//deadcode	else
//deadcode		flags=Flags(flags&~F_CANTMANAGETEXTURES);

    primarySurfaceDesc.dwSize=sizeof(DDSURFACEDESC2);
    if ((lastError=pDDSP7->GetSurfaceDesc(&primarySurfaceDesc))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }

    ZeroMemory((void*)texFmt,sizeof(DDPIXELFORMAT)*TF_MAX);
    for (i=0; i<TF_MAX; i++)
    {
        texFmtReq=TEXFMT(i);
        if ((lastError=pD3DDEV7->EnumTextureFormats(EnumTextureFormatsCallback,(LPVOID)this))!=D3D_OK)
        {
            CloseDown();
            return lastError;
        }
    }
    lastError=pD3DDEV7->EnumTextureFormats(MakeListTextureFormatsCallback,(LPVOID)this);


// Evaluate texture RAM (-video RAM)
    DDSCAPS2 ddscaps;
    ZeroMemory(&ddscaps,sizeof(ddscaps));
    ddscaps.dwCaps=DDSCAPS_TEXTURE;
    DWORD	tmpFreeRAM;

    //get available video memory to decide whether a mode should be allowed
    pDD7->GetAvailableVidMem(&ddscaps,&texturesTotalRAM,&tmpFreeRAM);

    PreBuildTextures();

    for (i=MAX_TEXTURES-1; i>=0; textureTable[i--]=NULL);

    if (CheckIfTextureCanBeRenderTarget()==DD_OK)
        flags=Flags(flags|F_TEXTURECANBERENDERTARGET);
    else
        flags=Flags(flags&~F_TEXTURECANBERENDERTARGET);

    IsSlowCopyRequired();


//	CpuInfo();

    projMatStackPos=
        viewMatStackPos=
            objMatStackPos=0;

    lastError=S_OK;

    D3DVERTEXBUFFERDESC vertBufDesc;

    vertBufDesc.dwSize=sizeof(D3DVERTEXBUFFERDESC);
    vertBufDesc.dwCaps=0;//D3DVBCAPS_SYSTEMMEMORY;

#ifndef NO_HARD_TNL
    if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
    {
        vertBufDesc.dwNumVertices=2048;
        vertBufDesc.dwFVF=D3DFVF_R3DVERTEX;
    }
    else
#endif
    {
        vertBufDesc.dwNumVertices=1024;
        vertBufDesc.dwFVF=D3DFVF_TLVERTEX;
        vertBufDesc.dwCaps=D3DVBCAPS_SYSTEMMEMORY;

// Create a vertex buffer for lines only...	   NUM_FLAG_VERTICES

        if ((lastError=pD3D7->CreateVertexBuffer(&vertBufDesc,&gpD3DVBL7,NULL))!=D3D_OK)
            CloseDown();

        vertBufDesc.dwCaps=D3DVBCAPS_SYSTEMMEMORY;
        vertBufDesc.dwNumVertices=1024;
        vertBufDesc.dwFVF=D3DFVF_R3DTNLVERTEX3;

//	ULong sz1,sz2,sz3;
    }
    if ((lastError=pD3D7->CreateVertexBuffer(&vertBufDesc,&gpD3DVB7,NULL))!=D3D_OK)
        CloseDown();

    memPool=AllocInit();
    RadixReset();

    if (selectedDevice.wMaxTextureBlendStages<2 ||
            selectedDevice.wMaxSimultaneousTextures<2)
        flags=Flags(flags|F_CANTBLENDTEXTURES);
    else
        flags=Flags(flags&~F_CANTBLENDTEXTURES);

    if  ( (selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGTABLE)!=0 )
        flags=Flags(flags&(~F_VERTEXFOG));
    else
        flags=Flags(flags|F_VERTEXFOG);

    if (selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_ANTIALIASEDGES)
        masterEdgeAlias=HINT_ALIASEDGES;
    else
        masterEdgeAlias=HINT_ALIASNONE;

    renderMode=HINT_3DRENDER;

#ifdef _NO_CLIPPING_RESIZE
//DeadCode  28Oct00 	guardBandMod = CLIP_RESIZE_FACTOR;
    hwClip = false;
#else
#ifndef _NO_GUARDBAND_CLIPPING_
    if ( selectedDevice.dvGuardBandRight >= 10.f )
    {
        //DeadCode JON 12Jun00 		hwClipFlag=F_NULL;  // we don't ever need to do any clipping - never set the clipflag
        // now we need to calculate a value to have hw multiplied by.
        float sx, sy, cx, cy;
        GetViewPort( sx, sy, cx, cy );

        guardBandModLeft = -(selectedDevice.dvGuardBandLeft/sx)*0.99f;
        guardBandModRight = ((selectedDevice.dvGuardBandRight-sx)/sx)*0.99f;
        guardBandModTop = (selectedDevice.dvGuardBandTop/sy)*0.99f;
        guardBandModBottom = -((selectedDevice.dvGuardBandBottom+sy)/sy)*0.99f;

//DeadCode JON 28Oct00 		float bandScale, bandScaleOther;
//DeadCode JON 28Oct00
//DeadCode JON 28Oct00 		bandScale = -(selectedDevice.dvGuardBandLeft/sx)*0.99f;
//DeadCode JON 28Oct00 		bandScaleOther = ((selectedDevice.dvGuardBandRight-sx)/sx)*0.99f;
//DeadCode JON 28Oct00 		if ( bandScaleOther < bandScale )
//DeadCode JON 28Oct00 			bandScale = bandScaleOther;
//DeadCode JON 28Oct00 		bandScaleOther = (selectedDevice.dvGuardBandTop/sy)*0.99f;
//DeadCode JON 28Oct00 		if ( bandScaleOther < bandScale )
//DeadCode JON 28Oct00 			bandScale = bandScaleOther;
//DeadCode JON 28Oct00 		bandScaleOther = -((selectedDevice.dvGuardBandBottom+sy)/sy)*0.99f;
//DeadCode JON 28Oct00 		if ( bandScaleOther < bandScale )
//DeadCode JON 28Oct00 			bandScale = bandScaleOther;
//DeadCode JON 28Oct00
//DeadCode JON 28Oct00 		if ( bandScale > 2.0f )
//DeadCode JON 28Oct00 		{
//DeadCode JON 28Oct00 			guardBandMod = bandScale;
//DeadCode JON 28Oct00 			hwClip = true;
//DeadCode JON 28Oct00 		} else
//DeadCode JON 28Oct00 		{
//DeadCode JON 28Oct00 			hwClip = false;
//DeadCode JON 28Oct00 		}
//DeadCode JON 28Oct00 		float bandClipScaleVert = (selectedDevice.dvGuardBandRight/sx)*0.95f;
//DeadCode JON 28Oct00 		float bandClipScaleHoriz = (selectedDevice.dvGuardBandTop/sy)*0.95f;
//DeadCode JON 28Oct00 		if ( bandClipScaleVert > bandClipScaleHoriz ) // use the smaller
//DeadCode JON 28Oct00 			guardBandMod = bandClipScaleHoriz;
//DeadCode JON 28Oct00 		else
//DeadCode JON 28Oct00 			guardBandMod = bandClipScaleVert;
//DeadCode  28Oct00 		hwClip = true;
    }
    else
        hwClip = false;
#else
    hwClip = false;
#endif
#endif
//DeadCode JON 12Jun00 	else
//DeadCode JON 12Jun00 	hwClipFlag=F_NOCLIPPING; // we may need to clip
//dvGuardBandLeft, dvGuardBandTop, dvGuardBandRight, and dvGuardBandBottom
    //let the kludges begin!
    HandleNaffDriver();

    if ( flags&F_VERTEXFOG )
    {
        // vertex fog mode
        globTextureTypeFlags = DO_SW_FOG;
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_NONE);
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_LINEAR);
    }
    else
    {
        globTextureTypeFlags = 0;
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_LINEAR);
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_NONE);
    }


//deadcode	if ((flags&F_CANTMANAGETEXTURES)==0)
    pD3D7->EvictManagedTextures();


//DeadCode CSB 12Jul00 	LPDIRECTDRAWCOLORCONTROL colCont;
//DeadCode CSB 12Jul00 	HRESULT hr = pDDSP7->QueryInterface( IID_IDirectDrawColorControl, (LPVOID*)&colCont );
//DeadCode CSB 12Jul00 	char* errordesc;
//DeadCode CSB 12Jul00 	GetErrorDesc( hr, errordesc );
//DeadCode CSB 12Jul00
//DeadCode CSB 12Jul00
//DeadCode CSB 12Jul00 	DDCOLORCONTROL colContDesc;
//DeadCode CSB 12Jul00 	colContDesc.dwSize = sizeof( DDCOLORCONTROL );
//DeadCode CSB 12Jul00
//DeadCode CSB 12Jul00 	colCont->GetColorControls( &colContDesc );

    return lastError;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestoreDisplayMode
//Author		Paul.
//Date			Wed 15 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::RestoreDisplayMode()
{
    for (int i=MAX_TEXTURES-1; i>=0; i--)
        if (textureTable[i]!=NULL)
        {
            textureTable[i]->Release();
            textureTable[i]=NULL;
        }
    CloseDown(true);
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScreenSwap
//Author		Paul.
//Date			Wed 10 Nov 1999

//
//------------------------------------------------------------------------------
HRESULT Lib3D::ScreenSwap()
{
	if (pDDSP7 == NULL)
	{
		INT3;
	}
	else
	{
		if (flags&F_WINDOWED)
			lastError = pDDSP7->Blt(&windowRect, pDDSB7, NULL, DDBLT_WAIT, NULL);
		else
			lastError = pDDSP7->Flip(NULL, DDFLIP_WAIT);
	}

    if (lastError!=DD_OK)
        CloseDown();

#ifndef _NO_VERTEX_SHARING
    // fill the last vertex table with the dummy vertex.
    for ( int i=0; i<=MAX_DOPOINTS; i++ )
    {
//		lastDoPoint[ i ] = &dummyVertex;
        lastDoPoint[ i ]->info.addToFlags( PLAINCOL_FLAG );
//		lastDoPoint[ i ]->info.setAllInvalid();
    }
#endif
    static DWORD lastTime = 0;
    DWORD time = timeGetTime();
    int frameTime = time - lastTime;

    if ( frameTime<minFrameTime ) // lock to min frame time
        Sleep(minFrameTime-frameTime);

    frameTime = timeGetTime() - lastTime;

    if ( frameTimeBuff != NULL )
    {
        QueryPerformanceCounter( &tickCountBuff[curFrameTimeI] );
        frameTimeBuff[curFrameTimeI++] = frameTime;
        curFrameTimeI%=frameTimeBuffSize;
    }

    lastTime+=frameTime;

//tempcode JON 15/03/01		static DWORD lastTime = 0;
//tempcode JON 15/03/01		DWORD frameTime = lastTime+minFrameTime;
//tempcode JON 15/03/01		while( (lastTime=timeGetTime())<frameTime )
//tempcode JON 15/03/01		{/*nasty loop of doom*/
//tempcode JON 15/03/01			Sleep(1);
//tempcode JON 15/03/01		};

    return lastError;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetGamma

// Date:		12/07/00
// Author:		JON
//
//Description:	Sets the gamma ramps -set values from 0 - 4 inclusive
//				0 - darken most, 1 - darken a bit, 2 - nothing, 3 - lighten, 4 - lighten most
//	NOTE:		Only works for full screen modes.
//
////////////////////////////////////////////////////////////////////////
HRESULT Lib3D::SetGammaLevel( ULong val )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    switch ( val )
    {
    case 0:
        return SetGamma( double( 1.0/2.0 ) );
        break;
    case 1:
        return SetGamma( double( 1.0/1.5 ) );
        break;
    case 2:
        return SetGamma( double( 1.0 ) );
        break;
    case 3:
        return SetGamma( double( 1.5 ) );
        break;
    case 4:
        return SetGamma( double( 2.0 ) );
        break;
    default:
        return DDERR_INVALIDPARAMS;
        break;
    }
#endif
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetGamma

// Date:		12/07/00
// Author:		JON
//
//Description:	Sets the gamma ramps - set with +ve values to darken and with 1/values for lighten
//				Creates a curve with x to pow gammaAmmount between 0-1 then scaled
//	NOTE:		Only works for full screen modes.
//
////////////////////////////////////////////////////////////////////////
HRESULT Lib3D::SetGamma( double gammaAmount )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    LPDIRECTDRAWGAMMACONTROL gammaCont;
    lastError = pDDSP7->QueryInterface( IID_IDirectDrawGammaControl, (LPVOID*)&gammaCont );
    if ( lastError != S_OK )
        return lastError;

    DDGAMMARAMP gammaContDesc;

    DWORD  dwFlags=0;

    for ( int i = 0; i< 256; i++ )
    {
        double tmpVal = double(i)/255.0;
        tmpVal = pow( tmpVal, gammaAmount );
        tmpVal *= (255.0 * 256.0);
        gammaContDesc.red[i] =
            gammaContDesc.green[i] =
                gammaContDesc.blue[i] = DWORD( tmpVal );
    }

    lastError=gammaCont->SetGammaRamp( dwFlags, &gammaContDesc );

    gammaCont->Release();
    gammaCont=NULL;

    return lastError;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPaletteTable
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetPaletteTable(UByte* pPalettes)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    if (pPalettes==NULL) return lastError=DDERR_GENERIC;

//DeadCode JON 26Sep00 	memcopy(paletteTable,pPalettes,256*3*NUM_PALETTES);
    paletteTable = pPalettes;

#ifdef _NOBBLE_BRIGHTERSHAPE
    // right have a go at lightening up that palette
    const float palMod = 1.25;
    for ( int j = 32*3; j< 256*3; j++ )
    {
        float newVal=float(paletteTable[j])*palMod;
        if ( newVal > 255.f )
            paletteTable[j]=255;
        else
            paletteTable[j]=UByte( newVal );
    }

#endif

#ifndef NO_HARD_TNL
    D3DMATERIAL7 *pM7=materialTable;
    UByte *pPal=paletteTable;
    D3DVALUE colorScale=1.f/255.f;
    D3DCOLORVALUE nullColour= {0.f,0.f,0.f,0.f};
    ZeroMemory(pM7,sizeof(D3DMATERIAL7)*256);
    for (int i=0; i<256; i++)
    {
        pM7->diffuse.dvR=*pPal++;
        pM7->diffuse.dvG=*pPal++;
        pM7->diffuse.dvB=*pPal++;
        pM7->diffuse.dvR*=colorScale;
        pM7->diffuse.dvG*=colorScale;
        pM7->diffuse.dvB*=colorScale;
        pM7++;
    }
    // alpha runs in opposite direction as they are subtracted
    materialMapped.diffuse.dvR=
        materialMapped.diffuse.dvG=
            materialMapped.diffuse.dvB=1.f;
    materialMapped.diffuse.dvA=0.f;
    materialMapped.ambient.dvR=
        materialMapped.ambient.dvG=
            materialMapped.ambient.dvB=8.f;
    materialMapped.ambient.dvA=0.f;
    materialMapped.emissive=
        materialMapped.specular=nullColour;
#endif
    return lastError=S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSurfaceDesc
//Author		Paul.
//Date			Fri 3 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::GetSurfaceDesc(ROWANSURFACEDESC *pRowanSurface)
{
    return pDDSB7->GetSurfaceDesc((LPDDSURFACEDESC2)pRowanSurface);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginScene
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::BeginScene(const HRENDERTARGET & hRenderTarget)
{
#ifdef	_SHAPE_DEBUG_
    noPolysDebug = 0;
#endif

    if ((flags&F_INSCENE)!=0)
        return D3DERR_SCENE_IN_SCENE;

    globAlpha = 0xFF;//0x00;

    zDepth2d=0.0f;
    zBuffer2d=0;
    hLastMaterial=HMATERIAL();

    updateLightVecs=true;
    fCombineMatrices=true;
    transMatPos=-1;
    addNewTransMat=true;
    fRecalcClipPlanes=true;

//DeadCode JON 6Sep00 	FillFogTable(fogStart,fogEnd);

    lightflag=LF_AMBIENT;
    edgeAlias=HINT_ALIASNONE;
    renderMode=HINT_3DRENDER;
    gFontColour=0x00FFFFFF;
//TEMPCODE JON 3/30/00 	gFontColour=gLightingDesc.ambientRGB;
//TEMPCODE JON 3/30/00 	SetColAlpha( gFontColour, 0 );

    gLightingDesc.ambientRGB=
        gLightingDesc.lowRGB=
            gLightingDesc.highRGB=0;
//DeadCode JON 11Sep00 	gLightingDesc.specularPower=0.f;
    gLightingDesc.lowDot=
        gLightingDesc.highDot=123456.f;

//DeadCode JON 20Sep00 	lightModeFlag = 0;
    lightModeCount = 0;

    AllocResetPool();

    HRESULT tmp = _BeginScene( hRenderTarget );

#ifdef _WIPE_BACKGROUND
    switch (hRenderTarget.getType())
    {
    case RENDERTARGET_PRIMARY:
//			pD3DDEV7->Clear(0,NULL,D3DCLEAR_TARGET,0x0090B8E8,0,0);
        pD3DDEV7->Clear(0,NULL,D3DCLEAR_TARGET,0x00FF0000,0,0);
        break;
    case RENDERTARGET_MIRROR:
        pD3DDEV7->Clear(0,NULL,D3DCLEAR_TARGET,0x0000FF00,0,0);
        break;
    case RENDERTARGET_LANDSCAPE:
        pD3DDEV7->Clear(0,NULL,D3DCLEAR_TARGET,0x000000FF,0,0);
        break;
    }
#endif

    return tmp;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		_BeginScene
//Author		Jon
//
//				Stripped out of above so it can be used from FlushAsBackground too
//------------------------------------------------------------------------------
//#pragma warnmsg( "inline me" )
inline HRESULT Lib3D::_BeginScene(const HRENDERTARGET & hRenderTarget)
{
    flags=Flags(flags|F_INSCENE);

    plainPolyVCnt=0;
    textPolyVCnt = 0;
    texturedPolys = NULL;
    if ( prefZType == D3DZB_USEW )
        zBias = NUM_Z_LAYERS;
    else
        zBias = 0;
    tZBias = 0;
    tZBias_f = D3DVALUE( tZBias );

    plainPolys=
        transparentPolys=NULL;
    lineList=NULL;
    aliasLineList=NULL;
    pointList=NULL;

    if (hRenderTarget.getType()!=hCurrentRenderTarget.getType())
    {
        switch (hRenderTarget.getType())
        {
        case RENDERTARGET_PRIMARY:
        {
            globTextureTypeFlags&=(~LANDSCAPE_TEXTURE);
            flags=Flags(flags&~F_NOCLIPPING);
            if ( flags&F_TEXTURECANBERENDERTARGET )
                lastError=pD3DDEV7->SetRenderTarget(pDDSB7,0);

            if (flags&F_WINDOWED)
            {
                ULong dwRenderWidth=windowRect.right-windowRect.left;
                ULong dwRenderHeight=windowRect.bottom-windowRect.top;
                D3DVIEWPORT7 vp= {0,0,dwRenderWidth,dwRenderHeight,0,1.0f};
                lastError=pD3DDEV7->SetViewport(&vp);
                clipVal2D = 1.0f + (1.f/vp.dwHeight);
            }
            else
            {
                D3DVIEWPORT7 vp= {0,0,selectedMode.ddsd.dwWidth,selectedMode.ddsd.dwHeight,0,1.0f};
                lastError=pD3DDEV7->SetViewport(&vp);
                clipVal2D = 1.0f + (1.f/vp.dwHeight);
            }

            lastError=pD3DDEV7->BeginScene();
#ifndef NO_HARD_TNL
            if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
            {
                lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_CLIPPING,TRUE);
                lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE);
            }
            else
#endif
            {
                lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_CLIPPING,FALSE);
                lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);
            }
            lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_EXTENTS,FALSE);
            lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);

            EnableFogging(true);
            break;
        }
        case RENDERTARGET_MIRROR:

        {
            clipVal2D = 1.0f;
            lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);

            globTextureTypeFlags&=(~LANDSCAPE_TEXTURE);
            flags=Flags(flags&~F_NOCLIPPING);

            if ( flags&F_TEXTURECANBERENDERTARGET )
                lastError=pD3DDEV7->SetRenderTarget(pDDS7MirrorRT,0);
            D3DVIEWPORT7 vp= {mirrorRect.left,mirrorRect.top,mirrorRect.right,mirrorRect.bottom,0,1};
            lastError=pD3DDEV7->SetViewport(&vp);

            //lastError=pD3DDEV7->SetViewport(&vp);
            lastError=pD3DDEV7->BeginScene();
            lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);
            EnableFogging(true);
        }
        break;
        case RENDERTARGET_LANDSCAPE:
        {
            lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);

            SLong index = hRenderTarget.getInstance();
            for (int i=0; i<8; i++)
            {
                if ( index<landTextureBandSize[i] )
                {
                    index=i;
                    break;
                }
                index-=landTextureBandSize[i];
            }
//DeadCode JON 16Oct00 			D3DVALUE textureDimension = D3DVALUE(1024>>index);
            ULong textureDimension = ULong(1024>>index);
//DeadCode JON 16Oct00 			landRect.right=landRect.bottom=textureDimension;
            globTextureTypeFlags|=LANDSCAPE_TEXTURE;
            lightflag=LF_LIGHTSOURCE;
//DeadCode JON 25Sep00 			flags=Flags(flags|F_NOCLIPPING); // turn off clipping
            flags=Flags(flags&~F_NOCLIPPING); // no make sure it is on actually
            if ( flags&F_TEXTURECANBERENDERTARGET )
            {
                landRect.left=
                    landRect.top=0;
                landRect.right=
                    landRect.bottom=
                        textureDimension;
                lastError=pD3DDEV7->SetRenderTarget(pDDS7LandRT,0);
            }
            else
            {
                // center the landrect on the screen...
                ULong dwRenderWidth,dwRenderHeight;
                if (flags&F_WINDOWED)
                {
                    dwRenderWidth=windowRect.right-windowRect.left;
                    dwRenderHeight=windowRect.bottom-windowRect.top;
                }
                else
                {
                    dwRenderWidth=selectedMode.ddsd.dwWidth;
                    dwRenderHeight=selectedMode.ddsd.dwHeight;
                }

                landRect.left=(dwRenderWidth-textureDimension)>>1;
                landRect.top=(dwRenderHeight-textureDimension)>>1;
                landRect.right=landRect.left+textureDimension;
                landRect.bottom=landRect.top+textureDimension;
                //end of center on the screen
            }

            D3DVIEWPORT7 vp= {landRect.left,landRect.top,textureDimension,textureDimension,0,1.0f};
            lastError=pD3DDEV7->SetViewport(&vp);

//TempCode JON 25Sep00 			clipVal2D = 1.0f + (0.5f/textureDimension);
            clipVal2D = 1.0f + (1.f/256.f);

            lastError=pD3DDEV7->BeginScene();
            lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);

            EnableFogging(false);
        }
        break;
        NODEFAULT;
        }
        hCurrentRenderTarget=hRenderTarget;
    }
    else
    {
        lastError=pD3DDEV7->BeginScene();
        switch (hCurrentRenderTarget.getType())
        {
        case RENDERTARGET_PRIMARY:
            lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);
            EnableFogging(true);
            break;
        case RENDERTARGET_MIRROR:
//TempCode JON 7Nov00 			lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER|D3DCLEAR_TARGET,0x0000FF00,1,0);
            lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);
            break;
        case RENDERTARGET_LANDSCAPE:
        {
            lightflag=LF_LIGHTSOURCE;
            hCurrentRenderTarget = hRenderTarget;
            SLong index = hRenderTarget.getInstance();
            for (int i=0; i<8; i++)
            {
                if ( index<landTextureBandSize[i] )
                {
                    index=i;
                    break;
                }
                index-=landTextureBandSize[i];
            }
//DeadCode JON 16Oct00 			D3DVALUE textureDimension = D3DVALUE(1024>>index);
            ULong textureDimension = ULong(1024>>index);
//DeadCode JON 16Oct00 			landRect.right=landRect.bottom = textureDimension;
            if ( flags&F_TEXTURECANBERENDERTARGET )
            {
                landRect.left=
                    landRect.top=0;
                landRect.right=
                    landRect.bottom=
                        textureDimension;
            }
            else
            {
                // center the landrect on the screen...
                ULong dwRenderWidth,dwRenderHeight;
                if (flags&F_WINDOWED)
                {
                    dwRenderWidth=windowRect.right-windowRect.left;
                    dwRenderHeight=windowRect.bottom-windowRect.top;
                }
                else
                {
                    dwRenderWidth=selectedMode.ddsd.dwWidth;
                    dwRenderHeight=selectedMode.ddsd.dwHeight;
                }

                landRect.left=(dwRenderWidth-textureDimension)>>1;
                landRect.top=(dwRenderHeight-textureDimension)>>1;
                landRect.right=landRect.left+textureDimension;
                landRect.bottom=landRect.top+textureDimension;
                //end of center on the screen
            }
            D3DVIEWPORT7 vp= {landRect.left,landRect.top,textureDimension,textureDimension,0,1.0f};
//DeadCode JON 16Oct00 			D3DVIEWPORT7 vp={0.f,0.f,textureDimension,textureDimension,0.0f,1.0f};
            lastError=pD3DDEV7->SetViewport(&vp);
            lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);
            break;
        }
        NODEFAULT;
        }

    }
    return S_OK;
}
HRESULT Lib3D::ClearTargetZ()
{
    switch (hCurrentRenderTarget.getType())
    {
    case RENDERTARGET_PRIMARY:
        lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);
        break;
    case RENDERTARGET_MIRROR:
        lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER|D3DCLEAR_TARGET,0x007F7F7F,1,0);
        break;
    case RENDERTARGET_LANDSCAPE:
        lastError=pD3DDEV7->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1,0);
        break;
        NODEFAULT;
    }
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		End3DScene
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::End3DScene()
{
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndScene
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::EndScene()
{
	pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGCOLOR, gFogColour);

#ifndef NO_HARD_TNL
	if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
	{
		if (texturedPolys!=NULL)	RenderTLPolyList(texturedPolys);
		if (transparentPolys!=NULL)	RenderTransTLPolyList(transparentPolys);
	}
	else
#endif
	{
		InlineSetCurrentMaterial(hLastMaterial, IS_PLAIN);
		if (lineList != NULL)
			RenderLineList(lineList);
		if (pointList != NULL)
			RenderPointList(pointList);
		if (plainPolys != NULL)
		{
			RenderPlainPolyList(plainPolys);
		}
		//DeadCode JON 21Aug00 		for ( int i=NUM_Z_LAYERS-1; i>=0; i-- )
		//DeadCode JON 21Aug00 		for ( int i=0; i<NUM_Z_LAYERS; i++ )
		//DeadCode JON 21Aug00 		{
		//DeadCode JON 21Aug00 			if (texturedPolys[i]!=NULL)
		//DeadCode JON 21Aug00 				RenderPolyList(texturedPolys[i]);
		//DeadCode JON 21Aug00 		}
		if (texturedPolys != NULL)
			RenderPolyList(texturedPolys);
		if (transparentPolys != NULL)
			RenderTPolyList(transparentPolys);
	}
	//TempCode JON 18Sep00 	if (aliasLineList!=NULL)
	//TempCode JON 18Sep00 	{
	//TempCode JON 18Sep00 		InlineSetCurrentMaterial( hLastMaterial, IS_PLAIN );
	//TempCode JON 18Sep00 		pD3DDEV7->SetRenderState(D3DRENDERSTATE_EDGEANTIALIAS,TRUE);
	//TempCode JON 18Sep00 		RenderLineList(aliasLineList);
	//TempCode JON 18Sep00 //DeadCode JON 23Aug00 		pD3DDEV7->SetRenderState(D3DRENDERSTATE_EDGEANTIALIAS,FALSE);
	//TempCode JON 18Sep00 	}
	//	if (transparentPolys!=NULL)	RenderTPolyList(transparentPolys);

	if ((lastError = pD3DDEV7->EndScene()) != D3D_OK)
			  CloseDown();

    flags=Flags(flags&~F_INSCENE);
    return lastError;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PushMatrix
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::PushMatrix(const HMATRIX& hMatrix)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        projMatStackPos++;
        if (projMatStackPos>=MATRIX_STACK_SIZE)
            return lastError=DDERR_GENERIC;
        projectionMatrix[projMatStackPos]=projectionMatrix[projMatStackPos-1];
//DeadCode JON 19Sep00 		projMatBits[projMatStackPos]=projMatBits[projMatStackPos-1];
        break;
    case MATRIX_VIEWER:
        viewMatStackPos++;
        if (viewMatStackPos>=MATRIX_STACK_SIZE)
            return lastError=DDERR_GENERIC;
        viewerMatrix[viewMatStackPos]=viewerMatrix[viewMatStackPos-1];
//DeadCode JON 19Sep00 		viewMatBits[viewMatStackPos]=viewMatBits[viewMatStackPos-1];
        break;
    case MATRIX_OBJECT:
        objMatStackPos++;
        if (objMatStackPos>=MATRIX_STACK_SIZE)
            return lastError=DDERR_GENERIC;
        objectMatrix[objMatStackPos]=objectMatrix[objMatStackPos-1];
//DeadCode JON 19Sep00 		objMatBits[objMatStackPos]=objMatBits[objMatStackPos-1];
        break;
    default:
        return lastError=DDERR_INVALIDPARAMS;
    }
    return lastError=S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PopMatrix
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::PopMatrix(const HMATRIX& hMatrix)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    R3DMATRIX *pMat;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        if ( !MatrixEqu( projectionMatrix[projMatStackPos], projectionMatrix[projMatStackPos-1] ) )
            fCombineMatrices=true;
        projMatStackPos--;
        if (projMatStackPos<0)
        {
            projMatStackPos=0;
            return lastError=DDERR_GENERIC;
        }
        pMat=projectionMatrix+projMatStackPos;
        break;
    case MATRIX_VIEWER:
        if ( !MatrixEqu( viewerMatrix[viewMatStackPos], viewerMatrix[viewMatStackPos-1] ) )
            fCombineMatrices=true;
        viewMatStackPos--;
        if (viewMatStackPos<0)
        {
            viewMatStackPos=0;
            return lastError=DDERR_GENERIC;
        }
        pMat=viewerMatrix+viewMatStackPos;
        break;
    case MATRIX_OBJECT:
        if ( !MatrixEqu( objectMatrix[objMatStackPos], objectMatrix[objMatStackPos-1] ) )
        {
            fCombineMatrices=updateLightVecs=true;
        }
        objMatStackPos--;
        if (objMatStackPos<0)
        {
            objMatStackPos=0;
            return lastError=DDERR_GENERIC;
        }
        pMat=objectMatrix+objMatStackPos;
        break;
    default:
        return lastError=DDERR_INVALIDPARAMS;
    }
    fRecalcClipPlanes=fCombineMatrices;
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMatrix
//Author		Paul.
//Date			Thu 9 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetMatrix(const HMATRIX& hMatrix,const R3DMATRIX& mat)
{
    R3DMATRIX *pMat;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
        if ( !MatrixEqu( *pMat, mat ) )
        {
            fCombineMatrices=true;
            *pMat=mat;
        }
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
        if ( !MatrixEqu( *pMat, mat ) )
        {
            fCombineMatrices=true;
            *pMat=mat;
        }
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
        if ( !MatrixEqu( *pMat, mat ) )
        {
            fCombineMatrices=updateLightVecs=true;
            *pMat=mat;
        }
        break;
    default:
        return DDERR_INVALIDPARAMS;
    }

//DEADCODE JON 5/11/00 	if ( !MatrixEqu( *pMat, mat ) )
//DEADCODE JON 5/11/00 	{
//DEADCODE JON 5/11/00 		fCombineMatrices=true;
//DEADCODE JON 5/11/00 		*pMat=mat;
//DEADCODE JON 5/11/00 	}
    fRecalcClipPlanes=fCombineMatrices;
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMatrix
//Author		Paul.
//Date			Thu 9 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::GetMatrix(const HMATRIX& hMatrix,R3DMATRIX& mat)
{
    R3DMATRIX *pMat;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
        break;
    default:
        return DDERR_INVALIDPARAMS;
    }
    mat=*pMat;
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadIdentity
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::LoadIdentity(const HMATRIX& hMatrix)
{
    R3DMATRIX *pMat;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
//DeadCode JON 19Sep00 		projMatBits[projMatStackPos]=M_IDENTITY;
        if ( !MatrixEqu( *pMat, IDENTITY ) )
        {
            fCombineMatrices=true;
            *pMat=IDENTITY;
        }
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
//DeadCode JON 19Sep00 		viewMatBits[viewMatStackPos]=M_IDENTITY;
        if ( !MatrixEqu( *pMat, IDENTITY ) )
        {
            fCombineMatrices=true;
            *pMat=IDENTITY;
        }
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
//DeadCode JON 19Sep00 		objMatBits[objMatStackPos]=M_IDENTITY;
        if ( !MatrixEqu( *pMat, IDENTITY ) )
        {
            fCombineMatrices=updateLightVecs=true;
            *pMat=IDENTITY;
        }
        break;
    default:
        pMat=(R3DMATRIX*)hMatrix;
        if ( !MatrixEqu( *pMat, IDENTITY ) )
        {
            *pMat=IDENTITY;
        }
    }
//DEADCODE JON 5/11/00 	if ( !MatrixEqu( *pMat, IDENTITY ) )
//DEADCODE JON 5/11/00 	{
//DEADCODE JON 5/11/00 		fCombineMatrices=true;
//DEADCODE JON 5/11/00 		*pMat=IDENTITY;
//DEADCODE JON 5/11/00 	}
    fRecalcClipPlanes=fCombineMatrices;
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Rotate
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::Rotate(const HMATRIX& hMatrix,const HAXIS& hAxis,const Angles& rotation)
{
    R3DMATRIX *pMat;
//DeadCode JON 19Sep00 	ULong *pBit,bit;
    D3DTRANSFORMSTATETYPE trnsStateType;

    if (UWord(rotation)==0)
        return lastError=S_OK;

    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
//DeadCode JON 19Sep00 		pBit=projMatBits+projMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_PROJECTION;
        fCombineMatrices=true;
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
//DeadCode JON 19Sep00 		pBit=viewMatBits+viewMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_VIEW;
        fCombineMatrices=true;
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
//DeadCode JON 19Sep00 		pBit=objMatBits+objMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_WORLD;
        fCombineMatrices=updateLightVecs=true;
        break;
    default:
        pMat=(R3DMATRIX*)hMatrix;
//DeadCode JON 19Sep00 		bit=MatrixFlags(pMat);
//DeadCode JON 19Sep00 		pBit=&bit;
    }
    D3DVALUE sine,cosine,temp;
    SineCosine(rotation,&sine,&cosine);
    switch (hAxis)
    {
    case AXIS_PITCH:
        temp=pMat->_12;
        pMat->_12=temp*cosine-pMat->_13*sine;
        pMat->_13=temp*sine+pMat->_13*cosine;
        temp=pMat->_22;
        pMat->_22=temp*cosine-pMat->_23*sine;
        pMat->_23=temp*sine+pMat->_23*cosine;
        temp=pMat->_32;
        pMat->_32=temp*cosine-pMat->_33*sine;
        pMat->_33=temp*sine+pMat->_33*cosine;
        temp=pMat->_42;
        pMat->_42=temp*cosine-pMat->_43*sine;
        pMat->_43=temp*sine+pMat->_43*cosine;
        break;
    case AXIS_HEADING:
        temp=pMat->_11;
        pMat->_11=temp*cosine+pMat->_13*sine;
        pMat->_13=pMat->_13*cosine-temp*sine;
        temp=pMat->_21;
        pMat->_21=temp*cosine+pMat->_23*sine;
        pMat->_23=pMat->_23*cosine-temp*sine;
        temp=pMat->_31;
        pMat->_31=temp*cosine+pMat->_33*sine;
        pMat->_33=pMat->_33*cosine-temp*sine;
        temp=pMat->_41;
        pMat->_41=temp*cosine+pMat->_43*sine;
        pMat->_43=pMat->_43*cosine-temp*sine;
        break;
    case AXIS_ROLL:
        temp=pMat->_11;
        pMat->_11=temp*cosine-pMat->_12*sine;
        pMat->_12=temp*sine+pMat->_12*cosine;
        temp=pMat->_21;
        pMat->_21=temp*cosine-pMat->_22*sine;
        pMat->_22=temp*sine+pMat->_22*cosine;
        temp=pMat->_31;
        pMat->_31=temp*cosine-pMat->_32*sine;
        pMat->_32=temp*sine+pMat->_32*cosine;
        temp=pMat->_41;
        pMat->_41=temp*cosine-pMat->_42*sine;
        pMat->_42=temp*sine+pMat->_42*cosine;
        break;
    default:
        return lastError=DDERR_INVALIDPARAMS;
    }
//DeadCode JON 19Sep00 	*pBit=MatrixFlags(pMat);
    fRecalcClipPlanes=fCombineMatrices;
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scale
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::Scale(const HMATRIX& hMatrix,const D3DVALUE& scaleFactor)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    R3DMATRIX *pMat;
//DeadCode JON 19Sep00 	ULong *pBit,bit;
    D3DTRANSFORMSTATETYPE trnsStateType;
    ULong fpb;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
//DeadCode JON 19Sep00 		pBit=projMatBits+projMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_PROJECTION;
        fCombineMatrices=true;
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
//DeadCode JON 19Sep00 		pBit=viewMatBits+viewMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_VIEW;
        fCombineMatrices=true;
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
//DeadCode JON 19Sep00 		pBit=objMatBits+objMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_WORLD;
        fCombineMatrices=updateLightVecs=true;
        break;
    default:
        pMat=(R3DMATRIX*)hMatrix;
//DeadCode JON 19Sep00 		bit=MatrixFlags(pMat);
//DeadCode JON 19Sep00 		pBit=&bit;
    }
    fpb=FP_BITS(scaleFactor);
    if (fpb)
    {
        if (fpb!=FP_ONE_BITS)
        {
            pMat->_11*=scaleFactor;
            pMat->_12*=scaleFactor;
            pMat->_13*=scaleFactor;
            pMat->_21*=scaleFactor;
            pMat->_22*=scaleFactor;
            pMat->_23*=scaleFactor;
            pMat->_31*=scaleFactor;
            pMat->_32*=scaleFactor;
            pMat->_33*=scaleFactor;
            pMat->_41*=scaleFactor;
            pMat->_42*=scaleFactor;
            pMat->_43*=scaleFactor;
        }
    }
    else
    {
        FP_BITS(pMat->_11)=0;
        FP_BITS(pMat->_12)=0;
        FP_BITS(pMat->_13)=0;
        FP_BITS(pMat->_21)=0;
        FP_BITS(pMat->_22)=0;
        FP_BITS(pMat->_23)=0;
        FP_BITS(pMat->_31)=0;
        FP_BITS(pMat->_32)=0;
        FP_BITS(pMat->_33)=0;
        FP_BITS(pMat->_41)=0;
        FP_BITS(pMat->_42)=0;
        FP_BITS(pMat->_43)=0;
    }
//DeadCode JON 19Sep00 	*pBit=MatrixFlags(pMat);
    fRecalcClipPlanes=fCombineMatrices;
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scale
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::Scale(const HMATRIX& hMatrix,const D3DVECTOR& scaleVector)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    R3DMATRIX *pMat;
//DeadCode JON 19Sep00 	ULong *pBit,bit;
    D3DTRANSFORMSTATETYPE trnsStateType;
    ULong fpb;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
//DeadCode JON 19Sep00 		pBit=projMatBits+projMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_PROJECTION;
        fCombineMatrices=true;
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
//DeadCode JON 19Sep00 		pBit=viewMatBits+viewMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_VIEW;
        fCombineMatrices=true;
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
//DeadCode JON 19Sep00 		pBit=objMatBits+objMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_WORLD;
        fCombineMatrices=updateLightVecs=true;
        break;
    default:
        pMat=(R3DMATRIX*)hMatrix;
//DeadCode JON 19Sep00 		bit=MatrixFlags(pMat);
//DeadCode JON 19Sep00 		pBit=&bit;
    }
    fpb=FP_BITS(scaleVector.dvX);
    if (fpb)
    {
        if (fpb!=FP_ONE_BITS)
        {
            pMat->_11*=scaleVector.dvX;
            pMat->_21*=scaleVector.dvX;
            pMat->_31*=scaleVector.dvX;
            pMat->_41*=scaleVector.dvX;
        }
    }
    else
    {
        FP_BITS(pMat->_11)=0;
        FP_BITS(pMat->_21)=0;
        FP_BITS(pMat->_31)=0;
        FP_BITS(pMat->_41)=0;
    }
    fpb=FP_BITS(scaleVector.dvY);
    if (fpb)
    {
        if (fpb!=FP_ONE_BITS)
        {
            pMat->_12*=scaleVector.dvY;
            pMat->_22*=scaleVector.dvY;
            pMat->_32*=scaleVector.dvY;
            pMat->_42*=scaleVector.dvY;
        }
    }
    else
    {
        FP_BITS(pMat->_12)=0;
        FP_BITS(pMat->_22)=0;
        FP_BITS(pMat->_32)=0;
        FP_BITS(pMat->_42)=0;
    }
    fpb=FP_BITS(scaleVector.dvZ);
    if (fpb)
    {
        if (fpb!=FP_ONE_BITS)
        {
            pMat->_13*=scaleVector.dvZ;
            pMat->_23*=scaleVector.dvZ;
            pMat->_33*=scaleVector.dvZ;
            pMat->_43*=scaleVector.dvZ;
        }
    }
    else
    {
        FP_BITS(pMat->_13)=0;
        FP_BITS(pMat->_23)=0;
        FP_BITS(pMat->_33)=0;
        FP_BITS(pMat->_43)=0;
    }
//DeadCode JON 19Sep00 	*pBit=MatrixFlags(pMat);
    fRecalcClipPlanes=fCombineMatrices;
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Translate
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::Translate(const HMATRIX& hMatrix,const D3DVECTOR& translateVector)
{
    R3DMATRIX *pMat;
//DeadCode JON 19Sep00 	ULong *pBit,bit;
    D3DTRANSFORMSTATETYPE trnsStateType;
    ULong fpb;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
//DeadCode JON 19Sep00 		pBit=projMatBits+projMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_PROJECTION;
        fCombineMatrices=true;
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
//DeadCode JON 19Sep00 		pBit=viewMatBits+viewMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_VIEW;
        fCombineMatrices=true;
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
//DeadCode JON 19Sep00 		pBit=objMatBits+objMatStackPos;
        trnsStateType=D3DTRANSFORMSTATE_WORLD;
        fCombineMatrices=updateLightVecs=true;
        break;
    default:
        pMat=(R3DMATRIX*)hMatrix;
//DeadCode JON 19Sep00 		bit=MatrixFlags(pMat);
//DeadCode JON 19Sep00 		pBit=&bit;
    }
    fpb=FP_BITS(translateVector.dvX);
    if (fpb)
    {
        if (fpb==FP_ONE_BITS)
        {
            pMat->_11+=pMat->_14;
            pMat->_41+=pMat->_44;
            pMat->_21+=pMat->_24;
            pMat->_31+=pMat->_34;
        }
        else
        {
            pMat->_11+=pMat->_14*translateVector.dvX;
            pMat->_41+=pMat->_44*translateVector.dvX;
            pMat->_21+=pMat->_24*translateVector.dvX;
            pMat->_31+=pMat->_34*translateVector.dvX;
        }
    }
    fpb=FP_BITS(translateVector.dvY);
    if (fpb)
    {
        if (fpb==FP_ONE_BITS)
        {
            pMat->_12+=pMat->_14;
            pMat->_22+=pMat->_24;
            pMat->_32+=pMat->_34;
            pMat->_42+=pMat->_44;
        }
        else
        {
            pMat->_12+=pMat->_14*translateVector.dvY;
            pMat->_22+=pMat->_24*translateVector.dvY;
            pMat->_32+=pMat->_34*translateVector.dvY;
            pMat->_42+=pMat->_44*translateVector.dvY;
        }
    }
    fpb=FP_BITS(translateVector.dvZ);
    if (fpb)
    {
        if (fpb==FP_ONE_BITS)
        {
            pMat->_13+=pMat->_14;
            pMat->_23+=pMat->_24;
            pMat->_33+=pMat->_34;
            pMat->_43+=pMat->_44;
        }
        else
        {
            pMat->_13+=pMat->_14*translateVector.dvZ;
            pMat->_23+=pMat->_24*translateVector.dvZ;
            pMat->_33+=pMat->_34*translateVector.dvZ;
            pMat->_43+=pMat->_44*translateVector.dvZ;
        }
    }
//DeadCode JON 19Sep00 	*pBit=MatrixFlags(pMat);
    fRecalcClipPlanes=fCombineMatrices;
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BodyToScreen
//Author		Paul.
//Date			Tue 23 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::BodyToScreen(const R3DVERTEX& vertex,D3DVALUE& screenx,D3DVALUE& screeny,D3DVALUE& screenz, D3DVALUE* distAtZ)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    if (fCombineMatrices) CombineMatrices();

//	R3DVERTEX* pv = &vertex;

    D3DTLVERTEX transformed;

    Transform(&vertex,&transformed,&combinedMatrix);

    D3DVIEWPORT7 vp;

    D3DVALUE sx,sy;
    D3DVALUE cx,cy;
    GetViewPort( sx, sy, cx, cy );

//DeadCode JON 15Nov00 	pD3DDEV7->GetViewport(&vp);
//DeadCode JON 15Nov00
//DeadCode JON 15Nov00 	sx=D3DVALUE(vp.dwWidth>>1);
//DeadCode JON 15Nov00 	sy=-D3DVALUE(vp.dwHeight>>1);
//DeadCode JON 15Nov00 	cx=D3DVALUE(vp.dwX)+sx;
//DeadCode JON 15Nov00 	cy=D3DVALUE(vp.dwY)-sy;

    D3DVALUE sz;
    sz=1./transformed.rhw;
    screenx=transformed.sx*sz*(sx)+(cx);
    screeny=transformed.sy*sz*(sy)+(cy);
    screenz=transformed.sz; // leave as the distance in cm from the front plane...

    if ( distAtZ != NULL )
        *distAtZ=sz*sx;

    return lastError=S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Transform
//Author		Paul.
//Date			Wed 24 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::Transform(const HMATRIX& hMatrix,DoPointStruc& vertex)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    R3DMATRIX *pMat;
//DeadCode JON 19Sep00 	ULong flags;
    switch (hMatrix)
    {
    case MATRIX_PROJECTION:
        pMat=projectionMatrix+projMatStackPos;
//DeadCode JON 19Sep00 		flags=projMatBits[projMatStackPos];
        break;
    case MATRIX_VIEWER:
        pMat=viewerMatrix+viewMatStackPos;
//DeadCode JON 19Sep00 		flags=viewMatBits[viewMatStackPos];
        break;
    case MATRIX_OBJECT:
        pMat=objectMatrix+objMatStackPos;
//DeadCode JON 19Sep00 		flags=objMatBits[objMatStackPos];
        break;
    default:
        pMat=(R3DMATRIX*)hMatrix;
//DeadCode JON 19Sep00 		flags=MatrixFlags(pMat);
    }
//DeadCode JON 19Sep00 	if (flags==M_IDENTITY) return lastError=S_OK;
    if ( (*pMat)==IDENTITY )
        return lastError=S_OK;

    D3DVALUE x,y,z,w;
    x=vertex.x;
    y=vertex.y;
    z=vertex.z;
    vertex.x=pMat->_11*x+pMat->_21*y+pMat->_31*z+pMat->_41;
    vertex.y=pMat->_12*x+pMat->_22*y+pMat->_32*z+pMat->_42;
    vertex.z=pMat->_13*x+pMat->_23*y+pMat->_33*z+pMat->_43;
    w=pMat->_14*x+pMat->_24*y+pMat->_34*z+pMat->_44;
    if (FP_BITS(w)!=FP_ONE_BITS)
    {
        w=FPInv(w);
        vertex.x*=w;
        vertex.y*=w;
        vertex.z*=w;
    }
    return lastError=S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalculateClipPlanes
//Author		Paul.
//Date			Wed 16 Feb 2000
//
//------------------------------------------------------------------------------
void Lib3D::CalculateClipPlanes()
{
    R3DMATRIX objView;
    R3DMATRIX *proj;
    D3DVALUE *obj,*view;
    obj=(D3DVALUE*)(objectMatrix+objMatStackPos);
    view=(D3DVALUE*)(viewerMatrix+viewMatStackPos);
    //combine object and viewer matrices
    MatMulCEqAxB_AisRot_BisRot(((D3DVALUE*)&objView),obj,view);
    // Note:
    // objView._14, objView._24, objView._34 must be 0.0
    // and objView._44 must be 1.0 for the inverse
    // operation to succeed
    D3DVALUE fInvDeterm = 1.0f/(objView._11*(objView._22*objView._33-objView._23*objView._32)-
                                objView._12*(objView._21*objView._33-objView._23*objView._31)+
                                objView._13*(objView._21*objView._32-objView._22*objView._31));

    D3DVALUE mx11= fInvDeterm*(objView._22*objView._33-objView._23*objView._32);
    D3DVALUE mx12=-fInvDeterm*(objView._12*objView._33-objView._13*objView._32);
    D3DVALUE mx13= fInvDeterm*(objView._12*objView._23-objView._13*objView._22);
    D3DVALUE mx21=-fInvDeterm*(objView._21*objView._33-objView._23*objView._31);
    D3DVALUE mx22= fInvDeterm*(objView._11*objView._33-objView._13*objView._31);
    D3DVALUE mx23=-fInvDeterm*(objView._11*objView._23-objView._13*objView._21);
    D3DVALUE mx31= fInvDeterm*(objView._21*objView._32-objView._22*objView._31);
    D3DVALUE mx32=-fInvDeterm*(objView._11*objView._32-objView._12*objView._31);
    D3DVALUE mx33= fInvDeterm*(objView._11*objView._22-objView._12*objView._21);
    D3DVALUE mx41=-(objView._41*mx11+objView._42*mx21+objView._43*mx31);
    D3DVALUE mx42=-(objView._41*mx12+objView._42*mx22+objView._43*mx32);
    D3DVALUE mx43=-(objView._41*mx13+objView._42*mx23+objView._43*mx33);

    objView._11=mx11;
    objView._12=mx12;
    objView._13=mx13;
    objView._14=0.0f;
    objView._21=mx21;
    objView._22=mx22;
    objView._23=mx23;
    objView._24=0.0f;
    objView._31=mx31;
    objView._32=mx32;
    objView._33=mx33;
    objView._34=0.0f;
    objView._41=mx41;
    objView._42=mx42;
    objView._43=mx43;
    objView._44=1.0f;
    //view cone once transformed is a box with the following coordinates
    // (-1,1,0) , (1,1,0) , (1,-1,0) , (-1,-1,0)
    // (-1,1,1) , (1,1,1) , (1,-1,1) , (-1,-1,1)
    //use the current projection matrix to regenerate the unprojected coordinates
    D3DVALUE x[8]= {-1, 1, 1,-1,-1, 1, 1,-1};
    D3DVALUE y[8]= { 1, 1,-1,-1, 1, 1,-1,-1};
    D3DVALUE z[8]= { 0, 0, 0, 0, 1, 1, 1, 1};
    proj=projectionMatrix+projMatStackPos;
    D3DVALUE fInvProj11=1.f/proj->_11;
    D3DVALUE fInvProj22=1.f/proj->_22;
    for (int i=7; i>=0; i--)
    {
        z[i]=nearZPlane+z[i]*(farZPlane-nearZPlane);
        x[i]*=z[i]*fInvProj11;
        y[i]*=z[i]*fInvProj22;
    }
    D3DVECTOR va,vb,vc,pos,tpos;
    pos.dvX=x[0];
    pos.dvY=y[0];
    pos.dvZ=z[0];
    tpos=pos;
    VecTransform(&tpos,&objView);
    va.dvX=x[1]-pos.dvX;
    va.dvY=y[1]-pos.dvY;
    va.dvZ=z[1]-pos.dvZ;
    vb.dvX=x[3]-pos.dvX;
    vb.dvY=y[3]-pos.dvY;
    vb.dvZ=z[3]-pos.dvZ;
    VecCrossCEqAxB(&vc,&vb,&va);
    VecTransform(&vc,&objView);
    VecNormalise(&vc);
    clipPlanes[0].A=vc.dvX;
    clipPlanes[0].B=vc.dvY;
    clipPlanes[0].C=vc.dvZ;
    clipPlanes[0].D=-VecDotProduct(&vc,&tpos);
    va.dvX=x[4]-pos.dvX;
    va.dvY=y[4]-pos.dvY;
    va.dvZ=z[4]-pos.dvZ;
    VecCrossCEqAxB(&vc,&va,&vb);
    VecTransform(&vc,&objView);
    VecNormalise(&vc);
    clipPlanes[2].A=vc.dvX;
    clipPlanes[2].B=vc.dvY;
    clipPlanes[2].C=vc.dvZ;
    clipPlanes[2].D=-VecDotProduct(&vc,&tpos);
    vb.dvX=x[1]-pos.dvX;
    vb.dvY=y[1]-pos.dvY;
    vb.dvZ=z[1]-pos.dvZ;
    VecCrossCEqAxB(&vc,&vb,&va);
    VecTransform(&vc,&objView);
    VecNormalise(&vc);
    clipPlanes[4].A=vc.dvX;
    clipPlanes[4].B=vc.dvY;
    clipPlanes[4].C=vc.dvZ;
    clipPlanes[4].D=-VecDotProduct(&vc,&tpos);
    pos.dvX=x[4];
    pos.dvY=y[4];
    pos.dvZ=z[4];
    tpos=pos;
    VecTransform(&tpos,&objView);
    va.dvX=x[5]-pos.dvX;
    va.dvY=y[5]-pos.dvY;
    va.dvZ=z[5]-pos.dvZ;
    vb.dvX=x[7]-pos.dvX;
    vb.dvY=y[7]-pos.dvY;
    vb.dvZ=z[7]-pos.dvZ;
    VecCrossCEqAxB(&vc,&va,&vb);
    VecTransform(&vc,&objView);
    VecNormalise(&vc);
    clipPlanes[1].A=vc.dvX;
    clipPlanes[1].B=vc.dvY;
    clipPlanes[1].C=vc.dvZ;
    clipPlanes[1].D=-VecDotProduct(&vc,&tpos);
    pos.dvX=x[6];
    pos.dvY=y[6];
    pos.dvZ=z[6];
    tpos=pos;
    VecTransform(&tpos,&objView);
    va.dvX=x[2]-pos.dvX;
    va.dvY=y[2]-pos.dvY;
    va.dvZ=z[2]-pos.dvZ;
    vb.dvX=x[5]-pos.dvX;
    vb.dvY=y[5]-pos.dvY;
    vb.dvZ=z[5]-pos.dvZ;
    VecCrossCEqAxB(&vc,&vb,&va);
    VecTransform(&vc,&objView);
    VecNormalise(&vc);
    clipPlanes[3].A=vc.dvX;
    clipPlanes[3].B=vc.dvY;
    clipPlanes[3].C=vc.dvZ;
    clipPlanes[3].D=-VecDotProduct(&vc,&tpos);
    vb.dvX=x[7]-pos.dvX;
    vb.dvY=y[7]-pos.dvY;
    vb.dvZ=z[7]-pos.dvZ;
    VecCrossCEqAxB(&vc,&va,&vb);
    VecTransform(&vc,&objView);
    VecNormalise(&vc);
    clipPlanes[5].A=vc.dvX;
    clipPlanes[5].B=vc.dvY;
    clipPlanes[5].C=vc.dvZ;
    clipPlanes[5].D=-VecDotProduct(&vc,&tpos);
    fRecalcClipPlanes=false;
}

//TEMPCODE JON 5/11/00 //get the inverse matrix - note source row 4 must be { 0,0,0,1 }. i.e no funny buisness. (homogenisation)
//TEMPCODE JON 5/11/00 inline void InvertMatrix( R3DMATRIX& source, R3DMATRIX& dest )
//TEMPCODE JON 5/11/00 {
//TEMPCODE JON 5/11/00    D3DVALUE fInvDeterm = 1.0f/(source._11*(source._22*source._33-source._23*source._32)-
//TEMPCODE JON 5/11/00 							  source._12*(source._21*source._33-source._23*source._31)+
//TEMPCODE JON 5/11/00 							  source._13*(source._21*source._32-source._22*source._31));
//TEMPCODE JON 5/11/00
//TEMPCODE JON 5/11/00     D3DVALUE mx11= fInvDeterm*(source._22*source._33-source._23*source._32);
//TEMPCODE JON 5/11/00     D3DVALUE mx12=-fInvDeterm*(source._12*source._33-source._13*source._32);
//TEMPCODE JON 5/11/00     D3DVALUE mx13= fInvDeterm*(source._12*source._23-source._13*source._22);
//TEMPCODE JON 5/11/00     D3DVALUE mx21=-fInvDeterm*(source._21*source._33-source._23*source._31);
//TEMPCODE JON 5/11/00     D3DVALUE mx22= fInvDeterm*(source._11*source._33-source._13*source._31);
//TEMPCODE JON 5/11/00     D3DVALUE mx23=-fInvDeterm*(source._11*source._23-source._13*source._21);
//TEMPCODE JON 5/11/00     D3DVALUE mx31= fInvDeterm*(source._21*source._32-source._22*source._31);
//TEMPCODE JON 5/11/00     D3DVALUE mx32=-fInvDeterm*(source._11*source._32-source._12*source._31);
//TEMPCODE JON 5/11/00     D3DVALUE mx33= fInvDeterm*(source._11*source._22-source._12*source._21);
//TEMPCODE JON 5/11/00     D3DVALUE mx41=-(source._41*mx11+source._42*mx21+source._43*mx31);
//TEMPCODE JON 5/11/00     D3DVALUE mx42=-(source._41*mx12+source._42*mx22+source._43*mx32);
//TEMPCODE JON 5/11/00     D3DVALUE mx43=-(source._41*mx13+source._42*mx23+source._43*mx33);
//TEMPCODE JON 5/11/00
//TEMPCODE JON 5/11/00     dest._11=mx11;    dest._12=mx12;    dest._13=mx13;    dest._14=0.0f;
//TEMPCODE JON 5/11/00     dest._21=mx21;    dest._22=mx22;    dest._23=mx23;    dest._24=0.0f;
//TEMPCODE JON 5/11/00     dest._31=mx31;    dest._32=mx32;    dest._33=mx33;    dest._34=0.0f;
//TEMPCODE JON 5/11/00     dest._41=mx41;    dest._42=mx42;    dest._43=mx43;    dest._44=1.0f;
//TEMPCODE JON 5/11/00 }

void Lib3D::UpdateLightVecs()
{
#ifdef _NOT_IN_SAMPLE
//	INT3;
#else
    updateLightVecs = false;
    //get the inverse matrix - note source row 4 must be { 0,0,0,1 }. i.e no funny buisness. (homogenisation)

    R3DMATRIX* source = objectMatrix+objMatStackPos;

#ifndef NDEBUG
    if ( source->_14 != 0.f ||
            source->_24 != 0.f ||
            source->_34 != 0.f ||
            source->_44 != 1.f )
    {
        INT3; // illegal matrix
    }
#endif

    D3DVALUE fInvDeterm = 1.0f/(source->_11*(source->_22*source->_33-source->_23*source->_32)-
                                source->_12*(source->_21*source->_33-source->_23*source->_31)+
                                source->_13*(source->_21*source->_32-source->_22*source->_31));

    D3DVALUE mx11= fInvDeterm*(source->_22*source->_33-source->_23*source->_32);
    D3DVALUE mx12=-fInvDeterm*(source->_12*source->_33-source->_13*source->_32);
    D3DVALUE mx13= fInvDeterm*(source->_12*source->_23-source->_13*source->_22);
    D3DVALUE mx21=-fInvDeterm*(source->_21*source->_33-source->_23*source->_31);
    D3DVALUE mx22= fInvDeterm*(source->_11*source->_33-source->_13*source->_31);
    D3DVALUE mx23=-fInvDeterm*(source->_11*source->_23-source->_13*source->_21);
    D3DVALUE mx31= fInvDeterm*(source->_21*source->_32-source->_22*source->_31);
    D3DVALUE mx32=-fInvDeterm*(source->_11*source->_32-source->_12*source->_31);
    D3DVALUE mx33= fInvDeterm*(source->_11*source->_22-source->_12*source->_21);

    R3DMATRIX dest;

    dest._11=mx11;
    dest._12=mx12;
    dest._13=mx13;
    dest._21=mx21;
    dest._22=mx22;
    dest._23=mx23;
    dest._31=mx31;
    dest._32=mx32;
    dest._33=mx33;

    sunTX=d3dl7Lights[LIGHT_SUNMOON].dvDirection.dvX;
    sunTY=d3dl7Lights[LIGHT_SUNMOON].dvDirection.dvY;
    sunTZ=d3dl7Lights[LIGHT_SUNMOON].dvDirection.dvZ;

    D3DVALUE tx,ty,tz;
    tx=(dest._11*sunTX+dest._21*sunTY+dest._31*sunTZ);
    ty=(dest._12*sunTX+dest._22*sunTY+dest._32*sunTZ);
    tz=(dest._13*sunTX+dest._23*sunTY+dest._33*sunTZ);
    sunTX=tx;
    sunTY=ty;
    sunTZ=tz;
    NormalizeVector( sunTX, sunTY, sunTZ );

#ifndef PER_POINT_SPECULAR
    R3DMATRIX* viewM = viewerMatrix+viewMatStackPos;
    D3DVECTOR tmpVec;
    tmpVec.x = -viewM->_13;
    tmpVec.y = -viewM->_23;
    tmpVec.z = -viewM->_33;


    halfSunEye.x = tmpVec.x*dest._11 + tmpVec.y*dest._21 + tmpVec.z*dest._31;
    halfSunEye.y = tmpVec.x*dest._12 + tmpVec.y*dest._22 + tmpVec.z*dest._32;
    halfSunEye.z = tmpVec.x*dest._13 + tmpVec.y*dest._23 + tmpVec.z*dest._33;

    //normalize - not needed, already normalized...
    halfSunEye.x+=sunTX;
    halfSunEye.y+=sunTY;
    halfSunEye.z+=sunTZ;

    NormalizeVector( halfSunEye );
#endif
#endif
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackProjectViewCone
//Author		Paul.
//Date			Wed 16 Feb 2000
//------------------------------------------------------------------------------
HRESULT Lib3D::BackProjectViewCone(COORDS3D* viewCone)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    R3DMATRIX objView;
    R3DMATRIX *proj;
    D3DVALUE *obj,*view;

    obj=(D3DVALUE*)(objectMatrix+objMatStackPos);
    view=(D3DVALUE*)(viewerMatrix+viewMatStackPos);
    //combine object and viewer matrices
    MatMulCEqAxB_AisRot_BisRot(((D3DVALUE*)&objView),obj,view);
    // Note:
    // objView._14, objView._24, objView._34 must be 0.0
    // and objView._44 must be 1.0 for the inverse
    // operation to succeed
    D3DVALUE fInvDeterm = 1.0f/(objView._11*(objView._22*objView._33-objView._23*objView._32)-
                                objView._12*(objView._21*objView._33-objView._23*objView._31)+
                                objView._13*(objView._21*objView._32-objView._22*objView._31));

    D3DVALUE mx11= fInvDeterm*(objView._22*objView._33-objView._23*objView._32);
    D3DVALUE mx12=-fInvDeterm*(objView._12*objView._33-objView._13*objView._32);
    D3DVALUE mx13= fInvDeterm*(objView._12*objView._23-objView._13*objView._22);
    D3DVALUE mx21=-fInvDeterm*(objView._21*objView._33-objView._23*objView._31);
    D3DVALUE mx22= fInvDeterm*(objView._11*objView._33-objView._13*objView._31);
    D3DVALUE mx23=-fInvDeterm*(objView._11*objView._23-objView._13*objView._21);
    D3DVALUE mx31= fInvDeterm*(objView._21*objView._32-objView._22*objView._31);
    D3DVALUE mx32=-fInvDeterm*(objView._11*objView._32-objView._12*objView._31);
    D3DVALUE mx33= fInvDeterm*(objView._11*objView._22-objView._12*objView._21);
    D3DVALUE mx41=-(objView._41*mx11+objView._42*mx21+objView._43*mx31);
    D3DVALUE mx42=-(objView._41*mx12+objView._42*mx22+objView._43*mx32);
    D3DVALUE mx43=-(objView._41*mx13+objView._42*mx23+objView._43*mx33);

    objView._11=mx11;
    objView._12=mx12;
    objView._13=mx13;
    objView._14=0.0f;
    objView._21=mx21;
    objView._22=mx22;
    objView._23=mx23;
    objView._24=0.0f;
    objView._31=mx31;
    objView._32=mx32;
    objView._33=mx33;
    objView._34=0.0f;
    objView._41=mx41;
    objView._42=mx42;
    objView._43=mx43;
    objView._44=1.0f;
    //view cone once transformed is a box with the following coordinates
    // (-1,1,0) , (1,1,0) , (1,-1,0) , (-1,-1,0)
    // (-1,1,1) , (1,1,1) , (1,-1,1) , (-1,-1,1)
    //use the current projection matrix to regenerate the unprojected coordinates
    D3DVALUE x[8]= {-1, 1, 1,-1,-1, 1, 1,-1};
    D3DVALUE y[8]= { 1, 1,-1,-1, 1, 1,-1,-1};
    D3DVALUE z[8]= { 0, 0, 0, 0, 1, 1, 1, 1};
    //				0  1  2  3  4  5  6  7

    // now using an oversised viewcone to produce bounding area
//	D3DVALUE x[8]={-1, 1, 1,-1,-1.01, 1.01, 1.01,-1.01};
//	D3DVALUE y[8]={ 1, 1,-1,-1, 1.01, 1.01,-1.01,-1.01};

    // hugely oversised near plane to ensure all of the nearer tiles are drawn!
//	D3DVALUE x[8]={-30000, 30000, 30000,-30000,-1.01, 1.01, 1.01,-1.01};
//	D3DVALUE y[8]={ 30000, 30000,-30000,-30000, 1.01, 1.01,-1.01,-1.01};
//	D3DVALUE z[8]={-0.00001,-0.00001,-0.00001,-0.00001,    1,    1,    1,    1};
//	D3DVALUE z[8]={-0.001,-0.001,-0.001,-0.001,    1,    1,    1,    1};




    proj=projectionMatrix+projMatStackPos;
    D3DVALUE fInvProj11=1.f/proj->_11;
    D3DVALUE fInvProj22=1.f/proj->_22;
    for (int i=7; i>=0; i--)
    {
        D3DVALUE tx,ty,tz;
        tz=nearZPlane+z[i]*(farZPlane-nearZPlane);
        tx=x[i]*tz*fInvProj11;
        ty=y[i]*tz*fInvProj22;
        //back transform to world coordinates
        x[i]=objView._11*tx+objView._21*ty+objView._31*tz+objView._41;
        y[i]=objView._12*tx+objView._22*ty+objView._32*tz+objView._42;
        z[i]=objView._13*tx+objView._23*ty+objView._33*tz+objView._43;
        FloatToInt(&viewCone[i].X,x[i]);
        FloatToInt(&viewCone[i].Y,y[i]);
        FloatToInt(&viewCone[i].Z,z[i]);
    }
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MatrixFlags
//Author		Paul.
//Date			Fri 26 Nov 1999
//
//------------------------------------------------------------------------------
//DeadCode JON 19Sep00 ULong Lib3D::MatrixFlags(R3DMATRIX* pMat)
//DeadCode JON 19Sep00 {
//DeadCode JON 19Sep00 	ULong flags,zbit,obit,*ptr;
//DeadCode JON 19Sep00 	flags=0;
//DeadCode JON 19Sep00 	ptr=(ULong*)pMat;
//DeadCode JON 19Sep00 	zbit=1;
//DeadCode JON 19Sep00 	obit=1<<16;
//DeadCode JON 19Sep00 	for (int i=16;i!=0;i--)
//DeadCode JON 19Sep00 	{
//DeadCode JON 19Sep00 		if (*ptr==0)				flags+=zbit;
//DeadCode JON 19Sep00 		else if (*ptr==FP_ONE_BITS)	flags+=obit;
//DeadCode JON 19Sep00 		zbit<<=1;
//DeadCode JON 19Sep00 		obit<<=1;
//DeadCode JON 19Sep00 		ptr++;
//DeadCode JON 19Sep00 	}
//DeadCode JON 19Sep00 	return flags;
//DeadCode JON 19Sep00 }
//DeadCode JON 7Sep00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 7Sep00 //Procedure		CombineTranspMat
//DeadCode JON 7Sep00 //Author		Jon
//DeadCode JON 7Sep00 //Date			Fri 11 Feb 2000
//DeadCode JON 7Sep00 //
//DeadCode JON 7Sep00 //------------------------------------------------------------------------------
//DeadCode JON 7Sep00 void Lib3D::CombineTranspMat()
//DeadCode JON 7Sep00 {
//DeadCode JON 7Sep00 	D3DVALUE *pA,*pB,*pM;
//DeadCode JON 7Sep00 	ULong x,*px;
//DeadCode JON 7Sep00 	SLong i,j,k;
//DeadCode JON 7Sep00 	for (x=16,px=(ULong*)&transpMatrix[++transMatPos];x!=0;*px++=ULong(0),x--)
//DeadCode JON 7Sep00 	{/*clear matrix*/}
//DeadCode JON 7Sep00
//DeadCode JON 7Sep00 	// build the combination of world and viewer matrix and store
//DeadCode JON 7Sep00 	pA=(D3DVALUE*)(objectMatrix+objMatStackPos);
//DeadCode JON 7Sep00 	pB=(D3DVALUE*)(viewerMatrix+viewMatStackPos);
//DeadCode JON 7Sep00 	pM=(D3DVALUE*)&transpMatrix[transMatPos];
//DeadCode JON 7Sep00
//DeadCode JON 7Sep00 	for (i=3;i>=0;i--)
//DeadCode JON 7Sep00 		for (j=3;j>=0;j--)
//DeadCode JON 7Sep00 			for (k=3;k>=0;k--)
//DeadCode JON 7Sep00 				pM[4*i+j]+=pA[4*i+k]*pB[4*k+j];
//DeadCode JON 7Sep00
//DeadCode JON 7Sep00
//DeadCode JON 7Sep00 	addNewTransMat=false;
//DeadCode JON 7Sep00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CombineMatrices
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
void Lib3D::CombineMatrices()
{
//DeadCode JON 7Sep00 	R3DMATRIX tmp;
    R3DMATRIX_VAL *pA,*pB;
    pA=(R3DMATRIX_VAL*)(objectMatrix+objMatStackPos);
    pB=(R3DMATRIX_VAL*)(viewerMatrix+viewMatStackPos);
    //DeadCode JON 7Sep00 	MatMulCEqAxB_AisRot_BisRot(((D3DVALUE*)&tmp),pA,pB);
    MatMulCEqAxB_AisRot_BisRot(((R3DMATRIX_VAL*)&objViewMatrix),pA,pB);
    clippingMatrix=*(projectionMatrix+projMatStackPos);
//DeadCode JON 7Sep00 	MatMulCEqAxB_AisRot_BisPerspective(((D3DVALUE*)&combinedMatrix),((D3DVALUE*)&tmp),((D3DVALUE*)&clippingMatrix));
    MatMulCEqAxB_AisRot_BisPerspective(((R3DMATRIX_VAL*)&combinedMatrix),((R3DMATRIX_VAL*)&objViewMatrix),((R3DMATRIX_VAL*)&clippingMatrix));
//DeadCode JON 21Aug00 	MatMulCEqAxB(((D3DVALUE*)&combinedMatrix),((D3DVALUE*)&tmp),((D3DVALUE*)&clippingMatrix));
//DeadCode JON 21Aug00 #pragma warnmsg ( "are you sure" )
//DeadCode JON 19Sep00 	combMatBits=MatrixFlags(&combinedMatrix);
    fCombineMatrices=false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TNLUploadMatrixies
//Author		Jon
//Date			Tue 8th Feb 2000
//
//				Uploads the world, view and transform matrixes onto a TNL card.
//------------------------------------------------------------------------------
HRESULT	Lib3D::TNLUploadMatrixes()
{
#ifndef NO_HARD_TNL
    // render anything in the poly list first - i.e anything to use the old matrixes
    if (texturedPolys!=NULL)	RenderTLPolyList(texturedPolys);
    texturedPolys=NULL;

    // upload the transform matrix
    if ( (lastError=pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_PROJECTION,projectionMatrix+projMatStackPos)) != S_OK )
        return lastError;

    // the view matrix
    if ( (lastError=pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_VIEW,viewerMatrix+viewMatStackPos)) != S_OK )
        return lastError;

    // the object matrix
    if ( (lastError=pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_WORLD,objectMatrix+objMatStackPos)) != S_OK )
        return lastError;

    fCombineMatrices=false;
    addNewTransMat=true;

#endif
    return lastError=S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VisibleCheck
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
//TempCode PD 18Feb100 	HRESULT Lib3D::VisibleCheck(D3DVECTOR* pos,ULong num,ULong* res)
//TempCode PD 18Feb100 	{
//TempCode PD 18Feb100 	if (fRecalcClipPlanes)
//TempCode PD 18Feb100 		CalculateClipPlanes();
//TempCode PD 18Feb100 	for (SLong i=SLong(num-1);i>=0;i--)
//TempCode PD 18Feb100 	{
//TempCode PD 18Feb100 		ULong clipCode;
//TempCode PD 18Feb100 		clipCode=clipPlanes[0].Inside(pos);
//TempCode PD 18Feb100 		clipCode<<=1;
//TempCode PD 18Feb100 		clipCode|=clipPlanes[1].Inside(pos);
//TempCode PD 18Feb100 		clipCode<<=1;
//TempCode PD 18Feb100 		clipCode|=clipPlanes[5].Inside(pos);
//TempCode PD 18Feb100 		clipCode<<=1;
//TempCode PD 18Feb100 		clipCode|=clipPlanes[4].Inside(pos);
//TempCode PD 18Feb100 		clipCode<<=1;
//TempCode PD 18Feb100 		clipCode|=clipPlanes[2].Inside(pos);
//TempCode PD 18Feb100 		clipCode<<=1;
//TempCode PD 18Feb100 		clipCode|=clipPlanes[3].Inside(pos);
//TempCode PD 18Feb100 		clipCode<<=1;
//TempCode PD 18Feb100 		pos++;
//TempCode PD 18Feb100 		*res++=clipCode;
//TempCode PD 18Feb100 	}
//TempCode PD 18Feb100 	return S_OK;
//TempCode PD 18Feb100 }
HRESULT Lib3D::VisibleCheck(D3DVECTOR* pos,ULong num,ULong* res)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if (fCombineMatrices) CombineMatrices();

    for (SLong i=SLong(num-1); i>=0; i--)
    {
        R3DVERTEX v;
        D3DTLVERTEX tv;
        v.x=pos->x;
        v.y=pos->y;
        v.z=pos->z;
        Transform(&v,&tv,&combinedMatrix);
        *res=ClipCodeFBLRTB(&tv);
        pos++;
        res++;
    }
    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VisibleCheck
//Author		Jon.
//Date			Fri 5 May 2000
//
//------------------------------------------------------------------------------
HRESULT Lib3D::VisibleCheck(DoPointStruc* v,ULong num,ULong* res)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if (fCombineMatrices) CombineMatrices();

    for (SLong i=SLong(num-1); i>=0; i--)
    {
        D3DTLVERTEX tv;
//DEADCODE JON 5/24/00 		Transform((D3DVERTEX*)v,&tv,&combinedMatrix);
        Transform(&v->getR3DVert(),&tv,&combinedMatrix);
        *res=ClipCodeFBLRTB(&tv);
        v++;
        res++;
    }
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VisibleCheck
//Author		Paul.
//Date			Mon 13 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::VisibleCheck(D3DVECTOR* pos,D3DVALUE* rad,ULong num,ULong* res)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if (fCombineMatrices) CombineMatrices();

    for (SLong i=SLong(num-1); i>=0; i--)
    {
        D3DTLVERTEX v,v2;
        D3DVALUE rhw;
        ULong outcode;
        v.rhw=combinedMatrix._14*pos->x+combinedMatrix._24*pos->y+combinedMatrix._34*pos->z+combinedMatrix._44;
        v.sx=combinedMatrix._11*pos->x+combinedMatrix._21*pos->y+combinedMatrix._31*pos->z+combinedMatrix._41;
        v.sy=combinedMatrix._12*pos->x+combinedMatrix._22*pos->y+combinedMatrix._32*pos->z+combinedMatrix._42;
        v.sz=combinedMatrix._13*pos->x+combinedMatrix._23*pos->y+combinedMatrix._33*pos->z+combinedMatrix._43;
        outcode=ClipCodeFBLRTB(&v);
        *res=outcode;
        if (0!=outcode)
        {
            //only gets here if the sphere center is outside
            //the viewing frustrum
            R3DMATRIX radMatrix;
            ULong newcode;
            radMatrix=combinedMatrix;
            radMatrix._11*=*rad;
            radMatrix._21*=*rad;
            radMatrix._31*=*rad;
            radMatrix._12*=*rad;
            radMatrix._22*=*rad;
            radMatrix._32*=*rad;
            radMatrix._13*=*rad;
            radMatrix._23*=*rad;
            radMatrix._33*=*rad;
            radMatrix._14*=*rad;
            radMatrix._24*=*rad;
            radMatrix._34*=*rad;

            //6 points on the spheres circumference to check
            v2=v;
            v2.sx+=radMatrix._11;
            v2.sy+=radMatrix._12;
            v2.sz+=radMatrix._13;
            v2.rhw+=radMatrix._14;
            newcode=ClipCodeFBLRTB(&v2);
            outcode&=newcode;
            if (0!=outcode)
            {
                v2=v;
                v2.sx-=radMatrix._11;
                v2.sy-=radMatrix._12;
                v2.sz-=radMatrix._13;
                v2.rhw-=radMatrix._14;
                newcode=ClipCodeFBLRTB(&v2);
                outcode&=newcode;
//DeadCode JON 15Aug00 				if (0!=outcode)
                {
                    v2=v;
                    v2.sx+=radMatrix._21;
                    v2.sy+=radMatrix._22;
                    v2.sz+=radMatrix._23;
                    v2.rhw+=radMatrix._24;
                    newcode=ClipCodeFBLRTB(&v2);
                    outcode&=newcode;
                    if (0!=outcode)
                    {
                        v2=v;
                        v2.sx-=radMatrix._21;
                        v2.sy-=radMatrix._22;
                        v2.sz-=radMatrix._23;
                        v2.rhw-=radMatrix._24;
                        newcode=ClipCodeFBLRTB(&v2);
                        outcode&=newcode;
                        if (0!=outcode)
                        {
                            v2=v;
                            v2.sx+=radMatrix._31;
                            v2.sy+=radMatrix._32;
                            v2.sz+=radMatrix._33;
                            v2.rhw+=radMatrix._34;
                            newcode=ClipCodeFBLRTB(&v2);
                            outcode&=newcode;
                            if (0!=outcode)
                            {
                                v2=v;
                                v2.sx-=radMatrix._31;
                                v2.sy-=radMatrix._32;
                                v2.sz-=radMatrix._33;
                                v2.rhw-=radMatrix._34;
                                newcode=ClipCodeFBLRTB(&v2);
                                outcode&=newcode;
//DeadCode RJS 20Mar00 								*res=outcode;
                            }
                        }
                    }
                }
            }

//If any one of the edges are visible, we need to know...
            *res=outcode;										//RJS 20Mar00
        }
        pos++;
        rad++;
        res++;
    }
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetProjectionMatrix
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetProjectionMatrix(const Angles& fov,const D3DVALUE& aspect,const D3DVALUE& Zni,const D3DVALUE& Zfi,const bool noFog)
{
    return _SetProjectionMatrix( fov, aspect, Zni, Zfi, noFog );
}

// use current screens aspect ratio
HRESULT Lib3D::SetProjectionMatrix(const Angles& fov,const D3DVALUE& Zni,const D3DVALUE& Zfi,const bool noFog)
{
    return _SetProjectionMatrix( fov, aspectRatio, Zni, Zfi, noFog );
}

inline HRESULT Lib3D::_SetProjectionMatrix(const Angles& fov,const D3DVALUE& aspect,const D3DVALUE& Zni,const D3DVALUE& Zfi,const bool noFog/* = false*/)
{

    R3DMATRIX_VAL Zn = Zni;
    R3DMATRIX_VAL Zf = Zfi;

    zNearClip = 0.0;		// the z at the near clip plane				//JON 29Aug00

    // the clip distances for the proj matrix
    matrixNearPlane=
        nearZPlane=Zn;
    matrixFarPlane=
        farZPlane=Zf;
    zFactor=1.f/farZPlane;

    lastError=S_OK;

    R3DMATRIX *pMat;
//DeadCode JON 21Aug00 	{
//DeadCode JON 21Aug00 		D3DVALUE Q,w,h;
//DeadCode JON 21Aug00 		D3DVALUE sin_fov,cos_fov;
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 		SineCosine(fov>>1,&sin_fov,&cos_fov);
//DeadCode JON 21Aug00 		w=D3DVALUE(cos_fov/sin_fov);
//DeadCode JON 21Aug00 		h=4.f/3.f*w;
//DeadCode JON 21Aug00 		Q=Zf/(Zf-Zn);
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 		D3DVALUE B = (Zn)/( (Zn/Zf)-1.0 );
//DeadCode JON 21Aug00 		D3DVALUE A = -B/Zn;
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 //		const D3DVALUE gMin[] = { 0.0,0.002,0.004 };
//DeadCode JON 21Aug00 //		const D3DVALUE gMax[] = { 0.096,0.098,1.0 };
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 		const D3DVALUE gMin[] = { 0.004,0.002,0.0 };
//DeadCode JON 21Aug00 		const D3DVALUE gMax[] = { 1.0,0.098,0.096 };
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 //TempCode JON 21Aug00 		const D3DVALUE gMin[] = { 0.3,0.3,0.3 };
//DeadCode JON 21Aug00 //TempCode JON 21Aug00 		const D3DVALUE gMax[] = { 0.8,0.8,0.8 };
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 		int oldpos = projMatStackPos;
//DeadCode JON 21Aug00 		int stackoffset = projMatStackPos%MATRIX_STACK_SIZE;
//DeadCode JON 21Aug00 		for ( int i = 0; i<NUM_Z_LAYERS; i++ )
//DeadCode JON 21Aug00 		{
//DeadCode JON 21Aug00 			projMatStackPos = stackoffset+MATRIX_STACK_SIZE*i;
//DeadCode JON 21Aug00 			pMat=projectionMatrix+projMatStackPos;
//DeadCode JON 21Aug00 			*pMat=IDENTITY;
//DeadCode JON 21Aug00 			pMat->_11=w;
//DeadCode JON 21Aug00 			pMat->_22=h;
//DeadCode JON 21Aug00 			pMat->_43=-Zn*Q;
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 			D3DVALUE A1, B1;
//DeadCode JON 21Aug00 			B1 = (gMax[i]-gMin[i])/( (1.0/Zf) - (1.0/Zn) );
//DeadCode JON 21Aug00 			A1 = (gMin[i]-(B1/Zn));
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 			pMat->_33=A1;
//DeadCode JON 21Aug00 			pMat->_43=B1;
//DeadCode JON 21Aug00 			pMat->_34=1.0;
//DeadCode JON 21Aug00 			pMat->_44=0.0;
//DeadCode JON 21Aug00
//DeadCode JON 21Aug00 			projMatBits[projMatStackPos]=MatrixFlags(pMat);
//DeadCode JON 21Aug00 		}
//DeadCode JON 21Aug00 		projMatStackPos = oldpos;
//DeadCode JON 21Aug00 	}
    pMat = projectionMatrix+projMatStackPos;
    if ( prefZType == D3DZB_USEW )
    {

        R3DMATRIX_VAL Q,w,h;
        D3DVALUE sin_fov,cos_fov;

        SineCosine(fov>>1,&sin_fov,&cos_fov);
        w=R3DMATRIX_VAL(cos_fov/sin_fov);
//DeadCode JON 6Oct00 		h=4.f/3.f*w;
        h=aspect*w;
        Q=Zf/(Zf-Zn);
        *pMat=IDENTITY;
        pMat->_11=w;
        pMat->_22=h;
        pMat->_33=Q;
        pMat->_34=1.f;
        pMat->_43=-Zn*Q;
        pMat->_44=0.f;
        zFarClip = 1.0-zSMALL;
    }
    else
    {
        R3DMATRIX_VAL w,h;
        D3DVALUE sin_fov,cos_fov;

        SineCosine(fov>>1,&sin_fov,&cos_fov);
        w=R3DMATRIX_VAL(cos_fov/sin_fov);
//DeadCode JON 6Oct00 		h=4.f/3.f*w;
        h=aspect*w;
//		Q=Zf/(Zf-Zn);
        *pMat=IDENTITY;
        pMat->_11=w;
        pMat->_22=h;
//		pMat->_43=-Zn*Q;

//DeadCode JON 28Sep00 		const R3DMATRIX_VAL M = 1.0-/*SPolygon::*/(zFiddle*1.1); // the maximum z value generated..
        const R3DMATRIX_VAL M = 1.0-((zFiddle*D3DVALUE(NUM_Z_LAYERS-1))+(zFiddle/3.0f)); // the maximum z value generated..
        R3DMATRIX_VAL B = (Zn*M)/( (Zn/Zf)-1.0 );
        R3DMATRIX_VAL A = -B/Zn;

        pMat->_33=A;
        pMat->_43=B;
        pMat->_34=1.0;
        pMat->_44=0.0;

        zFarClip = pMat->_33*farZPlane + pMat->_43;		// the z at the far clip plane					//JON 29Aug00
    }
    backProjectX = -1.0/pMat->_11;
    backProjectY = -1.0/pMat->_22;

//DeadCode JON 19Sep00 	projMatBits[projMatStackPos]=MatrixFlags(pMat);

    fCombineMatrices=true;
    if ((flags&F_INSCENE)!=0 && !noFog )
    {
        D3DVALUE curFogStart,curFogEnd;
        curFogStart=Zf*fogStart;
        curFogEnd=Zf*fogEnd;
#ifdef	_WBUFFERTEST_
        curFogStart /= 0.005;
        curFogEnd /= 0.005;
#endif
        if ( flags&F_VERTEXFOG &&
                ( curFogStart != lastFogStart || curFogEnd != lastFogEnd )
           )
        {
            fogMul=1023.0/Zf;												//JON 2Aug00

            lastFogStart = fogStart;
            lastFogEnd = curFogEnd;
            FillFogTable(fogStart,fogEnd);
        }
        else
        {
            // upload the projection matrix for non tnl cards as they may need this for fogging
            D3DMATRIX projMat = *pMat;
            lastError=pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_PROJECTION,&projMat);
//DeadCode JON 22Aug00 		if (selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGTABLE)

//DeadCode JON 22Aug00 		if ( !(flags&F_VERTEXFOG) )
//DeadCode JON 22Aug00 		{
//DeadCode JON 24Aug00 		static D3DVALUE lastFogStart = -10000.0;
//DeadCode JON 24Aug00 		static D3DVALUE lastFogEnd = -10000.0;

            if ( curFogStart != lastFogStart || curFogEnd != lastFogEnd )
            {
                lastFogStart = fogStart;
                lastFogEnd = curFogEnd;
                ChangeRenderStateFog( curFogStart, curFogEnd );
            }
//DeadCode JON 22Aug00 		}
        }
    }
    return lastError;
}
HRESULT Lib3D::SetFogColour(const ULong& fogColour)
{
    gFogColour=fogColour;
    return S_OK;
}
HRESULT Lib3D::SetFontColour(const ULong& fontColour)
{
    gFontColour=fontColour;
    SetColAlpha( gFontColour, globAlpha );
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAmbientLighting
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetAmbientLighting(LIGHTINGDESC lightDesc)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

//DeadCode JON 27Jul00 	lightModeFlag=(~lightModeFlag)&LIGHTMODE_FLAG;
    NextLmFlag();

#ifndef	NO_HARD_TNL
    if (flags&Flags(F_TNL+F_TNL_EMULATION))
    {
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_AMBIENT,lightDesc.ambientRGB);
        return lastError;
    }
#endif
    if (gLightingDesc.lowRGB!=lightDesc.lowRGB ||
            gLightingDesc.highRGB!=lightDesc.highRGB)
    {
        //construct a table of rgb values from lowlight to highlight in 256 steps
        SLong lr,lg,lb;
        SLong hr,hg,hb;
        SLong dr,dg,db;
        ULong startlight;
        ULong tLowRGB = lightDesc.lowRGB;
        ULong tHighRGB = lightDesc.highRGB;
//DEADCODE JON 3/30/00 		startlight=lightDesc.lowRGB;
        lb=(tLowRGB&0xFF)<<16;
        tLowRGB>>=8;
        lg=(tLowRGB&0xFF)<<16;
        tLowRGB>>=8;
        lr=(tLowRGB&0xFF)<<16;
        hb=(tHighRGB&0xFF)<<16;
        tHighRGB>>=8;
        hg=(tHighRGB&0xFF)<<16;
        tHighRGB>>=8;
        hr=(tHighRGB&0xFF)<<16;
        dr=(hr-lr)>>8;
        dg=(hg-lg)>>8;
        db=(hb-lb)>>8;
        for (int i=0; i<256; i++)
        {
            lightingTable[i]=RGBMake(UByte(lr>>16),UByte(lg>>16),UByte(lb>>16));
//DEADCODE JON 3/30/00 			lightingTable[i]=startlight;
            lr+=dr;
            lg+=dg;
            lb+=db;
//DEADCODE JON 3/30/00 			startlight=RGBMake(UByte(lr>>16),UByte(lg>>16),UByte(lb>>16));
        }
    }
    if (gLightingDesc.lowDot!=lightDesc.lowDot ||
            gLightingDesc.highDot!=lightDesc.highDot)
    {
        D3DVALUE delta(lightDesc.highDot-lightDesc.lowDot);
        gLightBase=-lightDesc.lowDot;
        gLightScale=255.f/delta;
    }
//DeadCode JON 11Sep00 	if (gLightingDesc.specularPower!=lightDesc.specularPower)
    if ( gLightingDesc.specularRGB.all != lightDesc.specularRGB.all )
    {
        specularTable[0] = 0x00000000;
//DeadCode JON 11Sep00 		float redMax = 255.f;
//DeadCode JON 11Sep00 		float greenMax = 224.f;
//DeadCode JON 11Sep00 		float blueMax = 192.f;
        float redMax = lightDesc.specularRGB.red;
        float greenMax = lightDesc.specularRGB.green;
        float blueMax = lightDesc.specularRGB.blue;
        specularTable[255]=0;
//DeadCode JON 11Sep00 		specularTable[255].red=redMax;
//DeadCode JON 11Sep00 		specularTable[255].green=greenMax;
//DeadCode JON 11Sep00 		specularTable[255].blue=blueMax;
        specularTable[255]= lightDesc.specularRGB;
        for ( int i = 1; i < 255; i++ )
        {
            const float specularPower = 64.f;

            D3DVALUE thisVal = pow( D3DVALUE(i)*(1.f/255.f), specularPower);
            UByte colR = UByte( F2UL_Round( thisVal*redMax ) );
            UByte colG = UByte( F2UL_Round( thisVal*greenMax ) );
            UByte colB = UByte( F2UL_Round( thisVal*blueMax ) );
            specularTable[i]=0;
            specularTable[i].red=colR;
            specularTable[i].green=colG;
            specularTable[i].blue=colB;
        }
    }
    gLightingDesc=lightDesc;
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetObjectLighting
//Author		Paul.
//Date			Wed 10 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetObjectLighting(LIGHTFLAG& lf)
{
#ifndef NDEBUG
    if ( lf>LF_SPECULAR )
        INT3;
#endif

    if ( lf>masterLightFlag )
        lf = masterLightFlag;

    if ( lf!=lightflag )
        NextLmFlag();
    else
        return S_OK;

    LIGHTFLAG old=lightflag;
    lightflag=lf;
    lf=old;

    if ( lightflag == LF_SPECULAR
#ifdef LIGHT_ALL_SPECULAR
            || lightflag == LF_LIGHTING
#endif
       )
        hLastMaterial.materialFlags |= IS_SPECULAR;
    else
        hLastMaterial.materialFlags &= (~IS_SPECULAR);

    return S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCurrentLighting
//Author		Jon.
//Date			Wed 16 Feb 2000
//
//------------------------------------------------------------------------------
//TempCode JON 4Oct00 HRESULT Lib3D::SetCurrentLighting(const LIGHTFLAG& lf = LF_DUMMY )
//TempCode JON 4Oct00 {
//TempCode JON 4Oct00 	static LIGHTFLAG cur;
//TempCode JON 4Oct00 	if ( lf != LF_DUMMY )
//TempCode JON 4Oct00 		cur = lf;
//TempCode JON 4Oct00
//TempCode JON 4Oct00 	lastError=DDERR_GENERIC;
//TempCode JON 4Oct00 #ifndef NO_TNL_LIGHTING
//TempCode JON 4Oct00 	switch (cur)
//TempCode JON 4Oct00 	{
//TempCode JON 4Oct00 	case LF_AMBIENT:
//TempCode JON 4Oct00 #endif
//TempCode JON 4Oct00 		if ((lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_LIGHTING,FALSE))==D3D_OK &&
//TempCode JON 4Oct00 			(lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE))==D3D_OK &&
//TempCode JON 4Oct00 			(lastError=pD3DDEV7->LightEnable(0,FALSE))==D3D_OK)
//TempCode JON 4Oct00 			return lastError=S_OK;
//TempCode JON 4Oct00 #ifndef NO_TNL_LIGHTING
//TempCode JON 4Oct00 		break;
//TempCode JON 4Oct00 	case LF_LIGHTING:
//TempCode JON 4Oct00 		if ((lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE))==D3D_OK &&
//TempCode JON 4Oct00 			(lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE))==D3D_OK &&
//TempCode JON 4Oct00 			(lastError=pD3DDEV7->LightEnable(0,TRUE))==D3D_OK)
//TempCode JON 4Oct00 			return lastError=S_OK;
//TempCode JON 4Oct00 		break;
//TempCode JON 4Oct00 	case LF_SPECULAR:
//TempCode JON 4Oct00 		if ((lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE))==D3D_OK &&
//TempCode JON 4Oct00 			(lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE))==D3D_OK &&
//TempCode JON 4Oct00 			(lastError=pD3DDEV7->LightEnable(0,TRUE))==D3D_OK)
//TempCode JON 4Oct00 			return lastError=S_OK;
//TempCode JON 4Oct00 		break;
//TempCode JON 4Oct00 	default:
//TempCode JON 4Oct00 		lastError=DDERR_INVALIDPARAMS;
//TempCode JON 4Oct00 	}
//TempCode JON 4Oct00 #endif
//TempCode JON 4Oct00 	// only gets here if error
//TempCode JON 4Oct00 	CloseDown();
//TempCode JON 4Oct00 	return lastError;
//TempCode JON 4Oct00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLightVector
//Author		Paul.
//Date			Tue 23 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetLightVector(D3DVALUE dvX,D3DVALUE dvY,D3DVALUE dvZ)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    NextLmFlag();

    D3DLIGHT7 *pLight;
    D3DCOLORVALUE white= {1.f,1.f,1.f,1.f};
    D3DVALUE mag;

    //needs to be normalised for SW lighting
#ifndef NO_HARD_TNL
    if ((flags&Flags(F_TNL+F_TNL_EMULATION))==0)
#endif
    {
        updateLightVecs=true;
        mag=dvX*dvX+dvY*dvY+dvZ*dvZ;
        mag=1.f/FastSqrt(mag);
        dvX*=mag;
        dvY*=mag;
        dvZ*=mag;
    }
    pLight=d3dl7Lights+LIGHT_SUNMOON;
    ZeroMemory(pLight,sizeof(D3DLIGHT7));
    pLight->dltType=D3DLIGHT_DIRECTIONAL;
    pLight->dcvDiffuse=
        pLight->dcvAmbient=
            pLight->dcvSpecular=white;
    pLight->dvDirection.dvX=dvX;
    pLight->dvDirection.dvY=dvY;
    pLight->dvDirection.dvZ=dvZ;
#ifndef NO_HARD_TNL
    if (flags&Flags(F_TNL+F_TNL_EMULATION))
    {
        lastError=pD3DDEV7->SetLight(DWORD(LIGHT_SUNMOON),pLight);
        return lastError=pD3DDEV7->LightEnable(0,TRUE);
    }
#endif
    return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGlobal
//Author		Paul.
//Date			Mon 22 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetGlobal(const TOGGLES& tog,const ULong val)
{
    ULong localVal=val;
    return SetGlobal(tog,&localVal);
}
HRESULT Lib3D::SetGlobal(const TOGGLES& tog,ULong* val)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    lastError =  S_OK;
    switch (tog)
    {
    case TOGGLE_TRANSPARENT_ZBIAS:
    {
//DeadCode JON 3Oct00 		if ( prefZType == D3DZB_USEW )
//DeadCode JON 3Oct00 			return S_OK;

        ULong oldV = tZBias;
        tZBias = *val;
        *val = oldV;
        tZBias_f=-D3DVALUE(tZBias);
    }
    break;
    case TOGGLE_TEXTURE_ZBIAS:
    {
        if ( prefZType == D3DZB_USEW )
        {
            if ( *val == FORCE_TO_BACK_Z )
            {
                zBias = FORCE_TO_BACK_Z;
                *val = NUM_Z_LAYERS;
            }
            else
            {
                zBias = NUM_Z_LAYERS;
            }
            return S_OK;
        }
#ifndef NDEBUG
        if ( *val >= NUM_Z_LAYERS )
        {
            INT3;
            lastError = DDERR_INVALIDPARAMS;
        }
        else
#endif
        {
//DeadCode JON 21Aug00 ULong oldV = texturedPolysP - texturedPolys;
            ULong oldV = zBias;
            zBias = *val;
//DeadCode JON 21Aug00 			texturedPolysP = texturedPolys+zBias;
//DeadCode JON 21Aug00 			textPolyVCntP = textPolyVCnt+zBias;
//DeadCode JON 21Aug00 			projMatStackPos=(projMatStackPos%MATRIX_STACK_SIZE)+MATRIX_STACK_SIZE*(*val);
//DeadCode JON 21Aug00 			fCombineMatrices=true;
            *val = oldV;
        }
    }
    break;
    case TOGGLE_GLOBALALPHA:
    {
        UByte oldA;
//DeadCode JON 14Jun00 		oldA = 0xFF-globAlpha;
//DeadCode JON 14Jun00 		globAlpha = 0xFF-UByte( *val );
        oldA = globAlpha;
        globAlpha = UByte( *val );
        *val=ULong(oldA);
        SetColAlpha( gFontColour, globAlpha );
        lastError=DD_OK;
        break;
    }
    case TOGGLE_GLOBAL2DZDEPTH:
    {
        if ( *val == 0 )
            NOP;
        ULong oldVal = zBuffer2d;//ULong(zDepth2d/zSMALL);
        zBuffer2d=*val;
        zDepth2d=D3DVALUE((*val))*zSMALL;
        *val = oldVal;
        break;
    }
    case TOGGLE_TEXTURE_QUALITY:// only use in cases of extreme need, otherwise give hint
    {
        ULong oldVal = ULong( textureQuality );
        textureQuality=HINTS( *val );
        *val = oldVal;
        break;
    }
    default:
        lastError = DDERR_INVALIDPARAMS;
        break;
    }
    return lastError;
#endif
}

HRESULT Lib3D::IncGlobal(const TOGGLES& tog)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    lastError =  S_OK;
    switch (tog)
    {
    case TOGGLE_TEXTURE_ZBIAS:
    {
        if ( prefZType == D3DZB_USEW )
            return S_OK;
#ifndef NDEBUG
        ULong oldV = zBias;
        if ( ++oldV >= NUM_Z_LAYERS )
        {
            INT3;
            lastError = DDERR_INVALIDPARAMS;
        }
        else
#endif
        {
//DeadCode JON 21Aug00 			texturedPolysP++;
//DeadCode JON 21Aug00 			textPolyVCntP++;
            zBias++;
            //DeadCode JON 21Aug00 			projMatStackPos+=MATRIX_STACK_SIZE;
//DeadCode JON 21Aug00 			fCombineMatrices=true;
        }
    }
    break;
    default:
        lastError = DDERR_INVALIDPARAMS;
        break;
    }
    return lastError;
#endif
}

HRESULT Lib3D::DecGlobal(const TOGGLES& tog)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    lastError =  S_OK;
    switch (tog)
    {
    case TOGGLE_TEXTURE_ZBIAS:
    {
        if ( prefZType == D3DZB_USEW )
            return S_OK;
#ifndef NDEBUG
        ULong oldV = zBias;
        if ( --oldV >= NUM_Z_LAYERS )
        {
            INT3;
            lastError = DDERR_INVALIDPARAMS;
        }
        else
#endif
        {
//DeadCode JON 21Aug00 			texturedPolysP--;
//DeadCode JON 21Aug00 			textPolyVCntP--;
            zBias--;
//DeadCode JON 21Aug00 			projMatStackPos-=MATRIX_STACK_SIZE;
//DeadCode JON 21Aug00 			fCombineMatrices=true;
        }
    }
    break;
    default:
        lastError = DDERR_INVALIDPARAMS;
        break;
    }
    return lastError;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateTextureMap
//Author		Paul.
//Date			Mon 22 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::CreateTextureMap(MAPDESC *pMapDesc,LPDIRECTDRAWSURFACE7 &pddsTexture,SLong textureStage)
{
    return _CreateTextureMap( pMapDesc, pddsTexture, textureStage );
}

HRESULT Lib3D::UploadAsDitherTexture( MAPDESC *pmap )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if (pmap->hTextureMap==0 || pmap->hTextureMap==NULL)
    {
        SLong j;
        for (j=MAX_TEXTURES-1; j>0 && textureTable[j]!=NULL; j--);
        if (!j)
        {
            CloseDown();
            return DDERR_GENERIC;
        }
        pmap->hTextureMap=HTEXTUREMAP(j);
        return _CreateTextureMap(pmap,textureTable[pmap->hTextureMap],1,true);
    }
    return S_OK;
#endif
}

HRESULT Lib3D::UploadAsMipMapLevel( MAPDESC *destination, MAPDESC *source, int level )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if (destination->hTextureMap==0 || destination->hTextureMap==NULL)
    {
        return DDERR_GENERIC;// there is no trexture uploaded to have the mip map stomped...
    }

    LPDIRECTDRAWSURFACE7 pCur = textureTable[destination->hTextureMap];
    LPDIRECTDRAWSURFACE7 pDst;

    DDSCAPS2 ddscaps;
    ddscaps.dwCaps=DDSCAPS_MIPMAP;
    ddscaps.dwCaps2=0L;
    ddscaps.dwCaps3=0L;
    ddscaps.dwCaps4=0L;

    level--;

    pCur->AddRef();
    for (	pCur->GetAttachedSurface(&ddscaps,&pDst);
            level--;
            pCur->Release(),pCur=pDst,pCur->GetAttachedSurface(&ddscaps,&pDst))
    {
        if ( pDst == NULL )
            return DDERR_GENERIC;
    }
    pCur->Release();

    return CopyMapToSurface( source, pDst );
#endif
}

inline HRESULT Lib3D::CopyMapToSurface( MAPDESC *pMapDesc,LPDIRECTDRAWSURFACE7 &targetSurface )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    LPDDPIXELFORMAT pPixelFmt;
    LPDDPIXELFORMAT pTargetFmt;
    LPVOID			*pPalette;
    LPVOID			pTmpPal=NULL;
    RECT			srcRect,dstRect;
    SWord			scaleX,scaleY;
    ULong			stepX,stepY;
    ULong			scaledW,scaledH;
    DDSURFACEDESC2	ddsd;

    ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
    lastError=targetSurface->GetSurfaceDesc(&ddsd);
    if (lastError!=DD_OK)
    {
        CloseDown();
        return lastError;
    }

    if (pMapDesc->alpha!=NULL)
    {
        pPixelFmt=texFmt+TF_TRNSINIT;
        pTargetFmt=texFmt+TF_TRNS;
        pPalette=pMapDesc->palette?(LPVOID*)0xFFFFFFFF:trnsPalLookUp+pMapDesc->paletteindex;
    }
    else if (pMapDesc->isMasked)
    {
        pPixelFmt=texFmt+TF_MASKINIT;
        pTargetFmt=texFmt+TF_MASK;
        pPalette=pMapDesc->palette?(LPVOID*)0xFFFFFFFF:maskPalLookUp+pMapDesc->paletteindex;
    }
    else
    {
        pPixelFmt=texFmt+TF_NORMINIT;
        pTargetFmt=texFmt+TF_NORM;
        pPalette=pMapDesc->palette?(LPVOID*)0xFFFFFFFF:normPalLookUp+pMapDesc->paletteindex;
    }


    scaledW=pMapDesc->w;
    scaledH=pMapDesc->h;
	scaleX = scaleY = 0;
    while ( scaledW > ddsd.dwWidth )
    {
        scaledW>>=1;
        scaleX++;
    }
    while ( scaledH > ddsd.dwHeight )
    {
        scaledH>>=1;
        scaleY++;
    }


    stepX=1<<scaleX;
    stepY=pMapDesc->w*(1<<scaleY);

    if (pPalette==LPVOID(0xFFFFFFFF))
        pPalette=&pTmpPal;
    if (pPalette[0]==NULL)
    {
        if ((pPixelFmt->dwFlags&DDPF_PALETTEINDEXED8)!=0)
        {
            LPDIRECTDRAWPALETTE pDDPal;
            PALETTEENTRY palEntry[256],*pDst=palEntry+255;
            UByte *pSrc;
            pSrc=(pPalette==&pTmpPal)?pMapDesc->palette:paletteTable+(3*255)+(256*3)*pMapDesc->paletteindex;
            for (int i=256; i>0; pDst--,pSrc-=3,i--)
            {
                pDst->peRed=pSrc[0];
                pDst->peGreen=pSrc[1];
                pDst->peBlue=pSrc[2];
                pDst->peFlags=0;
            }
            if ((lastError=pDD7->CreatePalette(DDPCAPS_8BIT|DDPCAPS_ALLOW256,palEntry,&pDDPal,NULL))!=DD_OK)
            {
                CloseDown();
                return lastError;
            }
            pPalette[0]=(void*)pDDPal;
        }
        else if (pPixelFmt->dwRGBBitCount==16)
        {
            SWord redShift,greenShift,blueShift;
            UByte redBits,greenBits,blueBits;
            UWord alphaVal;
            UWord *pDst;
            UByte *pSrc;
            pPalette[0]=(LPVOID)(pDst=new UWord[256]);
            if (pDst==NULL)
                return DDERR_GENERIC;

#ifndef _NOBBLE_BRIGHTER
            pSrc=(pPalette==&pTmpPal)?pMapDesc->palette+(3*255):paletteTable+(3*255)+(256*3)*pMapDesc->paletteindex;
#else
            float scaleVal;
            if (pPalette==&pTmpPal)
            {
                pSrc=pMapDesc->palette+(3*255);
                scaleVal=1.25f;
            }
            else
            {
                pSrc=paletteTable+(3*255)+(256*3)*pMapDesc->paletteindex;
                if( pMapDesc->paletteindex == 0 )
                    scaleVal=1.0f;
                else
                    scaleVal=1.25f;
            }
#endif

            redShift=greenShift=blueShift=0;
            redBits=greenBits=blueBits=8;
            alphaVal=UWord(pPixelFmt->dwRBitMask);
            while ((alphaVal&1)==0)
            {
                alphaVal>>=1;
                redShift++;
            }
            while ((alphaVal&1)!=0)
            {
                alphaVal>>=1;
                redBits--;
            }
            alphaVal=UWord(pPixelFmt->dwGBitMask);
            while ((alphaVal&1)==0)
            {
                alphaVal>>=1;
                greenShift++;
            }
            while ((alphaVal&1)!=0)
            {
                alphaVal>>=1;
                greenBits--;
            }
            alphaVal=UWord(pPixelFmt->dwBBitMask);
            while ((alphaVal&1)==0)
            {
                alphaVal>>=1;
                blueShift++;
            }
            while ((alphaVal&1)!=0)
            {
                alphaVal>>=1;
                blueBits--;
            }
            alphaVal=UWord(pPixelFmt->dwRGBAlphaBitMask);
            for (int i=256; i>0; pSrc-=3,i--)
            {
#ifndef _NOBBLE_BRIGHTER
                pDst[i-1]=(UWord(pSrc[0]>>redBits)<<redShift)+
                      (UWord(pSrc[1]>>greenBits)<<greenShift)+
                      (UWord(pSrc[2]>>blueBits)<<blueShift)+
                      alphaVal;
#else
                float rf=float(pSrc[0])*scaleVal;
                rf=(rf<255.f)?rf:255.f;
                float gf=float(pSrc[1])*scaleVal;
                gf=(gf<255.f)?gf:255.f;
                float bf=float(pSrc[2])*scaleVal;
                bf=(bf<255.f)?bf:255.f;
                pDst[i-1]=(UWord(UByte(rf)>>redBits)<<redShift)+
                      (UWord(UByte(gf)>>greenBits)<<greenShift)+
                      (UWord(UByte(bf)>>blueBits)<<blueShift)+
                      alphaVal;
#endif
            }

            pDst[254]&=~alphaVal;
        }
        else return DDERR_GENERIC;
    }

    if ((pPixelFmt->dwFlags&DDPF_PALETTEINDEXED8)!=0)
        if ((lastError=targetSurface->SetPalette(LPDIRECTDRAWPALETTE(pPalette[0])))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
    if (flags&F_PAGELOCK)
        lastError=targetSurface->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WRITEONLY,NULL);
    else
        lastError=targetSurface->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WRITEONLY|DDLOCK_NOSYSLOCK,NULL);
    if (lastError!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    if ((pPixelFmt->dwFlags&DDPF_PALETTEINDEXED8)!=0)
    {
        UByte *pDst=(UByte*)ddsd.lpSurface;
        UByte *pSrc=pMapDesc->body;
        for (int i=scaledH; i>0; i--)
        {
            UByte *pNxt=pDst+ddsd.lPitch;
            UByte *pSr2=pSrc+stepY;
            for (int j=scaledW; j>0; *pDst++=*pSrc,pSrc+=stepX,j--);
            pDst=pNxt;
            pSrc=pSr2;
        }
    }
    else if (pMapDesc->alpha==NULL)
    {
        UWord *pDst=(UWord*)ddsd.lpSurface;
        UWord *pPal=(UWord*)pPalette[0];
        UByte *pSrc=pMapDesc->body;
        for (int i=scaledH; i>0; i--)
        {
            UWord *pNxt=(UWord*)(ULong(pDst)+ddsd.lPitch);
            UByte *pSr2=pSrc+stepY;
            for (int j=scaledW; j>0; *pDst++=pPal[*pSrc],pSrc+=stepX,j--);
            pDst=pNxt;
            pSrc=pSr2;
        }
    }
    else if (pMapDesc->body==NULL)
    {
        SWord alphaShift=0;
        UByte alphaBits=8;
        UWord alphaSMsk=UWord(pPixelFmt->dwRGBAlphaBitMask),alphaDMsk=alphaSMsk;
        while ((alphaSMsk&1)==0)
        {
            alphaSMsk>>=1;
            alphaShift++;
        }
        while ((alphaSMsk&1)!=0)
        {
            alphaSMsk>>=1;
            alphaBits--;
        }
        alphaSMsk=~alphaDMsk;
        UWord *pDst=(UWord*)ddsd.lpSurface;
        UByte *pTrn=pMapDesc->alpha;
        for (int i=scaledH; i>0; i--)
        {
            UWord *pNxt=(UWord*)(ULong(pDst)+ddsd.lPitch);
            UByte *pTr2=pTrn+stepY;
            for (int j=scaledW; j>0; pTrn+=stepX,j--)
                *pDst++=alphaSMsk+(UWord(pTrn[0]>>alphaBits)<<alphaShift);
            pDst=pNxt;
            pTrn=pTr2;
        }
    }
    else
    {
        SWord alphaShift=0;
        UByte alphaBits=8;
        UWord alphaSMsk=UWord(pPixelFmt->dwRGBAlphaBitMask),alphaDMsk=alphaSMsk;
        while ((alphaSMsk&1)==0)
        {
            alphaSMsk>>=1;
            alphaShift++;
        }
        while ((alphaSMsk&1)!=0)
        {
            alphaSMsk>>=1;
            alphaBits--;
        }
        alphaSMsk=~alphaDMsk;
        UWord *pDst=(UWord*)ddsd.lpSurface;
        UWord *pPal=(UWord*)pPalette[0];
        UByte *pSrc=pMapDesc->body;
        UByte *pTrn=pMapDesc->alpha;
        for (int i=scaledH; i>0; i--)
        {
            UWord *pNxt=(UWord*)(ULong(pDst)+ddsd.lPitch);
            UByte *pSr2=pSrc+stepY;
            UByte *pTr2=pTrn+stepY;
            for (int j=scaledW; j>0; pSrc+=stepX,pTrn+=stepX,j--)
                *pDst++=(pPal[*pSrc]&alphaSMsk)+(UWord(pTrn[0]>>alphaBits)<<alphaShift);
            pDst=pNxt;
            pSrc=pSr2;
            pTrn=pTr2;
        }
    }
    if ((lastError=targetSurface->Unlock(NULL))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    return S_OK;
#endif
}

inline HRESULT Lib3D::_CreateTextureMap(MAPDESC *pMapDesc,LPDIRECTDRAWSURFACE7 &pddsTexture,SLong textureStage,bool isDither)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    LPDIRECTDRAWSURFACE7 pDDSTemp;
    LPDIRECTDRAWSURFACE7 pDDSMipLevel;
    LPDIRECTDRAWSURFACE7 pDDSTarget;
    DDSURFACEDESC2	ddsd;
    LPDDPIXELFORMAT pPixelFmt;
    LPDDPIXELFORMAT pTargetFmt;
    LPVOID			*pPalette;
    LPVOID			pTmpPal=NULL;
    RECT			srcRect,dstRect;
    SWord			scaleX,scaleY;
    ULong			stepX,stepY;
    ULong			scaledW,scaledH;
    bool isMasked = false;

#ifndef NDEBUG
    if ( pddsTexture!=NULL )
        INT3;
#endif

    if (pMapDesc->alpha!=NULL)
    {
        pPixelFmt=texFmt+TF_TRNSINIT;
        pTargetFmt=texFmt+TF_TRNS;
        pPalette=pMapDesc->palette?(LPVOID*)0xFFFFFFFF:trnsPalLookUp+pMapDesc->paletteindex;
    }
    else if (pMapDesc->isMasked)
    {
        INT3;
        isMasked = true;
        pPixelFmt=texFmt+TF_MASKINIT;
        pTargetFmt=texFmt+TF_MASK;
        pPalette=pMapDesc->palette?(LPVOID*)0xFFFFFFFF:maskPalLookUp+pMapDesc->paletteindex;
    }
    else
    {
        pPixelFmt=texFmt+TF_NORMINIT;
        pTargetFmt=texFmt+TF_NORM;
        pPalette=pMapDesc->palette?(LPVOID*)0xFFFFFFFF:normPalLookUp+pMapDesc->paletteindex;
    }
    if (textureQuality==HINT_EIGHTH_RES_TEXTURE)		scaleX=scaleY=3;
    else if (textureQuality==HINT_QUARTER_RES_TEXTURE)	scaleX=scaleY=2;
    else if (textureQuality==HINT_HALF_RES_TEXTURE)		scaleX=scaleY=1;
    else												scaleX=scaleY=0;

    scaledW=pMapDesc->w;
    scaledH=pMapDesc->h;
	//assert(scaledW != 512); //x0r
    if (scaledW!=scaledH &&
            (selectedDevice.dpcTriCaps.dwTextureCaps&D3DPTEXTURECAPS_SQUAREONLY)!=0)
    {
        if (scaledW>scaledH)
            for (ULong localW=scaledW; localW!=scaledH; localW>>=1,scaleX++);
        else
            for (ULong localH=scaledH; localH!=scaledW; localH>>=1,scaleY++);
    }
    if (scaleX!=0) scaledW>>=scaleX;
    if (scaleY!=0) scaledH>>=scaleY;

    while (scaledW>selectedDevice.dwMaxTextureWidth || scaledH>selectedDevice.dwMaxTextureHeight)
    {
        scaleX++;
        scaleY++;
        scaledW>>=1;
        scaledH>>=1;
    }
    if (scaledW==0 ||
            scaledH==0 ||
            scaledW<selectedDevice.dwMinTextureWidth ||
            scaledH<selectedDevice.dwMinTextureHeight)
    {
        return DDERR_GENERIC;
    }

    stepX=1<<scaleX;
    stepY=pMapDesc->w*(1<<scaleY);

    if (pPalette==LPVOID(0xFFFFFFFF))
        pPalette=&pTmpPal;
    if (pPalette[0]==NULL)
    {
        if ((pPixelFmt->dwFlags&DDPF_PALETTEINDEXED8)!=0)
        {
            LPDIRECTDRAWPALETTE pDDPal;
            PALETTEENTRY palEntry[256],*pDst=palEntry+255;
            UByte *pSrc;
            pSrc=(pPalette==&pTmpPal)?pMapDesc->palette:paletteTable+(3*255)+(256*3)*pMapDesc->paletteindex;
            for (int i=256; i>0; pDst--,pSrc-=3,i--)
            {
                pDst->peRed=pSrc[0];
                pDst->peGreen=pSrc[1];
                pDst->peBlue=pSrc[2];
                pDst->peFlags=0;
            }
            if ((lastError=pDD7->CreatePalette(DDPCAPS_8BIT|DDPCAPS_ALLOW256,palEntry,&pDDPal,NULL))!=DD_OK)
            {
                CloseDown();
                return lastError;
            }
            pPalette[0]=(void*)pDDPal;
        }
        else if (pPixelFmt->dwRGBBitCount==16)
        {
            SWord redShift,greenShift,blueShift;
            UByte redBits,greenBits,blueBits;
            UWord alphaVal;
            UWord *pDst;
            UByte *pSrc;
            pPalette[0]=(LPVOID)(pDst=new UWord[256]);
            if (pDst==NULL)
                return DDERR_GENERIC;

#ifndef _NOBBLE_BRIGHTER
            pSrc=(pPalette==&pTmpPal)?pMapDesc->palette+(3*255):paletteTable+(3*255)+(256*3)*pMapDesc->paletteindex;
#else
            float scaleVal;
            if (pPalette==&pTmpPal)
            {
                pSrc=pMapDesc->palette+(3*255);
                scaleVal=1.25f;
            }
            else
            {
                pSrc=paletteTable+(3*255)+(256*3)*pMapDesc->paletteindex;
                if( pMapDesc->paletteindex == 0 )
                    scaleVal=1.0f;
                else
                    scaleVal=1.25f;
            }
#endif

            redShift=greenShift=blueShift=0;
            redBits=greenBits=blueBits=8;
            alphaVal=UWord(pPixelFmt->dwRBitMask);
            while ((alphaVal&1)==0)
            {
                alphaVal>>=1;
                redShift++;
            }
            while ((alphaVal&1)!=0)
            {
                alphaVal>>=1;
                redBits--;
            }
            alphaVal=UWord(pPixelFmt->dwGBitMask);
            while ((alphaVal&1)==0)
            {
                alphaVal>>=1;
                greenShift++;
            }
            while ((alphaVal&1)!=0)
            {
                alphaVal>>=1;
                greenBits--;
            }
            alphaVal=UWord(pPixelFmt->dwBBitMask);
            while ((alphaVal&1)==0)
            {
                alphaVal>>=1;
                blueShift++;
            }
            while ((alphaVal&1)!=0)
            {
                alphaVal>>=1;
                blueBits--;
            }
            alphaVal=UWord(pPixelFmt->dwRGBAlphaBitMask);
            for (int i=256; i>0; pSrc-=3,i--)
            {
#ifndef _NOBBLE_BRIGHTER
                pDst[i-1]=(UWord(pSrc[0]>>redBits)<<redShift)+
                      (UWord(pSrc[1]>>greenBits)<<greenShift)+
                      (UWord(pSrc[2]>>blueBits)<<blueShift)+
                      alphaVal;
#else
                float rf=float(pSrc[0])*scaleVal;
                rf=(rf<255.f)?rf:255.f;
                float gf=float(pSrc[1])*scaleVal;
                gf=(gf<255.f)?gf:255.f;
                float bf=float(pSrc[2])*scaleVal;
                bf=(bf<255.f)?bf:255.f;
                pDst[i-1]=(UWord(UByte(rf)>>redBits)<<redShift)+
                      (UWord(UByte(gf)>>greenBits)<<greenShift)+
                      (UWord(UByte(bf)>>blueBits)<<blueShift)+
                      alphaVal;
#endif
            }

            pDst[254]&=~alphaVal;
        }
        else return DDERR_GENERIC;
    }
    ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
    ddsd.dwWidth=scaledW;
    ddsd.dwHeight=scaledH;
    ddsd.ddpfPixelFormat=*pPixelFmt;
    ddsd.ddsCaps.dwCaps=DDSCAPS_SYSTEMMEMORY|DDSCAPS_TEXTURE;
    if ((lastError=pDD7->CreateSurface(&ddsd,&pDDSTemp,NULL))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    if ((pPixelFmt->dwFlags&DDPF_PALETTEINDEXED8)!=0)
        if ((lastError=pDDSTemp->SetPalette(LPDIRECTDRAWPALETTE(pPalette[0])))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
    ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize=sizeof(ddsd);
    if (flags&F_PAGELOCK)
        lastError=pDDSTemp->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WRITEONLY,NULL);
    else
        lastError=pDDSTemp->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WRITEONLY|DDLOCK_NOSYSLOCK,NULL);
    if (lastError!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    if ((pPixelFmt->dwFlags&DDPF_PALETTEINDEXED8)!=0)
    {
        UByte *pDst=(UByte*)ddsd.lpSurface;
        UByte *pSrc=pMapDesc->body;
        for (int i=scaledH; i>0; i--)
        {
            UByte *pNxt=pDst+ddsd.lPitch;
            UByte *pSr2=pSrc+stepY;
            for (int j=scaledW; j>0; *pDst++=*pSrc,pSrc+=stepX,j--);
            pDst=pNxt;
            pSrc=pSr2;
        }
    }
    else if (pMapDesc->alpha==NULL)
    {
        UWord *pDst=(UWord*)ddsd.lpSurface;
        UWord *pPal=(UWord*)pPalette[0];
        UByte *pSrc=pMapDesc->body;
        for (int i=scaledH; i>0; i--)
        {
            UWord *pNxt=(UWord*)(ULong(pDst)+ddsd.lPitch);
            UByte *pSr2=pSrc+stepY;
            for (int j=scaledW; j>0; *pDst++=pPal[*pSrc],pSrc+=stepX,j--);
            pDst=pNxt;
            pSrc=pSr2;
        }
    }
    else if (pMapDesc->body==NULL)
    {
        SWord alphaShift=0;
        UByte alphaBits=8;
        UWord alphaSMsk=UWord(pPixelFmt->dwRGBAlphaBitMask),alphaDMsk=alphaSMsk;
        while ((alphaSMsk&1)==0)
        {
            alphaSMsk>>=1;
            alphaShift++;
        }
        while ((alphaSMsk&1)!=0)
        {
            alphaSMsk>>=1;
            alphaBits--;
        }
        alphaSMsk=~alphaDMsk;
        UWord *pDst=(UWord*)ddsd.lpSurface;
        UByte *pTrn=pMapDesc->alpha;
        for (int i=scaledH; i>0; i--)
        {
            UWord *pNxt=(UWord*)(ULong(pDst)+ddsd.lPitch);
            UByte *pTr2=pTrn+stepY;
            for (int j=scaledW; j>0; pTrn+=stepX,j--)
                *pDst++=alphaSMsk+(UWord(pTrn[0]>>alphaBits)<<alphaShift);
            pDst=pNxt;
            pTrn=pTr2;
        }
    }
    else
    {
        SWord alphaShift=0;
        UByte alphaBits=8;
        UWord alphaSMsk=UWord(pPixelFmt->dwRGBAlphaBitMask),alphaDMsk=alphaSMsk;
        while ((alphaSMsk&1)==0)
        {
            alphaSMsk>>=1;
            alphaShift++;
        }
        while ((alphaSMsk&1)!=0)
        {
            alphaSMsk>>=1;
            alphaBits--;
        }
        alphaSMsk=~alphaDMsk;
        UWord *pDst=(UWord*)ddsd.lpSurface;
        UWord *pPal=(UWord*)pPalette[0];
        UByte *pSrc=pMapDesc->body;
        UByte *pTrn=pMapDesc->alpha;
        for (int i=scaledH; i>0; i--)
        {
            UWord *pNxt=(UWord*)(ULong(pDst)+ddsd.lPitch);
            UByte *pSr2=pSrc+stepY;
            UByte *pTr2=pTrn+stepY;
            for (int j=scaledW; j>0; pSrc+=stepX,pTrn+=stepX,j--)
                *pDst++=(pPal[*pSrc]&alphaSMsk)+(UWord(pTrn[0]>>alphaBits)<<alphaShift);
            pDst=pNxt;
            pSrc=pSr2;
            pTrn=pTr2;
        }
    }
    if ((lastError=pDDSTemp->Unlock(NULL))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS|DDSD_MIPMAPCOUNT|DDSD_TEXTURESTAGE;//|DDSD_CKSRCBLT;
    ddsd.dwWidth=scaledW;
    ddsd.dwHeight=scaledH;
    ddsd.ddpfPixelFormat=*pTargetFmt;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;

	SLong mipMapCount;
    if (textureBlending==HINT_TRILINEAR && !isMasked )
    {
        mipMapCount=5;
        if (scaledW>256)
        {
            for (ULong sw=scaledW; sw!=256; sw>>=1,mipMapCount++)
            {
                // calc the number of extra mipmap levels 
            }
        }
        else  if (scaledW<256 && !isDither)
        {
            for (ULong sw=scaledW; sw!=256; sw<<=1,mipMapCount--)
            {
                // calc the number of mipmap levels not required
            }
            if ( mipMapCount <= 0 )
                mipMapCount = 1;
        }
    }
    else 
        mipMapCount=1;

    ddsd.ddsCaps.dwCaps2=DDSCAPS2_D3DTEXTUREMANAGE;

    ddsd.dwMipMapCount=mipMapCount;
    ddsd.dwTextureStage=textureStage;
    if ((lastError=pDD7->CreateSurface(&ddsd,&pDDSTarget,NULL))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    if ((pTargetFmt->dwFlags&DDPF_PALETTEINDEXED8)!=0)
        if ((lastError=pDDSTarget->SetPalette(LPDIRECTDRAWPALETTE(pPalette[0])))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }

    srcRect.top=0L;
    srcRect.left=0L;
    srcRect.bottom=scaledH-1;
    srcRect.right=scaledW-1;

    dstRect=srcRect;

    if (flags&F_PAGELOCK)
        pDDSTemp->PageLock(0);

    if ((lastError=pDDSTarget->BltFast(0,0,pDDSTemp,NULL,DDBLTFAST_WAIT|DDBLTFAST_NOCOLORKEY))!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    DDSCAPS2 ddscaps;
    ddscaps.dwCaps=DDSCAPS_MIPMAP;
    ddscaps.dwCaps2=0L;
    ddscaps.dwCaps3=0L;
    ddscaps.dwCaps4=0L;

    pddsTexture=pDDSTarget;

    if ( !isDither )
    {
        UpdateMipMaps( pddsTexture );
    }
    else
    {
        // make plain black lower level mips
        DDBLTFX bltFx;

        ZeroMemory(&bltFx, sizeof(bltFx));
        bltFx.dwSize = sizeof(DDBLTFX);

//		bltFx.dwFillColor = 0; // always should be black anyhow

        LPDIRECTDRAWSURFACE7 pdst;
        LPDIRECTDRAWSURFACE7 psrc = pddsTexture;

        DDSCAPS2 ddscaps;
        ddscaps.dwCaps=DDSCAPS_MIPMAP;
        ddscaps.dwCaps2=0L;
        ddscaps.dwCaps3=0L;
        ddscaps.dwCaps4=0L;

        int curr = 0;
        const int BLANK_AT = 3;

        psrc->AddRef();
        for (	psrc->GetAttachedSurface(&ddscaps,&pdst);
                pdst!=NULL;
                psrc->Release(),psrc=pdst,psrc->GetAttachedSurface(&ddscaps,&pdst))
        {
            if ( curr++ >= BLANK_AT )
            {
                lastError=pdst->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&bltFx);
//				char* ErrorDesc;
//				GetErrorDesc( lastError, ErrorDesc );
            }
            else
            {
#ifndef SOFT_MIPMAP
                lastError=pdst->Blt(NULL,psrc,NULL,DDBLT_WAIT,NULL);
#else
                MakeMipLevel(psrc,pdst);
#endif
            }
        }
        psrc->Release();

    }

//DeadCode JON 11Jul00 	for (	/*pDDSTarget->AddRef(),*/lastError=pDDSTarget->GetAttachedSurface(&ddscaps,&pDDSMipLevel);
//DeadCode JON 11Jul00 			lastError==DD_OK && pDDSMipLevel!=NULL;
//DeadCode JON 11Jul00 			/*pDDSTarget->Release(),*/pDDSTarget=pDDSMipLevel,lastError=pDDSTarget->GetAttachedSurface(&ddscaps,&pDDSMipLevel) )
//DeadCode JON 11Jul00 		{
//DeadCode JON 11Jul00 #ifndef SOFT_MIPMAP
//DeadCode JON 11Jul00 			pDDSMipLevel->Blt(NULL,pDDSTarget,NULL,DDBLT_WAIT|DDBLT_ASYNC,NULL);
//DeadCode JON 11Jul00 #else
//DeadCode JON 11Jul00 			MakeMipLevel(pDDSTarget,pDDSMipLevel);
//DeadCode JON 11Jul00 #endif
//DeadCode JON 11Jul00 		}

    if (flags&F_PAGELOCK)
        pDDSTemp->PageUnlock(0);

    pDDSTemp->Release();

//DeadCode JON 07Mar100 	pddsTexture=pDDSTarget;

    if (pPalette==&pTmpPal && (pPixelFmt->dwFlags&DDPF_PALETTEINDEXED8)==0)
        delete[](UWord*)pTmpPal;

    return DD_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnloadTexture
//Author		Jon.
//Date			Tue 8 Feb 2000
//
//------------------------------------------------------------------------------
HRESULT Lib3D::UnloadTexture( MAPDESC* map )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if (map->hTextureMap==NULL)
        return S_OK;
    if ( textureTable[map->hTextureMap] != NULL )
    {
        textureTable[map->hTextureMap]->Release();
        textureTable[map->hTextureMap] = NULL;
        map->hTextureMap=NULL;
    }
    else
        map->hTextureMap=NULL;

    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMaterial
//Author		Paul.
//Date			Wed 24 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetMaterial(const HMATERIAL& hMaterial)
{
    if (SameMaterial(hLastMaterial,hMaterial))
        return DD_OK;

    hLastMaterial=hMaterial;

#ifdef _ONLY_ONE_LANSDCAPE_TEXTURE
    if ( landscapeTexture == NULL &&
            ( hMaterial.p[0] && hMaterial.p[0]->w == hMaterial.p[0]->h && hMaterial.p[0]->h == 256 &&
              hMaterial.p[0]->alpha == NULL ) )
    {
        landscapeTexture = hMaterial.p[0];
    }
#endif

//	IS_LAND = 1,
//	IS_DOUBLE_TEXTURED = 1<<1,
//	IS_PLAIN = 1<<2,
//	IS_ALPHA = 1<<3,
//	IS_ALPHA_SOLID = 1<<4,
//	IS_SPECULAR = 1<<5

    hLastMaterial.materialFlags = 0;
    if ( hLastMaterial.f == 0 )
    {
        hLastMaterial.materialFlags = IS_PLAIN;
    }
    else
    {
        // textured - how many textures?
        if ( hLastMaterial.f != 1 )
        {
            // double textured
            hLastMaterial.materialFlags = IS_DOUBLE_TEXTURED;
        }
        // note that the actual is alpha stuff is set later (i.e in the render poly list...)
        if ( hLastMaterial.p[0]->blendType == BLEND_SRCALPHA_DESTSOLID )
        {
            hLastMaterial.materialFlags += IS_ALPHA_SOLID;
        }
    }

    if ( lightflag == LF_SPECULAR
#ifdef LIGHT_ALL_SPECULAR
            || lightflag == LF_LIGHTING
#endif
       )
        hLastMaterial.materialFlags |= IS_SPECULAR;

    if (	hLastMaterial.uniqueTextID == 0 ||
            ( hLastMaterial.p[1] && hLastMaterial.p[1]->hTextureMap == 0 )
       )
    {
        // we need to upload the texture... - must be a none landscape, none plain
        for (int i=flags&F_CANTBLENDTEXTURES?0:hLastMaterial.f-1; i>=0; i--)
        {
            if (hLastMaterial.p[i]!=NULL && hLastMaterial.p[i]->hTextureMap==0 || textureTable[hLastMaterial.p[i]->hTextureMap]==NULL)
            {
                int j;
                for (j=MAX_TEXTURES-1; j>0 && textureTable[j]!=NULL; j--)
                {
                    /* search for next free texture slot */
                }
                if (!j)
                {
                    INT3; // run out of textures!!!
                    CloseDown();
                    return DDERR_GENERIC;
                }
                hLastMaterial.p[i]->hTextureMap=HTEXTUREMAP(j);
                if ((lastError=CreateTextureMap(hLastMaterial.p[i],textureTable[hLastMaterial.p[i]->hTextureMap],i))!=D3D_OK)
                {
                    INT3;
                    CloseDown();
                    return lastError;
                }
            } // end of is that texture blank
        } // end of loop possible  texture stages

//		if ( hLastMaterial.p[1] )
//			hLastMaterial.uniqueTextID = hLastMaterial.p[0]->hTextureMap + ((hLastMaterial.p[1]->hTextureMap<<11)&TIT_MASK_SECONDARY);
//	else
        hLastMaterial.uniqueTextID = hLastMaterial.p[0]->hTextureMap;
    }

    curMatTextureTypeFlags = globTextureTypeFlags|hLastMaterial.f;

//TEMPCODE JIM 23/05/00 	if ( hLastMaterial.f != 0 )
//TEMPCODE JIM 23/05/00 		if ( (int)hLastMaterial.p[0] == 0 )
//TEMPCODE JIM 23/05/00 			INT3;

//DEADCODE JON 5/10/00 	if (hMaterial.f==0x00)	//plain color material
//DEADCODE JON 5/10/00 	{
//DEADCODE JON 5/10/00 //DEADCODE JON 5/10/00 		hLastMaterial.mathandle=hLastMaterial.c;
//DEADCODE JON 5/10/00 	}
//DEADCODE JON 5/10/00 	else
//DEADCODE JON 5/10/00 	{
//DEADCODE JON 5/10/00 		//check to see whether this material contains textures that need to be uploaded
//DEADCODE JON 5/10/00 		for (int i=flags&F_CANTBLENDTEXTURES?0:hMaterial.f-1;i>=0;i--)
//DEADCODE JON 5/10/00 		{
//DEADCODE JON 5/10/00 			if (hMaterial.p[i]!=NULL && hMaterial.p[i]->hTextureMap==0 || textureTable[hMaterial.p[i]->hTextureMap]==NULL)
//DEADCODE JON 5/10/00 			{
//DEADCODE JON 5/10/00 				//for non-texture manage version -
//DEADCODE JON 5/10/00 				// check how much video memory is available
//DEADCODE JON 5/10/00 				// if < some figure then clear out the current set after
//DEADCODE JON 5/10/00 				// rendering any polys that are already buffered
//DEADCODE JON 5/10/00 /*/deadcode				if (flags&F_CANTMANAGETEXTURES)
//DEADCODE JON 5/10/00 				{
//DEADCODE JON 5/10/00 					DDSCAPS2 ddscaps;
//DEADCODE JON 5/10/00 					ZeroMemory(&ddscaps,sizeof(ddscaps));
//DEADCODE JON 5/10/00 					ddscaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
//DEADCODE JON 5/10/00 //deadcode					DWORD avail;
//DEADCODE JON 5/10/00 //deadcode					DWORD total;
//DEADCODE JON 5/10/00 //deadcode					pDD7->GetAvailableVidMem(&ddscaps,&total,&avail);
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 //deadcode					char debStr[256];
//DEADCODE JON 5/10/00 //deadcode					sprintf(debStr,"TMEM=%dbytes\tFMEM=%dbytes\n",total,avail);
//DEADCODE JON 5/10/00 //deadcode					OutputDebugString(debStr);
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 					g_usedRAM+=EstimateTextureRAM(hMaterial.p[i]);
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 					if (gFreeRAM-g_usedRAM<65536*4)
//DEADCODE JON 5/10/00 					{
//DEADCODE JON 5/10/00 						g_usedRAM=EstimateTextureRAM(hMaterial.p[i]);
//DEADCODE JON 5/10/00 						if (texturedPolys!=NULL)
//DEADCODE JON 5/10/00 							RenderPolyList(texturedPolys);
//DEADCODE JON 5/10/00 						if (transparentPolys!=NULL)
//DEADCODE JON 5/10/00 							RenderTPolyList(transparentPolys);
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 						texturedPolys=NULL;
//DEADCODE JON 5/10/00 						transparentPolys=NULL;
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 						pD3DDEV7->EndScene();
//DEADCODE JON 5/10/00 						pD3DDEV7->BeginScene();
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 //						if (textureBlending==HINT_TRILINEAR)
//DEADCODE JON 5/10/00 //							textureBlending=HINT_BILINEAR;
//DEADCODE JON 5/10/00 //						else if (textureQuality==HINT_FULL_RES_TEXTURE)
//DEADCODE JON 5/10/00 //							textureQuality=HINT_HALF_RES_TEXTURE;
//DEADCODE JON 5/10/00 //						else if (textureQuality==HINT_HALF_RES_TEXTURE)
//DEADCODE JON 5/10/00 //							textureQuality=HINT_QUARTER_RES_TEXTURE;
//DEADCODE JON 5/10/00 //						else if (textureQuality==HINT_QUARTER_RES_TEXTURE)
//DEADCODE JON 5/10/00 //							textureQuality=HINT_EIGHTH_RES_TEXTURE;
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 						for (int i=MAX_TEXTURES-1;i>=0;i--)
//DEADCODE JON 5/10/00 							if (textureTable[i]!=NULL)
//DEADCODE JON 5/10/00 							{
//DEADCODE JON 5/10/00 								textureTable[i]->Release();
//DEADCODE JON 5/10/00 								textureTable[i]=NULL;
//DEADCODE JON 5/10/00 							}
//DEADCODE JON 5/10/00 					}
//DEADCODE JON 5/10/00 				}
//DEADCODE JON 5/10/00 //deadcode*/
//DEADCODE JON 5/10/00 				for (int j=MAX_TEXTURES-1;j>0 && textureTable[j]!=NULL;j--)
//DEADCODE JON 5/10/00 				{/* search for next free texture slot */}
//DEADCODE JON 5/10/00 				if (!j)
//DEADCODE JON 5/10/00 				{
//DEADCODE JON 5/10/00 					INT3; // run out of textures!!!
//DEADCODE JON 5/10/00 					CloseDown();
//DEADCODE JON 5/10/00 					return DDERR_GENERIC;
//DEADCODE JON 5/10/00 				}
//DEADCODE JON 5/10/00 				hMaterial.p[i]->hTextureMap=HTEXTUREMAP(j);
//DEADCODE JON 5/10/00 				if ((hr=CreateTextureMap(hMaterial.p[i],textureTable[hMaterial.p[i]->hTextureMap],i))!=D3D_OK)
//DEADCODE JON 5/10/00 				{
//DEADCODE JON 5/10/00 					CloseDown();
//DEADCODE JON 5/10/00 					return hr;
//DEADCODE JON 5/10/00 				}
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 			} // end of is that texture blank
//DEADCODE JON 5/10/00 		}
//DEADCODE JON 5/10/00
//DEADCODE JON 5/10/00 //DEADCODE JON 5/10/00 		hLastMaterial.mathandle=hLastMaterial.p[0]->hTextureMap;
//DEADCODE JON 5/10/00 	}
    return DD_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateTexture // not used?
//Author		Paul.
//Date			Mon 29 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::CreateTexture(MAPDESC* pMapDesc,const TCFLAGS& tcFlag)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    DDSURFACEDESC2 ddsd;
    HTEXTUREMAP hTextureMap;
    LPDIRECTDRAWSURFACE7 pDDS7;

    hTextureMap=pMapDesc->hTextureMap;

    if (hTextureMap==0 || textureTable[hTextureMap]==NULL)
    {
        SLong i;
        for (i=MAX_TEXTURES-1; i>256 && textureTable[i]!=NULL; i--);
        if (i==256)
        {
            CloseDown();
            return DDERR_GENERIC;
        }
        pMapDesc->hTextureMap=hTextureMap=HTEXTUREMAP(i);

        if (pMapDesc->w!=pMapDesc->h &&
                (selectedDevice.dpcTriCaps.dwTextureCaps&D3DPTEXTURECAPS_SQUAREONLY)!=0)
            pMapDesc->w=pMapDesc->h=MAX(pMapDesc->w,pMapDesc->h);

        pMapDesc->w=
            MIN(MAX(pMapDesc->w,selectedDevice.dwMinTextureWidth),selectedDevice.dwMaxTextureWidth);
        pMapDesc->h=
            MIN(MAX(pMapDesc->h,selectedDevice.dwMinTextureHeight),selectedDevice.dwMaxTextureHeight);

        ZeroMemory(&ddsd,sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
        ddsd.dwWidth=pMapDesc->w;
        ddsd.dwHeight=pMapDesc->h;
        if ((tcFlag&TC_RENDERTARGET)!=0)
        {
            ddsd.ddpfPixelFormat=texFmt[TF_LANDINIT];
            if ((flags&F_TEXTURECANBERENDERTARGET)!=0)
                ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_3DDEVICE|DDSCAPS_VIDEOMEMORY;
            else
                ddsd.ddsCaps.dwCaps=DDSCAPS_3DDEVICE|DDSCAPS_SYSTEMMEMORY;
        }
        else
        {
            ddsd.ddpfPixelFormat=texFmt[TF_LAND];
            ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE;
//deadcode			if (flags&F_CANTMANAGETEXTURES)	ddsd.ddsCaps.dwCaps|=DDSCAPS_LOCALVIDMEM|DDSCAPS_VIDEOMEMORY;
//deadcode			else
            ddsd.ddsCaps.dwCaps2=DDSCAPS2_D3DTEXTUREMANAGE;

        }
        if ((lastError=pDD7->CreateSurface(&ddsd,&pDDS7,0))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
        textureTable[hTextureMap]=pDDS7;
    }
    return S_OK;
#endif
}

ULong countRefs( IUnknown* com )
{
    ULong tVal = 0;
    if ( com != NULL )
    {
        com->AddRef();
        tVal = com->Release();
    }
    return tVal;
}

inline HRESULT Lib3D::UpdateMipMaps( LPDIRECTDRAWSURFACE7 psrc )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    LPDIRECTDRAWSURFACE7 pdst;

    DDSCAPS2 ddscaps;
    ddscaps.dwCaps=DDSCAPS_MIPMAP;
    ddscaps.dwCaps2=0L;
    ddscaps.dwCaps3=0L;
    ddscaps.dwCaps4=0L;

    psrc->AddRef();
    for (	psrc->GetAttachedSurface(&ddscaps,&pdst);
            pdst!=NULL;
            psrc->Release(),psrc=pdst,psrc->GetAttachedSurface(&ddscaps,&pdst))
    {
#ifndef SOFT_MIPMAP
        lastError=pdst->Blt(NULL,psrc,NULL,DDBLT_WAIT,NULL);
//		GetErrorDesc( hr, errDesc );
#else
        MakeMipLevel(psrc,pdst);
#endif
    }
    psrc->Release();

//TempCode JON 26Jul00 	countRefs( psrc );

    return lastError;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UploadTexture
//Author		Paul.
//Date			Fri 3 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::UploadTexture(/*const UWord& ht*/)
{
#ifdef _NO_DYNAMIC_TEXT_UPLOAD
    return S_OK;
#endif
    LPDIRECTDRAWSURFACE7 psrc,pdst;
    DDSURFACEDESC2 ddsd;
    RECT* outRect;

//TempCode JON 2Nov00 	RECT tmpRect;
    switch (hCurrentRenderTarget.getType())
    {
    case RENDERTARGET_PRIMARY:
        return DDERR_GENERIC;
    case RENDERTARGET_MIRROR:
//		return DDERR_GENERIC;
        if ( flags&F_TEXTURECANBERENDERTARGET )
            return S_OK; // no need to upload - already there
//#pragma warnmsg ( "when happy, change the imap coords" )
        outRect = &mirrorRect;
//TempCode JON 2Nov00 	    outRect = &tmpRect;
//TempCode JON 2Nov00 		tmpRect.left = mirrorRect.right;
//TempCode JON 2Nov00 		tmpRect.right = mirrorRect.left;
//TempCode JON 2Nov00 		tmpRect.top = mirrorRect.top;
//TempCode JON 2Nov00 		tmpRect.bottom = mirrorRect.bottom;

        psrc=pDDS7MirrorRT;
        pdst=pDDS7Mirror;//textureTable[mirrorTexture.p[0]->hTextureMap];		//JON 3Jul00
        break;
    case RENDERTARGET_LANDSCAPE:
#ifndef NDEBUG
//DeadCode JON 17Sep00 	if (ht >= MAX_LAND_TEXTURES)
        if (hCurrentRenderTarget.getInstance() >= MAX_LAND_TEXTURES)
            INT3;
#endif

        outRect = &landRect;
        psrc=pDDS7LandRT;
        pdst=landTextures[hCurrentRenderTarget.getInstance()];
        break;
        NODEFAULT;
    }

//DeadCode JON 16Oct00 	ddsd.dwSize=sizeof(ddsd);
//DeadCode JON 16Oct00 	lastError=pdst->GetSurfaceDesc(&ddsd);
#ifndef NDEBUG
//DeadCode JON 17Sep00 	if ( landRect.bottom != ddsd.dwHeight )
//DeadCode JON 17Sep00 		INT3;
#endif

    if (lastError!=DD_OK)
    {
        CloseDown();
        return lastError;
    }


//	hr = D3DXLoadTextureFromSurface( pD3DDEV7, pdst, 0, psrc, &landRect, NULL, D3DX_FT_POINT );
//	if (hr!=DD_OK)
//	{
//		char* errDesc;
//		GetErrorDesc( hr, errDesc );
//		int i = 0;
//	}


    if (flags&F_VSLOWCOPY)
    {
        PerformVSlowCopy(pdst,psrc,outRect);
    }
    else
    {
        if (flags&F_SLOWCOPY)
            PerformSlowCopy(pdst,psrc,outRect);
        else
            lastError=pdst->Blt(NULL,psrc,outRect,DDBLT_WAIT,NULL);
    }



#ifndef NDEBUG
    char *errDesc;
    GetErrorDesc( lastError, errDesc );
#endif

#ifndef _NO_LANDSCAPE_MIPMAPS
    UpdateMipMaps( pdst );
#else
//TempCode JON 1Nov00 	if (hCurrentRenderTarget.getType() == RENDERTARGET_MIRROR )
//TempCode JON 1Nov00 	{
//TempCode JON 1Nov00 		UpdateMipMaps( pdst );
//TempCode JON 1Nov00 	}
#endif


    /*	DDSCAPS2 ddscaps;
    	ddscaps.dwCaps=DDSCAPS_MIPMAP;
    	ddscaps.dwCaps2=0L;
    	ddscaps.dwCaps3=0L;
    	ddscaps.dwCaps4=0L;
    	for (	pdst->AddRef(),psrc=pdst,psrc->GetAttachedSurface(&ddscaps,&pdst);
    			pdst!=NULL;
    			psrc->Release(),psrc=pdst,psrc->GetAttachedSurface(&ddscaps,&pdst))
    	{
    #ifndef SOFT_MIPMAP
    		hr=pdst->Blt(NULL,psrc,NULL,DDBLT_WAIT,NULL);
    //		GetErrorDesc( hr, errDesc );
    #else
    		MakeMipLevel(psrc,pdst);
    #endif
    	}
    	psrc->Release();
    */
    //DeadCode JON 11Jul00 	countRefs( psrc );

//TEMPCODE JON 5/15/00 	if (hr!=DD_OK)
//TEMPCODE JON 5/15/00 		CloseDown();
    return lastError;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReduceLandQuality
//Author		Jon.
//Date			Tue 6 Jul 2000
//
//------------------------------------------------------------------------------
HRESULT Lib3D::ReduceLandQuality(UWord& sourceTextIndex, UWord& destTextIndex )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

#ifdef _NO_DYNAMIC_TEXT_UPLOAD
    return S_OK;
#endif
    LPDIRECTDRAWSURFACE7 pSrc,pDst;
    DDSURFACEDESC2 sourceSurfaceDesc, destSurfaceDesc;

    pSrc=landTextures[sourceTextIndex];
    pDst=landTextures[destTextIndex];

    sourceSurfaceDesc.dwSize=
        destSurfaceDesc.dwSize=sizeof(sourceSurfaceDesc);
    lastError=pSrc->GetSurfaceDesc(&sourceSurfaceDesc);
    if (lastError!=DD_OK)
    {
        CloseDown();
        return lastError;
    }

    lastError=pDst->GetSurfaceDesc(&destSurfaceDesc);
    if (lastError!=DD_OK)
    {
        CloseDown();
        return lastError;
    }

    // blit the lower texture rez...
    lastError=pDst->Blt(NULL,pSrc,NULL,DDBLT_WAIT,NULL);

#ifndef _NO_LANDSCAPE_MIPMAPS
    // now make the mipmaps..
    DDSCAPS2 ddscaps;
    ddscaps.dwCaps=DDSCAPS_MIPMAP;
    ddscaps.dwCaps2=0L;
    ddscaps.dwCaps3=0L;
    ddscaps.dwCaps4=0L;
    for (	pSrc=pDst,pSrc->GetAttachedSurface(&ddscaps,&pDst);
            pDst!=NULL;
            pSrc=pDst,pSrc->GetAttachedSurface(&ddscaps,&pDst))
    {
#ifndef SOFT_MIPMAP
        lastError=pDst->Blt(NULL,pSrc,NULL,DDBLT_WAIT,NULL);
//		GetErrorDesc( hr, errDesc );
#else
        MakeMipLevel(pSrc,pDst);
#endif
#endif
//TEMPCODE JON 5/15/00 	if (hr!=DD_OK)
//TEMPCODE JON 5/15/00 		CloseDown();
        return lastError;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateLandscapeTextures
//Author		Paul.
//Date			Wed 15 Dec 1999
//Modified		Jon 25/07/00 - now uses the current textureblending option as the max allowed
//				and sets that as the master.
//				also sets up some other options that need to be set in the meantime
//
//------------------------------------------------------------------------------
HRESULT Lib3D::AllocateLandscapeTextures()
{
    struct SLandTextureTable
    {
        ULong totalRAM;
        ULong biggestWH;
        UWord num[8];
        HINTS textureQuality;
        HINTS textureBlending;
    };
#pragma warnmsg ( "please tweak these values to max out the 64mb+ cards" )
    SLandTextureTable landTextureTable[]=
    {
//tempcode		{0,0,{2,	8,	16,	32,	64,	128,	4,	0},	HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
//DeadCode JON 31Jan100 		{0,0,{4,	8,	16,	32,	64,	128,	4,	0},	HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
//tempcode		{0,0,{1,	4,	8,	40,	64,	128,	11,	0},	HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
//tempcode		{0,0,{0,	1,	4,	8,	40,	64,		128,11},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
//DeadCode JON 18Jul00 		{0,0,{0,	0,	4,	8,	40,	64,		128,12},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
//DeadCode JON 18Jul00 		{0,0,{0,	0,	4,	8,	40,	64,		128,12},HINT_FULL_RES_TEXTURE,		HINT_BILINEAR},
//DeadCode JON 18Jul00 		{0,0,{0,	0,	1,	10,	41,	64,		128,12},HINT_HALF_RES_TEXTURE,		HINT_TRILINEAR},
//DeadCode JON 18Jul00 		{0,0,{0,	0,	1,	10,	41,	64,		128,12},HINT_HALF_RES_TEXTURE,		HINT_BILINEAR},
//DeadCode JON 18Jul00 		{0,0,{0,	0,	0,	4,	42,	70,		128,12},HINT_QUARTER_RES_TEXTURE,	HINT_TRILINEAR},
//DeadCode JON 18Jul00 		{0,0,{0,	0,	0,	4,	42,	70,		128,12},HINT_QUARTER_RES_TEXTURE,	HINT_BILINEAR}
//				1024512	256	128	64	32	8	4
        {0,0,{	0,	0,	6,	10,	44,	64,	100,32},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
//TempCode JON 5Sep00 		{0,0,{	0,	0,	256, 0,	 0,  0,   0, 0},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
        {0,0,{	0,	0,	6,	10,	44,	64,	100,32},HINT_FULL_RES_TEXTURE,		HINT_BILINEAR},
        {0,0,{	0,	0,	4,	10,	44,	64,	102,32},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
        {0,0,{	0,	0,	4,	10,	44,	64,	102,32},HINT_FULL_RES_TEXTURE,		HINT_BILINEAR},
        {0,0,{	0,	0,	2,	10,	41,	59,	112,32},HINT_HALF_RES_TEXTURE,		HINT_TRILINEAR},
        {0,0,{	0,	0,	2,	10,	41,	59,	112,32},HINT_HALF_RES_TEXTURE,		HINT_BILINEAR},
        {0,0,{	0,	0,	0,	4,	42,	70,	92,	48},HINT_QUARTER_RES_TEXTURE,	HINT_TRILINEAR},
        {0,0,{	0,	0,	0,	4,	42,	70,	92,	48},HINT_QUARTER_RES_TEXTURE,	HINT_BILINEAR},
        {0,0,{	0,	0,	0,	4,	42,	70,	80,	60},HINT_EIGHTH_RES_TEXTURE,	HINT_TRILINEAR},
        {0,0,{	0,	0,	0,	4,	42,	70,	80,	60},HINT_EIGHTH_RES_TEXTURE,	HINT_BILINEAR}
    },
    *pLTT;

    // fill this with corresponding on screen max's for the rows in the above table. - leave the lowest rez at full
    SLandTextureTable onScreenMax[]=
    {
        {0,0,{	0,	0,	6,	8,	14,	40,	60,	32},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
//TempCode JON 5Sep00 		{0,0,{	0,	0,	256,0,	 0,  0,	 0,	 0},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
        {0,0,{	0,	0,	6,	8,	14,	40,	60,	32},HINT_FULL_RES_TEXTURE,		HINT_BILINEAR},
        {0,0,{	0,	0,	4,	8,	14,	40,	60,	32},HINT_FULL_RES_TEXTURE,		HINT_TRILINEAR},
        {0,0,{	0,	0,	4,	8,	14,	40,	60,	32},HINT_FULL_RES_TEXTURE,		HINT_BILINEAR},
        {0,0,{	0,	0,	2,	8,	14,	40,	60,	32},HINT_HALF_RES_TEXTURE,		HINT_TRILINEAR},
        {0,0,{	0,	0,	2,	8,	14,	40,	60,	32},HINT_HALF_RES_TEXTURE,		HINT_BILINEAR},
        {0,0,{	0,	0,	0,	4,	20, 45,	60,	48},HINT_QUARTER_RES_TEXTURE,	HINT_TRILINEAR},
        {0,0,{	0,	0,	0,	4,	20,	45,	60,	48},HINT_QUARTER_RES_TEXTURE,	HINT_BILINEAR},
        {0,0,{	0,	0,	0,	4,	20,	45,	60,	60},HINT_EIGHTH_RES_TEXTURE,	HINT_TRILINEAR},
        {0,0,{	0,	0,	0,	4,	20,	45,	60,	60},HINT_EIGHTH_RES_TEXTURE,	HINT_BILINEAR}
    };

    const int MAX_OPTS=sizeof(landTextureTable)/sizeof(SLandTextureTable);

#ifndef NDEBUG
    // test table routine... - ensures that there is no more than max textures in an option
    // as I can't add up.
    {
        for ( int row = 0; row < MAX_OPTS; row++ )
        {
            int count = 0;
            for ( int rez = 0; rez<8; rez++ )
                count+=landTextureTable[row].num[rez];
            if ( count > MAX_LAND_TEXTURES )
                INT3;
        }
    }
#endif

    //initialise option table
    for (int w=MAX_OPTS-1; w>=0; w--)
    {
        SLandTextureTable *ltt=landTextureTable+w;
        ULong totalRAM,biggestWH;
        totalRAM=0;
        for (int x=7; x>=0; x--)
        {
            if (ltt->num[x])
            {
                biggestWH=1024>>x;
                ULong thisRAM;
                if (ltt->textureQuality==HINT_FULL_RES_TEXTURE)			thisRAM=biggestWH;
                else if (ltt->textureQuality==HINT_HALF_RES_TEXTURE)	thisRAM=biggestWH>>1;
                else													thisRAM=biggestWH>>2;
                if (ltt->textureBlending==HINT_TRILINEAR)
                    thisRAM=thisRAM*thisRAM+(thisRAM>>1)*(thisRAM>>1)+(thisRAM>>2)*(thisRAM>>2);
                else
                    thisRAM*=thisRAM;
                thisRAM=(thisRAM*ltt->num[x])<<1;
                totalRAM+=thisRAM;
            }
        }
        ltt->totalRAM=totalRAM;
        ltt->biggestWH=biggestWH;
    }

    //check the ammount of available texture RAM for stored textures
    DWORD totalRAM,freeRAM;
    DDSCAPS2 ddscaps;
    ZeroMemory(&ddscaps,sizeof(ddscaps));
    ddscaps.dwCaps=DDSCAPS_TEXTURE;

//DeadCode JON 10Jul00 	DDCAPS ddcaps;
//DeadCode JON 10Jul00 	ZeroMemory(&ddcaps,sizeof(ddcaps));
//DeadCode JON 10Jul00 	ddcaps.dwSize=sizeof(ddcaps);
//DeadCode JON 10Jul00
//DeadCode JON 10Jul00 	pDD7->GetCaps(&ddcaps,NULL);

//deadcode	if (flags&F_CANTMANAGETEXTURES)
//deadcode		ddscaps.dwCaps+=DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;

    lastError=pDD7->GetAvailableVidMem(&ddscaps,&totalRAM,&freeRAM);
//DeadCode JON 5Sep00 	gFreeRAM=freeRAM>>1;
//DeadCode JON 5Sep00 	g_usedRAM=0;
    if (lastError!=DD_OK)
    {
        CloseDown();
        return lastError;
    }
    //allow max 25% of RAM for landscape - or save 16mb for the shapes, whichever is greater...
    {
        if ( freeRAM > ((64*1024*1024)/3) )
        {
            freeRAM -= (16*1024*1024);
        }
        else
        {
            freeRAM>>=2;
        }
    }


    //DXT1 gives 6:1 compression
    if ((texFmt[TF_LAND].dwFlags&DDPF_FOURCC)!=0 &&
            texFmt[TF_LAND].dwFourCC==DXT1)
        totalRAM*=6;


    //if the back buffer is being used as a render target for the
    //landscape decompression then the maximum landscape texture size
    //is limited by the screen resolution
    ULong maximumWH;
    if ((flags&F_TEXTURECANBERENDERTARGET)!=0)
        maximumWH=selectedDevice.dwMaxTextureWidth;
    else
        maximumWH=MIN(selectedDevice.dwMaxTextureWidth,selectedMode.ddsd.dwHeight);

    maximumWH=MIN(256,maximumWH);

    // now checks to ensure that the textureblending is the same as the textureblending variable set...
    // picks a suitable set of texture resoultuions less than or equal to the texture quality flag
    // that may be set
    int i=0;
    if ( textureBlending == HINT_TRILINEAR )
    {
        for (; i<MAX_OPTS; i++)
            if ((landTextureTable[i].totalRAM<freeRAM) &&
                    (landTextureTable[i].biggestWH<=maximumWH) &&
                    (landTextureTable[i].textureBlending == HINT_TRILINEAR) &&
                    (landTextureTable[i].textureQuality >= textureQuality)
               )
                break;
    }
    else
    {
        // note same mem requirements for bi-linear as for no blending
        for (; i<MAX_OPTS; i++)
            if ((landTextureTable[i].totalRAM<freeRAM) &&
                    (landTextureTable[i].biggestWH<=maximumWH) &&
                    (landTextureTable[i].textureBlending != HINT_TRILINEAR) &&
                    (landTextureTable[i].textureQuality >= textureQuality)
               )
                break;
    }

    if (MAX_OPTS==i) return DDERR_GENERIC;

    pLTT=landTextureTable+i;

    masterTextureBlending = textureBlending;
    textureQuality=masterTextureQuality=pLTT->textureQuality;
//DeadCode JON 25Jul00 	textureBlending=masterTextureBlending=pLTT->textureBlending;
//	selectedDevice.dwMaxTextureWidth=
//		selectedDevice.dwMaxTextureHeight=maximumWH;

    //create a render target surface for the landscape if needed
    landRect.top=landRect.left=0;
    landRect.right=landRect.bottom=pLTT->biggestWH;

    if ((flags&F_TEXTURECANBERENDERTARGET)!=0)
    {
        // landscape render target
        DDSURFACEDESC2 ddsd;
        ZeroMemory(&ddsd,sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS;
        ddsd.dwWidth=ddsd.dwHeight=pLTT->biggestWH;
        ddsd.ddpfPixelFormat=texFmt[TF_LANDINIT];
        ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_3DDEVICE|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
        lastError=pDD7->CreateSurface(&ddsd,&pDDS7LandRT,NULL);
//DeadCode JON 17Aug00 		if ((selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_ZBUFFERLESSHSR)==0)
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 			DDSURFACEDESC2 zbsd;
//DeadCode JON 17Aug00 			zbsd.dwSize=sizeof(zbsd);
//DeadCode JON 17Aug00 			hr=pDDSZ7->GetSurfaceDesc(&zbsd);
//DeadCode JON 17Aug00 			zbsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
//DeadCode JON 17Aug00 			zbsd.ddsCaps.dwCaps=DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
//DeadCode JON 17Aug00 			zbsd.dwWidth=zbsd.dwHeight=pLTT->biggestWH;
//DeadCode JON 17Aug00 			hr=pDD7->CreateSurface(&zbsd,&pDDS7LandZB,NULL);
//DeadCode JON 17Aug00 			hr=pDDS7LandRT->AddAttachedSurface(pDDS7LandZB);
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 		else pDDS7LandZB=NULL;

        // mirror render target...
        ddsd.dwWidth=mirrorRect.right;
        ddsd.dwHeight=mirrorRect.bottom;
        lastError=pDD7->CreateSurface(&ddsd,&pDDS7MirrorRT,NULL);


        if ((selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_ZBUFFERLESSHSR)==0)
        {
            // make the z buffer
            DDSURFACEDESC2 zbsd;
            zbsd.dwSize=sizeof(zbsd);
            lastError=pDDSZ7->GetSurfaceDesc(&zbsd);
            zbsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
            zbsd.ddsCaps.dwCaps=DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
            zbsd.dwWidth=zbsd.dwHeight=pLTT->biggestWH;
            lastError=pDD7->CreateSurface(&zbsd,&pDDS7LandZB,NULL);
            lastError=pDDS7LandRT->AddAttachedSurface(pDDS7LandZB);

            zbsd.dwWidth=ddsd.dwWidth;
            zbsd.dwHeight=ddsd.dwHeight;
            lastError=pDD7->CreateSurface(&zbsd,&pDDS7MirrorZB,NULL);
            lastError=pDDS7MirrorRT->AddAttachedSurface(pDDS7MirrorZB);
        }
        else
        {
            pDDS7LandZB=pDDS7MirrorZB=NULL;
        }
    }
    else
    {
        pDDS7LandRT=pDDS7MirrorRT=pDDSB7;
        pDDS7LandZB=pDDS7MirrorZB=pDDSZ7;
    }

//DeadCode JON 18Jul00 	num1024Textures=pLTT->num[0];
//DeadCode JON 18Jul00 	num512Textures=pLTT->num[1];
//DeadCode JON 18Jul00 	num256Textures=pLTT->num[2];
//DeadCode JON 18Jul00 	num128Textures=pLTT->num[3];
//DeadCode JON 18Jul00 	num64Textures=pLTT->num[4];
//DeadCode JON 18Jul00 	num32Textures=pLTT->num[5];
//DeadCode JON 18Jul00 	num16Textures=pLTT->num[6];
//DeadCode JON 18Jul00 	num8Textures=pLTT->num[7];

    {
        for ( int j=0, cumV=0; j< LAND_TEXT_BANDS; j++ )
        {
            landTextureMaxOnScreen[j] = onScreenMax[i].num[j];
            landTextureBandSize[j] = pLTT->num[j];
            landTextureBandBase[j] = cumV;
            cumV+=landTextureBandSize[j];
        }
    }

    //allocate the textures
    LPDIRECTDRAWSURFACE7 *pLT=&landTextures[0];

    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|
                 DDSD_PIXELFORMAT|DDSD_CAPS|
                 DDSD_MIPMAPCOUNT|DDSD_TEXTURESTAGE;

//#define _VIDEOLANDSCAPE_
#ifdef _VIDEOLANDSCAPE_
    DDSURFACEDESC2 backBufferDesc;
    ZeroMemory(&backBufferDesc,sizeof(backBufferDesc));
    backBufferDesc.dwSize=sizeof(ddsd);
    pDDS7LandRT->GetSurfaceDesc(&backBufferDesc);

    ddsd.ddpfPixelFormat=backBufferDesc.ddpfPixelFormat;
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_COMPLEX|DDSCAPS_MIPMAP|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;
#else
    ddsd.ddpfPixelFormat=texFmt[TF_LAND];
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
    ddsd.ddsCaps.dwCaps2=DDSCAPS2_D3DTEXTUREMANAGE;

#endif
    if (flags&F_CANTMANAGETEXTURES)
        INT3;
//deadcode	if (flags&F_CANTMANAGETEXTURES)	ddsd.ddsCaps.dwCaps|=DDSCAPS_LOCALVIDMEM|DDSCAPS_VIDEOMEMORY;
//deadcode	else
//	ddsd.ddsCaps.dwCaps2=DDSCAPS2_D3DTEXTUREMANAGE;

#ifndef _NO_LANDSCAPE_MIPMAPS
    if (textureBlending==HINT_TRILINEAR)
        ddsd.dwMipMapCount=3;
    else
#endif
        ddsd.dwMipMapCount=1;

    ddsd.dwTextureStage=0L;
    ddsd.dwWidth=ddsd.dwHeight=1024;

    for (int j=0; j<8; j++,ddsd.dwWidth=(ddsd.dwHeight>>=1))
        for (int k=pLTT->num[j]; k>0; k--)
            if ((lastError=pDD7->CreateSurface(&ddsd,pLT++,NULL))!=DD_OK)
            {

                CloseDown();
                return lastError;
            }

    for (i=255; i>=0; landTextRec[i--]=0);


    // now build the mirror texture...
    if ((flags&F_TEXTURECANBERENDERTARGET)!=0)
    {
        // no need the darn thing is the render target...
        pDDS7Mirror = pDDS7MirrorRT;
    }
    else
    {
#pragma warnmsg( "should be a const not a constant...." )
        ddsd.dwWidth=ddsd.dwHeight=128;
        if ((lastError = pDD7->CreateSurface(&ddsd,&pDDS7Mirror,NULL))!=DD_OK)
        {
            CloseDown();
            return lastError;
        }
    }


    // now set up the render state blocks...
    return SetUpRenderBlocks();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeLandscapeTextures
//Author		Paul.
//Date			Wed 15 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::FreeLandscapeTextures()
{
    for (int i=255; i>=0; i--)
        if (landTextures[i]!=NULL)
        {
            landTextures[i]->Release();
            landTextures[i]=NULL;
        }
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandscapeTextureCount
//Author		Paul.
//Date			Wed 15 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::GetLandscapeTextureCount(SLong& n0,SLong& n1,SLong& n2,SLong& n3,
                                        SLong& n4,SLong& n5,SLong& n6,SLong& n7)
{
//DeadCode JON 18Jul00 	n0=num1024Textures;	n1=num512Textures;
//DeadCode JON 18Jul00 	n2=num256Textures;	n3=num128Textures;
//DeadCode JON 18Jul00 	n4=num64Textures;	n5=num32Textures;
//DeadCode JON 18Jul00 	n6=num16Textures;	n7=num8Textures;
    n0 = landTextureBandSize[0];
    n1 = landTextureBandSize[1];
    n2 = landTextureBandSize[2];
    n3 = landTextureBandSize[3];
    n4 = landTextureBandSize[4];
    n5 = landTextureBandSize[5];
    n6 = landTextureBandSize[6];
    n7 = landTextureBandSize[7];

    return S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandscapeTextureOnScreenMax
//Author		Jon.
//Date			Mon 31 Jul 2000
//
//------------------------------------------------------------------------------
HRESULT Lib3D::GetLandscapeTextureOnScreenMax(SLong& n0,SLong& n1,SLong& n2,SLong& n3,
        SLong& n4,SLong& n5,SLong& n6,SLong& n7)
{

    n0 = landTextureMaxOnScreen[0];
    n1 = landTextureMaxOnScreen[1];
    n2 = landTextureMaxOnScreen[2];
    n3 = landTextureMaxOnScreen[3];
    n4 = landTextureMaxOnScreen[4];
    n5 = landTextureMaxOnScreen[5];
    n6 = landTextureMaxOnScreen[6];
    n7 = landTextureMaxOnScreen[7];

    return S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeLandscapeTexture
//Author		Paul.
//Date			Wed 15 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::FreeLandscapeTexture(UWord tno)
{
    if (tno<MAX_LAND_TEXTURES) landTextRec[tno]=0;
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateLandscapeTexture
//Author		Paul.
//Date			Wed 15 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::AllocateLandscapeTexture(UWord reqRez,UWord& tHndl)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

//	SLong landTextureBandBase[LAND_TEXT_BANDS];							//JON 18Jul00
//	SLong landTextureBandSize[LAND_TEXT_BANDS];							//JON 18Jul00

#ifndef NDEBUG
    if ( reqRez>=LAND_TEXT_BANDS )
        return DDERR_INVALIDPARAMS;
#endif

    int base = landTextureBandBase[ reqRez ];
    int stop = base+landTextureBandSize[ reqRez ];

    for ( int i = base; i<stop; i++ )
    {
        if ( landTextRec[i] == 0 ) // is the thing free
        {
            landTextRec[i] = 1; // now it isn't free
            tHndl = i;
#ifndef NDEBUG
            if ( i >= MAX_LAND_TEXTURES)
                INT3;
#endif
            return S_OK;
        }
    }

#ifndef NDEBUG
    INT3;
#endif

    tHndl = NULL_LAND_TEXT_REF;
    return DDERR_GENERIC;

//DeadCode JON 18Jul00 	tHndl=0;
//DeadCode JON 18Jul00 	if (reqRez>0)	tHndl+=num1024Textures;
//DeadCode JON 18Jul00 	if (reqRez>1)	tHndl+=num512Textures;
//DeadCode JON 18Jul00 	if (reqRez>2)	tHndl+=num256Textures;
//DeadCode JON 18Jul00 	if (reqRez>3)	tHndl+=num128Textures;
//DeadCode JON 18Jul00 	if (reqRez>4)	tHndl+=num64Textures;
//DeadCode JON 18Jul00 	if (reqRez>5)	tHndl+=num32Textures;
//DeadCode JON 18Jul00 	if (reqRez>6)	tHndl+=num16Textures;
//DeadCode JON 18Jul00 	if (reqRez>7)	return DDERR_INVALIDPARAMS;
//DeadCode JON 18Jul00 	UWord scnHndl=tHndl;
//DeadCode JON 18Jul00 	while (landTextRec[scnHndl] && scnHndl<256) scnHndl++;
//DeadCode JON 18Jul00 	if (scnHndl==256)
//DeadCode JON 18Jul00 	{
//DeadCode JON 18Jul00 		scnHndl=tHndl;
//DeadCode JON 18Jul00 		while (landTextRec[scnHndl] && scnHndl) scnHndl--;
//DeadCode JON 18Jul00 		if (0==scnHndl)
//DeadCode JON 18Jul00 			return DDERR_GENERIC;
//DeadCode JON 18Jul00 	}
//DeadCode JON 18Jul00 	tHndl=scnHndl;
//DeadCode JON 18Jul00 	landTextRec[tHndl]=0xFF;
//DeadCode JON 18Jul00 	return S_OK;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMaterial
//Author		Paul.
//Date			Thu 16 Dec 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::SetMaterial(UWord ht,MAPDESC *pmap)
{
#ifdef _ONLY_ONE_LANSDCAPE_TEXTURE
    if ( landscapeTexture == NULL )
        return SetMaterial( HMATERIAL( pmap ) );
    else
        return SetMaterial( HMATERIAL( landscapeTexture, pmap ) );
#endif
    HMATERIAL hMaterial;
//DeadCode JON 31Aug00 	hMaterial.tsH[0]=hMaterial.tsW[0]=255.f/(256.f*256.f);
    hMaterial.isMasked=0;
    hMaterial.isLand=0xFFFFFFFF^ULong(ht);
    hMaterial.uniqueTextID = ht|TIT_LANDSCAPE;
    hMaterial.materialFlags = IS_LAND;

    if (pmap!=NULL)
    {
        // double textured
        hMaterial.materialFlags += IS_DOUBLE_TEXTURED;

        hMaterial.p[1]=pmap;
        hMaterial.f=2;
        hMaterial.tsW[1]=1.f/hMaterial.p[1]->w;
        hMaterial.tsH[1]=1.f/hMaterial.p[1]->h;
        if (hMaterial.p[1]->hTextureMap==0 || textureTable[hMaterial.p[1]->hTextureMap]==NULL)
        {
            SLong j;
            for (j=MAX_TEXTURES-1; j>0 && textureTable[j]!=NULL; j--);
            if (!j)
            {
                CloseDown();
                return DDERR_GENERIC;
            }
            hMaterial.p[1]->hTextureMap=HTEXTUREMAP(j);
            CreateTextureMap(hMaterial.p[1],textureTable[hMaterial.p[1]->hTextureMap],1);
        }
        // 	hMaterial.uniqueTextID|= ( (hMaterial.p[1]->hTextureMap<<11)&TIT_MASK_SECONDARY );
    }
    else
    {
        hMaterial.f=1;
    }

    if (SameMaterial(hLastMaterial,hMaterial))
        return DD_OK;

    hLastMaterial=hMaterial;

#ifndef NO_LANDSCAPE_SPECULAR
    if ( lightflag == LF_SPECULAR
#ifdef LIGHT_ALL_SPECULAR
            || lightflag == LF_LIGHTING
#endif
       )
        hLastMaterial.materialFlags |= IS_SPECULAR;
#endif

//	#pragma message ( __HERE__ "to optimize move this to set landscape material section" )
//DeadCode JON 18Jul00 	SLong *numbers[8] = {	&num1024Textures,	&num512Textures,
//DeadCode JON 18Jul00 							&num256Textures,	&num128Textures,
//DeadCode JON 18Jul00 							&num64Textures,		&num32Textures,
//DeadCode JON 18Jul00 							&num16Textures,		&num8Textures };

//DeadCode JON 5Sep00 	SLong index;
//DeadCode JON 5Sep00 	index=SLong(hLastMaterial.isLand^0xFFFFFFFFUL);

//DeadCode JON 31Aug00 	for (int i=0;i<8;i++)
//DeadCode JON 31Aug00 	{
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 		if (index<*numbers[i])
//DeadCode JON 31Aug00 		if ( index<landTextureBandSize[i] )
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 			index=i;
//DeadCode JON 31Aug00 			break;
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 		index-=*numbers[i];
//DeadCode JON 31Aug00 		index-=landTextureBandSize[i];
//DeadCode JON 31Aug00 	}
//TempCode JON 31Aug00 	D3DVALUE pixelSH;
//TempCode JON 31Aug00 	//landscapeTextScaleX = scW;
//TempCode JON 31Aug00
//TempCode JON 31Aug00 	pixelSH=(index==0)?.125f:(index==1)?.25f:(index==2)?.5f:D3DVALUE(1<<(index-3));
//TempCode JON 31Aug00
//TempCode JON 31Aug00 	landscapeTextOffsetX=hLastMaterial.tsW[0];
//TempCode JON 31Aug00 	landscapeTextScaleX=1.f/landscapeTextOffsetX;
//TempCode JON 31Aug00 	landscapeTextOffsetX*=pixelSH;	//*.5f;
//TempCode JON 31Aug00 	landscapeTextScaleX=(landscapeTextScaleX-2*pixelSH)/(landscapeTextScaleX*landscapeTextScaleX);
//TempCode JON 31Aug00 	landscapeTextOffsetY=landscapeTextOffsetX;
//TempCode JON 31Aug00 	landscapeTextScaleY=landscapeTextScaleX;
//DeadCode JON 5Sep00 						for ( int band = 7; landTextureBandBase[band] > index ; band-- )
//DeadCode JON 5Sep00 						{ /*search*/ }
//DeadCode JON 5Sep00
//DeadCode JON 5Sep00 						landscapeTextOffset = D3DVALUE( 1<<(6+band) );
//DeadCode JON 4Sep00 //	landscapeTextOffsetX=D3DVALUE( 1<<(10-band) );
//DeadCode JON 4Sep00 //	landscapeTextScaleX=D3DVALUE( 1<<(6+band) );
//DeadCode JON 4Sep00 //	landscapeTextScaleX=1.f/(255.f); // -1 as it removes the very edge
//DeadCode JON 4Sep00 	static float scale = (255.f/(256.f*256.f));//1.f/256.f;
//DeadCode JON 4Sep00 	static float offset = 1.f/512.f;
//DeadCode JON 4Sep00 //	static float scale = 1.f/128.f;//1.f/256.f;
//DeadCode JON 4Sep00 //	static float offset = -128.f/512.f;
//DeadCode JON 4Sep00 	landscapeTextScaleX=scale;
//DeadCode JON 4Sep00 	landscapeTextOffsetX=offset;
//DeadCode JON 4Sep00 	landscapeTextOffsetY=landscapeTextOffsetX;
//DeadCode JON 4Sep00 	landscapeTextScaleY=landscapeTextScaleX;

//DeadCode JON 5Sep00 const D3DVALUE landscapeTextScale = 255.f/(256.f*256.f);
//DeadCode JON 5Sep00 const D3DVALUE landscapeTextOffset = 1.f/512.f;


    curMatTextureTypeFlags = globTextureTypeFlags|hLastMaterial.f|LANDSCAPE_TEXTURE;

    return S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginStrip (3D vers)
//Author		Paul.
//Date			Thu 25 Nov p1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginStrip(const ULong& numVerts,R3DVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	return BeginPoly(numVerts,pVertArray);
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginFan (3D vers)
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
//#pragma message ( __HERE__ "begin fan" )
//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginFan(const ULong& numVerts,R3DVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	return BeginPoly(numVerts,pVertArray);
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginPoly (3D vers)
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
//#pragma message ( __HERE__ "begin poly" )
//DEADCODE JON 5/19/00 inline HRESULT Lib3D::BeginPoly(const ULong& numVerts,R3DVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	HRESULT hr;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	vertexType=D3DFVF_R3DVERTEX;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 #ifndef NDEBUG
//DEADCODE JON 5/19/00 	if (polyVertCount!=0xFFFFFFFF)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		INT3;
//DEADCODE JON 5/19/00 		return DDERR_GENERIC;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (numVerts<3 || numVerts>MAX_VERTICES)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		INT3;
//DEADCODE JON 5/19/00 		return DDERR_INVALIDPARAMS;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 #endif
//DEADCODE JON 5/19/00 	if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		SPolygon* spolygon;
//DEADCODE JON 5/19/00 		ALLOCATE_POLYGON_TNL( spolygon, numVerts );
//DEADCODE JON 5/19/00 		pVertArray=(R3DVERTEX*)spolygon->pVertexList;
//DEADCODE JON 5/19/00 		polyVertArray=pVertArray;
//DEADCODE JON 5/19/00 		polyVertCount=numVerts;
//DEADCODE JON 5/19/00 		return S_OK;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (hLastMaterial.f<=1)			pVertArray=vertArray;
//DEADCODE JON 5/19/00 	else if (hLastMaterial.f==2)	pVertArray=(R3DVERTEX*)vertArray2;
//DEADCODE JON 5/19/00 	else if (hLastMaterial.f==3)	pVertArray=(R3DVERTEX*)vertArray3;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	polyVertCount=numVerts;
//DEADCODE JON 5/19/00 	polyVertArray=pVertArray;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	return S_OK;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginStrip (3D vers)
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginStrip(const HMATERIAL& hMaterial,const ULong& numVerts,R3DVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	return BeginPoly(hMaterial,numVerts,pVertArray);
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginFan (3D vers)
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
//#pragma message ( __HERE__ "begin fan new material" )
Lib3DPoint* Lib3D::BeginFan( const HMATERIAL& mat, const ULong &vertexCount )
{
    if ((lastError=SetMaterial(mat))!=DD_OK) return NULL;
    return _BeginPoly( vertexCount );
}

Lib3DPoint* Lib3D::BeginFan( const ULong &vertexCount )
{
    return _BeginPoly( vertexCount );
}

//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginFan(const HMATERIAL& hMaterial,const ULong& numVerts,R3DVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	return BeginPoly(hMaterial,numVerts,pVertArray);
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginPoly (3D vers)
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
Lib3DPoint* Lib3D::BeginPoly( const ULong &vertexCount )
{
    return _BeginPoly( vertexCount );
}

Lib3DPoint* Lib3D::BeginPoly( const HMATERIAL& mat, const ULong &vertexCount )
{
    if ((lastError=SetMaterial(mat))!=DD_OK) return NULL;
    return _BeginPoly( vertexCount );
}

//#pragma message ( __HERE__ "inline me" )
inline Lib3DPoint* Lib3D::_BeginPoly( const ULong vertexCount )
{
#ifndef NDEBUG
//	if (polyVertCount!=0xFFFFFFFF)
    if ( insidePoly )
    {
        INT3;
        return NULL;
    }
    insidePoly = true;
    if (vertexCount<3 || vertexCount>MAX_VERTICES)
    {
        INT3;
        return NULL;
    }
#endif

//	SPolygon* sPolygon;
    ALLOCATE_POLYGON_NOLINK( currentPoly, vertexCount );
#ifndef _NO_VERTEX_SHARING
    SVertex* tmp = currentPoly->pVertexList;
    for ( int i = 0; i< vertexCount; i++ )
    {
#ifdef DO_INDEXED_VB
        tmp->identical = NULL;
#endif
        tmp->info.setUnique();
        tmp++;
    }
#endif
    //TEMPCODE JON 6/1/00 	memset( currentPoly->pVertexList, 0, vertexCount*sizeof( SVertex ) );
    return (Lib3DPoint*)currentPoly->pVertexList;
}

//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginPoly(const HMATERIAL& hMaterial,const ULong& numVerts,R3DVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	HRESULT hr;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	vertexType=D3DFVF_R3DVERTEX;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 #ifndef NDEBUG
//DEADCODE JON 5/19/00 	if (polyVertCount!=0xFFFFFFFF)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		INT3;
//DEADCODE JON 5/19/00 		return DDERR_GENERIC;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (numVerts<3 || numVerts>MAX_VERTICES)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		INT3;
//DEADCODE JON 5/19/00 		return DDERR_INVALIDPARAMS;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 #endif
//DEADCODE JON 5/19/00 	if ((hr=SetMaterial(hMaterial))!=DD_OK) return hr;					//PD 28Feb2000
//DEADCODE JON 5/19/00 	if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		SPolygon* spolygon;
//DEADCODE JON 5/19/00 		ALLOCATE_POLYGON_TNL( spolygon, numVerts );
//DEADCODE JON 5/19/00 		pVertArray=(R3DVERTEX*)spolygon->pVertexList;
//DEADCODE JON 5/19/00 		polyVertArray=pVertArray;
//DEADCODE JON 5/19/00 		polyVertCount=numVerts;
//DEADCODE JON 5/19/00 		return S_OK;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	else
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		if (hLastMaterial.f<=1)			pVertArray=vertArray;
//DEADCODE JON 5/19/00 		else if (hLastMaterial.f==2)	pVertArray=(R3DVERTEX*)vertArray2;
//DEADCODE JON 5/19/00 		else if (hLastMaterial.f==3)	pVertArray=(R3DVERTEX*)vertArray3;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	polyVertCount=numVerts;
//DEADCODE JON 5/19/00 	polyVertArray=pVertArray;
//DEADCODE JON 5/19/00 	return S_OK;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginStrip (2D vers)
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginStrip(const HMATERIAL& hMaterial,const ULong& numVerts,R3DTLVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	return BeginPoly(hMaterial,numVerts,pVertArray);
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginFan (2D vers)
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginFan(const HMATERIAL& hMaterial,const ULong& numVerts,R3DTLVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	return BeginPoly(hMaterial,numVerts,pVertArray);
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginPoly (2D vers)
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 HRESULT Lib3D::BeginPoly(const HMATERIAL& hMaterial,const ULong& numVerts,R3DTLVERTEX*& pVertArray)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	HRESULT hr;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	vertexType=D3DFVF_R3DTLVERTEX;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (polyVertCount!=0xFFFFFFFF) return DDERR_GENERIC;
//DEADCODE JON 5/19/00 	if (numVerts<3 || numVerts>MAX_VERTICES) return DDERR_INVALIDPARAMS;
//DEADCODE JON 5/19/00 	if ((hr=SetMaterial(hMaterial))!=DD_OK) return hr;						//PD 28Feb2000
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		lpD3DVB7=gpD3DVB7;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 		if (hLastMaterial.f==0)
//DEADCODE JON 5/19/00 			hr=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,
//DEADCODE JON 5/19/00 							(LPVOID*)&pVertArray,NULL);
//DEADCODE JON 5/19/00 		else
//DEADCODE JON 5/19/00 			hr=lpD3DVB7->Lock(DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,
//DEADCODE JON 5/19/00 							(LPVOID*)&pVertArray,NULL);
//DEADCODE JON 5/19/00 		if (hr!=D3D_OK)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			CloseDown();
//DEADCODE JON 5/19/00 			return hr;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	else
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		pVertArray=tlVertArray;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	polyVertCount=numVerts;
//DEADCODE JON 5/19/00 	polyVertArrayTL=pVertArray;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	return S_OK;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScaleTextureCoordinates
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------

//DeadCode JON 31Aug00 void Lib3D::ScaleTextureCoordinates(const HMATERIAL& mat, SPolygon* sPolygon )//R3DVERTEX* pr3dv,ULong vertCnt)
//DeadCode JON 31Aug00 {
//DeadCode JON 31Aug00 	if (mat.isLand)
//DeadCode JON 31Aug00 	{
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 		SLong *numbers[8] = {	&num1024Textures,	&num512Textures,
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 								&num256Textures,	&num128Textures,
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 								&num64Textures,		&num32Textures,
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 								&num16Textures,		&num8Textures };
//DeadCode JON 31Aug00 		SLong index;
//DeadCode JON 31Aug00 		index=SLong(mat.isLand^0xFFFFFFFFUL);
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 		for (int i=0;i<8;i++)
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 			if ( index<landTextureBandSize[i] )
//DeadCode JON 31Aug00 			{
//DeadCode JON 31Aug00 				index=i;
//DeadCode JON 31Aug00 				break;
//DeadCode JON 31Aug00 			}
//DeadCode JON 31Aug00 			index-=landTextureBandSize[i];
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 		for (int i=0;i<8;i++)
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 		{
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 			if (index<*numbers[i])
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 			{
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 				index=i;
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 				break;
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 			}
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 			index-=*numbers[i];
//DeadCode JON 31Aug00 //DeadCode JON 18Jul00 		}
//DeadCode JON 31Aug00 		D3DVALUE pixelSH;
//DeadCode JON 31Aug00 		D3DVALUE scW,ofW;
//DeadCode JON 31Aug00 		D3DVALUE scH,ofH;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 		pixelSH=(index==0)?.125f:(index==1)?.25f:(index==2)?.5f:D3DVALUE(1<<(index-3));
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 		ofW=mat.tsW[0];
//DeadCode JON 31Aug00 		scW=1.f/ofW;
//DeadCode JON 31Aug00 		ofW*=pixelSH;	//*.5f;
//DeadCode JON 31Aug00 		scW=(scW-2*pixelSH)/(scW*scW);
//DeadCode JON 31Aug00 		ofH=ofW;
//DeadCode JON 31Aug00 		scH=scW;
//DeadCode JON 31Aug00 //		for (i=0;i<vertCnt;i++)
//DeadCode JON 31Aug00 //		{
//DeadCode JON 31Aug00 //			pr3dv[i].tu=scW*D3DVALUE(pr3dv[i].ix)+ofW;
//DeadCode JON 31Aug00 //			pr3dv[i].tv=scH*D3DVALUE(pr3dv[i].iy)+ofH;
//DeadCode JON 31Aug00 //		}
//DeadCode JON 31Aug00 		switch (mat.f)
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 		case 3:
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			R3DVERTEX3 *pr3dv3=(R3DVERTEX3*)pr3dv;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			D3DVALUE tsW=mat.tsW[2];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			D3DVALUE tsH=mat.tsH[2];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			for (int i=0;i<vertCnt;i++)
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //				pr3dv3[i].tu =mat.tsW[0]*pr3dv3[i].ix;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //				pr3dv3[i].tv =mat.tsH[0]*pr3dv3[i].iy;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv3[i].tu=scW*D3DVALUE(pr3dv3[i].ix)+ofW;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv3[i].tv=scH*D3DVALUE(pr3dv3[i].iy)+ofH;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv3[i].tu1=mat.tsW[1]*pr3dv3[i].ix1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv3[i].tv1=mat.tsH[1]*pr3dv3[i].iy1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv3[i].tu2=mat.tsW[2]*pr3dv3[i].ix2;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv3[i].tv2=mat.tsH[2]*pr3dv3[i].iy2;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			}
//DeadCode JON 31Aug00 			SVertex* curVert = sPolygon->pVertexList;
//DeadCode JON 31Aug00 			for ( int i = sPolygon->vertexcount; i!=0; i-- )
//DeadCode JON 31Aug00 			{
//DeadCode JON 31Aug00 				curVert->tu = scW*D3DVALUE(curVert->ix)+ofW;
//DeadCode JON 31Aug00 				curVert->tv = scH*D3DVALUE(curVert->iy)+ofH;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 				curVert->tu1=mat.tsW[1]*curVert->ix1;
//DeadCode JON 31Aug00 				curVert->tv1=mat.tsH[1]*curVert->iy1;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 				curVert->tu2=mat.tsW[2]*curVert->ix2;
//DeadCode JON 31Aug00 				curVert->tv2=mat.tsH[2]*curVert->iy2;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 //DEADCODE JON 5/25/00 				curVert=curVert->pNext;
//DeadCode JON 31Aug00 				curVert++;
//DeadCode JON 31Aug00 			}
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00 		break;
//DeadCode JON 31Aug00 		case 2:
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			R3DVERTEX2 *pr3dv2=(R3DVERTEX2*)pr3dv;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			for (int i=0;i<vertCnt;i++)
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //				pr3dv2[i].tu =mat.tsW[0]*pr3dv2[i].ix;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //				pr3dv2[i].tv =mat.tsH[0]*pr3dv2[i].iy;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv2[i].tu=scW*D3DVALUE(pr3dv2[i].ix)+ofW;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv2[i].tv=scH*D3DVALUE(pr3dv2[i].iy)+ofH;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv2[i].tu1=mat.tsW[1]*pr3dv2[i].ix1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv2[i].tv1=mat.tsH[1]*pr3dv2[i].iy1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			}
//DeadCode JON 31Aug00 			SVertex* curVert = sPolygon->pVertexList;
//DeadCode JON 31Aug00 			for ( int i = sPolygon->vertexcount; i!=0; i-- )
//DeadCode JON 31Aug00 			{
//DeadCode JON 31Aug00 				curVert->tu = scW*D3DVALUE(curVert->ix)+ofW;
//DeadCode JON 31Aug00 				curVert->tv = scH*D3DVALUE(curVert->iy)+ofH;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 				curVert->tu1=mat.tsW[1]*curVert->ix1;
//DeadCode JON 31Aug00 				curVert->tv1=mat.tsH[1]*curVert->iy1;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 //DEADCODE JON 5/25/00 				curVert=curVert->pNext;
//DeadCode JON 31Aug00 				curVert++;
//DeadCode JON 31Aug00 			}
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00 		break;
//DeadCode JON 31Aug00 		case 1:
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //			D3DVALUE tsW=mat.tsW[0];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //			D3DVALUE tsH=mat.tsH[0];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			for (int i=0;i<vertCnt;i++)
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //				pr3dv[i].tu=tsW*pr3dv[i].ix;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 //				pr3dv[i].tv=tsH*pr3dv[i].iy;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv[i].tu=scW*D3DVALUE(pr3dv[i].ix)+ofW;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 				pr3dv[i].tv=scH*D3DVALUE(pr3dv[i].iy)+ofH;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			}
//DeadCode JON 31Aug00 			SVertex* curVert = sPolygon->pVertexList;
//DeadCode JON 31Aug00 			for ( int i = sPolygon->vertexcount; i!=0; i-- )
//DeadCode JON 31Aug00 			{
//DeadCode JON 31Aug00 				curVert->tu = scW*D3DVALUE(curVert->ix)+ofW;
//DeadCode JON 31Aug00 				curVert->tv = scH*D3DVALUE(curVert->iy)+ofH;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 //DEADCODE JON 5/25/00 				curVert=curVert->pNext;
//DeadCode JON 31Aug00 				curVert++;
//DeadCode JON 31Aug00 			}
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00 		break;
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 		return;
//DeadCode JON 31Aug00 	}
//DeadCode JON 31Aug00 	switch (mat.f)
//DeadCode JON 31Aug00 	{
//DeadCode JON 31Aug00 	case 3:
//DeadCode JON 31Aug00 	{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		R3DVERTEX3 *pr3dv3=(R3DVERTEX3*)pr3dv;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		D3DVALUE tsW=mat.tsW[2];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		D3DVALUE tsH=mat.tsH[2];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		for (int i=0;i<vertCnt;i++)
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv3[i].tu =mat.tsW[0]*pr3dv3[i].ix;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv3[i].tv =mat.tsH[0]*pr3dv3[i].iy;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv3[i].tu1=mat.tsW[1]*pr3dv3[i].ix1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv3[i].tv1=mat.tsH[1]*pr3dv3[i].iy1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv3[i].tu2=mat.tsW[2]*pr3dv3[i].ix2;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv3[i].tv2=mat.tsH[2]*pr3dv3[i].iy2;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		}
//DeadCode JON 31Aug00 		SVertex* curVert = sPolygon->pVertexList;
//DeadCode JON 31Aug00 		for ( int i = sPolygon->vertexcount; i!=0; i-- )
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 			curVert->tu=mat.tsW[0]*curVert->ix;
//DeadCode JON 31Aug00 			curVert->tv=mat.tsH[0]*curVert->iy;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 			curVert->tu1=mat.tsW[1]*curVert->ix1;
//DeadCode JON 31Aug00 			curVert->tv1=mat.tsH[1]*curVert->iy1;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 			curVert->tu2=mat.tsW[2]*curVert->ix2;
//DeadCode JON 31Aug00 			curVert->tv2=mat.tsH[2]*curVert->iy2;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 //DEADCODE JON 5/25/00 			curVert=curVert->pNext;
//DeadCode JON 31Aug00 			curVert++;
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 	}
//DeadCode JON 31Aug00 	break;
//DeadCode JON 31Aug00 	case 2:
//DeadCode JON 31Aug00 	{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		R3DVERTEX2 *pr3dv2=(R3DVERTEX2*)pr3dv;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		for (int i=0;i<vertCnt;i++)
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv2[i].tu =mat.tsW[0]*pr3dv2[i].ix;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv2[i].tv =mat.tsH[0]*pr3dv2[i].iy;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv2[i].tu1=mat.tsW[1]*pr3dv2[i].ix1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv2[i].tv1=mat.tsH[1]*pr3dv2[i].iy1;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		}
//DeadCode JON 31Aug00 		SVertex* curVert = sPolygon->pVertexList;
//DeadCode JON 31Aug00 		for ( int i = sPolygon->vertexcount; i!=0; i-- )
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 			curVert->tu=mat.tsW[0]*curVert->ix;
//DeadCode JON 31Aug00 			curVert->tv=mat.tsH[0]*curVert->iy;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 			curVert->tu1=mat.tsW[1]*curVert->ix1;
//DeadCode JON 31Aug00 			curVert->tv1=mat.tsH[1]*curVert->iy1;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 //DEADCODE JON 5/25/00 			curVert=curVert->pNext;
//DeadCode JON 31Aug00 			curVert++;
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 	}
//DeadCode JON 31Aug00 	break;
//DeadCode JON 31Aug00 	case 1:
//DeadCode JON 31Aug00 	{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		D3DVALUE tsW=mat.tsW[0];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		D3DVALUE tsH=mat.tsH[0];
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		for (int i=0;i<vertCnt;i++)
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		{
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv[i].tu=tsW*pr3dv[i].ix;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 			pr3dv[i].tv=tsH*pr3dv[i].iy;
//DeadCode JON 31Aug00 //DEADCODE JON 5/19/00 		}
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 		SVertex* curVert = sPolygon->pVertexList;
//DeadCode JON 31Aug00 		for ( int i = sPolygon->vertexcount; i!=0; i-- )
//DeadCode JON 31Aug00 		{
//DeadCode JON 31Aug00 			curVert->tu=mat.tsW[0]*curVert->ix;
//DeadCode JON 31Aug00 			curVert->tv=mat.tsH[0]*curVert->iy;
//DeadCode JON 31Aug00
//DeadCode JON 31Aug00 //DEADCODE JON 5/25/00 			curVert=curVert->pNext;
//DeadCode JON 31Aug00 			curVert++;
//DeadCode JON 31Aug00 		}
//DeadCode JON 31Aug00 	}
//DeadCode JON 31Aug00 	break;
//DeadCode JON 31Aug00 	}
//DeadCode JON 31Aug00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndStrip
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 HRESULT Lib3D::EndStrip()
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	INT3;
//DEADCODE JON 5/19/00 	HRESULT hr=S_OK;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (vertexType!=D3DFVF_R3DVERTEX)
//DEADCODE JON 5/19/00 		return DDERR_GENERIC;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (polyVertCount==0xFFFFFFFF)
//DEADCODE JON 5/19/00 		return DDERR_GENERIC;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (hLastMaterial.f)
//DEADCODE JON 5/19/00 		ScaleTextureCoordinates(hLastMaterial,polyVertArray,polyVertCount);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	polyVertCount=0xFFFFFFFF;
//DEADCODE JON 5/19/00 	return hr;
//DEADCODE JON 5/19/00 }

void CopyTextCoords( SVertex* sVertex, D3DVERTEX *pv, ULong SizeOfVertex )
{
    sVertex->tu=pv->tu;					// save all
    sVertex->tv=pv->tv;
    if (SizeOfVertex>sizeof(R3DVERTEX))
    {
        sVertex->tu1=((R3DVERTEX2*)pv)->tu1;
        sVertex->tv1=((R3DVERTEX2*)pv)->tv1;
//DeadCode JON 30Oct00 			if (SizeOfVertex>sizeof(R3DVERTEX2))
//DeadCode JON 30Oct00 			{
//DeadCode JON 30Oct00 				sVertex->tu2=((R3DVERTEX3*)pv)->tu2;
//DeadCode JON 30Oct00 				sVertex->tv2=((R3DVERTEX3*)pv)->tv2;
//DeadCode JON 30Oct00 			}
    }												// end of save all
}

//#pragma message (__HERE__ "inline me" )
// note should be inlined and expanded as constants as much as possible
inline void Lib3D::TransformVertexAsRequired( SVertex* sVertex, const ULong flags, const LIGHTFLAG curLF )
{

#ifndef _NO_VERTEX_SHARING
    int num = sVertex->info.getDoPointNum();
    // test for all valid

//DeadCode JON 15Jun00 	if ( sVertex->info.isAllValid() )
    if ( (flags&ALL_VALID)==ALL_VALID )
    {
        // right quick test
        if ( (flags&TEXTURE_COUNT_MASK) == 0 )
        {
            // we are plain colour - but everyting is valid - still need to retransform and set up the normals
            // to get the correct colour
            // transform the vertices
            sVertex->Transform( &combinedMatrix );

            sVertex->info.addToFlags( PLAINCOL_FLAG );
            SetVertexCol( sVertex, curLF );
            if ( flags&DO_SW_FOG )
            {
                SetColAlpha( sVertex->specular, fogTable[ (0x3FF&F2UL_Round( sVertex->hw*fogMul )) ] );
            }

            // do the texture coord copy - not bloody needed, it's plain col!!!
            // copy over the clipcode
            sVertex->clipcode = lastDoPoint[ num ]->clipcode;
//TempCode JON 30Oct00 #ifdef DO_INDEXED_VB
//TempCode JON 30Oct00 			sVertex->identical=NULL;
//TempCode JON 30Oct00 #endif
        }
        else
        {
#ifdef _TEST_VERTEX_SHARING
            SetVertexCol( sVertex, curLF );
            if ( sVertex->color.all != lastDoPoint[num]->color.all )
                NOP;
#endif
            // right just copy over the point
            memcopy( sVertex, lastDoPoint[num], sizeof( SVertex ) );
#ifdef DO_INDEXED_VB
            sVertex->identical = lastDoPoint[ num ]->identical;
#endif
            lastDoPoint[ num ]->identical = sVertex;
        }
    }
    else
#endif
    {
        // transform as needed
//TempCode JON 30Oct00 #ifdef DO_INDEXED_VB
//TempCode JON 30Oct00 		sVertex->identical=NULL;
//TempCode JON 30Oct00 #endif
        // is this a landscape texture
        if ( flags&LANDSCAPE_TEXTURE )
        {
            // yes
            switch ( flags&TEXTURE_COUNT_MASK )
            {
            case 3:
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING
//DeadCode JON 30Oct00
//DeadCode JON 30Oct00 				if ( flags&TEXTURE_COORDS )
//DeadCode JON 30Oct00 				{ // no need to transform
//DeadCode JON 30Oct00 					memcopy( &sVertex->tu, &lastDoPoint[ num ]->tu, 2*sizeof( D3DVALUE ) );
//DeadCode JON 30Oct00 				} else
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 				{
//DeadCode JON 30Oct00 //DeadCode JON 4Sep00 					sVertex->tu = landscapeTextScaleX*D3DVALUE(sVertex->ix)+landscapeTextOffsetX;
//DeadCode JON 30Oct00 //DeadCode JON 4Sep00 					sVertex->tv = landscapeTextScaleY*D3DVALUE(sVertex->iy)+landscapeTextOffsetY;
//DeadCode JON 30Oct00 					sVertex->tu = landscapeTextScale*D3DVALUE(sVertex->ix)+landscapeTextOffset;
//DeadCode JON 30Oct00 					sVertex->tv = landscapeTextScale*D3DVALUE(sVertex->iy)+landscapeTextOffset;
//DeadCode JON 30Oct00 				}
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING
//DeadCode JON 30Oct00 				if ( flags&TEXTURE1_COORDS )
//DeadCode JON 30Oct00 				{ // no need to transform
//DeadCode JON 30Oct00 					memcopy( &sVertex->tu1, &lastDoPoint[ num ]->tu1, 2*sizeof( D3DVALUE ) );
//DeadCode JON 30Oct00 				} else
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 				{
//DeadCode JON 30Oct00 					sVertex->tu1=hLastMaterial.tsW[1]*sVertex->ix1;
//DeadCode JON 30Oct00 					sVertex->tv1=hLastMaterial.tsH[1]*sVertex->iy1;
//DeadCode JON 30Oct00 				}
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING
//DeadCode JON 30Oct00 				if ( flags&TEXTURE2_COORDS )
//DeadCode JON 30Oct00 				{ // no need to transform
//DeadCode JON 30Oct00 					memcopy( &sVertex->tu2, &lastDoPoint[ num ]->tu2, 2*sizeof( D3DVALUE ) );
//DeadCode JON 30Oct00 				} else
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 				{
//DeadCode JON 30Oct00 					sVertex->tu2=hLastMaterial.tsW[2]*sVertex->ix2;
//DeadCode JON 30Oct00 					sVertex->tv2=hLastMaterial.tsH[2]*sVertex->iy2;
//DeadCode JON 30Oct00 				}
//DeadCode JON 30Oct00 				break;
            case 2:
#ifndef _NO_VERTEX_SHARING
                if ( flags&TEXTURE_COORDS )
                {
                    // no need to transform
                    memcopy( &sVertex->tu, &lastDoPoint[ num ]->tu, 2*sizeof( D3DVALUE ) );
                }
                else
#endif
                {
//DeadCode JON 4Sep00 					sVertex->tu = landscapeTextScaleX*D3DVALUE(sVertex->ix)+landscapeTextOffsetX;
//DeadCode JON 4Sep00 					sVertex->tv = landscapeTextScaleY*D3DVALUE(sVertex->iy)+landscapeTextOffsetY;
                    sVertex->tu = landscapeTextScale*D3DVALUE(sVertex->ix)+landscapeTextOffset;
                    sVertex->tv = landscapeTextScale*D3DVALUE(sVertex->iy)+landscapeTextOffset;
                }
#ifndef _NO_VERTEX_SHARING
                if ( flags&TEXTURE1_COORDS )
                {
                    // no need to transform
                    memcopy( &sVertex->tu1, &lastDoPoint[ num ]->tu1, 2*sizeof( D3DVALUE ) );
                }
                else
#endif
                {
                    sVertex->tu1=hLastMaterial.tsW[1]*sVertex->ix1;
                    sVertex->tv1=hLastMaterial.tsH[1]*sVertex->iy1;
                }
                break;
            case 1:
#ifndef _NO_VERTEX_SHARING
                if ( flags&TEXTURE_COORDS )
                {
                    // no need to transform
                    memcopy( &sVertex->tu, &lastDoPoint[ num ]->tu, 2*sizeof( D3DVALUE ) );
                }
                else
#endif
                {
//DeadCode JON 4Sep00 					sVertex->tu = landscapeTextScaleX*D3DVALUE(sVertex->ix)+landscapeTextOffsetX;
//DeadCode JON 4Sep00 					sVertex->tv = landscapeTextScaleY*D3DVALUE(sVertex->iy)+landscapeTextOffsetY;
                    sVertex->tu = landscapeTextScale*D3DVALUE(sVertex->ix)+landscapeTextOffset;
                    sVertex->tv = landscapeTextScale*D3DVALUE(sVertex->iy)+landscapeTextOffset;
                }
                break;
            case 0:
                break;// this is possible when rendering to a tile with a plain colour...
                NODEFAULT;
            }
        }
        else
        {
            // not a landscape texture
            switch ( flags&TEXTURE_COUNT_MASK )
            {
            case 3:
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING
//DeadCode JON 30Oct00 				if ( flags&TEXTURE_COORDS )
//DeadCode JON 30Oct00 				{ // no need to transform
//DeadCode JON 30Oct00 					memcopy( &sVertex->tu, &lastDoPoint[ num ]->tu, 2*sizeof( D3DVALUE ) );
//DeadCode JON 30Oct00 				} else
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 				{
//DeadCode JON 30Oct00 					sVertex->tu=hLastMaterial.tsW[0]*sVertex->ix;
//DeadCode JON 30Oct00 					sVertex->tv=hLastMaterial.tsH[0]*sVertex->iy;
//DeadCode JON 30Oct00 				}
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING
//DeadCode JON 30Oct00 				if ( flags&TEXTURE1_COORDS )
//DeadCode JON 30Oct00 				{ // no need to transform
//DeadCode JON 30Oct00 					memcopy( &sVertex->tu1, &lastDoPoint[ num ]->tu1, 2*sizeof( D3DVALUE ) );
//DeadCode JON 30Oct00 				} else
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 				{
//DeadCode JON 30Oct00 					sVertex->tu1=hLastMaterial.tsW[1]*sVertex->ix1;
//DeadCode JON 30Oct00 					sVertex->tv1=hLastMaterial.tsH[1]*sVertex->iy1;
//DeadCode JON 30Oct00 				}
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING
//DeadCode JON 30Oct00 				if ( flags&TEXTURE2_COORDS )
//DeadCode JON 30Oct00 				{ // no need to transform
//DeadCode JON 30Oct00 					memcopy( &sVertex->tu2, &lastDoPoint[ num ]->tu2, 2*sizeof( D3DVALUE ) );
//DeadCode JON 30Oct00 				} else
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 				{
//DeadCode JON 30Oct00 					sVertex->tu2=hLastMaterial.tsW[2]*sVertex->ix2;
//DeadCode JON 30Oct00 					sVertex->tv2=hLastMaterial.tsH[2]*sVertex->iy2;
//DeadCode JON 30Oct00 				}
//DeadCode JON 30Oct00 				break;
            case 2:
#ifndef _NO_VERTEX_SHARING
                if ( flags&TEXTURE_COORDS )
                {
                    // no need to transform
                    memcopy( &sVertex->tu, &lastDoPoint[ num ]->tu, 2*sizeof( D3DVALUE ) );
                }
                else
#endif
                {
                    sVertex->tu=hLastMaterial.tsW[0]*sVertex->ix;
                    sVertex->tv=hLastMaterial.tsH[0]*sVertex->iy;
                }
#ifndef _NO_VERTEX_SHARING
                if ( flags&TEXTURE1_COORDS )
                {
                    // no need to transform
                    memcopy( &sVertex->tu1, &lastDoPoint[ num ]->tu1, 2*sizeof( D3DVALUE ) );
                }
                else
#endif
                {
                    sVertex->tu1=hLastMaterial.tsW[1]*sVertex->ix1;
                    sVertex->tv1=hLastMaterial.tsH[1]*sVertex->iy1;
                }
                break;
            case 1:
#ifndef _NO_VERTEX_SHARING
                if ( flags&TEXTURE_COORDS )
                {
                    // no need to transform
                    memcopy( &sVertex->tu, &lastDoPoint[ num ]->tu, 2*sizeof( D3DVALUE ) );
                }
                else
#endif
                {
                    sVertex->tu=hLastMaterial.tsW[0]*sVertex->ix;
                    sVertex->tv=hLastMaterial.tsH[0]*sVertex->iy;
                }
                break;
            case 0:
                break;
                NODEFAULT;
            }
        }

#ifndef _NO_VERTEX_SHARING
        // do we need to transform?
        if ( flags&WORLD_COORDS )
        {
            // no the previous ones are valid
            memcopy( &sVertex->x, &lastDoPoint[num]->x, 3*sizeof( D3DVALUE ) );
            sVertex->hw = lastDoPoint[num]->hw;
        }
        else
#endif
        {
            // yeah
            sVertex->Transform( &combinedMatrix );
//DeadCode JON 19Jun00 			if ( (flags&DO_SW_FOG) // we need to set the fog
//DeadCode JON 19Jun00 				&& (flags&LIGHT_NORMAL) && (flags&TEXTURE_COUNT_MASK) != 0 )  // the light/colour won't change
//DeadCode JON 19Jun00 			{
//DeadCode JON 19Jun00 //				ULong index=ULong(1023.f*pp->hw/farZPlane);
//DeadCode JON 19Jun00 //				pp->specular&=0x00FFFFFF;
//DeadCode JON 19Jun00 //				pp->specular|=ULong(fogTable[index])<<24;
//DeadCode JON 19Jun00 				SetColAlpha( sVertex->specular, fogTable[ F2UL_Round( 1023.f*sVertex->hw/farZPlane) ] );
//DeadCode JON 19Jun00 			}
        }

        // has the lighting information changed (and is it a textured poly? )
#ifndef _NO_VERTEX_SHARING
        if ( ((flags&LIGHT_NORMAL) && (flags&TEXTURE_COUNT_MASK) != 0 ) )
        {
            // no change, and not plain colour
#ifdef _TEST_VERTEX_SHARING
            SetVertexCol( sVertex, curLF );
            if ( sVertex->color.all != lastDoPoint[num]->color.all )
                NOP;
#endif
//DeadCode JON 2Oct00 			memcopy( &sVertex->nx, &lastDoPoint[num]->nx, 3*sizeof( D3DVALUE ) );
            sVertex->color = lastDoPoint[num]->color;
            sVertex->specular = lastDoPoint[num]->specular;
            if ( (flags&DO_SW_FOG) && !(flags&WORLD_COORDS) )
            {
                // we need to recalculate the fog value though
                SetColAlpha( sVertex->specular, fogTable[ (0x3FF&F2UL_Round( sVertex->hw*fogMul )) ] );
            }
        }
        else
        {
            if ( (flags&TEXTURE_COUNT_MASK) == 0 )
            {
                sVertex->info.addToFlags( PLAINCOL_FLAG );
            }
#else
        {
#endif
            SetVertexCol( sVertex, curLF );
            if ( flags&DO_SW_FOG )
            {
                SetColAlpha( sVertex->specular, fogTable[ (0x3FF&F2UL_Round( sVertex->hw*fogMul )) ] );
            }
        }


        if ( (flags&DO_CLIP) )
        {
            //yes
            sVertex->clipcode=ClipCodeFBLRTB(sVertex);
        }
        else
        {
            // do 2d clip
            sVertex->clipcode=ClipCode2D(sVertex);
        }
    }
}

//#pragma message (__HERE__ "inline me" )
inline HRESULT Lib3D::PrepareForClipping( void  )
{
#ifdef	_SHAPE_DEBUG_
    noPolysDebug++;
#endif

#ifndef NDEBUG
    if (!insidePoly)
    {
        INT3;
        return DDERR_GENERIC;
    }
#endif

    SVertex *sVertex=currentPoly->pVertexList;

#ifndef NO_HARD_TNL
    if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
    {
        if (fCombineMatrices)
            if ( (hr=TNLUploadMatrixes()) !=S_OK )
                return hr;

        SPolygon *sPolygon = (SPolygon*)(ULong(polyVertArray)-sizeof(SPolygon));
        sPolygon->lightMode = lightflag;

        if ( sPolygon->material.isMasked!=0 && sPolygon->material.f!=0 )
        {
            if (addNewTransMat)
                CombineTranspMat();
            sPolygon->transMat=transMatPos;
            sPolygon->projMat=projMatStackPos;
            TnlTransSetPolyZ(sPolygon);
            ADD_POLYGON(transparentPolys,sPolygon);
        }
        else
        {
//DeadCode JON 21Aug00 			ADD_POLYGON(*texturedPolysP,sPolygon);
            ADD_POLYGON(texturedPolys,sPolygon);
        }

        polyVertCount=0xFFFFFFFF;
        return S_OK;
    }
#endif

    if (fCombineMatrices) CombineMatrices();
    if (updateLightVecs) UpdateLightVecs();

#ifdef _INVERT_SHAPE_NORMALS
    if ( !hLastMaterial.isLand )
    {
        SVertex* curPoint = currentPoly->pVertexList;
        for (int q=0; q<currentPoly->vertexcount; q++)
        {
            static D3DVALUE xscale = -1.f;
            static D3DVALUE yscale = -1.f;
            static D3DVALUE zscale = -1.f;

            static int xtrans = 0;
            static int ytrans = 1;
            static int ztrans = 2;

            D3DVALUE tmp[3];
            tmp[0] = curPoint->nx;
            tmp[1] = curPoint->ny;
            tmp[2] = curPoint->nz;

            curPoint->nx=tmp[xtrans]*xscale;
            curPoint->ny=tmp[ytrans]*yscale;
            curPoint->nz=tmp[ztrans]*zscale;
            curPoint++;
        }
    }
#endif

#ifdef _INVERT_LAND_NORMALS
    if ( hLastMaterial.isLand )
    {
        SVertex* curPoint = currentPoly->pVertexList;
        for (int q=0; q<currentPoly->vertexcount; q++)
        {
            static D3DVALUE xscale = 1.f;
            static D3DVALUE yscale = 1.f;
            static D3DVALUE zscale = -1.f;

            static int xtrans = 0;
            static int ytrans = 1;
            static int ztrans = 2;

            D3DVALUE tmp[3];
            tmp[0] = curPoint->nx;
            tmp[1] = curPoint->ny;
            tmp[2] = curPoint->nz;

            curPoint->nx=tmp[xtrans]*xscale;
            curPoint->ny=tmp[ytrans]*yscale;
            curPoint->nz=tmp[ztrans]*zscale;
            curPoint++;
        }
    }
#endif

#ifdef _DRAW_AXIS
    if (lightflag==LF_LIGHTING)
    {
        DoPointStruc end;
        HMATERIAL hM=hLastMaterial;

        SVertex* curPoint = currentPoly->pVertexList;
        for (int q=0; q<currentPoly->vertexcount; q++)
        {
            memcopy( &end, curPoint, sizeof( R3DVERTEX ) );
            static D3DVALUE size = 30.f;
            end.incPosX( (size) );
            DrawLine(HMATERIAL(96),*curPoint, end); // yellow line, x axis
            end.incPosX( -(size) );

//TempCode JON 13Sep00 			end.incPosY( (size) );
//TempCode JON 13Sep00 			DrawLine(HMATERIAL(127),*curPoint, end); // red line, y axis
//DeadCode JON 13Sep00 			end.incPosY( -(size) );

            end.incPosZ( (size) );
            DrawLine(HMATERIAL(144),*curPoint, end); // blue line, z axis

            curPoint++;
        }
        hLastMaterial=hM;
    }
#endif


#ifdef _DRAWNORMALS
    {
        static bool reallyDrawNormals = true;
        if (lightflag==LF_LIGHTING && reallyDrawNormals )
        {
            // draw in normal
            DoPointStruc end;
            HMATERIAL hM=hLastMaterial;

            SVertex* curPoint = currentPoly->pVertexList;
            for (int q=0; q<currentPoly->vertexcount; q++)
            {
                memcopy( &end, curPoint, sizeof( R3DVERTEX ) );
                static D3DVALUE xsize = 300.f;
                static D3DVALUE ysize = 300.f;
                static D3DVALUE zsize = 300.f;
                end.incPos( curPoint->nx*(xsize),curPoint->ny*(ysize), curPoint->nz*(zsize) );
                DrawLine(HMATERIAL(120),*curPoint, end);

                curPoint++;
            }
            hLastMaterial=hM;
        }
    }
#endif

#ifdef _DRAW_SPEC_H
    {
        static bool reallyDrawSpecH = true;
        if (lightflag==LF_LIGHTING && reallyDrawSpecH)
        {
            //draw in direction to sun ( only works on the ground and objects wiv no object twist )
            DoPointStruc end;
            HMATERIAL hM=hLastMaterial;

            SVertex* curPoint = currentPoly->pVertexList;
            for (int q=0; q<currentPoly->vertexcount; q++)
            {
                memcopy( &end, curPoint, sizeof( R3DVERTEX ) );
                static D3DVALUE size = 30.f;
                end.incPos( halfSunEye.x*(size),halfSunEye.y*(size), halfSunEye.z*(size) );
                DrawLine(HMATERIAL(191),*curPoint, end);
                curPoint++;
            }
            hLastMaterial=hM;
        }
    }
#endif

#ifdef _DRAWLIGHTVEC
    {
        static bool reallyDrawLightVecs = true;
        if (lightflag==LF_LIGHTING && reallyDrawLightVecs)
        {
            //draw in direction to sun ( only works on the ground and objects wiv no object twist )
            DoPointStruc end;
            HMATERIAL hM=hLastMaterial;

            SVertex* curPoint = currentPoly->pVertexList;
            for (int q=0; q<currentPoly->vertexcount; q++)
            {
                memcopy( &end, curPoint, sizeof( R3DVERTEX ) );
                static D3DVALUE size = 30.f;
                end.incPos( sunTX*(size),sunTY*(size), sunTZ*(size) );
                DrawLine(HMATERIAL(4),*curPoint, end);
                curPoint++;
            }
            hLastMaterial=hM;
        }
    }
#endif


    LIGHTFLAG curLF = lightflag;
//	D3DCOLOR matCol;
    // deal wiv global alpha info
    if ( currentPoly->material.f != 0 )
        currentPoly->material.c = globAlpha;

    if ( hLastMaterial.f == 0 && (lightflag != LF_VERTEX && lightflag != LF_FONT) )
    {
        curCol = RGB_MAKE(	paletteTable[3*currentPoly->material.c],	//RED
                            paletteTable[3*currentPoly->material.c+1],	//GREEN
                            paletteTable[3*currentPoly->material.c+2]);//BLUE
        // would like to do the following but byte order is wrong
        //TempCode JON 15Jun00 		curCol = *( (ULong*)(paletteTable+3*currentPoly->material.c-1) );
        //TempCode JON 15Jun00 		curCol &= 0x00FFFFFF;
        curLF = LIGHTFLAG(curLF + LF_MAPCOLBIT);
    }
//DeadCode JON 15Jun00 	else
//DeadCode JON 15Jun00 	{
//DeadCode JON 15Jun00 		matCol = COL_NULL;
//DeadCode JON 15Jun00 	}

#ifndef NDEBUG
    if ( hLastMaterial.f > 3 ) // illegal texture count
        INT3;
#endif
//DeadCode JON 4Sep00 	ULong textureTypeFlags = hLastMaterial.f;
    ULong textureTypeFlags = curMatTextureTypeFlags;
//DeadCode JON 4Sep00 	if ( hLastMaterial.isLand )
//DeadCode JON 4Sep00 	{
//DeadCode JON 4Sep00 		textureTypeFlags |= LANDSCAPE_TEXTURE;
//DeadCode JON 4Sep00
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 #pragma message ( __HERE__ "to optimize move this to set landscape material section" )
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		SLong *numbers[8] = {	&num1024Textures,	&num512Textures,
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 								&num256Textures,	&num128Textures,
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 								&num64Textures,		&num32Textures,
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 								&num16Textures,		&num8Textures };
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		SLong index;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		index=SLong(hLastMaterial.isLand^0xFFFFFFFFUL);
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		for (int i=0;i<8;i++)
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		{
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 			if (index<*numbers[i])
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 			{
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 				index=i;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 				break;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 			}
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 			index-=*numbers[i];
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		}
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		D3DVALUE pixelSH;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		//landscapeTextScaleX = scW;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		pixelSH=(index==0)?.125f:(index==1)?.25f:(index==2)?.5f:D3DVALUE(1<<(index-3));
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		landscapeTextOffsetX=hLastMaterial.tsW[0];
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		landscapeTextScaleX=1.f/landscapeTextOffsetX;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		landscapeTextOffsetX*=pixelSH;	//*.5f;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		landscapeTextScaleX=(landscapeTextScaleX-2*pixelSH)/(landscapeTextScaleX*landscapeTextScaleX);
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		landscapeTextOffsetY=landscapeTextOffsetX;
//DeadCode JON 4Sep00 //DeadCode JON 15Jun00 		landscapeTextScaleY=landscapeTextScaleX;
//DeadCode JON 4Sep00 	}

//DeadCode JON 4Sep00 	if (flags&F_VERTEXFOG)
//DeadCode JON 4Sep00 	{
//DeadCode JON 4Sep00 		textureTypeFlags+=DO_SW_FOG;
//DeadCode JON 4Sep00 	}

//#pragma warnmsg ( "put me back" )
//	if (renderMode==HINT_2DRENDER)// || (flags&F_NOCLIPPING)!=0)
//DeadCode JON 25Sep00 	if ((flags&F_NOCLIPPING)!=0)
    if (renderMode==HINT_2DRENDER)
    {
        // 2D clipping...
        for (int i=currentPoly->vertexcount; i!=0; i--)
        {
#ifndef _NO_VERTEX_SHARING
            int num = sVertex->info.getDoPointNum();

//DeadCode JON 2Oct00 #ifdef _TEST_VERTEX_SHARING
//DeadCode JON 2Oct00 			SVertex toCompare;
//DeadCode JON 2Oct00 			memcopy( &toCompare, sVertex, sizeof( SVertex ) );
//DeadCode JON 2Oct00 		    InlineVertexTransform( &toCompare, ALL_INVALID+textureTypeFlags, curLF );
//DeadCode JON 2Oct00 #endif

            ULong flags = sVertex->info.getFlags();
            if ( num == 0 )
            {
                flags=ALL_INVALID;
            }
            else
            {
                flags&=~(
                           (
//DeadCode JON 20Sep00 							  (
//DeadCode JON 20Sep00 								( ( lightModeFlag^lastDoPoint[ num ]->info.getFlags() ) >>LIGHTMODESHIFT ) //has the lightcols changed
//DeadCode JON 20Sep00 							  )
//DeadCode JON 20Sep00 						      & LIGHT_NORMAL
                               (lastDoPoint[ num ]->info.getLightModeCount() == lightModeCount)?0:LIGHT_NORMAL
                           ) |
                           (
                               SetToTopBit( lastDoPoint[ num ]->info.getFlags() )&(ALL_TEXT_COORDS|LIGHT_NORMAL)
                               // if the last was plain colour then set all textcoords and light normal
                           )
                       );
//DeadCode JON 27Jul00 				flags&=~(
//DeadCode JON 27Jul00 						  (
//DeadCode JON 27Jul00 							( ( lightModeFlag^lastDoPoint[ num ]->info.getFlags() ) >>LIGHTMODESHIFT ) | //has the lightcols changed
//DeadCode JON 27Jul00 							( lastDoPoint[num]->info.getFlags()>>PLAINCOLSHIFT ) // was the last plain col
//DeadCode JON 27Jul00 						  )
//DeadCode JON 27Jul00 					      & LIGHT_NORMAL
//DeadCode JON 27Jul00 					);
            }
#else
            ULong flags=ALL_INVALID;
#endif
            flags+=textureTypeFlags; // add in the texture count and other stuff

            InlineVertexTransform( sVertex, flags, curLF );

//DeadCode JON 2Oct00 #ifdef _TEST_VERTEX_SHARING
//DeadCode JON 2Oct00 			if ( !MemCmp( sVertex, &toCompare, sizeof( SVertex ) ) )
//DeadCode JON 2Oct00 				NOP;
//DeadCode JON 2Oct00 #endif

#ifndef _NO_VERTEX_SHARING
            lastDoPoint[ num ] = sVertex;
            sVertex->info.setLightModeCount( lightModeCount );
#endif

            // link the poly...
            sVertex->pNext = sVertex+1;
            // set the lightmode stuff

            currentPoly->andcode&=sVertex->clipcode;
            currentPoly->orcode|=sVertex->clipcode;

            // iterate
            sVertex=sVertex->pNext;
        }
//TempCode JON 25Sep00 		currentPoly->andcode=0;
// this is already the case...		currentPoly->orcode=0;
    }
    else
    {
        // ----------------------- do 3d clipping ----------------------------------------
        textureTypeFlags |= DO_CLIP;
        for (int i=currentPoly->vertexcount; i!=0; i--)
        {
#ifndef _NO_VERTEX_SHARING
            int num = sVertex->info.getDoPointNum();

//DeadCode JON 26Oct00 #pragma warnmsg ( "remove me" )
//DeadCode JON 26Oct00 			if ( num == 38 )
//DeadCode JON 26Oct00 				NOP;


#ifdef _TEST_VERTEX_SHARING
            SVertex toCompare, preCompare;
            memcopy( &toCompare, sVertex, sizeof( SVertex ) );
            memcopy( &preCompare, sVertex, sizeof( SVertex ) );
            InlineVertexTransform( &toCompare, ALL_INVALID+textureTypeFlags, curLF );
#endif

            ULong flags = sVertex->info.getFlags();
            if ( num == 0 )
            {
                flags=ALL_INVALID;
            }
            else
            {


//TempCode JON 30Jun00 				ULong last = lastDoPoint[ num ]->info.getFlags();
//TempCode JON 30Jun00 				ULong lastMsk = last&LIGHTMODE_FLAG;
//TempCode JON 30Jun00 				ULong lmFlag = LIGHTMODE_FLAG;
//TempCode JON 30Jun00 				ULong lmShift = LIGHTMODESHIFT;
//TempCode JON 30Jun00 				ULong tmp = ((lightModeFlag^last)&LIGHTMODE_FLAG)>>LIGHTMODESHIFT;
//TempCode JON 30Jun00 				if ( lastMsk )
//TempCode JON 30Jun00 				{
//TempCode JON 30Jun00 					NOP;
//TempCode JON 30Jun00 				} else
//TempCode JON 30Jun00 				{
//TempCode JON 30Jun00 					NOP;
//TempCode JON 30Jun00 				}
//TempCode JON 30Jun00 				flags&=~tmp;
//TempCode JON 30Jun00
//TempCode JON 30Jun00 				ULong pcFlag = (last>>PLAINCOLSHIFT)&LIGHT_NORMAL;

//TempCode JON 30Jun00 				flags&=~( ( (lightModeFlag^lastDoPoint[ num ]->info.getFlags())&LIGHTMODE_FLAG )>>LIGHTMODESHIFT );
//TempCode JON 30Jun00 				flags&=~( ( ( lightModeFlag^lastDoPoint[ num ]->info.getFlags() )>>LIGHTMODESHIFT ) & LIGHT_NORMAL );

                flags&=~(
                           (
//DeadCode JON 20Sep00 							  (
//DeadCode JON 20Sep00 								( ( lightModeFlag^lastDoPoint[ num ]->info.getFlags() ) >>LIGHTMODESHIFT ) | //has the lightcols changed
//DeadCode JON 20Sep00 								( ( lightModeFlag^lastDoPoint[ num ]->info.getFlags() ) >>LIGHTMODESHIFT1 ) | //has the lightcols changed
//DeadCode JON 20Sep00 								( ( lightModeFlag^lastDoPoint[ num ]->info.getFlags() ) >>LIGHTMODESHIFT2 ) //has the lightcols changed
//DeadCode JON 20Sep00 							  )
//DeadCode JON 20Sep00 						      & LIGHT_NORMAL
                               (lastDoPoint[ num ]->info.getLightModeCount() == lightModeCount)?0:LIGHT_NORMAL
                           ) |
                           (
                               SetToTopBit( lastDoPoint[ num ]->info.getFlags() )&(ALL_TEXT_COORDS|LIGHT_NORMAL)
                               // if the last was plain colour then set all textcoords and light normal
                           )
                       );

            }
#else
//DeadCode JON 26Oct00 #pragma warnmsg ( "remove me" )
//DeadCode JON 26Oct00 			int num = sVertex->info.getDoPointNum();
//DeadCode JON 26Oct00 			if ( num == 38 )
//DeadCode JON 26Oct00 				NOP;

            ULong flags=ALL_INVALID;
#endif
            flags+=textureTypeFlags; // add in the texture count and other stuff

            InlineVertexTransform( sVertex, flags, curLF );

#ifdef _TEST_VERTEX_SHARING
            if (
//TempCode JON 2Oct00 					(	sVertex->x != toCompare.x ||
//TempCode JON 2Oct00 						sVertex->y != toCompare.y ||
//TempCode JON 2Oct00 						sVertex->z != toCompare.z ||
//TempCode JON 26Oct00 						sVertex->color.all != toCompare.color.all //||
//TempCode JON 2Oct00 						sVertex->specular.all != toCompare.specular.all ||
//TempCode JON 2Oct00 						sVertex->hw != toCompare.hw ||
//TempCode JON 2Oct00 						sVertex->clipcode != toCompare.clipcode
//TempCode JON 2Oct00 					) ||
//TempCode JON 2Oct00 					(	hLastMaterial.f >=1 &&
//TempCode JON 2Oct00 						( sVertex->tu != toCompare.tu || sVertex->tv != toCompare.tv )
//TempCode JON 2Oct00 					) ||
                (	hLastMaterial.f >=2 &&
                    ( sVertex->tu1 != toCompare.tu1 || sVertex->tv1 != toCompare.tv1 )
                )
//TempCode JON 26Oct00 					||
//TempCode JON 2Oct00 					(	hLastMaterial.f >=3 &&
//TempCode JON 2Oct00 						( sVertex->tu2 != toCompare.tu2 || sVertex->tv2 != toCompare.tv2 )
//TempCode JON 2Oct00 					)
            )
            {
//DeadCode JON 20Sep00  				ULong lmFlag = LIGHTMODE_FLAG;
//DeadCode JON 20Sep00 				ULong lmFlag1 = LIGHTMODE_FLAG1;
//DeadCode JON 20Sep00 				ULong lmFlag2 = LIGHTMODE_FLAG2;
//DeadCode JON 20Sep00 				ULong pcFlag = PLAINCOL_FLAG;

                NOP;

                // right have another go to be stepped through...
                memcopy( sVertex, &preCompare, sizeof( SVertex ) );
                InlineVertexTransform( sVertex, flags, curLF );
            }
#endif

            currentPoly->andcode&=sVertex->clipcode;
            currentPoly->orcode|=sVertex->clipcode;
#ifndef _NO_VERTEX_SHARING
            lastDoPoint[ num ] = sVertex;
            // set the lightmode stuff
            sVertex->info.clearLightModeFlags();
//DeadCode JON 20Sep00 			sVertex->info.addToFlags( lightModeFlag );
            sVertex->info.setLightModeCount( lightModeCount );
#endif
            // link the poly...
            sVertex->pNext = sVertex+1;

            // iterate
            sVertex=sVertex->pNext;
        }
    }

    // make the poly linking circular
    (sVertex-1)->pNext = currentPoly->pVertexList;

    return S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndFan
//Author		Paul.
//Date			Thu 25 Nov 1999
//
//------------------------------------------------------------------------------
//#pragma message ( __HERE__ "end fan" )
HRESULT Lib3D::EndFan()
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    if ( (lastError = PrepareForClipping()) != S_OK )
        return lastError;

#ifndef _THROW_AWAY_CLIPPED
    if (currentPoly->andcode==0) // is any of this visible?
#else
    if ( currentPoly->orcode==0 && currentPoly->andcode==0 )
#endif
    {
//DeadCode JON 28Oct00 		if (	currentPoly->orcode!=0 &&
//DeadCode JON 28Oct00 				( GuardBandClipTest(currentPoly) || (currentPoly->orcode&~CLIP_LRTB) )
//DeadCode JON 28Oct00 			) // is any of the poly clipped
        if ( currentPoly->orcode!=0 ) // is any of the poly clipped
        {
            if (renderMode==HINT_2DRENDER)
            {
                // 2d clipping
#ifndef NO_CLEVER_FAN_CLIP
                if ( currentPoly->vertexcount < 4 )
#endif
                {
                    // it's not really a fan at all
                    GenericPolyClip2D(currentPoly);
                    if (currentPoly->vertexcount>2)
                    {
                        AddPolyToList( currentPoly );
                    }
                }
#ifndef NO_CLEVER_FAN_CLIP
                else
                {
                    // this stuff assumes the fan verticies are in consecutive order, mutual first
                    SVertex* vert2 = currentPoly->pVertexList+1;
                    SVertex* vert1;

                    for ( int tri = currentPoly->vertexcount-2; tri !=0; tri-- ) // loop thru triangles in fan
                    {
                        vert1 = vert2++;

                        SPolygon* newTri;
                        ALLOCATE_POLYGON_NOLINK(newTri,3);
//						newTri->material=currentPoly->material;

                        SVertex* newVert = newTri->pVertexList;

                        *newVert = currentPoly->pVertexList[0]; // the mutual vertex
                        newTri->andcode&=newVert->clipcode;
                        newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                        newVert->identical = NULL;
#endif
                        newVert->pNext = newVert+1;
                        newVert=newVert->pNext;

                        *newVert = *vert1; // first corner
                        newTri->andcode&=newVert->clipcode;
                        newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                        newVert->identical = NULL;
#endif
                        newVert->pNext = newVert+1;
                        newVert=newVert->pNext;

                        *newVert = *vert2; // second corner
                        newTri->andcode&=newVert->clipcode;
                        newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                        newVert->identical = NULL;
#endif
                        newVert->pNext = newTri->pVertexList; // make circular

                        if ( newTri->andcode == 0 )
                        {
                            if ( newTri->orcode != 0 )
                            {
                                GenericPolyClip2D( newTri );
                                if (newTri->vertexcount>2)
                                {
                                    AddPolyToList( newTri );
                                }
                            }
                            else
                                AddPolyToList( newTri );
                        }
//DEADCODE JON 05/06/00 						else
//DEADCODE JON 05/06/00 							DISCARD_POLYGON( newTri );
                    } // end of loop all triangles in fan

                } // end of can it be treated as a poly?
#endif
            }
            else
            {
                // 3d clipping
                if ( GuardBandClipTest(currentPoly) )
                {
#ifndef NO_CLEVER_FAN_CLIP
                    if ( currentPoly->vertexcount < 4 )
#endif
                    {
                        // it's not really a fan at all
                        GenericPolyClip(currentPoly);
                        if (currentPoly->vertexcount>2)
                        {
                            AddPolyToList( currentPoly );
                        }
                    }
#ifndef NO_CLEVER_FAN_CLIP
                    else
                    {
                        // this stuff assumes the fan verticies are in consecutive order, mutual first
                        SVertex* vert2 = currentPoly->pVertexList+1;
                        SVertex* vert1;

                        for ( int tri = currentPoly->vertexcount-2; tri !=0; tri-- ) // loop thru triangles in fan
                        {
                            vert1 = vert2++;

                            SPolygon* newTri;
                            ALLOCATE_POLYGON_NOLINK(newTri,3);
                            //						newTri->material=currentPoly->material;

                            SVertex* newVert = newTri->pVertexList;

                            *newVert = currentPoly->pVertexList[0]; // the mutual vertex
                            newTri->andcode&=newVert->clipcode;
                            newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                            newVert->identical = NULL;
#endif
                            newVert->pNext = newVert+1;
                            newVert=newVert->pNext;

                            *newVert = *vert1; // first corner
                            newTri->andcode&=newVert->clipcode;
                            newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                            newVert->identical = NULL;
#endif
                            newVert->pNext = newVert+1;
                            newVert=newVert->pNext;

                            *newVert = *vert2; // second corner
                            newTri->andcode&=newVert->clipcode;
                            newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                            newVert->identical = NULL;
#endif
                            newVert->pNext = newTri->pVertexList; // make circular

                            if ( newTri->andcode == 0 )
                            {
                                if ( newTri->orcode != 0 )
                                {
                                    GenericPolyClip( newTri );
                                    if (newTri->vertexcount>2)
                                    {
                                        AddPolyToList( newTri );
                                    }
                                }
                                else
                                    AddPolyToList( newTri );
                            }
//DEADCODE JON 05/06/00 						else
//DEADCODE JON 05/06/00 							DISCARD_POLYGON( newTri );
                        } // end of loop all triangles in fan

                    } // end of can it be treated as a poly?
#endif
                }
                else
                {
                    // only need to clip front and back...
#ifndef NO_CLEVER_FAN_CLIP
                    if ( currentPoly->vertexcount < 4 )
#endif
                    {
                        // it's not really a fan at all
                        PolyClipFrontBack(currentPoly);
                        if (currentPoly->vertexcount>2)
                        {
                            AddPolyToList( currentPoly );
                        }
                    }
#ifndef NO_CLEVER_FAN_CLIP
                    else
                    {
                        // this stuff assumes the fan verticies are in consecutive order, mutual first
                        SVertex* vert2 = currentPoly->pVertexList+1;
                        SVertex* vert1;

                        for ( int tri = currentPoly->vertexcount-2; tri !=0; tri-- ) // loop thru triangles in fan
                        {
                            vert1 = vert2++;

                            SPolygon* newTri;
                            ALLOCATE_POLYGON_NOLINK(newTri,3);
                            //						newTri->material=currentPoly->material;

                            SVertex* newVert = newTri->pVertexList;

                            *newVert = currentPoly->pVertexList[0]; // the mutual vertex
                            newTri->andcode&=newVert->clipcode;
                            newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                            newVert->identical = NULL;
#endif
                            newVert->pNext = newVert+1;
                            newVert=newVert->pNext;

                            *newVert = *vert1; // first corner
                            newTri->andcode&=newVert->clipcode;
                            newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                            newVert->identical = NULL;
#endif
                            newVert->pNext = newVert+1;
                            newVert=newVert->pNext;

                            *newVert = *vert2; // second corner
                            newTri->andcode&=newVert->clipcode;
                            newTri->orcode|=newVert->clipcode;
#ifdef DO_INDEXED_VB
                            newVert->identical = NULL;
#endif
                            newVert->pNext = newTri->pVertexList; // make circular

                            if ( newTri->andcode == 0 )
                            {
                                if ( newTri->orcode != 0 )
                                {
                                    PolyClipFrontBack( newTri );
                                    if (newTri->vertexcount>2)
                                    {
                                        AddPolyToList( newTri );
                                    }
                                }
                                else
                                    AddPolyToList( newTri );
                            }
//DEADCODE JON 05/06/00 						else
//DEADCODE JON 05/06/00 							DISCARD_POLYGON( newTri );
                        } // end of loop all triangles in fan

                    } // end of can it be treated as a poly?
#endif
                }
            }
            // right, all done

#ifndef NDEBUG
            insidePoly = false;
#endif
            return S_OK;

        }

//DEADCODE JON 05/06/00 		if (currentPoly->vertexcount>2)
//DEADCODE JON 05/06/00 		{

        AddPolyToList( currentPoly );

//DEADCODE JON 05/06/00 		} else
//DEADCODE JON 05/06/00 		{
//DEADCODE JON 05/06/00 			DISCARD_POLYGON(currentPoly);
//DEADCODE JON 05/06/00 		}
    }
    else
    {
//		DISCARD_POLYGON(currentPoly);
    }
#ifndef NDEBUG
    insidePoly = false;
#endif

    return S_OK;
#endif
}

void Lib3D::GetViewPortDimensions( D3DVALUE &sx, D3DVALUE &sy, D3DVALUE &cx, D3DVALUE &cy )
{
    GetViewPort( sx, sy, cx, cy );
}

inline void Lib3D::GetViewPort( D3DVALUE &sx, D3DVALUE &sy, D3DVALUE &cx, D3DVALUE &cy )
{
    D3DVIEWPORT7 vp;
    pD3DDEV7->GetViewport(&vp);

    sx=D3DVALUE(vp.dwWidth>>1);
    sy=-D3DVALUE(vp.dwHeight>>1);

    cx=D3DVALUE(vp.dwX)+sx;
    cy=D3DVALUE(vp.dwY)-sy;

#ifdef _NO_CLIPPING_RESIZE
    if ( hCurrentRenderTarget.getType() != RENDERTARGET_LANDSCAPE )
    {
        sx/=(CLIP_RESIZE_FACTOR/2.0f);
        sy/=(CLIP_RESIZE_FACTOR/2.0f);
    }
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPolyToList
//Author		Jon.
//Date			Wed 17 May 2000
//				Brought out of endpoly & endfan to modularize, & make the fan clip easier
//------------------------------------------------------------------------------
//#pragma message ( __HERE__ "inline me" )
inline void Lib3D::AddPolyToList( SPolygon* sPolygon )
{
//DEADCODE JON 6/2/00 	D3DVALUE sx,sy;
//DEADCODE JON 6/2/00 	D3DVALUE cx,cy;
//DEADCODE JON 6/2/00 	GetViewPort( pD3DDEV7, sx, sy, cx, cy );

//	CALC_FOG(sPolygon);  // 2/3 if needed
    if (sPolygon->material.f==0)
    {

//DeadCode JON 14Jun00 		if ( globAlpha==0x00 )
        if ( globAlpha==0xFF )
        {
            // this is solid
            if (renderMode == HINT_3DRENDER)
            {
                //DEADCODE JON 5/25/00 			PROJECT(sPolygon,cx,cy,sx,sy);
                sPolygon->projectType = STANDARD_PROJECT+zBias;
            }
            else
            {
                sPolygon->projectType = PROJECT_2D;
                sPolygon->zDepth2d = zDepth2d;

                //TEMPCODE JON 5/25/00 			R3DVERTEX3 tmp[ 20 ];
                //TEMPCODE JON 5/25/00 			R3DVERTEX3 *tmp1 = sPolygon->CopyToVertexBuffer( &tmp[0] ,cx,cy,sx,sy );
                //TEMPCODE JON 5/25/00 			int num = tmp1-tmp;
                //TEMPCODE JON 5/25/00
                //TEMPCODE JON 5/25/00  			PROJECT_2DSETCOL(sPolygon,cx,cy,sx,sy);
            }

            if (plainPolyVCnt+sPolygon->vertexcount>=1024)
            {
                plainPolyVCnt=0;
                RenderPlainPolyList(plainPolys);
                plainPolys=NULL;
            }
            plainPolyVCnt+=sPolygon->vertexcount;
            ADD_POLYGON(plainPolys,sPolygon);
        }
        else
        {
            // transparent plain poly... oh what fun
//DeadCode JON 17Aug00 			sPolygon->material.materialFlags+=IS_ALPHA;
            if (renderMode == HINT_3DRENDER)
            {
                sPolygon->projectType = STANDARD_PROJECT+zBias;
                sPolygon->CalcTransZ(zFactor,tZBias_f);
            }
            else
            {
                sPolygon->projectType = PROJECT_2D;
                sPolygon->zDepth2d = zDepth2d;
                sPolygon->SetTrans2DZ(zBuffer2d);
            }
            ADD_POLYGON(transparentPolys,sPolygon);
        }
    }
//DeadCode JON 14Jun00 	else if (sPolygon->material.isMasked==0 && globAlpha==0x00 )
    else if (sPolygon->material.isMasked==0 && globAlpha==0xFF )
    {
        if (renderMode == HINT_3DRENDER)
        {
//DEADCODE JON 5/25/00 			PROJECT(sPolygon,cx,cy,sx,sy);
            sPolygon->projectType = STANDARD_PROJECT+zBias;
//DEADCODE JON 5/25/00 			R3DVERTEX3 tmp[ 20 ];
//DEADCODE JON 5/25/00 			R3DVERTEX3 *tmp1 = tmp;
//DEADCODE JON 5/25/00 			tmp1 = sPolygon->CopyToVertexBuffer( tmp1 ,cx,cy,sx,sy, zFactor );
//DEADCODE JON 5/25/00 			int num = tmp1-tmp;
//DEADCODE JON 5/25/00
//DEADCODE JON 5/25/00 			PROJECT(sPolygon,cx,cy,sx,sy);

        }
        else
        {
//DEADCODE JON 5/25/00 			PROJECT_2D(sPolygon,cx,cy,sx,sy);
            sPolygon->projectType = PROJECT_2D;
            sPolygon->zDepth2d = zDepth2d;
        }
//#pragma warnmsg( "re-instate" )
//DeadCode JON 21Aug00 		if (*textPolyVCntP+sPolygon->vertexcount>=1024)
        if (textPolyVCnt+sPolygon->vertexcount>=1024)
        {
//DeadCode JON 21Aug00 			*textPolyVCntP=0;
//DeadCode JON 21Aug00 			RenderPolyList(*texturedPolysP);
//DeadCode JON 21Aug00 			*texturedPolysP=NULL;
            textPolyVCnt=0;
            RenderPolyList(texturedPolys);
            texturedPolys=NULL;
        }
//DeadCode JON 21Aug00 		*textPolyVCntP+=sPolygon->vertexcount;
//DeadCode JON 21Aug00 		ADD_POLYGON(*texturedPolysP,sPolygon);
        textPolyVCnt+=sPolygon->vertexcount;
        ADD_POLYGON(texturedPolys,sPolygon);
        AddEdgeAliasing(sPolygon);
    }
    else
    {
        // transparent type
        if (renderMode == HINT_3DRENDER)
        {
//DEADCODE JON 5/25/00 			PROJECT_SETZ(sPolygon,cx,cy,sx,sy);
            sPolygon->projectType = STANDARD_PROJECT+zBias;
            sPolygon->CalcTransZ(zFactor,tZBias_f);
        }
        else
        {
//DEADCODE JON 5/25/00 			PROJECT_2D(sPolygon,cx,cy,sx,sy);
            sPolygon->projectType = PROJECT_2D;
            sPolygon->zDepth2d = zDepth2d;
            sPolygon->SetTrans2DZ(zBuffer2d);
//TEMPCODE JON 6/1/00 			ADD_POLYGON(transparentPolys,sPolygon);
        }
//DeadCode JON 17Aug00 		sPolygon->material.materialFlags+=IS_ALPHA;
        ADD_POLYGON(transparentPolys,sPolygon);
    }
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndPoly
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
//#pragma message (__HERE__ "end poly" )
HRESULT Lib3D::EndPoly()
{
    if ( hLastMaterial.p[0] == mirrorTexture.p[0] )
        NOP;
    if ( (lastError = PrepareForClipping()) != S_OK )
        return lastError;

#ifndef	_INVISIBLE_
    if (currentPoly->andcode==0)
    {
        if (currentPoly->orcode!=0)
        {

            if ( GuardBandClipTest(currentPoly) )
            {
                if (renderMode==HINT_2DRENDER)
                    GenericPolyClip2D(currentPoly);
                else
                    GenericPolyClip(currentPoly);

            }
            else if ( currentPoly->orcode&~CLIP_LRTB )
            {
                PolyClipFrontBack(currentPoly);
            }
        }

        if (currentPoly->vertexcount>2)
        {
            AddPolyToList( currentPoly );
        }
        else
        {
//			DISCARD_POLYGON(currentPoly);
        }
    }
    else
#endif
    {
//		DISCARD_POLYGON(currentPoly);
    }
#ifndef NDEBUG
    insidePoly = false;
#endif
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EndPolyR3DTLVERTEX deprec
//Author		Paul.
//Date			Fri 3 Dec 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 HRESULT Lib3D::EndPolyR3DTLVERTEX()
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	HRESULT hr;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (polyVertCount==0xFFFFFFFF)
//DEADCODE JON 5/19/00 		return DDERR_GENERIC;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (hLastMaterial.f)
//DEADCODE JON 5/19/00 		for (int i=hLastMaterial.f-1;i>=0;i--)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			R3DVERTEX *ptr=polyVertArray;
//DEADCODE JON 5/19/00 			D3DVALUE tsW=hLastMaterial.tsW[i];
//DEADCODE JON 5/19/00 			D3DVALUE tsH=hLastMaterial.tsH[i];
//DEADCODE JON 5/19/00 			for (DWORD j=polyVertCount;j!=0;j--)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				ptr->tu=tsW*D3DVALUE(ptr->ix);
//DEADCODE JON 5/19/00 				ptr->tv=tsH*D3DVALUE(ptr->iy);
//DEADCODE JON 5/19/00 				ptr++;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 	if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		if (fCombineMatrices)
//DEADCODE JON 5/19/00 			if ( (hr=TNLUploadMatrixes()) !=S_OK )
//DEADCODE JON 5/19/00 				return hr;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 		if ((hr=lpD3DVB7->Unlock())!=D3D_OK)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			CloseDown();
//DEADCODE JON 5/19/00 			return hr;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		hr=pD3DDEV7->DrawIndexedPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,0,polyVertCount,polyVerts,polyVertCount,0);
//DEADCODE JON 5/19/00 		if (hr!=D3D_OK)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			CloseDown();
//DEADCODE JON 5/19/00 			return hr;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		lpD3DVB7=NULL;
//DEADCODE JON 5/19/00 		polyVertCount=0xFFFFFFFF;
//DEADCODE JON 5/19/00 		return S_OK;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	D3DVIEWPORT7 vp;
//DEADCODE JON 5/19/00 	if ((hr=pD3DDEV7->GetViewport(&vp))!=D3D_OK)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		CloseDown();
//DEADCODE JON 5/19/00 		return hr;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	ULong *clipFlags=new ULong[polyVertCount<<3];
//DEADCODE JON 5/19/00 	ULong *polyIndex=new ULong[polyVertCount<<3];
//DEADCODE JON 5/19/00 	ULong *ccf=clipFlags;
//DEADCODE JON 5/19/00 	R3DTLVERTEX *pv=polyVertArrayTL;
//DEADCODE JON 5/19/00 	ULong orcode=0L;
//DEADCODE JON 5/19/00 	ULong andcode=0xFFFFFFFF;
//DEADCODE JON 5/19/00 	ULong outcode;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	vpDesc.left=D3DVALUE(vp.dwX);
//DEADCODE JON 5/19/00 	vpDesc.right=vpDesc.left+D3DVALUE(vp.dwWidth-1);
//DEADCODE JON 5/19/00 	vpDesc.top=D3DVALUE(vp.dwY);
//DEADCODE JON 5/19/00 	vpDesc.bottom=vpDesc.top+D3DVALUE(vp.dwHeight-1);
//DEADCODE JON 5/19/00 	for (SLong i=polyVertCount-1;i>=0;i--)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 	 	polyIndex[i]=i;
//DEADCODE JON 5/19/00 		if (pv->sx<vpDesc.left)			outcode=CLIP_LEFT;
//DEADCODE JON 5/19/00 		else if (pv->sx>vpDesc.right)	outcode=CLIP_RIGHT;
//DEADCODE JON 5/19/00 		else							outcode=0L;
//DEADCODE JON 5/19/00 		if (pv->sy<vpDesc.top)			outcode|=CLIP_TOP;
//DEADCODE JON 5/19/00 		else if (pv->sy>vpDesc.bottom)	outcode|=CLIP_BOTTOM;
//DEADCODE JON 5/19/00 		*ccf++=outcode;
//DEADCODE JON 5/19/00 		orcode|=outcode;
//DEADCODE JON 5/19/00 		andcode&=outcode;
//DEADCODE JON 5/19/00 		pv++;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (andcode==0L)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 	 	if (orcode!=0L)
//DEADCODE JON 5/19/00 			GenericPolyClip(polyVertArrayTL,clipFlags,polyVertCount,polyIndex);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 		if (polyVertCount>2)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			D3DVIEWPORT7 vp;
//DEADCODE JON 5/19/00 			lpD3DVB7=gpD3DVB7;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			R3DTLVERTEX *ptlv;
//DEADCODE JON 5/19/00 			hr=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&ptlv,NULL);
//DEADCODE JON 5/19/00 			if (hr!=D3D_OK)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				delete[]polyIndex;
//DEADCODE JON 5/19/00 				CloseDown();
//DEADCODE JON 5/19/00 				return hr;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 			ULong *index=polyIndex;
//DEADCODE JON 5/19/00 			for (i=polyVertCount;i!=0;i--)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				pv=polyVertArrayTL+*index++;
//DEADCODE JON 5/19/00 				*ptlv=*pv;
//DEADCODE JON 5/19/00 				ptlv++;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 			if ((hr=lpD3DVB7->Unlock())!=D3D_OK ||
//DEADCODE JON 5/19/00 				(hr=pD3DDEV7->DrawIndexedPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,0,polyVertCount,polyVerts,polyVertCount,0))!=D3D_OK)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				delete[]polyIndex;
//DEADCODE JON 5/19/00 				CloseDown();
//DEADCODE JON 5/19/00 				return hr;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 			lpD3DVB7=NULL;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	polyVertCount=0xFFFFFFFF;
//DEADCODE JON 5/19/00 	delete[]clipFlags;
//DEADCODE JON 5/19/00 	delete[]polyIndex;
//DEADCODE JON 5/19/00 	return S_OK;
//DEADCODE JON 5/19/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VertexSetCols
//Author		Jon.
//Date			Web 29 Mar 2000
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 void Lib3D::VertexSetCols( SVertex* sVertex, const D3DVERTEX* pv, const D3DCOLOR matCol )
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	switch ( lightflag )
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		case LF_SPECULAR: // please impement me
//DEADCODE JON 5/19/00 		case LF_LIGHTING:
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			D3DVALUE v=gLightScale*(gLightBase+DotProduct(pv->nx,pv->ny,pv->nz,sunTX,sunTY,sunTZ));
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			sVertex->color=lightingTable[F2UB_Clip(v)];
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			sVertex->specular=0x00000000;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		break;
//DEADCODE JON 5/19/00 		case LF_ALPHA:
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			D3DVALUE v=gLightScale*(gLightBase+DotProduct(pv->nx,pv->ny,pv->nz,sunTX,sunTY,sunTZ));
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			UByte alpha;
//DEADCODE JON 5/19/00 			alpha = 255 - F2UB_Clip(v);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			sVertex->color=0xAAFFFFFF;  // the AA is the alpha - about to be set
//DEADCODE JON 5/19/00 			SetColAlpha( sVertex->color, alpha );
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			sVertex->specular=0x00000000;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		break;
//DEADCODE JON 5/19/00 		case LF_AMBIENT:
//DEADCODE JON 5/19/00 			sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			// alternative glob alpha fix
//DEADCODE JON 5/19/00 			SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			sVertex->specular=0x00000000;
//DEADCODE JON 5/19/00 		break;
//DEADCODE JON 5/19/00 		case LF_VERTEX:
//DEADCODE JON 5/19/00 			sVertex->color = ((R3DVERTEX*)pv)->vertexCol;
//DEADCODE JON 5/19/00 		break;
//DEADCODE JON 5/19/00 		case LF_FONT:											//RJS 10May00
//DEADCODE JON 5/19/00 			sVertex->color=gFontColour;  // the AA is the alpha - about to be set
//DEADCODE JON 5/19/00 			SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/19/00 			sVertex->specular=0x00000000;
//DEADCODE JON 5/19/00 		break;
//DEADCODE JON 5/19/00 		case LF_LIGHTSOURCE:
//DEADCODE JON 5/19/00 		default:
//DEADCODE JON 5/19/00 			sVertex->color=0xAAFFFFFF;  // the AA is the alpha - about to be set
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			// alternative glob alpha fix
//DEADCODE JON 5/19/00 			SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 			sVertex->specular=0x00000000;
//DEADCODE JON 5/19/00 		break;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	// now set the colour values 4 plain coloured polys
//DEADCODE JON 5/19/00 	if ( matCol != COL_NULL )
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		SetColLighting( sVertex->color, &matCol, globAlpha );
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 }

//#pragma message ( __HERE__ "inline me" )

void Lib3D::GetTransformedLightColour( R3DVERTEX& vertex, const LIGHTFLAG lf )
{
    if (fCombineMatrices) CombineMatrices();
    if (updateLightVecs) UpdateLightVecs();

    SVertex tmp;
//	tmp = vertex;
    memcpy( &tmp, &vertex, sizeof( R3DVERTEX ) );

    tmp.Transform( &combinedMatrix );
    SetVertexCol( &tmp, lf );
    vertex.color.all = tmp.color.all;
}

inline void Lib3D::SetVertexCol( SVertex* sVertex, const LIGHTFLAG localLF )
{
//	LF_AMBIENT,
//	LF_LIGHTING,
//	LF_SPECULAR,
//	LF_ALPHA,
//	LF_LIGHTSOURCE,
//	LF_VERTEX,
//	LF_FONT,
//	LF_DUMMY,
//	LF_MAPCOLBIT = 8 // must be a bit...  (	see SetVertexCol )

//	(lightflag != LF_VERTEX && lightflag != LF_FONT)

//	R3DVERTEX* pv = sVertex;

    switch ( localLF )
    {
#ifdef LIGHT_ALL_SPECULAR
    case LF_LIGHTING:
#endif
    case LF_SPECULAR:
    {
        D3DVALUE v=DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,sunTX,sunTY,sunTZ);

        D3DVALUE k;
#ifdef PER_POINT_SPECULAR
        {
#define TRANSFORM_DIR_VECTOR( vec, mat ) { \
D3DVALUE x,y,z; \
x = vec.x*mat._11 + vec.y*mat._21 + vec.z*mat._31; \
y = vec.x*mat._12 + vec.y*mat._22 + vec.z*mat._32; \
z = vec.x*mat._13 + vec.y*mat._23 + vec.z*mat._33; \
vec.x = x; vec.y = y; vec.z = z;}

            R3DMATRIX *pMat;
            pMat = projectionMatrix+projMatStackPos; // have to back project to get position from eye

            // try the N.H model for specular lightshading. where H is half way between eye and lightvec.
            D3DVECTOR h; // H = E+L/2.  E = -[position vector]. As normalising ignore the division...
            h.x = sunTX;
            h.y = sunTY;
            h.z = sunTZ;

            TRANSFORM_DIR_VECTOR( h, objViewMatrix );
            D3DVECTOR eye;
            eye.x = sVertex->x * backProjectX;
            eye.y = sVertex->y * backProjectY;
            eye.z = -sVertex->hw;

            NormalizeVector( eye );

            h.x += eye.x;
            h.y += eye.y;
            h.z += eye.z;
            NormalizeVector( h );

            D3DVECTOR normal;
            normal.x = sVertex->nx*objViewMatrix._11 + sVertex->ny*objViewMatrix._21 + sVertex->nz*objViewMatrix._31;// + objViewMatrix._41;
            normal.y = sVertex->nx*objViewMatrix._12 + sVertex->ny*objViewMatrix._22 + sVertex->nz*objViewMatrix._32;// + objViewMatrix._42;
            normal.z = sVertex->nx*objViewMatrix._13 + sVertex->ny*objViewMatrix._23 + sVertex->nz*objViewMatrix._33;// + objViewMatrix._43;
            NormalizeVector( normal );

            k = DotProduct(normal.x,normal.y,normal.z,h.x,h.y,h.z);
        }
#else
        {
            k = DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,halfSunEye.x,halfSunEye.y,halfSunEye.z);
        }
#endif

        sVertex->color=lightingTable[F2UB_Clip((v+gLightBase)*gLightScale)];
        sVertex->color.alpha = globAlpha;

        sVertex->specular=specularTable[F2UB_Clip(k*255.f)];
    }
    break;
#ifndef	LIGHT_ALL_SPECULAR
    case LF_LIGHTING:
    {

        D3DVALUE v=gLightScale*(gLightBase+DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,sunTX,sunTY,sunTZ));
        sVertex->color=lightingTable[F2UB_Clip(v)];
        SetColAlpha( sVertex->color, globAlpha );

        sVertex->specular=0x00000000;
    }
    break;
#endif
    case LF_SPECULAR+LF_MAPCOLBIT:
    {
        D3DVALUE v=DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,sunTX,sunTY,sunTZ);

        D3DVALUE k;
#ifdef PER_POINT_SPECULAR
        {
#define TRANSFORM_DIR_VECTOR( vec, mat ) { \
D3DVALUE x,y,z; \
x = vec.x*mat._11 + vec.y*mat._21 + vec.z*mat._31; \
y = vec.x*mat._12 + vec.y*mat._22 + vec.z*mat._32; \
z = vec.x*mat._13 + vec.y*mat._23 + vec.z*mat._33; \
vec.x = x; vec.y = y; vec.z = z;}

            R3DMATRIX *pMat;
            pMat = projectionMatrix+projMatStackPos; // have to back project to get position from eye

            // try the N.H model for specular lightshading. where H is half way between eye and lightvec.
            D3DVECTOR h; // H = E+L/2.  E = -[position vector]. As normalising ignore the division...
            h.x = sunTX;
            h.y = sunTY;
            h.z = sunTZ;

            TRANSFORM_DIR_VECTOR( h, objViewMatrix );
            D3DVECTOR eye;
            eye.x = sVertex->x * backProjectX;
            eye.y = sVertex->y * backProjectY;
            eye.z = -sVertex->hw;

            NormalizeVector( eye );

            h.x += eye.x;
            h.y += eye.y;
            h.z += eye.z;
            NormalizeVector( h );

            D3DVECTOR normal;
            normal.x = sVertex->nx*objViewMatrix._11 + sVertex->ny*objViewMatrix._21 + sVertex->nz*objViewMatrix._31;// + objViewMatrix._41;
            normal.y = sVertex->nx*objViewMatrix._12 + sVertex->ny*objViewMatrix._22 + sVertex->nz*objViewMatrix._32;// + objViewMatrix._42;
            normal.z = sVertex->nx*objViewMatrix._13 + sVertex->ny*objViewMatrix._23 + sVertex->nz*objViewMatrix._33;// + objViewMatrix._43;
            NormalizeVector( normal );

            k = DotProduct(normal.x,normal.y,normal.z,h.x,h.y,h.z);
        }
#else
        {
            k = DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,halfSunEye.x,halfSunEye.y,halfSunEye.z);
        }
#endif
        sVertex->color=lightingTable[F2UB_Clip((v+gLightBase)*gLightScale)];
        SetColLighting( sVertex->color, curCol, globAlpha );

        sVertex->specular=specularTable[F2UB_Clip(k*255.f)];
    }
    break;

    case LF_LIGHTING+LF_MAPCOLBIT:
    {

        D3DVALUE v=gLightScale*(gLightBase+DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,sunTX,sunTY,sunTZ));

        sVertex->color=lightingTable[F2UB_Clip(v)];

        sVertex->specular=0x00000000;

        SetColLighting( sVertex->color, curCol, globAlpha );
    }
    break;

    case LF_ALPHA:
    {
//			D3DVALUE v=gLightScale*(gLightBase+DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,sunTX,sunTY,sunTZ));
        D3DVALUE v=(255.f-255.f*DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,sunTX,sunTY,sunTZ));

//			UByte alpha;
//			alpha = F2UB_Clip(v);

        sVertex->color=0xAAFFFFFF;  // the AA is the alpha - about to be set
//			SetColAlpha( sVertex->color, alpha );
//			static UByte tmpAlpha = 0;
        sVertex->color.alpha = F2UB_Clip(v);

        sVertex->specular=0x00000000;
    }
    break;
    case LF_ALPHA+LF_MAPCOLBIT:
    {

        D3DVALUE v=gLightScale*(gLightBase+DotProduct(sVertex->nx,sVertex->ny,sVertex->nz,sunTX,sunTY,sunTZ));

        UByte alpha;
        alpha = F2UB_Clip(v);

//			sVertex->color=0xAAFFFFFF;  // the AA is the alpha - about to be set
//			SetColAlpha( sVertex->color, alpha );
//			SetColLighting( sVertex->color, curCol, globAlpha );
        sVertex->color=curCol;
        SetColAlpha( sVertex->color, alpha );

        sVertex->specular=0x00000000;
    }
    break;


    case LF_AMBIENT:
        sVertex->color=gLightingDesc.ambientRGB;
        SetColAlpha( sVertex->color, globAlpha );

        sVertex->specular=0x00000000;
        break;
    case LF_AMBIENT+LF_MAPCOLBIT:
        sVertex->color=gLightingDesc.ambientRGB;
        SetColLighting( sVertex->color, curCol, globAlpha );

        sVertex->specular=0x00000000;
        break;

    case LF_FONT:											//RJS 10May00
        sVertex->color=gFontColour;
        SetColAlpha( sVertex->color, globAlpha );
        sVertex->specular=0x00000000;
        break;

    case LF_LIGHTSOURCE:
        sVertex->color=0xAAFFFFFF;  // the AA is the alpha - about to be set
        SetColAlpha( sVertex->color, globAlpha );

        sVertex->specular=0x00000000;
        break;
    case LF_LIGHTSOURCE+LF_MAPCOLBIT:
//			sVertex->color=0xAAFFFFFF;  // the AA is the alpha - about to be set
//			SetColAlpha( sVertex->color, globAlpha );
        sVertex->color=curCol;
        SetColAlpha( sVertex->color, globAlpha );

        sVertex->specular=0x00000000;
        break;

    case LF_VERTEX:
    case LF_VERTEX+LF_MAPCOLBIT:
    case LF_FONT+LF_MAPCOLBIT:
    case LF_DEPTH+LF_MAPCOLBIT:
        // do nothing - the mapcolbits can't get here anyway, nor can the dunmmys
        // however this allows for the nodefault, removing the need for a test...
        break;
    case LF_DEPTH:
    {
        INT3;
        R3DCOLOUR other;
        other = 0xFF0000;
        sVertex->color.all=0xFFFFFF;
        sVertex->color.interpRGB( other, sVertex->hw*zFactor);
        sVertex->color.alpha = globAlpha;
        sVertex->specular = 0x00000000;
    }
    break;
    NODEFAULT;
    }

//DeadCode JON 15Jun00 	// now set the colour values 4 plain coloured polys
//DeadCode JON 15Jun00 	if ( curCol != COL_NULL )
//DeadCode JON 15Jun00 	{
//DeadCode JON 15Jun00 		SetColLighting( sVertex->color, curCol, globAlpha );
//DeadCode JON 15Jun00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipSetCols
//Author		Jon.
//Date			Web 29 Mar 2000
//				frav runs from in to out 0->1
//------------------------------------------------------------------------------
inline void Lib3D::ClipSetCols(SVertex* &vi, SVertex* &vo, SVertex* &vc, double &frac )
{
//DEADCODE JON 4/18/00 	if ( lightflag == LF_VERTEX )
//DEADCODE JON 4/18/00 		return;

//DEADCODE JON 6/5/00 	switch ( lightflag )
//DEADCODE JON 6/5/00 	{
//DEADCODE JON 6/5/00 		case LF_SPECULAR: // please implement me
//DEADCODE JON 6/5/00 		case LF_LIGHTING:
//DEADCODE JON 6/5/00 		case LF_VERTEX:
//DEADCODE JON 6/5/00 		{

//DeadCode JON 11Sep00 			UByte la, lr, lg, lb;
//DeadCode JON 11Sep00 			UByte ha, hr, hg, hb;
//DeadCode JON 11Sep00 			GetColARGB( vi->color, la, lr, lg, lb );
//DeadCode JON 11Sep00 			GetColARGB( vo->color, ha, hr, hg, hb );
//DeadCode JON 11Sep00 			SetCol( vc->color,
//DeadCode JON 11Sep00 					la + UByte( D3DVALUE( ha - la ) * frac ),
//DeadCode JON 11Sep00 					lr + UByte( D3DVALUE( hr - lr ) * frac ),
//DeadCode JON 11Sep00 					lg + UByte( D3DVALUE( hg - lg ) * frac ),
//DeadCode JON 11Sep00 					lb + UByte( D3DVALUE( hb - lb ) * frac ) );
    vc->color = vi->color;
    vc->color.interpRGBA( vo->color, frac );

    if ( lightflag == LF_SPECULAR
#ifdef	LIGHT_ALL_SPECULAR
            || lightflag == LF_LIGHTING
#endif
       )
    {

        vc->specular=vi->specular;
        vc->specular.interpRGB( vo->specular, frac );
    }
    else
    {
        vc->specular=0x00000000;
        if ( (hLastMaterial.materialFlags)&IS_SPECULAR )
            INT3;
    }
//DeadCode JON 11Sep00 			else
//DeadCode JON 11Sep00 			{
//DeadCode JON 11Sep00 				vc->specular=0x00000000;
//DeadCode JON 11Sep00 			}
    // average the fog...
//DeadCode JON 1Aug00 			lr = GetColAlpha( vi->specular );
//DeadCode JON 1Aug00 			hr = GetColAlpha( vo->specular );
//DeadCode JON 1Aug00 			SetColAlpha( vc->specular, lr + UByte( D3DVALUE( hr - lr ) * frac ) );
//			if ( flags&DO_SW_FOG )
//			{
//				SetColAlpha( vc->specular, fogTable[ F2UL_Round( 1023.f*vc->hw/farZPlane) ] );
    SetColAlpha( vc->specular, fogTable[ (0x3FF&F2UL_Round( vc->hw*fogMul )) ] );
//			}


//DEADCODE JON 6/5/00 		}
//DEADCODE JON 6/5/00 		break;
//DEADCODE JON 6/5/00 		case LF_ALPHA:
//DEADCODE JON 6/5/00 		{
//DEADCODE JON 6/5/00 			D3DVALUE li=D3DVALUE(GetColAlpha(vi->color));
//DEADCODE JON 6/5/00 			D3DVALUE lo=D3DVALUE(GetColAlpha(vo->color));
//DEADCODE JON 6/5/00 			D3DVALUE lc=li+frac*(lo-li);
//DEADCODE JON 6/5/00 			UByte alpha;
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 			if (lc<0.f)
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 				alpha = 255;
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 			else if (lc>255.f)
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 				alpha = 0;
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 			else
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 			{
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 				alpha = 255 - F2UL_Round( lc );
//DEADCODE JON 6/5/00 //DEADCODE JON 5/8/00 			}
//DEADCODE JON 6/5/00 			alpha = 255 - F2UB_Clip( lc );
//DEADCODE JON 6/5/00
//DEADCODE JON 6/5/00 			vc->color=0xAAFFFFFF;  // AA is the alpha val about to be filled
//DEADCODE JON 6/5/00 			vc->specular=0x00000000;
//DEADCODE JON 6/5/00
//DEADCODE JON 6/5/00 			SetColAlpha( vc->color, alpha );
//DEADCODE JON 6/5/00 		}
//DEADCODE JON 6/5/00 		break;
//DEADCODE JON 6/5/00 		case LF_AMBIENT:
//DEADCODE JON 6/5/00 //DEADCODE JON 3/29/00 			vc->color=0xAAFFFFFF;  // AA is the alpha val about to be filled
//DEADCODE JON 6/5/00 			vc->color=gLightingDesc.ambientRGB;
//DEADCODE JON 6/5/00 			vc->specular=0x00000000;
//DEADCODE JON 6/5/00 			// alternative glob alpha fix
//DEADCODE JON 6/5/00 			SetColAlpha( vc->color, globAlpha );
//DEADCODE JON 6/5/00 		break;
//DEADCODE JON 6/5/00 		case LF_FONT:											//RJS 10May00
//DEADCODE JON 6/5/00 			vc->color=gFontColour;
//DEADCODE JON 6/5/00 			vc->specular=0x00000000;
//DEADCODE JON 6/5/00 			// alternative glob alpha fix
//DEADCODE JON 6/5/00 			SetColAlpha( vc->color, globAlpha );
//DEADCODE JON 6/5/00 		break;
//DEADCODE JON 6/5/00 		default:
//DEADCODE JON 6/5/00 		case LF_LIGHTSOURCE:
//DEADCODE JON 6/5/00 			vc->color=0xAAFFFFFF;  // AA is the alpha val about to be filled
//DEADCODE JON 6/5/00 			vc->specular=0x00000000;
//DEADCODE JON 6/5/00 			// alternative glob alpha fix
//DEADCODE JON 6/5/00 			SetColAlpha( vc->color, globAlpha );
//DEADCODE JON 6/5/00 		break;
//DEADCODE JON 6/5/00 	}
//DEADCODE JON 6/5/00

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToFront
//Author		Paul.
//Date			Wed 5 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToFront(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    D3DVALUE xi,yi,zi;
    D3DVALUE xo,yo,zo;
    double frac;
    zi=vi->hw;
    xi=vi->sx;
    yi=vi->sy;
    zo=vo->hw;
    xo=vo->sx;
    yo=vo->sy;
    frac=(nearZPlane-zi)/(zo-zi);
    vc->sx=Interp(xi,xo,frac);
    vc->sy=Interp(yi,yo,frac);
//DeadCode JON 29Aug00 	vc->sz=0.f;
    vc->sz=zNearClip;
    vc->hw=nearZPlane;
    switch (numTextures)
    {
//DeadCode JON 1Aug00 		default:
//DeadCode JON 1Aug00 			INT3;
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }
    ClipSetCols( vi, vo, vc, frac );

    vc->clipcode=ClipCodeLRTB( vc );
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToBack
//Author		Paul.
//Date			Wed 5 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToBack(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    D3DVALUE xi,yi,zi;
    D3DVALUE xo,yo,zo;
    double frac;
    zi=vi->hw;
    xi=vi->sx;
    yi=vi->sy;
    zo=vo->hw;
    xo=vo->sx;
    yo=vo->sy;
    frac=(farZPlane-zi)/(zo-zi);
    vc->sx=Interp(xi,xo,frac);
    vc->sy=Interp(yi,yo,frac);
    vc->sz=zFarClip;													//JON 29Aug00
    vc->hw=farZPlane;
    switch (numTextures)
    {
//DeadCode JON 1Aug00 		default:
//DeadCode JON 1Aug00 			INT3;
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }

    ClipSetCols( vi, vo, vc, frac );

    vc->clipcode=ClipCodeLRTB( vc );
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToTop
//Author		Paul.
//Date			Wed 5 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToTop(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    D3DVALUE xi,yi,zi;
    D3DVALUE xc,yc,zc;
    D3DVALUE xo,yo,zo;
//	D3DVALUE temp;
    D3DVALUE dy,dz;
    double frac,grad,cnst;
    zi=vi->hw;
    xi=vi->sx;
    yi=vi->sy;
    zo=vo->hw;
    xo=vo->sx;
    yo=vo->sy;
    dz=zo-zi;
    dy=yo-yi;
    if (FPTiny(dy))
    {
        yc=zc=yi;
        frac=(zc-zi)/dz;
    }
    else if (FPTiny(dz))
    {
        yc=zc=zi;
        frac=(yc-yi)/dy;
    }
    else
    {
        grad=dz/dy;
        cnst=zi-grad*yi;
        zc=yc=cnst/(1.f-grad);
        frac=(yc-yi)/dy;
    }
    xc=xi+frac*(xo-xi);
    vc->hw=zc;
    zc=zc*clippingMatrix._33+clippingMatrix._43;
    vc->sx=xc;
    vc->sy=yc;
    vc->sz=zc;
    switch (numTextures)
    {
//DeadCode JON 1Aug00 		default:
//DeadCode JON 1Aug00 			INT3;
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }
    ClipSetCols( vi, vo, vc, frac );
    vc->clipcode=0;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToBottom
//Author		Paul.
//Date			Wed 5 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToBottom(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    D3DVALUE xi,yi,zi;
    D3DVALUE xc,yc,zc;
    D3DVALUE xo,yo,zo;
//	D3DVALUE temp;
    D3DVALUE dy,dz;
    double frac,grad,cnst;
    zi=vi->hw;
    xi=vi->sx;
    yi=vi->sy;
    zo=vo->hw;
    xo=vo->sx;
    yo=vo->sy;
    dz=zo-zi;
    dy=yo-yi;
    if (FPTiny(dy))
    {
        yc=yi;
        zc=-yc;
        frac=(zc-zi)/dz;
    }
    else if (FPTiny(dz))
    {
        zc=zi;
        yc=-zc;
        frac=(yc-yi)/dy;
    }
    else
    {
        grad=dz/dy;
        cnst=zi-grad*yi;
        yc=cnst/(-1.f-grad);
        zc=-yc;
        frac=(yc-yi)/dy;
    }
    xc=Interp(xi,xo,frac);
    vc->hw=zc;
    zc=zc*clippingMatrix._33+clippingMatrix._43;
    vc->sx=xc;
    vc->sy=yc;
    vc->sz=zc;
    switch (numTextures)
    {
//DeadCode JON 1Aug00 		default:
//DeadCode JON 1Aug00 			INT3;
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }

    ClipSetCols( vi, vo, vc, frac );

    vc->clipcode=0;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToLeft
//Author		Paul.
//Date			Wed 5 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToLeft(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    D3DVALUE xi,yi,zi;
    D3DVALUE xc,yc,zc;
    D3DVALUE xo,yo,zo;
    D3DVALUE dx,dz;
    double frac,grad,cnst;
    zi=vi->hw;
    xi=vi->sx;
    yi=vi->sy;
    zo=vo->hw;
    xo=vo->sx;
    yo=vo->sy;
    dz=zo-zi;
    dx=xo-xi;
    if (FPTiny(dx))
    {
        xc=xi;
        zc=-xc;
        frac=(zc-zi)/dz;
    }
    else if (FPTiny(dz))
    {
        zc=zi;
        xc=-zc;
        frac=(xc-xi)/dx;
    }
    else
    {
        grad=dz/dx;
        cnst=zi-grad*xi;
        xc=cnst/(-1.f-grad);
        zc=-xc;
        frac=(xc-xi)/dx;
    }
    yc=Interp(yi,yo,frac);
    vc->hw=zc;
    zc=zc*clippingMatrix._33+clippingMatrix._43;
    vc->sx=xc;
    vc->sy=yc;
    vc->sz=zc;
    switch (numTextures)
    {
//DeadCode JON 1Aug00 		default:
//DeadCode JON 1Aug00 			INT3;
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }

    ClipSetCols( vi, vo, vc, frac );
    vc->clipcode=ClipCodeTB( vc );
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToRight
//Author		Paul.
//Date			Wed 5 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToRight(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    D3DVALUE xi,yi,zi; // inside
    D3DVALUE xc,yc,zc; // clipped
    D3DVALUE xo,yo,zo; // outside
//	D3DVALUE temp;
    D3DVALUE dx,dz;
    double frac,grad,cnst;
    zi=vi->hw;
    xi=vi->sx;
    yi=vi->sy;
    zo=vo->hw;
    xo=vo->sx;
    yo=vo->sy;
    dz=zo-zi;
    dx=xo-xi;
    if (FPTiny(dx))
    {
        xc=zc=xi;
        frac=(zc-zi)/dz;
    }
    else if (FPTiny(dz))
    {
        xc=zc=zi;
        frac=(xc-xi)/dx;
    }
    else
    {
        grad=dz/dx;
        cnst=zi-grad*xi;
        zc=xc=cnst/(1.f-grad);
        frac=(xc-xi)/dx;
    }
    yc=Interp(yi,yo,frac);
    vc->hw=zc;
    zc=zc*clippingMatrix._33+clippingMatrix._43;
    vc->sx=xc;
    vc->sy=yc;
    vc->sz=zc;
    switch (numTextures)
    {
//DeadCode JON 1Aug00 		default:
//DeadCode JON 1Aug00 			INT3;
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }


    ClipSetCols( vi, vo, vc, frac );
    vc->clipcode=ClipCodeTB( vc );
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericPolyClip
//Author		Paul.
//Date			Wed 5 Jan 2000
//
//------------------------------------------------------------------------------

#define DOCLIP(srcpoly,srcindex,srcnext,dstpoly,dstindex,flag,cliprtn,numTextures)\
if (!((srcpoly)[(srcindex)]->clipcode&(flag)))\
{\
	(dstpoly)[(dstindex)++]=(srcpoly)[(srcindex)];\
	if ((srcpoly)[(srcnext)]->clipcode&(flag))\
	{\
		SVertex *ptltemp=(SVertex*)Alloc(sizeof(SVertex));\
		(cliprtn)((srcpoly)[(srcindex)],(srcpoly)[(srcnext)],ptltemp,numTextures);\
		(dstpoly)[(dstindex)++]=ptltemp;\
	}\
}\
else if (!((srcpoly)[(srcnext)]->clipcode&(flag)))\
{\
	SVertex *ptltemp=(SVertex*)Alloc(sizeof(SVertex));\
	(cliprtn)((srcpoly)[(srcnext)],(srcpoly)[(srcindex)],ptltemp,numTextures);\
	(dstpoly)[(dstindex)++]=ptltemp;\
}

void Lib3D::GenericPolyClip(SPolygon *poly /*,ULong SizeOfVertex*/)
{
    int numTextures = poly->material.f;
    SVertex **polyA,**polyB;
    SVertex **pCur,**pNxt;
    SVertex *pV;
    int i;

    polyA=pCur=(SVertex**)Alloc(sizeof(SVertex*)*(poly->vertexcount+8));
    polyB=(SVertex**)Alloc(sizeof(SVertex*)*(poly->vertexcount+8));

    pV=poly->pVertexList;

    for (i=poly->vertexcount; i!=0; i--)
    {
        *pCur=pV;
        pCur++;
        pV=pV->pNext;
    }
    //clip against near clipping plane

    ULong newPntCnt=0;
    ULong pntCnt=poly->vertexcount;

    int limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

//#pragma message ( TOSTR( DOCLIP(polyA,i,j,polyB,newPntCnt,CLIP_FRONT,ClipToFront) ) )

        DOCLIP(polyA,i,j,polyB,newPntCnt,CLIP_FRONT,ClipToFront, numTextures);
    }
    DOCLIP(polyA,i,0,polyB,newPntCnt,CLIP_FRONT,ClipToFront, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the far clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyB,i,j,polyA,newPntCnt,CLIP_BACK,ClipToBack, numTextures);
    }
    DOCLIP(polyB,i,0,polyA,newPntCnt,CLIP_BACK,ClipToBack, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the east clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyA,i,j,polyB,newPntCnt,CLIP_RIGHT,ClipToRight, numTextures);
    }
    DOCLIP(polyA,i,0,polyB,newPntCnt,CLIP_RIGHT,ClipToRight, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the west clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyB,i,j,polyA,newPntCnt,CLIP_LEFT,ClipToLeft, numTextures);
    }
    DOCLIP(polyB,i,0,polyA,newPntCnt,CLIP_LEFT,ClipToLeft, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the top clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyA,i,j,polyB,newPntCnt,CLIP_TOP,ClipToTop, numTextures);
    }
    DOCLIP(polyA,i,0,polyB,newPntCnt,CLIP_TOP,ClipToTop, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the bottom clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyB,i,j,polyA,newPntCnt,CLIP_BOTTOM,ClipToBottom, numTextures);
    }
    DOCLIP(polyB,i,0,polyA,newPntCnt,CLIP_BOTTOM,ClipToBottom, numTextures);

    pntCnt=newPntCnt;
    if (pntCnt>2)
    {
        // put the poly back together again...
        for (i=0; i<pntCnt-1; i++) polyA[i]->pNext=polyA[i+1];
        polyA[i]->pNext=polyA[0];
        poly->pVertexList=polyA[0];
    }
    poly->vertexcount=pntCnt;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PolyClipFrontBack
//Author		Jon.
//Date			Tue 13 Jun 2000
//
//				Clips to just the front and back plane - used for guard band clipping
//------------------------------------------------------------------------------
void Lib3D::PolyClipFrontBack(SPolygon *poly)
{
    int numTextures = poly->material.f;
    SVertex **polyA,**polyB;
    SVertex **pCur,**pNxt;
    SVertex *pV;
    int i;

    polyA=pCur=(SVertex**)Alloc(sizeof(SVertex*)*(poly->vertexcount+8));
    polyB=(SVertex**)Alloc(sizeof(SVertex*)*(poly->vertexcount+8));

    pV=poly->pVertexList;

    for (i=poly->vertexcount; i!=0; i--)
    {
        *pCur=pV;
        pCur++;
        pV=pV->pNext;
    }
    //clip against near clipping plane

    ULong newPntCnt=0;
    ULong pntCnt=poly->vertexcount;

    int limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyA,i,j,polyB,newPntCnt,CLIP_FRONT,ClipToFront, numTextures);
    }
    DOCLIP(polyA,i,0,polyB,newPntCnt,CLIP_FRONT,ClipToFront, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the far clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyB,i,j,polyA,newPntCnt,CLIP_BACK,ClipToBack, numTextures);
    }
    DOCLIP(polyB,i,0,polyA,newPntCnt,CLIP_BACK,ClipToBack, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    // put the poly back together again...
    pntCnt=newPntCnt;
    if (pntCnt>2)
    {
        for (i=0; i<pntCnt-1; i++)
            polyA[i]->pNext=polyA[i+1];

        polyA[i]->pNext=polyA[0];
        poly->pVertexList=polyA[0];
    }
    poly->vertexcount=pntCnt;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericLineClip
//Author
//Date			Thu 22 Jun 2000
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void Lib3D::GenericLineClip(SLine *line)//,ULong numTextures)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
#else
    SVertex *vertA,*vertB;

    vertA=line->vertices;
    vertB=line->vertices+1;

    if (vertA->clipcode&CLIP_FRONT)			ClipToFront(vertB,vertA,vertA,0);
    else if (vertB->clipcode&CLIP_FRONT)	ClipToFront(vertA,vertB,vertB,0);

    if (vertA->clipcode&CLIP_BACK)			ClipToBack(vertB,vertA,vertA,0);
    else if (vertB->clipcode&CLIP_BACK)		ClipToBack(vertA,vertB,vertB,0);

    if (vertA->clipcode&CLIP_RIGHT)			ClipToRight(vertB,vertA,vertA,0);
    else if (vertB->clipcode&CLIP_RIGHT)	ClipToRight(vertA,vertB,vertB,0);

    if (vertA->clipcode&CLIP_LEFT)			ClipToLeft(vertB,vertA,vertA,0);
    else if (vertB->clipcode&CLIP_LEFT)		ClipToLeft(vertA,vertB,vertB,0);

    if (vertA->clipcode&CLIP_TOP)			ClipToTop(vertB,vertA,vertA,0);
    else if (vertB->clipcode&CLIP_TOP)		ClipToTop(vertA,vertB,vertB,0);

    if (vertA->clipcode&CLIP_BOTTOM)		ClipToBottom(vertB,vertA,vertA,0);
    else if (vertB->clipcode&CLIP_BOTTOM)	ClipToBottom(vertA,vertB,vertB,0);
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToLeft
//Author		Paul.
//Date			Tue 30 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 void Lib3D::ClipToLeft(R3DTLVERTEX *pIn,R3DTLVERTEX *pOut,R3DTLVERTEX *pClip,ULong *pClipFlag)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	D3DVALUE frac=(vpDesc.left-pIn->sx)/(pOut->sx-pIn->sx);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sx)=FP_BITS(vpDesc.left);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sy)=FP_BITS(pIn->sy);
//DEADCODE JON 5/19/00 	pClip->sy+=frac*(pOut->sy-pIn->sy);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tu)=FP_BITS(pIn->tu);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tv)=FP_BITS(pIn->tv);
//DEADCODE JON 5/19/00 	pClip->tu+=frac*(pOut->tu-pIn->tu);
//DEADCODE JON 5/19/00 	pClip->tv+=frac*(pOut->tv-pIn->tv);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (pClip->sy<vpDesc.top)			*pClipFlag=CLIP_TOP;
//DEADCODE JON 5/19/00 	else if (pClip->sy>vpDesc.bottom)	*pClipFlag=CLIP_BOTTOM;
//DEADCODE JON 5/19/00 	else								*pClipFlag=0L;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToRight
//Author		Paul.
//Date			Tue 30 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 void Lib3D::ClipToRight(R3DTLVERTEX *pIn,R3DTLVERTEX *pOut,R3DTLVERTEX *pClip,ULong *pClipFlag)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	D3DVALUE frac=(vpDesc.right-pIn->sx)/(pOut->sx-pIn->sx);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sx)=FP_BITS(vpDesc.right);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sy)=FP_BITS(pIn->sy);
//DEADCODE JON 5/19/00 	pClip->sy+=frac*(pOut->sy-pIn->sy);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tu)=FP_BITS(pIn->tu);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tv)=FP_BITS(pIn->tv);
//DEADCODE JON 5/19/00 	pClip->tu+=frac*(pOut->tu-pIn->tu);
//DEADCODE JON 5/19/00 	pClip->tv+=frac*(pOut->tv-pIn->tv);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	if (pClip->sy<vpDesc.top)			*pClipFlag=CLIP_TOP;
//DEADCODE JON 5/19/00 	else if (pClip->sy>vpDesc.bottom)	*pClipFlag=CLIP_BOTTOM;
//DEADCODE JON 5/19/00 	else								*pClipFlag=0L;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToTop
//Author		Paul.
//Date			Tue 30 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 void Lib3D::ClipToTop(R3DTLVERTEX *pIn,R3DTLVERTEX *pOut,R3DTLVERTEX *pClip,ULong *pClipFlag)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	D3DVALUE frac=(vpDesc.top-pIn->sy)/(pOut->sy-pIn->sy);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sx)=FP_BITS(pIn->sx);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sy)=FP_BITS(vpDesc.top);
//DEADCODE JON 5/19/00 	pClip->sx+=frac*(pOut->sx-pIn->sx);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tu)=FP_BITS(pIn->tu);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tv)=FP_BITS(pIn->tv);
//DEADCODE JON 5/19/00 	pClip->tu+=frac*(pOut->tu-pIn->tu);
//DEADCODE JON 5/19/00 	pClip->tv+=frac*(pOut->tv-pIn->tv);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	*pClipFlag=0L;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToBottom
//Author		Paul.
//Date			Tue 30 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 void Lib3D::ClipToBottom(R3DTLVERTEX *pIn,R3DTLVERTEX *pOut,R3DTLVERTEX *pClip,ULong *pClipFlag)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	D3DVALUE frac=(vpDesc.bottom-pIn->sy)/(pOut->sy-pIn->sy);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sx)=FP_BITS(pIn->sx);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->sy)=FP_BITS(vpDesc.bottom);
//DEADCODE JON 5/19/00 	pClip->sx+=frac*(pOut->sx-pIn->sx);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tu)=FP_BITS(pIn->tu);
//DEADCODE JON 5/19/00 	FP_BITS(pClip->tv)=FP_BITS(pIn->tv);
//DEADCODE JON 5/19/00 	pClip->tu+=frac*(pOut->tu-pIn->tu);
//DEADCODE JON 5/19/00 	pClip->tv+=frac*(pOut->tv-pIn->tv);
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	*pClipFlag=0L;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenericPolyClip
//Author		Paul.
//Date			Tue 30 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/19/00 void Lib3D::GenericPolyClip(R3DTLVERTEX *pVerts,ULong *pClipFlags,ULong& numVerts,ULong *pVertList)
//DEADCODE JON 5/19/00 {
//DEADCODE JON 5/19/00 	ULong newVertCount=0L;
//DEADCODE JON 5/19/00 	ULong oriVertCount=numVerts;
//DEADCODE JON 5/19/00 	ULong newVertInsert=oriVertCount;
//DEADCODE JON 5/19/00 	ULong *pAVertList=new ULong[numVerts<<3];
//DEADCODE JON 5/19/00 	ULong i;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	ULong curIndex,nxtIndex;
//DEADCODE JON 5/19/00 	R3DTLVERTEX *pCur,*pNxt;
//DEADCODE JON 5/19/00 	nxtIndex=*pVertList;
//DEADCODE JON 5/19/00 	pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00 	pVertList[oriVertCount]=*pVertList;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	for (i=0;i<oriVertCount;i++)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		curIndex=nxtIndex;
//DEADCODE JON 5/19/00 		pCur=pNxt;
//DEADCODE JON 5/19/00 		nxtIndex=pVertList[i+1];
//DEADCODE JON 5/19/00 		pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 		if ((pClipFlags[curIndex]&CLIP_LEFT)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			pAVertList[newVertCount++]=curIndex;
//DEADCODE JON 5/19/00 			if ((pClipFlags[nxtIndex]&CLIP_LEFT)!=0)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				ClipToLeft(pCur,pNxt,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 				pAVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 				newVertInsert++;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		else if ((pClipFlags[nxtIndex]&CLIP_LEFT)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			ClipToLeft(pNxt,pCur,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 			pAVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 			newVertInsert++;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (newVertCount<3)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		numVerts=0L;
//DEADCODE JON 5/19/00 		delete[]pAVertList;
//DEADCODE JON 5/19/00 		return;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	oriVertCount=newVertCount;
//DEADCODE JON 5/19/00 	newVertCount=0L;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	nxtIndex=*pAVertList;
//DEADCODE JON 5/19/00 	pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00 	pAVertList[oriVertCount]=*pAVertList;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	for (i=0;i<oriVertCount;i++)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		curIndex=nxtIndex;
//DEADCODE JON 5/19/00 		pCur=pNxt;
//DEADCODE JON 5/19/00 		nxtIndex=pAVertList[i+1];
//DEADCODE JON 5/19/00 		pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 		if ((pClipFlags[curIndex]&CLIP_RIGHT)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			pVertList[newVertCount++]=curIndex;
//DEADCODE JON 5/19/00 			if ((pClipFlags[nxtIndex]&CLIP_RIGHT)!=0)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				ClipToRight(pCur,pNxt,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 				pVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 				newVertInsert++;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		else if ((pClipFlags[nxtIndex]&CLIP_RIGHT)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			ClipToRight(pNxt,pCur,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 			pVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 			newVertInsert++;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (newVertCount<3)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		numVerts=0L;
//DEADCODE JON 5/19/00 		delete[]pAVertList;
//DEADCODE JON 5/19/00 		return;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	oriVertCount=newVertCount;
//DEADCODE JON 5/19/00 	newVertCount=0L;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	nxtIndex=*pVertList;
//DEADCODE JON 5/19/00 	pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00 	pVertList[oriVertCount]=*pVertList;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	for (i=0;i<oriVertCount;i++)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		curIndex=nxtIndex;
//DEADCODE JON 5/19/00 		pCur=pNxt;
//DEADCODE JON 5/19/00 		nxtIndex=pVertList[i+1];
//DEADCODE JON 5/19/00 		pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 		if ((pClipFlags[curIndex]&CLIP_TOP)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			pAVertList[newVertCount++]=curIndex;
//DEADCODE JON 5/19/00 			if ((pClipFlags[nxtIndex]&CLIP_TOP)!=0)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				ClipToTop(pCur,pNxt,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 				pAVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 				newVertInsert++;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		else if ((pClipFlags[nxtIndex]&CLIP_TOP)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			ClipToTop(pNxt,pCur,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 			pAVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 			newVertInsert++;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (newVertCount<3)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		numVerts=0L;
//DEADCODE JON 5/19/00 		delete[]pAVertList;
//DEADCODE JON 5/19/00 		return;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	oriVertCount=newVertCount;
//DEADCODE JON 5/19/00 	newVertCount=0L;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	nxtIndex=*pAVertList;
//DEADCODE JON 5/19/00 	pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00 	pAVertList[oriVertCount]=*pAVertList;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 	for (i=0;i<oriVertCount;i++)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		curIndex=nxtIndex;
//DEADCODE JON 5/19/00 		pCur=pNxt;
//DEADCODE JON 5/19/00 		nxtIndex=pAVertList[i+1];
//DEADCODE JON 5/19/00 		pNxt=pVerts+nxtIndex;
//DEADCODE JON 5/19/00
//DEADCODE JON 5/19/00 		if ((pClipFlags[curIndex]&CLIP_BOTTOM)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			pVertList[newVertCount++]=curIndex;
//DEADCODE JON 5/19/00 			if ((pClipFlags[nxtIndex]&CLIP_BOTTOM)!=0)
//DEADCODE JON 5/19/00 			{
//DEADCODE JON 5/19/00 				ClipToBottom(pCur,pNxt,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 				pVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 				newVertInsert++;
//DEADCODE JON 5/19/00 			}
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 		else if ((pClipFlags[nxtIndex]&CLIP_BOTTOM)==0)
//DEADCODE JON 5/19/00 		{
//DEADCODE JON 5/19/00 			ClipToBottom(pNxt,pCur,pVerts+newVertInsert,pClipFlags+newVertInsert);
//DEADCODE JON 5/19/00 			pVertList[newVertCount++]=newVertInsert;
//DEADCODE JON 5/19/00 			newVertInsert++;
//DEADCODE JON 5/19/00 		}
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	if (newVertCount<3)
//DEADCODE JON 5/19/00 		numVerts=0L;
//DEADCODE JON 5/19/00 	delete[]pAVertList;
//DEADCODE JON 5/19/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSphere
//Author		Paul.
//Date			Wed 24 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::DrawSphere(	const HMATERIAL& hMaterial,	//texture
                            const DoPointStruc& vertex,	//center
                            const D3DVALUE& radius,		//radius
                            const Angles roll,			//roll angle
                            const SWord u0,const SWord v0,	//texture coords for tl corner
                            const SWord u1,const SWord v1)	//texture coords for br corner
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    D3DVALUE fu0,fv0,fu1,fv1;

#ifndef NDEBUG
    if ( insidePoly == true )
        return DDERR_GENERIC;
#endif
    if ((lastError=SetMaterial(hMaterial))!=DD_OK) return lastError;
//DeadCode JON 20Oct00 	if (hMaterial.tsW[0]!=0) // assume this is always the case
    {
        fu0=(D3DVALUE(u0)+0.5)*hMaterial.tsW[0];						//RJS 22Sep00
        fu1=(D3DVALUE(u1)-0.5)*hMaterial.tsW[0];						//RJS 22Sep00
        fv0=(D3DVALUE(v0)+0.5)*hMaterial.tsH[0];						//RJS 22Sep00
        fv1=(D3DVALUE(v1)-0.5)*hMaterial.tsH[0];						//RJS 22Sep00
    }

//DEADCODE JON 5/22/00 	R3DVERTEX* polyVertArray=vertArray;
//DEADCODE JON 5/22/00 	*polyVertArray=vertex;
//DEADCODE JON 5/22/00 	D3DVERTEX *pv=(D3DVERTEX *)polyVertArray;
//	SPolygon *sPolygon;

    ALLOCATE_POLYGON_NOLINK(currentPoly,4);
    SVertex *sVertex=currentPoly->pVertexList;

    *sVertex = vertex;

//DeadCode JON 13Sep00 	sVertex->Transform( objectMatrix+objMatStackPos );
//DEADCODE JON 5/22/00  	Transform(pv,&sVertex->d3dtlvert,objectMatrix+objMatStackPos);
    // 	D3DVALUE w;
// 	w=1/sVertex->rhw;
//DEADCODE JON 5/22/00  	pv[0].x=sVertex->sx;//*w;
//DEADCODE JON 5/22/00  	pv[0].y=sVertex->sy;//*w;
//DEADCODE JON 5/22/00  	pv[0].z=sVertex->sz;//*w;

//DeadCode JON 13Sep00 	sVertex->Transform( viewerMatrix+viewMatStackPos );
    if (fCombineMatrices) CombineMatrices();

    sVertex->Transform( &objViewMatrix );
//DEADCODE JON 5/22/00 	Transform(pv,&sVertex->d3dtlvert,viewerMatrix+viewMatStackPos);
// 	w=1/sVertex->rhw;
//DEADCODE JON 5/22/00 	pv[0].x=sVertex->sx;//*w;
//DEADCODE JON 5/22/00 	pv[0].y=sVertex->sy;//*w;
//DEADCODE JON 5/22/00 	pv[0].z=sVertex->sz;//*w;

    D3DVALUE rad = radius;
//DEADCODE JON 5/22/00  	VolumetricSphere(pv[0],rad);
    sVertex->VolumetricSphere( rad );

    return _DrawSphereTransformed( rad, roll, fu0, fv0, fu1, fv1 );
#endif
}

//DeadCode JIM 22Jun100 This is the start of some code to do masked clipping of spheres
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 HRESULT Lib3D::_BufferSphereTransformed( const D3DVALUE rad, const Angles roll,
//DeadCode JIM 22Jun100 										const D3DVALUE fu0,const D3DVALUE fv0,	//texture coords for tl corner
//DeadCode JIM 22Jun100 										const D3DVALUE fu1,const D3DVALUE fv1)	//texture coords for br corner )
//DeadCode JIM 22Jun100 {
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	pv[1]=pv[0];
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	pv[2]=pv[0];
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	pv[3]=pv[0];
//DeadCode JIM 22Jun100 	SVertex *sVertex=currentPoly->pVertexList;
//DeadCode JIM 22Jun100 	currentPoly->vertexcount=rad;
//DeadCode JIM 22Jun100 	sVertex[0].pNext = &sVertex[1];
//DeadCode JIM 22Jun100 	sVertex[1] = *sVertex;
//DeadCode JIM 22Jun100 	sVertex[1].pNext = &sVertex[2];
//DeadCode JIM 22Jun100 	sVertex[2] = *sVertex;
//DeadCode JIM 22Jun100 	sVertex[2].pNext = &sVertex[3];
//DeadCode JIM 22Jun100 	sVertex[3] = *sVertex;
//DeadCode JIM 22Jun100 	sVertex[3].pNext = sVertex;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 	if (Test_Rot || 0==roll)
//DeadCode JIM 22Jun100 		{
//DeadCode JIM 22Jun100 			sVertex[3].x-=rad;	sVertex[3].y-=rad;
//DeadCode JIM 22Jun100 			sVertex[2].x+=rad;	sVertex[2].y-=rad;
//DeadCode JIM 22Jun100 			sVertex[1].x+=rad;	sVertex[1].y+=rad;
//DeadCode JIM 22Jun100 			sVertex[0].x-=rad;	sVertex[0].y+=rad;
//DeadCode JIM 22Jun100 		}
//DeadCode JIM 22Jun100 		else
//DeadCode JIM 22Jun100 		{
//DeadCode JIM 22Jun100 			D3DVALUE sine,cosine;
//DeadCode JIM 22Jun100 			SineCosine(roll,&sine,&cosine);
//DeadCode JIM 22Jun100 			sine*=rad;
//DeadCode JIM 22Jun100 			cosine*=rad;
//DeadCode JIM 22Jun100 			sVertex[3].x+=-cosine+sine;	sVertex[3].y+=-sine-cosine;
//DeadCode JIM 22Jun100 			sVertex[2].x+=cosine+sine;	sVertex[2].y+=sine-cosine;
//DeadCode JIM 22Jun100 			sVertex[1].x+=cosine-sine;	sVertex[1].y+=sine+cosine;
//DeadCode JIM 22Jun100 			sVertex[0].x+=-cosine-sine;	sVertex[0].y+=-sine+cosine;
//DeadCode JIM 22Jun100 		}
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 	R3DMATRIX *pMat=projectionMatrix+projMatStackPos;
//DeadCode JIM 22Jun100 	ULong		theColour = gLightingDesc.ambientRGB;
//DeadCode JIM 22Jun100 	SetColAlpha( theColour, globAlpha );
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	Transform(pv,&sVertex->d3dtlvert,pMat);
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 	sVertex->Transform( pMat );
//DeadCode JIM 22Jun100 	sVertex->tu=fu0;
//DeadCode JIM 22Jun100 	sVertex->tv=fv0;
//DeadCode JIM 22Jun100 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DeadCode JIM 22Jun100 	sVertex->color = theColour;
//DeadCode JIM 22Jun100 	sVertex->specular=0x00000000;
//DeadCode JIM 22Jun100 	sVertex->clipcode=ClipCodeFBLRTB( sVertex );
//DeadCode JIM 22Jun100 	currentPoly->andcode&=sVertex->clipcode;
//DeadCode JIM 22Jun100 	currentPoly->orcode|=sVertex->clipcode;
//DeadCode JIM 22Jun100 	sVertex=sVertex->pNext;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	Transform(pv+1,&sVertex->d3dtlvert,pMat);
//DeadCode JIM 22Jun100 	sVertex->Transform( pMat );
//DeadCode JIM 22Jun100 	sVertex->tu=fu1;
//DeadCode JIM 22Jun100 	sVertex->tv=fv0;
//DeadCode JIM 22Jun100 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DeadCode JIM 22Jun100 	sVertex->color = theColour;
//DeadCode JIM 22Jun100 	sVertex->specular=0x00000000;
//DeadCode JIM 22Jun100 	sVertex->clipcode=ClipCodeFBLRTB( sVertex );
//DeadCode JIM 22Jun100 	currentPoly->andcode&=sVertex->clipcode;
//DeadCode JIM 22Jun100 	currentPoly->orcode|=sVertex->clipcode;
//DeadCode JIM 22Jun100 	sVertex=sVertex->pNext;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	Transform(pv+2,&sVertex->d3dtlvert,pMat);
//DeadCode JIM 22Jun100 	sVertex->Transform( pMat );
//DeadCode JIM 22Jun100 	sVertex->tu=fu1;
//DeadCode JIM 22Jun100 	sVertex->tv=fv1;
//DeadCode JIM 22Jun100 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DeadCode JIM 22Jun100 	sVertex->color = theColour;
//DeadCode JIM 22Jun100 	sVertex->specular=0x00000000;
//DeadCode JIM 22Jun100 	sVertex->clipcode=ClipCodeFBLRTB( sVertex );
//DeadCode JIM 22Jun100 	currentPoly->andcode&=sVertex->clipcode;
//DeadCode JIM 22Jun100 	currentPoly->orcode|=sVertex->clipcode;
//DeadCode JIM 22Jun100 	sVertex=sVertex->pNext;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	Transform(pv+3,&sVertex->d3dtlvert,pMat);
//DeadCode JIM 22Jun100 	sVertex->Transform( pMat );
//DeadCode JIM 22Jun100 	sVertex->tu=fu0;
//DeadCode JIM 22Jun100 	sVertex->tv=fv1;
//DeadCode JIM 22Jun100 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DeadCode JIM 22Jun100 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DeadCode JIM 22Jun100 	sVertex->color = theColour;
//DeadCode JIM 22Jun100 	sVertex->specular=0x00000000;
//DeadCode JIM 22Jun100 	sVertex->clipcode=ClipCodeFBLRTB( sVertex );
//DeadCode JIM 22Jun100 	currentPoly->andcode&=sVertex->clipcode;
//DeadCode JIM 22Jun100 	currentPoly->orcode|=sVertex->clipcode;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 	//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	for (int i=4;i!=0;i--)
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	{
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	 	sVertex->clipcode=ClipCodeFBLRTB( sVertex );
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 		sPolygon->andcode&=sVertex->clipcode;
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 		sPolygon->orcode|=sVertex->clipcode;
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 		sVertex=sVertex->pNext;
//DeadCode JIM 22Jun100 //DEADCODE JON 5/22/00 	}
//DeadCode JIM 22Jun100 	if (currentPoly->andcode==0)
//DeadCode JIM 22Jun100 	{
//DeadCode JIM 22Jun100 #ifdef	_SHAPE_DEBUG_
//DeadCode JIM 22Jun100 	noPolysDebug++;
//DeadCode JIM 22Jun100 #endif
//DeadCode JIM 22Jun100 //TEMPCODE JIM 09/06/00 	 	if (currentPoly->orcode!=0)
//DeadCode JIM 22Jun100 //TEMPCODE JIM 09/06/00 			GenericPolyClip(currentPoly/*,SizeOfVertex*/);
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 		if (currentPoly->vertexcount>2)
//DeadCode JIM 22Jun100 		{
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			D3DVIEWPORT7 vp;
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			pD3DDEV7->GetViewport(&vp);
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			D3DVALUE sx,sy;
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			D3DVALUE cx,cy;
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			sx=D3DVALUE(vp.dwWidth>>1);
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			sy=-D3DVALUE(vp.dwHeight>>1);
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			cx=D3DVALUE(vp.dwX)+sx;
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 			cy=D3DVALUE(vp.dwY)-sy;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 /*			if (sPolygon->material.f==0)			//can never be plain...
//DeadCode JIM 22Jun100 			{
//DeadCode JIM 22Jun100 				if (renderMode == HINT_3DRENDER)
//DeadCode JIM 22Jun100 				{
//DeadCode JIM 22Jun100 					PROJECT(sPolygon,cx,cy,sx,sy);
//DeadCode JIM 22Jun100 				}
//DeadCode JIM 22Jun100 				else
//DeadCode JIM 22Jun100 				{
//DeadCode JIM 22Jun100 					PROJECT_2D(sPolygon,cx,cy,sx,sy);
//DeadCode JIM 22Jun100 				}
//DeadCode JIM 22Jun100 				ADD_POLYGON(plainPolys,sPolygon);
//DeadCode JIM 22Jun100 			}
//DeadCode JIM 22Jun100 			else*/
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 			if (Test_Flag || currentPoly->material.isMasked==0)
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 			{
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				if (renderMode == HINT_3DRENDER)
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				{
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 					PROJECT(currentPoly,cx,cy,sx,sy);
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 					currentPoly->projectType=STANDARD_PROJECT;
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				}
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				else
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				{
//DeadCode JIM 22Jun100 //DEADCODE JON 5/25/00 					PROJECT_2D(currentPoly,cx,cy,sx,sy);
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 					currentPoly->projectType=PROJECT_2D;
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 					currentPoly->zDepth2d = zDepth2d;
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				}
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				ADD_POLYGON(localspheres,currentPoly);
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				AddEdgeAliasing(currentPoly);
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 			}
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 			else
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 			{  //its transparent
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				if (renderMode == HINT_3DRENDER)
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				{
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 //DEADCODE JON 5/25/00 					PROJECT_SPHERE(currentPoly,cx,cy,sx,sy);//,rad);	//RJS 12May00
//DeadCode JIM 22Jun100 					currentPoly->projectType=SPHERE_PROJECT;
//DeadCode JIM 22Jun100 					currentPoly->CalcTransZ( zFactor );
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				}
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				else
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				{
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 //DEADCODE JON 5/25/00 					PROJECT_2D(currentPoly,cx,cy,sx,sy);
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 					currentPoly->projectType=PROJECT_2D;
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 					currentPoly->zDepth2d = zDepth2d;
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 					currentPoly->CalcTrans2DZ();
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 				}
//DeadCode JIM 22Jun100 				ADD_POLYGON(localspheres,currentPoly);
//DeadCode JIM 22Jun100 //DEADCODE JIM 09/06/00 			}
//DeadCode JIM 22Jun100 		}
//DeadCode JIM 22Jun100 	}
//DeadCode JIM 22Jun100 	else
//DeadCode JIM 22Jun100 	{
//DeadCode JIM 22Jun100 		DISCARD_POLYGON(currentPoly);
//DeadCode JIM 22Jun100 	}
//DeadCode JIM 22Jun100 //	polyVertCount=0xFFFFFFFF;
//DeadCode JIM 22Jun100 	return S_OK;
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 }
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 HRESULT	 Lib3D::_DrawBufferedSpheres()
//DeadCode JIM 22Jun100 {
//DeadCode JIM 22Jun100 	int	offset=ULong(&localspheres->zbuffer)-ULong(localspheres);
//DeadCode JIM 22Jun100 	localspheres=(SPolygon*)RadixSortAscending((radix_sort_t*)localspheres,offset);
//DeadCode JIM 22Jun100 	SPolygon*  addsphere=localspheres;
//DeadCode JIM 22Jun100 	SWord	StringLineArr[4000],*StringLine=&StringLineArr[2000];
//DeadCode JIM 22Jun100 	//At this stage I don't have screen X,Y,Z, but Body
//DeadCode JIM 22Jun100 	//Need to build up an 'exclusion zone' arround each sphere as it is added
//DeadCode JIM 22Jun100 	//But why bother?
//DeadCode JIM 22Jun100
//DeadCode JIM 22Jun100 	while (addsphere)
//DeadCode JIM 22Jun100 	{
//DeadCode JIM 22Jun100 		currentPoly=addsphere;
//DeadCode JIM 22Jun100 		addsphere=addsphere->pNext;
//DeadCode JIM 22Jun100 		if (currentPoly->orcode!=0)
//DeadCode JIM 22Jun100 			GenericPolyClip(currentPoly/*,SizeOfVertex*/);
//DeadCode JIM 22Jun100 		if (currentPoly->vertexcount>2)
//DeadCode JIM 22Jun100 			ADD_POLYGON(transparentPolys,currentPoly);
//DeadCode JIM 22Jun100 	}
//DeadCode JIM 22Jun100 	return S_OK;
//DeadCode JIM 22Jun100 }
//DeadCode JIM 22Jun100

//#pragma message( __HERE__ "inline me" )
inline HRESULT Lib3D::_DrawSphereTransformed( const D3DVALUE rad, const Angles roll,
        const D3DVALUE fu0,const D3DVALUE fv0,	//texture coords for tl corner
        const D3DVALUE fu1,const D3DVALUE fv1)	//texture coords for br corner )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

//DEADCODE JON 5/22/00 	pv[1]=pv[0];
//DEADCODE JON 5/22/00 	pv[2]=pv[0];
//DEADCODE JON 5/22/00 	pv[3]=pv[0];
    SVertex *sVertex=currentPoly->pVertexList;

    if (lightflag == LF_LIGHTSOURCE)									//RJS 22Sep00
        sVertex->color = 0xAAFFFFFF;
    else
        sVertex->color = gLightingDesc.ambientRGB;

    sVertex->color.alpha = globAlpha;									//RJS 22Sep00
    sVertex->specular=0x00000000;
    // Optimised version of CALC_FOG   (all vertices are in the same Z plane)
    sVertex->specular.alpha = fogTable[ (0x3FF&F2UL_Round( sVertex->z*fogMul )) ];	//RJS 22Sep00

    sVertex[0].pNext = &sVertex[1];
    sVertex[1] = *sVertex;
    sVertex[1].pNext = &sVertex[2];
    sVertex[2] = *sVertex;
    sVertex[2].pNext = &sVertex[3];
    sVertex[3] = *sVertex;
    sVertex[3].pNext = sVertex;
#ifdef DO_INDEXED_VB
    sVertex[0].identical =
        sVertex[1].identical =
            sVertex[2].identical =
                sVertex[3].identical = NULL;
#endif


    if (0==roll)
    {
        sVertex[3].x-=rad;
        sVertex[3].y-=rad;
        sVertex[2].x+=rad;
        sVertex[2].y-=rad;
        sVertex[1].x+=rad;
        sVertex[1].y+=rad;
        sVertex[0].x-=rad;
        sVertex[0].y+=rad;
    }
    else
    {
        D3DVALUE sine,cosine;
        SineCosine(roll,&sine,&cosine);
        sine*=rad;
        cosine*=rad;
        sVertex[3].x+=-cosine+sine;
        sVertex[3].y+=-sine-cosine;
        sVertex[2].x+=cosine+sine;
        sVertex[2].y+=sine-cosine;
        sVertex[1].x+=cosine-sine;
        sVertex[1].y+=sine+cosine;
        sVertex[0].x+=-cosine-sine;
        sVertex[0].y+=-sine+cosine;
    }

    R3DMATRIX *pMat=projectionMatrix+projMatStackPos;
//DeadCode RJS 22Sep00 	R3DCOLOUR		theColour;										//RJS 07Sep00
//DeadCode RJS 22Sep00 																//RJS 07Sep00
//DeadCode RJS 22Sep00 	if (lightflag == LF_LIGHTSOURCE)							//RJS 07Sep00
//DeadCode RJS 22Sep00 		theColour = 0xAAFFFFFF;									//RJS 07Sep00
//DeadCode RJS 22Sep00 	else														//RJS 07Sep00
//DeadCode RJS 22Sep00 		theColour = gLightingDesc.ambientRGB;					//RJS 07Sep00
//DeadCode RJS 22Sep00
//DeadCode RJS 22Sep00 	SetColAlpha( theColour, globAlpha );

//DEADCODE JON 5/22/00 	Transform(pv,&sVertex->d3dtlvert,pMat);

    sVertex->Transform( pMat );
    sVertex->tu=fu0;
    sVertex->tv=fv0;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

//DEADCODE JON 5/22/00 	Transform(pv+1,&sVertex->d3dtlvert,pMat);
    sVertex->Transform( pMat );
    sVertex->tu=fu1;
    sVertex->tv=fv0;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

//DEADCODE JON 5/22/00 	Transform(pv+2,&sVertex->d3dtlvert,pMat);
    sVertex->Transform( pMat );
    sVertex->tu=fu1;
    sVertex->tv=fv1;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

//DEADCODE JON 5/22/00 	Transform(pv+3,&sVertex->d3dtlvert,pMat);
    sVertex->Transform( pMat );
    sVertex->tu=fu0;
    sVertex->tv=fv1;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;

    //DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DeadCode RJS 22Sep00 	CALC_FOG( currentPoly );

//DEADCODE JON 5/22/00 	for (int i=4;i!=0;i--)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 	 	sVertex->clipcode=ClipCodeFBLRTB( sVertex );
//DEADCODE JON 5/22/00 		sPolygon->andcode&=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sPolygon->orcode|=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00 	}
    if (currentPoly->andcode==0)
    {
#ifdef	_SHAPE_DEBUG_
        noPolysDebug++;
#endif
        if (currentPoly->orcode!=0)
            GenericPolyClip(currentPoly/*,SizeOfVertex*/);

        if (currentPoly->vertexcount>2)
        {
            //its always transparent
            if (renderMode == HINT_3DRENDER)
            {
                //DEADCODE JON 5/25/00 					PROJECT_SPHERE(currentPoly,cx,cy,sx,sy);//,rad);	//RJS 12May00
                currentPoly->projectType=SPHERE_PROJECT+zBias;
                currentPoly->CalcTransZ( zFactor, 0.0f );
//				currentPoly->CalcTransZ(zFactor,tZBias_f); // don't ever do a bias on these...
            }
            else
            {
                //DEADCODE JON 5/25/00 					PROJECT_2D(currentPoly,cx,cy,sx,sy);
                currentPoly->projectType=PROJECT_2D;
                currentPoly->zDepth2d = zDepth2d;
                currentPoly->SetTrans2DZ(zBuffer2d);
            }
            ADD_POLYGON(transparentPolys,currentPoly);
        }
    }
    else
    {
        DISCARD_POLYGON(currentPoly);
    }
//	polyVertCount=0xFFFFFFFF;
    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawTrailSphere
//Author		Robert.
//Date			Thu 16 Mar 2000
//
//				Same as DrawSphere, but without the object & viewer transforms
//
//------------------------------------------------------------------------------
HRESULT Lib3D::DrawTransformedSphere (
    const HMATERIAL& hMaterial,	//texture
    const DoPointStruc& vertex,	//center
    const D3DVALUE& rad,		//radius
    const Angles roll,			//roll angle
    const SWord u0,const SWord v0,	//texture coords for tl corner
    const SWord u1,const SWord v1)	//texture coords for br corner
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    D3DVALUE fu0,fv0,fu1,fv1;

#ifndef NDEBUG
    if ( insidePoly == true )
        return DDERR_GENERIC;
#endif
    if ((lastError=SetMaterial(hMaterial))!=DD_OK) return lastError;
//DeadCode JON 20Oct00 	if (hMaterial.tsW[0]!=0) // assume this is always the case
    {
        fu0=(D3DVALUE(u0)+0.5)*hMaterial.tsW[0];						//RJS 22Sep00
        fu1=(D3DVALUE(u1)-0.5)*hMaterial.tsW[0];						//RJS 22Sep00
        fv0=(D3DVALUE(v0)+0.5)*hMaterial.tsH[0];						//RJS 22Sep00
        fv1=(D3DVALUE(v1)-0.5)*hMaterial.tsH[0];						//RJS 22Sep00
    }

    ALLOCATE_POLYGON_NOLINK(currentPoly,4);
    *currentPoly->pVertexList = vertex;

    return _DrawSphereTransformed( rad, roll, fu0, fv0, fu1, fv1 );

//DEADCODE JON 5/22/00 	pv[1]=pv[0];
//DEADCODE JON 5/22/00 	pv[2]=pv[0];
//DEADCODE JON 5/22/00 	pv[3]=pv[0];
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	if (0==roll)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 		pv[3].x-=rad;	pv[3].y-=rad;
//DEADCODE JON 5/22/00 		pv[2].x+=rad;	pv[2].y-=rad;
//DEADCODE JON 5/22/00 		pv[1].x+=rad;	pv[1].y+=rad;
//DEADCODE JON 5/22/00 		pv[0].x-=rad;	pv[0].y+=rad;
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00 	else
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 		D3DVALUE sine,cosine;
//DEADCODE JON 5/22/00 		SineCosine(roll,&sine,&cosine);
//DEADCODE JON 5/22/00 		sine*=rad;
//DEADCODE JON 5/22/00 		cosine*=rad;
//DEADCODE JON 5/22/00 		pv[3].x+=-cosine+sine;	pv[3].y+=-sine-cosine;
//DEADCODE JON 5/22/00 		pv[2].x+=cosine+sine;	pv[2].y+=sine-cosine;
//DEADCODE JON 5/22/00 		pv[1].x+=cosine-sine;	pv[1].y+=sine+cosine;
//DEADCODE JON 5/22/00 		pv[0].x+=-cosine-sine;	pv[0].y+=-sine+cosine;
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	R3DMATRIX *pMat=projectionMatrix+projMatStackPos;
//DEADCODE JON 5/22/00 	ULong		theColour = gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 	SetColAlpha( theColour, globAlpha );
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu0;
//DEADCODE JON 5/22/00 	sVertex->tv=fv0;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv+1,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu1;
//DEADCODE JON 5/22/00 	sVertex->tv=fv0;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv+2,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu1;
//DEADCODE JON 5/22/00 	sVertex->tv=fv1;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv+3,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu0;
//DEADCODE JON 5/22/00 	sVertex->tv=fv1;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	for (int i=4;i!=0;i--)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 	 	sVertex->clipcode=ClipCodeFBLRTB(&sVertex->d3dtlvert);
//DEADCODE JON 5/22/00 		sPolygon->andcode&=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sPolygon->orcode|=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00 	if (sPolygon->andcode==0)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 #ifdef	_SHAPE_DEBUG_
//DEADCODE JON 5/22/00 	noPolysDebug++;
//DEADCODE JON 5/22/00 #endif
//DEADCODE JON 5/22/00 	 	if (sPolygon->orcode!=0)
//DEADCODE JON 5/22/00 			GenericPolyClip(sPolygon);
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 		if (sPolygon->vertexcount>2)
//DEADCODE JON 5/22/00 		{
//DEADCODE JON 5/22/00 			D3DVIEWPORT7 vp;
//DEADCODE JON 5/22/00 			pD3DDEV7->GetViewport(&vp);
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 			D3DVALUE sx,sy;
//DEADCODE JON 5/22/00 			D3DVALUE cx,cy;
//DEADCODE JON 5/22/00 			sx=D3DVALUE(vp.dwWidth>>1);
//DEADCODE JON 5/22/00 			sy=-D3DVALUE(vp.dwHeight>>1);
//DEADCODE JON 5/22/00 			cx=D3DVALUE(vp.dwX)+sx;
//DEADCODE JON 5/22/00 			cy=D3DVALUE(vp.dwY)-sy;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 /*			if (sPolygon->material.f==0)			//can never be plain
//DEADCODE JON 5/22/00 			{
//DEADCODE JON 5/22/00 				if (renderMode == HINT_3DRENDER)
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				else
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_2D(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				ADD_POLYGON(plainPolys,sPolygon);
//DEADCODE JON 5/22/00 			}
//DEADCODE JON 5/22/00 			else*/ if (sPolygon->material.isMasked==0)
//DEADCODE JON 5/22/00 			{
//DEADCODE JON 5/22/00 				if (renderMode == HINT_3DRENDER)
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				else
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_2D(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				ADD_POLYGON(texturedPolys,sPolygon);
//DEADCODE JON 5/22/00 				AddEdgeAliasing(sPolygon);
//DEADCODE JON 5/22/00 			}
//DEADCODE JON 5/22/00 			else
//DEADCODE JON 5/22/00 			{
//DEADCODE JON 5/22/00 				if (renderMode == HINT_3DRENDER)
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_SPHERE(sPolygon,cx,cy,sx,sy);//,0);//this causes problems
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				else
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_2D(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				ADD_POLYGON(transparentPolys,sPolygon);
//DEADCODE JON 5/22/00 			}
//DEADCODE JON 5/22/00 		}
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00 	else
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 		DISCARD_POLYGON(sPolygon);
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00 	return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawLine
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/22/00 HRESULT Lib3D::DrawLine(const HMATERIAL& hMaterial,const R3DVERTEX& v0,const R3DVERTEX& v1)
HRESULT Lib3D::DrawLine(const HMATERIAL& hMaterial,const DoPointStruc& v0,const DoPointStruc& v1)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    R3DVERTEX* pVertArray;
    D3DVERTEXBUFFERDESC vertBufDesc;
    LPDIRECT3DVERTEXBUFFER7 pD3DVB7;

#ifndef NO_HARD_TNL
    if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
    {
        vertBufDesc.dwSize=sizeof(D3DVERTEXBUFFERDESC);
        vertBufDesc.dwCaps=0L;
        vertBufDesc.dwFVF=D3DFVF_R3DVERTEX;
        vertBufDesc.dwNumVertices=2;

        if ((flags&F_TNL)==0)
            vertBufDesc.dwCaps|=D3DVBCAPS_SYSTEMMEMORY;

//		hr=pD3D7->CreateVertexBuffer(&vertBufDesc,&pD3DVB7,NULL);
        hr=pD3D7->CreateVertexBuffer(&vertBufDesc,&pD3DVB7,D3DDP_DONOTCLIP);

        if (hr!=D3D_OK)	return hr;

        hr=pD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,
                         (LPVOID*)&pVertArray,NULL);

        *pVertArray++=v0.getR3DVert();
        *pVertArray=v1.getR3DVert();

        if ((hr=pD3DVB7->Unlock())==D3D_OK &&
                (hr=pD3DDEV7->DrawPrimitiveVB(D3DPT_LINELIST,pD3DVB7,0,2,0))==D3D_OK)
        {
            pD3DVB7->Release();
            pD3DVB7=NULL;
            return S_OK;
        }
        CloseDown();
        return hr;
    }
#endif
    if (fCombineMatrices) CombineMatrices();

    SLine *sLine;
    sLine=(SLine*)Alloc(sizeof(SLine));

    sLine->vertices[0]=v0;
    sLine->vertices[1]=v1;


//TEMPCODE JON 6/1/00 	if ( sLine->vertices[0].info.isWorldValid() )
//TEMPCODE JON 6/1/00 	{// yes copy it
//TEMPCODE JON 6/1/00 		memcopy(
//TEMPCODE JON 6/1/00 				&sLine->vertices[0].x,
//TEMPCODE JON 6/1/00 				lastDoPoint[ sLine->vertices[0].info.getDoPointNum() ],
//TEMPCODE JON 6/1/00 				3*sizeof(D3DVALUE)
//TEMPCODE JON 6/1/00 			);
//TEMPCODE JON 6/1/00 	} else
//TEMPCODE JON 6/1/00 	{ // transform
    sLine->vertices[0].Transform( &combinedMatrix );
//TEMPCODE JON 6/1/00 	}
//TEMPCODE JON 6/1/00 	lastDoPoint[ sLine->vertices[0].info.getDoPointNum() ] = &sLine->vertices[0];


//TEMPCODE JON 6/1/00 	if ( sLine->vertices[1].info.isWorldValid() )
//TEMPCODE JON 6/1/00 	{// yes copy it
//TEMPCODE JON 6/1/00 		memcopy(
//TEMPCODE JON 6/1/00 				&sLine->vertices[1].x,
//TEMPCODE JON 6/1/00 				lastDoPoint[ sLine->vertices[1].info.getDoPointNum() ],
//TEMPCODE JON 6/1/00 				3*sizeof(D3DVALUE)
//TEMPCODE JON 6/1/00 			);
//TEMPCODE JON 6/1/00 	} else
//TEMPCODE JON 6/1/00 	{ // transform
    sLine->vertices[1].Transform( &combinedMatrix );
//TEMPCODE JON 6/1/00 	}
//TEMPCODE JON 6/1/00 	lastDoPoint[ sLine->vertices[1].info.getDoPointNum() ] = &sLine->vertices[1];


#ifndef _NO_VERTEX_SHARING
    v0.info.setAllInvalid();
    v1.info.setAllInvalid();
#endif
//TEMPCODE JON 6/1/00 	v0.info.setValidWorld();
//TEMPCODE JON 6/1/00 	v1.info.setValidWorld();

    if ( (flags&F_NOCLIPPING)==0 )
    {
        // do the clipping
        sLine->vertices[0].clipcode=ClipCodeFBLRTB(&sLine->vertices[0]);
        sLine->vertices[1].clipcode=ClipCodeFBLRTB(&sLine->vertices[1]);

        if ((sLine->vertices[0].clipcode&sLine->vertices[1].clipcode)!=0)
        {
            // both vertices are clipped off the same view plane
            AllocDiscard((char*)sLine);
            return S_OK;
        }
    }
    else
    {
        // don't clip
        sLine->vertices[0].clipcode=sLine->vertices[1].clipcode=0;
    }

    D3DCOLOR lineCol;
    if ( hMaterial.f==0 && hMaterial.c != 254)
    {
        // the material is plain colour
        lineCol = RGB_MAKE(	paletteTable[3*hMaterial.c],	//RED
                            paletteTable[3*hMaterial.c+1],	//GREEN
                            paletteTable[3*hMaterial.c+2]);	//BLUE
    }
    else
    {
        // it is texture mapped - use the font colour as default
        lineCol = gFontColour;
    }

    if ( lightflag == LF_AMBIENT || lightflag == LF_LIGHTING || lightflag == LF_SPECULAR )
    {
        SetColLighting( lineCol, gLightingDesc.ambientRGB );
    }

    if ((sLine->vertices[0].clipcode|sLine->vertices[1].clipcode)!=0)
    {
        GenericLineClip(sLine);//,sizeof(R3DVERTEX));
        if ( (ClipCodeLRTB(&sLine->vertices[0])|ClipCodeLRTB(&sLine->vertices[1]))!=0 )
        {
            // one of the vertices is still clipped.
            AllocDiscard((char*)sLine);
            return S_OK;
        }
    }

    sLine->vertices[0].color=lineCol;
    sLine->vertices[0].specular=SPECULAR_NO_FOG;
    sLine->vertices[1].color=lineCol;
    sLine->vertices[1].specular=SPECULAR_NO_FOG;

    D3DVIEWPORT7 vp;
#pragma message ( __HERE__ "drawline can be further optimised by moving the projection to the render" )

    D3DVALUE sx,sy;
    D3DVALUE cx,cy;
    GetViewPort( sx, sy, cx, cy );

//DeadCode JON 15Nov00 	pD3DDEV7->GetViewport(&vp);
//DeadCode JON 15Nov00
//DeadCode JON 15Nov00 	sx=D3DVALUE(vp.dwWidth>>1);
//DeadCode JON 15Nov00 	sy=-D3DVALUE(vp.dwHeight>>1);
//DeadCode JON 15Nov00 	cx=D3DVALUE(vp.dwX)+sx;
//DeadCode JON 15Nov00 	cy=D3DVALUE(vp.dwY)-sy;

    PROJECT_LINE(sLine,cx,cy,sx,sy);

    sLine->pNext=lineList;
    lineList=sLine;
    return S_OK;
#endif
}

HRESULT Lib3D::DrawTransformedLine(const HMATERIAL& hMaterial,const DoPointStruc& v0,const DoPointStruc& v1)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    SLine *sLine;
    sLine=(SLine*)Alloc(sizeof(SLine));

    D3DCOLOR lineCol;

    if ( hMaterial.f==0 && hMaterial.c != 254)
    {
        // the material is plain colour
        lineCol = RGB_MAKE(	paletteTable[3*hMaterial.c],	//RED
                            paletteTable[3*hMaterial.c+1],	//GREEN
                            paletteTable[3*hMaterial.c+2]);	//BLUE
    }
    else
    {
        // it is texture mapped - use the font colour as default
        lineCol = gFontColour;
    }

    if ( lightflag == LF_AMBIENT || lightflag == LF_LIGHTING || lightflag == LF_SPECULAR )
    {
        SetColLighting( lineCol, gLightingDesc.ambientRGB );
    }

    sLine->vertices[0]=v0;
    sLine->vertices[1]=v1;

    sLine->vertices[0].color=lineCol;
    sLine->vertices[0].specular=SPECULAR_NO_FOG;

    sLine->vertices[1].color=lineCol;
    sLine->vertices[1].specular=SPECULAR_NO_FOG;

    if (renderMode == HINT_2DRENDER)
    {
        // set the 2d z depth..
        sLine->vertices[0].z=
            sLine->vertices[1].z=
                zDepth2d;
        sLine->vertices[0].rhw=
            sLine->vertices[1].rhw=
                1.0f-zDepth2d;
    }

    sLine->material=hMaterial;

    sLine->pNext=lineList;
    lineList=sLine;
    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawLine
//Author		Paul.
//Date			Thu 13 Jan 2000
//
//------------------------------------------------------------------------------
//DEADCODE JON 5/22/00 HRESULT Lib3D::DrawLine(const HMATERIAL& hMaterial,const R3DTLVERTEX& v0,const R3DTLVERTEX& v1)
//DEADCODE JON 5/22/00 {
//DEADCODE JON 5/22/00 	HRESULT hr;
//DEADCODE JON 5/22/00 	R3DVERTEX* pVertArray;
//DEADCODE JON 5/22/00 	D3DVERTEXBUFFERDESC vertBufDesc;
//DEADCODE JON 5/22/00 	LPDIRECT3DVERTEXBUFFER7 pD3DVB7;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	if ((flags&Flags(F_TNL+F_TNL_EMULATION))!=0)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 		return S_OK;  // please implement!!!
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	SLine *sLine;
//DEADCODE JON 5/22/00 	sLine=(SLine*)Alloc(sizeof(SLine));
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	D3DTLVERTEX *v;
//DEADCODE JON 5/22/00 	D3DCOLOR lineCol;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	if ( hMaterial.f==0 )
//DEADCODE JON 5/22/00 	{ // the material is plain colour
//DEADCODE JON 5/22/00 		lineCol = RGB_MAKE(	paletteTable[3*hMaterial.c],	//RED
//DEADCODE JON 5/22/00 							paletteTable[3*hMaterial.c+1],	//GREEN
//DEADCODE JON 5/22/00 							paletteTable[3*hMaterial.c+2]);	//BLUE
//DEADCODE JON 5/22/00 	} else
//DEADCODE JON 5/22/00 	{ // it is texture mapped - use the font colour as default
//DEADCODE JON 5/22/00 		lineCol = 0xFFFFFFFF;
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	if ( lightflag == LF_AMBIENT || lightflag == LF_LIGHTING || lightflag == LF_SPECULAR )
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 		SetColLighting( lineCol, gLightingDesc.ambientRGB );
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	v=(D3DTLVERTEX*)&v0;
//DEADCODE JON 5/22/00 	sLine->vertices[0]=*v;
//DEADCODE JON 5/22/00 	sLine->vertices[0].color=lineCol;
//DEADCODE JON 5/22/00 	sLine->vertices[0].specular=0xFF000000;
//DEADCODE JON 5/22/00 	v=(D3DTLVERTEX*)&v1;
//DEADCODE JON 5/22/00 	sLine->vertices[1]=*v;
//DEADCODE JON 5/22/00 	sLine->vertices[1].color=lineCol;
//DEADCODE JON 5/22/00 	sLine->vertices[1].specular=0xFF000000;
//DEADCODE JON 5/22/00 	sLine->material=hMaterial;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	sLine->pNext=lineList;
//DEADCODE JON 5/22/00 	lineList=sLine;
//DEADCODE JON 5/22/00 	return S_OK;
//DEADCODE JON 5/22/00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawPoint
//Author		Paul.
//Date			Thu 11 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT Lib3D::DrawPoint(const HMATERIAL& hMaterial,const DoPointStruc& v0)
{
    if (fCombineMatrices) CombineMatrices();

    SPoint *sPoint;
    sPoint=(SPoint*)Alloc(sizeof(SPoint));

//	R3DVERTEX3(sPoint->vertex) = v0.getR3DVert();
    memcpy( &sPoint->vertex, &v0, sizeof( SVertex ) );
//DeadCode JON 19Oct00 	Transform(&v0,&sPoint->vertex,&combinedMatrix);
    sPoint->vertex.Transform( &combinedMatrix );
    sPoint->vertex.clipcode=ClipCodeFBLRTB(&sPoint->vertex);

//DeadCode JON 19Oct00 	sPoint->vertex.clipcode=ClipCodeFBLRTB(&sPoint->vertex);

    if (sPoint->vertex.clipcode!=0)
    {
        AllocDiscard((char*)sPoint);
        return S_OK;
    }


    D3DCOLOR pointCol;
    if ( hMaterial.f==0 && hMaterial.c != 254)
    {
        // the material is plain colour
        pointCol = RGB_MAKE(	paletteTable[3*hMaterial.c],	//RED
                                paletteTable[3*hMaterial.c+1],	//GREEN
                                paletteTable[3*hMaterial.c+2]);	//BLUE
    }
    else
    {
        // it is texture mapped - use the font colour as default
        pointCol = gFontColour;
    }

    if ( lightflag == LF_AMBIENT || lightflag == LF_LIGHTING || lightflag == LF_SPECULAR )
    {
        SetColLighting( pointCol, gLightingDesc.ambientRGB );
    }

    sPoint->vertex.color=pointCol;
    sPoint->vertex.specular=SPECULAR_NO_FOG;

    D3DVIEWPORT7 vp;
#pragma message ( __HERE__ "drawpoint can be further optimised by moving the projection to the render" )

    D3DVALUE sx,sy;
    D3DVALUE cx,cy;
    GetViewPort( sx, sy, cx, cy );

//DeadCode JON 15Nov00 	pD3DDEV7->GetViewport(&vp);
//DeadCode JON 15Nov00
//DeadCode JON 15Nov00 	sx=D3DVALUE(vp.dwWidth>>1);
//DeadCode JON 15Nov00 	sy=-D3DVALUE(vp.dwHeight>>1);
//DeadCode JON 15Nov00 	cx=D3DVALUE(vp.dwX)+sx;
//DeadCode JON 15Nov00 	cy=D3DVALUE(vp.dwY)-sy;

    PROJECT_POINT(&sPoint->vertex,cx,cy,sx,sy);

    sPoint->pNext=pointList;
    pointList=sPoint;

    return S_OK;
}

HRESULT Lib3D::DrawTransformedPoint(const HMATERIAL& hMaterial,const DoPointStruc& v0)
{

    SPoint *sPoint;
    sPoint=(SPoint*)Alloc(sizeof(SPoint));

//	R3DVERTEX3(sPoint->vertex) = v0.getR3DVert();
    memcpy( &sPoint->vertex, &v0, sizeof( SVertex ) );
//DeadCode JON 19Oct00 	sPoint->vertex.clipcode=ClipCodeFBLRTB(&sPoint->vertex);
//DeadCode JON 19Oct00
//DeadCode JON 19Oct00 	if (sPoint->vertex.clipcode!=0)
//DeadCode JON 19Oct00 	{
//DeadCode JON 19Oct00 		AllocDiscard((char*)sPoint);
//DeadCode JON 19Oct00 		return S_OK;
//DeadCode JON 19Oct00 	}

    D3DCOLOR pointCol;
    if ( hMaterial.f==0 && hMaterial.c != 254)
    {
        // the material is plain colour
        pointCol = RGB_MAKE(	paletteTable[3*hMaterial.c],	//RED
                                paletteTable[3*hMaterial.c+1],	//GREEN
                                paletteTable[3*hMaterial.c+2]);	//BLUE
    }
    else
    {
        // it is texture mapped - use the font colour as default
        pointCol = gFontColour;
    }

    if ( lightflag == LF_AMBIENT || lightflag == LF_LIGHTING || lightflag == LF_SPECULAR )
    {
        SetColLighting( pointCol, gLightingDesc.ambientRGB );
    }

    sPoint->vertex.color=pointCol;
    sPoint->vertex.specular=SPECULAR_NO_FOG;

    sPoint->pNext=pointList;
    pointList=sPoint;

    return S_OK;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GiveHint
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//------------------------------------------------------------------------------
HRESULT	Lib3D::GiveHint(const HINTS& hint)
{
    switch (hint)
    {
    case HINT_CLIPPING_OFF:
        flags=Flags(flags|F_NOCLIPPING);
        break;
    case HINT_CLIPPING_ON:
        flags=Flags(flags&~F_NOCLIPPING);
        break;
    case HINT_TRILINEAR:
    case HINT_BILINEAR:
    case HINT_NOBLEND:
        if (hint>=masterTextureBlending)	textureBlending=hint;
        else								textureBlending=masterTextureBlending;
        break;
    case HINT_FULL_RES_TEXTURE:
    case HINT_HALF_RES_TEXTURE:
    case HINT_QUARTER_RES_TEXTURE:
    case HINT_EIGHTH_RES_TEXTURE:
        if (hint>=masterTextureQuality)		textureQuality=hint;
        else								textureQuality=masterTextureQuality;
        break;
    case HINT_ALIASNONE:
    case HINT_ALIASEDGES:
        edgeAlias=masterEdgeAlias==HINT_ALIASEDGES?hint:HINT_ALIASNONE;
        break;
    case HINT_2DRENDER:
//DeadCode JON 25Sep00 		flags=Flags(flags|F_NOCLIPPING); // turn off clipping
        lightflag=LF_LIGHTSOURCE;
        renderMode=hint;
        break;
    case HINT_3DRENDER:
//DeadCode JON 25Sep00 		flags=Flags(flags&~F_NOCLIPPING); // turn on clipping
        renderMode=hint;
        break;
    default:
        return DDERR_INVALIDPARAMS;
    }
    return S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawCylinder
//Author		Robert Slater
//Date			Mon 14 Feb 2000
//
//Comments		Cylinder function, adapted from the DrawSphere code
//
//------------------------------------------------------------------------------
HRESULT Lib3D::DrawCylinder(const HMATERIAL& hMaterial,	//texture
                            const DoPointStruc& vertex0,	//p0
                            const DoPointStruc& vertex1,	//p1
                            const D3DVALUE& rad,		//radius
                            const SWord u0,const SWord v0,	//texture coords for tl corner
                            const SWord u1,const SWord v1)	//texture coords for br corner
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    D3DVALUE fu0,fv0,fu1,fv1;

#ifndef NDEBUG
    if ( insidePoly == true )
        return DDERR_GENERIC;
#endif
    if ((lastError=SetMaterial(hMaterial))!=DD_OK) return lastError;
//DeadCode JON 20Oct00 	if (hMaterial.tsW[0]!=0) // assume this is always the case
    {
        fu0=D3DVALUE(u0)*hMaterial.tsW[0];
        fu1=D3DVALUE(u1)*hMaterial.tsW[0];
        fv0=D3DVALUE(v0)*hMaterial.tsH[0];
        fv1=D3DVALUE(v1)*hMaterial.tsH[0];
    }
//DEADCODE JON 5/22/00 	R3DVERTEX *polyVertArray=vertArray;
//DEADCODE JON 5/22/00 	*polyVertArray=vertex0;
//DEADCODE JON 5/22/00 	polyVertArray[2]=vertex1;
//DEADCODE JON 5/22/00 	D3DVERTEX *pv=(D3DVERTEX *)polyVertArray;

//DEADCODE JON 5/22/00 	SPolygon *sPolygon;
//DEADCODE JON 5/22/00 	ALLOCATE_POLYGON(sPolygon,4);
    ALLOCATE_POLYGON_NOLINK( currentPoly, 4 );

//DEADCODE JON 5/22/00 	SVertex *sVertex=sPolygon->pVertexList;
    SVertex *sVertex=currentPoly->pVertexList;
    sVertex[0]=vertex0;
    sVertex[2]=vertex1;

    if (fCombineMatrices) CombineMatrices();							//RJS 22Sep00
    //RJS 22Sep00
    sVertex->Transform( &objViewMatrix );								//RJS 22Sep00
//DeadCode RJS 22Sep00 	sVertex->Transform(	objectMatrix+objMatStackPos );
//DeadCode RJS 22Sep00 	sVertex->Transform(	viewerMatrix+viewMatStackPos );

    sVertex[2].Transform( &objViewMatrix );								//RJS 22Sep00
//DeadCode RJS 22Sep00 	sVertex[2].Transform( objectMatrix+objMatStackPos );
//DeadCode RJS 22Sep00 	sVertex[2].Transform( viewerMatrix+viewMatStackPos );

    D3DVALUE	xoff, yoff;

//DEADCODE JON 5/22/00 	pv[1]=pv[0];
//DEADCODE JON 5/22/00 	pv[3]=pv[2];
    sVertex[1]=sVertex[0];
    sVertex[3]=sVertex[2];
    sVertex[0].pNext=&sVertex[1];
    sVertex[1].pNext=&sVertex[2];
    sVertex[2].pNext=&sVertex[3];
    sVertex[3].pNext=sVertex;

#ifdef DO_INDEXED_VB
    sVertex[0].identical =
        sVertex[1].identical =
            sVertex[2].identical =
                sVertex[3].identical = NULL;
#endif

    Float	rhz0 = 1./sVertex[0].z;										//RJS 10Aug00
    Float	rhz2 = 1./sVertex[2].z;										//RJS 10Aug00

    Float	adjacent = sVertex[0].y*rhz0 - sVertex[2].y*rhz2;			//RJS 10Aug00
    Float	opposite = sVertex[0].x*rhz0 - sVertex[2].x*rhz2;			//RJS 10Aug00
    if (opposite || adjacent)
    {
//DeadCode RJS 10Aug00 		SWord	sin_ang,cos_ang;
        Float	angle;
//#ifdef __GNUC__
        angle=atan2(opposite,adjacent);
        /*#else
        		_asm
        		{
        			fld		opposite
        			fld		adjacent
        			fpatan
        			fstp	angle
        		}
#endif*/
//DeadCode RJS 10Aug00 		angle *= 10430.37835047;
//DeadCode RJS 10Aug00 		SWord	angleofcyl = SWord(angle)-16384;

    D3DVALUE sine,cosine;
    SineCosine_Radian(D3DVALUE(angle-1.57079632),&sine,&cosine);

    xoff = sine * rad;
    yoff = cosine * rad;
}
else
    xoff = yoff = 0;

sVertex[3].x+=xoff;
sVertex[3].y+=yoff;
sVertex[2].x-=xoff;
sVertex[2].y-=yoff;
sVertex[1].x-=xoff;
sVertex[1].y-=yoff;
sVertex[0].x+=xoff;
sVertex[0].y+=yoff;

return _DrawTransformedCylinder( fu0, fv0, fu1, fv1 );
#endif
}

HRESULT Lib3D::_DrawTransformedCylinder( const D3DVALUE fu0, const D3DVALUE fv0, const D3DVALUE fu1, const D3DVALUE fv1 )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    SVertex* sVertex = currentPoly->pVertexList;

    R3DMATRIX *pMat=projectionMatrix+projMatStackPos;
    R3DCOLOUR		theColour;										//RJS 07Sep00

    if (lightflag == LF_LIGHTSOURCE)							//RJS 07Sep00
        theColour = 0xAAFFFFFF;									//RJS 07Sep00
    else														//RJS 07Sep00
        theColour = gLightingDesc.ambientRGB;					//RJS 07Sep00

    SetColAlpha( theColour, globAlpha );

//DEADCODE JON 5/22/00 	Transform(pv,&sVertex->d3dtlvert,pMat);
    sVertex->Transform( pMat );
    sVertex->tu=fu0;
    sVertex->tv=fv0;
    sVertex->color = theColour;
    sVertex->specular=0x00000000;
    sVertex->specular.alpha = fogTable[ (0x3FF&F2UL_Round( sVertex->hw*fogMul )) ];	//RJS 22Sep00
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

//DEADCODE JON 5/22/00 	Transform(pv+1,&sVertex->d3dtlvert,pMat);
    sVertex->Transform( pMat );

    sVertex->tu=fu1;
    sVertex->tv=fv0;
    sVertex->color = theColour;
    sVertex->specular=0x00000000;
    sVertex->specular.alpha = fogTable[ (0x3FF&F2UL_Round( sVertex->hw*fogMul )) ];	//RJS 22Sep00
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

//DEADCODE JON 5/22/00 	Transform(pv+2,&sVertex->d3dtlvert,pMat);
    sVertex->Transform( pMat );
    sVertex->tu=fu1;
    sVertex->tv=fv1;
    sVertex->color = theColour;
    sVertex->specular=0x00000000;
    sVertex->specular.alpha = fogTable[ (0x3FF&F2UL_Round( sVertex->hw*fogMul )) ];	//RJS 22Sep00
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

//DEADCODE JON 5/22/00 	Transform(pv+3,&sVertex->d3dtlvert,pMat);
    sVertex->Transform( pMat );
    sVertex->tu=fu0;
    sVertex->tv=fv1;
    sVertex->color = theColour;
    sVertex->specular=0x00000000;
    sVertex->specular.alpha = fogTable[ (0x3FF&F2UL_Round( sVertex->hw*fogMul )) ];	//RJS 22Sep00
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

//DeadCode RJS 22Sep00 	CALC_FOG( currentPoly );

//DEADCODE JON 5/22/00 	for (int i=4;i!=0;i--)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 	 	sVertex->clipcode=ClipCodeFBLRTB(sVertex);
//DEADCODE JON 5/22/00 		sPolygon->andcode&=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sPolygon->orcode|=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00 	}
    if (currentPoly->andcode==0)
    {
#ifdef	_SHAPE_DEBUG_
        noPolysDebug++;
#endif
        if (currentPoly->orcode!=0)
            GenericPolyClip(currentPoly);

        if (currentPoly->vertexcount>2)
        {
            //its transparent
            if (renderMode == HINT_3DRENDER)
            {
//DEADCODE JON 5/25/00 					PROJECT_SPHERE(currentPoly,cx,cy,sx,sy);//,rad);	//RJS 12May00
                currentPoly->projectType=STANDARD_PROJECT+zBias;	//RJS 06Jun00
                currentPoly->CalcTransZ( zFactor, 0.0f );
//				currentPoly->CalcTransZ(zFactor,tZBias_f); // don't ever do a bias on these...
            }
            else
            {
//DEADCODE JON 5/25/00 					PROJECT_2D(currentPoly,cx,cy,sx,sy);
                currentPoly->projectType=PROJECT_2D;
                currentPoly->zDepth2d = zDepth2d;
                currentPoly->SetTrans2DZ(zBuffer2d);
            }
            ADD_POLYGON(transparentPolys,currentPoly);
        }
    }
    else
    {
        DISCARD_POLYGON(currentPoly);
    }
    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CylinderOffsets
//Author		Robert Slater
//Date			Mon 14 Feb 2000
//
//Comments
//
//------------------------------------------------------------------------------
HRESULT Lib3D::CylinderOffsets(	const DoPointStruc& vertex0,	//p0
                                const DoPointStruc& vertex1,	//p1
                                const D3DVALUE& rad,		//radius
                                D3DVALUE& xoffset,
                                D3DVALUE& yoffset,
                                DoPointStruc& lastpoint	)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    HRESULT hr;
    D3DVALUE fu0,fv0,fu1,fv1;

    D3DTLVERTEX		tv0,tv1;
    R3DVERTEX		rv[2];
    D3DVALUE w;
    R3DVERTEX *pv=rv;

    rv[0] = vertex0.getR3DVert();
    rv[1] = vertex1.getR3DVert();

//We only need the translation...
    R3DMATRIX*	pObjMat = (R3DMATRIX*)(objectMatrix+objMatStackPos);

    pv[1].x += pObjMat->_41;
    pv[1].y += pObjMat->_42;
    pv[1].z += pObjMat->_43;

//And view transform...
    Transform(pv+1,&tv1,viewerMatrix+viewMatStackPos);
//	w=1/tv1.rhw;
    pv[1].x=tv1.sx;//*w;
    pv[1].y=tv1.sy;//*w;
    pv[1].z=tv1.sz;//*w;

    Float	rz0 = 1./pv[0].z;										//RJS 10Aug00
    Float	rz1 = 1./pv[1].z;										//RJS 10Aug00

    Float	adjacent = pv[0].y*rz0 - pv[1].y*rz1;						//RJS 10Aug00
    Float	opposite = pv[0].x*rz0 - pv[1].x*rz1;						//RJS 10Aug00
    if (opposite || adjacent)
    {
//DeadCode RJS 10Aug00 		SWord	sin_ang,cos_ang;
        Float	angle;
//#ifdef __GNUC__
        angle=atan2(opposite,adjacent);
        /*#else
                        _asm
                        {
                                fld             opposite
                                fld             adjacent
                                fpatan
                                fstp    angle
                        }
#endif*/

//DeadCode RJS 10Aug00 		angle *= 10430.37835047;
//DeadCode RJS 10Aug00 		SWord	angleofcyl = SWord(angle)-16384;

    D3DVALUE sine,cosine;
    SineCosine_Radian(D3DVALUE(angle-1.57079632),&sine,&cosine);

    xoffset = sine * rad;
    yoffset = cosine * rad;
}
else
    xoffset = yoffset = 0;

                    lastpoint.setPosition( pv[1].x, pv[1].y, pv[1].z );

                    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawTransformedCylinder
//Author		Robert Slater
//Date			Mon 14 Feb 2000
//
//Comments		Special Cylinder Draw Code, for pre-calculated top&bottom
//				vertices, with rotated texture coords.
//
//------------------------------------------------------------------------------
                           HRESULT Lib3D::DrawTransformedCylinder(	const HMATERIAL& hMaterial,	//texture
                                   const DoPointStruc& vertex0,	//p0
                                   const DoPointStruc& vertex1,	//p1
                                   const D3DVALUE& xofftop,		//radius x component
                                   const D3DVALUE& yofftop,		//radius y component
                                   const D3DVALUE& xoffbot,		//radius x component
                                   const D3DVALUE& yoffbot,		//radius y component
                                   const SWord u0,const SWord v0,	//texture coords for tl corner
                                   const SWord u1,const SWord v1)	//texture coords for br corner
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    D3DVALUE fu0,fv0,fu1,fv1;

#ifndef NDEBUG
    if ( insidePoly == true )
        return DDERR_GENERIC;
#endif
    if ((lastError=SetMaterial(hMaterial))!=DD_OK) return lastError;
//DeadCode JON 20Oct00 	if (hMaterial.tsW[0]!=0) // assume this is always the case
    {
        fu0=D3DVALUE(u0)*hMaterial.tsW[0];
        fu1=D3DVALUE(u1)*hMaterial.tsW[0];
        fv0=D3DVALUE(v0)*hMaterial.tsH[0];
        fv1=D3DVALUE(v1)*hMaterial.tsH[0];
    }
//DEADCODE JON 5/22/00 	R3DVERTEX* polyVertArray=vertArray;
//DEADCODE JON 5/22/00 	*polyVertArray=vertex0;
//DEADCODE JON 5/22/00 	polyVertArray[2]=vertex1;
//DEADCODE JON 5/22/00 	D3DVERTEX *pv=(D3DVERTEX *)polyVertArray;

//DEADCODE JON 5/22/00 	SPolygon *sPolygon;

    ALLOCATE_POLYGON(currentPoly,4);
    SVertex *sVertex=currentPoly->pVertexList;

    sVertex[0] = vertex0;
    sVertex[2] = vertex1;

    // Dup. up top and bottom vertices
//DEADCODE JON 5/22/00 	pv[3] = pv[2];	// bottom
//DEADCODE JON 5/22/00 	pv[1] = pv[0];	// top

    sVertex[1]=sVertex[0];
    sVertex[3]=sVertex[2];
    sVertex[0].pNext=&sVertex[1];
    sVertex[1].pNext=&sVertex[2];
    sVertex[2].pNext=&sVertex[3];
    sVertex[3].pNext=sVertex;

#ifdef DO_INDEXED_VB
    sVertex[0].identical =
        sVertex[1].identical =
            sVertex[2].identical =
                sVertex[3].identical = NULL;
#endif

    // X&Y offsets pre-calculated from known top & bot radii
    sVertex[3].x+=xoffbot;
    sVertex[3].y+=yoffbot;
    sVertex[2].x-=xoffbot;
    sVertex[2].y-=yoffbot;

    sVertex[1].x-=xofftop;
    sVertex[1].y-=yofftop;
    sVertex[0].x+=xofftop;
    sVertex[0].y+=yofftop;

    // rotate points by 90% (cos of texture coords)
    currentPoly->pVertexList=sVertex->pNext;

    return _DrawTransformedCylinder( fu0, fv0, fu1, fv1 );
#endif
}
//DEADCODE JON 5/22/00 	R3DMATRIX *pMat=projectionMatrix+projMatStackPos;
//DEADCODE JON 5/22/00 	ULong		theColour = gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 	SetColAlpha( theColour, globAlpha );
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu1;
//DEADCODE JON 5/22/00 	sVertex->tv=fv0;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv+1,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu1;
//DEADCODE JON 5/22/00 	sVertex->tv=fv1;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv+2,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu0;
//DEADCODE JON 5/22/00 	sVertex->tv=fv1;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	Transform(pv+3,&sVertex->d3dtlvert,pMat);
//DEADCODE JON 5/22/00 	sVertex->tu=fu0;
//DEADCODE JON 5/22/00 	sVertex->tv=fv0;
//DEADCODE JON 5/22/00 //DEADCODE JON 3/29/00 	sVertex->color=0xFFFFFFFF;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	sVertex->color=gLightingDesc.ambientRGB;
//DEADCODE JON 5/22/00 //DEADCODE RJS 4/28/00 	SetColAlpha( sVertex->color, globAlpha );
//DEADCODE JON 5/22/00 	sVertex->color = theColour;
//DEADCODE JON 5/22/00 	sVertex->specular=0x00000000;
//DEADCODE JON 5/22/00 	sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	for (int i=4;i!=0;i--)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 	 	sVertex->clipcode=ClipCodeFBLRTB(&sVertex->d3dtlvert);
//DEADCODE JON 5/22/00 		sPolygon->andcode&=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sPolygon->orcode|=sVertex->clipcode;
//DEADCODE JON 5/22/00 		sVertex=sVertex->pNext;
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00 	if (sPolygon->andcode==0)
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 #ifdef	_SHAPE_DEBUG_
//DEADCODE JON 5/22/00 	noPolysDebug++;
//DEADCODE JON 5/22/00 #endif
//DEADCODE JON 5/22/00 	 	if (sPolygon->orcode!=0)
//DEADCODE JON 5/22/00 			GenericPolyClip(sPolygon);
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 		if (sPolygon->vertexcount>2)
//DEADCODE JON 5/22/00 		{
//DEADCODE JON 5/22/00 			D3DVIEWPORT7 vp;
//DEADCODE JON 5/22/00 			pD3DDEV7->GetViewport(&vp);
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 			D3DVALUE sx,sy;
//DEADCODE JON 5/22/00 			D3DVALUE cx,cy;
//DEADCODE JON 5/22/00 			sx=D3DVALUE(vp.dwWidth>>1);
//DEADCODE JON 5/22/00 			sy=-D3DVALUE(vp.dwHeight>>1);
//DEADCODE JON 5/22/00 			cx=D3DVALUE(vp.dwX)+sx;
//DEADCODE JON 5/22/00 			cy=D3DVALUE(vp.dwY)-sy;
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 /*			if (sPolygon->material.f==0)
//DEADCODE JON 5/22/00 			{
//DEADCODE JON 5/22/00 				if (renderMode == HINT_3DRENDER)
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				else
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_2D(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				ADD_POLYGON(plainPolys,sPolygon);
//DEADCODE JON 5/22/00 			}
//DEADCODE JON 5/22/00 			else*/ if (sPolygon->material.isMasked==0)
//DEADCODE JON 5/22/00 			{
//DEADCODE JON 5/22/00 				if (renderMode == HINT_3DRENDER)
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				else
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_2D(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				ADD_POLYGON(texturedPolys,sPolygon);
//DEADCODE JON 5/22/00 				AddEdgeAliasing(sPolygon);
//DEADCODE JON 5/22/00 			}
//DEADCODE JON 5/22/00 			else
//DEADCODE JON 5/22/00 			{
//DEADCODE JON 5/22/00 				if (renderMode == HINT_3DRENDER)
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_SETZ(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				else
//DEADCODE JON 5/22/00 				{
//DEADCODE JON 5/22/00 					PROJECT_2D(sPolygon,cx,cy,sx,sy);
//DEADCODE JON 5/22/00 				}
//DEADCODE JON 5/22/00 				ADD_POLYGON(transparentPolys,sPolygon);
//DEADCODE JON 5/22/00 			}
//DEADCODE JON 5/22/00 		}
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00 	else
//DEADCODE JON 5/22/00 	{
//DEADCODE JON 5/22/00 		DISCARD_POLYGON(sPolygon);
//DEADCODE JON 5/22/00 	}
//DEADCODE JON 5/22/00
//DEADCODE JON 5/22/00 	return S_OK;
//DEADCODE JON 5/22/00 }

char* getRefCount( void* tmp )
{
    static char txt[10];
    IUnknown* j = (IUnknown*)tmp;
    int i = 0;
    if ( tmp )
    {
        j->AddRef();
        i = j->Release();
    }
    sprintf( txt, "%i", i );
    return txt;
}

inline void MonoCls()
{
#ifdef MONO_DEBUG
    Mono_Text.ClsMono();
#endif
}

inline void MonoPrintAt( int x, int y, const char* txt )
{
#ifdef MONO_DEBUG
    Mono_Text.PrintAt( x, y, (UByte*)txt );
#endif
}

inline void MonoPrintVal( int x, int y, double val )
{
#ifdef MONO_DEBUG
    static char str[20];
    sprintf( str, "%f", val );
    Mono_Text.PrintAt( x, y, (UByte*)str );
#endif
}

inline void MonoPrintVal( int x, int y, int val )
{
#ifdef MONO_DEBUG
    static char str[10];
    sprintf( str, "%i", val );
    Mono_Text.PrintAt( x, y, (UByte*)str );
#endif
}

inline void MonoPrintHex( int x, int y, ULong val )
{
#ifdef MONO_DEBUG
    static char str[10];
    sprintf( str, "%X", val );
    Mono_Text.PrintAt( x, y, (UByte*)str );
#endif
}
#ifdef __GNUC__
char * __cdecl _i64toa(
    LONGLONG value, /* [I] Value to be converted */
    char *str,      /* [O] Destination for the converted value */
    int radix)      /* [I] Number base for conversion */
{
    ULONGLONG val;
    int negative;
    char buffer[65];
    char *pos;
    int digit;

    if (value < 0 && radix == 10)
    {
        negative = 1;
        val = -value;
    }
    else
    {
        negative = 0;
        val = value;
    } /* if */

    pos = &buffer[64];
    *pos = '\0';

    do
    {
        digit = val % radix;
        val = val / radix;
        if (digit < 10)
        {
            *--pos = '0' + digit;
        }
        else
        {
            *--pos = 'a' + digit - 10;
        } /* if */
    }
    while (val != 0L);

    if (negative)
    {
        *--pos = '-';
    } /* if */

    memcpy(str, pos, &buffer[64] - pos + 1);
    return str;
}
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseDown
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//------------------------------------------------------------------------------
void Lib3D::CloseDown(bool could_be_legit)
{

    if (frameTimeBuff!=NULL)
    {   /*
        // write out this stuff and delete the store
        class To // cheaty streamer for the int64 type
        {
        public:
            static char* str( __int64 v )
            {
                const int TEXT_SIZE = 32;
                const int BUFF_SIZE = 8;
                static char buff[TEXT_SIZE*BUFF_SIZE];
                static int curI = 0;
                curI++;
                curI%=BUFF_SIZE;
                _i64toa( v, buff+(TEXT_SIZE*curI), 10 );
                return buff+(TEXT_SIZE*curI);
            }
            static char* str( LARGE_INTEGER v )
            {
                return str( v.QuadPart );
            }
        };
        */
		std::fstream timeFile;
        timeFile.open( "3D_Timings.txt", std::fstream::out );
        if ( timeFile.is_open() )
        {
            ULong min = 0xFFFFFFFF;
            ULong max = 0;
            ULong tot = 0;
            int term = curFrameTimeI++;
            curFrameTimeI%=frameTimeBuffSize;
            while ( curFrameTimeI !=term )
            {
                tot+=frameTimeBuff[curFrameTimeI];
                if ( frameTimeBuff[curFrameTimeI] < min )
                    min = frameTimeBuff[curFrameTimeI];
                if ( frameTimeBuff[curFrameTimeI] > max )
                    max = frameTimeBuff[curFrameTimeI];

                timeFile
                << 
				(string) tickCountBuff[curFrameTimeI].QuadPart 
				<< " <-Counter" << " \t"
                << frameTimeBuff[curFrameTimeI] << " ms \t"
                << double( 1000.0/double(frameTimeBuff[curFrameTimeI])) << " fps\n";
                curFrameTimeI++;
                curFrameTimeI%=frameTimeBuffSize;
            }
            timeFile << "Best: \t" << min << " ms \t"
            << double( 1000.0/double(min)) << " fps\n";
            timeFile << "Worst: \t" << max << " ms \t"
            << double( 1000.0/double(max)) << " fps\n";
            timeFile << "Average: \t" << double(double(tot)/double(frameTimeBuffSize)) << " ms \t"
            << double( 1000.0/double(double(tot)/double(frameTimeBuffSize))) << " fps\n";

            timeFile.close();
        }
        delete[] frameTimeBuff;
        delete[] tickCountBuff;
        frameTimeBuff=NULL;
                      tickCountBuff=NULL;
    }
#ifdef	WRITE_DEBUG_FILE
                  fstream debFile;
                  debFile.open( "3D_DEB.txt", std::fstream::out );
                  if ( !debFile.is_open() )
    {
        INT3;
    }
    debFile << "Entered 3D closedown\n" << flush;
    debFile.close();
#endif

#ifdef _ONLY_ONE_LANSDCAPE_TEXTURE
    landscapeTexture = NULL;
#endif
    paletteTable=NULL;
    if (!could_be_legit)
        INT3;
    while ( supportedTextFmt )
    {
        DDTextureFormat* next = supportedTextFmt->next;
        delete supportedTextFmt;
        supportedTextFmt = next;
    }
    if ( diagString )
    {
        delete[] diagString;
        diagString = NULL;
    }
    MonoCls();
    int monoline = 0;
    MonoPrintAt( 0, monoline++, "entered closedown                     " );
    if ( lastError !=S_OK )
    {
        char *ErrorDesc;
        GetErrorDesc( lastError, ErrorDesc );
    }

//DeadCode JON 20Oct00 	ULong count = 0;
    if (pD3D7)		 													//JON 10Jul00
    {
        pD3D7->EvictManagedTextures();
    }
    MonoPrintAt( 5, monoline++, "evicted textures                       " );

    DeRefAndNULL( IUnknownPtrRef( gpD3DVB7 ) ); //glob vertex buffer
    DeRefAndNULL( IUnknownPtrRef( gpD3DVBL7 ) ); //line vertex buffer
    MonoPrintAt( 5, monoline++, "released both vertex buffers                 " );

    if ((flags&F_TEXTURECANBERENDERTARGET)!=0)	 //JON 15Jun00
    {
        MonoPrintAt( 0, monoline, getRefCount(  pDDS7LandZB ) );
        DeRefAndNULL( IUnknownPtrRef( pDDS7LandZB ) );
        MonoPrintAt( 5, monoline++, "released land z                   " );
        MonoPrintAt( 0, monoline, getRefCount(  pDDS7LandRT ) );
        DeRefAndNULL( IUnknownPtrRef( pDDS7LandRT ) );
        MonoPrintAt( 5, monoline++, "released land                   " );
        MonoPrintAt( 0, monoline, getRefCount(  pDDS7MirrorZB ) );
        DeRefAndNULL( IUnknownPtrRef( pDDS7MirrorZB ) );
        MonoPrintAt( 5, monoline++, "released mirror z                   " );
// no need to free the mirror texture - it's been done already with the other textures...
//DeadCode JON 17Aug00 		MonoPrintAt( 0, monoline, getRefCount(  pDDS7MirrorRT ) );
//DeadCode JON 17Aug00 		DeRefAndNULL( IUnknownPtrRef( pDDS7MirrorRT ) );
//DeadCode JON 17Aug00 		MonoPrintAt( 5, monoline++, "released mirror                  " );

    }

    MonoPrintAt( 0, monoline, getRefCount(  pDDSZ7 ) );
    DeRefAndNULL( IUnknownPtrRef( pDDSZ7 ) ); // back buffer zbuffer
    MonoPrintAt( 5, monoline++, "released z buffer                   " );

    MonoPrintAt( 0, monoline, getRefCount(  pDDSB7 ) );
    DeRefAndNULL( IUnknownPtrRef( pDDSB7 ) ); // back buffer
    MonoPrintAt( 5, monoline++, "released back buffer                   " );

    MonoPrintAt( 0, monoline, getRefCount(  pDDSP7 ) );
    DeRefAndNULL( IUnknownPtrRef( pDDSP7 ) ); // primary surface
    MonoPrintAt( 5, monoline++, "released primary surface                 " );

    MonoPrintAt( 0, monoline, getRefCount(  pDD7 ) );
    if (pDD7)	// direct draw object
    {
        pDD7->SetCooperativeLevel(hwTop,DDSCL_NORMAL);
        DeRefAndNULL( IUnknownPtrRef( pDD7 ) );
    }
    MonoPrintAt( 5, monoline++, "released DirectDraw object                   " );

    MonoPrintAt( 0, monoline, getRefCount(  pD3DDEV7 ) );
    if ( (flags&F_WINDOWED) )
    {
#ifndef _NO_D3D_DEV_RELEASE
        DeRefAndNULL( IUnknownPtrRef( pD3DDEV7 ) ); //D3D device
#endif
    }
    else
        pD3DDEV7 = NULL;

    MonoPrintAt( 5, monoline++, "released D3D device                    " );

    MonoPrintAt( 0, monoline, getRefCount(  pD3D7 ) );
    DeRefAndNULL( IUnknownPtrRef( pD3D7 ) );
    MonoPrintAt( 5, monoline++, "released D3D object                   " );

    MonoPrintAt( 0, monoline++, "exited closedown                     " );

#ifdef	WRITE_DEBUG_FILE
    debFile.open( "3D_DEB.txt", std::fstream::out );
    if ( !debFile.is_open() )
    {
        INT3;
    }
    debFile << "Exited 3D closedown\n" << flush;
    debFile.close();
#endif

    CloseDiags();
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 //	Mono_Text.ClsMono();
//DeadCode CSB 21Jul00 //	int monoline = 0;
//DeadCode CSB 21Jul00 //	Mono_Text.PrintAt( 0, monoline++, (UByte*)"entered closedown                     " );
//DeadCode CSB 21Jul00 //	char *ErrorDesc;
//DeadCode CSB 21Jul00 //	GetErrorDesc( lastError, ErrorDesc );
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 	ULong count = 0;
//DeadCode CSB 21Jul00 	if (pD3D7)		 													//JON 10Jul00
//DeadCode CSB 21Jul00 	{
//DeadCode CSB 21Jul00 		pD3D7->EvictManagedTextures();
//DeadCode CSB 21Jul00 	}
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 	if (pDD7)	// direct draw object
//DeadCode CSB 21Jul00 	{
//DeadCode CSB 21Jul00 		pDD7->SetCooperativeLevel(hwTop,DDSCL_NORMAL);
//DeadCode CSB 21Jul00 		DeRefAndNULL( IUnknownPtrRef( pDD7 ) );
//DeadCode CSB 21Jul00 	}
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 	if (pD3D7)	// D3D Object
//DeadCode CSB 21Jul00 	{
//DeadCode CSB 21Jul00 //		DeRefAndNULL( IUnknownPtrRef( pD3D7 ) );
//DeadCode CSB 21Jul00 		count=pD3D7->Release();
//DeadCode CSB 21Jul00 		pD3D7=NULL;
//DeadCode CSB 21Jul00 	}
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 //	DeRefAndNULL( IUnknownPtrRef( pD3DDEV7 ) ); //D3D device
//DeadCode CSB 21Jul00 	if ( pD3DDEV7 != NULL )
//DeadCode CSB 21Jul00 	{
//DeadCode CSB 21Jul00 		if ( (flags&F_WINDOWED) )
//DeadCode CSB 21Jul00 			count =pD3DDEV7->Release();
//DeadCode CSB 21Jul00 		pD3DDEV7=NULL;
//DeadCode CSB 21Jul00 	}
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 	if (flags&F_WINDOWED)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 	{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (gpD3DVB7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			count=gpD3DVB7->Release();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			gpD3DVB7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (gpD3DVBL7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			count=gpD3DVBL7->Release();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			gpD3DVBL7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (pD3DDEV7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			count=pD3DDEV7->Release();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pD3DDEV7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (pD3D7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 //deadcode			if ((flags&F_CANTMANAGETEXTURES)==0)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pD3D7->EvictManagedTextures();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			count=pD3D7->Release();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pD3D7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 //		if (pDDS7LandRT != pDDSB7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if ((flags&F_TEXTURECANBERENDERTARGET)!=0)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pDDS7LandZB=NULL; //remove the z buffer for the landscape textures
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			while (pDDS7LandRT->Release()>0);
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pDDS7LandRT=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (pDDSZ7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pDDSZ7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (pDDSB7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			while (pDDSB7->Release()>0);
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		pDDSB7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (pDDSP7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			count=pDDSP7->Release();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pDDSP7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		if (pDD7)
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		{
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pDD7->SetCooperativeLevel(hwTop,DDSCL_NORMAL);
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			count=pDD7->Release();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			while ( count )
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 				count=pDD7->Release();
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 			pDD7=NULL;
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 		}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 	}
//DeadCode CSB 21Jul00 //TempCode JON 13Jul00 	else
//DeadCode CSB 21Jul00 	{
//DeadCode CSB 21Jul00 		DeRefAndNULL( IUnknownPtrRef( gpD3DVB7 ) ); //glob vertex buffer
//DeadCode CSB 21Jul00 		DeRefAndNULL( IUnknownPtrRef( gpD3DVBL7 ) ); //line vertex buffer
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 		if ((flags&F_TEXTURECANBERENDERTARGET)!=0)	 //JON 15Jun00
//DeadCode CSB 21Jul00 		{
//DeadCode CSB 21Jul00 			DeRefAndNULL( IUnknownPtrRef( pDDS7LandZB ) );
//DeadCode CSB 21Jul00 			DeRefAndNULL( IUnknownPtrRef( pDDS7LandRT ) );
//DeadCode CSB 21Jul00 			DeRefAndNULL( IUnknownPtrRef( pDDS7MirrorZB ) );
//DeadCode CSB 21Jul00 			DeRefAndNULL( IUnknownPtrRef( pDDS7MirrorRT ) );
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 		}
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 		DeRefAndNULL( IUnknownPtrRef( pDDSZ7 ) ); // back buffer zbuffer
//DeadCode CSB 21Jul00 		DeRefAndNULL( IUnknownPtrRef( pDDSB7 ) ); // back buffer
//DeadCode CSB 21Jul00 		DeRefAndNULL( IUnknownPtrRef( pDDSP7 ) ); // primary surface
//DeadCode CSB 21Jul00
//DeadCode CSB 21Jul00 	}
//DeadCode CSB 21Jul00 //DeadCode JON 11Jul00 	pDD7=NULL;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderPointList
//Author		Paul.
//Date			Mon 10 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::RenderPointList(SPoint *pHead)
{
#ifndef	_NODOTS_
    SPoint *pCur;
    HRESULT hr;
    D3DTLVERTEX *pIns;
    ULong vertcnt;
    lpD3DVB7=gpD3DVBL7;//gpD3DVB7;										//RJS 15Aug00
    InlineSetCurrentMaterial( hLastMaterial, IS_PLAIN );

    while (pHead!=NULL)
    {
        hr=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
        vertcnt=0;
        pCur=pHead;
        while (vertcnt<1023 && pCur!=NULL)
        {
            *pIns++=D3DTLVERTEX(pCur->vertex.getR3DVert());
            pCur=pCur->pNext;
            vertcnt++;
        }
        hr=lpD3DVB7->Unlock();
        hr=pD3DDEV7->DrawPrimitiveVB(D3DPT_POINTLIST,lpD3DVB7,0,vertcnt,0);
        pHead=pCur;
    }
#else
    pHead=NULL;
#endif
    lpD3DVB7=NULL;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderLineList
//Author		Paul.
//Date			Mon 10 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::RenderLineList(SLine *pHead)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
#else
    SLine *pCur;
//DEADCODE RJS 4/17/00 static	D3DTLVERTEX  pInsPOO[1024];
    D3DTLVERTEX *pIns;
//DEADCODE RJS 4/17/00 	D3DTLVERTEX3 *pIns;
//DeadCode RJS 06Jun100 	HRESULT hr;
    ULong vertcnt;
    lpD3DVB7=gpD3DVBL7;												//RJS 17Apr00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	// Force the Z-Buffer State
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );	//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);//RJS 17May00
//DeadCode JON 17Aug00   	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );//RJS 17May00
//TempCode JON 31Oct00 	InlineSetCurrentMaterial( hLastMaterial, IS_PLAIN );

    while (pHead!=NULL)
    {
        lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
//		char * ErrorDesc;
//		GetErrorDesc( hr, ErrorDesc );
        vertcnt=0;
        pCur=pHead;
//DEADCODE RJS 4/17/00 		pIns = pInsPOO;
        while (vertcnt<1023 && pCur!=NULL)
        {
            *pIns++=D3DTLVERTEX(pCur->vertices[0].getR3DVert());
            *pIns++=D3DTLVERTEX(pCur->vertices[1].getR3DVert());

//DeadCode JON 23Aug00 			*pIns++ = pCur->vertices[0];
//DeadCode JON 23Aug00 			*pIns++ = pCur->vertices[1];
//DEADCODE RJS 4/17/00 			*pIns++=pCur->vertices[0]3;
//DEADCODE RJS 4/17/00 			*pIns++=pCur->vertices[1]3;
            pCur=pCur->pNext;
            vertcnt+=2;
        }

        lastError=lpD3DVB7->Unlock();
//DeadCode JON 30Oct00 		lastError=pD3DDEV7->SetTexture(0,NULL);

        lastError=pD3DDEV7->DrawPrimitiveVB(D3DPT_LINELIST,lpD3DVB7,0,vertcnt,0);
//DEADCODE RJS 4/17/00 		hr=pD3DDEV7->DrawPrimitive(D3DPT_LINELIST,D3DFVF_TLVERTEX,pInsPOO,vertcnt,0);

        pHead=pCur;
    }
    lpD3DVB7=NULL;
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTLPolyList
//Author		Jon.
//Date			Tue 8 Feb 2000
//
//------------------------------------------------------------------------------
#ifndef NO_HARD_TNL
void Lib3D::RenderTLPolyList(SPolygon *pHead)
{
    return;
    SPolygon *pTail,*pCur;
    D3DVERTEX *pIns;
    SVertex *pSVert;
    ULong vertcnt;
    ULong verttot;
    ULong offset;
    int	i;
    HRESULT hr;
    HMATERIAL curmat;

    lpD3DVB7=gpD3DVB7;
    offset=ULong(&pHead->material)-ULong(pHead);
    pHead=(SPolygon*)RadixSortAscending((radix_sort_t*)pHead,offset);
    curmat=0xFFFF;
//	hr=pD3DDEV7->SetMaterial(&materialMapped);
    LIGHTFLAG lastlight = LF_DUMMY;
    pTail=pHead;
    while (pHead!=NULL)
    {
        vertcnt=0;
        pCur=pHead;
        while (pTail!=NULL)
        {
            vertcnt+=pTail->vertexcount;
            if (vertcnt>2048) break;
            pTail=pTail->pNext;
        }
        hr=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
        while (pTail!=pCur)
        {
            pSVert=pCur->pVertexList;
            memcopy( pIns, pSVert, pCur->vertexcount*sizeof(TNLSVertex) );
            pIns+=pCur->vertexcount;
            pCur=pCur->pNext;
        }
        hr=lpD3DVB7->Unlock();

        pCur=pHead;
        vertcnt=0;
        while (pTail!=pCur)
        {
            if (!SameMaterial(pCur->material,curmat))
            {
                curmat=pCur->material;
                InlineSetCurrentMaterial(curmat);
            }
            if ( lastlight != pCur->lightMode )
            {
                SetCurrentLighting( LIGHTFLAG(pCur->lightMode) );
                lastlight=LIGHTFLAG(pCur->lightMode);
            }
            verttot=pCur->vertexcount;
            hr=pD3DDEV7->DrawPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,vertcnt,verttot,0);
            vertcnt+=verttot;
            pCur=pCur->pNext;
        }
        pHead=pTail;
    }
    lpD3DVB7=NULL;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTransTLPolyList
//Author		Jon.
//Date			Tue 8 Feb 2000
//
//------------------------------------------------------------------------------
void Lib3D::RenderTransTLPolyList(SPolygon *pHead)
{
    return;
    SPolygon *pTail,*pCur;
    D3DVERTEX *pIns;
    SVertex *pSVert;
    ULong vertcnt;
    ULong verttot;
    ULong offset;
    SWord lastTransMatrix = -1;
    int	i;
    HRESULT hr;
    HMATERIAL curmat;

    // set the view matrix to being the identity
    pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_VIEW,&IDENTITY);

    lpD3DVB7=gpD3DVB7;
    offset=ULong(&pHead->material)-ULong(pHead);
    pHead=(SPolygon*)RadixSortDescending((radix_sort_t*)pHead,offset);
    curmat=0xFFFF;
    hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);
    hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);
    hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,TRUE);
    pTail=pHead;

    LIGHTFLAG lastlight = LF_DUMMY;

    while (pHead!=NULL)
    {
        vertcnt=0;
        pCur=pHead;
        while (pTail!=NULL)
        {
            vertcnt+=pTail->vertexcount;
            if (vertcnt>2048) break;
            pTail=pTail->pNext;
        }
        hr=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
        while (pTail!=pCur)
        {
            pSVert=pCur->pVertexList;
            memcopy( pIns, pSVert, pCur->vertexcount*sizeof(TNLSVertex) );
            pIns+=pCur->vertexcount;
            pCur=pCur->pNext;
        }
        hr=lpD3DVB7->Unlock();

        pCur=pHead;
        vertcnt=0;
        while (pTail!=pCur)
        {
            if (!SameMaterial(pCur->material,curmat))
            {
                curmat=pCur->material;
                InlineSetCurrentMaterial(curmat);
            }
            if ( lastTransMatrix!=pCur->transMat )
            {
                // update the world matrix on the card to being the current one...
                lastTransMatrix=pCur->transMat;
                pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_WORLD,&transpMatrix[lastTransMatrix]);
                pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_PROJECTION,&projectionMatrix[pCur->projMat]);
            }
            if ( lastlight != pCur->lightMode )
            {
                SetCurrentLighting( LIGHTFLAG(pCur->lightMode) );
                lastlight=LIGHTFLAG(pCur->lightMode);
            }
            verttot=pCur->vertexcount;
            hr=pD3DDEV7->DrawPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,vertcnt,verttot,0);
            vertcnt+=verttot;
            pCur=pCur->pNext;
        }
        pHead=pTail;
    }
    lpD3DVB7=NULL;

    pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
}
#endif
//#pragma warnmsg ( "inline me" )
inline bool Lib3D::CkValidDevice()
{
    DWORD dwNumPasses;
    lastError=pD3DDEV7->ValidateDevice( &dwNumPasses );
    if ( lastError != 0 )
    {
#ifndef NDEBUG
        char* ErrorDesc;
        GetErrorDesc( lastError, ErrorDesc );
#endif
        return false;
    }
    return true;
}




//////////////////////////////////////////////////////////////////////
//
// Function:    SetUpRenderBlocks

// Date:		17/08/00
// Author:		JON
//
//Description:	builds the renderstate blocks and validates them....
//
//
////////////////////////////////////////////////////////////////////////
HRESULT Lib3D::SetUpRenderBlocks( void )
{

//tempcode JON 16/03/01		fstream debFile;
//tempcode JON 16/03/01		debFile.open( "3D_DEB.txt", std::fstream::out );
//tempcode JON 16/03/01		if ( !debFile.is_open() )
//tempcode JON 16/03/01		{
//tempcode JON 16/03/01			INT3;
//tempcode JON 16/03/01		}
//tempcode JON 16/03/01		debFile << "Entered 3D closedown\n" << flush;
//tempcode JON 16/03/01		debFile.close();
//#pragma warnmsg ( "remove me" )
//	prefZType = D3DZB_USEW;
    char* ErrorDesc=NULL;

    bool doValidate = (flags&F_CANTVALIDATEDEVICE)==0;

    if( doValidate )
        OutDiagLine( "Setting up render state, using validation\n" );
    else
        OutDiagLine( "Setting up render state, no validation\n" );

    //	pD3DDEV7->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
#define CheckValidDevice( arg ) (doValidate?CkValidDevice( arg ):true)

    // make sure that everything is ok to begin with (thanks to matrox G400 for needing this),,,
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );		//ATI cards only accept TEXTURE in COLORARG1
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    if (!CheckValidDevice( ) )
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating basic state, %s\n", ErrorDesc );
        INT3;
        CloseDown();
    }


//	EnableFogging( true );
    // first set up the anti-aliasing - is same for each block...
    switch ( textureBlending )
    {
    case HINT_NOBLEND:
        OutDiagLine( "Using no texture blending\n" );
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_POINT);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_POINT);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_POINT);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_POINT);
        break;
    case HINT_TRILINEAR:
        OutDiagLine( "Using tri-linear blending\n" );
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        break;
    case HINT_BILINEAR:
        OutDiagLine( "Using bi-linear blending\n" );
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        break;
    }

    while ( !CheckValidDevice() )
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating filtering mode, %s\n", ErrorDesc );

        if ( textureBlending == HINT_NOBLEND )
        {
            INT3;
            CloseDown();
            return DDERR_GENERIC;
        }

        textureBlending = HINTS(ULong(textureBlending)+1);
        switch ( textureBlending )
        {
        case HINT_NOBLEND:
            OutDiagLine( "Using no texture blending\n" );
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_POINT);
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_POINT);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_POINT);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_POINT);
            break;
        case HINT_TRILINEAR:
            OutDiagLine( "Using tri-linear blending\n" );
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
            break;
        case HINT_BILINEAR:
            OutDiagLine( "Using bi-linear blending\n" );
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
            lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
            break;
        }

    }

    masterTextureBlending = textureBlending;

    // other global stuff
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_CLIPPING,FALSE);
    if ( !CheckValidDevice( ) )
    {
        INT3;
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error switching off clipping, %s\n", ErrorDesc );
        CloseDown();
        return DDERR_GENERIC;
    }

    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_EXTENTS,FALSE);
    if ( !CheckValidDevice( ) )
    {
        INT3;
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error switching off extents, %s\n", ErrorDesc );
        CloseDown();
        return DDERR_GENERIC;
    }

    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DITHERENABLE,TRUE);	// fixes sky banding in 16 bit colour mode JON 2Feb01


    // we never need these - swithc 'em off just incase.
    lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

    // always do this
    lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_TEXCOORDINDEX,0);
    lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_TEXCOORDINDEX,1);
    lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_ADDRESS,D3DTADDRESS_WRAP);


#ifdef	_NOTEXTURES_
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG2 );
#else
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
#endif
    if ( !CheckValidDevice() )
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating colour modulation, %s\n", ErrorDesc );
        INT3;
        CloseDown();
        return DDERR_GENERIC;
    }

    // stuff for no alpha
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);
    if ( !CheckValidDevice( ) )
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating no alpha mode, %s\n", ErrorDesc );
        INT3;
        CloseDown();
        return DDERR_GENERIC;
    }


//TempCode JON 27Sep00    // Set the depth-buffering states
//TempCode JON 27Sep00     m_pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, TRUE );
//TempCode JON 27Sep00     m_pd3dDevice->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
//TempCode JON 27Sep00     m_pd3dDevice->SetRenderState( D3DRENDERSTATE_ZFUNC,   D3DCMP_LESSEQUAL );
//TempCode JON 27Sep00     m_pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, m_dwDepthBufferType );

    // Force the Z-Buffer State
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);
    if ( flags&F_FAKE_W )
    {
        OutDiagLine( "Faking W buffer with Z\n" );
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE );
    }
    else
    {
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );
    }


    if ( !CheckValidDevice( ) )
    {
        INT3;
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating z buffer mode, %s\n", ErrorDesc );
        CloseDown();
        return DDERR_GENERIC;
    }

    // render block 0 - landscape texture, no dither/sea animation...
    lastError=pD3DDEV7->SetTextureStageState( 0,D3DTSS_ADDRESS,D3DTADDRESS_MIRROR);
//	lastError=pD3DDEV7->SetTextureStageState( 0,D3DTSS_ADDRESS,D3DTADDRESS_CLAMP);

    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    if ( textureBlending == HINT_TRILINEAR )
    {
        // turn down to bi-linear for the primary stage - we've got no mipmaps anyhow
        OutDiagLine( "Turning down to bi-linear filtering for landscape\n" );
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
    }

    if ( !CheckValidDevice( ) )
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating render block 0 - landscape texture, no dither/sea animation, %s\n", ErrorDesc );
        INT3;
        CloseDown();
        return DDERR_GENERIC;
    }
    lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[0] );

    // render block 1 - landscape texture, dither/sea animation...
    if ( !(flags&F_CANTBLENDTEXTURES) ) // keep same if we can't do this...
    {
//deadcode JON 16/03/01			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
//deadcode JON 16/03/01			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_TEXTURE );
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_CURRENT );
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_ADDSIGNED );
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

        lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
        lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

        if ( CheckValidDevice( ) )
        {
            OutDiagLine( "validated render block 1 - landscape texture, dither/sea animation\n" );
            lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[1] );
        }
        else   // oops can't do that (for whatever reason...)
        {
//tempcode JON 19/03/01				GetErrorDesc( lastError, ErrorDesc );
//tempcode JON 19/03/01				OutDiagLine( "Error validating render block 1 - landscape texture, dither/sea animation %s\n", ErrorDesc );
//tempcode JON 19/03/01
//tempcode JON 19/03/01				OutDiagLine( "Turning off diffuse lighting\n" );
//tempcode JON 19/03/01				lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
//tempcode JON 19/03/01
//tempcode JON 19/03/01	//			OutDiagLine( "Turning down texture filtering\n" );
//tempcode JON 19/03/01	//			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_POINT);
//tempcode JON 19/03/01
//tempcode JON 19/03/01	//			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_POINT);
//tempcode JON 19/03/01	//			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_POINT);
//tempcode JON 19/03/01	//			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_POINT);
//tempcode JON 19/03/01	//			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_POINT);
//tempcode JON 19/03/01
//tempcode JON 19/03/01				if ( CheckValidDevice( ) )
//tempcode JON 19/03/01				{
//tempcode JON 19/03/01					OutDiagLine( "validated render block 1 - landscape texture, dither/sea animation\n" );
//tempcode JON 19/03/01					lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[1] );
//tempcode JON 19/03/01				} else // oops can't do that (for whatever reason...)
//tempcode JON 19/03/01				{
            GetErrorDesc( lastError, ErrorDesc );
            OutDiagLine( "Error validating render block 1 - landscape texture, dither/sea animation %s\n", ErrorDesc );
            OutDiagLine( "Turning off dither\n" );
            stateBlocks[1]=stateBlocks[0];
//tempcode JON 19/03/01				}
//tempcode JON 19/03/01
//tempcode JON 19/03/01				#ifdef	_NOTEXTURES_
//tempcode JON 19/03/01					lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG2 );
//tempcode JON 19/03/01				#else
//tempcode JON 19/03/01					lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
//tempcode JON 19/03/01				#endif
//tempcode JON 19/03/01
        }
    }
    else
    {
        OutDiagLine( "Flags disable render block 1 - landscape texture, dither/sea animation\n" );
        OutDiagLine( "Using no dither" );
        stateBlocks[1]=stateBlocks[0];
    }

    // render block 2 - Single Texture - No Alpha
    lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[0] );
    if ( textureBlending == HINT_TRILINEAR )
    {
        // back to tri-linear
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
    }

    lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_ADDRESS,D3DTADDRESS_WRAP);

    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    if ( CheckValidDevice( ) )
    {
        OutDiagLine( "validated render block 2 - Single Texture - No Alpha\n", ErrorDesc );
        lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[2] );
    }
    else
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating render block 2 - Single Texture - No Alpha, %s\n", ErrorDesc );
        INT3;
        CloseDown();
        return DDERR_GENERIC;
    }

    // render block 3 - Double texture - No Alpha
    if ( !(flags&F_CANTBLENDTEXTURES) ) // keep same if we can't do this...
    {
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_BLENDTEXTUREALPHA);
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );

        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);

        lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
        lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    }
    else
    {
        OutDiagLine( "Flags disable render block 3 - Double texture - No Alpha\n" );
    }
    if ( CheckValidDevice( ) )
    {
        OutDiagLine( "Validated render block 3 - Double texture - No Alpha\n" );
        lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[3] );
    }
    else   // oops can't do that (for whatever reason...)
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating render block 3 - Double texture - No Alpha, %s\n", ErrorDesc );
        stateBlocks[3]=stateBlocks[2];
        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[2] );
    }

    // stuff for alpha
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);		//how much is put on top
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);	//how much shows through underneath
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,TRUE);
    // Force the Z-Buffer State
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);
    if ( flags&F_FAKE_W )
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE );
    else
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );

    // render block 4 - Single Texture - Non Solid Alpha
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
#ifndef _NO_ALPHA
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
#endif
    if ( !CheckValidDevice( ) )
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating render block 4 - Single Texture - Non Solid Alpha, %s\n", ErrorDesc );
        OutDiagLine( "Trying no alpha modulation\n" );
        lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
        if ( !CheckValidDevice( ) )
        {
            GetErrorDesc( lastError, ErrorDesc );
            OutDiagLine( "Error validating render block 4 - Single Texture - Non Solid Alpha, %s\n", ErrorDesc );
            INT3;
            CloseDown();
            return DDERR_GENERIC;
        }
    }
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    if ( !CheckValidDevice( ) )
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating render block 4 - Single Texture - Non Solid Alpha, %s\n", ErrorDesc );
        INT3;
        CloseDown();
        return DDERR_GENERIC;
    }
    lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[4] );

    // render block 5 - Single Texture - Solid Alpha
    if ( (flags&F_STIPPLEALPHA)==0 &&
            ((lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE))==S_OK) &&
            CheckValidDevice( ) )
    {
        OutDiagLine( "Validated render block 5 - Single Texture - Solid Alpha\n" );
        lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[5] );
    }
    else
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "render block 5 - Single Texture - Solid Alpha, %s\n", ErrorDesc );
        OutDiagLine( "Either this is flagged stippled or we have a problem\n" );
        stateBlocks[5]=stateBlocks[4];
        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[4] );
    }

    // render block 6 - Double Texture - Non Solid Alpha
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);
    if ( !(flags&F_CANTBLENDTEXTURES) ) // keep same if we can't do this...
    {
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE);
//TempCode JON 6Sep00 		lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_BLENDTEXTUREALPHA);
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );

        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAARG2, D3DTA_CURRENT );
#ifndef _NO_ALPHA
        lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
#endif
        if ( !CheckValidDevice( ) )
        {
            lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG2 );
        }

        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
        lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);

        lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
        lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    }
    else
    {
        OutDiagLine( "Flags disable render block 6 - Double Texture - Non Solid Alpha\n" );
    }
    if ( CheckValidDevice( ) )
    {
        OutDiagLine( "Validated render block 6 - Double Texture - Non Solid Alpha\n" );
        lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[6] );
    }
    else // oops can't do that (for whatever reason...)
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error validating render block 6 - Double Texture - Non Solid Alpha, %s\n", ErrorDesc );
        stateBlocks[6]=stateBlocks[4];
        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[4] );
    }

    // render block 7 - Double Texture - Solid Alpha
    if ( (flags&F_STIPPLEALPHA)==0 &&
            ((lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE))==S_OK) &&
            CheckValidDevice( ) )
    {
        OutDiagLine( "Validated render block 7 - Double Texture - Solid Alpha\n" );
        lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[7] );
    }
    else
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "render block 7 - Double Texture - Solid Alpha, %s\n", ErrorDesc );
        OutDiagLine( "Either this is flagged stippled or we have a problem\n" );
        stateBlocks[7]=stateBlocks[5];
        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[5] );
    }

    // stuff for no alpha
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);

    // Force the Z-Buffer State
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);
    if ( flags&F_FAKE_W )
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE );
    else
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );

    // render block 8 - Plain Colour - No Alpha.
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DITHERENABLE,TRUE);	// fixes sky banding in 16 bit colour mode JON 2Feb01
    lastError=pD3DDEV7->SetTexture(0,NULL);
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    if ( CheckValidDevice( ) )
    {
        OutDiagLine( "Validated render block 8 - Plain Colour - No Alpha\n" );
        lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[8] );
    }
    else
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error Validating render block 8 - Plain Colour - No Alpha, %s\n", ErrorDesc );
        INT3;
        CloseDown();
        return DDERR_GENERIC;
    }

    // stuff for alpha
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);		//how much is put on top
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);	//how much shows through underneath
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,TRUE);
    // Force the Z-Buffer State
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);
    lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);
    if ( flags&F_FAKE_W )
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE );
    else
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );

    // render block 9 - Plain Colour - with Alpha (always non solid...)
#ifndef _NO_ALPHA
    pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG2 );
#endif
    if ( CheckValidDevice( ) )
    {
        OutDiagLine( "Validated render block 9 - Plain Colour - with Alpha (always non solid...)\n" );
        lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &stateBlocks[9] );
    }
    else
    {
        GetErrorDesc( lastError, ErrorDesc );
        OutDiagLine( "Error Validating render block 9 - Plain Colour - with Alpha (always non solid...), %s\n", ErrorDesc );
        INT3;
        CloseDown();
        return DDERR_GENERIC;
    }


    OutDiagLine( "Completed render state creation\n" );
    return lastError;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ChangeRenderStateFog
//
// Date:		22/08/00
// Author:		JON
//
//Description:	changes the fog start and end values stored in the renderstate...
// 				render blocks are optimised for gfx card memory - shouldn't be called often.
//
//////////////////////////////////////////////////////////////////////
inline void Lib3D::ChangeRenderStateFog( float curFogStart, float curFogEnd )
{

    DWORD newStateBlocks[MAX_TEXTURE_OPTS];
    for (int i = 0; i < MAX_TEXTURE_OPTS; i++ )
    {
        int j;
        for (j = 0; j < i && stateBlocks[i] != stateBlocks[j]; j++ )
        {
            /*search for duplicate*/
        }
        if ( i != j )
        {
            //  a duplicate state block has been\found...
            newStateBlocks[i] = newStateBlocks[j];
        }
        else
        {
            lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[i] );
            lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGSTART,*(DWORD*)&curFogStart);
            lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGEND,*(DWORD*)&curFogEnd);
            lastError=pD3DDEV7->DeleteStateBlock( stateBlocks[i] );
            lastError=pD3DDEV7->CreateStateBlock( D3DSBT_PIXELSTATE, &newStateBlocks[i] );
        }
    }
    for (int ii=0; ii<MAX_TEXTURE_OPTS; ii++ )
    {
        stateBlocks[ii] = newStateBlocks[ii];
    }
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCurrentMaterial
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------

//#pragma warnmsg ( "inline me" )
//DeadCode JON 17Aug00 inline void Lib3D::SetTransCurrentMaterial(const HMATERIAL& mat)
//DeadCode JON 17Aug00 {
//DeadCode JON 17Aug00 //DeadCode JON 14Jun00 	materialMapped.diffuse.dvA=
//DeadCode JON 17Aug00 //DeadCode JON 14Jun00 		materialMapped.ambient.dvA=D3DVALUE(mat.c)*(1/255.f);
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	if (mat.f)													//RJS 06Jun00
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 		if (mat.p[0]->blendType != lastBlendType)
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 			lastBlendType = AlphaBlendTypes(mat.p[0]->blendType);
//DeadCode JON 17Aug00 			switch (lastBlendType)
//DeadCode JON 17Aug00 			{
//DeadCode JON 17Aug00 			case BLEND_SRCALPHA_DESTSOLID:
//DeadCode JON 17Aug00 //Temp				pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);
//DeadCode JON 17Aug00 				lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
//DeadCode JON 17Aug00 			break;
//DeadCode JON 17Aug00 			default:
//DeadCode JON 17Aug00 			case BLEND_SRCALPHA_DESTINVSRCALPHA:
//DeadCode JON 17Aug00 //Temp				pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);
//DeadCode JON 17Aug00 				lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);
//DeadCode JON 17Aug00 			break;
//DeadCode JON 17Aug00 			}
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 	}
//DeadCode JON 17Aug00 	else
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 		// Plain Colour will always use the same blend...
//DeadCode JON 17Aug00 		if (lastBlendType != BLEND_SRCALPHA_DESTINVSRCALPHA)
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 			lastBlendType = BLEND_SRCALPHA_DESTINVSRCALPHA;
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 	}
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	CheckValidDevice( pD3DDEV7 );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	SetCurrentMaterial( mat );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	if ( mat.f == 0 )
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 		pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG2 );
//DeadCode JON 17Aug00 	}
//DeadCode JON 17Aug00 }
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 //#pragma warnmsg ( "inline me" )
//DeadCode JON 17Aug00 inline void Lib3D::SetPlainMaterial(/*const HMATERIAL& mat*/)
//DeadCode JON 17Aug00 {
//DeadCode JON 17Aug00 //DeadCode RJS 06Jun100 	HRESULT hr;
//DeadCode JON 17Aug00 //	SetCurrentLighting();
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	// plain col poly
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE);
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->LightEnable(0,TRUE);
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTexture(0,NULL);
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 	hr=pD3DDEV7->SetMaterial(&materialTable[mat.c]);
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 #ifndef NDEBUG
//DeadCode JON 17Aug00 	CheckValidDevice( pD3DDEV7 );
//DeadCode JON 17Aug00 #endif
//DeadCode JON 17Aug00 }
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 //#pragma warnmsg ( "inline me" )
//DeadCode JON 17Aug00 inline void Lib3D::SetAntiAliasing( const HMATERIAL& mat )
//DeadCode JON 17Aug00 {
//DeadCode JON 17Aug00 	if ( mat.isMasked==MSK_MASKED )
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 	} else
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 		switch (textureBlending)
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 		case HINT_NOBLEND:
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_POINT);
//DeadCode JON 17Aug00 			break;
//DeadCode JON 17Aug00 		case HINT_TRILINEAR:
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //TEMPCODE JON 4/6/00 			hr=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_ANISOTROPIC );//D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //TEMPCODE JON 4/6/00 			hr=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_ANISOTROPIC );//D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 	//		hr=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAXANISOTROPY ,2 );
//DeadCode JON 17Aug00 			break;
//DeadCode JON 17Aug00 		case HINT_BILINEAR:
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 //DeadCode RDH 28Jun100 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 //DeadCode RDH 28Jun100 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 //DeadCode RDH 28Jun100 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //DeadCode RDH 28Jun100 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //DeadCode RDH 28Jun100 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //DeadCode RDH 28Jun100 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //DeadCode RDH 28Jun100 			break;
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			break;
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 	}
//DeadCode JON 17Aug00 }

//#pragma warnmsg ( "inline me" )
inline void Lib3D::SetCurrentMaterial(const HMATERIAL& mat, const ULong flags)
{
//	IS_LAND = 1,
//	IS_DOUBLE_TEXTURED = 1<<1,
//	IS_PLAIN = 1<<2,
//	IS_ALPHA = 1<<3,
//	IS_ALPHA_SOLID = 1<<4,
//	IS_SPECULAR = 1<<5,
//	TEXTURE_SETMASK = IS_LAND+IS_DOUBLE_TEXTURED+IS_PLAIN

    if ( flags&IS_LAND )
    {
        if ( flags&IS_DOUBLE_TEXTURED )
        {
            lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[1] );
            lastError=pD3DDEV7->SetTexture( 1, textureTable[mat.p[1]->hTextureMap] );
        }
        else
        {
            lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[0] );
        }
        ULong landTextureIndex=mat.isLand^0xFFFFFFFF;
        lastError=pD3DDEV7->SetTexture(0,landTextures[landTextureIndex]);
#pragma warnmsg ( "I believe that this should be redundant- however it doesn't work without it" )
#pragma warnmsg ( "			-Note in SetUpRenderBlocks() this is set to mirror to force the switch" )
        lastError=pD3DDEV7->SetTextureStageState( 0,D3DTSS_ADDRESS,D3DTADDRESS_CLAMP);
    }
    else
    {
        if ( flags&IS_PLAIN )
        {
            if ( flags&IS_ALPHA )
            {
                lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[9] );
            }
            else
            {
                lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[8] );
            }
        }
        else
        {
            if ( flags&IS_DOUBLE_TEXTURED )
            {
                if ( flags&IS_ALPHA )
                {
                    if ( flags&IS_ALPHA_SOLID )
                    {
                        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[7] );
                    }
                    else
                    {
                        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[6] );
                    }
                }
                else
                {
                    lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[3] );
                }
                lastError=pD3DDEV7->SetTexture(0,textureTable[mat.p[0]->hTextureMap]);
                lastError=pD3DDEV7->SetTexture(1,textureTable[mat.p[1]->hTextureMap]);
            }
            else
            {
                if ( flags&IS_ALPHA )
                {
                    if ( flags&IS_ALPHA_SOLID )
                    {
                        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[5] );
                    }
                    else
                    {
                        lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[4] );
                    }
                }
                else
                {
                    lastError=pD3DDEV7->ApplyStateBlock( stateBlocks[2] );
                }
            }
            lastError=pD3DDEV7->SetTexture(0,textureTable[mat.p[0]->hTextureMap]);
        }
    }

    if ( flags&IS_SPECULAR )
    {
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);
    }
    else
    {
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
    }

//DeadCode JON 17Aug00 //	HRESULT hr;
//DeadCode JON 17Aug00 	SetCurrentLighting();
//DeadCode JON 17Aug00 #ifdef	_NOTEXTURES_
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG2 );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 #else
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
//DeadCode JON 17Aug00 #endif
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );		//ATI cards only accept TEXTURE in COLORARG1
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );	//JON 3/23/00
//DeadCode JON 17Aug00 //	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SUBTRACT );
//DeadCode JON 17Aug00 //	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
//DeadCode JON 17Aug00 //	CheckValidDevice( pD3DDEV7 );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	SetAntiAliasing( mat );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	if (mat.isLand)
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 #ifndef NO_HARD_TNL
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetMaterial(&materialMapped);
//DeadCode JON 17Aug00 #endif
//DeadCode JON 17Aug00 		ULong landTextureIndex;
//DeadCode JON 17Aug00 		landTextureIndex=mat.isLand^0xFFFFFFFF;
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTexture(0,landTextures[landTextureIndex]);
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 		lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_ADDRESS,D3DTADDRESS_CLAMP);
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 		if (mat.p[1]!=NULL && !(flags&F_CANTBLENDTEXTURES))
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 //TempCode JON 25Jul00 			lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG2 );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTexture( 1, textureTable[mat.p[1]->hTextureMap] );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_TEXTURE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_ADDSIGNED );
//DeadCode JON 17Aug00 //			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_ADD );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_CURRENT );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 //DeadCode JON 2Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //DeadCode JON 2Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 //DeadCode JON 26Jul00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 		else
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 		return;
//DeadCode JON 17Aug00 	}
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetTextureStageState(0,D3DTSS_ADDRESS,D3DTADDRESS_WRAP);
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	SLong opt;
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	if (mat.f)
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 		opt=flags&F_CANTBLENDTEXTURES?1:mat.f;
//DeadCode JON 17Aug00 		for (SLong index=opt-1;index>=0;index--)
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTexture(index,textureTable[mat.p[index]->hTextureMap]);
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 	}
//DeadCode JON 17Aug00 	else opt=0;
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 	switch ( opt )
//DeadCode JON 17Aug00 	{
//DeadCode JON 17Aug00 	case 0:	// plain col poly (should be dealt wiv elsewhere but just incase
//DeadCode JON 17Aug00 			// it could be transparent...
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 			SetPlainMaterial(/* mat */);
//DeadCode JON 17Aug00 #ifndef NDEBUG
//DeadCode JON 17Aug00 //			INT3;
//DeadCode JON 17Aug00 #endif
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 			hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE);
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 			hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 			hr=pD3DDEV7->LightEnable(0,TRUE);
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 			hr=pD3DDEV7->SetTexture(0,NULL);
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 			hr=pD3DDEV7->SetMaterial(&materialTable[mat.c]);
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 			hr=pD3DDEV7->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 //DEADCODE JON 5/9/00 			hr=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 		break;
//DeadCode JON 17Aug00 	case 1: // textured
//DeadCode JON 17Aug00 #ifndef NO_HARD_TNL
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetMaterial(&materialMapped);
//DeadCode JON 17Aug00 #endif
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 		break;
//DeadCode JON 17Aug00 	case 2: // double textured - i.e clouds
//DeadCode JON 17Aug00 		{
//DeadCode JON 17Aug00 #ifndef NO_HARD_TNL
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetMaterial(&materialMapped);
//DeadCode JON 17Aug00 #endif
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_BLENDTEXTUREALPHA);	//MODULATE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTFG_LINEAR);
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState(1,D3DTSS_MIPFILTER,D3DTFP_NONE);
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 			lastError=pD3DDEV7->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
//DeadCode JON 17Aug00 		}
//DeadCode JON 17Aug00 		break;
//DeadCode JON 17Aug00 	default:
//DeadCode JON 17Aug00 		break;
//DeadCode JON 17Aug00 	}
//DeadCode JON 17Aug00
//DeadCode JON 17Aug00 #ifndef NDEBUG
//DeadCode JON 17Aug00 	CheckValidDevice( pD3DDEV7 );
//DeadCode JON 17Aug00 #endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderPolyList
//Author		Paul.
//Date			Tue 4 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::RenderPolyList(SPolygon* &pHead)
{
    SPolygon *pTail;
    D3DTLVERTEX3 *pIns;
    SVertex *pSVert;
    ULong offset;

    int	i;
//DeadCode RJS 06Jun100 	HRESULT hr;

    D3DVALUE sx, sy, cx, cy;
    GetViewPort( /*pD3DDEV7,*/ sx, sy, cx, cy );

//DeadCode JON 17Aug00 // Force the Z-Buffer State
//DeadCode JON 17Aug00 //??	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );	//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);//RJS 17May00
//DeadCode JON 17Aug00   	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );//RJS 17May00

//DeadCode JON 21Aug00 	ULong zBias = &pHead - texturedPolys;
//DeadCode JON 21Aug00 	D3DVALUE zAdd;
//DeadCode JON 21Aug00 	if ( zBias >=0 && zBias < NUM_Z_LAYERS )
//DeadCode JON 21Aug00 		zAdd = zSMALL * (zBias<<2);
//	else
//		zAdd = 0.0;


//DeadCode JON 21Aug00 	R3DMATRIX* pMat = projectionMatrix+((projMatStackPos%MATRIX_STACK_SIZE)+(MATRIX_STACK_SIZE*zBias));
//DeadCode JON 21Aug00 	lastError=pD3DDEV7->SetTransform(D3DTRANSFORMSTATE_PROJECTION,pMat);

//DeadCode JON 21Aug00 	switch ( zBias )
//DeadCode JON 21Aug00 	{
//DeadCode JON 21Aug00 	case 0:
//DeadCode JON 21Aug00 //		return;
//DeadCode JON 21Aug00 		break;
//DeadCode JON 21Aug00 	case 1:
//DeadCode JON 21Aug00 		return;
//DeadCode JON 21Aug00 		break;
//DeadCode JON 21Aug00 	case 2:
//DeadCode JON 21Aug00 //		return;
//DeadCode JON 21Aug00 		break;
//DeadCode JON 21Aug00 	NODEFAULT;
//DeadCode JON 21Aug00 	}
//DeadCode JON 21Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZBIAS , zBias );

//#define DO_INDEXED_VB

    lpD3DVB7=gpD3DVB7;
    offset=ULong(&pHead->material.uniqueTextID)-ULong(pHead);
    pHead=(SPolygon*)RadixSortAscending((radix_sort_t*)pHead,offset);
    HMATERIAL* curmat=&pHead->material;
    InlineSetCurrentMaterial( *curmat, ULong( curmat->materialFlags) );
    pTail=pHead;
    while (pHead!=NULL) // step thru all poly's
    {
        SPolygon* pCur=pHead;
#ifndef DO_INDEXED_VB
        ULong vertcnt;
        ULong verttot;
        vertcnt=0;

        while (pTail!=NULL) // get the polys containing total of up to 1024 vertices
        {
            vertcnt+=pTail->vertexcount;
            if (vertcnt>1024) break;
            pTail=pTail->pNext;
        }
        lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
        while (pTail!=pCur) // go through each poly in this chunk
        {
            pIns = pCur->CopyToVertexBuffer( pIns, cx, cy, sx, sy );
            pCur=pCur->pNext;
        }
        lastError=lpD3DVB7->Unlock();
        vertcnt=0;
        pCur=pHead;

#else
        DWORD totVertC = 0;
        DWORD primVertCount[512];
        DWORD* curPrimCount = primVertCount;
        WORD primVertIndex[2048];
        WORD* curPrimIndex = primVertIndex;

        lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
        D3DTLVERTEX3* pStart = pIns;
        while (pTail!=NULL) // get the polys containing total of up to 1024 vertices
        {
            *curPrimCount = pTail->vertexcount;
            WORD nextVertC = totVertC+*curPrimCount;
            if (nextVertC>1024)
                break; // we've run out of room...
            pIns = pTail->CopyToIndexdedVB( pIns, curPrimIndex, pStart, bufferPass, cx, cy, sx, sy );

            curPrimCount++;
            totVertC=DWORD(pIns-pStart);//nextVertC;
            pTail=pTail->pNext;
        }
        bufferPass++;
        lastError=lpD3DVB7->Unlock();
        curPrimCount = primVertCount;
        curPrimIndex = primVertIndex;
#endif

        while (pTail!=pCur) // now go through each poly in the chunk again
        {
            if (!SameMaterial(pCur->material,*curmat)) // set correct material & render states if needed
            {
                curmat=&pCur->material;
                InlineSetCurrentMaterial(*curmat, ULong(pCur->material.materialFlags) );
            }
#ifndef DO_INDEXED_VB
            verttot=pCur->vertexcount; // actually draw the fans/poly's
            lastError=pD3DDEV7->DrawPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,vertcnt,verttot,0);
            vertcnt+=verttot;
#else
            pD3DDEV7->DrawIndexedPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,0,totVertC,curPrimIndex,*curPrimCount,0);
            curPrimIndex+=*curPrimCount++;
#endif
            pCur=pCur->pNext;
        }
        pHead=pTail;
    }
    lpD3DVB7=NULL;
//TempCode JON 15Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZBIAS , 16 );
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderPlainPolyList
//Author		Jon.
//Date			Tue 9 May 2000
//
//------------------------------------------------------------------------------
void Lib3D::RenderPlainPolyList(SPolygon *pHead)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
#else
    SPolygon *pTail,*pCur;
    D3DTLVERTEX3 *pIns;
    SVertex *pSVert;
    ULong vertcnt;
    ULong verttot;
    ULong offset;
    int	i;

    D3DVALUE sx, sy, cx, cy;
    GetViewPort( /*pD3DDEV7,*/ sx, sy, cx, cy );

//DeadCode JON 17Aug00 // Force the Z-Buffer State
//DeadCode JON 17Aug00 //??	hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );	//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);//RJS 17May00
//DeadCode JON 17Aug00   	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );//RJS 17May00


    lpD3DVB7=gpD3DVB7;
//DeadCode JON 17Aug00 	SetPlainMaterial();
//DeadCode JON 17Aug00 	HMATERIAL* curmat=&pHead->material;
//DeadCode JON 17Aug00 	InlineSetCurrentMaterial( *curmat, ULong( curmat->materialFlags) );
    InlineSetCurrentMaterial( hLastMaterial, IS_PLAIN );
    pTail=pHead;
    while (pHead!=NULL)
    {
        vertcnt=0;
        pCur=pHead;
        while (pTail!=NULL)
        {
            vertcnt+=pTail->vertexcount;
            if (vertcnt>1024) break;
            pTail=pTail->pNext;
        }
//#define PROJECT_TO_TEMP_BUFF
#ifndef PROJECT_TO_TEMP_BUFF
        lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
#else
        D3DTLVERTEX3 tmpBuffer[ 1024 ];
        pIns = tmpBuffer;
#endif
        if ( lastError != 0 )
        {
            char *errorDesc;
            GetErrorDesc( lastError, errorDesc );
            INT3;
        }
        else
        {
//			INT3;
        }
        while (pTail!=pCur)
        {
//DEADCODE JON 5/25/00 			pSVert=pCur->pVertexList;
//DEADCODE JON 5/25/00 		  	for (i=pCur->vertexcount;i>0;i--)
//DEADCODE JON 5/25/00 			{
//DEADCODE JON 5/25/00 			 	*pIns++=pSVert->getR3DVert();
//DEADCODE JON 5/25/00 				pSVert=pSVert->pNext;
//DEADCODE JON 5/25/00 			}
            pIns = pCur->CopyToVertexBuffer( pIns, cx, cy, sx, sy );
            pCur=pCur->pNext;
        }
#ifdef PROJECT_TO_TEMP_BUFF
        {
            D3DTLVERTEX3* pIns2;
            lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns2,NULL);
            memcopy( pIns2, tmpBuffer, ULong( pIns ) - ULong( tmpBuffer ) );
        }
#endif
        lastError=lpD3DVB7->Unlock();

        pCur=pHead;
        vertcnt=0;
        while (pTail!=pCur)
        {
//DEADCODE JON 5/9/00 			if (!SamePlainMaterial(pCur->material,curmat))
//DEADCODE JON 5/9/00 			{
//DEADCODE JON 5/9/00 			 	curmat=pCur->material;
//DEADCODE JON 5/9/00 				SetPlainMaterial(/*curmat*/);
//DEADCODE JON 5/9/00 			}
            verttot=pCur->vertexcount;
            lastError=pD3DDEV7->DrawPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,vertcnt,verttot,0);
            vertcnt+=verttot;
            pCur=pCur->pNext;
        }
        pHead=pTail;
    }
    lpD3DVB7=NULL;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTPolyList
//Author		Paul.
//Date			Fri 7 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::RenderTPolyList(SPolygon *pHead)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
#else
    SPolygon *pTail;
    //,*pCur;
    D3DTLVERTEX3 *pIns;
//	SVertex *pSVert;
    ULong offset;
    int	i;
//	HRESULT hr;
    HMATERIAL curmat;

    D3DVALUE sx, sy, cx, cy;
    GetViewPort( /*pD3DDEV7,*/ sx, sy, cx, cy );

    lpD3DVB7=gpD3DVB7;
    offset=ULong(&pHead->zbuffer)-ULong(pHead);
    pHead=(SPolygon*)RadixSortDescending((radix_sort_t*)pHead,offset);
//	curmat=0xFFFF;
//	hr=pD3DDEV7->SetMaterial(&materialMapped);
// Alpha subtract blending
//	hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);
//	hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);

// Alpha addition blending
//	hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);
//	hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);

//DeadCode JON 17Aug00 	lastBlendType = BLEND_SRCALPHA_DESTINVSRCALPHA;					//RJS 16May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCALPHA);		//how much is put on top
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_INVSRCALPHA);	//how much shows through underneath
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,TRUE);

// Force the Z-Buffer State
//??	hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE );	//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);//RJS 17May00
//DeadCode JON 17Aug00   	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);//RJS 17May00
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZENABLE, prefZType );//RJS 17May00

//DeadCode JON 17Aug00 	CheckValidDevice( pD3DDEV7 );

    curmat=pHead->material;
    InlineSetCurrentMaterial(curmat, ULong(curmat.materialFlags)+IS_ALPHA );
//DeadCode JON 17Aug00 	SetTransCurrentMaterial(curmat);

    pTail=pHead;
    while (pHead!=NULL) // step thru all poly's
    {
        SPolygon* pCur=pHead;
#ifndef DO_INDEXED_VB
        ULong vertcnt;
        ULong verttot;
        vertcnt=0;

        while (pTail!=NULL) // get the polys containing total of up to 1024 vertices
        {
            vertcnt+=pTail->vertexcount;
            if (vertcnt>1024) break;
            pTail=pTail->pNext;
        }
        lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
        while (pTail!=pCur) // go through each poly in this chunk
        {
            pIns = pCur->CopyToVertexBuffer( pIns, cx, cy, sx, sy );
            pCur=pCur->pNext;
        }
        lastError=lpD3DVB7->Unlock();
        vertcnt=0;
        pCur=pHead;

#else
        DWORD totVertC = 0;
        DWORD primVertCount[512];
        DWORD* curPrimCount = primVertCount;
        WORD primVertIndex[2048];
        WORD* curPrimIndex = primVertIndex;

        lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
        D3DTLVERTEX3* pStart = pIns;
        while (pTail!=NULL) // get the polys containing total of up to 1024 vertices
        {
            *curPrimCount = pTail->vertexcount;
            WORD nextVertC = totVertC+*curPrimCount;
            if (nextVertC>1024)
                break; // we've run out of room...
            pIns = pTail->CopyToIndexdedVB( pIns, curPrimIndex, pStart, bufferPass, cx, cy, sx, sy );

            curPrimCount++;
            totVertC=DWORD(pIns-pStart);//nextVertC;
            pTail=pTail->pNext;
        }
        bufferPass++;
        lastError=lpD3DVB7->Unlock();
        curPrimCount = primVertCount;
        curPrimIndex = primVertIndex;
#endif

        while (pTail!=pCur) // now go through each poly in the chunk again
        {
            if (!SameTransMat(pCur->material,curmat))
            {
                curmat=pCur->material;
                InlineSetCurrentMaterial(curmat, ULong(pCur->material.materialFlags)+IS_ALPHA );
            }
#ifndef DO_INDEXED_VB
            verttot=pCur->vertexcount; // actually draw the fans/poly's
            lastError=pD3DDEV7->DrawPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,vertcnt,verttot,0);
            vertcnt+=verttot;
#else
            pD3DDEV7->DrawIndexedPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,0,totVertC,curPrimIndex,*curPrimCount,0);
            curPrimIndex+=*curPrimCount++;
#endif
            pCur=pCur->pNext;
        }
        pHead=pTail;
    }

//DeadCode JON 30Oct00 	while (pHead!=NULL)
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		vertcnt=0;
//DeadCode JON 30Oct00 		pCur=pHead;
//DeadCode JON 30Oct00 		while (pTail!=NULL)
//DeadCode JON 30Oct00 		{
//DeadCode JON 30Oct00 			vertcnt+=pTail->vertexcount;
//DeadCode JON 30Oct00 			if (vertcnt>1024) break;
//DeadCode JON 30Oct00 			pTail=pTail->pNext;
//DeadCode JON 30Oct00 		}
//DeadCode JON 30Oct00 		lastError=lpD3DVB7->Lock(DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_DISCARDCONTENTS,(LPVOID*)&pIns,NULL);
//DeadCode JON 30Oct00 #ifndef NDEBUG
//DeadCode JON 30Oct00 		if ( lastError != 0 )
//DeadCode JON 30Oct00 		{
//DeadCode JON 30Oct00 			char *errorDesc;
//DeadCode JON 30Oct00 			GetErrorDesc( lastError, errorDesc );
//DeadCode JON 30Oct00 			INT3;
//DeadCode JON 30Oct00 		} else
//DeadCode JON 30Oct00 		{
//DeadCode JON 30Oct00 //			INT3;
//DeadCode JON 30Oct00 		}
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 		while (pTail!=pCur)
//DeadCode JON 30Oct00 		{
//DeadCode JON 30Oct00 //DEADCODE JON 5/25/00 			pSVert=pCur->pVertexList;
//DeadCode JON 30Oct00 //DEADCODE JON 5/25/00 		  	for (i=pCur->vertexcount
//DeadCode JON 30Oct00 //DEADCODE JON 5/25/00 				pSVert=pSVert->pNext;;i>0;i--)
//DeadCode JON 30Oct00 //DEADCODE JON 5/25/00 			{
//DeadCode JON 30Oct00 //DEADCODE JON 5/25/00 			 	*pIns++=pSVert->getR3DVert();;
//DeadCode JON 30Oct00 //DEADCODE JON 5/25/00 			}
//DeadCode JON 30Oct00 			pIns = pCur->CopyToVertexBuffer( pIns, cx, cy, sx, sy );
//DeadCode JON 30Oct00 			pCur=pCur->pNext;
//DeadCode JON 30Oct00 		}
//DeadCode JON 30Oct00 		lastError=lpD3DVB7->Unlock();
//DeadCode JON 30Oct00
//DeadCode JON 30Oct00 		pCur=pHead;
//DeadCode JON 30Oct00 		vertcnt=0;
//DeadCode JON 30Oct00 		while (pTail!=pCur)
//DeadCode JON 30Oct00 		{
//DeadCode JON 30Oct00 			if (!SameTransMat(pCur->material,curmat))
//DeadCode JON 30Oct00 			{
//DeadCode JON 30Oct00 			 	curmat=pCur->material;
//DeadCode JON 30Oct00 //DeadCode JON 17Aug00 				SetTransCurrentMaterial(curmat);
//DeadCode JON 30Oct00 				InlineSetCurrentMaterial(curmat, ULong(pCur->material.materialFlags)+IS_ALPHA );
//DeadCode JON 30Oct00 			}
//DeadCode JON 30Oct00 			verttot=pCur->vertexcount;
//DeadCode JON 30Oct00 			lastError=pD3DDEV7->DrawPrimitiveVB(D3DPT_TRIANGLEFAN,lpD3DVB7,vertcnt,verttot,0);
//DeadCode JON 30Oct00 #ifndef NDEBUG
//DeadCode JON 30Oct00 			if ( lastError != 0 )
//DeadCode JON 30Oct00 			{
//DeadCode JON 30Oct00 				char *errorDesc;
//DeadCode JON 30Oct00 				GetErrorDesc( lastError, errorDesc );
//DeadCode JON 30Oct00 			}
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 			vertcnt+=verttot;
//DeadCode JON 30Oct00 			pCur=pCur->pNext;
//DeadCode JON 30Oct00 		}
//DeadCode JON 30Oct00 		pHead=pTail;
//DeadCode JON 30Oct00 	}
    lpD3DVB7=NULL;

//DeadCode JON 17Aug00 	EnableFogging(true);

//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
//DeadCode JON 17Aug00 	lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);//RJS 17May00
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillFogTable
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::FillFogTable(D3DVALUE fStart,D3DVALUE fEnd)
{
    D3DVALUE fCur=1.f;
    for (int i=0x3FF; i>=0; i--)
    {
        if (fCur<fStart)
            fogTable[i]=0xFF;
        else if (fCur>fEnd)
            fogTable[i]=0x00;
        else
        {
            D3DVALUE frac;
            frac=255.f*(fCur-fEnd)/(fStart-fEnd);
            fogTable[i]=UByte(frac);
        }
        fCur-=D3DVALUE(1.f/1024.f);
    }
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EnableFogging
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
void Lib3D::EnableFogging(bool fEnable)
{
	if (!pD3DDEV7)
	{
		INT3;
		return;
	}
//DeadCode JON 24Jul00 	HRESULT hr;
//DeadCode JON 24Jul00 #ifndef _FORCE_SW_FOG_ // try for hardware fog
//DeadCode JON 24Jul00 	if (fEnable && (selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGTABLE)!=0)
//DeadCode JON 24Jul00 	{
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_LINEAR);
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_NONE);
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
//DeadCode JON 24Jul00 	}
//DeadCode JON 24Jul00 	else if (fEnable && (selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)!=0)
//DeadCode JON 24Jul00 	{
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_NONE);
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_LINEAR);
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
//DeadCode JON 24Jul00 	}
//DeadCode JON 24Jul00 	else hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,FALSE);
//DeadCode JON 24Jul00 #else // software fog only
//DeadCode JON 24Jul00 	if (fEnable && (selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)!=0)
//DeadCode JON 24Jul00 	{
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_NONE);
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_LINEAR);
//DeadCode JON 24Jul00 		hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
//DeadCode JON 24Jul00 	}
//DeadCode JON 24Jul00 	else hr=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,FALSE);
//DeadCode JON 24Jul00 #endif
#ifndef _NO_FOG_
    static bool lastFog = false;

    if ( fEnable == lastFog )
        return;

    lastFog = fEnable;

    if ( fEnable )
    {
//DeadCode JON 22Aug00 		if ( flags&F_VERTEXFOG )
//DeadCode JON 22Aug00 		{ // vertex fog mode
//DeadCode JON 22Aug00 			lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_NONE);
//DeadCode JON 22Aug00 			lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_LINEAR);
//DeadCode JON 22Aug00 			lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
//DeadCode JON 22Aug00 		} else
//DeadCode JON 22Aug00 		{
//DeadCode JON 22Aug00 			lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE,D3DFOG_LINEAR);
//DeadCode JON 22Aug00 			lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_NONE);
//DeadCode JON 22Aug00 			lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
//DeadCode JON 22Aug00 		}
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
    }
    else
    {
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,FALSE);
    }
#ifndef NDEBUG
    if ( lastError != S_OK )
    {
        INT3;
        lastError=pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,FALSE);
    }
#endif

#else
    pD3DDEV7->SetRenderState(D3DRENDERSTATE_FOGENABLE,FALSE);
#endif
}

inline void getNextToken( char* token, std::fstream & input )
{
    input.get( token[0] );
    while ( token[0] == ' ' || token[0] == '\t'|| token[0] == ','  )
    {
        input.get( token[0] );
    }
    if ( token[0] != '\n' )
    {
        int i = 0;
        while ( token[i] != ' ' && token[i] != '\t' && token[i] != ',' && token[i] != '\n' )
            input.get( token[++i] );
        if ( token[i] == '\n' )
            input.putback( '\n' );
        token[i] = 0;
    }
    else
        token[1]=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleNaffDriver
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
HRESULT Lib3D::HandleNaffDriver()
{

//	while ( supportedTextFmt )
//	{
//		DDTextureFormat* next = supportedTextFmt->next;
//		delete supportedTextFmt;
//		supportedTextFmt = next;
//	}
    doDeviceDiags = false;
    frameTimeBuff = NULL;
    tickCountBuff = NULL;
    curFrameTimeI = 0;
    frameTimeBuffSize = 0;
    minFrameTime = 0;
    w_16bit = 0;
    DDDEVICEIDENTIFIER2 devID;
    lastError=pDD7->GetDeviceIdentifier(&devID,0);

    flags=Flags(flags&~F_STIPPLEALPHA);

    // right now a super new version that loads a test file, in human readable form...
	std::fstream input;
    input.open( "CardBase.rc", std::fstream::in );
    if ( !input.is_open() )
    {
//		INT3;
        diagString = new char[100];
        _snprintf( diagString, 99, "Warning: no cardbase.rc found, so no gfx card fixes possible");
        // RERUN: original fell into the token loop on a dead stream - getNextToken
        // overruns the buffer. No file means no card fixes; return the S_OK the empty parse yields.
        return S_OK;
    }

    struct CardToken
    {
        const char* tokenStr;
        int tokenVal;
    };

    enum TokenVal
    {
        VERTEX_FOG = 0,
        NO_TEXTURE_TARGET,
        NO_TEXTURE_BLEND,
        SLOW_TEXTURE_DOWNLOAD,
        SLOWEST_TEXTURE_DOWNLOAD,
        MAX_TEXTURE_WIDTH,
        MAX_TEXTURE_HEIGHT,
        STIPPLE_ALPHA,
        NO_DEVICE_VALIDATION,
        SET_TEX_FMT_NUMBER,
        LOCK_TARG_FMT_TO_BACK_BUFF,
        ALWAYS_USE_W,
        ALWAYS_USE_Z,
        NO_GUARDBAND_CLIP,
        FAKE_W_BUFFER,
        W_16BIT,
        MIN_FRAME_TIME_MS,
        FRAME_TIME_BUFF,
        DO_DIAGS,
        MAX_TOKEN
    };

    CardToken tokenList[] =
    {
        { "VERTEX_FOG", VERTEX_FOG },
        { "NO_TEXTURE_TARGET", NO_TEXTURE_TARGET },
        { "NO_TEXTURE_BLEND", NO_TEXTURE_BLEND },
        { "SLOW_TEXTURE_DOWNLOAD", SLOW_TEXTURE_DOWNLOAD },
        { "SLOWEST_TEXTURE_DOWNLOAD", SLOWEST_TEXTURE_DOWNLOAD },
        { "MAX_TEXTURE_WIDTH", MAX_TEXTURE_WIDTH },
        { "MAX_TEXTURE_HEIGHT", MAX_TEXTURE_HEIGHT },
        { "STIPPLE_ALPHA", 	STIPPLE_ALPHA },
        { "NO_DEVICE_VALIDATION", NO_DEVICE_VALIDATION },
        { "SET_TEX_FMT_NUMBER", SET_TEX_FMT_NUMBER },
        { "LOCK_TARG_FMT_TO_BACK_BUFF", LOCK_TARG_FMT_TO_BACK_BUFF },
        { "ALWAYS_USE_W", ALWAYS_USE_W },
        { "ALWAYS_USE_Z", ALWAYS_USE_Z },
        { "NO_GUARDBAND_CLIP", NO_GUARDBAND_CLIP },
        { "FAKE_W_BUFFER", FAKE_W_BUFFER },
        { "W_16BIT", W_16BIT },
        { "MIN_FRAME_TIME_MS", MIN_FRAME_TIME_MS },
        { "FRAME_TIME_BUFF", FRAME_TIME_BUFF },
        { "DO_DIAGS", DO_DIAGS },
    };

    char newToken[256];
    DWORD identifier;
    while ( !input.eof() )
    {
        bool continueParse = false;
        getNextToken( newToken, input );
        // right, skip a comment
        if ( newToken[0] == '#' )
        {
            while ( !input.eof() && newToken[0] != '\n' )
                input.get( newToken[0] );
            continue; // go back to the top of the parser for the next line
        }
        // skip blank lines
        if ( newToken[0] == '\n' )
            continue;

        if ( strcmp( newToken, "DEFAULT" ) )
        {
            // it's not default...
            if ( !strcmp( newToken, "FORALL" ) )
            {
                continueParse = true;
            }
            else
            {
                // get the identifier
				input >> std::hex >> identifier;

                if ( identifier != devID.dwDeviceId )
                {
                    while ( !input.eof() && newToken[0] != '\n' )
                        input.get( newToken[0] );
                    continue; // go back to the top of the next line
                }
            }
        }
        else
        {
            diagString = new char[100];
            _snprintf( diagString, 99, "Using default card fix - your cards number is: %X", devID.dwDeviceId );
        }

        while( !input.eof() )
        {
            getNextToken( newToken, input );
            if ( newToken[0] == '\n' )
                break; // check for end of line.

            int ii;
            for (ii = 0; ii < MAX_TOKEN; ii++ )
            {
                if ( !strcmp( tokenList[ii].tokenStr, newToken ) )
                {
                    break;
                }
            }
            switch( tokenList[ii].tokenVal )
            {
            case DO_DIAGS:
                OpenDiags();
                break;
            case FRAME_TIME_BUFF:
                input >> std::dec >> frameTimeBuffSize; // read the new minimum frame time - default 0...
                break;
            case MIN_FRAME_TIME_MS:
                input >> std::dec >> minFrameTime; // read the new minimum frame time - default 0...
                break;
            case W_16BIT:
                flags=Flags(flags|F_16BIT_W);
                w_16bit = W_16BIT_OFFSET;
                break;
            case FAKE_W_BUFFER:
                flags=Flags(flags|F_FAKE_W);
                break;
            case NO_GUARDBAND_CLIP:
                hwClip = false;
                break;
            case LOCK_TARG_FMT_TO_BACK_BUFF:
            {
                DDSURFACEDESC2 backBuffDesc;
                backBuffDesc.dwSize= sizeof(DDSURFACEDESC2);
                pDDSB7->GetSurfaceDesc(&backBuffDesc);

//					backBuffDesc.ddpfPixelFormat.dwRGBBitCount

                DDTextureFormat* curr = supportedTextFmt;
                for ( int format = 0; curr != NULL; format++ )
                {
                    if (
                        ( curr->dwRGBBitCount == backBuffDesc.ddpfPixelFormat.dwRGBBitCount ) &&
                        ( curr->dwRGBAlphaBitMask == 0 ) &&
                        ( (curr->dwFlags&DDPF_COMPRESSED)==0 )
                    )
                    {
                        break;
                    }
                    curr = curr->next;
                }
                if ( curr != NULL )
                {
//DeadCode JON 10Oct00 							texFmt[format] = *curr;
                    texFmt[TF_LAND] = *curr;
                    texFmt[TF_LANDINIT] = *curr;
                }
                else
                {
                    if ( diagString )
                        delete[] diagString;
                    diagString = new char[100];
                    _snprintf( diagString, 99, "Unable to find an available texture format to lock texture target to at depth %lu",backBuffDesc.ddpfPixelFormat.dwRGBBitCount );
                    OutDiagLine( "%s\n",diagString );
                }
                break;
            }
            case SET_TEX_FMT_NUMBER:
            {
                ULong val;
                input >> std::dec >> val;
                DDTextureFormat* curr = supportedTextFmt;
                int i;
                for (i = 0; i < val && curr != NULL; i++ )
                {
                    curr = curr->next;
                }
                if ( curr == NULL )
                {
                    if ( diagString )
                        delete[] diagString;
                    diagString = new char[100];
                    _snprintf( diagString, 99, "Illegal texture format number - you card has 0 -> %i, inclusive", i-1 );
                    OutDiagLine( "%s\n",diagString );
                }
                else
                {
                    // right now read in the next character - needs to be a value...
                    CardToken numberList[] =
                    {
//							{ "TF_NORM", TF_NORM },
//							{ "TF_NORMINIT", TF_NORMINIT },
//							{ "TF_MASK", TF_MASK },
//							{ "TF_MASKINIT", TF_MASKINIT },
//							{ "TF_TRNS", TF_TRNS },
//							{ "TF_TRNSINIT", TF_TRNSINIT },
                        { "TF_LAND", TF_LAND },
                        { "TF_LANDINIT", TF_LANDINIT }
                    };
                    getNextToken( newToken, input );
                    if ( newToken[0] == '\n' )
                    {
                        // check for end of line.
                        INT3;
                        if ( diagString )
                            delete[] diagString;
                        diagString = new char[100];
                        _snprintf( diagString, 99, "Error in CardBase.rc: No texture format identifier" );
                        OutDiagLine( "%s\n",diagString );
                        input.close();
                        return DDERR_GENERIC;
                    }
                    int format;
                    for (format = 0; format < sizeof( numberList ); format++ )
                    {
                        if ( !strcmp( numberList[format].tokenStr, newToken ) )
                        {
                            break;
                        }
                    }
                    if ( format != sizeof( numberList ) )
                        texFmt[numberList[format].tokenVal] = *curr;
                    else
                    {
                        INT3;
                        if ( diagString )
                            delete[] diagString;
                        diagString = new char[100];
                        _snprintf( diagString, 99, "Error in CardBase.rc: Illegal texture format identifier" );
                        OutDiagLine( "%s\n",diagString );
                        input.close();
                        return DDERR_GENERIC;
                    }
                }
                break;
            }

            case NO_DEVICE_VALIDATION:
            {
                flags=Flags(flags|F_CANTVALIDATEDEVICE);
                break;
            }

            case VERTEX_FOG:
            {
                flags=Flags(flags|F_VERTEXFOG);
                break;
            }
            case NO_TEXTURE_TARGET:
            {
                SetNoRenderToTexture();
                break;
            }
            case NO_TEXTURE_BLEND:
            {
                flags=Flags(flags|F_CANTBLENDTEXTURES);
                break;
            }
            case SLOW_TEXTURE_DOWNLOAD:
            {
                flags=Flags(flags|F_SLOWCOPY);
                break;
            }
            case SLOWEST_TEXTURE_DOWNLOAD:
            {
                flags=Flags(flags|F_VSLOWCOPY);
                break;
            }
            case MAX_TEXTURE_WIDTH:
            {
                ULong val;
                input >> std::dec >> val;
                selectedDevice.dwMaxTextureWidth=val;
                break;
            }
            case MAX_TEXTURE_HEIGHT:
            {
                ULong val;
                input >> std::dec >> val;
                selectedDevice.dwMaxTextureHeight=val;
                break;
            }
            case  ALWAYS_USE_W:
            {
                prefZType = D3DZB_USEW;
                break;
            }
            case  ALWAYS_USE_Z:
            {
                prefZType = D3DZB_TRUE;
                break;
            }
            case STIPPLE_ALPHA:
            {
                flags=Flags(flags|F_STIPPLEALPHA);
                break;
            }
            case MAX_TOKEN:
            {
                // ooh, an unidentified token - should throw out a warning...
#ifndef NDEBUG
                INT3;
                if ( diagString )
                    delete[] diagString;
                diagString = new char[100];
                _snprintf( diagString, 99, "Error in CardBase.rc: Unknown identifier \"%s\"", newToken );
                OutDiagLine( "%s\n",diagString );
                input.close();
                return DDERR_GENERIC;
#endif
                break;
            }
            NODEFAULT;
            }
        }
        if ( continueParse )
            continue;
        break; // to have got here we must have matched a line...
    }

    input.close();

    OutDiagLine( "Initilising Lib3D on %s, identifier number: %x\n",devID.szDescription, devID.dwDeviceId );

    if ( frameTimeBuffSize )
    {
        frameTimeBuff = new ULong[frameTimeBuffSize];
        tickCountBuff = new LARGE_INTEGER[frameTimeBuffSize];
        for ( int i = 0; i<frameTimeBuffSize; i++ )
        {
            tickCountBuff[i].QuadPart = 0L;
            frameTimeBuff[i] = 0;
        }
    }


#ifdef _FORCE_SW_FOG_
    flags=Flags(flags|F_VERTEXFOG);
#endif

          if (selectedDevice.dwMaxTextureWidth==0)	selectedDevice.dwMaxTextureWidth=256;
          if (selectedDevice.dwMaxTextureHeight==0)	selectedDevice.dwMaxTextureHeight=256;

#ifndef NDEBUG
    {
        // now some debug stuff to see what the flags are...
        bool f_WINDOWED = (flags&F_WINDOWED) != 0;
        bool f_TNL = (flags&F_TNL) != 0;
        bool f_MMX = (flags&F_MMX) != 0;
        bool f_PAGELOCK = (flags&F_PAGELOCK) != 0;
        bool f_INSCENE = (flags&F_INSCENE) != 0;
        bool f_TEXTURECANBERENDERTARGET = (flags&F_TEXTURECANBERENDERTARGET) != 0;
        bool f_TNL_EMULATION = (flags&F_TNL_EMULATION) != 0;
        bool f_NOCLIPPING = (flags&F_NOCLIPPING) != 0;
        bool f_VERTEXFOG = (flags&F_VERTEXFOG) != 0;
        bool f_SLOWCOPY = (flags&F_SLOWCOPY) != 0;
        bool f_VSLOWCOPY = (flags&F_VSLOWCOPY) != 0;
        bool f_STIPPLEALPHA = (flags&F_STIPPLEALPHA) != 0;
        bool f_CANTMANAGETEXTURES = (flags&F_CANTMANAGETEXTURES) != 0;
        bool f_CANTBLENDTEXTURES = (flags&F_CANTBLENDTEXTURES) != 0;
        bool f_CANTVALIDATEDEVICE = (flags&F_CANTVALIDATEDEVICE) != 0;
        bool f_FAKE_W = (flags&F_FAKE_W) != 0;
        bool f_16BIT_W = (flags&F_16BIT_W) != 0;


//							{ "TF_NORM", TF_NORM },
//							{ "TF_NORMINIT", TF_NORMINIT },
//							{ "TF_MASK", TF_MASK },
//							{ "TF_MASKINIT", TF_MASKINIT },
//							{ "TF_TRNS", TF_TRNS },
//							{ "TF_TRNSINIT", TF_TRNSINIT },
//							{ "TF_LAND", TF_LAND },
//							{ "TF_LANDINIT", TF_LANDINIT }


        int texFmtLand, texFmtLandInit, texFmtNorm, texFmtMask, texFmtTrns;
        texFmtLand = texFmtLandInit = texFmtNorm = -1;
        DDTextureFormat* curr = supportedTextFmt;
        for ( int i = 0; curr != NULL; i++,	curr = curr->next )
        {
            if ( *curr == texFmt[TF_NORM] )
                texFmtNorm = i;
            if ( *curr == texFmt[TF_LAND] )
                texFmtLand = i;
            if ( *curr == texFmt[TF_MASK] )
                texFmtMask = i;
            if ( *curr == texFmt[TF_TRNS] )
                texFmtTrns = i;
        }
        NOP;
    }
#endif
    return S_OK;

//DeadCode JON 16Aug00 	// values got from 3dinfo.exe
//DeadCode JON 16Aug00 	const DWORD Riva_TNT		= 0x0020;
//DeadCode JON 16Aug00 	const DWORD Riva_TNT2		= 0x0028;
//DeadCode JON 16Aug00 	const DWORD GeForce			= 0x0100;
//DeadCode JON 16Aug00 	const DWORD GeForce2		= 0x0150;
//DeadCode JON 16Aug00 	const DWORD ATI_Rage_Pro	= 0x4742;
//DeadCode JON 16Aug00 	const DWORD ATI_Radeon		= 0x5144;
//DeadCode JON 16Aug00 	const DWORD FireGL_1KPro	= 0x3D07;
//DeadCode JON 16Aug00 	const DWORD S3_Savage4		= 0x8A22;
//DeadCode JON 16Aug00 	const DWORD Voodoo2			= 0x0002;
//DeadCode JON 16Aug00 	const DWORD VoodooBanshee	= 0x0003;
//DeadCode JON 16Aug00 	const DWORD Voodoo3			= 0x0005;
//DeadCode JON 16Aug00 	const DWORD Voodoo5			= 0x0009;
//DeadCode JON 16Aug00
//DeadCode JON 16Aug00 	// Check this driver against a list of known broken drivers
//DeadCode JON 16Aug00
//DeadCode JON 16Aug00 	flags=Flags(flags&~F_STIPPLEALPHA);
//DeadCode JON 16Aug00
//DeadCode JON 16Aug00 //	flags=Flags(flags|F_CANTBLENDTEXTURES);
//DeadCode JON 16Aug00
//DeadCode JON 16Aug00
//DeadCode JON 16Aug00 	switch ( devID.dwDeviceId )
//DeadCode JON 16Aug00 	{
//DeadCode JON 16Aug00 	case ATI_Radeon:
//DeadCode JON 16Aug00 		flags=Flags(flags|F_VERTEXFOG);
//DeadCode JON 16Aug00 		flags=Flags(flags|F_SLOWCOPY);
//DeadCode JON 16Aug00 		SetNoRenderToTexture();
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case Voodoo2:
//DeadCode JON 16Aug00 		flags=Flags(flags|F_CANTBLENDTEXTURES);
//DeadCode JON 16Aug00 		flags=Flags(flags|F_VERTEXFOG);
//DeadCode JON 16Aug00 		SetNoRenderToTexture();
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case VoodooBanshee:
//DeadCode JON 16Aug00 		flags=Flags(flags|F_VERTEXFOG);
//DeadCode JON 16Aug00 		SetNoRenderToTexture();
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case Voodoo5:
//DeadCode JON 16Aug00 		flags=Flags(flags|F_VERTEXFOG);
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case Voodoo3:
//DeadCode JON 16Aug00 		flags=Flags(flags|F_CANTBLENDTEXTURES);
//DeadCode JON 16Aug00 		flags=Flags(flags|F_VERTEXFOG);
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case FireGL_1KPro:
//DeadCode JON 16Aug00 		flags=Flags(flags|F_VSLOWCOPY);
//DeadCode JON 16Aug00 		flags=Flags(flags|F_STIPPLEALPHA);
//DeadCode JON 16Aug00 		SetNoRenderToTexture();
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case ATI_Rage_Pro:
//DeadCode JON 16Aug00 		selectedDevice.dwMaxTextureWidth=256;
//DeadCode JON 16Aug00 		selectedDevice.dwMaxTextureHeight=256;
//DeadCode JON 16Aug00 		flags=Flags(flags|F_SLOWCOPY);
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case GeForce2:
//DeadCode JON 16Aug00 	case GeForce:
//DeadCode JON 16Aug00 	case Riva_TNT2:
//DeadCode JON 16Aug00 	case Riva_TNT:
//DeadCode JON 16Aug00 //		flags=Flags(flags|F_SLOWCOPY);
//DeadCode JON 16Aug00 //		SetNoRenderToTexture();
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	case S3_Savage4:
//DeadCode JON 16Aug00 		flags=Flags(flags|F_SLOWCOPY);
//DeadCode JON 16Aug00 //DeadCode JON 3Jul00 		flags=Flags(flags&~F_TEXTURECANBERENDERTARGET);
//DeadCode JON 16Aug00 		SetNoRenderToTexture();
//DeadCode JON 16Aug00 		if (	(selectedDevice.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_WBUFFER)//RJS 06Jun00
//DeadCode JON 16Aug00 			&&	(currentZBufferDepth < 24)	)
//DeadCode JON 16Aug00 			prefZType = D3DZB_USEW;
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	default:
//DeadCode JON 16Aug00 		break;
//DeadCode JON 16Aug00 	}
//DeadCode JON 16Aug00
//DeadCode JON 16Aug00 #ifdef _FORCE_SW_FOG_
//DeadCode JON 16Aug00 		flags=Flags(flags|F_VERTEXFOG);
//DeadCode JON 16Aug00 #endif
//DeadCode JON 16Aug00
//DeadCode JON 16Aug00 	if (selectedDevice.dwMaxTextureWidth==0)	selectedDevice.dwMaxTextureWidth=256;
//DeadCode JON 16Aug00 	if (selectedDevice.dwMaxTextureHeight==0)	selectedDevice.dwMaxTextureHeight=256;
//DeadCode JON 16Aug00 	return S_OK;
//DeadCode JON 16Aug00
//DEADCODE JON 5/4/00 	NaffDriver nd=(NaffDriver)ND_Max;
//DEADCODE JON 5/4/00
//DEADCODE JON 5/4/00 	for (int i=0;i<ND_Max;i++)
//DEADCODE JON 5/4/00 	{
//DEADCODE JON 5/4/00 		GUID FAR *pGuid=(GUID FAR*)&naffDriverTable[i].ndGuid;
//DEADCODE JON 5/4/00 		if (*pGuid==devID.guidDeviceIdentifier)
//DEADCODE JON 5/4/00 		{
//DEADCODE JON 5/4/00 			nd=naffDriverTable[i].naffDriver;
//DEADCODE JON 5/4/00 			break;
//DEADCODE JON 5/4/00 		}
//DEADCODE JON 5/4/00 	}
//DEADCODE JON 5/4/00
//DEADCODE JON 5/4/00 	switch (nd)
//DEADCODE JON 5/4/00 	{
//DEADCODE JON 5/4/00 	case ND_FireGL1KPro:
//DEADCODE JON 5/4/00 		flags=Flags(flags|F_VSLOWCOPY);
//DEADCODE JON 5/4/00 		flags=Flags(flags|F_STIPPLEALPHA);
//DEADCODE JON 5/4/00 		flags=Flags(flags&~F_TEXTURECANBERENDERTARGET);
//DEADCODE JON 5/4/00 		break;
//DEADCODE JON 5/4/00 	case ND_ATIRagePro:
//DEADCODE JON 5/4/00 		selectedDevice.dwMaxTextureWidth=256;
//DEADCODE JON 5/4/00 		selectedDevice.dwMaxTextureHeight=256;
//DEADCODE JON 5/4/00 	case ND_GeoForce256:
//DEADCODE JON 5/4/00 	case ND_RivaTNT:
//DEADCODE JON 5/4/00 		flags=Flags(flags|F_SLOWCOPY);
//DEADCODE JON 5/4/00 		flags=Flags(flags&~F_TEXTURECANBERENDERTARGET);
//DEADCODE JON 5/4/00 		break;
//DEADCODE JON 5/4/00 	default:
//DEADCODE JON 5/4/00 		break;
//DEADCODE JON 5/4/00 	}

//	flags=Flags(flags|F_VSLOWCOPY);
//	flags=Flags(flags|F_SLOWCOPY);
//	flags=Flags(flags&~F_TEXTURECANBERENDERTARGET);

//	selectedDevice.dwMaxTextureWidth=256;
//	selectedDevice.dwMaxTextureHeight=256;

//Poo	flags = Flags(flags|F_CANTBLENDTEXTURES);
//	flags = Flags(flags|F_CANTBLENDTEXTURES);

}

HRESULT Lib3D::LoadBMP(UByte * data)
{
    return BackgroundImage( (BITMAPFILEHEADER*) data );
}

//
// for cards that can't manage textures
//
void Lib3D::PreBuildTextures()
{
    /*	const int MAX_UNMANAGEABLE=4096;

    	DDSURFACEDESC2	ddsdNormal,ddsdMask,ddsdTrans;
    	DDSCAPS2 ddscaps;
    	DWORD freemem,totalmem;
    	HRESULT hr;

    	ZeroMemory(&ddscaps,sizeof(ddscaps));
    	ddscaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_VIDEOMEMORY|DDSCAPS_LOCALVIDMEM;

    	ZeroMemory(&ddsdNormal,sizeof(DDSURFACEDESC2));
    	ZeroMemory(&ddsdMask,sizeof(DDSURFACEDESC2));
    	ZeroMemory(&ddsdTrans,sizeof(DDSURFACEDESC2));

    	ddsdNormal.dwSize=sizeof(DDSURFACEDESC2);
    	ddsdMask.dwSize=sizeof(DDSURFACEDESC2);
    	ddsdTrans.dwSize=sizeof(DDSURFACEDESC2);

    	ddsdNormal.dwFlags=
    		ddsdMask.dwFlags=
    		ddsdTrans.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_CAPS|DDSD_MIPMAPCOUNT|DDSD_TEXTURESTAGE;

    	ddsdNormal.dwWidth=
    		ddsdNormal.dwHeight=
    		ddsdMask.dwWidth=
    		ddsdMask.dwHeight=
    		ddsdTrans.dwWidth=
    		ddsdTrans.dwHeight=256;

    	ddsdNormal.ddpfPixelFormat=texFmt[TF_NORM];
    	ddsdMask.ddpfPixelFormat=texFmt[TF_MASK];
    	ddsdTrans.ddpfPixelFormat=texFmt[TF_TRNS];

    	ddsdNormal.ddsCaps.dwCaps=
    		ddsdMask.ddsCaps.dwCaps=
    		ddsdTrans.ddsCaps.dwCaps=DDSCAPS_TEXTURE|DDSCAPS_COMPLEX|DDSCAPS_MIPMAP|DDSCAPS_LOCALVIDMEM|DDSCAPS_VIDEOMEMORY;

    	ddsdNormal.dwMipMapCount=3;
    	ddsdMask.dwMipMapCount=1;
    	ddsdTrans.dwMipMapCount=1;

    	for (int i=0;i<MAX_UNMANAGEABLE;i++)
    	{
    		LPDIRECTDRAWSURFACE7 pdds7;
    		hr=pDD7->CreateSurface(&ddsdNormal,&pdds7,NULL);
    		if (hr!=DD_OK)
    			_asm {int 3}
    		hr=pDD7->GetAvailableVidMem(&ddscaps,&totalmem,&freemem);
    	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestPoly
//Author		Paul.
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
HRESULT Lib3D::TestPoly(const HMATERIAL& hMat)
{
    /*
    UWord ww=UWord(hMat);;

    SetMaterial(ww);

    SPolygon *poly;
    ALLOCATE_POLYGON(poly,4);

    SVertex *vertex;
    vertex=poly->pVertexList;
    vertex->sx=-1.f;
    vertex->sy=-1.f;
    vertex->sz=0.f;
    vertex->rhw=1.f;
    vertex->tu=0.f;
    vertex->tv=0.f;
    vertex->color=0xFFFFFFFF;
    vertex->specular=0x0000000;
    vertex=vertex->pNext;

    vertex->sx=1.f;
    vertex->sy=-1.f;
    vertex->sz=0.f;
    vertex->rhw=1.f;
    vertex->tu=1.f;
    vertex->tv=0.f;
    vertex->color=0xFFFFFFFF;
    vertex->specular=0x0000000;
    vertex=vertex->pNext;

    vertex->sx=1.f;
    vertex->sy=1.f;
    vertex->sz=0.f;
    vertex->rhw=1.f;
    vertex->tu=1.f;
    vertex->tv=1.f;
    vertex->color=0xFFFFFFFF;
    vertex->specular=0x0000000;
    vertex=vertex->pNext;

    vertex->sx=-1.f;
    vertex->sy=1.f;
    vertex->sz=0.f;
    vertex->rhw=1.f;
    vertex->tu=0.f;
    vertex->tv=1.f;
    vertex->color=0xFFFFFFFF;
    vertex->specular=0x0000000;

    D3DVIEWPORT7 vp;
    pD3DDEV7->GetViewport(&vp);

    D3DVALUE sx,sy;
    D3DVALUE cx,cy;
    sx=128;
    sy=128;
    cx=D3DVALUE(vp.dwX)+sx;
    cy=D3DVALUE(vp.dwY)+sy;

    PROJECT(poly,cx,cy,sx,sy);
    ADD_POLYGON(texturedPolys,poly);
      */
    return S_OK;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		cpu_id
//Author		Paul.
//Date			Fri 23 Apr 1999
//------------------------------------------------------------------------------
#define HAS_NPU		0x01
#define CPU_MMX		0x02
#define	CPU_TS		0x04
#define CYRIX		0x08
#define NEC			0x10
#define NEXGEN		0x20
#define AMD			0x40
#define UMC			0x80

#define	CPUSUPP_FP		0x00000001
#define	CPUSUPP_V86X	0x00000002
#define	CPUSUPP_IOBP	0x00000004
#define	CPUSUPP_PSX		0x00000008
#define	CPUSUPP_TS		0x00000010
#define	CPUSUPP_PSMR	0x00000020
#define	CPUSUPP_PAX		0x00000040
#define	CPUSUPP_MCX		0x00000080
#define	CPUSUPP_CXG8	0x00000100
#define	CPUSUPP_APIC	0x00000200
#define	CPUSUPP_reserved 0x00000400
#define	CPUSUPP_SYSE_E	0x00000800
#define	CPUSUPP_MTRR	0x00001000
#define	CPUSUPP_PGX		0x00002000
#define	CPUSUPP_MCA		0x00004000
#define	CPUSUPP_CMOV	0x00008000
#define	CPUSUPP_MMX		0x00800000
/*
#define cpuid _asm _emit 0x0f _asm _emit 0xa2
#define wrmsr _asm _emit 0x0f _asm _emit 0x30
#define rdtsc _asm _emit 0x0f _asm _emit 0x31
#define rdmsr _asm _emit 0x0f _asm _emit 0x32
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CpuInfo
//Author		Paul.
//Date			Fri 26 Nov 1999
//
//------------------------------------------------------------------------------
void Lib3D::CpuInfo()
{
    flags=Flags(flags|F_MMX);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Lib3DCreate
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//Description	Single global exported function used to create an
// 				initial library interface ptr
//
//Inputs		ptr to GUID for required library version number
//
//Returns		ptr to library interface or NULL for error.
//
//------------------------------------------------------------------------------
LIB3D_API CLib3D *Lib3DCreate(const GUID pGUID)
{
    CLib3D *pLib=NULL;

//	if (Lib3D::refCnt==0 && memcmp(&pGUID,&IID_ILib3D,sizeof(GUID)))
    {
        pLib=(CLib3D*)new Lib3D;
        if (pLib)
            pLib->AddRef();
    }
    return pLib;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DllMain
//Author		Paul.
//Date			Mon 8 Nov 1999
//
//Description	The usual Windows DLL stuff
//
//------------------------------------------------------------------------------
BOOL APIENTRY DllMain(HANDLE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

struct SErrorText
{
    HRESULT hrErrorCode;
    const char *errorDesc;
}
ErrorCodes[]=
{
    {DDERR_ALREADYINITIALIZED,			"DDERR_ALREADYINITIALIZED"},
    {DDERR_BLTFASTCANTCLIP,				"DDERR_BLTFASTCANTCLIP"},
    {DDERR_CANNOTATTACHSURFACE,			"DDERR_CANNOTATTACHSURFACE"},
    {DDERR_CANNOTDETACHSURFACE,			"DDERR_CANNOTDETACHSURFACE"},
    {DDERR_CANTCREATEDC,				"DDERR_CANTCREATEDC"},
    {DDERR_CANTDUPLICATE,				"DDERR_CANTDUPLICATE"},
    {DDERR_CANTLOCKSURFACE,				"DDERR_CANTLOCKSURFACE"},
    {DDERR_CANTPAGELOCK,				"DDERR_CANTPAGELOCK"},
    {DDERR_CANTPAGEUNLOCK,				"DDERR_CANTPAGEUNLOCK"},
    {DDERR_CLIPPERISUSINGHWND,			"DDERR_CLIPPERISUSINGHWND"},
    {DDERR_COLORKEYNOTSET,				"DDERR_COLORKEYNOTSET"},
    {DDERR_CURRENTLYNOTAVAIL,			"DDERR_CURRENTLYNOTAVAIL"},
    {DDERR_DDSCAPSCOMPLEXREQUIRED,		"DDERR_DDSCAPSCOMPLEXREQUIRED"},
    {DDERR_DCALREADYCREATED,			"DDERR_DCALREADYCREATED"},
    {DDERR_DEVICEDOESNTOWNSURFACE,		"DDERR_DEVICEDOESNTOWNSURFACE"},
    {DDERR_DIRECTDRAWALREADYCREATED,	"DDERR_DIRECTDRAWALREADYCREATED"},
    {DDERR_EXCEPTION,					"DDERR_EXCEPTION"},
    {DDERR_EXCLUSIVEMODEALREADYSET,		"DDERR_EXCLUSIVEMODEALREADYSET"},
    {DDERR_EXPIRED,						"DDERR_EXPIRED"},
    {DDERR_GENERIC,						"DDERR_GENERIC"},
    {DDERR_HEIGHTALIGN,					"DDERR_HEIGHTALIGN"},
    {DDERR_HWNDALREADYSET,				"DDERR_HWNDALREADYSET"},
    {DDERR_HWNDSUBCLASSED,				"DDERR_HWNDSUBCLASSED"},
    {DDERR_IMPLICITLYCREATED,			"DDERR_IMPLICITLYCREATED"},
    {DDERR_INCOMPATIBLEPRIMARY,			"DDERR_INCOMPATIBLEPRIMARY"},
    {DDERR_INVALIDCAPS,					"DDERR_INVALIDCAPS"},
    {DDERR_INVALIDCLIPLIST,				"DDERR_INVALIDCLIPLIST"},
    {DDERR_INVALIDDIRECTDRAWGUID,		"DDERR_INVALIDDIRECTDRAWGUID"},
    {DDERR_INVALIDMODE,					"DDERR_INVALIDMODE"},
    {DDERR_INVALIDOBJECT,				"DDERR_INVALIDOBJECT"},
    {DDERR_INVALIDPARAMS,				"DDERR_INVALIDPARAMS"},
    {DDERR_INVALIDPIXELFORMAT,			"DDERR_INVALIDPIXELFORMAT"},
    {DDERR_INVALIDPOSITION,				"DDERR_INVALIDPOSITION"},
    {DDERR_INVALIDRECT,					"DDERR_INVALIDRECT"},
    {DDERR_INVALIDSTREAM,				"DDERR_INVALIDSTREAM"},
    {DDERR_INVALIDSURFACETYPE,			"DDERR_INVALIDSURFACETYPE"},
    {DDERR_LOCKEDSURFACES,				"DDERR_LOCKEDSURFACES"},
    {DDERR_MOREDATA,					"DDERR_MOREDATA"},
    {DDERR_NEWMODE,						"DDERR_NEWMODE"},
    {DDERR_NO3D,						"DDERR_NO3D"},
    {DDERR_NOALPHAHW,					"DDERR_NOALPHAHW"},
    {DDERR_NOBLTHW,						"DDERR_NOBLTHW"},
    {DDERR_NOCLIPLIST,					"DDERR_NOCLIPLIST"},
    {DDERR_NOCLIPPERATTACHED,			"DDERR_NOCLIPPERATTACHED"},
    {DDERR_NOCOLORCONVHW,				"DDERR_NOCOLORCONVHW"},
    {DDERR_NOCOLORKEY,					"DDERR_NOCOLORKEY"},
    {DDERR_NOCOLORKEYHW,				"DDERR_NOCOLORKEYHW"},
    {DDERR_NOCOOPERATIVELEVELSET,		"DDERR_NOCOOPERATIVELEVELSET"},
    {DDERR_NODC,						"DDERR_NODC"},
    {DDERR_NODDROPSHW,					"DDERR_NODDROPSHW"},
    {DDERR_NODIRECTDRAWHW,				"DDERR_NODIRECTDRAWHW"},
    {DDERR_NODIRECTDRAWSUPPORT,			"DDERR_NODIRECTDRAWSUPPORT"},
    {DDERR_NODRIVERSUPPORT,				"DDERR_NODRIVERSUPPORT"},
    {DDERR_NOEMULATION,					"DDERR_NOEMULATION"},
    {DDERR_NOEXCLUSIVEMODE,				"DDERR_NOEXCLUSIVEMODE"},
    {DDERR_NOFLIPHW,					"DDERR_NOFLIPHW"},
    {DDERR_NOFOCUSWINDOW,				"DDERR_NOFOCUSWINDOW"},
    {DDERR_NOGDI,						"DDERR_NOGDI"},
    {DDERR_NOHWND,						"DDERR_NOHWND"},
    {DDERR_NOMIPMAPHW,					"DDERR_NOMIPMAPHW"},
    {DDERR_NOMIRRORHW,					"DDERR_NOMIRRORHW"},
    {DDERR_NOMONITORINFORMATION,		"DDERR_NOMONITORINFORMATION"},
    {DDERR_NONONLOCALVIDMEM,			"DDERR_NONONLOCALVIDMEM"},
    {DDERR_NOOPTIMIZEHW,				"DDERR_NOOPTIMIZEHW"},
    {DDERR_NOOVERLAYDEST,				"DDERR_NOOVERLAYDEST"},
    {DDERR_NOOVERLAYHW,					"DDERR_NOOVERLAYHW"},
    {DDERR_NOPALETTEATTACHED,			"DDERR_NOPALETTEATTACHED"},
    {DDERR_NOPALETTEHW,					"DDERR_NOPALETTEHW"},
    {DDERR_NORASTEROPHW,				"DDERR_NORASTEROPHW"},
    {DDERR_NOROTATIONHW,				"DDERR_NOROTATIONHW"},
    {DDERR_NOSTEREOHARDWARE,			"DDERR_NOSTEREOHARDWARE"},
    {DDERR_NOSTRETCHHW,					"DDERR_NOSTRETCHHW"},
    {DDERR_NOSURFACELEFT,				"DDERR_NOSURFACELEFT"},
    {DDERR_NOT4BITCOLOR,				"DDERR_NOT4BITCOLOR"},
    {DDERR_NOT4BITCOLORINDEX,			"DDERR_NOT4BITCOLORINDEX"},
    {DDERR_NOT8BITCOLOR,				"DDERR_NOT8BITCOLOR"},
    {DDERR_NOTAOVERLAYSURFACE,			"DDERR_NOTAOVERLAYSURFACE"},
    {DDERR_NOTEXTUREHW,					"DDERR_NOTEXTUREHW"},
    {DDERR_NOTFLIPPABLE,				"DDERR_NOTFLIPPABLE"},
    {DDERR_NOTFOUND,					"DDERR_NOTFOUND"},
    {DDERR_NOTINITIALIZED,				"DDERR_NOTINITIALIZED"},
    {DDERR_NOTLOADED,					"DDERR_NOTLOADED"},
    {DDERR_NOTLOCKED,					"DDERR_NOTLOCKED"},
    {DDERR_NOTPAGELOCKED,				"DDERR_NOTPAGELOCKED"},
    {DDERR_NOTPALETTIZED,				"DDERR_NOTPALETTIZED"},
    {DDERR_NOVSYNCHW,					"DDERR_NOVSYNCHW"},
    {DDERR_NOZBUFFERHW,					"DDERR_NOZBUFFERHW"},
    {DDERR_NOZOVERLAYHW,				"DDERR_NOZOVERLAYHW"},
    {DDERR_OUTOFCAPS,					"DDERR_OUTOFCAPS"},
    {DDERR_OUTOFMEMORY,					"DDERR_OUTOFMEMORY"},
    {DDERR_OUTOFVIDEOMEMORY,			"DDERR_OUTOFVIDEOMEMORY"},
    {DDERR_OVERLAPPINGRECTS,			"DDERR_OVERLAPPINGRECTS"},
    {DDERR_OVERLAYCANTCLIP,				"DDERR_OVERLAYCANTCLIP"},
    {DDERR_OVERLAYCOLORKEYONLYONEACTIVE,"DDERR_OVERLAYCOLORKEYONLYONEACTIVE"},
    {DDERR_OVERLAYNOTVISIBLE,			"DDERR_OVERLAYNOTVISIBLE"},
    {DDERR_PALETTEBUSY,					"DDERR_PALETTEBUSY"},
    {DDERR_PRIMARYSURFACEALREADYEXISTS,	"DDERR_PRIMARYSURFACEALREADYEXISTS"},
    {DDERR_REGIONTOOSMALL,				"DDERR_REGIONTOOSMALL"},
    {DDERR_SURFACEALREADYATTACHED,		"DDERR_SURFACEALREADYATTACHED"},
    {DDERR_SURFACEALREADYDEPENDENT,		"DDERR_SURFACEALREADYDEPENDENT"},
    {DDERR_SURFACEBUSY,					"DDERR_SURFACEBUSY"},
    {DDERR_SURFACEISOBSCURED,			"DDERR_SURFACEISOBSCURED"},
    {DDERR_SURFACELOST,					"DDERR_SURFACELOST"},
    {DDERR_SURFACENOTATTACHED,			"DDERR_SURFACENOTATTACHED"},
    {DDERR_TESTFINISHED,				"DDERR_TESTFINISHED"},
    {DDERR_TOOBIGHEIGHT,				"DDERR_TOOBIGHEIGHT"},
    {DDERR_TOOBIGSIZE,					"DDERR_TOOBIGSIZE"},
    {DDERR_TOOBIGWIDTH,					"DDERR_TOOBIGWIDTH"},
    {DDERR_UNSUPPORTED,					"DDERR_UNSUPPORTED"},
    {DDERR_UNSUPPORTEDFORMAT,			"DDERR_UNSUPPORTEDFORMAT"},
    {DDERR_UNSUPPORTEDMASK,				"DDERR_UNSUPPORTEDMASK"},
    {DDERR_UNSUPPORTEDMODE,				"DDERR_UNSUPPORTEDMODE"},
    {DDERR_VERTICALBLANKINPROGRESS,		"DDERR_VERTICALBLANKINPROGRESS"},
    {DDERR_VIDEONOTACTIVE,				"DDERR_VIDEONOTACTIVE"},
    {DDERR_WASSTILLDRAWING,				"DDERR_WASSTILLDRAWING"},
    {DDERR_WRONGMODE,					"DDERR_WRONGMODE"},
    {DDERR_XALIGN,						"DDERR_XALIGN"},
    {D3DERR_BADMAJORVERSION,			"D3DERR_BADMAJORVERSION"},
    {D3DERR_BADMINORVERSION,			"D3DERR_BADMINORVERSION"},
    {D3DERR_COLORKEYATTACHED,			"D3DERR_COLORKEYATTACHED"},
    {D3DERR_CONFLICTINGTEXTUREFILTER,	"D3DERR_CONFLICTINGTEXTUREFILTER"},
    {D3DERR_CONFLICTINGTEXTUREPALETTE,	"D3DERR_CONFLICTINGTEXTUREPALETTE"},
    {D3DERR_CONFLICTINGRENDERSTATE,		"D3DERR_CONFLICTINGRENDERSTATE"},
    {D3DERR_DEVICEAGGREGATED,			"D3DERR_DEVICEAGGREGATED"},
    {D3DERR_INITFAILED,					"D3DERR_INITFAILED"},
    {D3DERR_INBEGIN,					"D3DERR_INBEGIN"},
    {D3DERR_INBEGINSTATEBLOCK,			"D3DERR_INBEGINSTATEBLOCK"},
    {D3DERR_INVALID_DEVICE,				"D3DERR_INVALID_DEVICE"},
    {D3DERR_INVALIDCURRENTVIEWPORT,		"D3DERR_INVALIDCURRENTVIEWPORT"},
    {D3DERR_INVALIDMATRIX,				"D3DERR_INVALIDMATRIX"},
    {D3DERR_INVALIDPALETTE,				"D3DERR_INVALIDPALETTE"},
    {D3DERR_INVALIDPRIMITIVETYPE,		"D3DERR_INVALIDPRIMITIVETYPE"},
    {D3DERR_INVALIDRAMPTEXTURE,			"D3DERR_INVALIDRAMPTEXTURE"},
    {D3DERR_INVALIDSTATEBLOCK,			"D3DERR_INVALIDSTATEBLOCK"},
    {D3DERR_INVALIDVERTEXFORMAT,		"D3DERR_INVALIDVERTEXFORMAT"},
    {D3DERR_INVALIDVERTEXTYPE,			"D3DERR_INVALIDVERTEXTYPE"},
    {D3DERR_LIGHT_SET_FAILED,			"D3DERR_LIGHT_SET_FAILED"},
    {D3DERR_LIGHTHASVIEWPORT,			"D3DERR_LIGHTHASVIEWPORT"},
    {D3DERR_LIGHTNOTINTHISVIEWPORT,		"D3DERR_LIGHTNOTINTHISVIEWPORT"},
    {D3DERR_MATERIAL_CREATE_FAILED,		"D3DERR_MATERIAL_CREATE_FAILED"},
    {D3DERR_MATERIAL_DESTROY_FAILED,	"D3DERR_MATERIAL_DESTROY_FAILED"},
    {D3DERR_MATERIAL_GETDATA_FAILED,	"D3DERR_MATERIAL_GETDATA_FAILED"},
    {D3DERR_MATERIAL_SETDATA_FAILED,	"D3DERR_MATERIAL_SETDATA_FAILED"},
    {D3DERR_MATRIX_CREATE_FAILED,		"D3DERR_MATRIX_CREATE_FAILED"},
    {D3DERR_MATRIX_DESTROY_FAILED,		"D3DERR_MATRIX_DESTROY_FAILED"},
    {D3DERR_MATRIX_GETDATA_FAILED,		"D3DERR_MATRIX_GETDATA_FAILED"},
    {D3DERR_MATRIX_SETDATA_FAILED,		"D3DERR_MATRIX_SETDATA_FAILED"},
    {D3DERR_NOCURRENTVIEWPORT,			"D3DERR_NOCURRENTVIEWPORT"},
    {D3DERR_NOTINBEGIN,					"D3DERR_NOTINBEGIN"},
    {D3DERR_NOTINBEGINSTATEBLOCK,		"D3DERR_NOTINBEGINSTATEBLOCK"},
    {D3DERR_NOVIEWPORTS,				"D3DERR_NOVIEWPORTS"},
    {D3DERR_SCENE_BEGIN_FAILED,			"D3DERR_SCENE_BEGIN_FAILED"},
    {D3DERR_SCENE_END_FAILED,			"D3DERR_SCENE_END_FAILED"},
    {D3DERR_SCENE_IN_SCENE,				"D3DERR_SCENE_IN_SCENE"},
    {D3DERR_SCENE_NOT_IN_SCENE,			"D3DERR_SCENE_NOT_IN_SCENE"},
    {D3DERR_SETVIEWPORTDATA_FAILED,		"D3DERR_SETVIEWPORTDATA_FAILED"},
    {D3DERR_STENCILBUFFER_NOTPRESENT,	"D3DERR_STENCILBUFFER_NOTPRESENT"},
    {D3DERR_SURFACENOTINVIDMEM,			"D3DERR_SURFACENOTINVIDMEM"},
    {D3DERR_TEXTURE_BADSIZE,			"D3DERR_TEXTURE_BADSIZE"},
    {D3DERR_TEXTURE_CREATE_FAILED,		"D3DERR_TEXTURE_CREATE_FAILED"},
    {D3DERR_TEXTURE_DESTROY_FAILED,		"D3DERR_TEXTURE_DESTROY_FAILED"},
    {D3DERR_TEXTURE_GETSURF_FAILED,		"D3DERR_TEXTURE_GETSURF_FAILED"},
    {D3DERR_TEXTURE_LOAD_FAILED,		"D3DERR_TEXTURE_LOAD_FAILED"},
    {D3DERR_TEXTURE_LOCK_FAILED,		"D3DERR_TEXTURE_LOCK_FAILED"},
    {D3DERR_TEXTURE_LOCKED,				"D3DERR_TEXTURE_LOCKED"},
    {D3DERR_TEXTURE_NO_SUPPORT,			"D3DERR_TEXTURE_NO_SUPPORT"},
    {D3DERR_TEXTURE_NOT_LOCKED,			"D3DERR_TEXTURE_NOT_LOCKED"},
    {D3DERR_TEXTURE_SWAP_FAILED,		"D3DERR_TEXTURE_SWAP_FAILED"},
    {D3DERR_TEXTURE_UNLOCK_FAILED,		"D3DERR_TEXTURE_UNLOCK_FAILED"},
    {D3DERR_TOOMANYOPERATIONS,			"D3DERR_TOOMANYOPERATIONS"},
    {D3DERR_TOOMANYPRIMITIVES,			"D3DERR_TOOMANYPRIMITIVES"},
    {D3DERR_UNSUPPORTEDALPHAARG,		"D3DERR_UNSUPPORTEDALPHAARG"},
    {D3DERR_UNSUPPORTEDALPHAOPERATION,	"D3DERR_UNSUPPORTEDALPHAOPERATION"},
    {D3DERR_UNSUPPORTEDCOLORARG,		"D3DERR_UNSUPPORTEDCOLORARG"},
    {D3DERR_UNSUPPORTEDCOLOROPERATION,	"D3DERR_UNSUPPORTEDCOLOROPERATION"},
    {D3DERR_UNSUPPORTEDFACTORVALUE,		"D3DERR_UNSUPPORTEDFACTORVALUE"},
    {D3DERR_UNSUPPORTEDTEXTUREFILTER,	"D3DERR_UNSUPPORTEDTEXTUREFILTER"},
    {D3DERR_VBUF_CREATE_FAILED,			"D3DERR_VBUF_CREATE_FAILED"},
    {D3DERR_VERTEXBUFFERLOCKED,			"D3DERR_VERTEXBUFFERLOCKED"},
    {D3DERR_VERTEXBUFFEROPTIMIZED,		"D3DERR_VERTEXBUFFEROPTIMIZED"},
    {D3DERR_VERTEXBUFFERUNLOCKFAILED,	"D3DERR_VERTEXBUFFERUNLOCKFAILED"},
    {D3DERR_VIEWPORTDATANOTSET,			"D3DERR_VIEWPORTDATANOTSET"},
    {D3DERR_VIEWPORTHASNODEVICE,		"D3DERR_VIEWPORTHASNODEVICE"},
    {D3DERR_WRONGTEXTUREFORMAT,			"D3DERR_WRONGTEXTUREFORMAT"},
    {D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY,	"D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY"},
    {D3DERR_ZBUFF_NEEDS_VIDEOMEMORY,	"D3DERR_ZBUFF_NEEDS_VIDEOMEMORY"},
    {D3DERR_ZBUFFER_NOTPRESENT,			"D3DERR_ZBUFFER_NOTPRESENT"},
    {E_NOINTERFACE,						"IUNKNOWN: E_NOINTERFACE"},
    {E_POINTER,							"IUNKNOWN: E_POINTER"},
    {S_OK,								NULL}
};

void GetErrorDesc( HRESULT err, const char* &desc )
{
    if ( err == 0 )
    {
        desc = "All OK";
    }
    else
    {
        HRESULT cur = ErrorCodes[0].hrErrorCode;
        int i;
        for (i=0; cur != err && cur != S_OK; cur = ErrorCodes[++i].hrErrorCode );

        if ( cur == err )
            desc = ErrorCodes[i].errorDesc;
        else
            desc = "Unknown Error";
    }
}

HRESULT Lib3D::ChangeDisplaySettings(HWND hWnd,SWord width,SWord height,bool fSet)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if (fSet)
    {
        DEVMODE dmMode;
        ZeroMemory(&dmMode,sizeof(DEVMODE));
        dmMode.dmSize=sizeof(DEVMODE);
        int i,f;
        for (i=0,f=0; (f=EnumDisplaySettings(NULL,i,&dmMode))!=0; i++)
            if (dmMode.dmPelsWidth==width &&
                    dmMode.dmPelsHeight==height)
                break;
        if (f)
        {
            dmMode.dmFields=DM_PELSWIDTH+DM_PELSHEIGHT;
            ::ChangeDisplaySettings(&dmMode,CDS_FULLSCREEN);
        }
        else return DDERR_UNSUPPORTED;
    }
    else ::ChangeDisplaySettings(NULL,0);
    return S_OK;
#endif
}

HRESULT Lib3D::GetMaxLandDotProduct(D3DVALUE& maxdp)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    maxdp=d3dl7Lights[LIGHT_SUNMOON].dvDirection.dvY;
    if (maxdp<0.f)	maxdp=-maxdp;
    return S_OK;
#endif
}

HRESULT Lib3D::MakeMipLevel(LPDIRECTDRAWSURFACE7 pddsSrc,LPDIRECTDRAWSURFACE7 pddsDst)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    DDSURFACEDESC2 ddsdSrc,ddsdDst;
    ZeroMemory(&ddsdSrc,sizeof(ddsdSrc));
    ZeroMemory(&ddsdDst,sizeof(ddsdDst));
    ddsdSrc.dwSize=sizeof(ddsdSrc);
    ddsdDst.dwSize=sizeof(ddsdDst);
    pddsDst->Lock(NULL,&ddsdDst,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT|DDLOCK_WRITEONLY,NULL);
    pddsSrc->Lock(NULL,&ddsdSrc,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT|DDLOCK_READONLY,NULL);
    UWord *pdst=(UWord*)ddsdDst.lpSurface;
    ULong *psrc=(ULong*)ddsdSrc.lpSurface;
    for (DWORD y=ddsdDst.dwHeight; y>0; y--)
    {
        UWord *pdst2=pdst;
        ULong *psrc2=psrc;
        for (DWORD x=ddsdDst.dwWidth; x>0; x--) *pdst2++=*psrc2++;
        pdst=(UWord*)(ULong(pdst)+ddsdDst.lPitch);
        psrc=(ULong*)(ULong(psrc)+(ddsdSrc.lPitch<<1));
    }
    pddsSrc->Unlock(NULL);
    pddsDst->Unlock(NULL);
    return S_OK;
#endif
}

void	Lib3D::SetFogValues( const D3DVALUE& FogStart, const D3DVALUE& FogEnd )
{
    fogStart = FogStart;
    fogEnd = FogEnd;
}

// Debug....
void	Lib3D::GivePolyCount(int&	nopolysest)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
#else

#ifdef	_SHAPE_DEBUG_
    nopolysest = noPolysDebug;
    noPolysDebug = 0;
#else
    nopolysest = 0;
#endif
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTextureRAM
//Author		Robert Slater
//Date			Fri 24 Mar 2000
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Lib3D::GetTextureRAM(ULong&	noBytes)
{
    noBytes = texturesTotalRAM;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GetFreeVideoMemory

// Date:		10/07/00
// Author:		JON
//
//Description:	Returns the amount of free video memory (as returned by direct x)
//
//////////////////////////////////////////////////////////////////////

ULong	Lib3D::GetFreeVideoMemory( void )
{
// Evaluate texture RAM (-video RAM)
    static ULong lastFree = 0;
    DDSCAPS2 ddscaps;
    ZeroMemory(&ddscaps,sizeof(ddscaps));
    ddscaps.dwCaps=DDSCAPS_TEXTURE;
    DWORD	freeRAM,totalAvail;

    //get available video memory to decide whether a mode should be allowed
    pDD7->GetAvailableVidMem(&ddscaps,&totalAvail,&freeRAM);
    lastFree = freeRAM;
    return freeRAM;
}

#ifndef _NOT_IN_SAMPLE

class Col24BitPtr
{
    UByte* data;
public:
    void setVal( ULong val ) // assign it a uLong value - use the bottom3 Bytes
    {
        UByte* t = (UByte*)&val;
        data[0] = t[0];
        data[1] = t[1];
        data[2] = t[2];
    }
    ULong getVal( void ) // might return some rubbish in the top bytes.. never mind...
    {
        ULong retVal = *( (ULong*)(data) );
        return retVal;
    }
    void operator= ( ULong* t )
    {
        data = (UByte*)t;
    }
    void operator= ( Col24BitPtr t )
    {
        data = t.data;
    }
    void operator++ ( void ) // prefix operator
    {
        data+=3;
    }
    void operator++ ( int ) // postfix operator
    {
        data+=3;
    }
    void operator+= ( int val )
    {
        data+=(3*val);
    }
    void incByBytes( int val )
    {
        data+=val;
    }
    void decByBytes( int val )
    {
        data-=val;
    }
};

class Col16BitPtr
{
    UWord* data;
    ULong buffer;
public:
    void setVal( ULong val ) // assign it a uLong value
    {
        *data=UWord(val);
    }
    ULong getVal( void )
    {
//		if (buffer&2)
//			return (buffer>>16);
//		else
//		{
//			buffer=*(ULong*)data;
//			return buffer&0xffff;
//		}
        return ULong(*data);
    }
    void operator= ( ULong* t )
    {
        data = (UWord*)t;
    }
    void operator= ( Col16BitPtr t )
    {
        data = t.data;
    }
    void operator++ ( void ) // prefix operator
    {
        ++data;
    }
    void operator++ ( int ) // postfix operator
    {
        data++;
    }
    void operator+= ( int val )
    {
        data+=val;
    }
    void incByBytes( int val )
    {
        data=(UWord*)( ULong(data)+val );
    }
    void decByBytes( int val )
    {
        data=(UWord*)( ULong(data)-val );
    }
};

class Col32BitPtr
{
    ULong* data;
public:
    void setVal( ULong val ) // assign it a uLong value
    {
        *data=val;
    }
    ULong getVal( void ) // might return some rubbish in the top bytes.. never mind...
    {
        return *data;
    }
    void operator= ( ULong* t )
    {
        data = t;
    }
    void operator= ( Col32BitPtr t )
    {
        data = t.data;
    }
    void operator++ ( void ) // prefix operator
    {
        ++data;
    }
    void operator++ ( int ) // postfix operator
    {
        data++;
    }
    void operator+= ( int val )
    {
        data+=val;
    }
    void incByBytes( int val )
    {
        data=(ULong*)( ULong(data)+val );
    }
    void decByBytes( int val )
    {
        data=(ULong*)( ULong(data)-val );
    }
};

#define COPY_AND_TRANSFORM_IMAGE_DATA(SOURCE_FORMAT,DEST_FORMAT)					\
{																					\
	SOURCE_FORMAT lpSrc;															\
	DEST_FORMAT lpDst;																\
																					\
	bool flipSource;																\
	if ( sourceHeight < 0 )															\
	{																				\
		flipSource = true;															\
		sourceHeight =- sourceHeight;												\
		lpSrc=(ULong*) (ULong(pSourceData) + (sourceHeight-1)*sourcePitch);			\
	} else																			\
	{																				\
		flipSource = false;															\
		lpSrc=(ULong*)pSourceData;													\
	}																				\
	lpDst=(ULong*)pDestData;														\
																					\
	for (DWORD y=destHeight;y>0;y--) /* for each y in the destination */			\
	{																				\
		SOURCE_FORMAT lpSrc2=lpSrc;													\
		DEST_FORMAT lpDst2=lpDst;													\
		for (DWORD x=destWidth;x>0;x--) /* for each x in the destination */			\
		{																			\
			lpDst2.setVal( MaskAndRot(lpSrc2.getVal(),rMShift,gMShift,bMShift,rmask,gmask,bmask)); \
			lpDst2++;																\
			lpSrc2++;																\
		}																			\
		if ( flipSource )															\
		{																			\
			lpSrc.decByBytes( sourcePitch );										\
		} else																		\
		{																			\
			lpSrc.incByBytes( sourcePitch );										\
		}																			\
		lpDst.incByBytes( destPitch );												\
	}																				\
}
#endif

// doesn't do any scaling at the moment... only supporst source and dest of 16, 24 and 32 bpp.
HRESULT Lib3D::SoftwareImageCopy(
    void* pSourceData,
    int sourceWidth,
    int sourceHeight,
    int sourceBitCount,
    DWORD sourceRBitMask,
    DWORD sourceGBitMask,
    DWORD sourceBBitMask,
    DWORD sourcePitch,			// number of bytes in a scan line of source (often sourceBitCount*sourceWidth)
    void* pDestData,
    int destWidth,
    int destHeight,
    int destBitCount,
    DWORD destRBitMask,
    DWORD destGBitMask,
    DWORD destBBitMask,
    DWORD destPitch				// number of bytes in a scan line of dest
)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    if ( destWidth<10)
    {
        UByte* pd=(UByte*)pSourceData;
        pd+=(sourceBitCount/8)*(int(sourceWidth*.5-destWidth*1.5-2));
        pSourceData=pd;
    }
    else if ( sourceWidth!=destWidth || abs(sourceHeight)!=abs(destHeight) )
        INT3;

    SWord redShift,greenShift,blueShift;

    redShift=	GET_BIT_POS32(destRBitMask)-GET_BIT_POS32(sourceRBitMask);
    greenShift=	GET_BIT_POS32(destGBitMask)-GET_BIT_POS32(sourceGBitMask);
    blueShift=	GET_BIT_POS32(destBBitMask)-GET_BIT_POS32(sourceBBitMask);

    UByte rMShift = calcMWordRot( redShift );
    UByte gMShift = calcMWordRot( greenShift );
    UByte bMShift = calcMWordRot( blueShift );

    ULong rmask=destRBitMask&MagicRotate(rMShift,sourceRBitMask);
    ULong gmask=destGBitMask&MagicRotate(gMShift,sourceGBitMask);
    ULong bmask=destBBitMask&MagicRotate(bMShift,sourceBBitMask);

    switch (destBitCount)
    {
    case 16:
        switch (sourceBitCount)
        {
        case 16:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col16BitPtr, Col16BitPtr );
            break;
        case 24:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col24BitPtr, Col16BitPtr );
            break;
        case 32:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col32BitPtr, Col16BitPtr );
            break;
            NODEFAULT;
        }
        break;
    case 24:
        switch (sourceBitCount)
        {
        case 16:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col16BitPtr, Col24BitPtr );
            break;
        case 24:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col24BitPtr, Col24BitPtr );
            break;
        case 32:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col32BitPtr, Col24BitPtr );
            break;
            NODEFAULT;
        }
        break;
    case 32:
        switch (sourceBitCount)
        {
        case 16:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col16BitPtr, Col32BitPtr );
            break;
        case 24:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col24BitPtr, Col32BitPtr );
            break;
        case 32:
            COPY_AND_TRANSFORM_IMAGE_DATA( Col32BitPtr, Col32BitPtr );
            break;
            NODEFAULT;
        }
        break;
        NODEFAULT;
    }

    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScreenShot
//Author		Jon Booth
//Date			Mon 10 Apr 2000
//
//Description	Grabs a screenshot to the given bitmap - bitmap must be 24 bit and
//				screen dimensions.  Also note this grabs the contents of the back buffer
//				The bitmap can be the 'wrong' way up - make it's height -ve
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
int Lib3D::ScreenShot( BITMAPINFOHEADER* pInfo,void* pData)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    DDSURFACEDESC2          ddsd;
//    HDC                     hdc;
    ddsd.dwSize = sizeof(ddsd);
    pDDSB7->GetSurfaceDesc(&ddsd); // the back buffer

    if (pData==NULL)
    {
        //request to fill in header & return length of header
        pInfo->biWidth=ddsd.dwWidth;
        pInfo->biHeight=ddsd.dwHeight;
        pInfo->biBitCount=24;	//ddsd.ddpfPixelFormat.dwRGBBitCount;
        BITMAPINFO* pIP=(BITMAPINFO*)pInfo;
        ULongP(pIP->bmiColors)[2]=0xff0000;
        ULongP(pIP->bmiColors)[1]=0x00ff00;
        ULongP(pIP->bmiColors)[0]=0x0000ff;
        return pInfo->biSize+12;
    }



    // get surface info
    if ( pInfo->biBitCount != 24 )
        INT3;

    ddsd.ddsCaps.dwCaps=DDSCAPS_VIDEOMEMORY | DDSCAPS_NONLOCALVIDMEM|DDSCAPS_OFFSCREENPLAIN ;
    ddsd.ddsCaps.dwCaps2=0;//DDSCAPS2_HINTDYNAMIC ;
    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
//    static LPDIRECTDRAWSURFACE7 tmp=NULL;
//	if (tmp==NULL)
//		pDD7->CreateSurface(&ddsd,&tmp,NULL);
//	tmp->Blt(NULL,pDDSB7,NULL,DDBLT_WAIT,NULL);
    ddsd.ddsCaps.dwCaps=DDSCAPS_SYSTEMMEMORY |DDSCAPS_OFFSCREENPLAIN ;
    static	LPDIRECTDRAWSURFACE7 tmp2=NULL;

//TempCode JIM 19Jul00	//THIS CODE PERFORMS A BLIT TO SYSTEM RAM
//TempCode RDH 17Jul00 	if (tmp2==NULL)
//TempCode RDH 17Jul00 		pDD7->CreateSurface(&ddsd,&tmp2,NULL);
//TempCode RDH 17Jul00 	tmp2->Blt(NULL,pDDSB7,NULL,DDBLT_WAIT,NULL);
    //THIS CODE READS DIRECT FROM VIDEO IMAGE
    tmp2=pDDSB7;

    int destpitch=((pInfo->biBitCount/8)*pInfo->biWidth+3)&-4;
    if (pInfo->biWidth<10)
        destpitch=((pInfo->biBitCount/8)*ddsd.dwWidth+3)&-4;
    tmp2->Lock(NULL,&ddsd,DDLOCK_READONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);


    SoftwareImageCopy( ddsd.lpSurface,												// source data
                       ddsd.dwWidth,									// source width
                       -SLong(ddsd.dwHeight),									// source height,
                       ddsd.ddpfPixelFormat.dwRGBBitCount,							// source bitcount
                       ddsd.ddpfPixelFormat.dwRBitMask,								// source r mask,
                       ddsd.ddpfPixelFormat.dwGBitMask,								//		   g
                       ddsd.ddpfPixelFormat.dwBBitMask,								//		   b
                       ddsd.lPitch,													// source pitch.
                       pData,														// dest data
                       pInfo->biWidth,									// dest width
                       pInfo->biHeight,									// dest height,
                       pInfo->biBitCount,									// dest bitcount
                       0xFF0000,													// dest. r mask
                       0xFF00,														// dest. g mask
                       0xFF,														// dest. b mask
                       destpitch
                     );
    tmp2->Unlock(NULL);
//TempCode JON 7Jul00 	tmp2->Release();

    return ((pInfo->biWidth*pInfo->biBitCount/8+3)&-4)*pInfo->biHeight;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackgroundImage
//Author		Jon Booth
//Date			Mon 10 Apr 2000
//
//Description	Displays the 24bit bmp image given onto the back of the display
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
HRESULT	Lib3D::BackgroundImage( BITMAPFILEHEADER* pFile )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    DDSURFACEDESC2          ddsd;
    HDC                     hdc;

    UByte* pData=(UByte*)pFile;
    BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));

    pData+=pFile->bfOffBits;

    //
    // Get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
    pDDSB7->GetSurfaceDesc(&ddsd); // the back buffer

    if ( ddsd.dwWidth >= pInfo->bmiHeader.biWidth )
    {
        // the target is bigger... lets make it stretch

        if ((lastError = pDDSB7->GetDC(&hdc)) == DD_OK)
        {
            StretchDIBits(
                hdc,					        // handle to device context
                0,							// x-coordinate of upper-left corner of dest. rectangle
                0,							// y-coordinate of upper-left corner of dest. rectangle
                ddsd.dwWidth,					// width of destination rectangle
                ddsd.dwHeight,				// height of destination rectangle
                0,							// x-coordinate of upper-left corner of source rectangle
                0,							// y-coordinate of upper-left corner of source rectangle
                pInfo->bmiHeader.biWidth,		// width of source rectangle
                pInfo->bmiHeader.biHeight,	// height of source rectangle
                pData,						// address of bitmap bits
                pInfo,						// address of bitmap data
                DIB_RGB_COLORS,		        // usage flags
                SRCCOPY						// raster operation code
            );
            pDDSB7->ReleaseDC(hdc);
        }
    }
    else
    {
        if ( pInfo->bmiHeader.biBitCount != 24 )
            INT3;

        pDDSB7->Lock(NULL,&ddsd,DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);

        ULong sPitch = (24/8)*pInfo->bmiHeader.biWidth;
        SoftwareImageCopy( pData+( sPitch*(pInfo->bmiHeader.biHeight-ddsd.dwHeight)),	// source data
                           ddsd.dwWidth,										// source width
                           -SLong(ddsd.dwHeight),								// source height,
                           24,													// source bitcount
                           0xFF0000,											// source r mask,
                           0xFF00,												//		   g
                           0xFF,												//		   b
                           sPitch,			// often sourceBitCount*sourceWidth,													// source pitch.
                           ddsd.lpSurface,										// dest data
                           ddsd.dwWidth,										// dest width
                           ddsd.dwHeight,										// dest height,
                           ddsd.ddpfPixelFormat.dwRGBBitCount,					// dest bitcount
                           ddsd.ddpfPixelFormat.dwRBitMask,						// dest. r mask
                           ddsd.ddpfPixelFormat.dwGBitMask,						// dest. g mask
                           ddsd.ddpfPixelFormat.dwBBitMask,						// dest. b mask
                           ddsd.lPitch
                         );
        pDDSB7->Unlock(NULL);

    }

//DEADCODE JON 6/8/00 	if ( pInfo->bmiHeader.biBitCount != 24 )
//DEADCODE JON 6/8/00 		INT3;
//DEADCODE JON 6/8/00 //	if ( ddsd.ddpfPixelFormat.dwRGBBitCount != 16 )
//DEADCODE JON 6/8/00 //		INT3;
//DEADCODE JON 6/8/00
//DEADCODE JON 6/8/00 	// lock the back buffer
//DEADCODE JON 6/8/00 //	UByte* tempOut = new UByte[ ddsd.dwHeight * ddsd.lPitch ];// make a fake output
//DEADCODE JON 6/8/00
//DEADCODE JON 6/8/00 	pDDSB7->Lock(NULL,&ddsd,DDLOCK_WRITEONLY|DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
//DEADCODE JON 6/8/00 	SoftwareImageCopy( pData,							// source data
//DEADCODE JON 6/8/00 					   pInfo->bmiHeader.biWidth,				// source width
//DEADCODE JON 6/8/00 					   -pInfo->bmiHeader.biHeight,				// source height,
//DEADCODE JON 6/8/00 					   24,								// source bitcount
//DEADCODE JON 6/8/00 					   0xFF0000,//pInfoHdr->bV4RedMask,			// source r mask,
//DEADCODE JON 6/8/00 					   0xFF00,//pInfoHdr->bV4GreenMask,			//		   g
//DEADCODE JON 6/8/00 					   0xFF,//pInfoHdr->bV4BlueMask,			//		   b
//DEADCODE JON 6/8/00 					   (24/8)*pInfo->bmiHeader.biWidth,			// source pitch.
//DEADCODE JON 6/8/00 					   /*tempOut,*/ ddsd.lpSurface,					// dest data
//DEADCODE JON 6/8/00 					   pInfo->bmiHeader.biWidth,				// dest width
//DEADCODE JON 6/8/00 					   pInfo->bmiHeader.biHeight,				// dest height,
//DEADCODE JON 6/8/00 					   ddsd.ddpfPixelFormat.dwRGBBitCount,	// dest bitcount
//DEADCODE JON 6/8/00 					   ddsd.ddpfPixelFormat.dwRBitMask, // dest. r mask
//DEADCODE JON 6/8/00 					   ddsd.ddpfPixelFormat.dwGBitMask, // dest. g mask
//DEADCODE JON 6/8/00 					   ddsd.ddpfPixelFormat.dwBBitMask, // dest. b mask
//DEADCODE JON 6/8/00 					   ddsd.lPitch						// dest pitch
//DEADCODE JON 6/8/00 		);
//DEADCODE JON 6/8/00 	pDDSB7->Unlock(NULL);
//DEADCODE JON 6/8/00
//DEADCODE JON 6/8/00 //	delete[] tempOut;

    return lastError;
#endif
}

HRESULT Lib3D::DoFade( D3DCOLOR fadeCol, UByte fadeDepth )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    //	fadeDepth = 64;
    UByte midVal = fadeDepth;
    int tmpVal = fadeDepth<<1;
    if( tmpVal > 0xFF )
    {
        fadeDepth = 0xFF;
    }
    else
    {
        fadeDepth = tmpVal;
    }

    struct PolyCoords
    {
        Float x,y;
    };
    struct PolyDefs
    {
        SLong a,b,c;
    };
    const int _pointCnt=9;
    const int _polyCnt=8;
    static PolyCoords _coords[_pointCnt]=
    {
        {-1,-1},
        {0,-1},
        {1,-1},
        {1,0},
        {1,1},
        {0,1},
        {-1,1},
        {-1,0},
        {0,0}
    };

    static PolyDefs _polys[_polyCnt]= {{8,1,0},{8,2,1},{8,3,2},{8,4,3},{8,5,4},{8,6,5},{8,7,6},{8,0,7}};

//DEADCODE JON 6/1/00 	D3DVIEWPORT7 vp;
//DEADCODE JON 6/1/00 #pragma message ( __HERE__ "fixfades" )
//DEADCODE JON 6/1/00 	pD3DDEV7->GetViewport(&vp);
//DEADCODE JON 6/1/00
//DEADCODE JON 6/1/00 	D3DVALUE sx,sy;
//DEADCODE JON 6/1/00 	D3DVALUE cx,cy;
//DEADCODE JON 6/1/00 	sx=D3DVALUE(vp.dwWidth>>1);
//DEADCODE JON 6/1/00 	sy=-D3DVALUE(vp.dwHeight>>1);
//DEADCODE JON 6/1/00 	cx=D3DVALUE(vp.dwX)+sx;
//DEADCODE JON 6/1/00 	cy=D3DVALUE(vp.dwY)-sy;
//DEADCODE JON 6/1/00

    SPolygon *sPolygon;
    SVertex *sVertex;

    for ( int i=0; i< _polyCnt; i++ )
    {
        ALLOCATE_POLYGON(sPolygon,3);
        sPolygon->zbuffer=1;

//DEADCODE JON 6/1/00 		sPolygon->material=HMATERIAL(UByte(120));//set a fake material
//DEADCODE JON 5/10/00 		sPolygon->material.uniqueTextId = (120&TIT_PLAIN); //shouldn't need
        sPolygon->material = NULL_MATERIAL;
        sPolygon->material.materialFlags = IS_PLAIN;
        sPolygon->projectType = PROJECT_2D;
        sPolygon->zDepth2d=0;
        sVertex=sPolygon->pVertexList;

        sVertex->sx=_coords[_polys[i].a].x;//*(sx)+(cx);			//center point
        sVertex->sy=_coords[_polys[i].a].y;//*(sy)+(cy);

//		sVertex->sz=0.0;
//		sVertex->rhw=1.0;//0.9999;
        sVertex->specular=SPECULAR_NO_FOG;
        sVertex->color=fadeCol;
        SetColAlpha( sVertex->color, midVal );
        sVertex=sVertex->pNext;

        sVertex->sx=_coords[_polys[i].b].x;//*(sx)+(cx);			//1st edgepoint
        sVertex->sy=_coords[_polys[i].b].y;//*(sy)+(cy);
//		sVertex->sz=0.0;
//		sVertex->rhw=1.0;//0.9999;
        sVertex->specular=SPECULAR_NO_FOG;
        sVertex->color=fadeCol;
        SetColAlpha( sVertex->color, fadeDepth );
        sVertex=sVertex->pNext;

        sVertex->sx=_coords[_polys[i].c].x;//*(sx)+(cx);			//2nd edgepoint
        sVertex->sy=_coords[_polys[i].c].y;//*(sy)+(cy);
//		sVertex->sz=0.0;
//		sVertex->rhw=1.0;//0.9999;
        sVertex->specular=SPECULAR_NO_FOG;
        sVertex->color=fadeCol;
        SetColAlpha( sVertex->color, fadeDepth );

        ADD_POLYGON(transparentPolys,sPolygon);
    }

    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoWhiteOut
//Author		Robert Slater
//Date			Thu 20 Apr 2000
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
HRESULT Lib3D::DoWhiteOut( const D3DCOLOR& fadeCol, const UByte& fadeDepth, const D3DVALUE& ssx,  const D3DVALUE& ssy, const D3DVALUE& glaredepth)
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    struct PolyCoords
    {
        Float x,y;
    };
    struct PolyDefs
    {
        SLong a,b,c;
    };
    const int _pointCnt=9;
    const int _polyCnt=8;
    float	minx,miny,maxx,maxy;
    float	centrex,centrey;
    float	glaresize = 0.25 + (0.75*glaredepth);
    UByte	realfade = UByte(glaredepth*D3DVALUE(fadeDepth));

    centrex = ssx;
    centrey = -ssy;

    minx = centrex - glaresize;
    if (minx < -1.)
        minx = -1.;

    maxx = centrex + glaresize;
    if (maxx > 1.)
        maxx = 1.;

    miny = centrey - glaresize;
    if (miny < -1.)
        miny = -1.;

    maxy = centrey + glaresize;
    if (maxy > 1.)
        maxy = 1.;

    PolyCoords _coords[_pointCnt]=
    {
        {minx,miny},
        {centrex,(miny+centrey)/2},
        {maxx,miny},
        {(maxx+centrex)/2,centrey},
        {maxx,maxy},
        {centrex,(maxy+centrey)/2},
        {minx,maxy},
        {(minx+centrex)/2,centrey},
        {centrex,centrey}
    };

    static PolyDefs _polys[_polyCnt]= {{8,1,0},{8,2,1},{8,3,2},{8,4,3},{8,5,4},{8,6,5},{8,7,6},{8,0,7}};

//DEADCODE JON 6/1/00 	D3DVIEWPORT7 vp;
//DEADCODE JON 6/1/00 #pragma message ( __HERE__ "fixfades" )
//DEADCODE JON 6/1/00 	pD3DDEV7->GetViewport(&vp);
//DEADCODE JON 6/1/00
//DEADCODE JON 6/1/00 	D3DVALUE sx,sy;
//DEADCODE JON 6/1/00 	D3DVALUE cx,cy;
//DEADCODE JON 6/1/00 	sx=D3DVALUE(vp.dwWidth>>1);
//DEADCODE JON 6/1/00 	sy=-D3DVALUE(vp.dwHeight>>1);
//DEADCODE JON 6/1/00 	cx=D3DVALUE(vp.dwX)+sx;
//DEADCODE JON 6/1/00 	cy=D3DVALUE(vp.dwY)-sy;

    SPolygon *sPolygon;
    SVertex *sVertex;

    for ( int i=0; i< _polyCnt; i++ )
    {
        ALLOCATE_POLYGON(sPolygon,3);
        sPolygon->zbuffer=1;
//DEADCODE JON 6/1/00 		sPolygon->material=HMATERIAL(UByte(120));//set a fake material
//DEADCODE JON 5/10/00 		sPolygon->material.mathandle = 120; //shouldn't need
        sPolygon->material = NULL_MATERIAL;
        sPolygon->material.materialFlags = IS_PLAIN;
        sPolygon->projectType = PROJECT_2D;
        sPolygon->zDepth2d=0;
        sVertex=sPolygon->pVertexList;

        sVertex->sx=_coords[_polys[i].a].x;//*(sx)+(cx);			//center point
        sVertex->sy=_coords[_polys[i].a].y;//*(sy)+(cy);

        sVertex->sz=0.0;
        sVertex->rhw=1.0;
        sVertex->specular=SPECULAR_NO_FOG;
        sVertex->color=fadeCol;
        SetColAlpha( sVertex->color, realfade );
        sVertex=sVertex->pNext;

        sVertex->sx=_coords[_polys[i].b].x;//*(sx)+(cx);			//1st edgepoint
        sVertex->sy=_coords[_polys[i].b].y;//*(sy)+(cy);

        sVertex->sz=0.0;
        sVertex->rhw=1.0;
        sVertex->specular=SPECULAR_NO_FOG;
        sVertex->color=fadeCol;
        SetColAlpha( sVertex->color, 0 );
        sVertex=sVertex->pNext;

        sVertex->sx=_coords[_polys[i].c].x;//*(sx)+(cx);			//2nd edgepoint
        sVertex->sy=_coords[_polys[i].c].y;//*(sy)+(cy);

        sVertex->sz=0.0;
        sVertex->rhw=1.0;
        sVertex->specular=SPECULAR_NO_FOG;
        sVertex->color=fadeCol;
        SetColAlpha( sVertex->color, 0 );

        ADD_POLYGON(transparentPolys,sPolygon);
    }

    return S_OK;
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackgroundImage
//Author		Jon Booth
//Date			Wed 19 Apr 2000
//
//	Descr:		This will flush all of the current information library onto the back buffer and
//				clear the z buffer.
HRESULT Lib3D::FlushAsBackground( void )
{
    HRESULT hr = EndScene(); // draw on the stuff
    if ( hr == S_OK )
        hr = _BeginScene(hCurrentRenderTarget); // start up a new scene
    return hr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetZDepth
//Author		Robert Slater
//Date			Thu 20 Apr 2000
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
HRESULT Lib3D::GetZDepth( ULong& zret)
{
    zret = currentZBufferDepth;

    return S_OK;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawQuadSphere
//Author		Robert Slater
//Date			Tue 6 Jun 2000
//
//Description	2----3----4			Draw a fan about point 0
//				|	 |	  |
//				|	 |	  |
//				1----0----5
//				|	 |	  |
//				|	 |	  |
//				8----7----6
//
//Inputs
//			Uses the translation on the object matrix as the center point of the sphere
//			in eye space, ignoring the vertex passed in. Ignores the roll too.
//Returns
//
//------------------------------------------------------------------------------
HRESULT Lib3D::DrawQuadSphere(	const HMATERIAL& hMaterial,	//texture
                                const DoPointStruc& vertex,	//center
                                const D3DVALUE& radius,		//radius
                                const Angles roll,			//roll angle
                                const SWord u0,const SWord v0,	//texture coords for tl corner
                                const SWord u1,const SWord v1)	//texture coords for br corner
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

    D3DVALUE fu0,fv0,fu1,fv1;

#ifndef NDEBUG
    if ( insidePoly == true )
        return DDERR_GENERIC;
#endif
    if ((lastError=SetMaterial(hMaterial))!=DD_OK) return lastError;
//DeadCode JON 20Oct00 	if (hMaterial.tsW[0]!=0) // assume this is always the case
    {
// Adding a 0.5 pixel border gets rid of the scruffy edges...
        fu0=(D3DVALUE(u0)+0.5)*hMaterial.tsW[0];						//RJS 17Sep00
        fu1=(D3DVALUE(u1)-0.5)*hMaterial.tsW[0];						//RJS 17Sep00
        fv0=(D3DVALUE(v0)+0.5)*hMaterial.tsH[0];						//RJS 17Sep00
        fv1=(D3DVALUE(v1)-0.5)*hMaterial.tsH[0];						//RJS 17Sep00
    }

    ALLOCATE_POLYGON_NOLINK(currentPoly,10);
    SVertex *sVertex=currentPoly->pVertexList;

//DeadCode JON 6Sep00 	*sVertex = vertex;

//DeadCode RJS 19Jun00 //Transform the centre point...
//DeadCode RJS 19Jun00
//DeadCode RJS 19Jun00 	sVertex->Transform( objectMatrix+objMatStackPos );
//DeadCode RJS 19Jun00 	sVertex->Transform( viewerMatrix+viewMatStackPos );

// The centre point has already been transformed... we just want the translation
    sVertex->x = objectMatrix[objMatStackPos]._41;
    sVertex->y = objectMatrix[objMatStackPos]._42;
    sVertex->z = objectMatrix[objMatStackPos]._43;
//DeadCode JON 31Aug00 	sVertex->rhw = objectMatrix[objMatStackPos]._44;

    if (sVertex->z > 1.0)												//RJS 19Jun00
    {
        D3DVALUE	rad = radius;
        ULong		theColour = gLightingDesc.ambientRGB;

        SetColAlpha( theColour, globAlpha );

        sVertex->color = theColour;
        sVertex->specular=SPECULAR_NO_FOG;

        sVertex[0].pNext = &sVertex[1];
        sVertex[1] = *sVertex;
        sVertex[1].pNext = &sVertex[2];
        sVertex[2] = *sVertex;
        sVertex[2].pNext = &sVertex[3];
        sVertex[3] = *sVertex;
        sVertex[3].pNext = &sVertex[4];
        sVertex[4] = *sVertex;
        sVertex[4].pNext = &sVertex[5];
        sVertex[5] = *sVertex;
        sVertex[5].pNext = &sVertex[6];
        sVertex[6] = *sVertex;
        sVertex[6].pNext = &sVertex[7];
        sVertex[7] = *sVertex;
        sVertex[7].pNext = &sVertex[8];
        sVertex[8] = *sVertex;
        sVertex[8].pNext = &sVertex[9];								//RJS 16Jun00
#ifdef DO_INDEXED_VB
        sVertex[0].identical =
            sVertex[1].identical =
                sVertex[2].identical =
                    sVertex[3].identical =
                        sVertex[4].identical =
                            sVertex[5].identical =
                                sVertex[6].identical =
                                    sVertex[7].identical =
                                        sVertex[8].identical =
                                            sVertex[9].identical = NULL;
#endif


        sVertex[1].x-=rad;
        sVertex[2].x-=rad;
        sVertex[2].y+=rad;
        sVertex[3].y+=rad;
        sVertex[4].x+=rad;
        sVertex[4].y+=rad;
        sVertex[5].x+=rad;
        sVertex[6].x+=rad;
        sVertex[6].y-=rad;
        sVertex[7].y-=rad;
        sVertex[8].x-=rad;
        sVertex[8].y-=rad;
        sVertex[9] = sVertex[1];
        sVertex[9].pNext = sVertex;									//RJS 16Jun00

        R3DMATRIX *pMat=projectionMatrix+projMatStackPos;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu1;
        sVertex->tv=fv1;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu0;
        sVertex->tv=fv1;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu0;
        sVertex->tv=fv0;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu1;
        sVertex->tv=fv0;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu0;
        sVertex->tv=fv0;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu0;
        sVertex->tv=fv1;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu0;
        sVertex->tv=fv0;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu1;
        sVertex->tv=fv0;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu0;
        sVertex->tv=fv0;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;
        sVertex=sVertex->pNext;

        sVertex->Transform( pMat );
        sVertex->z=zSMALL;
//DeadCode JON 31Aug00 		sVertex->z = sVertex->hw;										//JON 28Jul00
        sVertex->tu=fu0;
        sVertex->tv=fv1;
        sVertex->clipcode=ClipCodeLRTB( sVertex );
        currentPoly->andcode&=sVertex->clipcode;
        currentPoly->orcode|=sVertex->clipcode;

// should never be clipped, always be 3d, transparent
//TempCode JON 6Sep00 		if (currentPoly->andcode==0)
//TempCode JON 6Sep00 		{
//TempCode JON 6Sep00 	#ifdef	_SHAPE_DEBUG_
//TempCode JON 6Sep00 		noPolysDebug++;
//TempCode JON 6Sep00 	#endif
//TempCode JON 6Sep00 #pragma warnmsg ( "Should do the fan clipping stuff.." )
//TempCode JON 6Sep00 	 		if (currentPoly->orcode!=0)
//TempCode JON 6Sep00 				GenericPolyClip(currentPoly);
//TempCode JON 6Sep00
//TempCode JON 6Sep00 			if (currentPoly->vertexcount>2)
//TempCode JON 6Sep00 			{
//TempCode JON 6Sep00 				if (currentPoly->material.isMasked==0)
//TempCode JON 6Sep00 				{
//TempCode JON 6Sep00 					if (renderMode == HINT_3DRENDER)
//TempCode JON 6Sep00 					{
//TempCode JON 6Sep00 						currentPoly->projectType=STANDARD_PROJECT;
//TempCode JON 6Sep00 					}
//TempCode JON 6Sep00 					else
//TempCode JON 6Sep00 					{
//TempCode JON 6Sep00 						currentPoly->projectType=PROJECT_2D;
//TempCode JON 6Sep00 						currentPoly->zDepth2d = zDepth2d;
//TempCode JON 6Sep00 					}
//TempCode JON 6Sep00 //DeadCode JON 21Aug00 					ADD_POLYGON(*texturedPolysP,currentPoly);
//TempCode JON 6Sep00 //DeadCode JON 21Aug00 					AddEdgeAliasing(currentPoly);
//TempCode JON 6Sep00 					ADD_POLYGON(texturedPolys,currentPoly);
//TempCode JON 6Sep00 					AddEdgeAliasing(currentPoly);
//TempCode JON 6Sep00 				}
//TempCode JON 6Sep00 				else
//TempCode JON 6Sep00 				{  //its transparent
//TempCode JON 6Sep00 					if (renderMode == HINT_3DRENDER)
        {
            currentPoly->projectType=SPHERE_PROJECT;
            currentPoly->CalcTransZ( zFactor, 0.0f );
            //				currentPoly->CalcTransZ(zFactor,tZBias_f); // don't ever do a bias on these...
        }
//TempCode JON 6Sep00 					else
//TempCode JON 6Sep00 					{
//TempCode JON 6Sep00 						currentPoly->projectType=PROJECT_2D;
//TempCode JON 6Sep00 						currentPoly->zDepth2d = zDepth2d;
//TempCode JON 6Sep00 						currentPoly->SetTrans2DZ(zBuffer2d);
//TempCode JON 6Sep00 					}
        ADD_POLYGON(transparentPolys,currentPoly);
//TempCode JON 6Sep00 				}
//TempCode JON 6Sep00 			}
//TempCode JON 6Sep00 		}
//TempCode JON 6Sep00 		else
//TempCode JON 6Sep00 		{
//TempCode JON 6Sep00 			DISCARD_POLYGON(currentPoly);
//TempCode JON 6Sep00 		}
    }
    else
        DISCARD_POLYGON(currentPoly);

    return S_OK;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawPivotedSphere
//Author		Robert Slater
//Date			Tue 6 Jun 2000
//
//Description	The base of the sphere is its pivot point.
//				Scale the x & y to the ratio of the texture coords.
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
HRESULT Lib3D::DrawPivotedSphere(	const HMATERIAL& hMaterial,	//texture
                                    const DoPointStruc& vertex,	//center
                                    const D3DVALUE& radius,		//radius
                                    const Angles roll,			//roll angle
                                    const SWord u0,const SWord v0,	//texture coords for tl corner
                                    const SWord u1,const SWord v1)	//texture coords for br corner
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    D3DVALUE fu0,fv0,fu1,fv1;

#ifndef NDEBUG
    if ( insidePoly == true )
        return DDERR_GENERIC;
#endif
    if ((lastError=SetMaterial(hMaterial))!=DD_OK) return lastError;
//DeadCode JON 20Oct00 	if (hMaterial.tsW[0]!=0) // assume this is always the case
    {
        fu0=(D3DVALUE(u0)+0.5)*hMaterial.tsW[0];						//RJS 22Sep00
        fu1=(D3DVALUE(u1)-0.5)*hMaterial.tsW[0];						//RJS 22Sep00
        fv0=(D3DVALUE(v0)+0.5)*hMaterial.tsH[0];						//RJS 22Sep00
        fv1=(D3DVALUE(v1)-0.5)*hMaterial.tsH[0];						//RJS 22Sep00
    }

    ALLOCATE_POLYGON_NOLINK(currentPoly,4);
    SVertex *sVertex=currentPoly->pVertexList;

    *sVertex = vertex;

    if (fCombineMatrices) CombineMatrices();							//RJS 22Sep00
    //RJS 22Sep00
    sVertex->Transform( &objViewMatrix );								//RJS 22Sep00
//DeadCode RJS 22Sep00 	sVertex->Transform( objectMatrix+objMatStackPos );
//DeadCode RJS 22Sep00 	sVertex->Transform( viewerMatrix+viewMatStackPos );

    D3DVALUE radx = radius;
    D3DVALUE rady;

    sVertex->VolumetricSphere( radx );

    rady = (2.* radx * (fv1-fv0))/(fu1-fu0);

    ULong		theColour = gLightingDesc.ambientRGB;
    SetColAlpha( theColour, globAlpha );

    sVertex->color = theColour;
    sVertex->specular=0x00000000;

// Optimised version of CALC_FOG   (all vertices are in the same Z plane)
    sVertex->specular.alpha = fogTable[ (0x3FF&F2UL_Round( sVertex->z*fogMul )) ];	//RJS 22Sep00

    sVertex[0].pNext = &sVertex[1];
    sVertex[1] = *sVertex;
    sVertex[1].pNext = &sVertex[2];
    sVertex[2] = *sVertex;
    sVertex[2].pNext = &sVertex[3];
    sVertex[3] = *sVertex;
    sVertex[3].pNext = sVertex;

#ifdef DO_INDEXED_VB
    sVertex[0].identical =
        sVertex[1].identical =
            sVertex[2].identical =
                sVertex[3].identical = NULL;
#endif

    if (0==roll)
    {
        sVertex[0].x-=radx;
        sVertex[0].y+=rady;
        sVertex[1].x+=radx;
        sVertex[1].y+=rady;
        sVertex[2].x+=radx;
        sVertex[3].x-=radx;
    }
    else
    {
        D3DVALUE sineX,cosineY;
        D3DVALUE sineY,cosineX;
        D3DVALUE sine,cosine;
        SineCosine(roll,&sine,&cosine);
        sineY=sine*rady;
        cosineX=cosine*radx;
        sineX=sine*radx;
        cosineY=cosine*rady;

        sVertex[0].x+=-sineY-cosineX;
        sVertex[0].y+=-sineX+cosineY;
        sVertex[1].x+=cosineX-sineY;
        sVertex[1].y+=cosineY+sineX;
        sVertex[2].x+=cosineX;
        sVertex[2].y+=sineX;
        sVertex[3].x+=-cosineX;
        sVertex[3].y+=-sineX;
    }

    R3DMATRIX *pMat=projectionMatrix+projMatStackPos;

    sVertex->Transform( pMat );
    sVertex->tu=fu0;
    sVertex->tv=fv0;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

    sVertex->Transform( pMat );
    sVertex->tu=fu1;
    sVertex->tv=fv0;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

    sVertex->Transform( pMat );
    sVertex->tu=fu1;
    sVertex->tv=fv1;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;
    sVertex=sVertex->pNext;

    sVertex->Transform( pMat );
    sVertex->tu=fu0;
    sVertex->tv=fv1;
    sVertex->clipcode=ClipCodeFBLRTB( sVertex );
    currentPoly->andcode&=sVertex->clipcode;
    currentPoly->orcode|=sVertex->clipcode;

    if (currentPoly->andcode==0)
    {
#ifdef	_SHAPE_DEBUG_
        noPolysDebug++;
#endif
        if (currentPoly->orcode!=0)
            GenericPolyClip(currentPoly/*,SizeOfVertex*/);

        if (currentPoly->vertexcount>2)
        {
            if (currentPoly->material.isMasked==0)
            {
                if (renderMode == HINT_3DRENDER)
                    currentPoly->projectType=STANDARD_PROJECT;
                else
                {
                    currentPoly->projectType=PROJECT_2D;
                    currentPoly->zDepth2d = zDepth2d;
                }
//DeadCode JON 21Aug00 				ADD_POLYGON(*texturedPolysP,currentPoly);
                ADD_POLYGON(texturedPolys,currentPoly);
                AddEdgeAliasing(currentPoly);
            }
            else
            {
                //its transparent
                if (renderMode == HINT_3DRENDER)
                {
                    currentPoly->projectType=SPHERE_PROJECT;
                    currentPoly->CalcTransZ( zFactor, 0.0f );
//					currentPoly->CalcTransZ(zFactor,tZBias_f); // don't ever do a bias on these...
                }
                else
                {
                    currentPoly->projectType=PROJECT_2D;
                    currentPoly->zDepth2d = zDepth2d;
                    currentPoly->SetTrans2DZ(zBuffer2d);
                }
                ADD_POLYGON(transparentPolys,currentPoly);
            }
        }
    }
    else
    {
        DISCARD_POLYGON(currentPoly);
    }
    return S_OK;
#endif
}

HRESULT Lib3D::SetMirrorTexture( const HMATERIAL& mat )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else
    mirrorTexture = mat;
//	mirrorRect.bottom=mirrorRect.right=256;
    // test that the texture given is not too big
    if ( mirrorTexture.p[0]->w != 128 || mirrorTexture.p[0]->h != 128)
    {
        return DDERR_INVALIDRECT;
        INT3;
    }

    mirrorRect.bottom = mirrorTexture.p[0]->h;
    mirrorRect.right = mirrorTexture.p[0]->w;

//DeadCode JON 7Nov00 	if (flags&F_TEXTURECANBERENDERTARGET)
//DeadCode JON 7Nov00 	{
    if ( textureTable[ mat.p[0]->hTextureMap ] != pDDS7Mirror )
    {
        textureTable[ mat.p[0]->hTextureMap ]->Release();
        textureTable[ mat.p[0]->hTextureMap ] = pDDS7Mirror;
    }
//DeadCode JON 7Nov00 	}
    return S_OK;
#endif
}

HRESULT Lib3D::Wipe( const D3DCOLOR col )							//JON 4Jul00
{
    return pD3DDEV7->Clear(0,NULL,D3DCLEAR_TARGET,col,0,0);
}

void Lib3D::GetDiagnosticString( char* &theString )						//JON 22Aug00
{
    theString = diagString;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetNearClipPlane

// Date:		29/08/00
// Author:		JON
//
//Description:  Sets the near clip plane without changing the projection matrix...
//				returns an error in debug mode if outside the allowed values from the matrix
//
//////////////////////////////////////////////////////////////////////
HRESULT Lib3D::SetNearClipPlane( D3DVALUE dist )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

#ifndef NDEBUG
    if ( dist > matrixFarPlane || dist < matrixNearPlane )
    {
        INT3;
        return DDERR_INVALIDPARAMS;
    }
#endif

    nearZPlane=dist;

    // from the transformation matrix and knowing that some values are 0 or 1
    // z	= mat->_13*tx + mat->_23*ty + mat->_33*tz + mat->_43;
    R3DMATRIX* pMat = projectionMatrix+projMatStackPos;
    zNearClip = pMat->_33*dist + pMat->_43;		// the z at the near clip plane

    return S_OK;
#endif
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetFarClipPlane

// Date:		29/08/00
// Author:		JON
//
//Description:  Sets the far clip plane without changing the projection matrix...
//				returns an error in debug mode if outside the allowed values from the matrix
//
//////////////////////////////////////////////////////////////////////
HRESULT Lib3D::SetFarClipPlane( D3DVALUE dist )
{
#ifdef _NOT_IN_SAMPLE
    INT3;
    return S_OK;
#else

#ifndef NDEBUG
    if ( dist > matrixFarPlane || dist < matrixNearPlane )
    {
        INT3;
        return DDERR_INVALIDPARAMS;
    }
#endif
    farZPlane=dist;

    // from the transformation matrix and knowing that some values are 0 or 1
    // z	= mat->_13*tx + mat->_23*ty + mat->_33*tz + mat->_43;
    R3DMATRIX* pMat = projectionMatrix+projMatStackPos;
    zFarClip = pMat->_33*dist + pMat->_43;		// the z at the far clip plane

    return S_OK;
#endif
}


//////////////////////////////////////////////////////////////////////
//
// Function:   ResetClipDistances

// Date:		10/23/00
// Author:		JON
//
//Description: Sets the near and far clip planes to those from the matrix
//
//////////////////////////////////////////////////////////////////////
void Lib3D::ResetClipDistances( void )						//JON 23Oct00
{
    nearZPlane=matrixNearPlane;

    // from the transformation matrix and knowing that some values are 0 or 1
    // z	= mat->_13*tx + mat->_23*ty + mat->_33*tz + mat->_43;
    zNearClip =  0.0;//pMat->_33*matrixNearPlane + pMat->_43;		// the z at the near clip plane


    farZPlane=matrixFarPlane;

    // from the transformation matrix and knowing that some values are 0 or 1
    // z	= mat->_13*tx + mat->_23*ty + mat->_33*tz + mat->_43;
    R3DMATRIX* pMat = projectionMatrix+projMatStackPos;
    zFarClip = pMat->_33*matrixFarPlane + pMat->_43;		// the z at the far clip plane



}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipTop2D
//Author		Jon.
//Date			Mon 25 Sep 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToTop2D(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    double frac;

    D3DVALUE dy = vo->y-vi->y;

    frac=( clipVal2D-vi->y )/dy;

    vc->y=vi->y+frac*(dy);
    vc->x=vi->x+frac*(vo->x-vi->x);

    vc->hw=vi->hw;
    vc->z=vi->z;

    switch (numTextures)
    {
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }
    ClipSetCols( vi, vo, vc, frac );
    vc->clipcode=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToBottom2D
//Author		Jon.
//Date			Mon 25 Sep 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToBottom2D(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    double frac;

    D3DVALUE dy = vo->y-vi->y;

    frac=( (-clipVal2D)-vi->y )/dy;

    vc->y=vi->y+frac*(dy);
    vc->x=vi->x+frac*(vo->x-vi->x);

    vc->hw=vi->hw;
    vc->z=vi->z;

    switch (numTextures)
    {
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }
    ClipSetCols( vi, vo, vc, frac );
    vc->clipcode=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToRight2D
//Author		Jon.
//Date			Mon 25 Sep 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToRight2D(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    double frac;

    D3DVALUE dx = vo->x-vi->x;

    frac=( clipVal2D-vi->x)/dx;

    vc->y=vi->y+frac*(vo->y-vi->y);
    vc->x=vi->x+frac*(dx);

    vc->hw=vi->hw;
    vc->z=vi->z;

    switch (numTextures)
    {
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }
    ClipSetCols( vi, vo, vc, frac );
    vc->clipcode=ClipCodeTB2D( vc );
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToLeft2D
//Author		Jon.
//Date			Mon 25 Sep 2000
//
//------------------------------------------------------------------------------
void Lib3D::ClipToLeft2D(SVertex *vi,SVertex *vo,SVertex *vc,const ULong numTextures)
{
#ifdef DO_INDEXED_VB
    vc->identical = NULL;
#endif

    double frac;

    D3DVALUE dx = vo->x-vi->x;

    frac=( (-clipVal2D)-vi->x)/dx;

    vc->y=vi->y+frac*(vo->y-vi->y);
    vc->x=vi->x+frac*(dx);

    vc->hw=vi->hw;
    vc->z=vi->z;

    switch (numTextures)
    {
        NODEFAULT;
//DeadCode JON 30Oct00 		case 3:
//DeadCode JON 30Oct00 			vc->tu2=Interp(vi->tu2,vo->tu2,frac);
//DeadCode JON 30Oct00 			vc->tv2=Interp(vi->tv2,vo->tv2,frac);
    case 2:
        vc->tu1=Interp(vi->tu1,vo->tu1,frac);
        vc->tv1=Interp(vi->tv1,vo->tv1,frac);
    case 1:
        vc->tu =Interp(vi->tu ,vo->tu ,frac);
        vc->tv =Interp(vi->tv ,vo->tv ,frac);
    case 0:
        break;
    }
    ClipSetCols( vi, vo, vc, frac );
    vc->clipcode=ClipCodeTB2D( vc );
}

void Lib3D::GenericPolyClip2D(SPolygon *poly)
{
    int newPntCnt=0;
    int pntCnt=int(poly->vertexcount);
    int limit;
    int i;

    int numTextures = poly->material.f;
    SVertex **polyA,**polyB;
    SVertex **pCur/* ,**pNxt */;
    SVertex *pV;

    polyA=pCur=(SVertex**)Alloc(sizeof(SVertex*)*(poly->vertexcount+8));
    polyB=(SVertex**)Alloc(sizeof(SVertex*)*(poly->vertexcount+8));

    pV=poly->pVertexList;

    for (i=poly->vertexcount; i!=0; i--)
    {
        *pCur=pV;
        pCur++;
        pV=pV->pNext;
    }

    //clip against the east clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyA,i,j,polyB,newPntCnt,CLIP_RIGHT,ClipToRight2D, numTextures);
    }
    DOCLIP(polyA,i,0,polyB,newPntCnt,CLIP_RIGHT,ClipToRight2D, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the west clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyB,i,j,polyA,newPntCnt,CLIP_LEFT,ClipToLeft2D, numTextures);
    }
    DOCLIP(polyB,i,0,polyA,newPntCnt,CLIP_LEFT,ClipToLeft2D, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the top clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyA,i,j,polyB,newPntCnt,CLIP_TOP,ClipToTop2D, numTextures);
    }
    DOCLIP(polyA,i,0,polyB,newPntCnt,CLIP_TOP,ClipToTop2D, numTextures);

    if ((pntCnt=newPntCnt)<3)
    {
        poly->vertexcount=0;
        return;
    }

    newPntCnt=0;

    //clip against the bottom clipping plane

    limit=int(pntCnt)-1;

    for (i=0; i<limit; i++)
    {
        int j=i+1;

        DOCLIP(polyB,i,j,polyA,newPntCnt,CLIP_BOTTOM,ClipToBottom2D, numTextures);
    }
    DOCLIP(polyB,i,0,polyA,newPntCnt,CLIP_BOTTOM,ClipToBottom2D, numTextures);

    pntCnt=newPntCnt;
    if (pntCnt>2)
    {
        // put the poly back together again...
        for (i=0; i<pntCnt-1; i++) polyA[i]->pNext=polyA[i+1];
        polyA[i]->pNext=polyA[0];
        poly->pVertexList=polyA[0];
    }
    poly->vertexcount=pntCnt;
}

void	Lib3D::SetMasterShading( LIGHTFLAG& lf )							//JON 29Sep00
{
    LIGHTFLAG old = masterLightFlag;
    masterLightFlag = lf;
    lf = old;
}

  void Lib3D::AddEdgeAliasing(SPolygon *poly)
    {
        if (edgeAlias==HINT_ALIASEDGES)
        {
            SVertex *cur,*nxt;
            HMATERIAL hM(UByte(0));
            nxt=poly->pVertexList;
            for (int i=poly->vertexcount; i>0; i--)
            {
                cur=nxt;
                nxt=nxt->pNext;
                SLine *line=(SLine*)Alloc(sizeof(SLine));
//DeadCode JON 15Nov00 				line->andcode=
//DeadCode JON 15Nov00 					line->orcode=0;
                line->material=hM;
//DEADCODE JON 5/24/00 				line->vertices[0]=cur->d3dtlvert;
//DEADCODE JON 5/24/00 				line->vertices[1]=nxt->d3dtlvert;
                line->vertices[0]=*cur;
                line->vertices[1]=*nxt;

                line->pNext=aliasLineList;
                aliasLineList=line;
            }
        }
    }

 inline void Lib3D::ALLOCATE_POLYGON( SPolygon* &p1, const ULong &p2 )
    {
        (p1)=(SPolygon*)Alloc(sizeof(SPolygon)+(p2)*sizeof(SVertex));
        (p1)->vertexcount=(p2);
        (p1)->material=hLastMaterial;
        (p1)->orcode=0;
        (p1)->andcode=0xFFFF;
        (p1)->pVertexList=(SVertex*)(ULong(p1)+sizeof(SPolygon));
        {
            SVertex *pp=(p1)->pVertexList;
            for (int q=(p2)-1; q>0; q--,pp++)
            {
#ifdef DO_INDEXED_VB
                pp->identical = NULL;
#endif
                pp->pNext=(pp+1);
            }
            pp->pNext=(p1)->pVertexList;
        }
    }

  inline void Lib3D::ALLOCATE_POLYGON_NOLINK( SPolygon* &p1, const ULong &p2 ) // allocates the polygon - doesn't link the verices tho, or set and and orcode
    {
        (p1)=(SPolygon*)Alloc(sizeof(SPolygon)+(p2)*sizeof(SVertex));
        (p1)->vertexcount=(p2);
        (p1)->material=hLastMaterial;
        (p1)->orcode=0;
        (p1)->andcode=0xFFFF;
        (p1)->pVertexList=(SVertex*)(ULong(p1)+sizeof(SPolygon));
    }

    inline void Lib3D::ALLOCATE_POLYGON_TNL( SPolygon* &p1, const ULong &p2 )
    {
        (p1)=(SPolygon*)Alloc(sizeof(SPolygon)+(p2)*sizeof(TNLSVertex));
        (p1)->vertexcount=(p2);
        (p1)->material=hLastMaterial;
        (p1)->pVertexList=(SVertex*)(ULong(p1)+sizeof(SPolygon));
    }

    inline void Lib3D::ADD_POLYGON( SPolygon* &l1, SPolygon* &p1 )
    {

        (p1)->pNext=(l1);
        (l1)=(p1);
        (p1)->projectType+=w_16bit;
    }

//DEADCODE JON 5/25/00 	inline void PROJECT_SETZ( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)
//DEADCODE JON 5/25/00 	{
//DEADCODE JON 5/25/00 		SVertex *pp=(p1)->pVertexList;
//DEADCODE JON 5/25/00 		D3DVALUE ztot=0.f;
//DEADCODE JON 5/25/00 		for (int q=(p1)->vertexcount;q>0;q--)
//DEADCODE JON 5/25/00 		{
//DEADCODE JON 5/25/00 			D3DVALUE sz;
//DEADCODE JON 5/25/00 			sz=1/pp->hw;
//DEADCODE JON 5/25/00 #ifdef	_WBUFFERTEST_
//DEADCODE JON 5/25/00 			pp->rhw=sz*.001;
//DEADCODE JON 5/25/00 #else
//DEADCODE JON 5/25/00 			pp->rhw=sz;
//DEADCODE JON 5/25/00 #endif
//DEADCODE JON 5/25/00 			pp->sx=pp->sx*sz*(sx)+(cx);
//DEADCODE JON 5/25/00 			pp->sy=pp->sy*sz*(sy)+(cy);
//DEADCODE JON 5/25/00 //DEADCODE JON 4/12/00 			pp->sz*=sz;
//DEADCODE JON 5/25/00 			pp->sz*=zFactor;
//DEADCODE JON 5/25/00 			ztot+=pp->sz;
//DEADCODE JON 5/25/00 #ifdef	_ZBUFFERTEST_
//DEADCODE JON 5/25/00 			pp->sz = 0;
//DEADCODE JON 5/25/00 #endif
//DEADCODE JON 5/25/00 			pp=pp->pNext;
//DEADCODE JON 5/25/00 		}
//DEADCODE JON 5/25/00 		ztot/=D3DVALUE((p1)->vertexcount);
//DEADCODE JON 5/25/00 		(p1)->zbuffer=FPNormToLong(ztot);
//DEADCODE JON 5/25/00 	}

//DEADCODE JON 5/25/00 	inline void PROJECT_SPHERE( SPolygon* p1, const D3DVALUE& cx, const D3DVALUE& cy, const D3DVALUE& sx, const D3DVALUE& sy)//, const D3DVALUE& radius)
//DEADCODE JON 5/25/00 	{
//DEADCODE JON 5/25/00 		//All points are on the same plane...
//DEADCODE JON 5/25/00 		SVertex		*pp=(p1)->pVertexList;
//DEADCODE JON 5/25/00 		D3DVALUE	toScreen = 1./pp->hw;
//DEADCODE JON 5/25/00 //		D3DVALUE	shiftedrhw = 1./(pp->rhw - radius);
//DEADCODE JON 5/25/00 		D3DVALUE	toScreenX = toScreen*sx;
//DEADCODE JON 5/25/00 		D3DVALUE	toScreenY = toScreen*sy;
//DEADCODE JON 5/25/00 		D3DVALUE	sz = pp->sz*zFactor;//(pp->sz-radius)*zFactor;
//DEADCODE JON 5/25/00
//DEADCODE JON 5/25/00 		for (int q=(p1)->vertexcount;q>0;q--)
//DEADCODE JON 5/25/00 		{
//DEADCODE JON 5/25/00 			pp->rhw=toScreen;//shiftedrhw;
//DEADCODE JON 5/25/00 			pp->sx=(pp->sx*toScreenX)+(cx);
//DEADCODE JON 5/25/00 			pp->sy=(pp->sy*toScreenY)+(cy);
//DEADCODE JON 5/25/00 			pp->sz=sz;
//DEADCODE JON 5/25/00 			pp=pp->pNext;
//DEADCODE JON 5/25/00 		}
//DEADCODE JON 5/25/00 		(p1)->zbuffer=FPNormToLong(sz);
//DEADCODE JON 5/25/00 	}

    inline void Lib3D::PROJECT_LINE( SLine* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)
    {
        D3DVALUE sz;
        SVertex *pp=(p1)->vertices;
        if ( prefZType == D3DZB_USEW )
        {
            sz=1.f/pp->hw;
            pp->rhw=sz;
            pp->sx=pp->sx*sz*(sx)+(cx);
            pp->sy=pp->sy*sz*(sy)+(cy);
            pp->sz*=zFactor;
            pp++;
            sz=1.f/pp->hw;
            pp->rhw=sz;
            pp->sx=pp->sx*sz*(sx)+(cx);
            pp->sy=pp->sy*sz*(sy)+(cy);
            pp->sz*=zFactor;
        }
        else
        {
            sz=1.f/pp->hw;
            pp->rhw=sz;
            pp->sx=pp->sx*sz*(sx)+(cx);
            pp->sy=pp->sy*sz*(sy)+(cy);
            pp->sz*=sz;
            pp++;
            sz=1.f/pp->hw;
            pp->rhw=sz;
            pp->sx=pp->sx*sz*(sx)+(cx);
            pp->sy=pp->sy*sz*(sy)+(cy);
            pp->sz*=sz;
        }
    }

    inline void Lib3D::PROJECT_POINT( SVertex* pp, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)
    {
        if ( prefZType == D3DZB_USEW )
        {
            D3DVALUE sz=1.f/pp->hw;
            pp->rhw=sz;
            pp->sx=pp->sx*sz*(sx)+(cx);
            pp->sy=pp->sy*sz*(sy)+(cy);
            pp->sz*=zFactor;
        }
        else
        {
            D3DVALUE sz=1.f/pp->hw;
            pp->rhw=sz;
            pp->sx=pp->sx*sz*(sx)+(cx);
            pp->sy=pp->sy*sz*(sy)+(cy);
            pp->sz*=sz;
        }
    }

//DeadCode JON 27Sep00 	inline void PROJECT( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)
//DeadCode JON 27Sep00 	{
//DeadCode JON 27Sep00 		SVertex *pp=(p1)->pVertexList;
//DeadCode JON 27Sep00 		for (int q=(p1)->vertexcount;q>0;q--)
//DeadCode JON 27Sep00 		{
//DeadCode JON 27Sep00 			D3DVALUE sz;
//DeadCode JON 27Sep00 			sz=1./pp->hw;
//DeadCode JON 27Sep00 #ifdef	_WBUFFERTEST_
//DeadCode JON 27Sep00 			pp->rhw=sz*.001;
//DeadCode JON 27Sep00 #else
//DeadCode JON 27Sep00 			pp->rhw=sz;
//DeadCode JON 27Sep00 #endif
//DeadCode JON 27Sep00 			pp->sx=pp->sx*sz*(sx)+(cx);
//DeadCode JON 27Sep00 			pp->sy=pp->sy*sz*(sy)+(cy);
//DeadCode JON 27Sep00 #ifndef LINEAR_Z_FIX
//DeadCode JON 27Sep00 	 		pp->sz*=sz;
//DeadCode JON 27Sep00 #else
//DeadCode JON 27Sep00 			pp->sz*=zFactor;
//DeadCode JON 27Sep00 #endif
//DeadCode JON 27Sep00 			pp=pp->pNext;
//DeadCode JON 27Sep00 		}
//DeadCode JON 27Sep00 	}

    inline void Lib3D::PROJECT( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)
    {
        SVertex *pp=(p1)->pVertexList;

        if ( prefZType == D3DZB_USEW )
            for (int q=(p1)->vertexcount; q>0; q--)
            {
                D3DVALUE sz;
                sz=1./pp->hw;
                pp->rhw=sz;
                pp->sx=pp->sx*sz*(sx)+(cx);
                pp->sy=pp->sy*sz*(sy)+(cy);
                pp->sz*=zFactor;
                pp=pp->pNext;
            }
        else
            for (int q=(p1)->vertexcount; q>0; q--)
            {
                D3DVALUE sz;
                sz=1./pp->hw;
                pp->rhw=sz;
                pp->sx=pp->sx*sz*(sx)+(cx);
                pp->sy=pp->sy*sz*(sy)+(cy);
                pp->sz*=sz;
                pp=pp->pNext;
            }
    }


//DEADCODE JON 5/25/00 	inline void PROJECT_2D( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)
//DEADCODE JON 5/25/00 	{
//DEADCODE JON 5/25/00 		SVertex *pp=(p1)->pVertexList;
//DEADCODE JON 5/25/00 		for (int q=(p1)->vertexcount;q>0;q--)
//DEADCODE JON 5/25/00 		{
//DEADCODE JON 5/25/00 			pp->rhw=1.0f-zDepth2d;
//DEADCODE JON 5/25/00 			pp->sz=zDepth2d;
//DEADCODE JON 5/25/00 			pp->sx=pp->sx*(sx)+(cx);
//DEADCODE JON 5/25/00 			pp->sy=pp->sy*(sy)+(cy);
//DEADCODE JON 5/25/00 //DEADCODE JON 4/13/00 			pp->color=0xFFFFFF;
//DEADCODE JON 5/25/00 			pp=pp->pNext;
//DEADCODE JON 5/25/00 		}
//DEADCODE JON 5/25/00 		(p1)->zbuffer=0;
//DEADCODE JON 5/25/00 	}

//TempCode JON 14Jul00 	inline void PROJECT_2DSETCOL( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)
//TempCode JON 14Jul00 	{
//TempCode JON 14Jul00 		SVertex *pp=(p1)->pVertexList;
//TempCode JON 14Jul00 		for (int q=(p1)->vertexcount;q>0;q--)
//TempCode JON 14Jul00 		{
//TempCode JON 14Jul00 			pp->rhw=1.0f-zDepth2d;
//TempCode JON 14Jul00 			pp->sz=zDepth2d;
//TempCode JON 14Jul00 			pp->sx=pp->sx*(sx)+(cx);
//TempCode JON 14Jul00 			pp->sy=pp->sy*(sy)+(cy);
//TempCode JON 14Jul00 			pp->color=gFontColour;
//TempCode JON 14Jul00 			pp=pp->pNext;
//TempCode JON 14Jul00 		}
//TempCode JON 14Jul00 		(p1)->zbuffer=0;
//TempCode JON 14Jul00 	}

#ifndef NO_HARD_TNL
    inline void Lib3D::TnlTransSetPolyZ(SPolygon* poly)
    {
        D3DVERTEX pc;
        D3DTLVERTEX pct;
        D3DVALUE ztot=0.f;
        pc.x = pc.y = pc.z = 0;
        for ( int i=0; i<poly->vertexcount; i++ )
        {
            pc.x+=polyVertArray[i].x;
            pc.y+=polyVertArray[i].y;
            pc.z+=polyVertArray[i].z;
        }
        D3DVALUE recipvercount = 1.f/poly->vertexcount;
        pc.x*=recipvercount;
        pc.y*=recipvercount;
        pc.z*=recipvercount;
        Transform(&pc,&pct,&transpMatrix[transMatPos]);
        ztot+=pct.sx*pct.sx;
        ztot+=pct.sy*pct.sz;
        ztot+=pct.sy*pct.sz;
        poly->zbuffer=FPNormToLong(ztot);
    }
#endif

    inline void Lib3D::SetColAlpha( ULong &col, const UByte& val )
    {
        UByte *t = (UByte*)(&col);
        t[3]=val;
    }

inline ULong Lib3D::InlineGenGuardBandClipCode( const SVertex* pV, const D3DVALUE sz, const ULong prevFlags )
{
	ULong retVal;
	switch ( prevFlags )
	{
//DeadCode JON 12Jun00 		case 0:		retVal = GenGuardBandClipCode( pV, sz, 0 );
		case 0:		retVal = 0;break;
		case 1:		retVal = GenGuardBandClipCode( pV, sz, 1 ); break;
		case 2:		retVal = GenGuardBandClipCode( pV, sz, 2 ); break;
		case 3:		retVal = GenGuardBandClipCode( pV, sz, 3 ); break;
		case 4:		retVal = GenGuardBandClipCode( pV, sz, 4 ); break;
		case 5:		retVal = GenGuardBandClipCode( pV, sz, 5 ); break;
		case 6:		retVal = GenGuardBandClipCode( pV, sz, 6 ); break;
		case 7:		retVal = GenGuardBandClipCode( pV, sz, 7 ); break;
		case 8:		retVal = GenGuardBandClipCode( pV, sz, 8 ); break;
		case 9:		retVal = GenGuardBandClipCode( pV, sz, 9 ); break;
		case 10:	retVal = GenGuardBandClipCode( pV, sz, 10 ); break;
		case 11:	retVal = GenGuardBandClipCode( pV, sz, 11 ); break;
		case 12:	retVal = GenGuardBandClipCode( pV, sz, 12 ); break;
		case 13:	retVal = GenGuardBandClipCode( pV, sz, 13 ); break;
		case 14:	retVal = GenGuardBandClipCode( pV, sz, 14 ); break;
		case 15:	retVal = GenGuardBandClipCode( pV, sz, 15 ); break;
		NODEFAULT;
	}
	return retVal;
}

inline void Lib3D::InlineSetCurrentMaterial(const HMATERIAL& mat, const ULong flags)
{
	switch( flags )
	{
		case 0: SetCurrentMaterial( mat, 0 ); break;
		case 1: SetCurrentMaterial( mat, 1 ); break;
		case 2: SetCurrentMaterial( mat, 2 ); break;
		case 3: SetCurrentMaterial( mat, 3 ); break;
		case 4: SetCurrentMaterial( mat, 4 ); break;
		case 5: SetCurrentMaterial( mat, 5 ); break;
		case 6: SetCurrentMaterial( mat, 6 ); break;
		case 7: SetCurrentMaterial( mat, 7 ); break;
		case 8: SetCurrentMaterial( mat, 8 ); break;
		case 9: SetCurrentMaterial( mat, 9 ); break;
		case 10: SetCurrentMaterial( mat, 10 ); break;
		case 11: SetCurrentMaterial( mat, 11 ); break;
		case 12: SetCurrentMaterial( mat, 12 ); break;
		case 13: SetCurrentMaterial( mat, 13 ); break;
		case 14: SetCurrentMaterial( mat, 14 ); break;
		case 15: SetCurrentMaterial( mat, 15 ); break;
		case 16: SetCurrentMaterial( mat, 16 ); break;
		case 17: SetCurrentMaterial( mat, 17 ); break;
		case 18: SetCurrentMaterial( mat, 18 ); break;
		case 19: SetCurrentMaterial( mat, 19 ); break;
		case 20: SetCurrentMaterial( mat, 20 ); break;
		case 21: SetCurrentMaterial( mat, 21 ); break;
		case 22: SetCurrentMaterial( mat, 22 ); break;
		case 23: SetCurrentMaterial( mat, 23 ); break;
		case 24: SetCurrentMaterial( mat, 24 ); break;
		case 25: SetCurrentMaterial( mat, 25 ); break;
		case 26: SetCurrentMaterial( mat, 26 ); break;
		case 27: SetCurrentMaterial( mat, 27 ); break;
		case 28: SetCurrentMaterial( mat, 28 ); break;
		case 29: SetCurrentMaterial( mat, 29 ); break;
		case 30: SetCurrentMaterial( mat, 30 ); break;
		case 31: SetCurrentMaterial( mat, 31 ); break;
		case 32: SetCurrentMaterial( mat, 32 ); break;
		case 33: SetCurrentMaterial( mat, 33 ); break;
		case 34: SetCurrentMaterial( mat, 34 ); break;
		case 35: SetCurrentMaterial( mat, 35 ); break;
		case 36: SetCurrentMaterial( mat, 36 ); break;
		case 37: SetCurrentMaterial( mat, 37 ); break;
		case 38: SetCurrentMaterial( mat, 38 ); break;
		case 39: SetCurrentMaterial( mat, 39 ); break;
		case 40: SetCurrentMaterial( mat, 40 ); break;
		case 41: SetCurrentMaterial( mat, 41 ); break;
		case 42: SetCurrentMaterial( mat, 42 ); break;
		case 43: SetCurrentMaterial( mat, 43 ); break;
		case 44: SetCurrentMaterial( mat, 44 ); break;
		case 45: SetCurrentMaterial( mat, 45 ); break;
		case 46: SetCurrentMaterial( mat, 46 ); break;
		case 47: SetCurrentMaterial( mat, 47 ); break;
		case 48: SetCurrentMaterial( mat, 48 ); break;
		case 49: SetCurrentMaterial( mat, 49 ); break;
		case 50: SetCurrentMaterial( mat, 50 ); break;
		case 51: SetCurrentMaterial( mat, 51 ); break;
		case 52: SetCurrentMaterial( mat, 52 ); break;
		case 53: SetCurrentMaterial( mat, 53 ); break;
		case 54: SetCurrentMaterial( mat, 54 ); break;
		case 55: SetCurrentMaterial( mat, 55 ); break;
		case 56: SetCurrentMaterial( mat, 56 ); break;
		case 57: SetCurrentMaterial( mat, 57 ); break;
		case 58: SetCurrentMaterial( mat, 58 ); break;
		case 59: SetCurrentMaterial( mat, 59 ); break;
		case 60: SetCurrentMaterial( mat, 60 ); break;
		case 61: SetCurrentMaterial( mat, 61 ); break;
		case 62: SetCurrentMaterial( mat, 62 ); break;
		case 63: SetCurrentMaterial( mat, 63 ); break;
		NODEFAULT;
	}
}
//#pragma warnmsg ( "inline me" )
inline void Lib3D::InlineVertexTransform( SVertex* sVertex, const ULong flags, const LIGHTFLAG curLF )
{
	switch( flags )
	{
		case 0: TransformVertexAsRequired( sVertex, 0, curLF ); break;
		case 1: TransformVertexAsRequired( sVertex, 1, curLF ); break;
		case 2: TransformVertexAsRequired( sVertex, 2, curLF ); break;
		case 3: TransformVertexAsRequired( sVertex, 3, curLF ); break;
		case 4: TransformVertexAsRequired( sVertex, 4, curLF ); break;
		case 5: TransformVertexAsRequired( sVertex, 5, curLF ); break;
		case 6: TransformVertexAsRequired( sVertex, 6, curLF ); break;
		case 7: TransformVertexAsRequired( sVertex, 7, curLF ); break;
		case 8: TransformVertexAsRequired( sVertex, 8, curLF ); break;
		case 9: TransformVertexAsRequired( sVertex, 9, curLF ); break;
		case 10: TransformVertexAsRequired( sVertex, 10, curLF ); break;
		case 11: TransformVertexAsRequired( sVertex, 11, curLF ); break;
		case 12: TransformVertexAsRequired( sVertex, 12, curLF ); break;
		case 13: TransformVertexAsRequired( sVertex, 13, curLF ); break;
		case 14: TransformVertexAsRequired( sVertex, 14, curLF ); break;
		case 15: TransformVertexAsRequired( sVertex, 15, curLF ); break;
		case 16: TransformVertexAsRequired( sVertex, 16, curLF ); break;
		case 17: TransformVertexAsRequired( sVertex, 17, curLF ); break;
		case 18: TransformVertexAsRequired( sVertex, 18, curLF ); break;
		case 19: TransformVertexAsRequired( sVertex, 19, curLF ); break;
		case 20: TransformVertexAsRequired( sVertex, 20, curLF ); break;
		case 21: TransformVertexAsRequired( sVertex, 21, curLF ); break;
		case 22: TransformVertexAsRequired( sVertex, 22, curLF ); break;
		case 23: TransformVertexAsRequired( sVertex, 23, curLF ); break;
		case 24: TransformVertexAsRequired( sVertex, 24, curLF ); break;
		case 25: TransformVertexAsRequired( sVertex, 25, curLF ); break;
		case 26: TransformVertexAsRequired( sVertex, 26, curLF ); break;
		case 27: TransformVertexAsRequired( sVertex, 27, curLF ); break;
		case 28: TransformVertexAsRequired( sVertex, 28, curLF ); break;
		case 29: TransformVertexAsRequired( sVertex, 29, curLF ); break;
		case 30: TransformVertexAsRequired( sVertex, 30, curLF ); break;
		case 31: TransformVertexAsRequired( sVertex, 31, curLF ); break;
		case 32: TransformVertexAsRequired( sVertex, 32, curLF ); break;
		case 33: TransformVertexAsRequired( sVertex, 33, curLF ); break;
		case 34: TransformVertexAsRequired( sVertex, 34, curLF ); break;
		case 35: TransformVertexAsRequired( sVertex, 35, curLF ); break;
		case 36: TransformVertexAsRequired( sVertex, 36, curLF ); break;
		case 37: TransformVertexAsRequired( sVertex, 37, curLF ); break;
		case 38: TransformVertexAsRequired( sVertex, 38, curLF ); break;
		case 39: TransformVertexAsRequired( sVertex, 39, curLF ); break;
		case 40: TransformVertexAsRequired( sVertex, 40, curLF ); break;
		case 41: TransformVertexAsRequired( sVertex, 41, curLF ); break;
		case 42: TransformVertexAsRequired( sVertex, 42, curLF ); break;
		case 43: TransformVertexAsRequired( sVertex, 43, curLF ); break;
		case 44: TransformVertexAsRequired( sVertex, 44, curLF ); break;
		case 45: TransformVertexAsRequired( sVertex, 45, curLF ); break;
		case 46: TransformVertexAsRequired( sVertex, 46, curLF ); break;
		case 47: TransformVertexAsRequired( sVertex, 47, curLF ); break;
		case 48: TransformVertexAsRequired( sVertex, 48, curLF ); break;
		case 49: TransformVertexAsRequired( sVertex, 49, curLF ); break;
		case 50: TransformVertexAsRequired( sVertex, 50, curLF ); break;
		case 51: TransformVertexAsRequired( sVertex, 51, curLF ); break;
		case 52: TransformVertexAsRequired( sVertex, 52, curLF ); break;
		case 53: TransformVertexAsRequired( sVertex, 53, curLF ); break;
		case 54: TransformVertexAsRequired( sVertex, 54, curLF ); break;
		case 55: TransformVertexAsRequired( sVertex, 55, curLF ); break;
		case 56: TransformVertexAsRequired( sVertex, 56, curLF ); break;
		case 57: TransformVertexAsRequired( sVertex, 57, curLF ); break;
		case 58: TransformVertexAsRequired( sVertex, 58, curLF ); break;
		case 59: TransformVertexAsRequired( sVertex, 59, curLF ); break;
		case 60: TransformVertexAsRequired( sVertex, 60, curLF ); break;
		case 61: TransformVertexAsRequired( sVertex, 61, curLF ); break;
		case 62: TransformVertexAsRequired( sVertex, 62, curLF ); break;
		case 63: TransformVertexAsRequired( sVertex, 63, curLF ); break;
		case 64: TransformVertexAsRequired( sVertex, 64, curLF ); break;
		case 65: TransformVertexAsRequired( sVertex, 65, curLF ); break;
		case 66: TransformVertexAsRequired( sVertex, 66, curLF ); break;
		case 67: TransformVertexAsRequired( sVertex, 67, curLF ); break;
		case 68: TransformVertexAsRequired( sVertex, 68, curLF ); break;
		case 69: TransformVertexAsRequired( sVertex, 69, curLF ); break;
		case 70: TransformVertexAsRequired( sVertex, 70, curLF ); break;
		case 71: TransformVertexAsRequired( sVertex, 71, curLF ); break;
		case 72: TransformVertexAsRequired( sVertex, 72, curLF ); break;
		case 73: TransformVertexAsRequired( sVertex, 73, curLF ); break;
		case 74: TransformVertexAsRequired( sVertex, 74, curLF ); break;
		case 75: TransformVertexAsRequired( sVertex, 75, curLF ); break;
		case 76: TransformVertexAsRequired( sVertex, 76, curLF ); break;
		case 77: TransformVertexAsRequired( sVertex, 77, curLF ); break;
		case 78: TransformVertexAsRequired( sVertex, 78, curLF ); break;
		case 79: TransformVertexAsRequired( sVertex, 79, curLF ); break;
		case 80: TransformVertexAsRequired( sVertex, 80, curLF ); break;
		case 81: TransformVertexAsRequired( sVertex, 81, curLF ); break;
		case 82: TransformVertexAsRequired( sVertex, 82, curLF ); break;
		case 83: TransformVertexAsRequired( sVertex, 83, curLF ); break;
		case 84: TransformVertexAsRequired( sVertex, 84, curLF ); break;
		case 85: TransformVertexAsRequired( sVertex, 85, curLF ); break;
		case 86: TransformVertexAsRequired( sVertex, 86, curLF ); break;
		case 87: TransformVertexAsRequired( sVertex, 87, curLF ); break;
		case 88: TransformVertexAsRequired( sVertex, 88, curLF ); break;
		case 89: TransformVertexAsRequired( sVertex, 89, curLF ); break;
		case 90: TransformVertexAsRequired( sVertex, 90, curLF ); break;
		case 91: TransformVertexAsRequired( sVertex, 91, curLF ); break;
		case 92: TransformVertexAsRequired( sVertex, 92, curLF ); break;
		case 93: TransformVertexAsRequired( sVertex, 93, curLF ); break;
		case 94: TransformVertexAsRequired( sVertex, 94, curLF ); break;
		case 95: TransformVertexAsRequired( sVertex, 95, curLF ); break;
		case 96: TransformVertexAsRequired( sVertex, 96, curLF ); break;
		case 97: TransformVertexAsRequired( sVertex, 97, curLF ); break;
		case 98: TransformVertexAsRequired( sVertex, 98, curLF ); break;
		case 99: TransformVertexAsRequired( sVertex, 99, curLF ); break;
		case 100: TransformVertexAsRequired( sVertex, 100, curLF ); break;
		case 101: TransformVertexAsRequired( sVertex, 101, curLF ); break;
		case 102: TransformVertexAsRequired( sVertex, 102, curLF ); break;
		case 103: TransformVertexAsRequired( sVertex, 103, curLF ); break;
		case 104: TransformVertexAsRequired( sVertex, 104, curLF ); break;
		case 105: TransformVertexAsRequired( sVertex, 105, curLF ); break;
		case 106: TransformVertexAsRequired( sVertex, 106, curLF ); break;
		case 107: TransformVertexAsRequired( sVertex, 107, curLF ); break;
		case 108: TransformVertexAsRequired( sVertex, 108, curLF ); break;
		case 109: TransformVertexAsRequired( sVertex, 109, curLF ); break;
		case 110: TransformVertexAsRequired( sVertex, 110, curLF ); break;
		case 111: TransformVertexAsRequired( sVertex, 111, curLF ); break;
		case 112: TransformVertexAsRequired( sVertex, 112, curLF ); break;
		case 113: TransformVertexAsRequired( sVertex, 113, curLF ); break;
		case 114: TransformVertexAsRequired( sVertex, 114, curLF ); break;
		case 115: TransformVertexAsRequired( sVertex, 115, curLF ); break;
		case 116: TransformVertexAsRequired( sVertex, 116, curLF ); break;
		case 117: TransformVertexAsRequired( sVertex, 117, curLF ); break;
		case 118: TransformVertexAsRequired( sVertex, 118, curLF ); break;
		case 119: TransformVertexAsRequired( sVertex, 119, curLF ); break;
		case 120: TransformVertexAsRequired( sVertex, 120, curLF ); break;
		case 121: TransformVertexAsRequired( sVertex, 121, curLF ); break;
		case 122: TransformVertexAsRequired( sVertex, 122, curLF ); break;
		case 123: TransformVertexAsRequired( sVertex, 123, curLF ); break;
		case 124: TransformVertexAsRequired( sVertex, 124, curLF ); break;
		case 125: TransformVertexAsRequired( sVertex, 125, curLF ); break;
		case 126: TransformVertexAsRequired( sVertex, 126, curLF ); break;
		case 127: TransformVertexAsRequired( sVertex, 127, curLF ); break;
		case 128: TransformVertexAsRequired( sVertex, 128, curLF ); break;
		case 129: TransformVertexAsRequired( sVertex, 129, curLF ); break;
		case 130: TransformVertexAsRequired( sVertex, 130, curLF ); break;
		case 131: TransformVertexAsRequired( sVertex, 131, curLF ); break;
		case 132: TransformVertexAsRequired( sVertex, 132, curLF ); break;
		case 133: TransformVertexAsRequired( sVertex, 133, curLF ); break;
		case 134: TransformVertexAsRequired( sVertex, 134, curLF ); break;
		case 135: TransformVertexAsRequired( sVertex, 135, curLF ); break;
		case 136: TransformVertexAsRequired( sVertex, 136, curLF ); break;
		case 137: TransformVertexAsRequired( sVertex, 137, curLF ); break;
		case 138: TransformVertexAsRequired( sVertex, 138, curLF ); break;
		case 139: TransformVertexAsRequired( sVertex, 139, curLF ); break;
		case 140: TransformVertexAsRequired( sVertex, 140, curLF ); break;
		case 141: TransformVertexAsRequired( sVertex, 141, curLF ); break;
		case 142: TransformVertexAsRequired( sVertex, 142, curLF ); break;
		case 143: TransformVertexAsRequired( sVertex, 143, curLF ); break;
		case 144: TransformVertexAsRequired( sVertex, 144, curLF ); break;
		case 145: TransformVertexAsRequired( sVertex, 145, curLF ); break;
		case 146: TransformVertexAsRequired( sVertex, 146, curLF ); break;
		case 147: TransformVertexAsRequired( sVertex, 147, curLF ); break;
		case 148: TransformVertexAsRequired( sVertex, 148, curLF ); break;
		case 149: TransformVertexAsRequired( sVertex, 149, curLF ); break;
		case 150: TransformVertexAsRequired( sVertex, 150, curLF ); break;
		case 151: TransformVertexAsRequired( sVertex, 151, curLF ); break;
		case 152: TransformVertexAsRequired( sVertex, 152, curLF ); break;
		case 153: TransformVertexAsRequired( sVertex, 153, curLF ); break;
		case 154: TransformVertexAsRequired( sVertex, 154, curLF ); break;
		case 155: TransformVertexAsRequired( sVertex, 155, curLF ); break;
		case 156: TransformVertexAsRequired( sVertex, 156, curLF ); break;
		case 157: TransformVertexAsRequired( sVertex, 157, curLF ); break;
		case 158: TransformVertexAsRequired( sVertex, 158, curLF ); break;
		case 159: TransformVertexAsRequired( sVertex, 159, curLF ); break;
		case 160: TransformVertexAsRequired( sVertex, 160, curLF ); break;
		case 161: TransformVertexAsRequired( sVertex, 161, curLF ); break;
		case 162: TransformVertexAsRequired( sVertex, 162, curLF ); break;
		case 163: TransformVertexAsRequired( sVertex, 163, curLF ); break;
		case 164: TransformVertexAsRequired( sVertex, 164, curLF ); break;
		case 165: TransformVertexAsRequired( sVertex, 165, curLF ); break;
		case 166: TransformVertexAsRequired( sVertex, 166, curLF ); break;
		case 167: TransformVertexAsRequired( sVertex, 167, curLF ); break;
		case 168: TransformVertexAsRequired( sVertex, 168, curLF ); break;
		case 169: TransformVertexAsRequired( sVertex, 169, curLF ); break;
		case 170: TransformVertexAsRequired( sVertex, 170, curLF ); break;
		case 171: TransformVertexAsRequired( sVertex, 171, curLF ); break;
		case 172: TransformVertexAsRequired( sVertex, 172, curLF ); break;
		case 173: TransformVertexAsRequired( sVertex, 173, curLF ); break;
		case 174: TransformVertexAsRequired( sVertex, 174, curLF ); break;
		case 175: TransformVertexAsRequired( sVertex, 175, curLF ); break;
		case 176: TransformVertexAsRequired( sVertex, 176, curLF ); break;
		case 177: TransformVertexAsRequired( sVertex, 177, curLF ); break;
		case 178: TransformVertexAsRequired( sVertex, 178, curLF ); break;
		case 179: TransformVertexAsRequired( sVertex, 179, curLF ); break;
		case 180: TransformVertexAsRequired( sVertex, 180, curLF ); break;
		case 181: TransformVertexAsRequired( sVertex, 181, curLF ); break;
		case 182: TransformVertexAsRequired( sVertex, 182, curLF ); break;
		case 183: TransformVertexAsRequired( sVertex, 183, curLF ); break;
		case 184: TransformVertexAsRequired( sVertex, 184, curLF ); break;
		case 185: TransformVertexAsRequired( sVertex, 185, curLF ); break;
		case 186: TransformVertexAsRequired( sVertex, 186, curLF ); break;
		case 187: TransformVertexAsRequired( sVertex, 187, curLF ); break;
		case 188: TransformVertexAsRequired( sVertex, 188, curLF ); break;
		case 189: TransformVertexAsRequired( sVertex, 189, curLF ); break;
		case 190: TransformVertexAsRequired( sVertex, 190, curLF ); break;
		case 191: TransformVertexAsRequired( sVertex, 191, curLF ); break;
		case 192: TransformVertexAsRequired( sVertex, 192, curLF ); break;
		case 193: TransformVertexAsRequired( sVertex, 193, curLF ); break;
		case 194: TransformVertexAsRequired( sVertex, 194, curLF ); break;
		case 195: TransformVertexAsRequired( sVertex, 195, curLF ); break;
		case 196: TransformVertexAsRequired( sVertex, 196, curLF ); break;
		case 197: TransformVertexAsRequired( sVertex, 197, curLF ); break;
		case 198: TransformVertexAsRequired( sVertex, 198, curLF ); break;
		case 199: TransformVertexAsRequired( sVertex, 199, curLF ); break;
		case 200: TransformVertexAsRequired( sVertex, 200, curLF ); break;
		case 201: TransformVertexAsRequired( sVertex, 201, curLF ); break;
		case 202: TransformVertexAsRequired( sVertex, 202, curLF ); break;
		case 203: TransformVertexAsRequired( sVertex, 203, curLF ); break;
		case 204: TransformVertexAsRequired( sVertex, 204, curLF ); break;
		case 205: TransformVertexAsRequired( sVertex, 205, curLF ); break;
		case 206: TransformVertexAsRequired( sVertex, 206, curLF ); break;
		case 207: TransformVertexAsRequired( sVertex, 207, curLF ); break;
		case 208: TransformVertexAsRequired( sVertex, 208, curLF ); break;
		case 209: TransformVertexAsRequired( sVertex, 209, curLF ); break;
		case 210: TransformVertexAsRequired( sVertex, 210, curLF ); break;
		case 211: TransformVertexAsRequired( sVertex, 211, curLF ); break;
		case 212: TransformVertexAsRequired( sVertex, 212, curLF ); break;
		case 213: TransformVertexAsRequired( sVertex, 213, curLF ); break;
		case 214: TransformVertexAsRequired( sVertex, 214, curLF ); break;
		case 215: TransformVertexAsRequired( sVertex, 215, curLF ); break;
		case 216: TransformVertexAsRequired( sVertex, 216, curLF ); break;
		case 217: TransformVertexAsRequired( sVertex, 217, curLF ); break;
		case 218: TransformVertexAsRequired( sVertex, 218, curLF ); break;
		case 219: TransformVertexAsRequired( sVertex, 219, curLF ); break;
		case 220: TransformVertexAsRequired( sVertex, 220, curLF ); break;
		case 221: TransformVertexAsRequired( sVertex, 221, curLF ); break;
		case 222: TransformVertexAsRequired( sVertex, 222, curLF ); break;
		case 223: TransformVertexAsRequired( sVertex, 223, curLF ); break;
		case 224: TransformVertexAsRequired( sVertex, 224, curLF ); break;
		case 225: TransformVertexAsRequired( sVertex, 225, curLF ); break;
		case 226: TransformVertexAsRequired( sVertex, 226, curLF ); break;
		case 227: TransformVertexAsRequired( sVertex, 227, curLF ); break;
		case 228: TransformVertexAsRequired( sVertex, 228, curLF ); break;
		case 229: TransformVertexAsRequired( sVertex, 229, curLF ); break;
		case 230: TransformVertexAsRequired( sVertex, 230, curLF ); break;
		case 231: TransformVertexAsRequired( sVertex, 231, curLF ); break;
		case 232: TransformVertexAsRequired( sVertex, 232, curLF ); break;
		case 233: TransformVertexAsRequired( sVertex, 233, curLF ); break;
		case 234: TransformVertexAsRequired( sVertex, 234, curLF ); break;
		case 235: TransformVertexAsRequired( sVertex, 235, curLF ); break;
		case 236: TransformVertexAsRequired( sVertex, 236, curLF ); break;
		case 237: TransformVertexAsRequired( sVertex, 237, curLF ); break;
		case 238: TransformVertexAsRequired( sVertex, 238, curLF ); break;
		case 239: TransformVertexAsRequired( sVertex, 239, curLF ); break;
		case 240: TransformVertexAsRequired( sVertex, 240, curLF ); break;
		case 241: TransformVertexAsRequired( sVertex, 241, curLF ); break;
		case 242: TransformVertexAsRequired( sVertex, 242, curLF ); break;
		case 243: TransformVertexAsRequired( sVertex, 243, curLF ); break;
		case 244: TransformVertexAsRequired( sVertex, 244, curLF ); break;
		case 245: TransformVertexAsRequired( sVertex, 245, curLF ); break;
		case 246: TransformVertexAsRequired( sVertex, 246, curLF ); break;
		case 247: TransformVertexAsRequired( sVertex, 247, curLF ); break;
		case 248: TransformVertexAsRequired( sVertex, 248, curLF ); break;
		case 249: TransformVertexAsRequired( sVertex, 249, curLF ); break;
		case 250: TransformVertexAsRequired( sVertex, 250, curLF ); break;
		case 251: TransformVertexAsRequired( sVertex, 251, curLF ); break;
		case 252: TransformVertexAsRequired( sVertex, 252, curLF ); break;
		case 253: TransformVertexAsRequired( sVertex, 253, curLF ); break;
		case 254: TransformVertexAsRequired( sVertex, 254, curLF ); break;
		case 255: TransformVertexAsRequired( sVertex, 255, curLF ); break;
		case 256: TransformVertexAsRequired( sVertex, 256, curLF ); break;
		case 257: TransformVertexAsRequired( sVertex, 257, curLF ); break;
		case 258: TransformVertexAsRequired( sVertex, 258, curLF ); break;
		case 259: TransformVertexAsRequired( sVertex, 259, curLF ); break;
		case 260: TransformVertexAsRequired( sVertex, 260, curLF ); break;
		case 261: TransformVertexAsRequired( sVertex, 261, curLF ); break;
		case 262: TransformVertexAsRequired( sVertex, 262, curLF ); break;
		case 263: TransformVertexAsRequired( sVertex, 263, curLF ); break;
		case 264: TransformVertexAsRequired( sVertex, 264, curLF ); break;
		case 265: TransformVertexAsRequired( sVertex, 265, curLF ); break;
		case 266: TransformVertexAsRequired( sVertex, 266, curLF ); break;
		case 267: TransformVertexAsRequired( sVertex, 267, curLF ); break;
		case 268: TransformVertexAsRequired( sVertex, 268, curLF ); break;
		case 269: TransformVertexAsRequired( sVertex, 269, curLF ); break;
		case 270: TransformVertexAsRequired( sVertex, 270, curLF ); break;
		case 271: TransformVertexAsRequired( sVertex, 271, curLF ); break;
		case 272: TransformVertexAsRequired( sVertex, 272, curLF ); break;
		case 273: TransformVertexAsRequired( sVertex, 273, curLF ); break;
		case 274: TransformVertexAsRequired( sVertex, 274, curLF ); break;
		case 275: TransformVertexAsRequired( sVertex, 275, curLF ); break;
		case 276: TransformVertexAsRequired( sVertex, 276, curLF ); break;
		case 277: TransformVertexAsRequired( sVertex, 277, curLF ); break;
		case 278: TransformVertexAsRequired( sVertex, 278, curLF ); break;
		case 279: TransformVertexAsRequired( sVertex, 279, curLF ); break;
		case 280: TransformVertexAsRequired( sVertex, 280, curLF ); break;
		case 281: TransformVertexAsRequired( sVertex, 281, curLF ); break;
		case 282: TransformVertexAsRequired( sVertex, 282, curLF ); break;
		case 283: TransformVertexAsRequired( sVertex, 283, curLF ); break;
		case 284: TransformVertexAsRequired( sVertex, 284, curLF ); break;
		case 285: TransformVertexAsRequired( sVertex, 285, curLF ); break;
		case 286: TransformVertexAsRequired( sVertex, 286, curLF ); break;
		case 287: TransformVertexAsRequired( sVertex, 287, curLF ); break;
		case 288: TransformVertexAsRequired( sVertex, 288, curLF ); break;
		case 289: TransformVertexAsRequired( sVertex, 289, curLF ); break;
		case 290: TransformVertexAsRequired( sVertex, 290, curLF ); break;
		case 291: TransformVertexAsRequired( sVertex, 291, curLF ); break;
		case 292: TransformVertexAsRequired( sVertex, 292, curLF ); break;
		case 293: TransformVertexAsRequired( sVertex, 293, curLF ); break;
		case 294: TransformVertexAsRequired( sVertex, 294, curLF ); break;
		case 295: TransformVertexAsRequired( sVertex, 295, curLF ); break;
		case 296: TransformVertexAsRequired( sVertex, 296, curLF ); break;
		case 297: TransformVertexAsRequired( sVertex, 297, curLF ); break;
		case 298: TransformVertexAsRequired( sVertex, 298, curLF ); break;
		case 299: TransformVertexAsRequired( sVertex, 299, curLF ); break;
		case 300: TransformVertexAsRequired( sVertex, 300, curLF ); break;
		case 301: TransformVertexAsRequired( sVertex, 301, curLF ); break;
		case 302: TransformVertexAsRequired( sVertex, 302, curLF ); break;
		case 303: TransformVertexAsRequired( sVertex, 303, curLF ); break;
		case 304: TransformVertexAsRequired( sVertex, 304, curLF ); break;
		case 305: TransformVertexAsRequired( sVertex, 305, curLF ); break;
		case 306: TransformVertexAsRequired( sVertex, 306, curLF ); break;
		case 307: TransformVertexAsRequired( sVertex, 307, curLF ); break;
		case 308: TransformVertexAsRequired( sVertex, 308, curLF ); break;
		case 309: TransformVertexAsRequired( sVertex, 309, curLF ); break;
		case 310: TransformVertexAsRequired( sVertex, 310, curLF ); break;
		case 311: TransformVertexAsRequired( sVertex, 311, curLF ); break;
		case 312: TransformVertexAsRequired( sVertex, 312, curLF ); break;
		case 313: TransformVertexAsRequired( sVertex, 313, curLF ); break;
		case 314: TransformVertexAsRequired( sVertex, 314, curLF ); break;
		case 315: TransformVertexAsRequired( sVertex, 315, curLF ); break;
		case 316: TransformVertexAsRequired( sVertex, 316, curLF ); break;
		case 317: TransformVertexAsRequired( sVertex, 317, curLF ); break;
		case 318: TransformVertexAsRequired( sVertex, 318, curLF ); break;
		case 319: TransformVertexAsRequired( sVertex, 319, curLF ); break;
		case 320: TransformVertexAsRequired( sVertex, 320, curLF ); break;
		case 321: TransformVertexAsRequired( sVertex, 321, curLF ); break;
		case 322: TransformVertexAsRequired( sVertex, 322, curLF ); break;
		case 323: TransformVertexAsRequired( sVertex, 323, curLF ); break;
		case 324: TransformVertexAsRequired( sVertex, 324, curLF ); break;
		case 325: TransformVertexAsRequired( sVertex, 325, curLF ); break;
		case 326: TransformVertexAsRequired( sVertex, 326, curLF ); break;
		case 327: TransformVertexAsRequired( sVertex, 327, curLF ); break;
		case 328: TransformVertexAsRequired( sVertex, 328, curLF ); break;
		case 329: TransformVertexAsRequired( sVertex, 329, curLF ); break;
		case 330: TransformVertexAsRequired( sVertex, 330, curLF ); break;
		case 331: TransformVertexAsRequired( sVertex, 331, curLF ); break;
		case 332: TransformVertexAsRequired( sVertex, 332, curLF ); break;
		case 333: TransformVertexAsRequired( sVertex, 333, curLF ); break;
		case 334: TransformVertexAsRequired( sVertex, 334, curLF ); break;
		case 335: TransformVertexAsRequired( sVertex, 335, curLF ); break;
		case 336: TransformVertexAsRequired( sVertex, 336, curLF ); break;
		case 337: TransformVertexAsRequired( sVertex, 337, curLF ); break;
		case 338: TransformVertexAsRequired( sVertex, 338, curLF ); break;
		case 339: TransformVertexAsRequired( sVertex, 339, curLF ); break;
		case 340: TransformVertexAsRequired( sVertex, 340, curLF ); break;
		case 341: TransformVertexAsRequired( sVertex, 341, curLF ); break;
		case 342: TransformVertexAsRequired( sVertex, 342, curLF ); break;
		case 343: TransformVertexAsRequired( sVertex, 343, curLF ); break;
		case 344: TransformVertexAsRequired( sVertex, 344, curLF ); break;
		case 345: TransformVertexAsRequired( sVertex, 345, curLF ); break;
		case 346: TransformVertexAsRequired( sVertex, 346, curLF ); break;
		case 347: TransformVertexAsRequired( sVertex, 347, curLF ); break;
		case 348: TransformVertexAsRequired( sVertex, 348, curLF ); break;
		case 349: TransformVertexAsRequired( sVertex, 349, curLF ); break;
		case 350: TransformVertexAsRequired( sVertex, 350, curLF ); break;
		case 351: TransformVertexAsRequired( sVertex, 351, curLF ); break;
		case 352: TransformVertexAsRequired( sVertex, 352, curLF ); break;
		case 353: TransformVertexAsRequired( sVertex, 353, curLF ); break;
		case 354: TransformVertexAsRequired( sVertex, 354, curLF ); break;
		case 355: TransformVertexAsRequired( sVertex, 355, curLF ); break;
		case 356: TransformVertexAsRequired( sVertex, 356, curLF ); break;
		case 357: TransformVertexAsRequired( sVertex, 357, curLF ); break;
		case 358: TransformVertexAsRequired( sVertex, 358, curLF ); break;
		case 359: TransformVertexAsRequired( sVertex, 359, curLF ); break;
		case 360: TransformVertexAsRequired( sVertex, 360, curLF ); break;
		case 361: TransformVertexAsRequired( sVertex, 361, curLF ); break;
		case 362: TransformVertexAsRequired( sVertex, 362, curLF ); break;
		case 363: TransformVertexAsRequired( sVertex, 363, curLF ); break;
		case 364: TransformVertexAsRequired( sVertex, 364, curLF ); break;
		case 365: TransformVertexAsRequired( sVertex, 365, curLF ); break;
		case 366: TransformVertexAsRequired( sVertex, 366, curLF ); break;
		case 367: TransformVertexAsRequired( sVertex, 367, curLF ); break;
		case 368: TransformVertexAsRequired( sVertex, 368, curLF ); break;
		case 369: TransformVertexAsRequired( sVertex, 369, curLF ); break;
		case 370: TransformVertexAsRequired( sVertex, 370, curLF ); break;
		case 371: TransformVertexAsRequired( sVertex, 371, curLF ); break;
		case 372: TransformVertexAsRequired( sVertex, 372, curLF ); break;
		case 373: TransformVertexAsRequired( sVertex, 373, curLF ); break;
		case 374: TransformVertexAsRequired( sVertex, 374, curLF ); break;
		case 375: TransformVertexAsRequired( sVertex, 375, curLF ); break;
		case 376: TransformVertexAsRequired( sVertex, 376, curLF ); break;
		case 377: TransformVertexAsRequired( sVertex, 377, curLF ); break;
		case 378: TransformVertexAsRequired( sVertex, 378, curLF ); break;
		case 379: TransformVertexAsRequired( sVertex, 379, curLF ); break;
		case 380: TransformVertexAsRequired( sVertex, 380, curLF ); break;
		case 381: TransformVertexAsRequired( sVertex, 381, curLF ); break;
		case 382: TransformVertexAsRequired( sVertex, 382, curLF ); break;
		case 383: TransformVertexAsRequired( sVertex, 383, curLF ); break;
		case 384: TransformVertexAsRequired( sVertex, 384, curLF ); break;
		case 385: TransformVertexAsRequired( sVertex, 385, curLF ); break;
		case 386: TransformVertexAsRequired( sVertex, 386, curLF ); break;
		case 387: TransformVertexAsRequired( sVertex, 387, curLF ); break;
		case 388: TransformVertexAsRequired( sVertex, 388, curLF ); break;
		case 389: TransformVertexAsRequired( sVertex, 389, curLF ); break;
		case 390: TransformVertexAsRequired( sVertex, 390, curLF ); break;
		case 391: TransformVertexAsRequired( sVertex, 391, curLF ); break;
		case 392: TransformVertexAsRequired( sVertex, 392, curLF ); break;
		case 393: TransformVertexAsRequired( sVertex, 393, curLF ); break;
		case 394: TransformVertexAsRequired( sVertex, 394, curLF ); break;
		case 395: TransformVertexAsRequired( sVertex, 395, curLF ); break;
		case 396: TransformVertexAsRequired( sVertex, 396, curLF ); break;
		case 397: TransformVertexAsRequired( sVertex, 397, curLF ); break;
		case 398: TransformVertexAsRequired( sVertex, 398, curLF ); break;
		case 399: TransformVertexAsRequired( sVertex, 399, curLF ); break;
		case 400: TransformVertexAsRequired( sVertex, 400, curLF ); break;
		case 401: TransformVertexAsRequired( sVertex, 401, curLF ); break;
		case 402: TransformVertexAsRequired( sVertex, 402, curLF ); break;
		case 403: TransformVertexAsRequired( sVertex, 403, curLF ); break;
		case 404: TransformVertexAsRequired( sVertex, 404, curLF ); break;
		case 405: TransformVertexAsRequired( sVertex, 405, curLF ); break;
		case 406: TransformVertexAsRequired( sVertex, 406, curLF ); break;
		case 407: TransformVertexAsRequired( sVertex, 407, curLF ); break;
		case 408: TransformVertexAsRequired( sVertex, 408, curLF ); break;
		case 409: TransformVertexAsRequired( sVertex, 409, curLF ); break;
		case 410: TransformVertexAsRequired( sVertex, 410, curLF ); break;
		case 411: TransformVertexAsRequired( sVertex, 411, curLF ); break;
		case 412: TransformVertexAsRequired( sVertex, 412, curLF ); break;
		case 413: TransformVertexAsRequired( sVertex, 413, curLF ); break;
		case 414: TransformVertexAsRequired( sVertex, 414, curLF ); break;
		case 415: TransformVertexAsRequired( sVertex, 415, curLF ); break;
		case 416: TransformVertexAsRequired( sVertex, 416, curLF ); break;
		case 417: TransformVertexAsRequired( sVertex, 417, curLF ); break;
		case 418: TransformVertexAsRequired( sVertex, 418, curLF ); break;
		case 419: TransformVertexAsRequired( sVertex, 419, curLF ); break;
		case 420: TransformVertexAsRequired( sVertex, 420, curLF ); break;
		case 421: TransformVertexAsRequired( sVertex, 421, curLF ); break;
		case 422: TransformVertexAsRequired( sVertex, 422, curLF ); break;
		case 423: TransformVertexAsRequired( sVertex, 423, curLF ); break;
		case 424: TransformVertexAsRequired( sVertex, 424, curLF ); break;
		case 425: TransformVertexAsRequired( sVertex, 425, curLF ); break;
		case 426: TransformVertexAsRequired( sVertex, 426, curLF ); break;
		case 427: TransformVertexAsRequired( sVertex, 427, curLF ); break;
		case 428: TransformVertexAsRequired( sVertex, 428, curLF ); break;
		case 429: TransformVertexAsRequired( sVertex, 429, curLF ); break;
		case 430: TransformVertexAsRequired( sVertex, 430, curLF ); break;
		case 431: TransformVertexAsRequired( sVertex, 431, curLF ); break;
		case 432: TransformVertexAsRequired( sVertex, 432, curLF ); break;
		case 433: TransformVertexAsRequired( sVertex, 433, curLF ); break;
		case 434: TransformVertexAsRequired( sVertex, 434, curLF ); break;
		case 435: TransformVertexAsRequired( sVertex, 435, curLF ); break;
		case 436: TransformVertexAsRequired( sVertex, 436, curLF ); break;
		case 437: TransformVertexAsRequired( sVertex, 437, curLF ); break;
		case 438: TransformVertexAsRequired( sVertex, 438, curLF ); break;
		case 439: TransformVertexAsRequired( sVertex, 439, curLF ); break;
		case 440: TransformVertexAsRequired( sVertex, 440, curLF ); break;
		case 441: TransformVertexAsRequired( sVertex, 441, curLF ); break;
		case 442: TransformVertexAsRequired( sVertex, 442, curLF ); break;
		case 443: TransformVertexAsRequired( sVertex, 443, curLF ); break;
		case 444: TransformVertexAsRequired( sVertex, 444, curLF ); break;
		case 445: TransformVertexAsRequired( sVertex, 445, curLF ); break;
		case 446: TransformVertexAsRequired( sVertex, 446, curLF ); break;
		case 447: TransformVertexAsRequired( sVertex, 447, curLF ); break;
		case 448: TransformVertexAsRequired( sVertex, 448, curLF ); break;
		case 449: TransformVertexAsRequired( sVertex, 449, curLF ); break;
		case 450: TransformVertexAsRequired( sVertex, 450, curLF ); break;
		case 451: TransformVertexAsRequired( sVertex, 451, curLF ); break;
		case 452: TransformVertexAsRequired( sVertex, 452, curLF ); break;
		case 453: TransformVertexAsRequired( sVertex, 453, curLF ); break;
		case 454: TransformVertexAsRequired( sVertex, 454, curLF ); break;
		case 455: TransformVertexAsRequired( sVertex, 455, curLF ); break;
		case 456: TransformVertexAsRequired( sVertex, 456, curLF ); break;
		case 457: TransformVertexAsRequired( sVertex, 457, curLF ); break;
		case 458: TransformVertexAsRequired( sVertex, 458, curLF ); break;
		case 459: TransformVertexAsRequired( sVertex, 459, curLF ); break;
		case 460: TransformVertexAsRequired( sVertex, 460, curLF ); break;
		case 461: TransformVertexAsRequired( sVertex, 461, curLF ); break;
		case 462: TransformVertexAsRequired( sVertex, 462, curLF ); break;
		case 463: TransformVertexAsRequired( sVertex, 463, curLF ); break;
		case 464: TransformVertexAsRequired( sVertex, 464, curLF ); break;
		case 465: TransformVertexAsRequired( sVertex, 465, curLF ); break;
		case 466: TransformVertexAsRequired( sVertex, 466, curLF ); break;
		case 467: TransformVertexAsRequired( sVertex, 467, curLF ); break;
		case 468: TransformVertexAsRequired( sVertex, 468, curLF ); break;
		case 469: TransformVertexAsRequired( sVertex, 469, curLF ); break;
		case 470: TransformVertexAsRequired( sVertex, 470, curLF ); break;
		case 471: TransformVertexAsRequired( sVertex, 471, curLF ); break;
		case 472: TransformVertexAsRequired( sVertex, 472, curLF ); break;
		case 473: TransformVertexAsRequired( sVertex, 473, curLF ); break;
		case 474: TransformVertexAsRequired( sVertex, 474, curLF ); break;
		case 475: TransformVertexAsRequired( sVertex, 475, curLF ); break;
		case 476: TransformVertexAsRequired( sVertex, 476, curLF ); break;
		case 477: TransformVertexAsRequired( sVertex, 477, curLF ); break;
		case 478: TransformVertexAsRequired( sVertex, 478, curLF ); break;
		case 479: TransformVertexAsRequired( sVertex, 479, curLF ); break;
		case 480: TransformVertexAsRequired( sVertex, 480, curLF ); break;
		case 481: TransformVertexAsRequired( sVertex, 481, curLF ); break;
		case 482: TransformVertexAsRequired( sVertex, 482, curLF ); break;
		case 483: TransformVertexAsRequired( sVertex, 483, curLF ); break;
		case 484: TransformVertexAsRequired( sVertex, 484, curLF ); break;
		case 485: TransformVertexAsRequired( sVertex, 485, curLF ); break;
		case 486: TransformVertexAsRequired( sVertex, 486, curLF ); break;
		case 487: TransformVertexAsRequired( sVertex, 487, curLF ); break;
		case 488: TransformVertexAsRequired( sVertex, 488, curLF ); break;
		case 489: TransformVertexAsRequired( sVertex, 489, curLF ); break;
		case 490: TransformVertexAsRequired( sVertex, 490, curLF ); break;
		case 491: TransformVertexAsRequired( sVertex, 491, curLF ); break;
		case 492: TransformVertexAsRequired( sVertex, 492, curLF ); break;
		case 493: TransformVertexAsRequired( sVertex, 493, curLF ); break;
		case 494: TransformVertexAsRequired( sVertex, 494, curLF ); break;
		case 495: TransformVertexAsRequired( sVertex, 495, curLF ); break;
		case 496: TransformVertexAsRequired( sVertex, 496, curLF ); break;
		case 497: TransformVertexAsRequired( sVertex, 497, curLF ); break;
		case 498: TransformVertexAsRequired( sVertex, 498, curLF ); break;
		case 499: TransformVertexAsRequired( sVertex, 499, curLF ); break;
		case 500: TransformVertexAsRequired( sVertex, 500, curLF ); break;
		case 501: TransformVertexAsRequired( sVertex, 501, curLF ); break;
		case 502: TransformVertexAsRequired( sVertex, 502, curLF ); break;
		case 503: TransformVertexAsRequired( sVertex, 503, curLF ); break;
		case 504: TransformVertexAsRequired( sVertex, 504, curLF ); break;
		case 505: TransformVertexAsRequired( sVertex, 505, curLF ); break;
		case 506: TransformVertexAsRequired( sVertex, 506, curLF ); break;
		case 507: TransformVertexAsRequired( sVertex, 507, curLF ); break;
		case 508: TransformVertexAsRequired( sVertex, 508, curLF ); break;
		case 509: TransformVertexAsRequired( sVertex, 509, curLF ); break;
		case 510: TransformVertexAsRequired( sVertex, 510, curLF ); break;
		case 511: TransformVertexAsRequired( sVertex, 511, curLF ); break;
//DeadCode JON 30Oct00 		case 512: TransformVertexAsRequired( sVertex, 512, curLF ); break;
//DeadCode JON 30Oct00 		case 513: TransformVertexAsRequired( sVertex, 513, curLF ); break;
//DeadCode JON 30Oct00 		case 514: TransformVertexAsRequired( sVertex, 514, curLF ); break;
//DeadCode JON 30Oct00 		case 515: TransformVertexAsRequired( sVertex, 515, curLF ); break;
//DeadCode JON 30Oct00 		case 516: TransformVertexAsRequired( sVertex, 516, curLF ); break;
//DeadCode JON 30Oct00 		case 517: TransformVertexAsRequired( sVertex, 517, curLF ); break;
//DeadCode JON 30Oct00 		case 518: TransformVertexAsRequired( sVertex, 518, curLF ); break;
//DeadCode JON 30Oct00 		case 519: TransformVertexAsRequired( sVertex, 519, curLF ); break;
//DeadCode JON 30Oct00 		case 520: TransformVertexAsRequired( sVertex, 520, curLF ); break;
//DeadCode JON 30Oct00 		case 521: TransformVertexAsRequired( sVertex, 521, curLF ); break;
//DeadCode JON 30Oct00 		case 522: TransformVertexAsRequired( sVertex, 522, curLF ); break;
//DeadCode JON 30Oct00 		case 523: TransformVertexAsRequired( sVertex, 523, curLF ); break;
//DeadCode JON 30Oct00 		case 524: TransformVertexAsRequired( sVertex, 524, curLF ); break;
//DeadCode JON 30Oct00 		case 525: TransformVertexAsRequired( sVertex, 525, curLF ); break;
//DeadCode JON 30Oct00 		case 526: TransformVertexAsRequired( sVertex, 526, curLF ); break;
//DeadCode JON 30Oct00 		case 527: TransformVertexAsRequired( sVertex, 527, curLF ); break;
//DeadCode JON 30Oct00 		case 528: TransformVertexAsRequired( sVertex, 528, curLF ); break;
//DeadCode JON 30Oct00 		case 529: TransformVertexAsRequired( sVertex, 529, curLF ); break;
//DeadCode JON 30Oct00 		case 530: TransformVertexAsRequired( sVertex, 530, curLF ); break;
//DeadCode JON 30Oct00 		case 531: TransformVertexAsRequired( sVertex, 531, curLF ); break;
//DeadCode JON 30Oct00 		case 532: TransformVertexAsRequired( sVertex, 532, curLF ); break;
//DeadCode JON 30Oct00 		case 533: TransformVertexAsRequired( sVertex, 533, curLF ); break;
//DeadCode JON 30Oct00 		case 534: TransformVertexAsRequired( sVertex, 534, curLF ); break;
//DeadCode JON 30Oct00 		case 535: TransformVertexAsRequired( sVertex, 535, curLF ); break;
//DeadCode JON 30Oct00 		case 536: TransformVertexAsRequired( sVertex, 536, curLF ); break;
//DeadCode JON 30Oct00 		case 537: TransformVertexAsRequired( sVertex, 537, curLF ); break;
//DeadCode JON 30Oct00 		case 538: TransformVertexAsRequired( sVertex, 538, curLF ); break;
//DeadCode JON 30Oct00 		case 539: TransformVertexAsRequired( sVertex, 539, curLF ); break;
//DeadCode JON 30Oct00 		case 540: TransformVertexAsRequired( sVertex, 540, curLF ); break;
//DeadCode JON 30Oct00 		case 541: TransformVertexAsRequired( sVertex, 541, curLF ); break;
//DeadCode JON 30Oct00 		case 542: TransformVertexAsRequired( sVertex, 542, curLF ); break;
//DeadCode JON 30Oct00 		case 543: TransformVertexAsRequired( sVertex, 543, curLF ); break;
//DeadCode JON 30Oct00 		case 544: TransformVertexAsRequired( sVertex, 544, curLF ); break;
//DeadCode JON 30Oct00 		case 545: TransformVertexAsRequired( sVertex, 545, curLF ); break;
//DeadCode JON 30Oct00 		case 546: TransformVertexAsRequired( sVertex, 546, curLF ); break;
//DeadCode JON 30Oct00 		case 547: TransformVertexAsRequired( sVertex, 547, curLF ); break;
//DeadCode JON 30Oct00 		case 548: TransformVertexAsRequired( sVertex, 548, curLF ); break;
//DeadCode JON 30Oct00 		case 549: TransformVertexAsRequired( sVertex, 549, curLF ); break;
//DeadCode JON 30Oct00 		case 550: TransformVertexAsRequired( sVertex, 550, curLF ); break;
//DeadCode JON 30Oct00 		case 551: TransformVertexAsRequired( sVertex, 551, curLF ); break;
//DeadCode JON 30Oct00 		case 552: TransformVertexAsRequired( sVertex, 552, curLF ); break;
//DeadCode JON 30Oct00 		case 553: TransformVertexAsRequired( sVertex, 553, curLF ); break;
//DeadCode JON 30Oct00 		case 554: TransformVertexAsRequired( sVertex, 554, curLF ); break;
//DeadCode JON 30Oct00 		case 555: TransformVertexAsRequired( sVertex, 555, curLF ); break;
//DeadCode JON 30Oct00 		case 556: TransformVertexAsRequired( sVertex, 556, curLF ); break;
//DeadCode JON 30Oct00 		case 557: TransformVertexAsRequired( sVertex, 557, curLF ); break;
//DeadCode JON 30Oct00 		case 558: TransformVertexAsRequired( sVertex, 558, curLF ); break;
//DeadCode JON 30Oct00 		case 559: TransformVertexAsRequired( sVertex, 559, curLF ); break;
//DeadCode JON 30Oct00 		case 560: TransformVertexAsRequired( sVertex, 560, curLF ); break;
//DeadCode JON 30Oct00 		case 561: TransformVertexAsRequired( sVertex, 561, curLF ); break;
//DeadCode JON 30Oct00 		case 562: TransformVertexAsRequired( sVertex, 562, curLF ); break;
//DeadCode JON 30Oct00 		case 563: TransformVertexAsRequired( sVertex, 563, curLF ); break;
//DeadCode JON 30Oct00 		case 564: TransformVertexAsRequired( sVertex, 564, curLF ); break;
//DeadCode JON 30Oct00 		case 565: TransformVertexAsRequired( sVertex, 565, curLF ); break;
//DeadCode JON 30Oct00 		case 566: TransformVertexAsRequired( sVertex, 566, curLF ); break;
//DeadCode JON 30Oct00 		case 567: TransformVertexAsRequired( sVertex, 567, curLF ); break;
//DeadCode JON 30Oct00 		case 568: TransformVertexAsRequired( sVertex, 568, curLF ); break;
//DeadCode JON 30Oct00 		case 569: TransformVertexAsRequired( sVertex, 569, curLF ); break;
//DeadCode JON 30Oct00 		case 570: TransformVertexAsRequired( sVertex, 570, curLF ); break;
//DeadCode JON 30Oct00 		case 571: TransformVertexAsRequired( sVertex, 571, curLF ); break;
//DeadCode JON 30Oct00 		case 572: TransformVertexAsRequired( sVertex, 572, curLF ); break;
//DeadCode JON 30Oct00 		case 573: TransformVertexAsRequired( sVertex, 573, curLF ); break;
//DeadCode JON 30Oct00 		case 574: TransformVertexAsRequired( sVertex, 574, curLF ); break;
//DeadCode JON 30Oct00 		case 575: TransformVertexAsRequired( sVertex, 575, curLF ); break;
//DeadCode JON 30Oct00 		case 576: TransformVertexAsRequired( sVertex, 576, curLF ); break;
//DeadCode JON 30Oct00 		case 577: TransformVertexAsRequired( sVertex, 577, curLF ); break;
//DeadCode JON 30Oct00 		case 578: TransformVertexAsRequired( sVertex, 578, curLF ); break;
//DeadCode JON 30Oct00 		case 579: TransformVertexAsRequired( sVertex, 579, curLF ); break;
//DeadCode JON 30Oct00 		case 580: TransformVertexAsRequired( sVertex, 580, curLF ); break;
//DeadCode JON 30Oct00 		case 581: TransformVertexAsRequired( sVertex, 581, curLF ); break;
//DeadCode JON 30Oct00 		case 582: TransformVertexAsRequired( sVertex, 582, curLF ); break;
//DeadCode JON 30Oct00 		case 583: TransformVertexAsRequired( sVertex, 583, curLF ); break;
//DeadCode JON 30Oct00 		case 584: TransformVertexAsRequired( sVertex, 584, curLF ); break;
//DeadCode JON 30Oct00 		case 585: TransformVertexAsRequired( sVertex, 585, curLF ); break;
//DeadCode JON 30Oct00 		case 586: TransformVertexAsRequired( sVertex, 586, curLF ); break;
//DeadCode JON 30Oct00 		case 587: TransformVertexAsRequired( sVertex, 587, curLF ); break;
//DeadCode JON 30Oct00 		case 588: TransformVertexAsRequired( sVertex, 588, curLF ); break;
//DeadCode JON 30Oct00 		case 589: TransformVertexAsRequired( sVertex, 589, curLF ); break;
//DeadCode JON 30Oct00 		case 590: TransformVertexAsRequired( sVertex, 590, curLF ); break;
//DeadCode JON 30Oct00 		case 591: TransformVertexAsRequired( sVertex, 591, curLF ); break;
//DeadCode JON 30Oct00 		case 592: TransformVertexAsRequired( sVertex, 592, curLF ); break;
//DeadCode JON 30Oct00 		case 593: TransformVertexAsRequired( sVertex, 593, curLF ); break;
//DeadCode JON 30Oct00 		case 594: TransformVertexAsRequired( sVertex, 594, curLF ); break;
//DeadCode JON 30Oct00 		case 595: TransformVertexAsRequired( sVertex, 595, curLF ); break;
//DeadCode JON 30Oct00 		case 596: TransformVertexAsRequired( sVertex, 596, curLF ); break;
//DeadCode JON 30Oct00 		case 597: TransformVertexAsRequired( sVertex, 597, curLF ); break;
//DeadCode JON 30Oct00 		case 598: TransformVertexAsRequired( sVertex, 598, curLF ); break;
//DeadCode JON 30Oct00 		case 599: TransformVertexAsRequired( sVertex, 599, curLF ); break;
//DeadCode JON 30Oct00 		case 600: TransformVertexAsRequired( sVertex, 600, curLF ); break;
//DeadCode JON 30Oct00 		case 601: TransformVertexAsRequired( sVertex, 601, curLF ); break;
//DeadCode JON 30Oct00 		case 602: TransformVertexAsRequired( sVertex, 602, curLF ); break;
//DeadCode JON 30Oct00 		case 603: TransformVertexAsRequired( sVertex, 603, curLF ); break;
//DeadCode JON 30Oct00 		case 604: TransformVertexAsRequired( sVertex, 604, curLF ); break;
//DeadCode JON 30Oct00 		case 605: TransformVertexAsRequired( sVertex, 605, curLF ); break;
//DeadCode JON 30Oct00 		case 606: TransformVertexAsRequired( sVertex, 606, curLF ); break;
//DeadCode JON 30Oct00 		case 607: TransformVertexAsRequired( sVertex, 607, curLF ); break;
//DeadCode JON 30Oct00 		case 608: TransformVertexAsRequired( sVertex, 608, curLF ); break;
//DeadCode JON 30Oct00 		case 609: TransformVertexAsRequired( sVertex, 609, curLF ); break;
//DeadCode JON 30Oct00 		case 610: TransformVertexAsRequired( sVertex, 610, curLF ); break;
//DeadCode JON 30Oct00 		case 611: TransformVertexAsRequired( sVertex, 611, curLF ); break;
//DeadCode JON 30Oct00 		case 612: TransformVertexAsRequired( sVertex, 612, curLF ); break;
//DeadCode JON 30Oct00 		case 613: TransformVertexAsRequired( sVertex, 613, curLF ); break;
//DeadCode JON 30Oct00 		case 614: TransformVertexAsRequired( sVertex, 614, curLF ); break;
//DeadCode JON 30Oct00 		case 615: TransformVertexAsRequired( sVertex, 615, curLF ); break;
//DeadCode JON 30Oct00 		case 616: TransformVertexAsRequired( sVertex, 616, curLF ); break;
//DeadCode JON 30Oct00 		case 617: TransformVertexAsRequired( sVertex, 617, curLF ); break;
//DeadCode JON 30Oct00 		case 618: TransformVertexAsRequired( sVertex, 618, curLF ); break;
//DeadCode JON 30Oct00 		case 619: TransformVertexAsRequired( sVertex, 619, curLF ); break;
//DeadCode JON 30Oct00 		case 620: TransformVertexAsRequired( sVertex, 620, curLF ); break;
//DeadCode JON 30Oct00 		case 621: TransformVertexAsRequired( sVertex, 621, curLF ); break;
//DeadCode JON 30Oct00 		case 622: TransformVertexAsRequired( sVertex, 622, curLF ); break;
//DeadCode JON 30Oct00 		case 623: TransformVertexAsRequired( sVertex, 623, curLF ); break;
//DeadCode JON 30Oct00 		case 624: TransformVertexAsRequired( sVertex, 624, curLF ); break;
//DeadCode JON 30Oct00 		case 625: TransformVertexAsRequired( sVertex, 625, curLF ); break;
//DeadCode JON 30Oct00 		case 626: TransformVertexAsRequired( sVertex, 626, curLF ); break;
//DeadCode JON 30Oct00 		case 627: TransformVertexAsRequired( sVertex, 627, curLF ); break;
//DeadCode JON 30Oct00 		case 628: TransformVertexAsRequired( sVertex, 628, curLF ); break;
//DeadCode JON 30Oct00 		case 629: TransformVertexAsRequired( sVertex, 629, curLF ); break;
//DeadCode JON 30Oct00 		case 630: TransformVertexAsRequired( sVertex, 630, curLF ); break;
//DeadCode JON 30Oct00 		case 631: TransformVertexAsRequired( sVertex, 631, curLF ); break;
//DeadCode JON 30Oct00 		case 632: TransformVertexAsRequired( sVertex, 632, curLF ); break;
//DeadCode JON 30Oct00 		case 633: TransformVertexAsRequired( sVertex, 633, curLF ); break;
//DeadCode JON 30Oct00 		case 634: TransformVertexAsRequired( sVertex, 634, curLF ); break;
//DeadCode JON 30Oct00 		case 635: TransformVertexAsRequired( sVertex, 635, curLF ); break;
//DeadCode JON 30Oct00 		case 636: TransformVertexAsRequired( sVertex, 636, curLF ); break;
//DeadCode JON 30Oct00 		case 637: TransformVertexAsRequired( sVertex, 637, curLF ); break;
//DeadCode JON 30Oct00 		case 638: TransformVertexAsRequired( sVertex, 638, curLF ); break;
//DeadCode JON 30Oct00 		case 639: TransformVertexAsRequired( sVertex, 639, curLF ); break;
//DeadCode JON 30Oct00 		case 640: TransformVertexAsRequired( sVertex, 640, curLF ); break;
//DeadCode JON 30Oct00 		case 641: TransformVertexAsRequired( sVertex, 641, curLF ); break;
//DeadCode JON 30Oct00 		case 642: TransformVertexAsRequired( sVertex, 642, curLF ); break;
//DeadCode JON 30Oct00 		case 643: TransformVertexAsRequired( sVertex, 643, curLF ); break;
//DeadCode JON 30Oct00 		case 644: TransformVertexAsRequired( sVertex, 644, curLF ); break;
//DeadCode JON 30Oct00 		case 645: TransformVertexAsRequired( sVertex, 645, curLF ); break;
//DeadCode JON 30Oct00 		case 646: TransformVertexAsRequired( sVertex, 646, curLF ); break;
//DeadCode JON 30Oct00 		case 647: TransformVertexAsRequired( sVertex, 647, curLF ); break;
//DeadCode JON 30Oct00 		case 648: TransformVertexAsRequired( sVertex, 648, curLF ); break;
//DeadCode JON 30Oct00 		case 649: TransformVertexAsRequired( sVertex, 649, curLF ); break;
//DeadCode JON 30Oct00 		case 650: TransformVertexAsRequired( sVertex, 650, curLF ); break;
//DeadCode JON 30Oct00 		case 651: TransformVertexAsRequired( sVertex, 651, curLF ); break;
//DeadCode JON 30Oct00 		case 652: TransformVertexAsRequired( sVertex, 652, curLF ); break;
//DeadCode JON 30Oct00 		case 653: TransformVertexAsRequired( sVertex, 653, curLF ); break;
//DeadCode JON 30Oct00 		case 654: TransformVertexAsRequired( sVertex, 654, curLF ); break;
//DeadCode JON 30Oct00 		case 655: TransformVertexAsRequired( sVertex, 655, curLF ); break;
//DeadCode JON 30Oct00 		case 656: TransformVertexAsRequired( sVertex, 656, curLF ); break;
//DeadCode JON 30Oct00 		case 657: TransformVertexAsRequired( sVertex, 657, curLF ); break;
//DeadCode JON 30Oct00 		case 658: TransformVertexAsRequired( sVertex, 658, curLF ); break;
//DeadCode JON 30Oct00 		case 659: TransformVertexAsRequired( sVertex, 659, curLF ); break;
//DeadCode JON 30Oct00 		case 660: TransformVertexAsRequired( sVertex, 660, curLF ); break;
//DeadCode JON 30Oct00 		case 661: TransformVertexAsRequired( sVertex, 661, curLF ); break;
//DeadCode JON 30Oct00 		case 662: TransformVertexAsRequired( sVertex, 662, curLF ); break;
//DeadCode JON 30Oct00 		case 663: TransformVertexAsRequired( sVertex, 663, curLF ); break;
//DeadCode JON 30Oct00 		case 664: TransformVertexAsRequired( sVertex, 664, curLF ); break;
//DeadCode JON 30Oct00 		case 665: TransformVertexAsRequired( sVertex, 665, curLF ); break;
//DeadCode JON 30Oct00 		case 666: TransformVertexAsRequired( sVertex, 666, curLF ); break;
//DeadCode JON 30Oct00 		case 667: TransformVertexAsRequired( sVertex, 667, curLF ); break;
//DeadCode JON 30Oct00 		case 668: TransformVertexAsRequired( sVertex, 668, curLF ); break;
//DeadCode JON 30Oct00 		case 669: TransformVertexAsRequired( sVertex, 669, curLF ); break;
//DeadCode JON 30Oct00 		case 670: TransformVertexAsRequired( sVertex, 670, curLF ); break;
//DeadCode JON 30Oct00 		case 671: TransformVertexAsRequired( sVertex, 671, curLF ); break;
//DeadCode JON 30Oct00 		case 672: TransformVertexAsRequired( sVertex, 672, curLF ); break;
//DeadCode JON 30Oct00 		case 673: TransformVertexAsRequired( sVertex, 673, curLF ); break;
//DeadCode JON 30Oct00 		case 674: TransformVertexAsRequired( sVertex, 674, curLF ); break;
//DeadCode JON 30Oct00 		case 675: TransformVertexAsRequired( sVertex, 675, curLF ); break;
//DeadCode JON 30Oct00 		case 676: TransformVertexAsRequired( sVertex, 676, curLF ); break;
//DeadCode JON 30Oct00 		case 677: TransformVertexAsRequired( sVertex, 677, curLF ); break;
//DeadCode JON 30Oct00 		case 678: TransformVertexAsRequired( sVertex, 678, curLF ); break;
//DeadCode JON 30Oct00 		case 679: TransformVertexAsRequired( sVertex, 679, curLF ); break;
//DeadCode JON 30Oct00 		case 680: TransformVertexAsRequired( sVertex, 680, curLF ); break;
//DeadCode JON 30Oct00 		case 681: TransformVertexAsRequired( sVertex, 681, curLF ); break;
//DeadCode JON 30Oct00 		case 682: TransformVertexAsRequired( sVertex, 682, curLF ); break;
//DeadCode JON 30Oct00 		case 683: TransformVertexAsRequired( sVertex, 683, curLF ); break;
//DeadCode JON 30Oct00 		case 684: TransformVertexAsRequired( sVertex, 684, curLF ); break;
//DeadCode JON 30Oct00 		case 685: TransformVertexAsRequired( sVertex, 685, curLF ); break;
//DeadCode JON 30Oct00 		case 686: TransformVertexAsRequired( sVertex, 686, curLF ); break;
//DeadCode JON 30Oct00 		case 687: TransformVertexAsRequired( sVertex, 687, curLF ); break;
//DeadCode JON 30Oct00 		case 688: TransformVertexAsRequired( sVertex, 688, curLF ); break;
//DeadCode JON 30Oct00 		case 689: TransformVertexAsRequired( sVertex, 689, curLF ); break;
//DeadCode JON 30Oct00 		case 690: TransformVertexAsRequired( sVertex, 690, curLF ); break;
//DeadCode JON 30Oct00 		case 691: TransformVertexAsRequired( sVertex, 691, curLF ); break;
//DeadCode JON 30Oct00 		case 692: TransformVertexAsRequired( sVertex, 692, curLF ); break;
//DeadCode JON 30Oct00 		case 693: TransformVertexAsRequired( sVertex, 693, curLF ); break;
//DeadCode JON 30Oct00 		case 694: TransformVertexAsRequired( sVertex, 694, curLF ); break;
//DeadCode JON 30Oct00 		case 695: TransformVertexAsRequired( sVertex, 695, curLF ); break;
//DeadCode JON 30Oct00 		case 696: TransformVertexAsRequired( sVertex, 696, curLF ); break;
//DeadCode JON 30Oct00 		case 697: TransformVertexAsRequired( sVertex, 697, curLF ); break;
//DeadCode JON 30Oct00 		case 698: TransformVertexAsRequired( sVertex, 698, curLF ); break;
//DeadCode JON 30Oct00 		case 699: TransformVertexAsRequired( sVertex, 699, curLF ); break;
//DeadCode JON 30Oct00 		case 700: TransformVertexAsRequired( sVertex, 700, curLF ); break;
//DeadCode JON 30Oct00 		case 701: TransformVertexAsRequired( sVertex, 701, curLF ); break;
//DeadCode JON 30Oct00 		case 702: TransformVertexAsRequired( sVertex, 702, curLF ); break;
//DeadCode JON 30Oct00 		case 703: TransformVertexAsRequired( sVertex, 703, curLF ); break;
//DeadCode JON 30Oct00 		case 704: TransformVertexAsRequired( sVertex, 704, curLF ); break;
//DeadCode JON 30Oct00 		case 705: TransformVertexAsRequired( sVertex, 705, curLF ); break;
//DeadCode JON 30Oct00 		case 706: TransformVertexAsRequired( sVertex, 706, curLF ); break;
//DeadCode JON 30Oct00 		case 707: TransformVertexAsRequired( sVertex, 707, curLF ); break;
//DeadCode JON 30Oct00 		case 708: TransformVertexAsRequired( sVertex, 708, curLF ); break;
//DeadCode JON 30Oct00 		case 709: TransformVertexAsRequired( sVertex, 709, curLF ); break;
//DeadCode JON 30Oct00 		case 710: TransformVertexAsRequired( sVertex, 710, curLF ); break;
//DeadCode JON 30Oct00 		case 711: TransformVertexAsRequired( sVertex, 711, curLF ); break;
//DeadCode JON 30Oct00 		case 712: TransformVertexAsRequired( sVertex, 712, curLF ); break;
//DeadCode JON 30Oct00 		case 713: TransformVertexAsRequired( sVertex, 713, curLF ); break;
//DeadCode JON 30Oct00 		case 714: TransformVertexAsRequired( sVertex, 714, curLF ); break;
//DeadCode JON 30Oct00 		case 715: TransformVertexAsRequired( sVertex, 715, curLF ); break;
//DeadCode JON 30Oct00 		case 716: TransformVertexAsRequired( sVertex, 716, curLF ); break;
//DeadCode JON 30Oct00 		case 717: TransformVertexAsRequired( sVertex, 717, curLF ); break;
//DeadCode JON 30Oct00 		case 718: TransformVertexAsRequired( sVertex, 718, curLF ); break;
//DeadCode JON 30Oct00 		case 719: TransformVertexAsRequired( sVertex, 719, curLF ); break;
//DeadCode JON 30Oct00 		case 720: TransformVertexAsRequired( sVertex, 720, curLF ); break;
//DeadCode JON 30Oct00 		case 721: TransformVertexAsRequired( sVertex, 721, curLF ); break;
//DeadCode JON 30Oct00 		case 722: TransformVertexAsRequired( sVertex, 722, curLF ); break;
//DeadCode JON 30Oct00 		case 723: TransformVertexAsRequired( sVertex, 723, curLF ); break;
//DeadCode JON 30Oct00 		case 724: TransformVertexAsRequired( sVertex, 724, curLF ); break;
//DeadCode JON 30Oct00 		case 725: TransformVertexAsRequired( sVertex, 725, curLF ); break;
//DeadCode JON 30Oct00 		case 726: TransformVertexAsRequired( sVertex, 726, curLF ); break;
//DeadCode JON 30Oct00 		case 727: TransformVertexAsRequired( sVertex, 727, curLF ); break;
//DeadCode JON 30Oct00 		case 728: TransformVertexAsRequired( sVertex, 728, curLF ); break;
//DeadCode JON 30Oct00 		case 729: TransformVertexAsRequired( sVertex, 729, curLF ); break;
//DeadCode JON 30Oct00 		case 730: TransformVertexAsRequired( sVertex, 730, curLF ); break;
//DeadCode JON 30Oct00 		case 731: TransformVertexAsRequired( sVertex, 731, curLF ); break;
//DeadCode JON 30Oct00 		case 732: TransformVertexAsRequired( sVertex, 732, curLF ); break;
//DeadCode JON 30Oct00 		case 733: TransformVertexAsRequired( sVertex, 733, curLF ); break;
//DeadCode JON 30Oct00 		case 734: TransformVertexAsRequired( sVertex, 734, curLF ); break;
//DeadCode JON 30Oct00 		case 735: TransformVertexAsRequired( sVertex, 735, curLF ); break;
//DeadCode JON 30Oct00 		case 736: TransformVertexAsRequired( sVertex, 736, curLF ); break;
//DeadCode JON 30Oct00 		case 737: TransformVertexAsRequired( sVertex, 737, curLF ); break;
//DeadCode JON 30Oct00 		case 738: TransformVertexAsRequired( sVertex, 738, curLF ); break;
//DeadCode JON 30Oct00 		case 739: TransformVertexAsRequired( sVertex, 739, curLF ); break;
//DeadCode JON 30Oct00 		case 740: TransformVertexAsRequired( sVertex, 740, curLF ); break;
//DeadCode JON 30Oct00 		case 741: TransformVertexAsRequired( sVertex, 741, curLF ); break;
//DeadCode JON 30Oct00 		case 742: TransformVertexAsRequired( sVertex, 742, curLF ); break;
//DeadCode JON 30Oct00 		case 743: TransformVertexAsRequired( sVertex, 743, curLF ); break;
//DeadCode JON 30Oct00 		case 744: TransformVertexAsRequired( sVertex, 744, curLF ); break;
//DeadCode JON 30Oct00 		case 745: TransformVertexAsRequired( sVertex, 745, curLF ); break;
//DeadCode JON 30Oct00 		case 746: TransformVertexAsRequired( sVertex, 746, curLF ); break;
//DeadCode JON 30Oct00 		case 747: TransformVertexAsRequired( sVertex, 747, curLF ); break;
//DeadCode JON 30Oct00 		case 748: TransformVertexAsRequired( sVertex, 748, curLF ); break;
//DeadCode JON 30Oct00 		case 749: TransformVertexAsRequired( sVertex, 749, curLF ); break;
//DeadCode JON 30Oct00 		case 750: TransformVertexAsRequired( sVertex, 750, curLF ); break;
//DeadCode JON 30Oct00 		case 751: TransformVertexAsRequired( sVertex, 751, curLF ); break;
//DeadCode JON 30Oct00 		case 752: TransformVertexAsRequired( sVertex, 752, curLF ); break;
//DeadCode JON 30Oct00 		case 753: TransformVertexAsRequired( sVertex, 753, curLF ); break;
//DeadCode JON 30Oct00 		case 754: TransformVertexAsRequired( sVertex, 754, curLF ); break;
//DeadCode JON 30Oct00 		case 755: TransformVertexAsRequired( sVertex, 755, curLF ); break;
//DeadCode JON 30Oct00 		case 756: TransformVertexAsRequired( sVertex, 756, curLF ); break;
//DeadCode JON 30Oct00 		case 757: TransformVertexAsRequired( sVertex, 757, curLF ); break;
//DeadCode JON 30Oct00 		case 758: TransformVertexAsRequired( sVertex, 758, curLF ); break;
//DeadCode JON 30Oct00 		case 759: TransformVertexAsRequired( sVertex, 759, curLF ); break;
//DeadCode JON 30Oct00 		case 760: TransformVertexAsRequired( sVertex, 760, curLF ); break;
//DeadCode JON 30Oct00 		case 761: TransformVertexAsRequired( sVertex, 761, curLF ); break;
//DeadCode JON 30Oct00 		case 762: TransformVertexAsRequired( sVertex, 762, curLF ); break;
//DeadCode JON 30Oct00 		case 763: TransformVertexAsRequired( sVertex, 763, curLF ); break;
//DeadCode JON 30Oct00 		case 764: TransformVertexAsRequired( sVertex, 764, curLF ); break;
//DeadCode JON 30Oct00 		case 765: TransformVertexAsRequired( sVertex, 765, curLF ); break;
//DeadCode JON 30Oct00 		case 766: TransformVertexAsRequired( sVertex, 766, curLF ); break;
//DeadCode JON 30Oct00 		case 767: TransformVertexAsRequired( sVertex, 767, curLF ); break;
//DeadCode JON 30Oct00 		case 768: TransformVertexAsRequired( sVertex, 768, curLF ); break;
//DeadCode JON 30Oct00 		case 769: TransformVertexAsRequired( sVertex, 769, curLF ); break;
//DeadCode JON 30Oct00 		case 770: TransformVertexAsRequired( sVertex, 770, curLF ); break;
//DeadCode JON 30Oct00 		case 771: TransformVertexAsRequired( sVertex, 771, curLF ); break;
//DeadCode JON 30Oct00 		case 772: TransformVertexAsRequired( sVertex, 772, curLF ); break;
//DeadCode JON 30Oct00 		case 773: TransformVertexAsRequired( sVertex, 773, curLF ); break;
//DeadCode JON 30Oct00 		case 774: TransformVertexAsRequired( sVertex, 774, curLF ); break;
//DeadCode JON 30Oct00 		case 775: TransformVertexAsRequired( sVertex, 775, curLF ); break;
//DeadCode JON 30Oct00 		case 776: TransformVertexAsRequired( sVertex, 776, curLF ); break;
//DeadCode JON 30Oct00 		case 777: TransformVertexAsRequired( sVertex, 777, curLF ); break;
//DeadCode JON 30Oct00 		case 778: TransformVertexAsRequired( sVertex, 778, curLF ); break;
//DeadCode JON 30Oct00 		case 779: TransformVertexAsRequired( sVertex, 779, curLF ); break;
//DeadCode JON 30Oct00 		case 780: TransformVertexAsRequired( sVertex, 780, curLF ); break;
//DeadCode JON 30Oct00 		case 781: TransformVertexAsRequired( sVertex, 781, curLF ); break;
//DeadCode JON 30Oct00 		case 782: TransformVertexAsRequired( sVertex, 782, curLF ); break;
//DeadCode JON 30Oct00 		case 783: TransformVertexAsRequired( sVertex, 783, curLF ); break;
//DeadCode JON 30Oct00 		case 784: TransformVertexAsRequired( sVertex, 784, curLF ); break;
//DeadCode JON 30Oct00 		case 785: TransformVertexAsRequired( sVertex, 785, curLF ); break;
//DeadCode JON 30Oct00 		case 786: TransformVertexAsRequired( sVertex, 786, curLF ); break;
//DeadCode JON 30Oct00 		case 787: TransformVertexAsRequired( sVertex, 787, curLF ); break;
//DeadCode JON 30Oct00 		case 788: TransformVertexAsRequired( sVertex, 788, curLF ); break;
//DeadCode JON 30Oct00 		case 789: TransformVertexAsRequired( sVertex, 789, curLF ); break;
//DeadCode JON 30Oct00 		case 790: TransformVertexAsRequired( sVertex, 790, curLF ); break;
//DeadCode JON 30Oct00 		case 791: TransformVertexAsRequired( sVertex, 791, curLF ); break;
//DeadCode JON 30Oct00 		case 792: TransformVertexAsRequired( sVertex, 792, curLF ); break;
//DeadCode JON 30Oct00 		case 793: TransformVertexAsRequired( sVertex, 793, curLF ); break;
//DeadCode JON 30Oct00 		case 794: TransformVertexAsRequired( sVertex, 794, curLF ); break;
//DeadCode JON 30Oct00 		case 795: TransformVertexAsRequired( sVertex, 795, curLF ); break;
//DeadCode JON 30Oct00 		case 796: TransformVertexAsRequired( sVertex, 796, curLF ); break;
//DeadCode JON 30Oct00 		case 797: TransformVertexAsRequired( sVertex, 797, curLF ); break;
//DeadCode JON 30Oct00 		case 798: TransformVertexAsRequired( sVertex, 798, curLF ); break;
//DeadCode JON 30Oct00 		case 799: TransformVertexAsRequired( sVertex, 799, curLF ); break;
//DeadCode JON 30Oct00 		case 800: TransformVertexAsRequired( sVertex, 800, curLF ); break;
//DeadCode JON 30Oct00 		case 801: TransformVertexAsRequired( sVertex, 801, curLF ); break;
//DeadCode JON 30Oct00 		case 802: TransformVertexAsRequired( sVertex, 802, curLF ); break;
//DeadCode JON 30Oct00 		case 803: TransformVertexAsRequired( sVertex, 803, curLF ); break;
//DeadCode JON 30Oct00 		case 804: TransformVertexAsRequired( sVertex, 804, curLF ); break;
//DeadCode JON 30Oct00 		case 805: TransformVertexAsRequired( sVertex, 805, curLF ); break;
//DeadCode JON 30Oct00 		case 806: TransformVertexAsRequired( sVertex, 806, curLF ); break;
//DeadCode JON 30Oct00 		case 807: TransformVertexAsRequired( sVertex, 807, curLF ); break;
//DeadCode JON 30Oct00 		case 808: TransformVertexAsRequired( sVertex, 808, curLF ); break;
//DeadCode JON 30Oct00 		case 809: TransformVertexAsRequired( sVertex, 809, curLF ); break;
//DeadCode JON 30Oct00 		case 810: TransformVertexAsRequired( sVertex, 810, curLF ); break;
//DeadCode JON 30Oct00 		case 811: TransformVertexAsRequired( sVertex, 811, curLF ); break;
//DeadCode JON 30Oct00 		case 812: TransformVertexAsRequired( sVertex, 812, curLF ); break;
//DeadCode JON 30Oct00 		case 813: TransformVertexAsRequired( sVertex, 813, curLF ); break;
//DeadCode JON 30Oct00 		case 814: TransformVertexAsRequired( sVertex, 814, curLF ); break;
//DeadCode JON 30Oct00 		case 815: TransformVertexAsRequired( sVertex, 815, curLF ); break;
//DeadCode JON 30Oct00 		case 816: TransformVertexAsRequired( sVertex, 816, curLF ); break;
//DeadCode JON 30Oct00 		case 817: TransformVertexAsRequired( sVertex, 817, curLF ); break;
//DeadCode JON 30Oct00 		case 818: TransformVertexAsRequired( sVertex, 818, curLF ); break;
//DeadCode JON 30Oct00 		case 819: TransformVertexAsRequired( sVertex, 819, curLF ); break;
//DeadCode JON 30Oct00 		case 820: TransformVertexAsRequired( sVertex, 820, curLF ); break;
//DeadCode JON 30Oct00 		case 821: TransformVertexAsRequired( sVertex, 821, curLF ); break;
//DeadCode JON 30Oct00 		case 822: TransformVertexAsRequired( sVertex, 822, curLF ); break;
//DeadCode JON 30Oct00 		case 823: TransformVertexAsRequired( sVertex, 823, curLF ); break;
//DeadCode JON 30Oct00 		case 824: TransformVertexAsRequired( sVertex, 824, curLF ); break;
//DeadCode JON 30Oct00 		case 825: TransformVertexAsRequired( sVertex, 825, curLF ); break;
//DeadCode JON 30Oct00 		case 826: TransformVertexAsRequired( sVertex, 826, curLF ); break;
//DeadCode JON 30Oct00 		case 827: TransformVertexAsRequired( sVertex, 827, curLF ); break;
//DeadCode JON 30Oct00 		case 828: TransformVertexAsRequired( sVertex, 828, curLF ); break;
//DeadCode JON 30Oct00 		case 829: TransformVertexAsRequired( sVertex, 829, curLF ); break;
//DeadCode JON 30Oct00 		case 830: TransformVertexAsRequired( sVertex, 830, curLF ); break;
//DeadCode JON 30Oct00 		case 831: TransformVertexAsRequired( sVertex, 831, curLF ); break;
//DeadCode JON 30Oct00 		case 832: TransformVertexAsRequired( sVertex, 832, curLF ); break;
//DeadCode JON 30Oct00 		case 833: TransformVertexAsRequired( sVertex, 833, curLF ); break;
//DeadCode JON 30Oct00 		case 834: TransformVertexAsRequired( sVertex, 834, curLF ); break;
//DeadCode JON 30Oct00 		case 835: TransformVertexAsRequired( sVertex, 835, curLF ); break;
//DeadCode JON 30Oct00 		case 836: TransformVertexAsRequired( sVertex, 836, curLF ); break;
//DeadCode JON 30Oct00 		case 837: TransformVertexAsRequired( sVertex, 837, curLF ); break;
//DeadCode JON 30Oct00 		case 838: TransformVertexAsRequired( sVertex, 838, curLF ); break;
//DeadCode JON 30Oct00 		case 839: TransformVertexAsRequired( sVertex, 839, curLF ); break;
//DeadCode JON 30Oct00 		case 840: TransformVertexAsRequired( sVertex, 840, curLF ); break;
//DeadCode JON 30Oct00 		case 841: TransformVertexAsRequired( sVertex, 841, curLF ); break;
//DeadCode JON 30Oct00 		case 842: TransformVertexAsRequired( sVertex, 842, curLF ); break;
//DeadCode JON 30Oct00 		case 843: TransformVertexAsRequired( sVertex, 843, curLF ); break;
//DeadCode JON 30Oct00 		case 844: TransformVertexAsRequired( sVertex, 844, curLF ); break;
//DeadCode JON 30Oct00 		case 845: TransformVertexAsRequired( sVertex, 845, curLF ); break;
//DeadCode JON 30Oct00 		case 846: TransformVertexAsRequired( sVertex, 846, curLF ); break;
//DeadCode JON 30Oct00 		case 847: TransformVertexAsRequired( sVertex, 847, curLF ); break;
//DeadCode JON 30Oct00 		case 848: TransformVertexAsRequired( sVertex, 848, curLF ); break;
//DeadCode JON 30Oct00 		case 849: TransformVertexAsRequired( sVertex, 849, curLF ); break;
//DeadCode JON 30Oct00 		case 850: TransformVertexAsRequired( sVertex, 850, curLF ); break;
//DeadCode JON 30Oct00 		case 851: TransformVertexAsRequired( sVertex, 851, curLF ); break;
//DeadCode JON 30Oct00 		case 852: TransformVertexAsRequired( sVertex, 852, curLF ); break;
//DeadCode JON 30Oct00 		case 853: TransformVertexAsRequired( sVertex, 853, curLF ); break;
//DeadCode JON 30Oct00 		case 854: TransformVertexAsRequired( sVertex, 854, curLF ); break;
//DeadCode JON 30Oct00 		case 855: TransformVertexAsRequired( sVertex, 855, curLF ); break;
//DeadCode JON 30Oct00 		case 856: TransformVertexAsRequired( sVertex, 856, curLF ); break;
//DeadCode JON 30Oct00 		case 857: TransformVertexAsRequired( sVertex, 857, curLF ); break;
//DeadCode JON 30Oct00 		case 858: TransformVertexAsRequired( sVertex, 858, curLF ); break;
//DeadCode JON 30Oct00 		case 859: TransformVertexAsRequired( sVertex, 859, curLF ); break;
//DeadCode JON 30Oct00 		case 860: TransformVertexAsRequired( sVertex, 860, curLF ); break;
//DeadCode JON 30Oct00 		case 861: TransformVertexAsRequired( sVertex, 861, curLF ); break;
//DeadCode JON 30Oct00 		case 862: TransformVertexAsRequired( sVertex, 862, curLF ); break;
//DeadCode JON 30Oct00 		case 863: TransformVertexAsRequired( sVertex, 863, curLF ); break;
//DeadCode JON 30Oct00 		case 864: TransformVertexAsRequired( sVertex, 864, curLF ); break;
//DeadCode JON 30Oct00 		case 865: TransformVertexAsRequired( sVertex, 865, curLF ); break;
//DeadCode JON 30Oct00 		case 866: TransformVertexAsRequired( sVertex, 866, curLF ); break;
//DeadCode JON 30Oct00 		case 867: TransformVertexAsRequired( sVertex, 867, curLF ); break;
//DeadCode JON 30Oct00 		case 868: TransformVertexAsRequired( sVertex, 868, curLF ); break;
//DeadCode JON 30Oct00 		case 869: TransformVertexAsRequired( sVertex, 869, curLF ); break;
//DeadCode JON 30Oct00 		case 870: TransformVertexAsRequired( sVertex, 870, curLF ); break;
//DeadCode JON 30Oct00 		case 871: TransformVertexAsRequired( sVertex, 871, curLF ); break;
//DeadCode JON 30Oct00 		case 872: TransformVertexAsRequired( sVertex, 872, curLF ); break;
//DeadCode JON 30Oct00 		case 873: TransformVertexAsRequired( sVertex, 873, curLF ); break;
//DeadCode JON 30Oct00 		case 874: TransformVertexAsRequired( sVertex, 874, curLF ); break;
//DeadCode JON 30Oct00 		case 875: TransformVertexAsRequired( sVertex, 875, curLF ); break;
//DeadCode JON 30Oct00 		case 876: TransformVertexAsRequired( sVertex, 876, curLF ); break;
//DeadCode JON 30Oct00 		case 877: TransformVertexAsRequired( sVertex, 877, curLF ); break;
//DeadCode JON 30Oct00 		case 878: TransformVertexAsRequired( sVertex, 878, curLF ); break;
//DeadCode JON 30Oct00 		case 879: TransformVertexAsRequired( sVertex, 879, curLF ); break;
//DeadCode JON 30Oct00 		case 880: TransformVertexAsRequired( sVertex, 880, curLF ); break;
//DeadCode JON 30Oct00 		case 881: TransformVertexAsRequired( sVertex, 881, curLF ); break;
//DeadCode JON 30Oct00 		case 882: TransformVertexAsRequired( sVertex, 882, curLF ); break;
//DeadCode JON 30Oct00 		case 883: TransformVertexAsRequired( sVertex, 883, curLF ); break;
//DeadCode JON 30Oct00 		case 884: TransformVertexAsRequired( sVertex, 884, curLF ); break;
//DeadCode JON 30Oct00 		case 885: TransformVertexAsRequired( sVertex, 885, curLF ); break;
//DeadCode JON 30Oct00 		case 886: TransformVertexAsRequired( sVertex, 886, curLF ); break;
//DeadCode JON 30Oct00 		case 887: TransformVertexAsRequired( sVertex, 887, curLF ); break;
//DeadCode JON 30Oct00 		case 888: TransformVertexAsRequired( sVertex, 888, curLF ); break;
//DeadCode JON 30Oct00 		case 889: TransformVertexAsRequired( sVertex, 889, curLF ); break;
//DeadCode JON 30Oct00 		case 890: TransformVertexAsRequired( sVertex, 890, curLF ); break;
//DeadCode JON 30Oct00 		case 891: TransformVertexAsRequired( sVertex, 891, curLF ); break;
//DeadCode JON 30Oct00 		case 892: TransformVertexAsRequired( sVertex, 892, curLF ); break;
//DeadCode JON 30Oct00 		case 893: TransformVertexAsRequired( sVertex, 893, curLF ); break;
//DeadCode JON 30Oct00 		case 894: TransformVertexAsRequired( sVertex, 894, curLF ); break;
//DeadCode JON 30Oct00 		case 895: TransformVertexAsRequired( sVertex, 895, curLF ); break;
//DeadCode JON 30Oct00 		case 896: TransformVertexAsRequired( sVertex, 896, curLF ); break;
//DeadCode JON 30Oct00 		case 897: TransformVertexAsRequired( sVertex, 897, curLF ); break;
//DeadCode JON 30Oct00 		case 898: TransformVertexAsRequired( sVertex, 898, curLF ); break;
//DeadCode JON 30Oct00 		case 899: TransformVertexAsRequired( sVertex, 899, curLF ); break;
//DeadCode JON 30Oct00 		case 900: TransformVertexAsRequired( sVertex, 900, curLF ); break;
//DeadCode JON 30Oct00 		case 901: TransformVertexAsRequired( sVertex, 901, curLF ); break;
//DeadCode JON 30Oct00 		case 902: TransformVertexAsRequired( sVertex, 902, curLF ); break;
//DeadCode JON 30Oct00 		case 903: TransformVertexAsRequired( sVertex, 903, curLF ); break;
//DeadCode JON 30Oct00 		case 904: TransformVertexAsRequired( sVertex, 904, curLF ); break;
//DeadCode JON 30Oct00 		case 905: TransformVertexAsRequired( sVertex, 905, curLF ); break;
//DeadCode JON 30Oct00 		case 906: TransformVertexAsRequired( sVertex, 906, curLF ); break;
//DeadCode JON 30Oct00 		case 907: TransformVertexAsRequired( sVertex, 907, curLF ); break;
//DeadCode JON 30Oct00 		case 908: TransformVertexAsRequired( sVertex, 908, curLF ); break;
//DeadCode JON 30Oct00 		case 909: TransformVertexAsRequired( sVertex, 909, curLF ); break;
//DeadCode JON 30Oct00 		case 910: TransformVertexAsRequired( sVertex, 910, curLF ); break;
//DeadCode JON 30Oct00 		case 911: TransformVertexAsRequired( sVertex, 911, curLF ); break;
//DeadCode JON 30Oct00 		case 912: TransformVertexAsRequired( sVertex, 912, curLF ); break;
//DeadCode JON 30Oct00 		case 913: TransformVertexAsRequired( sVertex, 913, curLF ); break;
//DeadCode JON 30Oct00 		case 914: TransformVertexAsRequired( sVertex, 914, curLF ); break;
//DeadCode JON 30Oct00 		case 915: TransformVertexAsRequired( sVertex, 915, curLF ); break;
//DeadCode JON 30Oct00 		case 916: TransformVertexAsRequired( sVertex, 916, curLF ); break;
//DeadCode JON 30Oct00 		case 917: TransformVertexAsRequired( sVertex, 917, curLF ); break;
//DeadCode JON 30Oct00 		case 918: TransformVertexAsRequired( sVertex, 918, curLF ); break;
//DeadCode JON 30Oct00 		case 919: TransformVertexAsRequired( sVertex, 919, curLF ); break;
//DeadCode JON 30Oct00 		case 920: TransformVertexAsRequired( sVertex, 920, curLF ); break;
//DeadCode JON 30Oct00 		case 921: TransformVertexAsRequired( sVertex, 921, curLF ); break;
//DeadCode JON 30Oct00 		case 922: TransformVertexAsRequired( sVertex, 922, curLF ); break;
//DeadCode JON 30Oct00 		case 923: TransformVertexAsRequired( sVertex, 923, curLF ); break;
//DeadCode JON 30Oct00 		case 924: TransformVertexAsRequired( sVertex, 924, curLF ); break;
//DeadCode JON 30Oct00 		case 925: TransformVertexAsRequired( sVertex, 925, curLF ); break;
//DeadCode JON 30Oct00 		case 926: TransformVertexAsRequired( sVertex, 926, curLF ); break;
//DeadCode JON 30Oct00 		case 927: TransformVertexAsRequired( sVertex, 927, curLF ); break;
//DeadCode JON 30Oct00 		case 928: TransformVertexAsRequired( sVertex, 928, curLF ); break;
//DeadCode JON 30Oct00 		case 929: TransformVertexAsRequired( sVertex, 929, curLF ); break;
//DeadCode JON 30Oct00 		case 930: TransformVertexAsRequired( sVertex, 930, curLF ); break;
//DeadCode JON 30Oct00 		case 931: TransformVertexAsRequired( sVertex, 931, curLF ); break;
//DeadCode JON 30Oct00 		case 932: TransformVertexAsRequired( sVertex, 932, curLF ); break;
//DeadCode JON 30Oct00 		case 933: TransformVertexAsRequired( sVertex, 933, curLF ); break;
//DeadCode JON 30Oct00 		case 934: TransformVertexAsRequired( sVertex, 934, curLF ); break;
//DeadCode JON 30Oct00 		case 935: TransformVertexAsRequired( sVertex, 935, curLF ); break;
//DeadCode JON 30Oct00 		case 936: TransformVertexAsRequired( sVertex, 936, curLF ); break;
//DeadCode JON 30Oct00 		case 937: TransformVertexAsRequired( sVertex, 937, curLF ); break;
//DeadCode JON 30Oct00 		case 938: TransformVertexAsRequired( sVertex, 938, curLF ); break;
//DeadCode JON 30Oct00 		case 939: TransformVertexAsRequired( sVertex, 939, curLF ); break;
//DeadCode JON 30Oct00 		case 940: TransformVertexAsRequired( sVertex, 940, curLF ); break;
//DeadCode JON 30Oct00 		case 941: TransformVertexAsRequired( sVertex, 941, curLF ); break;
//DeadCode JON 30Oct00 		case 942: TransformVertexAsRequired( sVertex, 942, curLF ); break;
//DeadCode JON 30Oct00 		case 943: TransformVertexAsRequired( sVertex, 943, curLF ); break;
//DeadCode JON 30Oct00 		case 944: TransformVertexAsRequired( sVertex, 944, curLF ); break;
//DeadCode JON 30Oct00 		case 945: TransformVertexAsRequired( sVertex, 945, curLF ); break;
//DeadCode JON 30Oct00 		case 946: TransformVertexAsRequired( sVertex, 946, curLF ); break;
//DeadCode JON 30Oct00 		case 947: TransformVertexAsRequired( sVertex, 947, curLF ); break;
//DeadCode JON 30Oct00 		case 948: TransformVertexAsRequired( sVertex, 948, curLF ); break;
//DeadCode JON 30Oct00 		case 949: TransformVertexAsRequired( sVertex, 949, curLF ); break;
//DeadCode JON 30Oct00 		case 950: TransformVertexAsRequired( sVertex, 950, curLF ); break;
//DeadCode JON 30Oct00 		case 951: TransformVertexAsRequired( sVertex, 951, curLF ); break;
//DeadCode JON 30Oct00 		case 952: TransformVertexAsRequired( sVertex, 952, curLF ); break;
//DeadCode JON 30Oct00 		case 953: TransformVertexAsRequired( sVertex, 953, curLF ); break;
//DeadCode JON 30Oct00 		case 954: TransformVertexAsRequired( sVertex, 954, curLF ); break;
//DeadCode JON 30Oct00 		case 955: TransformVertexAsRequired( sVertex, 955, curLF ); break;
//DeadCode JON 30Oct00 		case 956: TransformVertexAsRequired( sVertex, 956, curLF ); break;
//DeadCode JON 30Oct00 		case 957: TransformVertexAsRequired( sVertex, 957, curLF ); break;
//DeadCode JON 30Oct00 		case 958: TransformVertexAsRequired( sVertex, 958, curLF ); break;
//DeadCode JON 30Oct00 		case 959: TransformVertexAsRequired( sVertex, 959, curLF ); break;
//DeadCode JON 30Oct00 		case 960: TransformVertexAsRequired( sVertex, 960, curLF ); break;
//DeadCode JON 30Oct00 		case 961: TransformVertexAsRequired( sVertex, 961, curLF ); break;
//DeadCode JON 30Oct00 		case 962: TransformVertexAsRequired( sVertex, 962, curLF ); break;
//DeadCode JON 30Oct00 		case 963: TransformVertexAsRequired( sVertex, 963, curLF ); break;
//DeadCode JON 30Oct00 		case 964: TransformVertexAsRequired( sVertex, 964, curLF ); break;
//DeadCode JON 30Oct00 		case 965: TransformVertexAsRequired( sVertex, 965, curLF ); break;
//DeadCode JON 30Oct00 		case 966: TransformVertexAsRequired( sVertex, 966, curLF ); break;
//DeadCode JON 30Oct00 		case 967: TransformVertexAsRequired( sVertex, 967, curLF ); break;
//DeadCode JON 30Oct00 		case 968: TransformVertexAsRequired( sVertex, 968, curLF ); break;
//DeadCode JON 30Oct00 		case 969: TransformVertexAsRequired( sVertex, 969, curLF ); break;
//DeadCode JON 30Oct00 		case 970: TransformVertexAsRequired( sVertex, 970, curLF ); break;
//DeadCode JON 30Oct00 		case 971: TransformVertexAsRequired( sVertex, 971, curLF ); break;
//DeadCode JON 30Oct00 		case 972: TransformVertexAsRequired( sVertex, 972, curLF ); break;
//DeadCode JON 30Oct00 		case 973: TransformVertexAsRequired( sVertex, 973, curLF ); break;
//DeadCode JON 30Oct00 		case 974: TransformVertexAsRequired( sVertex, 974, curLF ); break;
//DeadCode JON 30Oct00 		case 975: TransformVertexAsRequired( sVertex, 975, curLF ); break;
//DeadCode JON 30Oct00 		case 976: TransformVertexAsRequired( sVertex, 976, curLF ); break;
//DeadCode JON 30Oct00 		case 977: TransformVertexAsRequired( sVertex, 977, curLF ); break;
//DeadCode JON 30Oct00 		case 978: TransformVertexAsRequired( sVertex, 978, curLF ); break;
//DeadCode JON 30Oct00 		case 979: TransformVertexAsRequired( sVertex, 979, curLF ); break;
//DeadCode JON 30Oct00 		case 980: TransformVertexAsRequired( sVertex, 980, curLF ); break;
//DeadCode JON 30Oct00 		case 981: TransformVertexAsRequired( sVertex, 981, curLF ); break;
//DeadCode JON 30Oct00 		case 982: TransformVertexAsRequired( sVertex, 982, curLF ); break;
//DeadCode JON 30Oct00 		case 983: TransformVertexAsRequired( sVertex, 983, curLF ); break;
//DeadCode JON 30Oct00 		case 984: TransformVertexAsRequired( sVertex, 984, curLF ); break;
//DeadCode JON 30Oct00 		case 985: TransformVertexAsRequired( sVertex, 985, curLF ); break;
//DeadCode JON 30Oct00 		case 986: TransformVertexAsRequired( sVertex, 986, curLF ); break;
//DeadCode JON 30Oct00 		case 987: TransformVertexAsRequired( sVertex, 987, curLF ); break;
//DeadCode JON 30Oct00 		case 988: TransformVertexAsRequired( sVertex, 988, curLF ); break;
//DeadCode JON 30Oct00 		case 989: TransformVertexAsRequired( sVertex, 989, curLF ); break;
//DeadCode JON 30Oct00 		case 990: TransformVertexAsRequired( sVertex, 990, curLF ); break;
//DeadCode JON 30Oct00 		case 991: TransformVertexAsRequired( sVertex, 991, curLF ); break;
//DeadCode JON 30Oct00 		case 992: TransformVertexAsRequired( sVertex, 992, curLF ); break;
//DeadCode JON 30Oct00 		case 993: TransformVertexAsRequired( sVertex, 993, curLF ); break;
//DeadCode JON 30Oct00 		case 994: TransformVertexAsRequired( sVertex, 994, curLF ); break;
//DeadCode JON 30Oct00 		case 995: TransformVertexAsRequired( sVertex, 995, curLF ); break;
//DeadCode JON 30Oct00 		case 996: TransformVertexAsRequired( sVertex, 996, curLF ); break;
//DeadCode JON 30Oct00 		case 997: TransformVertexAsRequired( sVertex, 997, curLF ); break;
//DeadCode JON 30Oct00 		case 998: TransformVertexAsRequired( sVertex, 998, curLF ); break;
//DeadCode JON 30Oct00 		case 999: TransformVertexAsRequired( sVertex, 999, curLF ); break;
//DeadCode JON 30Oct00 		case 1000: TransformVertexAsRequired( sVertex, 1000, curLF ); break;
//DeadCode JON 30Oct00 		case 1001: TransformVertexAsRequired( sVertex, 1001, curLF ); break;
//DeadCode JON 30Oct00 		case 1002: TransformVertexAsRequired( sVertex, 1002, curLF ); break;
//DeadCode JON 30Oct00 		case 1003: TransformVertexAsRequired( sVertex, 1003, curLF ); break;
//DeadCode JON 30Oct00 		case 1004: TransformVertexAsRequired( sVertex, 1004, curLF ); break;
//DeadCode JON 30Oct00 		case 1005: TransformVertexAsRequired( sVertex, 1005, curLF ); break;
//DeadCode JON 30Oct00 		case 1006: TransformVertexAsRequired( sVertex, 1006, curLF ); break;
//DeadCode JON 30Oct00 		case 1007: TransformVertexAsRequired( sVertex, 1007, curLF ); break;
//DeadCode JON 30Oct00 		case 1008: TransformVertexAsRequired( sVertex, 1008, curLF ); break;
//DeadCode JON 30Oct00 		case 1009: TransformVertexAsRequired( sVertex, 1009, curLF ); break;
//DeadCode JON 30Oct00 		case 1010: TransformVertexAsRequired( sVertex, 1010, curLF ); break;
//DeadCode JON 30Oct00 		case 1011: TransformVertexAsRequired( sVertex, 1011, curLF ); break;
//DeadCode JON 30Oct00 		case 1012: TransformVertexAsRequired( sVertex, 1012, curLF ); break;
//DeadCode JON 30Oct00 		case 1013: TransformVertexAsRequired( sVertex, 1013, curLF ); break;
//DeadCode JON 30Oct00 		case 1014: TransformVertexAsRequired( sVertex, 1014, curLF ); break;
//DeadCode JON 30Oct00 		case 1015: TransformVertexAsRequired( sVertex, 1015, curLF ); break;
//DeadCode JON 30Oct00 		case 1016: TransformVertexAsRequired( sVertex, 1016, curLF ); break;
//DeadCode JON 30Oct00 		case 1017: TransformVertexAsRequired( sVertex, 1017, curLF ); break;
//DeadCode JON 30Oct00 		case 1018: TransformVertexAsRequired( sVertex, 1018, curLF ); break;
//DeadCode JON 30Oct00 		case 1019: TransformVertexAsRequired( sVertex, 1019, curLF ); break;
//DeadCode JON 30Oct00 		case 1020: TransformVertexAsRequired( sVertex, 1020, curLF ); break;
//DeadCode JON 30Oct00 		case 1021: TransformVertexAsRequired( sVertex, 1021, curLF ); break;
//DeadCode JON 30Oct00 		case 1022: TransformVertexAsRequired( sVertex, 1022, curLF ); break;
//DeadCode JON 30Oct00 		case 1023: TransformVertexAsRequired( sVertex, 1023, curLF ); break;
	NODEFAULT;
	}
}
