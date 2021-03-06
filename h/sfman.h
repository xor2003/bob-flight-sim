/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   SFMAN.H                                                               //
//                                                                         //
//   Description : Header file for acccesing the SoundFont Master Manager  //
//                                                                         //
//   Copyright (c) Creative Technology Ltd. / E-mu Systems, Inc.           //
//                 1996-1997. All rights reserved.                         //
//                                                                         //
//   Notes:        This header file is INDEPENDENT of the 'SFDEVMAN.H'     //
//                 header file. Any similarities in the prototypes or      //
//                 data values should be viewed as purely coincidental.    //
//                                                                         //
//   Revision:     1.01                                                    //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __SFMAN_H
#define __SFMAN_H

///// W I N D O W S   I N C L U D E S  //////////////////////////////////////

#include <windows.h>
#include <winbase.h>

///// E R R O R  C O D E S  /////////////////////////////////////////////////

/* 
    The following is a comprehensive list of the API error message values
*/

/*
--------------------------------
      Error Category
--------------------------------
*/

#define     SFERR_BASE_INVALID             100L
#define     SFERR_BASE_CONTENTION          200L
#define     SFERR_BASE_API                 400L
#define     SFERR_BASE_EXIT                800L
#define     SFERR_BASE_UNDEFINE            900L

/*
--------------------------------
      General Error Messages
--------------------------------
*/

#define     SFERR_NOERR                      0L
#define     SFERR_UNDEFINE_ERROR            (SFERR_BASE_UNDEFINE+1) 

/*
--------------------------------
   API Error Messages
--------------------------------
*/
 
#define     SFERR_LOAD_DLL_FAIL            (SFERR_BASE_API+1)
#define     SFERR_GET_ENTRYPOINT_FAIL      (SFERR_BASE_API+2)
#define     SFERR_DEVICE_NOT_FOUND         (SFERR_BASE_API+3)
#define     SFERR_INTERFACE_NOT_SUPPORTED  (SFERR_BASE_API+4)
#define     SFERR_LAST_API                 (SFERR_BASE_API+5)

/*
--------------------------------
   Invalid Error Messages
--------------------------------
*/

#define     SFERR_SYNTH_INVALID            (SFERR_BASE_INVALID+5)
#define     SFERR_BANK_INDEX_INVALID       (SFERR_BASE_INVALID+6)
#define     SFERR_PATHNAME_INVALID         (SFERR_BASE_INVALID+7)
#define     SFERR_FORMAT_INVALID           (SFERR_BASE_INVALID+8)
#define     SFERR_PRESET_INDEX_INVALID     (SFERR_BASE_INVALID+9)
#define     SFERR_ACCESS_NOT_PERMITTED     (SFERR_BASE_INVALID+11)
#define     SFERR_VERSION_INVALID          (SFERR_BASE_INVALID+12)
#define     SFERR_DEVICE_INVALID           (SFERR_BASE_INVALID+13)
#define     SFERR_SUPPORT_INVALID          (SFERR_BASE_INVALID+14)
#define     SFERR_INVALID_SOUND_ROM        (SFERR_BASE_INVALID+15)
#define     SFERR_NOT_STATIC_MEMORY        (SFERR_BASE_INVALID+16)
#define     SFERR_LAST_INVALID             (SFERR_BASE_INVALID+17)

/*
--------------------------------
   Contention Error Messages
--------------------------------
*/

#define     SFERR_DLL_BUSY                 (SFERR_BASE_CONTENTION+1)
#define     SFERR_DEVICE_BUSY              (SFERR_BASE_CONTENTION+2)
#define     SFERR_RESOURCE_INSUFFICIENT    (SFERR_BASE_CONTENTION+3)
#define     SFERR_SYSMEM_INSUFFICIENT      (SFERR_BASE_CONTENTION+4)
#define     SFERR_SOUNDMEM_INSUFFICIENT    (SFERR_BASE_CONTENTION+5)
#define     SFERR_LAST_CONTENTION          (SFERR_BASE_CONTENTION+6)



