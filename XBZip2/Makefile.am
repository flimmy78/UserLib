bin_PROGRAMS = XBZip2
XBZip2_SOURCES = XBZip2.cpp XBZip2Functions.cpp

XBZip2_LDADD = ../WinSources/libWinSources.la
XBZip2_LDFLAGS = 
XBZip2_CFLAGS = 
XBZip2_CPPFLAGS = -I$(top_srcdir)/CSources -I$(top_srcdir)/CppSources -I$(top_srcdir)/WinSources
XBZip2_CXXFLAGS = -fexceptions -Wall

if DEBUG
XBZip2_CPPFLAGS += -D_DEBUG
XBZip2_CXXFLAGS += -g
else
XBZip2_CPPFLAGS += -DNDEBUG
XBZip2_CXXFLAGS += -O
endif
if COND_MINGW
XBZip2_LDADD += -lodbc32 -lodbccp32 -lws2_32 -lwsock32 -luser32 -ladvapi32 -lmsvcrt
XBZip2_CXXFLAGS += -mthreads
XBZip2_LDFLAGS += -mthreads
XBZip2_CPPFLAGS += -D_MINGW_CONSOLE
endif
if COND_MINGW64
XBZip2_CPPFLAGS += -D_MINGW64_CONSOLE
endif
if COND_UNICODE
XBZip2_CPPFLAGS += -DUNICODE
endif
