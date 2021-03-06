/******************************************************************************
    
	This file is part of XCheckSum, which is part of UserLib.

    Copyright (C) 1995-2014  Oliver Kreis (okdev10@arcor.de)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by 
	the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/
// stdafx.h : Includedatei f�r Standardsystem-Includedateien
// oder h�ufig verwendete projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.
//

#pragma once

#include "PDEFS.H"

#include "CppObject.h"
#include "StringLiteral.h"
#include "StringBuffer.h"
#include "ByteBuffer.h"
#include "DataVector.h"
#include "FilePath.h"

#include <iostream>

#ifdef _UNICODE
#define COUT std::wcout
#define CERR std::wcerr
#define OSTREAM std::wostream
#else
#define COUT std::cout
#define CERR std::cerr
#define OSTREAM std::ostream
#endif
using std::endl;

void f_md4(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_md5(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_sha(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_sha1(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_dss(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_dss1(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_mdc2(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_ripemd160(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_sha224(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_sha256(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_sha384(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);
void f_sha512(ConstRef(CFilePath) a, ConstRef(CStringBuffer) r);