///////////////////////////////////////////////////////////////////////////////////
//  S U P P O R T E D   I N T E R F A C E     I D                              //
///////////////////////////////////////////////////////////////////////////////////

// Currently supported Interface ID

enum INTERFACEID {

    ID_SFMANL100API = 0x00010000,
    ID_SFMANL101API = 0x00010001

} ;


///////////////////////////////////////////////////////////////////////////////////
//  D A T A   S T R U C T U R E S   A N D   E N U M E R A T I O N   T A B L E S  //
///////////////////////////////////////////////////////////////////////////////////

#pragma pack(2)

/////  E N U M  /////

enum SFBANKSTYLE {
    
    /* Style 0, and the many names that go along with it... */
    SFBANK_AWE32,
    SFBANK_CC0_ONLY = SFBANK_AWE32,
    SFBANK_GS       = SFBANK_AWE32,
    SFBANK_DEFAULT  = SFBANK_AWE32,

    /* Style 1, and the many names that go along with it... */
    SFBANK_MMA,
    SFBANK_CC0_CC32 = SFBANK_MMA,
};

typedef enum SFBANKSTYLE*    PSFBANKSTYLE ;

enum SFFLAG_OPERATION {
    SFFLAG_OPER_FILE,
    SFFLAG_OPER_MEMORY
};

enum SFMANCAPS {
    SFMANCAP_DYNAMIC_MEM_CAP            = 0x80000000,
    SFMANCAP_SOFTWARE_SYNTH_CAP         = 0x40000000,
    SFMANCAP_NONMMSYSTEM_COMPATIBLE_CAP = 0x20000000,
    SFMANCAP_NONWAVEFORM_SUPPORT_CAP    = 0x10000000
};

   
///// S T R U C T /////

/*
This CSFMIDILocation is usually used when required to MIDI bank/preset 
locaions to the DLL. The PSFPARAMOBJECT type define a pointer to the
parameter object.
*/
typedef struct { 
    WORD            m_BankIndex;    
    WORD            m_PresetIndex;    
} CSFMIDILocation, SFMIDILOCATION, *PSFMIDILOCATION ;

/*
The CSFBufferObject is used to specify a buffer area to the DLL. This buffer
area will usually be filled with some strings or values. In some occassions,
the buffer itself, actually carries information to the DLL, like filename
etc. The PSFBUFFEROBJECT type define a pointer to the buffer object.
*/

typedef struct {

    DWORD   m_Size;         /* The size of the buffer attached */
    LPSTR   m_Buffer;       /* The pointer to the buffer itself */
    DWORD   m_SizeUsed;     /* The number of buffer characters used by DLL */
    WORD    m_Flag;         /* Scratch Variable */

} CSFBufferObject, *PSFBUFFEROBJECT;

/*
The CSFCapsObject is used to for querying device capabilities. This buffer
area will be filled with the capabilities of a particular SoundFont Device. 
The PSFCAPSOBJECT type define a pointer to the device object.
*/

typedef struct {
    WORD    m_SizeOf;           /* sizeof this structure                    */
    DWORD   m_RouterID;         /* SF Device Router ID                      */
    DWORD   m_DevCaps;          /* Capabilities                             */ 
    DWORD   m_MoreDevCaps;      /* More capabilities                        */
    DWORD   m_RomID;            /* ID for a Sound ROM used in a device      */
    DWORD   m_RomVer;           /* Version for a Sound ROM used in a device */
    CHAR    m_DevName[40];      /* MMSystem name for MIDI Output Device     */
    CHAR    m_DevMgrName[20];   /* File Name of the Device Manager DLL.     */
    CHAR    m_DevMgrEntry[20];  /* Entry point inside the Device Manager DLL*/
} CSFCapsObject , *PSFCAPSOBJECT ;

#pragma pack() 

/////  D E F I N E S  ///////////////////////////////////////////////////////

#ifndef DLLAPI
#define DLLAPI _declspec (dllimport)
#endif

