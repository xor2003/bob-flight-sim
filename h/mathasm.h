//------------------------------------------------------------------------------
//Filename       mathasm.h
//System
//Author         Jim Taylor
//Date           Fri 12 Jul 1996
//Description
//
//Math based assembler inline code.	  //JIM 20/05/99				  //JIM 20/05/99
//
//__fastcall defines:
//	param1:		ECX
//	param2:		EDX
//	param3..	on stack
//	return val	EAX
//	To get the optimiser to bother generating code, we must write the
//  following dummy statements which the optimiser will remove (yippee!):
//		mov	ecx,param1
//		mov	edx,param2
//	You can use eax as scratch as it must contain the return value on exit.
//	At present I don't know wether the optimiser assumes you may damage ecx and edx
//	The routines I wrote today never damage ecx or edx
//
//	Occasionally, the compiler/optimiser can do better than we can
//	and using __stdcall will allow the compiler to present the values to
//	our assembly code more efficiently, but often we need to do defensive
//	stacking, losing the benefit.
//
//------------------------------------------------------------------------------
#ifndef	MATHASM_Included
#define	MATHASM_Included

#define	DEFAULT_MATHASM 0
#include "cmath"
#pragma warning(disable:4800)

#ifdef __GNUC__

// RERUN: MSVC <intrin.h> defines __INTRIN_INLINE; under GCC just
// make the intrinsic shims static inline (was: #define inline __INTRIN_INLINE,
// which replaced the keyword and broke every inline below).
#ifdef _WIN32
// RERUN: mingw supplies the real _BitScan* intrinsics, but its
// _bittest*/_bittestand* use "rm" constraints - a register operand makes
// bt wrap the index mod 32, breaking the unbounded bit-string indexing
// BoB relies on (bt ds:[mem],reg). Shadow with memory-constrained copies.
#include <intrin.h>
static inline unsigned char _rowan_bittest(const long * const a, const long b)
{
	unsigned char retval;
	if (__builtin_constant_p(b))
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "mr" (*(a + (b / 32))), [b] "Ir" (b % 32));
	else
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "m" (*a), [b] "r" (b));
	return retval;
}
static inline unsigned char _rowan_bittestandset(long * const a, const long b)
{
	unsigned char retval;
	if (__builtin_constant_p(b))
		__asm__("bts %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("bts %[b], %[a]; setb %b[retval]" : [a] "+m" (*a), [retval] "=q" (retval) : [b] "r" (b));
	return retval;
}
static inline unsigned char _rowan_bittestandreset(long * const a, const long b)
{
	unsigned char retval;
	if (__builtin_constant_p(b))
		__asm__("btr %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("btr %[b], %[a]; setb %b[retval]" : [a] "+m" (*a), [retval] "=q" (retval) : [b] "r" (b));
	return retval;
}
static inline unsigned char _rowan_bittestandcomplement(long * const a, const long b)
{
	unsigned char retval;
	if (__builtin_constant_p(b))
		__asm__("btc %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("btc %[b], %[a]; setb %b[retval]" : [a] "+m" (*a), [retval] "=q" (retval) : [b] "r" (b));
	return retval;
}
#define _bittest				_rowan_bittest
#define _bittestandset		_rowan_bittestandset
#define _bittestandreset		_rowan_bittestandreset
#define _bittestandcomplement	_rowan_bittestandcomplement
#else
#define __INTRIN_INLINE static inline
__INTRIN_INLINE unsigned char _rowan_BitScanForward(unsigned long * const Index, const unsigned long Mask)
{
	__asm__("bsfl %[Mask], %[Index]" : [Index] "=r" (*Index) : [Mask] "mr" (Mask));
	return Mask ? 1 : 0;
}

__INTRIN_INLINE unsigned char _rowan_BitScanReverse(unsigned long * const Index, const unsigned long Mask)
{
	__asm__("bsrl %[Mask], %[Index]" : [Index] "=r" (*Index) : [Mask] "mr" (Mask));
	return Mask ? 1 : 0;
}

/* NOTE: again, the bizarre implementation follows Visual C++ */
__INTRIN_INLINE unsigned char _rowan_bittest(const long * const a, const long b)
{
	unsigned char retval;

	if (__builtin_constant_p(b))
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "mr" (*(a + (b / 32))), [b] "Ir" (b % 32));
	else
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "m" (*a), [b] "r" (b));

	return retval;
}

#ifdef _M_AMD64
__INTRIN_INLINE unsigned char _rowan_bittest64(const __int64 * const a, const __int64 b)
{
	unsigned char retval;

	if (__builtin_constant_p(b))
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "mr" (*(a + (b / 64))), [b] "Ir" (b % 64));
	else
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "m" (*a), [b] "r" (b));

	return retval;
}
#endif

