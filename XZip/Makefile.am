bin_PROGRAMS = XZip
XZip_SOURCES = XZip.cpp XZipFunctions.cpp

XZip_LDADD = ../WinSources/libWinSources.la
XZip_LDFLAGS = 
XZip_CFLAGS = 
XZip_CPPFLAGS = -I$(top_srcdir)/CSources -I$(top_srcdir)/CppSources -I$(top_srcdir)/WinSources
XZip_CXXFLAGS = -fexceptions -Wall

if DEBUG
XZip_CPPFLAGS += -D_DEBUG
XZip_CXXFLAGS += -g
else
XZip_CPPFLAGS += -DNDEBUG
XZip_CXXFLAGS += -O
endif
if COND_MINGW
XZip_LDADD += -lodbc32 -lodbccp32 -lws2_32 -lwsock32 -luser32 -ladvapi32 -lmsvcrt
XZip_CXXFLAGS += -mthreads
XZip_LDFLAGS += -mthreads
XZip_CPPFLAGS += -D_MINGW_CONSOLE
endif
if COND_MINGW64
XZip_CPPFLAGS += -D_MINGW64_CONSOLE
endif
if COND_UNICODE
XZip_CPPFLAGS += -DUNICODE
endif
