#ifndef LIB3D_Included
#define LIB3D_Included

#define _NO_VERTEX_SHARING_HDR
#define NOATL

// GUID for first implementation of 3D graphics library 08-11-1999
// {11038561-95E1-11d3-8795-0040052C1F45}
//TEMPCODE DAW 29/01/00 #include <objbase.h>
//#include <afxwin.h>

#include <fstream>
#include <cassert>
#include <math.h>
#include <d3dtypes.h>
#include <d3d.h>
#include "alloc.h"

#include "myangles.h"
#include <dosdefs.h>

class SPolygon;
struct SLine;
struct SPoint;
//struct alloc_handle_t;

#ifdef LIB3D_EXPORTS
#define LIB3D_API __declspec(dllexport)
#else
#define LIB3D_API __declspec(dllimport)
#endif

//#define DOUBLE_MATRIXES

#pragma warning (disable : 4189 )
template< class T > IUnknown* & IUnknownPtrRef( T*& tPtr )
{
#ifndef NDEBUG
    IUnknown* dummy = tPtr; // 4 diagnostic error
#endif
    return ( IUnknown*& )tPtr;
}
#pragma warning (default : 4189 )

const ULong FORCE_TO_BACK_Z = 3;
const ULong NUM_Z_LAYERS = 4;// as above but +1...						//JON 23Oct00

const int DEFAULT_SCREEN_WIDTH = 800;
const int DEFAULT_SCREEN_DEPTH = 32;
const int MINIMUM_TEXTURE_RAM_REQUIRED = 0;//4*1024*1024; // in bytes, just approx will do - shouldn't be needed now

enum MATERIAL_FLAGS
{
    IS_LAND = 1,
    IS_DOUBLE_TEXTURED = 1<<1,
    IS_PLAIN = 1<<2,
    IS_ALPHA = 1<<3,
    IS_ALPHA_SOLID = 1<<4,
    IS_SPECULAR = 1<<5,
};
const ULong MAX_TEXTURE_OPTS = 10;
//DeadCode JON 13Jul00 const D3DVALUE zSMALL = 0.000001;

const ULong COL_NULL = 0xFF000000;
const ULong SPECULAR_NO_FOG = 0xFF000000;
const int MAX_DOPOINTS = 1024;

const int LAND_TEXT_BANDS = 8;

const int MAX_LAND_TEXTURES = 256;

const D3DVALUE landscapeTextScale = 255.f/(256.f*256.f);
//TempCode JON 19Sep00 const D3DVALUE landscapeTextScale = 1.f/256.f;//(256.f*256.f);
const D3DVALUE landscapeTextOffset = 1.f/512.f;
//TempCode JON 19Sep00 const D3DVALUE landscapeTextOffset = 0.0;


#define MAX_TEXT_LENGTH 64
#define MATRIX_STACK_SIZE 128
#define ROWANANG_TO_RADANG	(3.14159265f/32768.0f)
#define MAX_VERTICES 2048
#define MAX_TEXTURES 2048
#define MAX_RENDER_TARGETS 16

#define DXT1 DWORD(('D'<<24)+('X'<<16)+('T'<<8)+'1')
#define DXT2 DWORD(('D'<<24)+('X'<<16)+('T'<<8)+'2')
#define DXT3 DWORD(('D'<<24)+('X'<<16)+('T'<<8)+'3')
#define DXT4 DWORD(('D'<<24)+('X'<<16)+('T'<<8)+'4')
#define DXT5 DWORD(('D'<<24)+('X'<<16)+('T'<<8)+'5')

//D3DFVF_R3DTLVERTEX is for mini vertex structure for 2D rendering (R3DTLVERTEX)
//D3DFVF_R3DTNLVERTEX is for full transformed vertex (D3DTLVERTEX)
//D3DFVF_R3DVERTEX is for untransformed vertex (R3DVERTEX)
//D3DFVF_R3DVERTEX2 is for untransformed vertex with 2 sets of texture coordinates (R3DVERTEX2)
//D3DFVF_R3DVERTEX3 is for untransformed vertex with 3 sets of texture coordinates (R3DVERTEX3)
#pragma warnmsg( "Look at these equates..." )
#define D3DFVF_R3DTLVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEXCOORDSIZE2(0))

#define D3DFVF_R3DTNLVERTEX D3DFVF_D3DTLVERTEX
#define D3DFVF_R3DTNLVERTEX2 (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_SPECULAR|D3DFVF_TEXCOORDSIZE2(0)|D3DFVF_TEXCOORDSIZE2(1)|D3DFVF_TEX2)
#define D3DFVF_R3DTNLVERTEX3 (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_SPECULAR|D3DFVF_TEXCOORDSIZE2(0)|D3DFVF_TEXCOORDSIZE2(1)|D3DFVF_TEXCOORDSIZE2(2)|D3DFVF_TEX3)

#define D3DFVF_R3DVERTEX D3DFVF_VERTEX
#define D3DFVF_R3DVERTEX2 (D3DFVF_VERTEX|D3DFVF_TEXCOORDSIZE2(1))
#define D3DFVF_R3DVERTEX3 (D3DFVF_VERTEX|D3DFVF_TEXCOORDSIZE2(1)|D3DFVF_TEXCOORDSIZE2(2)|D3DFVF_TEX3))

#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define NUMBITS (sizeof(ULong)*8)
//
// Get the integral form of a float
//
#define FP_BITS(fp) (*(ULong*)&(fp))
//
// Get the absolute value for a float in integral form
//
#define FP_ABS_BITS(fp) (FP_BITS(fp)&~(1<<(NUMBITS-1)))
#define FP_ABS_BITS2(x) ((x)&~(1<<(NUMBITS-1)))
//
// Get the sign bit of a float
//
#define FP_SIGN_BIT(fp) (FP_BITS(fp)&(1<<(NUMBITS-1)))
//
// Get the sign bit of a float in integral form as 0 or 1
//
#define FP_SIGN_BIT2(x) (ULong(x)>>(NUMBITS-1))
//
// Bit pattern for 1.0f
//
#define FP_ONE_BITS 0x3F800000
#define FP_MINUS_ONE_BITS 0xBF800000

#define M0_11	0
#define M0_12	1
#define M0_13	2
#define M0_14	3
#define M0_21	4
#define M0_22	5
#define M0_23	6
#define M0_24	7
#define M0_31	8
#define M0_32	9
#define M0_33	10
#define M0_34	11
#define M0_41	12
#define M0_42	13
#define M0_43	14
#define M0_44	15

#define M1_11	16
#define M1_12	17
#define M1_13	18
#define M1_14	19
#define M1_21	20
#define M1_22	21
#define M1_23	22
#define M1_24	23
#define M1_31	24
#define M1_32	25
#define M1_33	26
#define M1_34	27
#define M1_41	28
#define M1_42	29
#define M1_43	30
#define M1_44	31

#define M_I_ONES ((1<<M1_11)+(1<<M1_22)+(1<<M1_33)+(1<<M1_44))
#define M_I_ZEROS (~((1<<M0_11)+(1<<M0_22)+(1<<M0_33)+(1<<M0_44)))
#define M_IDENTITY (M_I_ONES+M_I_ZEROS)

/*
#define CLIP_W			0x00000001
#define CLIP_RIGHT		0x00000002
#define CLIP_LEFT		0x00000004
#define CLIP_TOP		0x00000008
#define CLIP_BOTTOM		0x00000010
#define CLIP_BACK		0x00000020
#define CLIP_FRONT		0x00000040
#define CLIP_ALL		(CLIP_RIGHT+CLIP_LEFT+CLIP_FRONT+CLIP_BACK+CLIP_FRONT+CLIP_BACK)
*/
enum ClipCode
{
    CLIP_RIGHT	=	0x00000001,
    CLIP_LEFT	=	0x00000002,
    CLIP_TOP	=	0x00000004,
    CLIP_BOTTOM	=	0x00000008,
    CLIP_BACK	=	0x00000010,
    CLIP_FRONT	=	0x00000020,
    CLIP_LRTB	=	(CLIP_RIGHT+CLIP_LEFT+CLIP_TOP+CLIP_BOTTOM),
    CLIP_ALL	=	(CLIP_LRTB+CLIP_FRONT+CLIP_BACK)
};
#define DEFINE_TIMER(name)\
	static __int64 last##name=0;\
	static __int64 start##name;\
	static __int64 fini##name;\
	static double average##name;\
	static int count##name=0;
/*
#define TIMER_ON(name)\
	_asm push eax _asm push edx _asm push ebx;\
	_asm lea ebx,start##name;\
	_asm _emit 0x0f _asm _emit 0x31;\
	_asm mov dword ptr [ebx],eax _asm mov dword ptr [ebx+4],edx;\
	_asm pop ebx _asm pop edx _asm pop eax;

#define TIMER_OFF(name,frames)\
	_asm push eax _asm push edx _asm push ebx;\
	_asm lea ebx,fini##name;\
	_asm _emit 0x0f _asm _emit 0x31;\
	_asm mov dword ptr [ebx],eax _asm mov dword ptr [ebx+4],edx;\
	_asm pop ebx _asm pop edx _asm pop eax;\
	fini##name-=start##name;\
	count##name++;\
	average##name=double(fini##name)/double(count##name);\
	if ((frames)==count##name) _asm int 3;
*/
//DEFINE_TIMER(textureBlt);

#define DISCARD_POLYGON(p1)	AllocDiscard((char*)(p1));

//DEADCODE JON 5/23/00 struct R3DTNLVERTEX
//DEADCODE JON 5/23/00 {
//DEADCODE JON 5/23/00 	union {D3DVALUE sx; D3DVALUE dvSX;};
//DEADCODE JON 5/23/00 	union {D3DVALUE sy; D3DVALUE dvSY;};
//DEADCODE JON 5/23/00 	union {D3DVALUE sz; D3DVALUE dvSZ;};
//DEADCODE JON 5/23/00 	union {D3DVALUE rhw; D3DVALUE dvRHW;};
//DEADCODE JON 5/23/00 	union {D3DCOLOR color; D3DCOLOR dcColor;};
//DEADCODE JON 5/23/00 	union {D3DCOLOR specular; D3DCOLOR dcSpecular;};
//DEADCODE JON 5/23/00 	union {D3DVALUE tu; D3DVALUE dvTU;};
//DEADCODE JON 5/23/00 	union {D3DVALUE tv; D3DVALUE dvTV;};
//DEADCODE JON 5/23/00 };

typedef struct VPDESC
{
    D3DVALUE top,bottom,left,right;
}
VPDESC;

typedef struct Plane
{
    D3DVALUE A,B,C,D;		//plane equation coefficients Ax+By+Cz+D==0
    Plane() {};

    D3DVALUE SignedDistanceToPlane(D3DVECTOR *v)
    {
        return A*v->x+B*v->y+C*v->z+D;
    }
    ULong Inside(D3DVECTOR *v)
    {
        D3DVALUE val=SignedDistanceToPlane(v);
        return (*(ULong*)&val)>>31;
    }
}
Plane;


#ifndef DOUBLE_MATRIXES
typedef D3DVALUE R3DMATRIX_VAL;
struct R3DMATRIX
{
    union
    {
//		D3DMATRIX mat;
        struct
        {
#pragma warning( disable : 4201)
            D3DVALUE        _11, _12, _13, _14;
            D3DVALUE        _21, _22, _23, _24;
            D3DVALUE        _31, _32, _33, _34;
            D3DVALUE        _41, _42, _43, _44;
        };
        D3DVALUE m[4][4];
    };
//    R3DMATRIX() { }
    R3DMATRIX(  D3DVALUE _m00=0, D3DVALUE _m01=0, D3DVALUE _m02=0, D3DVALUE _m03=0,
                D3DVALUE _m10=0, D3DVALUE _m11=0, D3DVALUE _m12=0, D3DVALUE _m13=0,
                D3DVALUE _m20=0, D3DVALUE _m21=0, D3DVALUE _m22=0, D3DVALUE _m23=0,
                D3DVALUE _m30=0, D3DVALUE _m31=0, D3DVALUE _m32=0, D3DVALUE _m33=0
             )
    {
        m[0][0] = _m00;
        m[0][1] = _m01;
        m[0][2] = _m02;
        m[0][3] = _m03;
        m[1][0] = _m10;
        m[1][1] = _m11;
        m[1][2] = _m12;
        m[1][3] = _m13;
        m[2][0] = _m20;
        m[2][1] = _m21;
        m[2][2] = _m22;
        m[2][3] = _m23;
        m[3][0] = _m30;
        m[3][1] = _m31;
        m[3][2] = _m32;
        m[3][3] = _m33;
    }
    operator const D3DMATRIX() const
    {
//		return mat;
        const D3DMATRIX* tmp = (D3DMATRIX*)m;
        return *tmp;
    }
    bool operator== ( const R3DMATRIX& other ) const
    {
        for (ULong i=16,*aptr=(ULong*)&_11,*bptr=(ULong*)&other._11; i!=0; i--,aptr++,bptr++)
            if (*aptr!=*bptr) return false;
        return true;
    }

};
#else
typedef double R3DMATRIX_VAL;
struct R3DMATRIX
{
    union
    {
        struct
        {
            R3DMATRIX_VAL        _11, _12, _13, _14;
            R3DMATRIX_VAL        _21, _22, _23, _24;
            R3DMATRIX_VAL        _31, _32, _33, _34;
            R3DMATRIX_VAL        _41, _42, _43, _44;
        };
        double m[4][4];
    };
    R3DMATRIX() { }
    R3DMATRIX(  R3DMATRIX_VAL _m00, R3DMATRIX_VAL _m01, R3DMATRIX_VAL _m02, R3DMATRIX_VAL _m03,
                R3DMATRIX_VAL _m10, R3DMATRIX_VAL _m11, R3DMATRIX_VAL _m12, R3DMATRIX_VAL _m13,
                R3DMATRIX_VAL _m20, R3DMATRIX_VAL _m21, R3DMATRIX_VAL _m22, R3DMATRIX_VAL _m23,
                R3DMATRIX_VAL _m30, R3DMATRIX_VAL _m31, R3DMATRIX_VAL _m32, R3DMATRIX_VAL _m33
             )
    {
        m[0][0] = _m00;
        m[0][1] = _m01;
        m[0][2] = _m02;
        m[0][3] = _m03;
        m[1][0] = _m10;
        m[1][1] = _m11;
        m[1][2] = _m12;
        m[1][3] = _m13;
        m[2][0] = _m20;
        m[2][1] = _m21;
        m[2][2] = _m22;
        m[2][3] = _m23;
        m[3][0] = _m30;
        m[3][1] = _m31;
        m[3][2] = _m32;
        m[3][3] = _m33;
    }

    R3DMATRIX( const D3DMATRIX& convert )
    {
        D3DVALUE* pother = (D3DVALUE*)&convert;
        R3DMATRIX_VAL* pv = (R3DMATRIX_VAL*)&_11;
        for ( int i = 0; i<16; i++ )
        {
            *pv++=*pother++;
        }
    }

