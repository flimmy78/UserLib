includedir = $(prefix)/include/UserLib/CryptSources
lib_LTLIBRARIES = libCryptSources.la
libCryptSources_la_SOURCES = AES.C BLOWFISH.C CBC.C CFB.C CTR.C DES.C MD2.C MD4.C MD5.C OFB.C SHA1.C SHA256.C SHA512.C TWOFISH.C XTS.C 
include_HEADERS = CIPHER.H DES.H HASH.H TWOFISH.H

libCryptSources_la_LDFLAGS = -no-undefined -version-info 1 -mthreads
libCryptSources_la_LIBADD = -lpthread
libCryptSources_la_CPPFLAGS = -I$(top_srcdir)/CSources
libCryptSources_la_CXXFLAGS = -mthreads
if DEBUG
libCryptSources_la_CPPFLAGS += -D_DEBUG
libCryptSources_la_CXXFLAGS += -g
else
libCryptSources_la_CPPFLAGS += -DNDEBUG
libCryptSources_la_CXXFLAGS += -O
endif
if COND_UNICODE
libCryptSources_la_CPPFLAGS += -DUNICODE
endif