__INTRIN_INLINE unsigned char _rowan_bittestandcomplement(long * const a, const long b)
{
	unsigned char retval;

	if (__builtin_constant_p(b))
		__asm__("btc %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("btc %[b], %[a]; setb %b[retval]" : [a] "+m" (*a), [retval] "=q" (retval) : [b] "r" (b));

	return retval;
}

__INTRIN_INLINE unsigned char _rowan_bittestandreset(long * const a, const long b)
{
	unsigned char retval;

	if (__builtin_constant_p(b))
		__asm__("btr %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("btr %[b], %[a]; setb %b[retval]" : [a] "+m" (*a), [retval] "=q" (retval) : [b] "r" (b));

	return retval;
}

__INTRIN_INLINE unsigned char _rowan_bittestandset(long * const a, const long b)
{
	unsigned char retval;

	if (__builtin_constant_p(b))
		__asm__("bts %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("bts %[b], %[a]; setb %b[retval]" : [a] "+m" (*a), [retval] "=q" (retval) : [b] "r" (b));

	return retval;
}
// RERUN: MSVC-name macros -> _rowan_* bodies (clang reserves these names
// as builtins under -fms-extensions; cannot define them directly)
#define _BitScanForward		_rowan_BitScanForward
#define _BitScanReverse		_rowan_BitScanReverse
#define _bittest				_rowan_bittest
#define _bittest64			_rowan_bittest64
#define _bittestandcomplement	_rowan_bittestandcomplement
#define _bittestandreset		_rowan_bittestandreset
#define _bittestandset		_rowan_bittestandset
#endif
#endif

#pragma warning(disable:4035)
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BTR
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro.
//				Tests a whole array of memory... up to 512Mb in principal!
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true
//
//------------------------------------------------------------------------------
/*
#ifdef __WATCOMC__
extern	Bool	BITRESET(void*,ULong);
#pragma	aux		BITRESET		=		\
		"btr	ds:[esi],ecx"			\
		"setc	al"					\
		parm	[esi] [ecx]				\
		modify exact	[al]			\
		value	[al]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    BITRESET
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
//DEADCODE RDH 20/05/99 	UByte retval;
//DEADCODE RDH 20/05/99 	_asm
//DEADCODE RDH 20/05/99 	{
//DEADCODE RDH 20/05/99 		push	esi
//DEADCODE RDH 20/05/99 		push	ecx
//DEADCODE RDH 20/05/99 		push	eax
//DEADCODE RDH 20/05/99 		mov		esi,num1
//DEADCODE RDH 20/05/99 		mov		ecx,num2
//DEADCODE RDH 20/05/99 		btr		ds:[esi],ecx
//DEADCODE RDH 20/05/99 		setc	al
//DEADCODE RDH 20/05/99 		mov		retval,al
//DEADCODE RDH 20/05/99 		pop		eax
//DEADCODE RDH 20/05/99 		pop		ecx
//DEADCODE RDH 20/05/99 		pop		esi
//DEADCODE RDH 20/05/99 	}
//DEADCODE RDH 20/05/99 	return (Bool)retval;

/*
inline bool __fastcall	oldBITRESET(void * num1,ULong num2)
{
	_asm 
	{
		mov	ecx,num1
		mov	edx,num2
		btr	ds:[ecx],edx
		setc	al
	}
}
*/
inline  bool __fastcall	BITRESET(void * num1,ULong num2)
{ 
	unsigned char* p=(unsigned char*)num1+(num2>>3);
	unsigned char m=(unsigned char)(1u<<(num2&7));
	bool prev=(*p&m)!=0;
	*p=(unsigned char)(*p&~m);
	return prev;
}
/*
#else
extern	Bool	BITRESET(void*,ULong);
#endif
#endif
*/
/*
#ifdef __WATCOMC__
extern	ULong	BITRESETI(ULong,ULong);
#pragma	aux		BITRESETI		=		\
		"btr	eax,ecx"			\
		parm	[eax] [ecx]				\
		modify exact	[eax]			\
		value	[eax]
#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    BITRESETI
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong __fastcall BITRESETI(ULong num1,ULong num2)
{
	_asm
	{
		mov	eax,num1
		mov	edx,num2
		btr	eax,edx
	}
}

#endif
#endif
*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BTS
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro.
//				Tests a whole array of memory... up to 512Mb in principal!
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true
//
//------------------------------------------------------------------------------
/*
#ifdef __WATCOMC__
extern	Bool	BITSET(void*,ULong);
#pragma	aux		BITSET		=			\
		"bts	ds:[esi],ecx"			\
		"setc	al"					\
		parm	[esi] [ecx]				\
		modify exact	[al]			\
		value	[al]					\

#else
#ifdef __MSVC__
*/
//-----------------------------------------------------------------------------
// Procedure    BITSET
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
/*
inline bool __fastcall oldBITSET(void* num1,ULong num2)
{
	_asm
	{
		mov	ecx, num1
			mov	edx, num2
			bts	ds : [ecx], edx
			setc	al
	}
}
*/
inline bool __fastcall BITSET(void* num1,ULong num2)
{
	unsigned char* p=(unsigned char*)num1+(num2>>3);
	unsigned char m=(unsigned char)(1u<<(num2&7));
	bool prev=(*p&m)!=0;
	*p=(unsigned char)(*p|m);
	return prev;
}
/*
#else
extern	Bool	BITSET(void*,ULong);
#endif
#endif
*/
/*
#ifdef __WATCOMC__
extern	ULong	BITSETI(ULong,ULong);
#pragma	aux		BITSETI		=		\
		"bts	eax,ecx"			\
		parm	[eax] [ecx]				\
		modify exact	[eax]			\
		value	[eax]					\

#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    BITSETI
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong __fastcall BITSETI(ULong num1, ULong num2)
{
	_asm
	{
		mov	eax,num1
		mov	edx,num2
		bts	eax,edx
	}
}

#endif
#endif
*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BT
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro.
//				Tests a whole array of memory... up to 512Mb in principal!
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true
//
//------------------------------------------------------------------------------

/*
#ifdef __WATCOMC__
extern	Bool	BITTEST(const void*,ULong);
#pragma	aux		BITTEST		=			\
		"bt		ds:[esi],ecx"			\
		"setc	al"					\
		parm	[esi] [ecx]				\
		modify exact	[al]			\
		value	[al]					\

#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    BITTEST
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline bool __fastcall BITTEST(const void* num1,ULong num2)
{
	return (((const unsigned char*)num1)[num2>>3]>>(num2&7))&1;
	/*
	_asm
	{
		mov	ecx,num1
		mov	edx,num2
		bt	ds:[ecx],edx
		setc	al
}*/
}
/*
#else
extern	Bool	BITTEST(const void*,ULong);
#endif
#endif
*/
/*
#ifdef __WATCOMC__
extern	Bool	BITTESTI(int,ULong);
#pragma	aux		BITTESTI		=			\
		"bt		esi,ecx"			\
		"setc	al"					\
		parm	[esi] [ecx]				\
		modify exact	[al]			\
		value	[al]					\

#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    BITTESTI
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline bool __fastcall BITTESTI(int num1,ULong num2)
{
	_asm
	{
		mov	ecx,num1
		mov	edx,num2
		bt	ecx,edx
		setc	al
	}
}

#endif
#endif
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BTC
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	bit test and reset assembler macro.
//				Tests a whole array of memory... up to 512Mb in principal!
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		false=0/true - old value
//
//------------------------------------------------------------------------------
/*
#ifdef __WATCOMC__
extern	Bool	BITCOMP(void*,ULong);
#pragma	aux		BITCOMP		=			\
		"btc	ds:[esi],ecx"			\
		"setc	al"					\
		parm	[esi] [ecx]				\
		modify exact [al]				\
		value	[al]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    BITCOMP
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline bool __fastcall BITCOMP(void* num1,ULong num2)
{
	unsigned char* p=(unsigned char*)num1+(num2>>3);
	unsigned char m=(unsigned char)(1u<<(num2&7));
	bool prev=(*p&m)!=0;
	*p=(unsigned char)(*p^m);
	return prev;
	/*
	_asm
	{
		mov	ecx,num1
		mov	edx,num2
		btc	ds:[ecx],edx
		setc	al
	}*/

}
/*
#else
extern	Bool	BITCOMP(void*,ULong);
#endif
#endif
*/
/*
#ifdef __WATCOMC__
extern	ULong	BITCOMPI(ULong,ULong);
#pragma	aux		BITCOMPI		=		\
		"btc	eax,ecx"			\
		parm	[eax] [ecx]				\
		modify exact	[eax]			\
		value	[eax]					\

#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    BITCOMPI
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong __fastcall BITCOMPI(ULong num1,ULong num2)
{
	_asm
	{
		mov	eax,num1
		mov	edx,num2
		btc	eax,edx
	}
}

#endif
#endif
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BSF/BSR
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	Return the lowest/highest set bit number
//				If the input has no bits set then errcode is returned...
//				The keyboard uses 0. Other code may use -1 or 32.
//				NOTE:	These routines test a register value - i.e. 1 location
//
//	To test a block of memory use:
//
//	ULong* arrptr=arrstart;
//	ULong	accum=0;
//	for(int arrcount=0;arrcount<ARRSIZE*32;arrcount+=32)
//		if ((accum+=arrptr++[0])!=0))
//		{
//		 	arrcount+=BITSCANLOWEST(accum,0);
//			break;
//		}
//	-Exits with accum = the bit or accum = ARRSIZE*32 if no bit
//
//	ULong* arrptr=&arrstart[ARRSIZE];
//	ULong	accum=0;
//	for(int arrcount=ARRSIZE*32;arrcount>=0;arrcount-=32)
//		if ((accum+=arrptr++[0])!=0))
//		{
//		 	arrcount+=BITSCANHIGHEST(accum,0);
//			break;
//		}
//	-Exits with accum = the bit or accum negative if no bit
//
//	This should compile down to optimal assembler.
//
//
//
//Inputs		pointer to word memory
//				index to test
//
//Returns		bit number or errcode
//
//------------------------------------------------------------------------------
/*
#ifdef __WATCOMC__
extern	ULong	BITSCANLOWEST(ULong bits,ULong errcode);
#pragma	aux		BITSCANLOWEST	=		\
		"bsf	edx,eax"				\
		parm	[eax] [edx]				\
		modify exact	[edx]			\
		value	[edx]
#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    BITSCANLOWEST
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong __fastcall BITSCANLOWEST(ULong bits,ULong errcode=0)
{
	_asm
	{
		mov	ecx,bits
		mov	eax,errcode
		bsf	ecx,eax
	}
}

#endif
#endif
*/
/*
#ifdef __WATCOMC__
extern	ULong	BITSCANHIGHEST(ULong bits,ULong errcode);
#pragma	aux		BITSCANHIGHEST	=		\
		"bsr	edx,eax"				\
		parm	[eax] [edx]				\
		modify exact [edx]				\
		value	[edx]
#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    BITSCANHIGHEST
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong __fastcall BITSCANHIGHEST(ULong bits,ULong errcode=0)
{
	_asm
	{
		mov	ecx,bits
		mov	eax,errcode
		bsr	ecx,eax
	}
}

#endif
#endif
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MUL[SH/DIV][SIN/UNS]
//Author		Jim Taylor
//Date			Fri 3 Nov 1995
//
//Description	Double long intermediate maths
//				Multiply to a 64 bit result, then divide or shift back to 32 bit
//				Note: if the division doesn't result in 32 bits you are in trouble
//
//Inputs		2 multipliers and a divisor
//
//
//Returns
//
//------------------------------------------------------------------------------
/*
#ifdef __WATCOMC__
extern	ULong MULSHUNS (ULong,ULong,UByte);
#pragma	aux	MULSHUNS		=			\
		"mul	edx"	  				\
		"shrd	eax,edx,cl"				\
		parm caller	[eax] [edx] [cl]	\
		modify	exact [edx eax]			\
		value	[eax]
#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    MULSHUNS
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong __fastcall MULSHUNS (ULong num1, ULong num2, UByte num3)
{
    _asm
    {
		mov		ecx,num1
		mov		eax,num2
		push	edx
		push	ecx
		mul		ecx
		mov		cl,num3
		shrd	eax,edx,cl
		pop		edx
		pop		ecx
    }
}

#endif
#endif
*/
#ifdef __WATCOMC__
extern	SLong	MULSHSIN (SLong,SLong,UByte);
#pragma	aux	MULSHSIN		=		\
		"imul	edx"	  			\
		"shrd	eax,edx,cl"			\
		parm	[eax] [edx] [cl]	\
		modify	exact [edx eax]		\
		value	[eax]
#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    MULSHSIN
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline SLong __fastcall MULSHSIN (SLong num1, SLong num2, UByte num3)
{// x0r  TODO not tested should be ok
	return (unsigned __int64)(num1 * (signed __int64)num2) >> num3;
/*    _asm
    {
		mov		ecx,num1
		mov		eax,num2
		push	edx
		push	ecx
		Imul	ecx
		mov		cl,num3
		shrd	eax,edx,cl
		pop		edx
		pop		ecx
}*/
}
#else
extern	SLong	MULSHSIN (SLong,SLong,UByte);
#endif
#endif
/*
#ifdef __WATCOMC__
extern	ULong SHDIVUNS (ULong,UByte,ULong);
#pragma	aux	SHDIVUNS		=			\
		"mov	edx,eax"				\
		"mov	bl,32"					\
		"shl	eax,cl"					\
		"sub	bl,cl"					\
		"mov	cl,bl"					\
		"shr	edx,cl"					\
		"div	esi"					\
		parm caller	[eax] [cl] [esi]	\
		modify	[ebx edx eax]	   		\
		value	[eax]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    SHDIVUNS
// Author       Paul
// Date         31/10/97
//
// Description
//	No point optimising to __fastcall as parameter ordering is bad!
//	p1 is in ecx - want in eax and edx
//	p2 is in edx - want in ecx
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong SHDIVUNS (ULong num1, UByte num2, ULong num3)
{
	// RERUN: was ((u64)num1 << num2) / num3 - SIGFPEs on num3==0 and is
	// C++ UB for num2>=64 (x86 shl masks count to 5 bits). Migalley form.
	const unsigned int safe_shift = num2 & 31;
	const unsigned __int64 shifted = (unsigned __int64)num1 << safe_shift;
	return num3 ? (ULong)(shifted / num3) : 0;
/*		_asm
    {
		push	ecx
		push	edx
		mov		eax,num1
		mov		cl,num2
		mov		edx,eax
		shl		eax,cl
		sub		ecx,32
		neg		ecx
		shr		edx,cl	;;sign extending...
		div		num3
		pop		edx
		pop		ecx
    }*/
}
/*
#endif
#endif
*/
/*
#ifdef __WATCOMC__
extern	ULong SHDIVSIN (SLong,UByte,ULong);
#pragma	aux	SHDIVSIN		=			\
		"mov	edx,eax"				\
		"mov	ebx,32"					\
		"shl	eax,cl"					\
		"sub	ebx,ecx"				\
		"mov	ecx,ebx"				\
		"sar	edx,cl"					\
		"idiv	esi"					\
		parm caller	[eax] [cl] [esi]	\
		modify	[ebx edx eax]	   		\
		value	[eax]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    SHDIVSIN
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline SLong SHDIVSIN (SLong num1,UByte num2,ULong num3)
{
	//RERUN: shipped asm dividend is edx:eax = num1 * 2^num2, a full signed
	//64-bit product: `mov edx,eax` copies num1 BEFORE `shl eax,cl`, then
	//`sar edx,32-cl` supplies the high dword -- the earlier "trunc32 then
	//sign-extend" reading dropped high bits (negative range2d/Range for
	//|num1|>=2^17; same fix as migalley H/MATHASM.H). idiv num3 is a
	//SIGNED 32-bit divisor (sin/cos go negative). Zero-guard retained
	//(shipped would #DE).
	return num3 ? (SLong)(((int64_t)num1 << (num2 & 31)) / (int32_t)num3) : 0;
/*    _asm
    {
		push	ecx
		push	edx
		mov		eax,num1
		mov		cl,num2
		mov		edx,eax
		shl		eax,cl
		sub		ecx,32
		neg		ecx
		sar		edx,cl	;;sign extending...
		idiv	num3
		pop		edx
		pop		ecx
}*/
}
/*
#else
extern	ULong SHDIVSIN (SLong,UByte,ULong);
#endif
#endif
*/
/*
#ifdef __WATCOMC__
extern	ULong	MULDIVUNS (ULong,ULong,ULong);
#pragma	aux	MULDIVUNS		=		\
		"mul	edx"	  			\
		"div	ecx"				\
		parm	[eax] [edx] [ecx]	\
		modify	[edx eax]			\
		value	[eax]
#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    MULDIVUNS
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline ULong MULDIVUNS (ULong num1, ULong num2, ULong num3)
{
    _asm
    {
		push	edx
		push	ecx
		mov		eax,num1
		mov		edx,num2
		mov		ecx,num3
		mul		edx
		div		ecx
		pop		ecx
		pop		edx
    }
}

#endif
#endif
*/
extern	SLong	MULDIVSIN (SLong,SLong,SLong);
#ifdef __WATCOMC__
#pragma	aux	MULDIVSIN		=		\
		"imul	edx"	  			\
		"idiv	ecx"				\
		parm	[eax] [edx] [ecx]	\
		modify	[edx eax]			\
		value	[eax]