    operator const D3DMATRIX() const
    {
        D3DMATRIX t;
        D3DVALUE* pt = (D3DVALUE*)&t;
        R3DMATRIX_VAL* pv = (R3DMATRIX_VAL*)&_11;
        for ( int i = 0; i<16; i++ )
        {
            *pt++=*pv++;
        }
        return	t;
    }

    bool operator== ( const R3DMATRIX& other ) const
    {
        for (ULong i=32,*aptr=(ULong*)&_11,*bptr=(ULong*)&other._11; i!=0; i--,aptr++,bptr++)
            if (*aptr!=*bptr) return false;
        return true;
    }

//DeadCode JON 19Sep00     R3DMATRIX_VAL& operator()(int iRow, int iColumn) { return m[iRow][iColumn]; }
//DeadCode JON 19Sep00     const R3DMATRIX_VAL& operator()(int iRow, int iColumn) const { return m[iRow][iColumn]; }
};
#endif

// the following may be used to speed up switch statements add NODEFAULT; after case statements
#ifdef NDEBUG

#define NODEFAULT   __assume(0)

#else

#ifdef _INSIDE_LIB3D_
#define NODEFAULT   default: INT3; break
#else
#define NODEFAULT	default: assert( 0 && "Default reached that doesn't exist" ); break
#endif

#endif

class F2UL_Round
{
    union
    {
        double f;
        ULong l[2];
    };
public:
    F2UL_Round( const double nf )
    {
        const double _BASE_ADD = (1024. * 1024. * 1024. * 1024. * 1024. * 4.); //2^52
        f=nf+_BASE_ADD;
    }
    inline operator ULong()
    {
        return l[0];
    }
};

class F2UB_Clip
{
    union
    {
        float f;
        ULong l;
    };
public:
    F2UB_Clip( const float nf )
    {
        const double _BASE_ADD = 8388608.; // 2^23
        f=nf+_BASE_ADD;
    }

    inline operator UByte()
    {
        if ( (l&0xFFFFFF00) != (0x4B000000) )
        {
            return (255-(l>>16))&0xFF;
        }
        else
        {
            return l&0xFF;
        }
    }
};

class R3DCOLOUR
{
public:
    union
    {
#pragma warning( disable : 4201)
        ULong all;
        struct
        {
            // funny order?3
#pragma warning( disable : 4201)
            UByte blue;//alpha;
            UByte green;//red;
            UByte red;//green;
            UByte alpha;//blue;
        };
        D3DCOLOR d3dcolor;
    };
    // RERUN: D3DCOLOR is DWORD; with the MSVC-faithful DWORD=unsigned long
    // typedef it is the same type as ULong, so the ULong operators below
    // cover it (MSVC6 tolerated the duplicate conversion decls; GCC does not).
    inline operator ULong()
    {
        return all;
    }
    	inline operator ULong&()
    	{
    		return all;
    	}

    inline operator const ULong() const
    {
        return all;
    }


//	inline operator const ULong&() const
//	{
//		return all;
//	}


    inline void set( UByte r, UByte g, UByte b )
    {
        red = r;
        green = g;
        blue = b;
    }

    inline R3DCOLOUR& operator= (const ULong t)
    {
        all = t;
        return *this;
    }
#ifdef __GNUC__
    inline R3DCOLOUR& operator&= (const ULong t)
    {
        all &= t;
        return *this;
    }
#endif

    // change to linear value frac distance between current col and other col
    // doesn't do alpha
    inline void interpRGB( const R3DCOLOUR & other, const double frac)
    {
        red+= UByte(double(other.red-red) * frac);
        green+= UByte(double(other.green-green) * frac);
        blue+= UByte(double(other.blue-blue) * frac);
    }

    inline void interpRGBA( const R3DCOLOUR & other, const double frac)
    {
        red+= UByte(double(other.red-red) * frac);
        green+= UByte(double(other.green-green) * frac);
        blue+= UByte(double(other.blue-blue) * frac);
        alpha+= UByte(double(other.alpha-alpha) * frac);
    }

};


enum Angles;
const UWord NULL_LAND_TEXT_REF = 0xFFFF;

typedef ULong HDRIVER;
typedef ULong HMODE;
//deadcode typedef ULong HMATERIAL;
typedef ULong HTEXTUREMAP;
//DeadCode JON 17Sep00 typedef ULong HRENDERTARGET;

enum RENDERTARGET_TYPE
{
    RENDERTARGET_PRIMARY = 0,
    RENDERTARGET_LANDSCAPE,
    RENDERTARGET_MIRROR
};

class HRENDERTARGET
{
    UByte targetType;
    UByte pad;
    UWord targetInstance;
public:
    HRENDERTARGET()
    {
        /* default constructor*/
    }
    HRENDERTARGET( ULong type )
    {
#ifndef NDEBUG
        if ( type == RENDERTARGET_LANDSCAPE )
            INT3; // you need to set a target tile for this...
#endif
        targetType = type;
    }
    HRENDERTARGET( ULong type, UWord instance )
    {
#ifndef NDEBUG
        if ( type != RENDERTARGET_LANDSCAPE )
            INT3; // doh, can't set an instance for these...
#endif
        targetType = RENDERTARGET_LANDSCAPE;
        targetInstance = instance;
    }
    UByte getType() const
    {
        return targetType;
    }
    UWord getInstance() const
    {
        return targetInstance;
    }
};

#define	MAX_DRIVERS		16
#define	MAX_MODES		128
#define	MAX_TEXT_LENGTH	64

//DeadCode JON 17Sep00 #define RENDERTARGET_PRIMARY HRENDERTARGET(0)
//DeadCode JON 17Sep00 #define RENDERTARGET_LANDSCAPE HRENDERTARGET(1)
//DeadCode JON 17Sep00 #define RENDERTARGET_MIRROR HRENDERTARGET(2)

#define NUM_PALETTES	8

typedef enum HMATRIX {MATRIX_PROJECTION,MATRIX_VIEWER,MATRIX_OBJECT} HMATRIX;
typedef enum HAXIS {AXIS_PITCH,AXIS_HEADING,AXIS_ROLL} HAXIS;
typedef enum LIGHTFLAG
{
    LF_ALPHA,
    LF_LIGHTSOURCE,
    LF_VERTEX,
    LF_FONT,
    LF_DEPTH,
    LF_AMBIENT, // must be in this order at the end so the < test can be done
    LF_LIGHTING,
    LF_SPECULAR,
    LF_MAPCOLBIT = 8, // must be a bit...  (	see SetVertexCol )
    LF_DUMMY = 0xff
} LIGHTFLAG;
typedef enum HINTS
{
    HINT_TRILINEAR,			HINT_BILINEAR,			HINT_NOBLEND,
    HINT_FULL_RES_TEXTURE,	HINT_HALF_RES_TEXTURE,	HINT_QUARTER_RES_TEXTURE,	HINT_EIGHTH_RES_TEXTURE,
    HINT_ALIASEDGES,		HINT_ALIASNONE,			HINT_CLIPPING_OFF,			HINT_CLIPPING_ON,
    HINT_2DRENDER,			HINT_3DRENDER,
    HINT_MAX_HINT
}
HINTS;
typedef enum TOGGLES
{
    TOGGLE_GLOBALALPHA=0,
    TOGGLE_GLOBALTRANSPARENCY=TOGGLE_GLOBALALPHA,
    TOGGLE_GLOBALLUMINOSITY=TOGGLE_GLOBALALPHA,
    TOGGLE_GLOBAL2DZDEPTH,
    TOGGLE_TEXTURE_ZBIAS,												//JON 14Aug00
    TOGGLE_TRANSPARENT_ZBIAS,											//JON 3Oct00
    TOGGLE_TEXTURE_QUALITY // only use when texture quality must be forced, otherwise use hint	//JON 19Jul00
}
TOGGLES;
typedef enum TRANSFORMFLAGS
{
    TF_NULL=0,
    TF_NOCOPY
}
TRANSFORMFLAGS;
typedef enum TCFLAGS
{
    TC_NULL			= 0x00000000,
    TC_RENDERTARGET	= 0x00000001
}
TCFLAGS;
typedef struct MAPDESC
{
    UWord		w,h;				//4
    UByteP		body;				//4
    UByteP		alpha;				//4
    UByteP		palette;			//4
    UByte		paletteindex:4,
                isMasked:1,
                blendType:3;
    HTEXTUREMAP	hTextureMap;		//4
    //21
}
MAPDESC;
typedef struct LIGHTINGDESC
{
    ULong		lowRGB;
    ULong		highRGB;
    ULong		ambientRGB;
    R3DCOLOUR	specularRGB;											//JON 11Sep00
    D3DVALUE	lowDot,highDot;
//	D3DVALUE	specularPower; // currently hardcoded...
}
LIGHTINGDESC;
enum TextIdType
{
    TIT_LOADED			= 0x0000,			// loaded in by rob's system
//	TIT_DYNAMIC			= 0x4000,			// dynamically built - not used, doh...
    TIT_LANDSCAPE		= 0x8000,			// landscape tiles.
    TIT_PLAIN			= 0xC000,			// plain coloured.
    TIT_MASK_INDEX		= 0x07FF,
    TIT_MASK_TYPE		= 0xC000,
    TIT_MASK_SECONDARY	= 0x3800,
    TIT_BASE_SECONDARY	= 0x0800,
    TIT_NULL			= 0xFFFF
}; // note that if value==0 then the texture needs uploading...

enum { MSK_NONE = 0, MSK_MASKED, MSK_TRANS };
enum	AlphaBlendTypes
{
    BLEND_NULL=0,
    BLEND_SRCALPHA_DESTSOLID,
    BLEND_ADDALPHA = BLEND_SRCALPHA_DESTSOLID,
    BLEND_SRCALPHA_DESTINVSRCALPHA,
    BLEND_AVERAGEALPHA = BLEND_SRCALPHA_DESTINVSRCALPHA,
    BLEND_SRCSOLID_DESTSOLID,
    BLEND_ADD = BLEND_SRCSOLID_DESTSOLID,
    BLEND_SRCRGB_DESTRBG,
    BLEND_MULTIPLY = BLEND_SRCRGB_DESTRBG,
    BLEND_SRCSOLID_DESTINVSRCALPHA,
    BLEND_GAY = BLEND_SRCSOLID_DESTINVSRCALPHA
};
typedef struct Material
{
    MAPDESC *p[3];				//12	//ImageMap ptrs
    float	tsW[3],tsH[3];		//24	//Texture coordinate scale factors
    ULong	isLand;				//4     //if a landscape it's number, else 0;
    UWord	uniqueTextID;		//2		//unique ID for this material
    UByte	materialFlags;		//1
    UByte	c;					//1		//Color index or the alpha value...
    UByte	f;					//1		//Flag 0==plain color, >0 gives number of texture stages for the material
    UByte	isMasked;			//1		//is the top level texture solid, masked or transparent
    UByte	pad0,pad1;			//2
    //48 == total bytes
    Material(UByte cc) // constructor with a colour index
    {
        c=cc;
        f=0x00;
        isLand=0;
        isMasked=MSK_NONE;
        uniqueTextID = TIT_PLAIN+cc;
        p[0]=p[1]=p[2]=NULL;
        tsW[0]=tsW[1]=tsW[2]=0;
        tsH[0]=tsH[1]=tsH[2]=0;
    }
    Material()
    {
        p[0]=p[1]=p[2]=NULL;
        tsW[0]=tsW[1]=tsW[2]=0;
        tsH[0]=tsH[1]=tsH[2]=0;
        isMasked=MSK_NONE;
        f=0;
        c=0;
        isLand=0;
        uniqueTextID = TIT_NULL;
    } // blank constructor - check
    Material(MAPDESC *p0,MAPDESC *p1=NULL,MAPDESC *p2=NULL) // construct with imagemaps.
    {
        c=0;
        p[0]=p0;
        p[1]=p1;
        p[2]=p2;
        f=0x00;
//DEADCODE JON 2/16/00 		isMasked=(p[0]->isMasked || p[0]->alpha!=NULL)?0x01:0x00;
        if ( p[0]->isMasked )
        {
            isMasked=MSK_MASKED;
        }
        else
        {
            if ( p[0]->alpha!=NULL )
                isMasked=MSK_TRANS;
            else
                isMasked=MSK_NONE;
        }

        isLand=0;
        for (int i=2; i>=0; i--)
            if (p[i])
            {
                tsW[i]=1.f/float(p[i]->w);
                tsH[i]=1.f/float(p[i]->h);
                f++;
            }

//		if ( p[1] )
//			uniqueTextID = p[0]->hTextureMap + ((p[1]->hTextureMap<<11)&TIT_MASK_SECONDARY);
//		else
        uniqueTextID = p[0]->hTextureMap;
    }
}
HMATERIAL;

const HMATERIAL NULL_MATERIAL( UByte(0) ); // this can be used when a plain col is drawn using vertexcols or font colour
const HMATERIAL FONTCOL_MATERIAL( UByte(254) ); // this can be used when a plain col is drawn using vertexcols or font colour

inline ULong RGBMake(UByte r,UByte g,UByte b)
{
    return (ULong(r)<<16)+(ULong(g)<<8)+ULong(b);
}

//
// vertex structure that is equivalent to
// the D3DVERTEX struct with some overloaded
// members added to match our DoPointStruc
//
//typedef float D3DVALUE, *LPD3DVALUE;

class TextCoords
{
public:
    union
    {
        SWord x;
        D3DVALUE u;
    };		// the x texture coord
    union
    {
        SWord y;
        D3DVALUE v;
    };		// the y texture coord
};

typedef D3DVECTOR R3DVECTOR;

class R3DVERTEX
{
public:
//	typedef union INTFLOAT {D3DVALUE f; SLong i;} INTFLOAT;
    // untransformed	transformed

    union
    {
        D3DVALUE x;
        D3DVALUE sx; /*INTFLOAT bodyx;*/
    };	// xval
    union
    {
        D3DVALUE y;
        D3DVALUE sy; /*INTFLOAT bodyy;*/
    };	// yval
    union
    {
        D3DVALUE z;
        D3DVALUE sz; /*INTFLOAT bodyz;*/
    };	// zval
    union
    {
        D3DVALUE nx;
        D3DVALUE rhw;
    };			// normal x or reciprical of homegenized w
    union
    {
        D3DVALUE ny;
        R3DCOLOUR color;
    };			// normal y or vertex col
    union
    {
        D3DVALUE nz;
        R3DCOLOUR specular;
    };		// normal z or vertex specular
    union
    {
        struct
        {
#pragma warning( disable : 4201)
            union
            {
                SWord ix;
                D3DVALUE tu;
            };		// the x texture coord
            union
            {
                SWord iy;
                D3DVALUE tv;
            };		// the y texture coord
        };
        TextCoords	t[1];									// will allow array indexing of textcoords
    };
//TEMPCODE JON 5/19/00 	R3DVERTEX& operator = ( const R3DVERTEX &source );
};

