//------------------------------------------------------------------------------
//Filename       bstream.h
//System
//Author         Jim Taylor
//Date           Sun 18 Aug 1996
//Description   Binary streams
//				Defines	BIStream	binary input stream
//						BOStream	binary output stream
//				These two streams interface with istream and ostream
//				The << and >> character mode manipulators are remapped
//				to the read/write binary manipulators, allowing overloads to
//				be written indipendently
//				In addition, auto-array manipulators are
//				provided for read/write to provide faster throughput
//
//------------------------------------------------------------------------------
#ifndef	BSTREAM_Included
#define	BSTREAM_Included

#define	DEFAULT_BSTREAM 0

#include	<iostream>
#include	<fstream>
#include	<stdio.h>
#include	<string.h>
#include	"io_compat.h"
#include	<string>
//using namespace std;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using std::ios;

class	BIStream:public	ifstream
{
public:
CON	BIStream(char* fname): ifstream()	{std::string _rp=resolve_ci_path(fname); open(_rp.empty()?fname:_rp.c_str(),ios::in|ios::binary);}
    
    BIStream &operator >> (           char * __b )	{return (read(__b,strlen(__b)));}
    BIStream &operator >> (           char & __b )	{return (read(&__b));}
    BIStream &operator >> (           bool & __b )	{return (read((char*)&__b));}
    BIStream &operator >> (    signed char & __b )	{return (read(&__b));}
    BIStream &operator >> (  unsigned char & __b )	{return (read(&__b));}
    BIStream &operator >> (   signed short & __b )	{return (read(&__b));}
    BIStream &operator >> ( unsigned short & __b )	{return (read(&__b));}
    BIStream &operator >> (     signed int & __b )	{return (read(&__b));}
    BIStream &operator >> (   unsigned int & __b )	{return (read(&__b));}
    BIStream &operator >> (    signed long & __b )	{return (read(&__b));}
    BIStream &operator >> (  unsigned long & __b )	{return (read(&__b));}

	BIStream &read(           char * __b ,int times=1)	{return (BIStream&)(istream::read(__b,times));}
	BIStream &read(           char * __b ,char* __e)	{return (BIStream&)(istream::read(__b,(int)(__e-__b)));}
	BIStream &read(    signed char * __b ,int times=1)	{return (BIStream&)(read((char*)__b,times));}
	BIStream &read(  unsigned char * __b ,int times=1)	{return (BIStream&)(read((char*)__b,times));}
	BIStream &read(   signed short * __b ,int times=1)	{return *(BIStream*)&(istream::read((char*)__b,times*sizeof(signed short)));}
	BIStream &read( unsigned short * __b ,int times=1)	{return (BIStream&)(istream::read((char*)__b,times*sizeof(unsigned short)));}
	BIStream &read(     signed int * __b ,int times=1)	{return (BIStream&)(istream::read((char*)__b,times*sizeof(signed int)));}
	BIStream &read(   unsigned int * __b ,int times=1)	{return (BIStream&)(istream::read((char*)__b,times*sizeof(unsigned int)));}
	BIStream &read(    signed long * __b ,int times=1)	{return (BIStream&)(istream::read((char*)__b,times*sizeof(signed long)));}
	BIStream &read(  unsigned long * __b ,int times=1)	{return (BIStream&)(istream::read((char*)__b,times*sizeof(unsigned long)));}
#ifndef __BORLANDC__
	template	<class c>     	BIStream&	Transfer(c* strucinst)	{return read((char*)strucinst,sizeof(c));}
#endif
};

//a template class	CString;
class	BOStream:public ofstream
{
public:

CON	BOStream(char* fname,Bool blockoverwrite=FALSE):ofstream()
	{
		std::string _rp=resolve_ci_path(fname); const char* _fn=_rp.empty()?fname:_rp.c_str();
		if(blockoverwrite)
		{
		open(_fn, std::ios::in | std::ios::binary);

if (this)
{
    // error, file exists!
}
else
{
    close();
    open(_fn,ios::out | ios::binary);
}
		}
		
		else

	    open(_fn,ios::out | ios::binary |
			ios::trunc);
				}

    BOStream &operator << (const    CString& __b );//	{return (write(__b,strlen(__b)));}
    BOStream &operator << (const           char * __b )	{return (write(__b,strlen(__b)));}
    BOStream &operator << (const           char & __b )	{return (write(&__b));}
	BOStream &operator << (const           bool & __b )	{return (write((char*)&__b));}
    BOStream &operator << (const    signed char & __b )	{return (write(&__b));}
    BOStream &operator << (const  unsigned char & __b )	{return (write(&__b));}
    BOStream &operator << (const   signed short & __b )	{return (write(&__b));}
    BOStream &operator << (const unsigned short & __b )	{return (write(&__b));}
    BOStream &operator << (const     signed int & __b )	{return (write(&__b));}
    BOStream &operator << (const   unsigned int & __b )	{return (write(&__b));}
    BOStream &operator << (const    signed long & __b )	{return (write(&__b));}
    BOStream &operator << (const  unsigned long & __b )	{return (write(&__b));}

	BOStream &write(const           char * __b ,int times=1)	{return (BOStream&)(ostream::write(__b,times));}
	BOStream &write(const           char * __b ,char* __e)	{return (BOStream&)(ostream::write(__b,(int)(__e-__b)));}
	BOStream &write(const    signed char * __b ,int times=1)	{return (BOStream&)(write((char*)__b,times));}
	BOStream &write(const  unsigned char * __b ,int times=1)	{return (BOStream&)(write((char*)__b,times));}
	BOStream &write(const   signed short * __b ,int times=1)	{return (BOStream&)(ostream::write((char*)__b,times*sizeof(signed short)));}
	BOStream &write(const unsigned short * __b ,int times=1)	{return (BOStream&)(ostream::write((char*)__b,times*sizeof(unsigned short)));}
	BOStream &write(const     signed int * __b ,int times=1)	{return (BOStream&)(ostream::write((char*)__b,times*sizeof(signed int)));}
	BOStream &write(const   unsigned int * __b ,int times=1)	{return (BOStream&)(ostream::write((char*)__b,times*sizeof(unsigned int)));}
	BOStream &write(const    signed long * __b ,int times=1)	{return (BOStream&)(ostream::write((char*)__b,times*sizeof(signed long)));}
	BOStream &write(const  unsigned long * __b ,int times=1)	{return (BOStream&)(ostream::write((char*)__b,times*sizeof(unsigned long)));}
#ifndef __BORLANDC__
	template	<class c>	BOStream&	Transfer(c* strucinst)	{return write((char*)strucinst,sizeof(c));}
#endif
};

inline	Bool	DeleteFile(char* fname)
{
	int retval=remove(fname);
	if (retval)
		return FALSE;
	else
		return TRUE;
}

#endif