#else
#ifdef __MSVC__

//-----------------------------------------------------------------------------
// Procedure    MULDIVSIN
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline SLong MULDIVSIN (SLong num1,SLong num2,SLong num3)
//static SLong MULDIVSIN (SLong num1,SLong num2,SLong num3)
{
	return num2 * (signed __int64)num1 / num3;
	/*
    _asm
    {
		push	edx
		push	ecx
		mov		eax,num1
		mov		edx,num2
		mov		ecx,num3
		imul	edx
		idiv	ecx
		pop		ecx
		pop		edx
}*/
}
#endif
#endif
////////////////////////////////////////////////////////////
/*
extern	SWord	mathlib_w_getsign(SWord);
#ifdef __WATCOMC__
#pragma	aux	mathlib_w_getsign=	\
		"cwd"			\
		parm	[ax]	\
		modify	exact	[dx]	\
		value	[dx]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    mathlib_w_getsign
// Author       Paul
// Date         31/10/97
//
// Description  optimiser puts expr straight in ax!
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline SWord mathlib_w_getsign(SWord num)
{
	return (num >= 0 ? 0 : -1);															  //RDH 20/05/99
/*    _asm
    {
		mov		ax,num
		sar		ax,15
    }*/
}

//#endif
//#endif
/*
#ifdef __WATCOMC__
extern	SWord	mathlib_w_applysign(SWord,SWord);
#pragma aux	mathlib_w_applysign=	\
		"xor	ax,dx"				\
		"sub	ax,dx"				\
		parm	[ax]	[dx]		\
		modify exact	[ax]		\
		value	[ax]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    mathlib_w_applysign
// Author       Paul
// Date         31/10/97
//
// Description  return value in ax...
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline SWord _fastcall mathlib_w_applysign(SWord num1,SWord num2)
{
	return (num2 ^  num1) - num2;
	/*
    _asm
    {
		mov		ax,num1
		mov		dx,num2
		xor		ax,dx
		sub		ax,dx
    }*/
}
/*#else
extern	SWord	mathlib_w_applysign(SWord,SWord);
#endif

#endif
*/
/*
extern	SLong	mathlib_l_getsign(SLong);
#ifdef __WATCOMC__
#pragma	aux	mathlib_l_getsign=	\
		"cdq"			\
		parm	[eax]	\
		modify	exact	[edx]	\
		value	[edx]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    mathlib_l_getsign
// Author       Paul
// Date         31/10/97
//
// Description  optimiser will put expr straight in eax!
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline SLong mathlib_l_getsign(SLong num)
{
	return (num >= 0 ? 0 : -1);															  //RDH 20/05/99
	/*
	SLong	retval;
    _asm
    {
		mov		eax,num
		sar		eax,31
    }*/
}