//TEMPCODE JON 5/18/00 #ifndef _R3DVERTEX_COPY_OPERATOR_DEFINED
//TEMPCODE JON 5/18/00 #define _R3DVERTEX_COPY_OPERATOR_DEFINED
//TEMPCODE JON 5/18/00 static R3DVERTEX& R3DVERTEX::operator = ( const R3DVERTEX &source ) // 1/2 save...
//TEMPCODE JON 5/18/00 {
//TEMPCODE JON 5/18/00 	memcpy( this, &source, sizeof( R3DVERTEX ) );
//TEMPCODE JON 5/18/00 	return *this;
//TEMPCODE JON 5/18/00 }
//TEMPCODE JON 5/18/00 #endif

class R3DVERTEX2 : public R3DVERTEX
{
public:
    union
    {
        D3DVALUE tu1;
        D3DVALUE dvTU1;
        SWord ix1;
    };
    union
    {
        D3DVALUE tv1;
        D3DVALUE dvTV1;
        SWord iy1;
    };
};

class _R3DVERTEX3 : public R3DVERTEX2
{
public: // we will steal these 8 bytes as we never use 3 textures
    ULong pad0;
    ULong pad1;
//DeadCode JON 30Oct00 	ULong clipcode;
//DeadCode JON 30Oct00 	UWord vertIndex;
//DeadCode JON 30Oct00 	UWord uploadPass;
//DeadCode JON 30Oct00 	union {D3DVALUE tu2; D3DVALUE dvTU2; SWord ix2;};
//DeadCode JON 30Oct00 	union {D3DVALUE tv2; D3DVALUE dvTV2; SWord iy2;};
};

#ifndef _NO_VERTEX_SHARING_HDR

const UWord UNIQUE_DOPOINTNUM = 0x0000;
#endif

enum DoPointFlags
{
    ALL_INVALID			= 0x00000000,
    TEXTURE_COUNT1		= 1,//0x00000001, // used to count number of textures needed - comes later	//0
    TEXTURE_COUNT2		= 1<<1,//0x00000002, // used to count number of textures needed - comes later	//1
    LANDSCAPE_TEXTURE	= 1<<2,//0x00000004, // used to flag a landscape texture - comes later			//2
    WORLD_COORDS		= 1<<3,//0x00000008,															//3
    TEXTURE_COORDS		= 1<<4,//0x00000010,															//4
    TEXTURE1_COORDS		= 1<<5,//0x00000020,															//5
//DeadCode JON 30Oct00 	TEXTURE2_COORDS		= 1<<6,//0x00000040,															//6
    LIGHT_NORMAL		= 1<<6,//0x00000080,															//7
    DO_CLIP				= 1<<7,//0x00000100, // added in at a later stage.								//8
    DO_SW_FOG			= 1<<8,//0x00000200, // as above												//9
    ALL_VALID			= (WORLD_COORDS|TEXTURE_COORDS|TEXTURE1_COORDS/*|TEXTURE2_COORDS*/|LIGHT_NORMAL),
    TEXTURE_COUNT_MASK	= (TEXTURE_COUNT1|TEXTURE_COUNT2),
    ALL_TEXT_COORDS		= (TEXTURE_COORDS|TEXTURE1_COORDS/*|TEXTURE2_COORDS*/),

    PLAINCOL_FLAG		= 1<<31,		// used outside... - MUST be top bit...
//	PLAINCOLSHIFT		= 31-7,			// the right shift to go to the lightnormal pos
//	PLAINCOLTEXTSHIFT	= 31-4,			// the right shift to go to the textureflag...
//DeadCode JON 20Sep00 	LIGHTMODE_FLAG		= 1<<30,		// used outside...
//DeadCode JON 20Sep00 	LIGHTMODE_FLAG1		= 1<<29,		// used outside...
//DeadCode JON 20Sep00 	LIGHTMODE_FLAG2		= 1<<28,		// used outside...
//DeadCode JON 20Sep00
//DeadCode JON 20Sep00 	LIGHTMODE_MASK		= (LIGHTMODE_FLAG|LIGHTMODE_FLAG1|LIGHTMODE_FLAG2),
//DeadCode JON 20Sep00 	LIGHTMODE_NUM_SHIFT = 28,
//DeadCode JON 20Sep00 	LIGHTMODE_NUM_MASK	= (1<<2)+(1<<1)+1,
//DeadCode JON 20Sep00 	LIGHTMODESHIFT		= 30-7,			// the right shift needed to move from lightmode flag to LIGHT_NORMAL.
//DeadCode JON 20Sep00 	LIGHTMODESHIFT1		= 29-7,			// the right shift needed to move from lightmode flag to LIGHT_NORMAL.
//DeadCode JON 20Sep00 	LIGHTMODESHIFT2		= 28-7,			// the right shift needed to move from lightmode flag to LIGHT_NORMAL.
};

#ifndef _NO_VERTEX_SHARING_HDR
class DoPointManagment
{
private:
    union
    {
#pragma warning( disable : 4201)
        ULong flags;
        struct
        {
#pragma warning( disable : 4201)
            ULong	flagBits:9,
                    lightModeCount:22, // ha ha my lazy cheat...
                    plainColFlag:1;
        };
    };
    UWord doPointNum;
public:
    DoPointManagment( void ) // constructor - set as a unique point
    {
        setUnique();
    }

    UWord getDoPointNum( void ) const
    {
        return doPointNum;
    }
    void setDoPointNum(const UWord newVal)
    {
        doPointNum = newVal;
    }

    ULong getFlags( void ) const
    {
        return flags;
    }
    ULong getLightModeCount( void ) const
    {
        return lightModeCount;
    }
    void setLightModeCount( ULong val )
    {
        lightModeCount = val;
    }
    void setUnique( void )
    {
        memset( this, 0, sizeof(DoPointManagment) );
    }//flags = ALL_INVALID; doPointNum = UNIQUE_DOPOINTNUM; }
    void setAllValid( void )
    {
        flagBits = ALL_VALID;
    }
    void setAllInvalid( void )
    {
        flags = ALL_INVALID;
    }
    bool isAllValid( void ) const
    {
        return flags==ALL_VALID;
    }
    void setInvalidWorld( void )
    {
        flags&=~WORLD_COORDS;
    }
    void setValidWorld( void )
    {
        flags|=WORLD_COORDS;
    }
    ULong isWorldValid( void ) const
    {
        return flags&WORLD_COORDS;
    }
    void setInvalidTexture( void )
    {
        flags&=~TEXTURE_COORDS;
    }
    ULong isTextureValid( void ) const
    {
        return flags&TEXTURE_COORDS;
    }
    void setInvalidTexture1( void )
    {
        flags&=~TEXTURE1_COORDS;
    }
    ULong isTexture1Valid( void ) const
    {
        return flags&TEXTURE1_COORDS;
    }
//DeadCode JON 30Oct00 	void setInvalidTexture2( void )			{ flags&=~TEXTURE2_COORDS; }
//DeadCode JON 30Oct00 	ULong isTexture2Valid( void ) const		{ return flags&TEXTURE2_COORDS; }
    void setInvalidNormal( void )
    {
        flags&=~LIGHT_NORMAL;
    }
    ULong isNormalValid( void ) const
    {
        return flags&LIGHT_NORMAL;
    }
    void addToFlags( const int i )
    {
        flags+= i;
    }
    void clearLightModeFlags( void )
    {
        lightModeCount = 0;
    }
//DeadCode JON 20Sep00 		flags&=~LIGHTMODE_MASK; }

};
#endif

class DoPointStruc :
/*#ifndef _INSIDE_LIB3D_
    protected R3DVERTEX2
#else */
    public R3DVERTEX2
/* #endif */
{
public:
#ifndef _NO_VERTEX_SHARING_HDR
    // extra stuff for dopoints
    mutable DoPointManagment info;
    UWord uploadPass;// make the vertices of a sensible size
#endif
/* x0r strange. let it be default
    DoPointStruc& operator = ( const DoPointStruc& source ) // copy operator... - copy constructor slightly quicker...
    {
        memcpy( this, &source, sizeof( R3DVERTEX2 ) );
#ifndef _NO_VERTEX_SHARING_HDR
        info.setAllInvalid();
#endif
        return *this;
    }
*/
//DEADCODE JON 5/24/00 #pragma message ( __HERE__ "sort out this" )
//DEADCODE JON 5/24/00 	R3DVERTEX& operator + () {return *this;}					//RJS 19May00

    const R3DVERTEX2& getR3DVert() const
    {
        return *((R3DVERTEX2*)this);
    }

    // accessor functions
    void setPosition( const D3DVALUE newX, const D3DVALUE newY, const D3DVALUE newZ ) // set the physical position of the vertex
    {
        x = newX;
        y = newY;
        z = newZ;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }
    void setPosition( const D3DVALUE newX, const D3DVALUE newY ) // set the phusical pos - sets z to 0 - use for 2d renders
    {
        x = newX;
        y = newY;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }
    void getPosition( D3DVALUE &rx, D3DVALUE &ry, D3DVALUE &rz ) const
    {
        rx = x;
        ry = y;
        rz = z;
    }
    D3DVALUE getPosX( void ) const
    {
        return x;
    }
    D3DVALUE getPosY( void ) const
    {
        return y;
    }
    D3DVALUE getPosZ( void ) const
    {
        return z;
    }
    void setPosX( const D3DVALUE nx )
    {
        x = nx;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }

    void setPosY( const D3DVALUE ny )
    {
        y = ny;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }

    void setPosZ( const D3DVALUE nz )
    {
        z = nz;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }

    void incPosX( const D3DVALUE offset )
    {
        x += offset;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }

    void incPosY( const D3DVALUE offset )
    {
        y += offset;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }

    void incPosZ( const D3DVALUE offset )
    {
        z += offset;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }

    void incPos( const D3DVALUE xOff, const D3DVALUE yOff, const D3DVALUE zOff )
    {
        x+=xOff;
        y+=yOff;
        z+=zOff;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidWorld();
#endif
    }

    void setNormal( const R3DVECTOR& newVec )
    {
        memcpy( &nx, &newVec, sizeof( R3DVECTOR ) );
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidNormal();
#endif
    }

    void setNormal( const D3DVALUE newX, const D3DVALUE newY, const D3DVALUE newZ ) // set the normal vector on the vertex (used for lighting)
    {
        nx = newX;
        ny = newY;
        nz = newZ;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidNormal();
#endif
    }
    void setRHW( const D3DVALUE newrhw ) // for pre-transformed matrices
    {
        rhw = newrhw;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidNormal();
#endif
    }
    void getNormal( D3DVALUE &rx, D3DVALUE &ry, D3DVALUE &rz ) const
    {
        rx = nx;
        ry = ny;
        rz = nz;
    }
    void setVertexCol( const R3DCOLOUR & newCol ) // set a colour on the vertex - cannot be used in conjunction with normal info
    {
        color = newCol;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidNormal();
#endif
    }

    void setVertexCol( const D3DCOLOR newCol ) // set a colour on the vertex - cannot be used in conjunction with normal info
    {
        color = newCol;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidNormal();
#endif
    }


    D3DVALUE getNormalX( void ) const
    {
        return nx;
    }
    D3DVALUE getNormalY( void ) const
    {
        return ny;
    }
    D3DVALUE getNormalZ( void ) const
    {
        return nz;
    }

//DeadCode JON 30Jun00 	R3DCOLOUR getVertexCol( void ) const // get a colour off a vertex - cannot be used in conjunction with normal info
//DeadCode JON 30Jun00 	{
//DeadCode JON 30Jun00 		return color;
//DeadCode JON 30Jun00 	}

    D3DCOLOR getVertexCol( void ) const // get a colour off a vertex - cannot be used in conjunction with normal info
    {
        return ((D3DCOLOR)color);
    }


    void setIMapCoords( const SWord newX, const SWord newY ) // set the image map coords for 1st texture
    {
        ix = newX;
        iy = newY;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidTexture();
#endif
    }
    void getIMapCoords( SWord &rx, SWord &ry ) const
    {
        rx = ix;
        ry = iy;
    }
    SWord getIMapX( void  ) const
    {
        return ix;
    }
    SWord getIMapY( void  ) const
    {
        return iy;
    }
    void setIMapCoords1( const SWord newX, const SWord newY ) // set the image map coords for 2nd texture
    {
        ix1 = newX;
        iy1 = newY;
#ifndef _NO_VERTEX_SHARING_HDR
        info.setInvalidTexture1();
#endif
    }
    void getIMapCoords1( SWord &rx, SWord &ry ) const
    {
        rx = ix1;
        ry = iy1;
    }
    SWord getIMapX1( void  ) const
    {
        return ix1;
    }
    SWord getIMapY1( void  ) const
    {
        return iy1;
    }
//DeadCode JON 30Oct00 	void setIMapCoords2( const SWord newX, const SWord newY ) // set the image map coords for 3rd texture
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		ix2 = newX;
//DeadCode JON 30Oct00 		iy2 = newY;
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING_HDR
//DeadCode JON 30Oct00 		info.setInvalidTexture2();
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 	}
//DeadCode JON 30Oct00 	void getIMapCoords2( SWord &rx, SWord &ry ) const
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		rx = ix2;
//DeadCode JON 30Oct00 		ry = iy2;
//DeadCode JON 30Oct00 	}
//DeadCode JON 30Oct00 	SWord getIMapX2( void  ) const
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		return ix2;
//DeadCode JON 30Oct00 	}
//DeadCode JON 30Oct00 	SWord getIMapY2( void  ) const
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		return iy2;
//DeadCode JON 30Oct00 	}

};

class SVertex : public DoPointStruc
{
    friend class CLib3D;
public:
//DEADCODE JON 5/24/00 	union
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		R3DVERTEX3		r3dvert;
//DEADCODE JON 5/24/00 		R3DVERTEX		d3dtlvert;
//DEADCODE JON 5/24/00 		R3DVERTEX2		d3dtlvert2;
//DEADCODE JON 5/24/00 		R3DVERTEX3		d3dtlvert3;
//DEADCODE JON 5/24/00 	};
    SVertex *pNext;
#ifndef _NO_VERTEX_SHARING_HDR
    SVertex *identical;
#endif
    R3DMATRIX_VAL hw;	// the homegenous w
    ULong clipcode;
    UWord vertIndex;
    static UWord copyCount;
    enum COUNTFLAGS
    {
        ODD_FRAME=1<<15,
        EVEN_FRAME=1<<14,
        FRAME_MASK=ODD_FRAME+EVEN_FRAME,
        COUNT_MASK=~FRAME_MASK
    };


    SVertex( void )	// constuctor
    {
        pNext=NULL;
#ifndef _NO_VERTEX_SHARING_HDR
        identical = NULL;
#endif
    }

