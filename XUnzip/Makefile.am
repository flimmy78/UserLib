bin_PROGRAMS = XUnzip
XUnzip_SOURCES = XUnzip.cpp XUnzipFunctions.cpp

XUnzip_LDADD = ../WinSources/libWinSources.la
XUnzip_LDFLAGS = 
XUnzip_CFLAGS = 
XUnzip_CPPFLAGS = -I$(top_srcdir)/CSources -I$(top_srcdir)/CppSources -I$(top_srcdir)/WinSources
XUnzip_CXXFLAGS = -fexceptions -Wall

if DEBUG
XUnzip_CPPFLAGS += -D_DEBUG
XUnzip_CXXFLAGS += -g
else
XUnzip_CPPFLAGS += -DNDEBUG
XUnzip_CXXFLAGS += -O
endif
if COND_MINGW
XUnzip_LDADD += -lodbc32 -lodbccp32 -lws2_32 -lwsock32 -luser32 -ladvapi32 -lmsvcrt
XUnzip_CXXFLAGS += -mthreads
XUnzip_LDFLAGS += -mthreads
XUnzip_CPPFLAGS += -D_MINGW_CONSOLE
endif
if COND_MINGW64
XUnzip_CPPFLAGS += -D_MINGW64_CONSOLE
endif
if COND_UNICODE
XUnzip_CPPFLAGS += -DUNICODE
endif