//#endif
//#endif
/*
#ifdef __WATCOMC__
extern	SLong	mathlib_l_applysign(SLong,SLong);
#pragma aux	mathlib_l_applysign=	\
		"xor	eax,edx"			\
		"sub	eax,edx"			\
		parm	[eax]	[edx]		\
		modify exact	[eax]		\
		value	[eax]
#else
#ifdef __MSVC__
		*/
//-----------------------------------------------------------------------------
// Procedure    mathlib_l_applysign
// Author       Paul
// Date         31/10/97
//
// Description
//
// Inputs
//
// Returns
//
//-----------------------------------------------------------------------------
inline SLong __fastcall mathlib_l_applysign(SLong num1,SLong num2)
{
	return (num2 ^  num1) - num2;
/*    _asm
    {
		mov		Eax,num1
		mov		Edx,num2
		xor		Eax,Edx
		sub		Eax,Edx
    }*/
}
/*#else
extern	SLong	mathlib_l_applysign(SLong,SLong);
#endif

#endif
*/

#ifdef __MSVC__
#include <float.h>
inline void SETPREC(int p)
{
  unsigned int v;
  v = _controlfp(0, 0); // store old vlaue
		v &=0xfffCffff;
		v|=p<<16;

		_controlfp(v, _MCW_PC);
}