    bool operator== (const SVertex& o) const // equivalence
    {
        return (
                   x	==	o.x		&&
                   y	==	o.y		&&
                   z	==	o.z		&&
                   nx	==	o.nx	&&
                   ny	==	o.ny	&&
                   nz	==	o.nz	&&
                   tu	==	o.tu	&&
                   tv	==	o.tv	&&
                   tu1	==	o.tu1	&&
                   tv1	==	o.tv1	&&
//DeadCode JON 30Oct00 			tu2	==	o.tu2	&&
//DeadCode JON 30Oct00 			tv2	==	o.tv2	&&
                   hw	==	o.hw	);
    }

    bool operator!= ( const SVertex& o) const
    {
        return ( !(*this==o) );
    }

    SVertex& operator= ( const DoPointStruc& source ) // copy operator...
    {
        memcpy( this, &source, sizeof( DoPointStruc ) );
#ifndef _NO_VERTEX_SHARING_HDR
        source.info.setAllValid();
#endif
        return *this;
    }

    static void CountAndCopyReset( void )
    {
#ifndef _NO_VERTEX_SHARING_HDR
        //		copyCount = 0;
        if ( copyCount&ODD_FRAME ) // was the last frame odd or even?
        {
            copyCount=EVEN_FRAME;
        }
        else
        {
            copyCount=ODD_FRAME;
        }
#endif
    }

    void CountAndCopy( const DoPointStruc& source )
    {
#ifndef _NO_VERTEX_SHARING_HDR

        if ( !( source.info.getDoPointNum() & (copyCount&FRAME_MASK) ) )
        {
            // this point hasn't been processed this frame
            source.info.setDoPointNum( ++copyCount );
            source.info.setAllInvalid();
        }
        memcpy( this, &source, sizeof( DoPointStruc ) );
        source.info.setAllValid();
        info.setDoPointNum( info.getDoPointNum()&COUNT_MASK );
#ifndef NDEBUG
        if ( copyCount == 1024 )
            INT3; // overrun the buffer...
#endif
#else
        memcpy( this, &source, sizeof( DoPointStruc ) );
#endif
    }

    void Transform( const R3DMATRIX* mat )
    {
//DEADCODE JON 5/24/00 		D3DVALUE x = r3dvert.x; // temporary store
//DEADCODE JON 5/24/00 		D3DVALUE y = r3dvert.y;
//DEADCODE JON 5/24/00 		D3DVALUE z = r3dvert.z;
//DEADCODE JON 5/24/00
//DEADCODE JON 5/24/00 		r3dvert.x	= mat->_11*x + mat->_21*y + mat->_31*z + mat->_41;
//DEADCODE JON 5/24/00 		r3dvert.y	= mat->_12*x + mat->_22*y + mat->_32*z + mat->_42;
//DEADCODE JON 5/24/00 		r3dvert.z	= mat->_13*x + mat->_23*y + mat->_33*z + mat->_43;
//DEADCODE JON 5/24/00 		hw			= mat->_14*x + mat->_24*y + mat->_34*z + mat->_44;
        R3DMATRIX_VAL tx = x; // temporary store
        R3DMATRIX_VAL ty = y;
        R3DMATRIX_VAL tz = z;

        x	= mat->_11*tx + mat->_21*ty + mat->_31*tz + mat->_41;
        y	= mat->_12*tx + mat->_22*ty + mat->_32*tz + mat->_42;
        z	= mat->_13*tx + mat->_23*ty + mat->_33*tz + mat->_43;
        hw	= mat->_14*tx + mat->_24*ty + mat->_34*tz + mat->_44;
    }

    void VolumetricSphere( D3DVALUE& radius) // scale the point if it is the center of a sphere - the point should have been transformed by both the view and object matrices.
    {
        // Just bring the sphere forward by the radius...
        //...must be called after the vertex has been transformed to the viewer
//DEADCODE JON 5/24/00 		D3DVALUE	oldZ = r3dvert.z;
//DEADCODE JON 5/24/00 		r3dvert.z -= radius;
//DEADCODE JON 5/24/00
//DEADCODE JON 5/24/00 		D3DVALUE fudgeScale = r3dvert.z/oldZ;
//DEADCODE JON 5/24/00 		radius *= fudgeScale;
//DEADCODE JON 5/24/00 		r3dvert.x *= fudgeScale;
//DEADCODE JON 5/24/00 		r3dvert.y *= fudgeScale;

        D3DVALUE	oldZ = z;
        z -= radius;

        D3DVALUE fudgeScale = z/oldZ;
        radius *= fudgeScale;
        x *= fudgeScale;
        y *= fudgeScale;

    }

};

typedef SVertex Lib3DPoint;

//typedef DWORD D3DCOLOR, *LPD3DCOLOR;

//DEADCODE JON 5/24/00 struct R3DTLVERTEX
//DEADCODE JON 5/24/00 {
//DEADCODE JON 5/24/00 	union {D3DVALUE sx; D3DVALUE dvSX;};
//DEADCODE JON 5/24/00 	union {D3DVALUE sy; D3DVALUE dvSY;};
//DEADCODE JON 5/24/00 	union {D3DVALUE sz; D3DVALUE dvSZ;};
//DEADCODE JON 5/24/00 	union {D3DVALUE rhw; D3DVALUE dvRHW;};
//DEADCODE JON 5/24/00 	union {D3DCOLOR color; D3DCOLOR dcColor;};
//DEADCODE JON 5/24/00 	union {D3DVALUE tu; D3DVALUE dvTU; SWord ix;};
//DEADCODE JON 5/24/00 	union {D3DVALUE tv; D3DVALUE dvTV; SWord iy;};
//DEADCODE JON 5/24/00 };
struct _DDCOLORKEY;
typedef _DDCOLORKEY DDCOLORKEY;
struct ROWANSURFACEDESC
{
    ULong	dwSize;
    ULong	dwFlags;
    ULong	dwHeight;
    ULong	dwWidth;
    union
    {
        ULong	lPitch;
        ULong dwLinearSize;
    };
    ULong	dwBackBufferCount;
    union
    {
        ULong dwMipMapCount;
        ULong dwRefreshRate;
    };
    ULong	dwAlphaBitDepth;
    ULong	dwReserved;
    void*	lpSurface;
    union
    {
        DDCOLORKEY ddckCKDestOverlay;
        ULong dwEmptyFaceColor;
    };
    DDCOLORKEY    ddckCKDestBlt;
    DDCOLORKEY    ddckCKSrcOverlay;
    DDCOLORKEY    ddckCKSrcBlt;
    DDPIXELFORMAT ddpfPixelFormat;
    DDSCAPS2      ddsCaps;
    ULong	dwTextureStage;
};
struct UIDrivers
{
    ULong 	size;
    ULong 	numDrivers;

    struct UIDriver
    {
        SByte	name[MAX_TEXT_LENGTH];
        HDRIVER hDriver;
    }
    driver[MAX_DRIVERS];
};

struct UIModes
{
    ULong	size;
    ULong 	numModes;
    struct UIModeInfo
    {
        ULong width,height,bpp;
        HMODE hMode;
    }
    mode[MAX_MODES];
};

class LIB3D_API CLib3D
{
public:
    //IUnknown methods
    virtual HRESULT	QueryInterface(REFIID,void**)=0;
    virtual ULong	AddRef()=0;
    virtual ULong	Release()=0;

    //Initialisation & configuration routines
    virtual HRESULT	Initialise(const HWND&, const ULong* sqrtTable)=0;
    virtual HRESULT	GetDrivers(UIDrivers&)=0;
    virtual HRESULT	GetModes(const HDRIVER&,UIModes&)=0;
    virtual HRESULT GetDefaultDriverAndMode(HDRIVER&,HMODE&)=0;

    virtual	HRESULT	SetDriverAndMode(const HDRIVER&,const HMODE&,const HWND&)=0;
    virtual HRESULT RestoreDisplayMode()=0;
    virtual HRESULT ChangeDisplaySettings(HWND,SWord,SWord,bool)=0;

    //2D interface methods
    virtual	HRESULT ScreenSwap()=0;
    virtual HRESULT SetPaletteTable(UByte*)=0;
    virtual HRESULT GetSurfaceDesc(ROWANSURFACEDESC*)=0;

    //3D interface methods
    virtual	HRESULT BeginScene(const HRENDERTARGET &)=0;
    virtual HRESULT End3DScene()=0;
    virtual HRESULT EndScene()=0;
    virtual HRESULT ClearTargetZ()=0;

    virtual HRESULT PushMatrix(const HMATRIX&)=0;
    virtual HRESULT PopMatrix(const HMATRIX&)=0;
    virtual HRESULT SetMatrix(const HMATRIX&,const R3DMATRIX&)=0;
    virtual HRESULT GetMatrix(const HMATRIX&,R3DMATRIX&)=0;
    virtual HRESULT LoadIdentity(const HMATRIX&)=0;
    virtual HRESULT Rotate(const HMATRIX&,const HAXIS&,const Angles&)=0;
    virtual HRESULT Scale(const HMATRIX&,const D3DVALUE&)=0;
    virtual HRESULT Scale(const HMATRIX&,const D3DVECTOR&)=0;
    virtual HRESULT Translate(const HMATRIX&,const D3DVECTOR&)=0;
    virtual HRESULT BodyToScreen(const R3DVERTEX&,D3DVALUE&,D3DVALUE&,D3DVALUE&,D3DVALUE* distAtZ=NULL)=0;//RJS 07Feb00
    virtual HRESULT Transform(const HMATRIX&,DoPointStruc&)=0;
    virtual HRESULT BackProjectViewCone(COORDS3D*)=0;

    virtual HRESULT VisibleCheck(D3DVECTOR*,ULong,ULong*)=0;
    virtual HRESULT VisibleCheck(D3DVECTOR*,D3DVALUE*,ULong,ULong*)=0;
//DEADCODE JON 5/24/00 	virtual HRESULT VisibleCheck(R3DVERTEX*,ULong,ULong*)=0;
    virtual HRESULT VisibleCheck(DoPointStruc*,ULong,ULong*)=0;

    virtual HRESULT SetProjectionMatrix(const Angles& fov,const D3DVALUE& aspect,const D3DVALUE& zN,const D3DVALUE& zF,const bool noFogInScene = false)=0;
    virtual HRESULT SetProjectionMatrix(const Angles& fov,const D3DVALUE& zN,const D3DVALUE& zF,const bool noFogInScene = false)=0;	//JON 6Oct00
    virtual HRESULT SetFogColour(const ULong&)=0;
    virtual HRESULT SetFontColour(const ULong&)=0;
    virtual void	EnableFogging(bool)=0;


    virtual HRESULT SetAmbientLighting(LIGHTINGDESC)=0;
    virtual HRESULT SetObjectLighting(LIGHTFLAG&)=0;
    virtual HRESULT SetLightVector(D3DVALUE,D3DVALUE,D3DVALUE)=0;
    virtual	HRESULT GetMaxLandDotProduct(D3DVALUE&)=0;

    virtual HRESULT SetGlobal(const TOGGLES&,const ULong)=0;
    virtual HRESULT SetGlobal(const TOGGLES&,ULong*)=0;
    virtual HRESULT IncGlobal(const TOGGLES&)=0;
    virtual HRESULT DecGlobal(const TOGGLES&)=0;

    virtual	HRESULT CreateTexture(MAPDESC*,const TCFLAGS&)=0;
//DeadCode JON 17Sep00 	virtual HRESULT UploadTexture( const UWord&)=0;
    virtual HRESULT UploadTexture()=0;
    virtual HRESULT ReduceLandQuality(UWord& sourceTextIndex, UWord& destTextIndex )=0;	//JON 6/6/00


    virtual HRESULT AllocateLandscapeTextures()=0;
    virtual HRESULT FreeLandscapeTextures()=0;
    virtual HRESULT GetLandscapeTextureCount(SLong&,SLong&,SLong&,SLong&,
            SLong&,SLong&,SLong&,SLong&)=0;
    virtual HRESULT GetLandscapeTextureOnScreenMax(SLong&,SLong&,SLong&,SLong&,	//JON 31Jul00
            SLong&,SLong&,SLong&,SLong&)=0;

    virtual HRESULT	FreeLandscapeTexture(UWord)=0;
    virtual HRESULT	AllocateLandscapeTexture(UWord,UWord&)=0;

    virtual HRESULT SetMaterial(UWord,MAPDESC *pmap=NULL)=0; // set to use a landscape material
    virtual HRESULT SetMaterial(const HMATERIAL& mat)=0; // set to use a non landscape material

//DEADCODE JON 5/19/00 	virtual HRESULT BeginPoly(const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginPoly(const HMATERIAL&,const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginPoly(const HMATERIAL&,const ULong&,R3DTLVERTEX*&)=0;
    virtual Lib3DPoint* BeginPoly(const ULong&)=0; // assume the material is already set.
    virtual Lib3DPoint* BeginPoly( const HMATERIAL& mat, const ULong& vertexCount )=0;
    virtual HRESULT EndPoly()=0;

//DEADCODE JON 5/19/00 	virtual HRESULT BeginStrip(const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginStrip(const HMATERIAL&,const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginStrip(const HMATERIAL&,const ULong&,R3DTLVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT EndStrip()=0;

//DEADCODE JON 5/19/00 	virtual HRESULT BeginFan(const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginFan(const HMATERIAL&,const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginFan(const HMATERIAL&,const ULong&,R3DTLVERTEX*&)=0;
    virtual Lib3DPoint* BeginFan( const ULong& vertexCount )=0;
    virtual Lib3DPoint* BeginFan( const HMATERIAL& mat, const ULong& vertexCount )=0;
    virtual HRESULT EndFan()=0;

//DEADCODE JON 5/22/00 	virtual HRESULT DrawSphere(const HMATERIAL&,const R3DVERTEX&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;
    virtual HRESULT DrawSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;
    virtual HRESULT DrawTransformedSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;//RJS 20Mar00
//DEADCODE JON 5/22/00 	virtual HRESULT DrawLine(const HMATERIAL&,const R3DVERTEX&,const R3DVERTEX&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT DrawLine(const HMATERIAL&,const R3DTLVERTEX&,const R3DTLVERTEX&)=0;
    virtual HRESULT DrawLine(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&)=0;
    virtual HRESULT DrawTransformedLine(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&)=0;

//DeadCode JON 19Oct00 	virtual HRESULT DrawPoint(const HMATERIAL&,const DoPointStruc&)=0;

