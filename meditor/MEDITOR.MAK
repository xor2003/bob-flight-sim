# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = MEDITOR.exe
OBJFILES = MEDITOR.obj About.obj AcItem.obj Static.obj MissText.obj \
   afselect.obj missobj.obj SelTarg.obj GrndGrp.obj currshp.obj info.obj \
   Confirm.obj Precomp.obj itemcnt.obj bfform.obj ..\BFIELDS\Meglobal.obj \
   ..\BFIELDS\Persons6.obj ..\BFIELDS\Persons5.obj 
   ..\BFIELDS\Persons2.obj Sgroups.obj gamestub.obj Memain.obj Memain2.obj \
   Loadsave.obj waypoint.obj ..\FILES\Fileman.obj mapload.obj Memain3.obj \
   Eventtxt.obj eventsel.obj Eventspn.obj ..\BFIELDS\Persons4.obj \
   ..\BFIELDS\persons7.obj NameList.obj TPaintWl.obj SGSelect.obj
RESFILES = Meditor.res
RESDEPEN = $(RESFILES) About.dfm AcItem.dfm Static.dfm MissText.dfm \
   afselect.dfm missobj.dfm SelTarg.dfm GrndGrp.dfm currshp.dfm info.dfm \
   Confirm.dfm Precomp.dfm itemcnt.dfm bfform.dfm Sgroups.dfm Memain.dfm \
   Loadsave.dfm waypoint.dfm Eventtxt.dfm eventsel.dfm Eventspn.dfm NameList.dfm \
   SGSelect.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -Od -w -k -r- -y -v -vi- -c -a4 -b- -w-par -w-inl -Vx -Ve -x -g255 \
   -j100
CFLAG2 = -Ii:..\files;i:..\bfields;..\bfields;..\files;$(BCB)\bin;$(BCB)\examples\controls\source;$(BCB)\images\buttons;.\icons;$(BCB)\projects;$(BCB)\examples\controls;c:\;$(BCB)\images;.\wav;$(BCB)\include;$(BCB)\include\vcl;..\h; 
PFLAGS = -Ui:..\files;i:..\bfields;..\bfields;..\files;$(BCB)\bin;$(BCB)\examples\controls\source;.\icons;$(BCB)\examples\controls;.\wav;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib \
   -Ii:..\files;i:..\bfields;..\bfields;..\files;$(BCB)\bin;$(BCB)\examples\controls\source;$(BCB)\images\buttons;.\icons;$(BCB)\projects;$(BCB)\examples\controls;c:\;$(BCB)\images;.\wav;$(BCB)\include;$(BCB)\include\vcl;..\h; 
   -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE -v \
   -$Y -$W -$O- -JPHNV -M     
RFLAGS = -ii:..\files;i:..\bfields;..\bfields;..\files;$(BCB)\bin;$(BCB)\examples\controls\source;$(BCB)\images\buttons;.\icons;$(BCB)\projects;$(BCB)\examples\controls;c:\;$(BCB)\images;.\wav;$(BCB)\include;$(BCB)\include\vcl;..\h; 
LFLAGS = -Li:..\files;i:..\bfields;..\bfields;..\files;$(BCB)\bin;$(BCB)\examples\controls\source;.\icons;$(BCB)\examples\controls;.\wav;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib \
   -Sc:0x80000 -aa -Tpe -x -v -V4.0 
IFLAGS = -g 
LINKER = tlink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
	$(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