inline int GETPREC()
{
  unsigned int v = _controlfp(0, 0); // store old vlaue
	return ((v>>16)&3);
}

inline UWord GETFPCW()
{
  unsigned int v = _controlfp(0, 0);
	return v;
}

inline void SETFPCW(UWord w)
{
}
#endif

#ifdef __GNUC__
#ifdef _WIN32
// RERUN: mingw has no fpu_control.h - use raw x87 fnstcw/fldcw (same as _FPU_*)
typedef unsigned short fpu_control_t;
#define _FPU_SINGLE	0x0000
#define _FPU_DOUBLE	0x0200
#define _FPU_EXTENDED	0x0300
#define _FPU_GETCW(cw)	__asm__ volatile ("fnstcw %0" : "=m" (cw))
#define _FPU_SETCW(cw)	__asm__ volatile ("fldcw %0" :: "m" (cw))
#else
#include <fpu_control.h>
#endif
inline void SETPREC(int p)
{
 
 fpu_control_t fpu_oldcw,fpu_cw,precision=0; // RERUN: fpu_cw was undeclared

if (p==0) precision=_FPU_SINGLE;
else if (p==2) precision=_FPU_DOUBLE;
else if (p==3) precision=_FPU_EXTENDED;

 _FPU_GETCW(fpu_oldcw); // store old cw
 fpu_cw = (fpu_oldcw & ~_FPU_EXTENDED & ~_FPU_DOUBLE & ~_FPU_SINGLE) | precision;
 _FPU_SETCW(fpu_cw); // RERUN: was SETCW(fpu_oldcw) - never applied new precision

}
inline int GETPREC()
{
 fpu_control_t fpu_cw;
 _FPU_GETCW(fpu_cw); // store cw
 // RERUN: mask checks were wrong - _FPU_EXTENDED(0x300) also matches _FPU_DOUBLE(0x200)
 // so p was always 3. Precision = bits 8-9; extract directly (same as migalley).
	return (fpu_cw >> 8) & 3;
}