    virtual HRESULT	GiveHint(const HINTS&)=0;

//DEADCODE JON 5/22/00 	virtual HRESULT DrawCylinder(const HMATERIAL&,const R3DVERTEX&,const R3DVERTEX&,
//DEADCODE JON 5/22/00 								const D3DVALUE&,const SWord,const SWord,const SWord,const SWord)=0;//RJS 14Feb00
    virtual HRESULT DrawCylinder(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&,
                                 const D3DVALUE&,const SWord,const SWord,const SWord,const SWord)=0;//RJS 14Feb00
    virtual	HRESULT CylinderOffsets(const DoPointStruc&,const DoPointStruc&,const D3DVALUE&,D3DVALUE&,D3DVALUE&,DoPointStruc&)=0;
    virtual	HRESULT DrawTransformedCylinder(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const SWord,const SWord,const SWord,const SWord)=0;

    virtual HRESULT TestPoly(const HMATERIAL&)=0;
    virtual HRESULT UnloadTexture( MAPDESC* )=0;
    virtual HRESULT LoadBMP(UByte*)=0;
    virtual void	SetFogValues( const D3DVALUE& FogStart, const D3DVALUE& FogEnd )=0;

    virtual	void	GivePolyCount(int&)=0;						//RJS 23Mar00
    virtual	void	GetTextureRAM(ULong&)=0;					//RJS 24Mar00
    virtual ULong	GetFreeVideoMemory()=0;										//JON 10Jul00

    virtual	HRESULT DoFade( D3DCOLOR fadeCol, UByte fadeDepth )=0;			//JON 4/11/00
    virtual	HRESULT DoWhiteOut( const D3DCOLOR&, const UByte&, const D3DVALUE&,  const D3DVALUE&, const D3DVALUE&)=0;//RJS 20Apr00

    virtual	HRESULT FlushAsBackground( void )=0;							//JON 4/19/00
    virtual	HRESULT GetZDepth( ULong& )=0;									//RJS 3/5/00
    virtual int ScreenShot( BITMAPINFOHEADER* pFile,void* imagebuffer=NULL )=0;//returns output data size

    virtual HRESULT DrawQuadSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;//RJS 06Jun00
    virtual HRESULT DrawPivotedSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;//RJS 06Jun00

    virtual HRESULT SetMirrorTexture( const HMATERIAL& )=0;						//JON 3Jul00
//DeadCode JON 17Sep00 	HRESULT UploadMirror( void )
//DeadCode JON 17Sep00 	{
//DeadCode JON 17Sep00 		return UploadTexture( /*0*/ );
//DeadCode JON 17Sep00 	}

    virtual HRESULT Wipe( const D3DCOLOR )=0;							//JON 4Jul00

    virtual HRESULT SetGamma( double gammaAmount )=0;					//JON 12Jul00
    virtual HRESULT SetGammaLevel( ULong val )=0;						//JON 12Jul00
    virtual HRESULT UploadAsDitherTexture( MAPDESC *pmap )=0;						//JON 26Jul00
    virtual HRESULT UploadAsMipMapLevel( MAPDESC *destination, MAPDESC *source, int level )=0;		//JON 8Aug00

    virtual void GetDiagnosticString( char* &theString )=0;						//JON 22Aug00

    virtual HRESULT SetNearClipPlane( D3DVALUE dist )=0;								//JON 29Aug00
    virtual HRESULT SetFarClipPlane( D3DVALUE dist )=0;									//JON 29Aug00
    virtual void	SetMasterShading( LIGHTFLAG& lf )=0;							//JON 29Sep00

    virtual HRESULT	DrawPoint( const HMATERIAL&, const DoPointStruc& )=0;				//JON 19Oct00
    virtual HRESULT	DrawTransformedPoint( const HMATERIAL&, const DoPointStruc& )=0;	//JON 19Oct00
    virtual void GetViewPortDimensions( D3DVALUE &sx, D3DVALUE &sy, D3DVALUE &cx, D3DVALUE &cy ) = 0;	//JON 19Oct00
    virtual void ResetClipDistances( void ) = 0;						//JON 23Oct00

    virtual void GetTransformedLightColour( R3DVERTEX& vertex, const LIGHTFLAG lf ) = 0;	//JON 7Nov00
};

LIB3D_API CLib3D *Lib3DCreate(const GUID);


#ifndef warnmsg
#define _XSTR(x)         #x
#define TOSTR(x)        _XSTR(x)

#define __HERE__	__FILE__ "(" TOSTR(__LINE__) "): "
#define	warnmsg(text)	message(__HERE__ "                 " text)
#endif
#pragma warnmsg("defining GUIDs")
class Lib3D : public CLib3D
{
public:
    typedef R3DVERTEX D3DTLVERTEX;
    typedef R3DVERTEX2 D3DTLVERTEX2;
    typedef _R3DVERTEX3 D3DTLVERTEX3;

    friend LIB3D_API CLib3D *Lib3DCreate(const GUID);



    struct	EnumNameEntry
    {
        enum	{MAX_LEN_INC_TERMINATOR=32};
        char	enumnamespace[MAX_LEN_INC_TERMINATOR];
        int		index;
    };

//these macros are intended to facilitate the loading and saving of text based config files
#define	ENUM(name)			enum	name
#define	ENUMENTRY(name,val)	name=val
//#define	ENUM(name)			EnumNameEntry	name##_names=
//#define	ENUMENTRY(name,val)	{TOSTR(name),val}
    ENUM(Flags)
    {
        ENUMENTRY(F_NULL,						0x00000000),
                                   ENUMENTRY(F_WINDOWED,					0x00000001),
                                   ENUMENTRY(F_TNL,						0x00000002),
                                   ENUMENTRY(F_MMX,						0x00000004),
                                   ENUMENTRY(F_PAGELOCK,					0x00000008),
                                   ENUMENTRY(F_INSCENE,					0x00000010),
                                   ENUMENTRY(F_TEXTURECANBERENDERTARGET,	0x00000020),
                                   ENUMENTRY(F_TNL_EMULATION,				0x00000040),
                                   ENUMENTRY(F_NOCLIPPING,					0x00000080),
                                   ENUMENTRY(F_VERTEXFOG,					0x00000100),
                                   ENUMENTRY(F_SLOWCOPY,					0x00000200),
                                   ENUMENTRY(F_VSLOWCOPY,					0x00000400),
                                   ENUMENTRY(F_STIPPLEALPHA,				0x00000800),
                                   ENUMENTRY(F_CANTMANAGETEXTURES,			0x00001000),
                                   ENUMENTRY(F_CANTBLENDTEXTURES,			0x00002000),
                                   ENUMENTRY(F_CANTVALIDATEDEVICE,			0x00004000),
                                   ENUMENTRY(F_FAKE_W,						0x00008000),
                                   ENUMENTRY(F_16BIT_W,					0x00010000)
    };
#undef	ENUM
#undef	ENUMENTRY
    typedef enum TEXFMT
    {
        TF_NORM=0,
        TF_NORMINIT,
        TF_MASK,
        TF_MASKINIT,
        TF_TRNS,
        TF_TRNSINIT,
        TF_LAND,
        TF_LANDINIT,
        TF_MAX
    }
    TEXFMT;

    typedef enum LIGHTS
    {
        LIGHT_SUNMOON=0,
        LIGHT_MAXLIGHTS=8
    }
    LIGHTS;

    typedef struct MyGUID
    {
        DWORD   Data1;
        WORD    Data2;
        WORD    Data3;
        BYTE    Data4[8];
    }
    MyGUID;

    enum NaffDriver
    {
        ND_FireGL1KPro=0,
        ND_RivaTNT,
        ND_GeoForce256,
        ND_ATIRagePro,
        ND_SavagePro3
    };

    typedef struct NaffDriverID
    {
        NaffDriver naffDriver;
        MyGUID ndGuid;
    }
    NaffDriverID;

private:
    void OpenDiags( void )												//JON 16/03/01
    {
        if ( !doDeviceDiags )
        {
            diagFile.open( "3D_Diags.txt", std::fstream::out );
            if ( diagFile.is_open() )
                doDeviceDiags = true;
        }
    }

    void CloseDiags( void )												//JON 16/03/01
    {
        if ( doDeviceDiags )
        {
            diagFile.close();
            doDeviceDiags = false;
        }
    }

    void OutDiagLine(const char*t ... )										//JON 16/03/01
    {
        if ( doDeviceDiags )
        {
            static char outBuff[256];
            //interface with vprintf
            //can be disabled.
            va_list	arglist;
            va_start(arglist, t);
            _vsnprintf(outBuff, 256, t,arglist);
            va_end(arglist);
            diagFile << outBuff << std::flush;
        }
    }

    bool doDeviceDiags;
    std::fstream diagFile;
    ULong* frameTimeBuff;
    LARGE_INTEGER* tickCountBuff;										//JON 19/03/01
    int curFrameTimeI;
    int frameTimeBuffSize;
    int minFrameTime;
    UWord bufferPass;													//JON 30Oct00
    UByte w_16bit;														//JON 20Oct00
    D3DVALUE aspectRatio;												//JON 6Oct00

    LIGHTFLAG masterLightFlag;													//JON 29Sep00
    D3DVALUE clipVal2D;													//JON 25Sep00

#ifdef _ONLY_ONE_LANSDCAPE_TEXTURE
    MAPDESC* landscapeTexture;
#endif
    ULong curMatTextureTypeFlags;										//JON 4Sep00
    ULong globTextureTypeFlags;											//JON 4Sep00

    R3DMATRIX_VAL zNearClip;		// the z at the near clip plane				//JON 29Aug00
    R3DMATRIX_VAL zFarClip;		// the z at the far clip plane				//JON 29Aug00
    // z at far clip plane = far clip plane...

    R3DMATRIX_VAL matrixNearPlane;	// the clip distances for the proj matrix	//JON 29Aug00
    R3DMATRIX_VAL matrixFarPlane;												//JON 29Aug00

    D3DVALUE lastFogStart;												//JON 24Aug00
    D3DVALUE lastFogEnd;												//JON 24Aug00

    char* diagString;													//JON 22Aug00
    ULong zBias;							// current zBias value..
    ULong tZBias;							// current transparent zBias value..//JON 3Oct00
    D3DVALUE tZBias_f;						// the float of the current tZBias..	//JON 3Oct00
    DWORD stateBlocks[MAX_TEXTURE_OPTS];	// for the stateblocks.
    D3DVALUE fogMul;						// multiplication factor for hw to get fog table lookup	//JON 13Jul00
    D3DVALUE zSMALL;						// smallest distance for one z value	//JON 13Jul00
    HMATERIAL mirrorTexture;				// where the mirror is put...
    SVertex dummyVertex;					// a dummy vertex to point to in the list
//DeadCode JON 20Sep00 	ULong lightModeFlag;						// store which lightmode (or colour) we are in...
    ULong lightModeCount;					// store which lightmode (or colour) we are in...
//DeadCode JON 28Oct00 	D3DVALUE guardBandMod;					// the guard band modification. JON 12Jun00
    D3DVALUE guardBandModLeft;
    D3DVALUE guardBandModRight;
    D3DVALUE guardBandModTop;
    D3DVALUE guardBandModBottom;
    bool hwClip;							//does the hardware need clipping
    unsigned long totAvailVidRam;			// the free memory after all required stuff is created
    LPDIRECTDRAW7 pDD7;						//current Direct Draw object
    LPDIRECTDRAWSURFACE7 pDDSP7;			//primary direct draw surface
    LPDIRECTDRAWSURFACE7 pDDSB7;			//direct draw surface to use as back buffer
    LPDIRECTDRAWSURFACE7 pDDSZ7;			//direct draw surface to use as zbuffer
    LPDIRECT3D7 pD3D7;						//current Direct 3D object
    LPDIRECT3DDEVICE7 pD3DDEV7;				//current Direct 3D Device
    LPDIRECT3DVERTEXBUFFER7 lpD3DVB7;		//current vertex buffer
    LPDIRECT3DVERTEXBUFFER7 gpD3DVB7;		//global vertex buffer
    LPDIRECT3DVERTEXBUFFER7 gpD3DVBL7;		//global vertex buffer for Lines etc (less text coords)

    D3DLIGHT7	d3dl7Lights[LIGHT_MAXLIGHTS];//list of light objects available

    bool updateLightVecs;					//does the light vec need transforming
    D3DVALUE sunTX;							//transformed sun light vectors 4 software version
    D3DVALUE sunTY;
    D3DVALUE sunTZ;
#ifndef PER_POINT_SPECULAR
    D3DVECTOR halfSunEye;					// used 4 specular lightshading	//JON 8Sep00
#endif

    RECT windowRect;
    RECT backBufferRect;

    SVertex* lastDoPoint[ MAX_DOPOINTS+1 ];								//JON 5/25/00
//DeadCode JON 4Sep00 	D3DVALUE	landscapeTextScaleX, landscapeTextScaleY;				//JON 5/26/00
//DeadCode JON 4Sep00 	D3DVALUE	landscapeTextOffsetX, landscapeTextOffsetY;				//JON 5/26/00
//DeadCode JON 5Sep00 	D3DVALUE landscapeTextScale;
//DeadCode JON 5Sep00 	D3DVALUE landscapeTextOffset;


    SLong		projMatStackPos;
    SLong		viewMatStackPos;
    SLong		objMatStackPos;
    SLong		transMatPos;
//TempCode JON 21Aug00 	R3DMATRIX 	projectionMatrix[MATRIX_STACK_SIZE*NUM_Z_LAYERS];//current projection matrix
    R3DMATRIX 	projectionMatrix[MATRIX_STACK_SIZE];//current projection matrix
    R3DMATRIX 	viewerMatrix[MATRIX_STACK_SIZE];	//current viewer matrix
    R3DMATRIX 	objectMatrix[MATRIX_STACK_SIZE];	//current object matrix
//DeadCode JON 7Sep00 	R3DMATRIX	transpMatrix[MATRIX_STACK_SIZE];	//matrices needed 4 transparent polys on TNL.
    R3DMATRIX	objViewMatrix;											//JON 7Sep00
    R3DMATRIX	combinedMatrix;
    R3DMATRIX	clippingMatrix;
//DeadCode JON 19Sep00 	ULong		combMatBits;
//TempCode JON 21Aug00 	ULong 		projMatBits[MATRIX_STACK_SIZE*NUM_Z_LAYERS];
//DeadCode JON 19Sep00 	ULong 		projMatBits[MATRIX_STACK_SIZE];
//DeadCode JON 19Sep00 	ULong 		viewMatBits[MATRIX_STACK_SIZE];
//DeadCode JON 19Sep00 	ULong 		objMatBits[MATRIX_STACK_SIZE];
    D3DVALUE	backProjectX;											//JON 11Sep00
    D3DVALUE	backProjectY;		// these multiplying projected x and y by these will give -ve eye space...

    HRENDERTARGET hCurrentRenderTarget;

    LPDIRECTDRAWSURFACE7	pDDS7MirrorRT;	// mirror render targ ( maybe texture too)
    LPDIRECTDRAWSURFACE7	pDDS7Mirror;	// mirror texture ( can be render targ too)
    LPDIRECTDRAWSURFACE7	pDDS7MirrorZB;	// mirror z buffer
    LPDIRECTDRAWSURFACE7	pDDS7LandRT;	// landscape render targ
    LPDIRECTDRAWSURFACE7	pDDS7LandZB;	// landscape z buffer
    RECT					mirrorRect,landRect;

