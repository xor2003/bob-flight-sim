### Generated by Winemaker 0.7.6


SRCDIR                = .
DLLS                  =
EXES                  = redtbt



### Common settings

CEXTRA                = -mno-cygwin \
			-m32
CXXEXTRA              = -mno-cygwin \
			-m32
RCEXTRA               =
DEFINES               =
INCLUDE_PATH          = -I../h \
			-I. \
			$(MFC_INCLUDE_PATH)
DLL_PATH              =
DLL_IMPORTS           =
LIBRARY_PATH          =
LIBRARIES             =


### redtbt sources and settings

redtbt_MODULE         = redtbt
redtbt_C_SRCS         =
redtbt_CXX_SRCS       = redtbt.cpp \
			redtbtc.cpp \
			redtbtp.cpp
redtbt_RC_SRCS        = redtbt.rc
redtbt_LDFLAGS        = -mwindows \
			-mno-cygwin \
			-m32
redtbt_DLL_PATH       = $(MFC_LIBRARY_PATH)
redtbt_DLLS           = odbc32 \
			ole32 \
			oleaut32 \
			winspool \
			odbccp32 \
			mfc.dll
redtbt_LIBRARY_PATH   = $(MFC_LIBRARY_PATH)
redtbt_LIBRARIES      = uuid \
			mfc

redtbt_OBJS           = $(redtbt_C_SRCS:.c=.o) \
			$(redtbt_CXX_SRCS:.cpp=.o) \
			$(redtbt_RC_SRCS:.rc=.res)



### Global source lists

C_SRCS                = $(redtbt_C_SRCS)
CXX_SRCS              = $(redtbt_CXX_SRCS)
RC_SRCS               = $(redtbt_RC_SRCS)


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

$(redtbt_MODULE): $(redtbt_OBJS)
	$(CXX) $(redtbt_LDFLAGS) -o $@ $(redtbt_OBJS) $(redtbt_LIBRARY_PATH) $(DEFLIB) $(redtbt_DLLS:%=-l%) $(redtbt_LIBRARIES:%=-l%)