inline UWord GETFPCW()
{
	fpu_control_t fpu_cw;
	_FPU_GETCW(fpu_cw); // store cw
	return fpu_cw;
}

inline void SETFPCW(UWord w)
{
	_FPU_SETCW(w); // RERUN: was an empty body
}
#endif

/*
#ifdef __WATCOMC__
extern	void repmovsd(void* s,void* d,int len);
#pragma aux repmovsd="rep movsd" parm [esi][edi][ecx]
#else
#ifdef __MSVC__
inline void repmovsd(void *s,void *d,int len)
{
    __asm
    {
		mov esi,s;
		mov edi,d;
		mov ecx,len;
		rep movsd;
    }
}

#endif
#endif
*/
/*
#ifdef __MSVC__
inline double SQUARE_ROOT(double w)
{
	register double v;
_asm	{
			FLD	w
			FSQRT
			FSTP	v
		}
		return	v;
}
#endif

#pragma warning(default:4035)
*/
//if included:
#pragma warning(default:4800)

// RERUN: GNUC bodies for functions still trapped in the commented-out
// Watcom/MSVC blocks above. Bodies ported per migalley/H/MATHASM.H
// (same-name functions, same asm semantics). BIT*I variants return the
// new value; BITSET/RESET/COMP (non-I) return the previous bit.