    HWND	hwTop;
    HWND	hwOther;
    Flags	flags;
//DeadCode JON 12Jun00 	Flags	hwClipFlag;
    LIGHTFLAG lightflag;
    ULong	gFogColour;
    ULong	gFontColour;
    ULong	curCol;														//JON 15Jun00
    LIGHTINGDESC gLightingDesc;
    D3DVALUE gLightBase,gLightScale;
    UByte	globAlpha;

    R3DMATRIX_VAL nearZPlane;
    R3DMATRIX_VAL farZPlane;
    D3DVALUE& zFactor;
    D3DVALUE zDepth2d;													//JON 4/12/00
    ULong	zBuffer2d;													//JON 14Jul00

    Plane	clipPlanes[6];	//0=front,1=back,2=left,3=right,4=top,5=bottom
    bool	fRecalcClipPlanes;
    bool	fCombineMatrices;
    bool	addNewTransMat;

    HINTS	textureQuality,	masterTextureQuality;
    HINTS	textureBlending, masterTextureBlending;
    HINTS	edgeAlias,		masterEdgeAlias;
    HINTS	renderMode;

    struct DDMode
    {
        enum ModeFlags {MF_16BITZBUFFER=0,MF_24BITZBUFFER,MF_32BITZBUFFER};
        DDSURFACEDESC2 	ddsd;	//DDSURFACEDESC2 structure defining a supported display mode
        ULong			flags;
        DDMode 			*pNext;
    };
    struct DDDriver
    {
        SByte		name[MAX_TEXT_LENGTH];
        SByte		desc[MAX_TEXT_LENGTH];
        GUID FAR 	*pGUID;
        GUID		guid;
        HMONITOR 	hm;
        DDMode		*pModes;
        DDDriver 	*pNext;
    }
    *pDrivers;

    struct DDTextureFormat : public DDPIXELFORMAT											//JON 5Sep00
    {
        DDTextureFormat* next; // for a linked list of these...
        DDTextureFormat& operator = ( const DDPIXELFORMAT& source )
        {
            memcpy( this, &source, sizeof( DDPIXELFORMAT ) );
            return *this;
        }
        bool operator == ( const DDPIXELFORMAT& source )
        {
//			return DDPIXELFORMAT(*this) == source;
            UByte* t1 = (UByte*)this;
            UByte* t2 = (UByte*)&source;
            for (size_t i=0; i< sizeof( DDPIXELFORMAT ); i++ )
                if ( *t1++!=*t2++ ) return false;
            return true;
        }
    }
    *supportedTextFmt;

    DDSURFACEDESC2	primarySurfaceDesc;

//DeadCode JON 26Sep00 	UByte			paletteTable[256*3*NUM_PALETTES];
    UByte*	paletteTable;
#ifndef NO_HARD_TNL
    D3DMATERIAL7	materialTable[256];
    D3DMATERIAL7	materialMapped;
#endif
    LPVOID			normPalLookUp[NUM_PALETTES];
    LPVOID			maskPalLookUp[NUM_PALETTES];
    LPVOID			trnsPalLookUp[NUM_PALETTES];

    DDPIXELFORMAT	texFmt[TF_MAX];
    TEXFMT			texFmtReq;

    LPDIRECTDRAWSURFACE7	textureTable[MAX_TEXTURES];
    LPDIRECTDRAWSURFACE7	landTextures[MAX_LAND_TEXTURES];
    UByte					landTextRec[MAX_LAND_TEXTURES];

    SLong landTextureBandBase[LAND_TEXT_BANDS];							//JON 18Jul00
    SLong landTextureBandSize[LAND_TEXT_BANDS];							//JON 18Jul00
    SLong landTextureMaxOnScreen[LAND_TEXT_BANDS];						//JON 31Jul00


//DeadCode JON 18Jul00 	SLong&	num1024Textures,	num512Textures, // note these should be depriciated
//DeadCode JON 18Jul00 			num256Textures,		num128Textures, // set to point to part of table above in constuctor
//DeadCode JON 18Jul00 			num64Textures,		num32Textures,
//DeadCode JON 18Jul00 			num16Textures,		num8Textures;

    HMATERIAL hLastMaterial;
    bool fDoMasked;

    static bool fixZbuffer;

    ULong plainPolyVCnt;
//DeadCode JON 21Aug00 	ULong *textPolyVCntP;
    ULong textPolyVCnt;
//DeadCode JON 21Aug00 	ULong textPolyVCnt[NUM_Z_LAYERS];										//JON 14Aug00
    SPolygon *plainPolys,*transparentPolys,*localspheres;//JIM 22Jun100
    SPolygon *texturedPolys;
    // layer 1 of the textured polys is behind layer 2 if they are co-planer.
//DeadCode JON 21Aug00 	SPolygon* texturedPolys[NUM_Z_LAYERS];									//JON 14Aug00
//DeadCode JON 21Aug00 	SPolygon** texturedPolysP;

    SLine *aliasLineList;
    SLine *lineList;
    SPoint *pointList;

//DeadCode JON 5Sep00 	ULong gFreeRAM;
//DeadCode JON 5Sep00 	ULong g_usedRAM;

    alloc_handle_t *memPool;

    D3DVALUE fogStart;
    D3DVALUE fogEnd;

    ULong	currentZBufferDepth;

#ifndef NDEBUG
    bool insidePoly;
#endif

    static	D3DZBUFFERTYPE	prefZType;							//RJS 06Jun00
    static	AlphaBlendTypes	lastBlendType;
    static	DDMode selectedMode;
    static	DDDriver selectedDriver;
    static	ULong gMemCheck;
    static	ULong gRenderDepths;
    static	HRESULT lastError;
    static	D3DDEVICEDESC7 selectedDevice;
    static	WORD polyVerts[MAX_VERTICES];
//DEADCODE JON 5/19/00 	static	DWORD polyVertCount;
    static	DWORD vertexType;
//DEADCODE JON 5/19/00 	static	R3DVERTEX *polyVertArray;
    SPolygon* currentPoly;												//JON 5/19/00
//DEADCODE JON 5/24/00 	static	R3DTLVERTEX *polyVertArrayTL;
    static	R3DMATRIX IDENTITY;
//	static	ULong fastSqrtTable[0x10000];
    ULong* fastSqrtTable;
//DeadCode JON 13Oct00 	static SWord tableCode1[65536];
//DeadCode JON 13Oct00 	static SWord tableCode2[256];
    static	ULong refCnt;
    static	VPDESC vpDesc;
    //RJS 24Mar00
    static	DWORD	texturesTotalRAM;									//RJS 24Mar00

//DEADCODE JON 5/25/00 	static	R3DVERTEX	vertArray[MAX_VERTICES];
//DEADCODE JON 5/25/00 	static	R3DVERTEX2	vertArray2[MAX_VERTICES];
//DEADCODE JON 5/25/00 	static	R3DVERTEX3	vertArray3[MAX_VERTICES];

//DEADCODE JON 5/24/00 	static	R3DTLVERTEX tlVertArray[MAX_VERTICES];
    static	UByte fogTable[1024];
//DeadCode JON 7Sep00 	static	NaffDriverID naffDriverTable[];
//DeadCode JON 7Sep00 	static	int ND_Max;
    static R3DCOLOUR lightingTable[256];
    static R3DCOLOUR specularTable[256];
private:
    inline void NextLmFlag( void )
    {
//			LIGHTMODE_NUM_SHIFT = 29,
//			LIGHTMODE_NUM_MASK	= (1<<1)+1,
        lightModeCount++;
//DeadCode JON 20Sep00 		lightModeFlag >>= LIGHTMODE_NUM_SHIFT;
//DeadCode JON 20Sep00 		lightModeFlag++;
//DeadCode JON 20Sep00 		lightModeFlag&=LIGHTMODE_NUM_MASK;
//DeadCode JON 20Sep00 		lightModeFlag <<= LIGHTMODE_NUM_SHIFT;
    }
#pragma warnmsg("many of these functions don't need this ptr. 4035 will only squelch at TOP l")
#pragma warning(disable:4035)  // don't tell me there is no return value
#ifndef _NOT_IN_SAMPLE
    inline ULong SetToTopBit( ULong i )
    {
//#ifdef __GNUC__
        return( (i & (1<<31) )?-1:0  );
        /*#else
        		__asm
        		{
        			mov eax, i
        			sar eax, 31
        		}
        #endif*/
    }
#endif
#pragma warning(default:4035) // turn the message back on then.
    inline bool MemCmp(const void* a, const void* b, ULong size )
    {
        UByte* x = (UByte*)a;
        UByte* y = (UByte*)b;
        for (size_t i = 0; i<size; i++ )
        {
            if ( *x++!=*y++ )
                return false;
        }
        return true;
    }

    inline bool SamePlainMaterial(const Material& a,const Material& b)
    {
        return ( a.c==b.c );
    }

    inline bool SameMaterial(const Material& a,const Material& b)
    {
//DEADCODE JON 5/10/00 		if (a.isLand!=0)						return bool (a.isLand==b.isLand && a.p[1]==b.p[1]);
//DEADCODE JON 5/10/00 		if (a.f!=b.f)							return false;
//DEADCODE JON 5/10/00 		if (a.f==0)								return bool(a.c==b.c);
//DEADCODE JON 5/10/00 		if (a.p[0]!=b.p[0])						return false;
//DEADCODE JON 5/10/00 		if (a.p[1]!=b.p[1])						return false;
//DEADCODE JON 5/10/00 		if (a.p[2]!=b.p[2])						return false;
//DEADCODE JON 5/10/00 		return true;
        return (
                   a.uniqueTextID == b.uniqueTextID &&
                   a.p[1] == b.p[1] &&
                   a.materialFlags == b.materialFlags
               );
    }
    inline bool SameTransMat(const Material& a,const Material& b)
    {
//DEADCODE JON 5/10/00 		if (a.c!=b.c)							return false;
//DEADCODE JON 5/10/00 		if (a.f!=b.f)							return false;
//DEADCODE JON 5/10/00 		if (a.p[0]!=b.p[0])						return false;
//DEADCODE JON 5/10/00 		if (a.p[1]!=b.p[1])						return false;
//DEADCODE JON 5/10/00 		if (a.p[2]!=b.p[2])						return false;
//DEADCODE JON 5/10/00 		return true;
        return ( SameMaterial( a, b ) && a.c==b.c );
    }
    //
    // Approximate but fast 'r=1/p'
    //
    D3DVALUE FPInv(const D3DVALUE p) const
    {
        return 1.f/p;
    }
    //
    // Fast normal value to byte
    //
    SLong FPNormToByte(D3DVALUE p) const
    {
        p*=1024.f;
        SLong retval;
        FloatToInt(&retval,p);
        return retval;
    }
    //
    // Fast normal value to unsigned word
    //
    UWord FPNormToWord(const D3DVALUE p) const
    {
//		D3DVALUE n=p+1.0f;
//		SLong i=*(SLong*)&n;
//		if (i>=0x40000000)		i=0xFFFF;
//		else if (i<=0x3F800000)	i=0;
//		else 					i=(i>>7)&0xFFFF;
//		return UWord(i);
        if (p>=1.0f)		return 0xFFFF;
        else if (p<=0.f)	return 0x0000;
        return (UWord)(p*65535.0f);
    }

    ULong FPNormToLong(const D3DVALUE p) const
    {
        if (p>=1.0f)		return 0xFFFFFFFF;
        else if (p<=0.f)	return 0x00000000;
        return F2UL_Round(p*D3DVALUE(ULong(0xFFFFFFFF)));
    }

    ULong FPNormTo24Bit(const D3DVALUE p) const
    {
        if (p>=1.0f)		return 0x00FFFFFF;
        else if (p<=0.f)	return 0x00000000;
        return (ULong)(p*D3DVALUE(ULong(0x00FFFFFF)));
    }

    //
    // Fast floating point square root calc
    //
    D3DVALUE FastSqrt(D3DVALUE n) const
    {
#ifdef _NOT_IN_SAMPLE
        return D3DVALUE(sqrt( n ));
#else
        //Check for sqrt(0)
        if (FP_BITS(n)==0)
            return 0.0f;

        FP_BITS(n)=fastSqrtTable[(FP_BITS(n)>>8)&0xFFFF]|
                   ((((FP_BITS(n)-0x3F800000)>>1)+0x3F800000)&0x7F800000);

        return n;
#endif
    }
    //
    // Fast floating point inverse square root calc
    //
    D3DVALUE FastInvSqrt(D3DVALUE n) const
    {
#ifdef _NOT_IN_SAMPLE
        return D3DVALUE(1.0/sqrt( n ));
#else

        //Check for inv sqrt(0)
        if (FP_BITS(n)==0)
            return 0.0f;

        FP_BITS(n)=fastSqrtTable[(FP_BITS(n)>>8)&0xFFFF]|
                   ((((FP_BITS(n)-0x3F800000)>>1)+0x3F800000)&0x7F800000);

        SLong i=2*FP_ONE_BITS-*(SLong*)&n;

        D3DVALUE r=*(D3DVALUE*)&i;

        return r*(2.0f-n*r);
#endif
    }
    void NormalizeVector( D3DVALUE &x, D3DVALUE &y, D3DVALUE &z )
    {
        D3DVALUE magnitude = x*x + y*y + z*z;
        magnitude = FastInvSqrt( magnitude );
        x*=magnitude;
        y*=magnitude;
        z*=magnitude;
    }
    void NormalizeVector( D3DVALUE* vec )
    {
        D3DVALUE magnitude = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
        magnitude = FastInvSqrt( magnitude );
        vec[0]*=magnitude;
        vec[1]*=magnitude;
        vec[2]*=magnitude;
    }
    void NormalizeVector( D3DVECTOR& vec )
    {
        NormalizeVector( &vec.x );
    }

    //
    // Fast floating point to integer conversion
    //
    inline void FloatToInt(SLong *int_pointer,D3DVALUE f) const
    {
//#ifdef __GNUC__
        *int_pointer=round(f);
        /*#else
        	 	__asm	fld		f;
        		__asm	mov		edx,int_pointer;
        		__asm	frndint;
        		__asm	fistp	dword ptr [edx];
        #endif*/
    }
    inline SLong FPTiny(D3DVALUE v) const
    {
        if (v>-.00001f && v<.00001f)
            return 1;
        return 0;
    }
    // pos == location of one point on the plane
    // va & vb are two vectors that lie on the plane (NOTE: va & vb must not be colinear)
    void MakePlane(Plane *p,D3DVECTOR *pos,D3DVECTOR *va,D3DVECTOR *vb)
    {
        D3DVALUE mag;
        mag=1.f/(FastSqrt(va->x*va->x+va->y*va->y+va->z*va->z)*
                 FastSqrt(vb->x*vb->x+vb->y*vb->y+vb->z*vb->z));
        p->A=mag*(va->y*vb->z-va->z*vb->y);
        p->B=mag*(va->x*vb->z-va->z*vb->x);
        p->C=mag*(va->x*vb->y-va->y*vb->x);
        p->D=-(p->A*pos->x+p->B*pos->y+p->C*pos->z);
    };

