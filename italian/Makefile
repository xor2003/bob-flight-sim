### Generated by Winemaker 0.7.6


SRCDIR                = .
DLLS                  =
EXES                  = litacln \
			litares



### Common settings

CEXTRA                = -mno-cygwin \
			-m32
CXXEXTRA              = -mno-cygwin \
			-m32
RCEXTRA               =
DEFINES               =
INCLUDE_PATH          = -I../h
DLL_PATH              =
DLL_IMPORTS           =
LIBRARY_PATH          =
LIBRARIES             =


### Extra source lists

EXTRA_C_SRCS          =
EXTRA_CXX_SRCS        =
EXTRA_RC_SRCS         = bob.rc \
			mig.rc \
			mig2.rc

EXTRA_OBJS            = $(EXTRA_C_SRCS:.c=.o) \
			$(EXTRA_CXX_SRCS:.cpp=.o)



### litacln sources and settings

litacln_MODULE        = litacln
litacln_C_SRCS        =
litacln_CXX_SRCS      =
litacln_RC_SRCS       =
litacln_LDFLAGS       = -mwindows \
			-mno-cygwin \
			-m32
litacln_DLL_PATH      =
litacln_DLLS          = odbc32 \
			ole32 \
			oleaut32 \
			winspool \
			odbccp32
litacln_LIBRARY_PATH  =
litacln_LIBRARIES     = uuid

litacln_OBJS          = $(litacln_C_SRCS:.c=.o) \
			$(litacln_CXX_SRCS:.cpp=.o) \
			$(litacln_RC_SRCS:.rc=.res)



### litares sources and settings

litares_MODULE        = litares
litares_C_SRCS        =
litares_CXX_SRCS      =
litares_RC_SRCS       =
litares_LDFLAGS       = -mwindows \
			-mno-cygwin \
			-m32
litares_DLL_PATH      =
litares_DLLS          = odbc32 \
			ole32 \
			oleaut32 \
			winspool \
			odbccp32
litares_LIBRARY_PATH  =
litares_LIBRARIES     = uuid

litares_OBJS          = $(litares_C_SRCS:.c=.o) \
			$(litares_CXX_SRCS:.cpp=.o) \
			$(litares_RC_SRCS:.rc=.res)



### Global source lists

C_SRCS                = $(litacln_C_SRCS) \
			$(litares_C_SRCS) \
			$(EXTRA_C_SRCS)
CXX_SRCS              = $(litacln_CXX_SRCS) \
			$(litares_CXX_SRCS) \
			$(EXTRA_CXX_SRCS)
RC_SRCS               = $(litacln_RC_SRCS) \
			$(litares_RC_SRCS) \
			$(EXTRA_RC_SRCS)


### Tools

CC = winegcc
CXX = wineg++
RC = wrc


### Generic targets

all: $(DLLS:%=%.so) $(EXES)

### Build rules

.PHONY: all clean dummy

$(SUBDIRS): dummy
	@cd $@ && $(MAKE)

# Implicit rules

.SUFFIXES: .cpp .rc .res
DEFINCL = $(INCLUDE_PATH) $(DEFINES) $(OPTIONS)

.c.o:
	$(CC) -c $(CFLAGS) $(CEXTRA) $(DEFINCL) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CXXEXTRA) $(DEFINCL) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(CXXEXTRA) $(DEFINCL) -o $@ $<

.rc.res:
	$(RC) $(RCFLAGS) $(RCEXTRA) $(DEFINCL) -fo$@ $<

# Rules for cleaning

CLEAN_FILES     = y.tab.c y.tab.h lex.yy.c core *.orig *.rej \
                  \\\#*\\\# *~ *% .\\\#*

clean:: $(SUBDIRS:%=%/__clean__) $(EXTRASUBDIRS:%=%/__clean__)
	$(RM) $(CLEAN_FILES) $(RC_SRCS:.rc=.res) $(C_SRCS:.c=.o) $(CXX_SRCS:.cpp=.o)
	$(RM) $(DLLS:%=%.so) $(EXES) $(EXES:%=%.so)

$(SUBDIRS:%=%/__clean__): dummy
	cd `dirname $@` && $(MAKE) clean

$(EXTRASUBDIRS:%=%/__clean__): dummy
	-cd `dirname $@` && $(RM) $(CLEAN_FILES)

### Target specific build rules
DEFLIB = $(LIBRARY_PATH) $(LIBRARIES) $(DLL_PATH) $(DLL_IMPORTS:%=-l%)

$(litacln_MODULE): $(litacln_OBJS)
	$(CC) $(litacln_LDFLAGS) -o $@ $(litacln_OBJS) $(litacln_LIBRARY_PATH) $(DEFLIB) $(litacln_DLLS:%=-l%) $(litacln_LIBRARIES:%=-l%)


$(litares_MODULE): $(litares_OBJS)
	$(CC) $(litares_LDFLAGS) -o $@ $(litares_OBJS) $(litares_LIBRARY_PATH) $(DEFLIB) $(litares_DLLS:%=-l%) $(litares_LIBRARIES:%=-l%)