inline ULong BITRESETI(ULong value, ULong bit_index)
{
    return value & ~(ULong(1) << (bit_index & 31));
}
inline ULong BITSETI(ULong value, ULong bit_index)
{
    return value | (ULong(1) << (bit_index & 31));
}
inline bool BITTESTI(int value, ULong bit_index)
{
    return (value & (1 << (bit_index & 31))) != 0;
}
inline ULong BITCOMPI(ULong value, ULong bit_index)
{
    return value ^ (ULong(1) << (bit_index & 31));
}
inline ULong BITSCANLOWEST(ULong bits, ULong errcode = 0)
{
    if (bits == 0) return errcode;
    return (ULong)__builtin_ctz(bits);
}
inline ULong BITSCANHIGHEST(ULong bits, ULong errcode = 0)
{
    if (bits == 0) return errcode;
    return (ULong)(31 - __builtin_clz(bits));
}
inline ULong MULSHUNS(ULong num1, ULong num2, UByte num3)
{
    const uint64_t product = static_cast<uint64_t>(num1) * num2;
    return static_cast<ULong>(product >> (num3 & 31));
}
inline ULong MULDIVUNS(ULong num1, ULong num2, ULong num3)
{
    uint64_t product = (uint64_t)num1 * num2;
    return num3 ? (ULong)(product / num3) : 0;
}
inline SLong MULSHSIN(SLong a, SLong b, UByte shift)
{
    // shrd semantics: 64-bit signed product shifted LOGICALLY (zeros in)
    const uint64_t product = static_cast<uint64_t>(static_cast<int64_t>(a) * b);
    return static_cast<SLong>(product >> (shift & 31));
}
inline SLong MULDIVSIN(SLong num1, SLong num2, SLong num3)
{
    int64_t product = (int64_t)num1 * num2;
    return num3 ? (SLong)(product / num3) : 0;
}
inline void repmovsd(const void* src, void* dst, int dwords)
{
    asm volatile(
        "rep movsd"
        : "+S"(src), "+D"(dst), "+c"(dwords)
        :
        : "memory"
    );
}

#endif