    bool FZero(D3DVALUE f) const
    {
        SLong	val;
        FloatToInt(&val,f);
        return val==0;
    }
//DEADCODE JON 5/19/00 	ULong ClipCodeLRTB(D3DTLVERTEX *pV)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		ULong clipCode;
//DEADCODE JON 5/19/00 		D3DVALUE sz;
//DEADCODE JON 5/19/00 		FP_BITS(sz)=FP_ABS_BITS(pV->rhw);
//DEADCODE JON 5/19/00 		if (pV->sx<-sz)		clipCode=CLIP_LEFT;
//DEADCODE JON 5/19/00 		else if (pV->sx>sz)	clipCode=CLIP_RIGHT;
//DEADCODE JON 5/19/00 		else				clipCode=0UL;
//DEADCODE JON 5/19/00 		if (pV->sy<-sz)		clipCode+=CLIP_BOTTOM;
//DEADCODE JON 5/19/00 		else if (pV->sy>sz)	clipCode+=CLIP_TOP;
//DEADCODE JON 5/19/00 		return clipCode;
//DEADCODE JON 5/19/00 	}
//DEADCODE JON 5/19/00 	ULong ClipCodeTB(D3DTLVERTEX *pV)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		ULong clipCode;
//DEADCODE JON 5/19/00 		D3DVALUE sz;
//DEADCODE JON 5/19/00 		FP_BITS(sz)=FP_ABS_BITS(pV->rhw);
//DEADCODE JON 5/19/00 		if (pV->sy<-sz)		clipCode=CLIP_BOTTOM;
//DEADCODE JON 5/19/00 		else if (pV->sy>sz)	clipCode=CLIP_TOP;
//DEADCODE JON 5/19/00 		else				clipCode=0UL;
//DEADCODE JON 5/19/00 		return clipCode;
//DEADCODE JON 5/19/00 	}

//DEADCODE JON 5/19/00 	void TransformNormal(D3DVALUE& dvX,D3DVALUE& dvY,D3DVALUE& dvZ,const R3DMATRIX* pM)
//DEADCODE JON 5/19/00 	{
//DEADCODE JON 5/19/00 		D3DVALUE tx,ty,tz,tw;
//DEADCODE JON 5/19/00 		tw=1.f/pM->_44;
//DEADCODE JON 5/19/00 		tx=(pM->_11*dvX+pM->_21*dvY+pM->_31*dvZ)*tw;
//DEADCODE JON 5/19/00 		ty=(pM->_12*dvX+pM->_22*dvY+pM->_32*dvZ)*tw;
//DEADCODE JON 5/19/00 		tz=(pM->_13*dvX+pM->_23*dvY+pM->_33*dvZ)*tw;
//DEADCODE JON 5/19/00 		dvX=tx; dvY=ty; dvZ=tz;
//DEADCODE JON 5/19/00 	}

    inline D3DVALUE DotProduct(const D3DVALUE &ai, const D3DVALUE &aj, const D3DVALUE &ak, const D3DVALUE &bi, const D3DVALUE &bj, const D3DVALUE &bk)
    {
        return ai*bi+aj*bj+ak*bk;
    }

    inline bool	MatrixEqu( const R3DMATRIX &a, const R3DMATRIX &b )
    {
        return ( a==b );
//DeadCode JON 19Sep00 		for (ULong i=16,*aptr=(ULong*)&a,*bptr=(ULong*)&b;i!=0;aptr++,bptr++)
//DeadCode JON 19Sep00 			if (*aptr!=*bptr) return false;
//DeadCode JON 19Sep00 		return true;
    }
//deadcode
//deadcode		return ( a._11 == b._11 &&
//deadcode				 a._12 == b._12 &&
//deadcode				 a._13 == b._13 &&
//deadcode				 a._14 == b._14 &&
//deadcode				 a._21 == b._21 &&
//deadcode				 a._22 == b._22 &&
//deadcode				 a._23 == b._23 &&
//deadcode				 a._24 == b._24 &&
//deadcode				 a._31 == b._31 &&
//deadcode				 a._32 == b._32 &&
//deadcode				 a._33 == b._33 &&
//deadcode				 a._34 == b._34 &&
//deadcode				 a._41 == b._41 &&
//deadcode				 a._42 == b._42 &&
//deadcode				 a._43 == b._43 &&
//deadcode				 a._44 == b._44 );
//deadcode	}
    D3DVALUE Interp(D3DVALUE in,D3DVALUE out,D3DVALUE frac)
    {
        return in+(out-in)*frac;
    }
    void AddEdgeAliasing(SPolygon *poly);

    inline ULong EstimateTextureRAM(const MAPDESC *pmap)
    {
        ULong estRAM=0;
        ULong width,height;
        width=pmap->w;
        height=pmap->h;
        for (int i=textureBlending==HINT_TRILINEAR?3:1; i>0; i--)
        {
            estRAM+=width*height*2;
            width>>=1;
            height>>=1;
        }
        return estRAM;
    }

    inline void ALLOCATE_POLYGON( SPolygon* &p1, const ULong &p2 );

    inline void ALLOCATE_POLYGON_NOLINK( SPolygon* &p1, const ULong &p2 ); // allocates the polygon - doesn't link the verices tho, or set and and orcode

    inline void ALLOCATE_POLYGON_TNL( SPolygon* &p1, const ULong &p2 );

    inline void ADD_POLYGON( SPolygon* &l1, SPolygon* &p1 );

//DEADCODE JON 5/25/00 	inline void PROJECT_SETZ( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)

//DEADCODE JON 5/25/00 	inline void PROJECT_SPHERE( SPolygon* p1, const D3DVALUE& cx, const D3DVALUE& cy, const D3DVALUE& sx, const D3DVALUE& sy)//, const D3DVALUE& radius)

    inline void PROJECT_LINE( SLine* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy);

    inline void PROJECT_POINT( SVertex* pp, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy);

//DeadCode JON 27Sep00 	inline void PROJECT( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)

    inline void PROJECT( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy);

//DEADCODE JON 5/25/00 	inline void PROJECT_2D( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)

//TempCode JON 14Jul00 	inline void PROJECT_2DSETCOL( SPolygon* p1, D3DVALUE cx, D3DVALUE cy, D3DVALUE sx, D3DVALUE sy)

#ifndef NO_HARD_TNL
    inline void TnlTransSetPolyZ(SPolygon* poly);
#endif

//#pragma message ( __HERE__ "inline me" )
    inline void SetColAlpha( ULong &col, const UByte& val );

    inline void SetCol( ULong &col, const UByte alpha,const UByte red,const UByte green,const UByte blue )
    {
        UByte *t = (UByte*)(&col);
        t[0]=blue;
        t[1]=green;
        t[2]=red;
        t[3]=alpha;
    }

#pragma warnmsg ( "mask and shift can be quicker" )
    inline UByte GetColAlpha( const ULong col )		//RERUN: was UByte& - returned ref to by-value param (dangling)
    {
        UByte *t = (UByte*)(&col);
        return t[3];
    }


    inline void GetColRGB( const ULong col, UByte& r, UByte& g, UByte& b )
    {
        UByte *t = (UByte*)(&col);
        r = t[2];
        g = t[1];
        b = t[0];
    }

    inline void GetColARGB( const ULong col, UByte& a, UByte& r, UByte& g, UByte& b )
    {
        UByte *t = (UByte*)(&col);
        a = t[3];
        r = t[2];
        g = t[1];
        b = t[0];
    }


    // modulate the two bytes as if multiplying them both together after converting them to range from 0->1
    inline UByte ModulateByte( const UByte b1, const UByte b2 )
    {
        return UByte( UWord( ((b1*b2) + 0xFF) >>8 ) );
    }

    // modify a colour so that it is light by value lightCol (modulate I guess)
    // sets the alpha to the given value too
    inline void SetColLighting( D3DCOLOR &col, const D3DCOLOR lightCol, UByte alpha )
    {
        UByte *c = (UByte*)(&col);
        UByte *l = (UByte*)(&lightCol);
        c[3] = alpha;
        c[2] = ModulateByte( c[2], l[2] ); // red
        c[1] = ModulateByte( c[1], l[1] ); // green
        c[0] = ModulateByte( c[0], l[0] ); // blue
    }

    // modify a colour so that it is light by value lightCol (modulate I guess)
    inline void SetColLighting( D3DCOLOR &col, const D3DCOLOR lightCol )
    {
        UByte *c = (UByte*)(&col);
        UByte *l = (UByte*)(&lightCol);
        c[2] = ModulateByte( c[2], l[2] ); // red
        c[1] = ModulateByte( c[1], l[1] ); // green
        c[0] = ModulateByte( c[0], l[0] ); // blue
    }

    inline void DeRefAndNULL( IUnknown* &tmp )
    {
        if ( tmp != NULL )
        {
            int count = tmp->Release();
#ifndef NDEBUG
            if ( count != 0 )
                NOP;
#endif
//TempCode JON 11Jul00 			while ( count != 0)
//TempCode JON 11Jul00 			{
//TempCode JON 11Jul00 				count = tmp->Release();
//TempCode JON 11Jul00 			}
        }
        tmp = NULL;
    }


private:
    bool CkValidDevice( void );				//JON 16/03/01
    void ChangeRenderStateFog( float curFogStart, float curFogEnd );	//JON 22Aug00
    HRESULT SetUpRenderBlocks( void );									//JON 17Aug00
    HRESULT CopyMapToSurface( MAPDESC *pMapDesc,LPDIRECTDRAWSURFACE7 &pddsSurface );	//JON 8Aug00
    HRESULT _CreateTextureMap(MAPDESC *pMapDesc,LPDIRECTDRAWSURFACE7 &pddsTexture,SLong textureStage,bool isDither = false);	//JON 26Jul00
    HRESULT UpdateMipMaps( LPDIRECTDRAWSURFACE7 psrc );					//JON 11Jul00
    void SetNoRenderToTexture( void );									//JON 3Jul00
    bool GuardBandClipTest(SPolygon *poly);								//JON 12Jun00
    ULong GenGuardBandClipCode( const SVertex* pV, const D3DVALUE sz, const ULong prevFlags );	//JON 12Jun00
    ULong InlineGenGuardBandClipCode( const SVertex* pV, const D3DVALUE sz, const ULong prevFlags );	//JON 12Jun00

    void GetViewPort( D3DVALUE &sx, D3DVALUE &sy, D3DVALUE &cx, D3DVALUE &cy );	//JON 12Jun00

    HRESULT SoftwareImageCopy(
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
    );
    void InlineVertexTransform( SVertex* sVertex, const ULong flags, const LIGHTFLAG curLF );
    void TransformVertexAsRequired( SVertex* sVertex, const ULong flags, const LIGHTFLAG curLF );	//JON 5/25/00
    void CALC_FOG(SPolygon *p1);
    void Transform(const R3DVERTEX *pV,D3DTLVERTEX *pTV,R3DMATRIX *pM);
    ULong ClipCodeFBLRTB(D3DTLVERTEX *pV);
    ULong ClipCodeFBLRTB(SVertex *pV);									//JON 5/19/00
    ULong ClipCode2D(SVertex *pV);										//JON 25Sep00
    ULong ClipCodeLRTB(SVertex *pV);
    ULong ClipCodeTB(SVertex *pV);
    ULong ClipCodeTB2D(SVertex *pV);									//JON 25Sep00

    void UpdateLightVecs(void);	//JON 5/11/00

    HRESULT MakeMipLevel(LPDIRECTDRAWSURFACE7,LPDIRECTDRAWSURFACE7);
    void	CalculateClipPlanes();
//DeadCode JON 31Aug00 	void	ScaleTextureCoordinates(const HMATERIAL&, SPolygon* );//R3DVERTEX*,ULong);
    void	SetAntiAliasing( const HMATERIAL& mat );
    void	SetCurrentMaterial(const HMATERIAL&, const ULong flags);
    void	InlineSetCurrentMaterial(const HMATERIAL& mat, const ULong flags);	//JON 17Aug00
//DeadCode JON 17Aug00 	void 	SetTransCurrentMaterial(const HMATERIAL&);
//DeadCode JON 17Aug00 	void	SetPlainMaterial(/*const HMATERIAL&*/);						//JON 5/9/00
    void	CalcFog(D3DTLVERTEX& v);
    void	FillFogTable(D3DVALUE,D3DVALUE);

//	void	VertexSetCols( SVertex* sVertex, const D3DVERTEX* pv, const D3DCOLOR matCol );
    void	SetVertexCol( SVertex* sVertex, const LIGHTFLAG localLF );	//JON 5/19/00

    void	ClipSetCols(SVertex* &vi,SVertex* &vo,SVertex* &vc,double &frac);
    typedef void (*ClipFunction)(SVertex*,SVertex*,SVertex*,const ULong);
    SVertex*	DoClip( const SVertex* a, const SVertex* b, SVertex* out,ClipCode code, ClipFunction fn );
    void	ClipToFront(SVertex*,SVertex*,SVertex*,const ULong);
    void	ClipToBack(SVertex*,SVertex*,SVertex*,const ULong);
    void	ClipToLeft(SVertex*,SVertex*,SVertex*,const ULong);
    void	ClipToRight(SVertex*,SVertex*,SVertex*,const ULong);
    void	ClipToTop(SVertex*,SVertex*,SVertex*,const ULong);
    void	ClipToBottom(SVertex*,SVertex*,SVertex*,const ULong);
    void	GenericPolyClip(SPolygon* /*,const ULong*/);
    void	PolyClipFrontBack(SPolygon *poly);							//JON 13Jun00
    void	GenericLineClip(SLine*);//,const ULong);

    void	ClipToRight2D(SVertex*,SVertex*,SVertex*,const ULong);	//JON 25Sep00
    void	ClipToLeft2D(SVertex*,SVertex*,SVertex*,const ULong);	//JON 25Sep00
    void	ClipToTop2D(SVertex*,SVertex*,SVertex*,const ULong);	//JON 25Sep00
    void	ClipToBottom2D(SVertex*,SVertex*,SVertex*,const ULong);	//JON 25Sep00
    void	GenericPolyClip2D(SPolygon*);								//JON 25Sep00

//	void	ClipToLeft(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*,ULong*);
//	void	ClipToRight(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*,ULong*);
//	void	ClipToTop(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*,ULong*);
//	void	ClipToBottom(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*,ULong*);
//	void	GenericPolyClip(R3DTLVERTEX*,ULong*,ULong&,ULong*);