#define SF_MASTER_MANAGER_FILENAME "SFMAN32.DLL"
#define SF_FUNCTION_TABLE_NAME "SFManager"

#define SFMAN_GET_ROUTING_INDEX(dwID, by1, by2, by3, by4)             \
  {                                                                   \
  (by1) = (BYTE)(((dwID)    ) & 0x7F);                                \
  (by2) = (BYTE)(((dwID)>> 8) & 0x7F);                                \
  (by3) = (BYTE)(((dwID)>>16) & 0x7F);                                \
  (by4) = (BYTE)(((dwID)>>24) & 0x7F);                                \
  }

#define SFMAN_PERCUSSIVE_BANK 0x8000

/////  S F M A N   F u n c t i o n   T a b l e   ////////////////////////////

typedef WORD SFDEVINDEX;

typedef struct SFMANAGERTAG {

    LRESULT (*SF_QueryInterface) ( INTERFACEID, PDWORD );

} SFMANAGER, *PSFMANAGER ;


typedef struct SFMANL101TAG {

    // Global functions
    LRESULT (*SF_GetNumDevs) ( PWORD ) ;

    // Device functions which do not require allocation (opening)
    LRESULT (*SF_GetDevCaps)    ( SFDEVINDEX, PSFCAPSOBJECT ) ;
    LRESULT (*SF_GetRouterID)   ( SFDEVINDEX, PDWORD ) ;    
    LRESULT (*SF_IsDeviceFree)  ( SFDEVINDEX ) ;
    LRESULT (*SF_Open)          ( SFDEVINDEX ) ;
    LRESULT (*SF_Close)         ( SFDEVINDEX ) ; 
 
    // Query functions
    LRESULT (*SF_IsMIDIBankUsed) (SFDEVINDEX, PWORD);
    LRESULT (*SF_QueryStaticSampleMemorySize) ( SFDEVINDEX, PDWORD, PDWORD ) ;

    // Synthesizer Emulation Functions
    LRESULT (*SF_GetAllSynthEmulations) ( SFDEVINDEX, PSFBUFFEROBJECT ) ;
    LRESULT (*SF_GetSynthEmulation)     ( SFDEVINDEX, PSFBUFFEROBJECT ) ;
    LRESULT (*SF_SelectSynthEmulation)  ( SFDEVINDEX, WORD ) ;

    // Sound Bank management functions
    LRESULT (*SF_LoadBank)  ( SFDEVINDEX, PSFMIDILOCATION, PSFBUFFEROBJECT ) ;
    LRESULT (*SF_GetLoadedBankDescriptor) ( SFDEVINDEX, PSFMIDILOCATION,
                                            PSFBUFFEROBJECT ) ;
    LRESULT (*SF_GetLoadedBankPathname) ( SFDEVINDEX, PSFMIDILOCATION,
                                          PSFBUFFEROBJECT ) ;
    LRESULT (*SF_ClearLoadedBank) ( SFDEVINDEX, PSFMIDILOCATION ) ;

    // Sound Preset management functions
    LRESULT (*SF_LoadPreset) ( SFDEVINDEX, PSFMIDILOCATION,
                               PSFMIDILOCATION, PSFBUFFEROBJECT ) ;
    LRESULT (*SF_GetLoadedPresetDescriptor) ( SFDEVINDEX, PSFMIDILOCATION,
                                              PSFBUFFEROBJECT ) ;
    LRESULT (*SF_ClearLoadedPreset) (SFDEVINDEX, PSFMIDILOCATION ) ;
 
    // Sound Waveform management functions
    LRESULT (*SF_LoadWaveform)  ( SFDEVINDEX, PSFMIDILOCATION, PSFBUFFEROBJECT ) ;
    LRESULT (*SF_ClearLoadedWaveform)  ( SFDEVINDEX, PSFMIDILOCATION ) ;

    // Device Specific Message
    LRESULT (*SF_DeviceSpecificMessage) ( SFDEVINDEX, UINT, LPARAM, LPARAM ) ;

} SFMANL101API , *PSFMANL101API ;


#endif   /* __SFMAN_H */