    void	CpuInfo();
    void	BuildSqrtTable();
    void	PreBuildTextures();
    HRESULT	CheckIfTextureCanBeRenderTarget();
    HRESULT IsSlowCopyRequired();
    HRESULT PerformVSlowCopy(LPDIRECTDRAWSURFACE7,LPDIRECTDRAWSURFACE7,LPRECT);
    HRESULT PerformSlowCopy(LPDIRECTDRAWSURFACE7,LPDIRECTDRAWSURFACE7,LPRECT);
    HRESULT HandleNaffDriver();
    void	CloseDown(bool legitimate=false);
    void	CombineMatrices();
    void	CombineTranspMat();
    HRESULT	TNLUploadMatrixes();			//jon 8/2/2000
//DeadCode JON 19Sep00 	ULong	MatrixFlags(R3DMATRIX*);
    HRESULT CreateTextureMap(MAPDESC*,LPDIRECTDRAWSURFACE7&,SLong);
    static	BOOL WINAPI DDEnumCallbackEx(GUID FAR *,LPSTR,LPSTR,LPVOID,HMONITOR);
    static	HRESULT WINAPI EnumModesCallback2(LPDDSURFACEDESC2,LPVOID);
    static	HRESULT CALLBACK EnumDevicesCallback(LPSTR,LPSTR,LPD3DDEVICEDESC7,LPVOID);
    static	HRESULT CALLBACK EnumRenderBitDepthsCallback(LPSTR,LPSTR,LPD3DDEVICEDESC7,LPVOID);
    static	HRESULT CALLBACK EnumZBufferCallback(LPDDPIXELFORMAT,LPVOID);
    static	HRESULT CALLBACK EnumTextureFormatsCallback(LPDDPIXELFORMAT,LPVOID);
    static	HRESULT CALLBACK MakeListTextureFormatsCallback(LPDDPIXELFORMAT,LPVOID);	//JON 5Sep00
    static 	void EnumerateDriverModes(DDDriver&);
    static HRESULT GetRenderBitDepths(LPDIRECTDRAW7,ULong&);

    HRESULT EndPolyR3DVERTEX();
    HRESULT EndPolyR3DTLVERTEX();
    HRESULT EndFanR3DVERTEX();
    HRESULT EndFanR3DTLVERTEX();

    void AddPolyToList( SPolygon* );									//JON 5/17/00

    void RenderPolyList(SPolygon* &);
    void RenderPlainPolyList(SPolygon*);								//JON 5/9/00
    void RenderTLPolyList(SPolygon*);
    void RenderTPolyList(SPolygon*);
    void RenderTransTLPolyList(SPolygon*);
    void RenderLineList(SLine*);
    void RenderPointList(SPoint*);

//TempCode JON 4Oct00 	HRESULT SetCurrentLighting(const LIGHTFLAG&);
//	void GetErrorDesc( HRESULT err, char* &desc );
    HRESULT	_SetDriverAndMode(const HDRIVER&,const HMODE&,const HWND& );
    HRESULT BackgroundImage( BITMAPFILEHEADER* pFile );
    HRESULT _BeginScene(const HRENDERTARGET & RenderTarget);				//JON 4/19/00

    Lib3DPoint* _BeginPoly( const ULong vertexCount ); // the internal versions of this routine
//	Lib3DPoint* _BeginFan( const ULong vertexCount ); // the internal versions of this routine
    HRESULT PrepareForClipping( void  );
    HRESULT _DrawSphereTransformed( const D3DVALUE rad, const Angles roll, // assumes that the sphere poly is created in current poly and the first vertex is the centre
                                    const D3DVALUE u0,const D3DVALUE v0,	//texture coords for tl corner
                                    const D3DVALUE u1,const D3DVALUE v1);	//texture coords for br corner )

    HRESULT _DrawTransformedCylinder( const D3DVALUE fu0, const D3DVALUE fv0, const D3DVALUE fu1, const D3DVALUE fv1 ); // assumes poly is within currentPoly
    HRESULT _SetProjectionMatrix(const Angles&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const bool justVisCheck = false);
public:
    Lib3D();
    virtual ~Lib3D();

    // standard IUnknown interface methods
    HRESULT	QueryInterface(REFIID,LPVOID*);
    ULong	AddRef();
    ULong	Release();

    // init, shutdown & driver,mode selection routines
    HRESULT	Initialise(const HWND&, const ULong* sqrtTable);
    HRESULT	GetDrivers(UIDrivers&);
    HRESULT	GetModes(const HDRIVER&,UIModes&);
    HRESULT GetDefaultDriverAndMode(HDRIVER&,HMODE&);
    HRESULT	SetDriverAndMode(const HDRIVER&,const HMODE&,const HWND&);
    HRESULT RestoreDisplayMode();
    HRESULT ChangeDisplaySettings(HWND,SWord,SWord,bool);

    // 2D interface methods
    HRESULT ScreenSwap();
    HRESULT SetPaletteTable(UByte*);
    HRESULT GetSurfaceDesc(ROWANSURFACEDESC*);

    // 3D interface methods
    HRESULT BeginScene(const HRENDERTARGET &);
    HRESULT End3DScene();
    HRESULT EndScene();
    HRESULT ClearTargetZ();

    HRESULT PushMatrix(const HMATRIX&);
    HRESULT PopMatrix(const HMATRIX&);
    HRESULT SetMatrix(const HMATRIX&,const R3DMATRIX&);
    HRESULT GetMatrix(const HMATRIX&,R3DMATRIX&);
    HRESULT LoadIdentity(const HMATRIX&);
    HRESULT Rotate(const HMATRIX&,const HAXIS&,const Angles&);
    HRESULT Scale(const HMATRIX&,const D3DVALUE&);
    HRESULT Scale(const HMATRIX&,const D3DVECTOR&);
    HRESULT Translate(const HMATRIX&,const D3DVECTOR&);
    HRESULT BodyToScreen(const R3DVERTEX&,D3DVALUE&,D3DVALUE&,D3DVALUE&,D3DVALUE* distAtZ = NULL);//RJS 07Feb00
    HRESULT Transform(const HMATRIX&,DoPointStruc&);
    HRESULT BackProjectViewCone(COORDS3D*);

    HRESULT VisibleCheck(D3DVECTOR*,ULong,ULong*);
    HRESULT VisibleCheck(D3DVECTOR*,D3DVALUE*,ULong,ULong*);
//DEADCODE JON 5/24/00 	HRESULT VisibleCheck(R3DVERTEX* v,ULong num,ULong* res);		//JON 5/5/00
    HRESULT VisibleCheck(DoPointStruc* v,ULong num,ULong* res);

    HRESULT SetProjectionMatrix(const Angles&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const bool justVisCheck = false);
    HRESULT SetProjectionMatrix(const Angles&,const D3DVALUE&,const D3DVALUE&,const bool justVisCheck = false);
    HRESULT SetFogColour(const ULong&);
    HRESULT SetFontColour(const ULong&);
    void	EnableFogging(bool);

    HRESULT SetAmbientLighting(LIGHTINGDESC);
    HRESULT SetObjectLighting(LIGHTFLAG&);
    HRESULT SetLightVector(D3DVALUE,D3DVALUE,D3DVALUE);
    HRESULT GetMaxLandDotProduct(D3DVALUE&);

    HRESULT SetGlobal(const TOGGLES&,const ULong);
    HRESULT SetGlobal(const TOGGLES&,ULong*);
    HRESULT IncGlobal(const TOGGLES&); 									//JON 14Aug00
    HRESULT DecGlobal(const TOGGLES&); 									//JON 14Aug00

    HRESULT CreateTexture(MAPDESC*,const TCFLAGS&);
//DeadCode JON 17Sep00 	HRESULT UploadTexture(const UWord&);
    HRESULT UploadTexture();
    HRESULT ReduceLandQuality(UWord& sourceTextIndex, UWord& destTextIndex );

    HRESULT AllocateLandscapeTextures();
    HRESULT FreeLandscapeTextures();
    HRESULT GetLandscapeTextureCount(SLong&,SLong&,SLong&,SLong&,
                                     SLong&,SLong&,SLong&,SLong&);

    HRESULT GetLandscapeTextureOnScreenMax(SLong&,SLong&,SLong&,SLong&,
                                           SLong&,SLong&,SLong&,SLong&);	//JON 31Jul00


    HRESULT	FreeLandscapeTexture(UWord);
    HRESULT	AllocateLandscapeTexture(UWord,UWord&);

    HRESULT SetMaterial(UWord,MAPDESC *pmap=NULL);
    HRESULT SetMaterial(const HMATERIAL&);

//DEADCODE JON 5/19/00 	HRESULT BeginPoly(const ULong&,R3DVERTEX*&);
//DEADCODE JON 5/19/00 	HRESULT BeginPoly(const HMATERIAL&,const ULong&,R3DVERTEX*&);
//DEADCODE JON 5/19/00 	HRESULT BeginPoly(const HMATERIAL&,const ULong&,R3DTLVERTEX*&);

    Lib3DPoint* BeginPoly(const ULong&);
    Lib3DPoint* BeginPoly( const HMATERIAL& mat, const ULong& vertexCount );
    HRESULT EndPoly();

//DEADCODE JON 5/19/00 	HRESULT BeginStrip(const ULong&,R3DVERTEX*&);
//DEADCODE JON 5/19/00 	HRESULT BeginStrip(const HMATERIAL&,const ULong&,R3DVERTEX*&);
//DEADCODE JON 5/19/00 	HRESULT BeginStrip(const HMATERIAL&,const ULong&,R3DTLVERTEX*&);
//DEADCODE JON 5/19/00 	HRESULT EndStrip();
//DEADCODE JON 5/19/00 	HRESULT BeginFan(const ULong&,R3DVERTEX*&);
//DEADCODE JON 5/19/00 	HRESULT BeginFan(const HMATERIAL&,const ULong&,R3DVERTEX*&);
//DEADCODE JON 5/19/00 	HRESULT BeginFan(const HMATERIAL&,const ULong&,R3DTLVERTEX*&);

    Lib3DPoint* BeginFan( const ULong& vertexCount );
    Lib3DPoint* BeginFan( const HMATERIAL& mat, const ULong& vertexCount );
    HRESULT EndFan();


    HRESULT DrawSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,
                       const Angles,const SWord,const SWord,const SWord,const SWord);
    HRESULT DrawTransformedSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,
                                  const Angles,const SWord,const SWord,const SWord,const SWord);//RJS 20Mar00
//DEADCODE JON 5/22/00 	HRESULT DrawLine(const HMATERIAL&,const R3DVERTEX&,const R3DVERTEX&);
//DEADCODE JON 5/22/00 	HRESULT DrawLine(const HMATERIAL&,const R3DTLVERTEX&,const R3DTLVERTEX&);
    HRESULT DrawLine(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&);
    HRESULT DrawTransformedLine(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&);
//DeadCode JON 19Oct00 	HRESULT DrawPoint(const HMATERIAL&,const DoPointStruc&);

    HRESULT	GiveHint(const HINTS&);

//DEADCODE JON 5/22/00 	HRESULT DrawCylinder(const HMATERIAL&,const R3DVERTEX&,const R3DVERTEX&,
//DEADCODE JON 5/22/00 						const D3DVALUE&,const SWord,const SWord,const SWord,const SWord);//RJS 14Feb00
    HRESULT DrawCylinder(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&,
                         const D3DVALUE&,const SWord,const SWord,const SWord,const SWord);//RJS 14Feb00
    HRESULT CylinderOffsets(const DoPointStruc&,const DoPointStruc&,const D3DVALUE&,D3DVALUE&,D3DVALUE&,DoPointStruc&);
    HRESULT DrawTransformedCylinder(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const SWord,const SWord,const SWord,const SWord);


    HRESULT TestPoly(const HMATERIAL&);

    HRESULT UnloadTexture( MAPDESC* );

    HRESULT LoadBMP(UByte *);
    void	SetFogValues( const D3DVALUE& FogStart, const D3DVALUE& FogEnd );

    void	GivePolyCount(int&);	//RJS 22Mar00
    void	GetTextureRAM(ULong&);								//RJS 24Mar00
    ULong	GetFreeVideoMemory();										//JON 10Jul00

    HRESULT DoFade( D3DCOLOR fadeCol, UByte fadeDepth );			//JON 4/11/00
    HRESULT DoWhiteOut( const D3DCOLOR&, const UByte&, const D3DVALUE&,  const D3DVALUE&, const D3DVALUE&);//RJS 20Apr00

    HRESULT FlushAsBackground( void );									//JON 4/19/00
    HRESULT GetZDepth( ULong& );										//RJS 3/5/00

    int ScreenShot( BITMAPINFOHEADER* pFile,void* imagebuffer=NULL );						//JON 6/8/00

    HRESULT DrawQuadSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,
                           const Angles,const SWord,const SWord,const SWord,const SWord);//RJS 06Jun00
    HRESULT DrawPivotedSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,
                              const Angles,const SWord,const SWord,const SWord,const SWord);//RJS 06Jun00

    HRESULT SetMirrorTexture( const HMATERIAL& );						//JON 3Jul00

    HRESULT Wipe( const D3DCOLOR );							//JON 4Jul00

    HRESULT SetGamma( double gammaAmount );						//JON 12Jul00
    HRESULT SetGammaLevel( ULong val );							//JON 12Jul00

    HRESULT UploadAsDitherTexture( MAPDESC *pmap );						//JON 26Jul00
    HRESULT UploadAsMipMapLevel( MAPDESC *destination, MAPDESC *source, int level );		//JON 8Aug00
    void GetDiagnosticString( char* &theString );						//JON 22Aug00
    HRESULT SetNearClipPlane( D3DVALUE dist );								//JON 29Aug00
    HRESULT SetFarClipPlane( D3DVALUE dist );								//JON 29Aug00
    void	SetMasterShading( LIGHTFLAG& lf );							//JON 29Sep00

    HRESULT DrawPoint( const HMATERIAL&, const DoPointStruc& );				//JON 19Oct00
    HRESULT DrawTransformedPoint( const HMATERIAL&, const DoPointStruc& );	//JON 19Oct00

    void GetViewPortDimensions( D3DVALUE &sx, D3DVALUE &sy, D3DVALUE &cx, D3DVALUE &cy );	//JON 19Oct00
    void ResetClipDistances( void );						//JON 23Oct00

    void GetTransformedLightColour( R3DVERTEX& vertex, const LIGHTFLAG lf );	//JON 7Nov00//RJS 10Nov00

};
// class lib3d

#include "polyvert.h"

//#ifdef _INSIDE_LIB3D_
DEFINE_GUID(IID_ILib3D, 0x11038561, 0x95e1, 0x11d3, 0x87, 0x95, 0x0, 0x40, 0x5, 0x2c, 0x1f, 0x45);
//#endif

#endif	//LIB3D_Included
