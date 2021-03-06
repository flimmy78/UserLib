/******************************************************************************
    
	This file is part of XTest, which is part of UserLib.

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
#include "Program.h"
#include "BZip2Filter.h"
#include "ZLibFilter.h"
#include "GZipFilter.h"
#include "ZipFilter.h"
#include "LZMAFilter.h"
#include "XZFilter.h"
#include "WinCryptFilter.h"
#include "TarArchive.h"
#include "ZipArchive.h"
#include "FilterPipe.h"
#include "okDateTime.h"
#include "WProcess.h"
#include "DirectoryIterator.h"
#include "SecurityFile.h"
#include "SecurityContext.h"
#include "WinDirectoryIterator.h"

#ifdef OK_COMP_MSC
#define ENCRYPT_SRCFILE _T("pgadmin.log")
#define ENCRYPT_SRCFILE1 _T("pgadmin.log1")
#define ENCRYPT_DESTFILE  _T("pgadmin.sec")
#define ENCRYPT_PASSWD _T("ok09zu")

class CPPSOURCES_LOCAL CTestFilterOutput : public CFilterOutput
{
public:
	CTestFilterOutput(Ref(CByteLinkedBuffer) buf): _buffer(buf) {}
	virtual ~CTestFilterOutput() {}

	virtual void open() {}
	virtual void write(Ref(CByteBuffer) outputbuf) 
	{ 
		_buffer.AddBufferItem(outputbuf);
	}
	virtual void close() {}

public:
	Ref(CByteLinkedBuffer) _buffer;
};

class CPPSOURCES_API CTestFilterInput : public CFilterInput
{
public:
	CTestFilterInput(Ref(CByteLinkedBuffer) buf): _buffer(buf), _it(_buffer.Begin()) {}
	virtual ~CTestFilterInput() {}

	virtual void open() {}
	virtual CFile::TFileSize size() { return _buffer.GetTotalLength(); }
	virtual void read(Ref(CByteBuffer) inputbuf) 
	{
		_buffer.GetSubBuffer(_it, inputbuf);
		_it += inputbuf.get_BufferSize();
	}
	virtual void close() {}

public:
	Ref(CByteLinkedBuffer) _buffer;
	CByteLinkedBuffer::Iterator _it;
};

static void _TestEnCryptFilter()
{
	CFilePath fsrc(__FILE__LINE__ ENCRYPT_SRCFILE);
	CFilePath fdest(__FILE__LINE__ ENCRYPT_DESTFILE);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fsrc);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fdest))
		CDirectoryIterator::RemoveFile(fdest);
	pOutputFile->Create(fdest, false, CFile::BinaryFile_NoEncoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptEncryptFilter* pEncryptFilter = OK_NEW_OPERATOR CWinCryptEncryptFilter(pTestInput, pTestOutput);

	pEncryptFilter->open();
	pEncryptFilter->do_filter();
	pEncryptFilter->close();

	pEncryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

}

static void _TestEnCryptFilter2()
{
	CFilePath fsrc(__FILE__LINE__ ENCRYPT_SRCFILE);
	CFilePath fdest(__FILE__LINE__ ENCRYPT_DESTFILE);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fsrc);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fdest))
		CDirectoryIterator::RemoveFile(fdest);
	pOutputFile->Create(fdest, false, CFile::BinaryFile_NoEncoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptEncryptFilter* pEncryptFilter = OK_NEW_OPERATOR CWinCryptEncryptFilter(pTestInput, pTestOutput);

	pEncryptFilter->set_Password(ENCRYPT_PASSWD);

	pEncryptFilter->open();
	pEncryptFilter->do_filter();
	pEncryptFilter->close();

	pEncryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

}

static void _TestEnCryptFilter3()
{
	CFilePath fsrc(__FILE__LINE__ ENCRYPT_SRCFILE);
	CFilePath fdest(__FILE__LINE__ ENCRYPT_DESTFILE);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fsrc);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fdest))
		CDirectoryIterator::RemoveFile(fdest);
	pOutputFile->Create(fdest, false, CFile::BinaryFile_NoEncoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptEncryptFilter* pEncryptFilter = OK_NEW_OPERATOR CWinCryptEncryptFilter(pTestInput, pTestOutput);

	pEncryptFilter->set_Algorithm(1);
	pEncryptFilter->set_Password(ENCRYPT_PASSWD);

	pEncryptFilter->open();
	pEncryptFilter->do_filter();
	pEncryptFilter->close();

	pEncryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

}

static void _TestEnCryptFilter4(Ref(CByteLinkedBuffer) buf)
{
	CFilePath fsrc(__FILE__LINE__ ENCRYPT_SRCFILE);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fsrc);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CTestFilterOutput(buf);

	CWinCryptEncryptFilter* pEncryptFilter = OK_NEW_OPERATOR CWinCryptEncryptFilter(pTestInput, pTestOutput);

	pEncryptFilter->set_Algorithm(1);
	pEncryptFilter->set_Password(ENCRYPT_PASSWD);

	pEncryptFilter->open();
	pEncryptFilter->do_filter();
	pEncryptFilter->close();

	pEncryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pInputFile->release();

}

static void _TestEnCryptFilter5()
{
	CFilePath fsrc(__FILE__LINE__ ENCRYPT_SRCFILE);
	CFilePath fdest(__FILE__LINE__ ENCRYPT_DESTFILE);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fsrc);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fdest))
		CDirectoryIterator::RemoveFile(fdest);
	pOutputFile->Create(fdest, false, CFile::BinaryFile_NoEncoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptEncryptFilter* pEncryptFilter = OK_NEW_OPERATOR CWinCryptEncryptFilter(pTestInput, pTestOutput);

	pEncryptFilter->set_Algorithm(2);
	pEncryptFilter->set_Password(ENCRYPT_PASSWD);

	pEncryptFilter->open();
	pEncryptFilter->do_filter();
	pEncryptFilter->close();

	pEncryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

}

static void _TestEnCryptFilter6()
{
	CFilePath fsrc(__FILE__LINE__ ENCRYPT_SRCFILE);
	CFilePath fdest(__FILE__LINE__ ENCRYPT_DESTFILE);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fsrc);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fdest))
		CDirectoryIterator::RemoveFile(fdest);
	pOutputFile->Create(fdest, false, CFile::BinaryFile_NoEncoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptEncryptFilter* pEncryptFilter = OK_NEW_OPERATOR CWinCryptEncryptFilter(pTestInput, pTestOutput);

	pEncryptFilter->set_Algorithm(3);
	pEncryptFilter->set_Password(ENCRYPT_PASSWD);

	pEncryptFilter->open();
	pEncryptFilter->do_filter();
	pEncryptFilter->close();

	pEncryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

}

static void callfc(CConstPointer f1, CConstPointer f2)
{
	CProcess process;
	CFilePath cmd(__FILE__LINE__ _T("fc"));
	CStringBuffer args;
	CDataVectorT<CStringBuffer> env(__FILE__LINE__ 1, 1);
	CFilePath startDir;
	CByteBuffer buf;
	CStringBuffer sBuf;

	CDirectoryIterator::GetCurrentDirectory(startDir);
	args.AppendString(f1);
	args.AppendString(_T(" "));
	args.AppendString(f2);

	process.Create(cmd, args, env, startDir);

	process.Write(buf);
	buf.set_BufferSize(__FILE__LINE__ 128);
	process.Read(buf);
	while (buf.get_BufferSize() > 0)
	{
		sBuf.convertFromByteBuffer(buf);
		COUT << sBuf;
		process.Read(buf);
	}
	process.Close();
}

static void _TestDeCryptFilter()
{
	CFilePath fin(__FILE__LINE__ ENCRYPT_DESTFILE);
	CFilePath fout(__FILE__LINE__ ENCRYPT_SRCFILE1);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fin);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fout))
		CDirectoryIterator::RemoveFile(fout);
	pOutputFile->Create(fout, true, CFile::ISO_8859_1_Encoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptDecryptFilter* pDecryptFilter = OK_NEW_OPERATOR CWinCryptDecryptFilter(pTestInput, pTestOutput);

	pDecryptFilter->open();
	pDecryptFilter->do_filter();
	pDecryptFilter->close();

	pDecryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

	callfc(ENCRYPT_SRCFILE, ENCRYPT_SRCFILE1);
}

static void _TestDeCryptFilter2()
{
	CFilePath fin(__FILE__LINE__ ENCRYPT_DESTFILE);
	CFilePath fout(__FILE__LINE__ ENCRYPT_SRCFILE1);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fin);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fout))
		CDirectoryIterator::RemoveFile(fout);
	pOutputFile->Create(fout, true, CFile::ISO_8859_1_Encoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptDecryptFilter* pDecryptFilter = OK_NEW_OPERATOR CWinCryptDecryptFilter(pTestInput, pTestOutput);

	pDecryptFilter->set_Password(ENCRYPT_PASSWD);

	pDecryptFilter->open();
	pDecryptFilter->do_filter();
	pDecryptFilter->close();

	pDecryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

	callfc(ENCRYPT_SRCFILE, ENCRYPT_SRCFILE1);
}

static void _TestDeCryptFilter3()
{
	CFilePath fin(__FILE__LINE__ ENCRYPT_DESTFILE);
	CFilePath fout(__FILE__LINE__ ENCRYPT_SRCFILE1);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fin);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fout))
		CDirectoryIterator::RemoveFile(fout);
	pOutputFile->Create(fout, true, CFile::ISO_8859_1_Encoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptDecryptFilter* pDecryptFilter = OK_NEW_OPERATOR CWinCryptDecryptFilter(pTestInput, pTestOutput);

	pDecryptFilter->set_Algorithm(1);
	pDecryptFilter->set_Password(ENCRYPT_PASSWD);

	pDecryptFilter->open();
	pDecryptFilter->do_filter();
	pDecryptFilter->close();

	pDecryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

	callfc(ENCRYPT_SRCFILE, ENCRYPT_SRCFILE1);
}

static void _TestDeCryptFilter4(Ref(CByteLinkedBuffer) buf)
{
	CFilePath fout(__FILE__LINE__ ENCRYPT_SRCFILE1);

	CFilterInput* pTestInput = OK_NEW_OPERATOR CTestFilterInput(buf);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fout))
		CDirectoryIterator::RemoveFile(fout);
	pOutputFile->Create(fout, true, CFile::ISO_8859_1_Encoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptDecryptFilter* pDecryptFilter = OK_NEW_OPERATOR CWinCryptDecryptFilter(pTestInput, pTestOutput);

	pDecryptFilter->set_Algorithm(1);
	pDecryptFilter->set_Password(ENCRYPT_PASSWD);

	pDecryptFilter->open();
	pDecryptFilter->do_filter();
	pDecryptFilter->close();

	pDecryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();

	callfc(ENCRYPT_SRCFILE, ENCRYPT_SRCFILE1);
}

static void _TestDeCryptFilter5()
{
	CFilePath fin(__FILE__LINE__ ENCRYPT_DESTFILE);
	CFilePath fout(__FILE__LINE__ ENCRYPT_SRCFILE1);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fin);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fout))
		CDirectoryIterator::RemoveFile(fout);
	pOutputFile->Create(fout, true, CFile::ISO_8859_1_Encoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptDecryptFilter* pDecryptFilter = OK_NEW_OPERATOR CWinCryptDecryptFilter(pTestInput, pTestOutput);

	pDecryptFilter->set_Algorithm(2);
	pDecryptFilter->set_Password(ENCRYPT_PASSWD);

	pDecryptFilter->open();
	pDecryptFilter->do_filter();
	pDecryptFilter->close();

	pDecryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

	callfc(ENCRYPT_SRCFILE, ENCRYPT_SRCFILE1);
}

static void _TestDeCryptFilter6()
{
	CFilePath fin(__FILE__LINE__ ENCRYPT_DESTFILE);
	CFilePath fout(__FILE__LINE__ ENCRYPT_SRCFILE1);

	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(fin);
	CFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile;

	if (CDirectoryIterator::FileExists(fout))
		CDirectoryIterator::RemoveFile(fout);
	pOutputFile->Create(fout, true, CFile::ISO_8859_1_Encoding);

	CFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);

	CWinCryptDecryptFilter* pDecryptFilter = OK_NEW_OPERATOR CWinCryptDecryptFilter(pTestInput, pTestOutput);

	pDecryptFilter->set_Algorithm(3);
	pDecryptFilter->set_Password(ENCRYPT_PASSWD);

	pDecryptFilter->open();
	pDecryptFilter->do_filter();
	pDecryptFilter->close();

	pDecryptFilter->release();
	pTestOutput->release();
	pTestInput->release();
	pOutputFile->release();
	pInputFile->release();

	callfc(ENCRYPT_SRCFILE, ENCRYPT_SRCFILE1);
}
#else
#define callfc(a, b)
#endif

static void _TestFilterThreadedPipe()
{
	CDataVectorT<CStringBuffer> _output(__FILE__LINE__ 16, 16);
	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(CFilePath(__FILE__LINE__ _T("aspell.lst.gz")));
	CFileFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CStringVectorFilterOutput* pTestOutput = OK_NEW_OPERATOR CStringVectorFilterOutput(_output);
	CFilterThreadedPipeConnector* pConnector = OK_NEW_OPERATOR CFilterThreadedPipeConnector();
	CGZipDeCompressFilter* pDeCompressFilter = OK_NEW_OPERATOR CGZipDeCompressFilter(pTestInput, pConnector);
	CLineReadFilter* pLineReadFilter = OK_NEW_OPERATOR CLineReadFilter(pConnector, pTestOutput, CLineReadFilter::UnixLineEnd);
	CFilterThreadedPipe* pPipe = OK_NEW_OPERATOR CFilterThreadedPipe(pDeCompressFilter, pLineReadFilter);

	pPipe->do_pipe();

	CDataVectorT<CStringBuffer>::Iterator it = _output.Begin();
	int ix = 0;

	while (it)
	{
		COUT << *it << endl;
		++it;
		++ix;
	}
	COUT << _T("#LineCount=") << ix << endl;

	pPipe->release();
	pLineReadFilter->release();
	pDeCompressFilter->release();
	pConnector->release();

	pTestInput->release();
	pTestOutput->release();

	pInputFile->release();

}

static void _TestFilterPipe()
{
	CDataVectorT<CStringBuffer> _output(__FILE__LINE__ 16, 16);
	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(CFilePath(__FILE__LINE__ _T("aspell.lst.gz")));
	CFileFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CStringVectorFilterOutput* pTestOutput = OK_NEW_OPERATOR CStringVectorFilterOutput(_output);
	CFilterPipeConnector* pConnector = OK_NEW_OPERATOR CFilterPipeConnector();
	CGZipDeCompressFilter* pDeCompressFilter = OK_NEW_OPERATOR CGZipDeCompressFilter(pTestInput, pConnector);
	CLineReadFilter* pLineReadFilter = OK_NEW_OPERATOR CLineReadFilter(pConnector, pTestOutput, CLineReadFilter::UnixLineEnd);
	CFilterPipe* pPipe = OK_NEW_OPERATOR CFilterPipe(pDeCompressFilter, pLineReadFilter);

	pPipe->do_pipe();

	CDataVectorT<CStringBuffer>::Iterator it = _output.Begin();
	int ix = 0;

	while (it)
	{
		COUT << *it << endl;
		++it;
		++ix;
	}
	COUT << _T("#LineCount=") << ix << endl;

	pPipe->release();
	pLineReadFilter->release();
	pDeCompressFilter->release();
	pConnector->release();

	pTestInput->release();
	pTestOutput->release();

	pInputFile->release();

}

static void _TestFilter()
{
	CSecurityFile* pInputFile = OK_NEW_OPERATOR CSecurityFile(CFilePath(__FILE__LINE__ _T("aspell.lst.gz")));

	CWinDirectoryIterator::UnlinkFile(CFilePath(__FILE__LINE__ _T("aspell.lst")));

	CSecurityFile* pOutputFile = OK_NEW_OPERATOR CSecurityFile();

	pOutputFile->Create(CFilePath(__FILE__LINE__ _T("aspell.lst")), true, CFile::ISO_8859_1_Encoding);

	CFileFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(pInputFile);
	CFileFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(pOutputFile);
	CGZipDeCompressFilter* pFilter = OK_NEW_OPERATOR CGZipDeCompressFilter(pTestInput, pTestOutput);

	pFilter->open();
	pFilter->do_filter();
	pFilter->close();

	pFilter->release();
	pTestInput->release();
	pTestOutput->release();

	pInputFile->release();
	pOutputFile->release();

}

static void _TestFileFilter()
{
	CFileFilterInput* pTestInput1 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("XTest.exe")));
	CFileFilterOutput* pTestOutput1 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.bz2")));

	CBZip2CompressFilter* pFilter1 = OK_NEW_OPERATOR CBZip2CompressFilter(pTestInput1, pTestOutput1);

	pFilter1->open();
	pFilter1->do_filter();
	pFilter1->close();

	CFileFilterInput* pTestInput2 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("XTest.bz2")));
	CFileFilterOutput* pTestOutput2 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.ex1")));

	CBZip2DeCompressFilter* pFilter2 = OK_NEW_OPERATOR CBZip2DeCompressFilter(pTestInput2, pTestOutput2);

	pFilter2->open();
	pFilter2->do_filter();
	pFilter2->close();

	CFileFilterOutput* pTestOutput3 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.z")));

	CZLibCompressFilter* pFilter3 = OK_NEW_OPERATOR CZLibCompressFilter(pTestInput1, pTestOutput3);

	pFilter3->open();
	pFilter3->do_filter();
	pFilter3->close();

	CFileFilterInput* pTestInput4 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("XTest.z")));
	CFileFilterOutput* pTestOutput4 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.ex2")));

	CZLibDeCompressFilter* pFilter4 = OK_NEW_OPERATOR CZLibDeCompressFilter(pTestInput4, pTestOutput4);

	pFilter4->open();
	pFilter4->do_filter();
	pFilter4->close();

	CFileFilterOutput* pTestOutput5 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.gz")));

	CGZipCompressFilter* pFilter5 = OK_NEW_OPERATOR CGZipCompressFilter(pTestInput1, pTestOutput5);

	pFilter5->open();
	pFilter5->do_filter();
	pFilter5->close();

	CFileFilterInput* pTestInput6 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("XTest.gz")));
	CFileFilterOutput* pTestOutput6 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.ex3")));

	CGZipDeCompressFilter* pFilter6 = OK_NEW_OPERATOR CGZipDeCompressFilter(pTestInput6, pTestOutput6);

	pFilter6->open();
	pFilter6->do_filter();
	pFilter6->close();

	CFileFilterOutput* pTestOutput7 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.lzma")));

	CLZMACompressFilter* pFilter7 = OK_NEW_OPERATOR CLZMACompressFilter(pTestInput1, pTestOutput7);

	pFilter7->open();
	pFilter7->do_filter();
	pFilter7->close();

	CFileFilterInput* pTestInput8 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("XTest.lzma")));
	CFileFilterOutput* pTestOutput8 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.ex4")));

	CLZMADeCompressFilter* pFilter8 = OK_NEW_OPERATOR CLZMADeCompressFilter(pTestInput8, pTestOutput8);

	pFilter8->open();
	pFilter8->do_filter();
	pFilter8->close();

	CFileFilterOutput* pTestOutput9 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.xz")));

	CXZCompressFilter* pFilter9 = OK_NEW_OPERATOR CXZCompressFilter(pTestInput1, pTestOutput9);

	pFilter9->open();
	pFilter9->do_filter();
	pFilter9->close();

	CFileFilterInput* pTestInput10 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("XTest.xz")));
	CFileFilterOutput* pTestOutput10 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.ex5")));

	CXZDeCompressFilter* pFilter10 = OK_NEW_OPERATOR CXZDeCompressFilter(pTestInput10, pTestOutput10);

	pFilter10->open();
	pFilter10->do_filter();
	pFilter10->close();

	CFileFilterOutput* pTestOutput11 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.zip")));

	CZipCompressFilter* pFilter11 = OK_NEW_OPERATOR CZipCompressFilter(pTestInput1, pTestOutput11);

	pFilter11->open();
	pFilter11->do_filter();
	pFilter11->close();

	CFileFilterInput* pTestInput12 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("XTest.zip")));
	CFileFilterOutput* pTestOutput12 = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("XTest.ex6")));

	CZipDeCompressFilter* pFilter12 = OK_NEW_OPERATOR CZipDeCompressFilter(pTestInput12, pTestOutput12);

	pFilter12->open();
	pFilter12->do_filter();
	pFilter12->close();

	pFilter1->release();
	pFilter2->release();
	pFilter3->release();
	pFilter4->release();
	pFilter5->release();
	pFilter6->release();
	pFilter7->release();
	pFilter8->release();
	pFilter9->release();
	pFilter10->release();
	pFilter11->release();
	pFilter12->release();

	pTestInput1->release();
	pTestInput2->release();
	pTestInput4->release();
	pTestInput6->release();
	pTestInput8->release();
	pTestInput10->release();
	pTestInput12->release();

	pTestOutput1->release();
	pTestOutput2->release();
	pTestOutput3->release();
	pTestOutput4->release();
	pTestOutput5->release();
	pTestOutput6->release();
	pTestOutput7->release();
	pTestOutput8->release();
	pTestOutput9->release();
	pTestOutput10->release();
	pTestOutput11->release();
	pTestOutput12->release();

	callfc(_T("XTest.exe"), _T("XTest.ex1"));
	callfc(_T("XTest.exe"), _T("XTest.ex2"));
	callfc(_T("XTest.exe"), _T("XTest.ex3"));
	callfc(_T("XTest.exe"), _T("XTest.ex4"));
	callfc(_T("XTest.exe"), _T("XTest.ex5"));
	callfc(_T("XTest.exe"), _T("XTest.ex6"));
}

static void _TestArchive()
{
	CFilePath curDir;

	CDirectoryIterator::GetCurrentDirectory(curDir);

	CFileFilterInput* pTestInput = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("libagg2-2.5-2.tar.xz")));
	CFileFilterOutput* pTestOutput = OK_NEW_OPERATOR CFileFilterOutput(CFilePath(__FILE__LINE__ _T("libagg2-2.5-2.tar")));

	CXZDeCompressFilter* pFilter = OK_NEW_OPERATOR CXZDeCompressFilter(pTestInput, pTestOutput);

	pFilter->open();
	pFilter->do_filter();
	pFilter->close();

	pFilter->release();
	pTestInput->release();
	pTestOutput->release();

	if (CDirectoryIterator::DirectoryExists(CFilePath(__FILE__LINE__ _T("usr"))) >= 0)
		CDirectoryIterator::RemoveDirectory(CFilePath(__FILE__LINE__ _T("usr")));

	CSecurityFile* pArchiveFile = OK_NEW_OPERATOR CSecurityFile(CFilePath(__FILE__LINE__ _T("libagg2-2.5-2.tar")));

	CTarArchive tarArchive(pArchiveFile);
	CArchiveIterator *tarIt = tarArchive.begin();

	while ( tarIt->Next() )
	{
		switch ( tarIt->GetType() )
		{
		case CArchiveIterator::ARCHIVE_FILE_REGULAR:
			{
				CStringBuffer tmp(__FILE__LINE__ tarIt->GetFileName());
				CFilePath fpath(tmp, CDirectoryIterator::UnixPathSeparatorString());
				CFilePath fpath1;

				COUT << _T("ARCHIVE_FILE_REGULAR: ") << tmp << endl;
				fpath.Normalize(curDir.GetString());

				fpath1 = fpath;
				fpath1.set_Filename(_T(""));
				CDirectoryIterator::MakeDirectory(fpath1);

				sqword vfiletime;
				sqword vfilemode;
				bool isNull;

				tarIt->GetProperty(_T("FILETIME"), vfiletime, isNull);
				tarIt->GetProperty(_T("FILEMODE"), vfilemode, isNull);

				CSecurityFile* ofile = OK_NEW_OPERATOR CSecurityFile();

				ofile->Create(fpath, false, CFile::BinaryFile_NoEncoding, Cast(mode_t, vfilemode));

				CArchiveFile* afile = tarIt->GetFile();
				CFileFilterInput* pInput = OK_NEW_OPERATOR CFileFilterInput(afile);
				CFileFilterOutput* pOutput = OK_NEW_OPERATOR CFileFilterOutput(ofile);
				CCopyFilter* pFilter = OK_NEW_OPERATOR CCopyFilter(pInput, pOutput);

				pFilter->open();
				pFilter->do_filter();
				pFilter->close();

				pFilter->release();
				pInput->release();
				pOutput->release();
				afile->release();
				ofile->release();

#ifdef OK_SYS_WINDOWS
				CDateTime ftime(Cast(time_t, vfiletime));

				CWinDirectoryIterator::WriteFileTimes(fpath, ftime, ftime, ftime);
#endif
#ifdef OK_SYS_UNIX
				CDateTime ftime1(Cast(time_t, vfiletime), CDateTime::LocalTime);
				CDateTime ftime2(Cast(time_t, vfiletime), CDateTime::LocalTime);
				CDateTime ftime3(Cast(time_t, vfiletime), CDateTime::LocalTime);

				CWinDirectoryIterator::WriteFileTimes(fpath, ftime1, ftime2, ftime3);
#endif
			}
			break;
		case CArchiveIterator::ARCHIVE_FILE_DIRECTORY:
			{
				CStringBuffer tmp = tarIt->GetFileName();
				CFilePath fpath(tmp, CDirectoryIterator::UnixPathSeparatorString());

				COUT << _T("ARCHIVE_FILE_DIRECTORY: ") << tmp << endl;
				fpath.Normalize(curDir.GetString());

				sqword vfiletime;
				sqword vfilemode;
				bool isNull;

				tarIt->GetProperty(_T("FILETIME"), vfiletime, isNull);
				tarIt->GetProperty(_T("FILEMODE"), vfilemode, isNull);
				
				CWinDirectoryIterator::MakeDirectory(fpath, Cast(mode_t, vfilemode));

#ifdef OK_SYS_WINDOWS
				CDateTime ftime(Cast(time_t, vfiletime));
#endif
#ifdef OK_SYS_UNIX
				CDateTime ftime(Cast(time_t, vfiletime), CDateTime::LocalTime);
#endif
				CWinDirectoryIterator::WriteFileTimes(fpath, ftime, ftime, ftime);
			}
			break;
		case CArchiveIterator::ARCHIVE_FILE_HARDLINK:
			COUT << _T("ARCHIVE_FILE_HARDLINK: ") << tarIt->GetFileName() << _T(":") << tarIt->GetLinkName() << endl;
			break;
		case CArchiveIterator::ARCHIVE_FILE_SYMLINK:
			COUT << _T("ARCHIVE_FILE_SYMLINK: ") << tarIt->GetFileName() << _T(":") << tarIt->GetLinkName() << endl;
			break;
		default:
			COUT << _T("Unknown type") << endl;
			break;
		}
	}
	tarIt->release();
	pArchiveFile->release();

}

static void _TestLineCopyFilter()
{
#ifdef OK_SYS_WINDOWS
	CFileFilterInput* pTestInput1 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("c:\\cygwin\\etc\\setup\\installed.db")));
#endif
#ifdef OK_SYS_UNIX
	CFileFilterInput* pTestInput1 = OK_NEW_OPERATOR CFileFilterInput(CFilePath(__FILE__LINE__ _T("/etc/setup/installed.db")));
#endif
	CStdOutFilterOutput* pTestOutput1 = OK_NEW_OPERATOR CStdOutFilterOutput(true);

	CLineReadFilter* pFilter1 = OK_NEW_OPERATOR CLineReadFilter(pTestInput1, pTestOutput1, CLineReadFilter::UnixLineEnd);

	pFilter1->open();
	pFilter1->do_filter();
	pFilter1->close();

	pTestInput1->release();
	pTestOutput1->release();
	pFilter1->release();
}

static void _TestZipArchive()
{
	CFilePath curDir(__FILE__LINE__ _T("UserLib"));
	CSecurityFile* pArchiveFile = OK_NEW_OPERATOR CSecurityFile(CFilePath(__FILE__LINE__ _T("UserLib.zip")));

	CZipArchive zipArchive(pArchiveFile);
	CArchiveIterator *zipIt = zipArchive.begin();

	if (CDirectoryIterator::DirectoryExists(curDir) >= 0)
		CDirectoryIterator::RemoveDirectory(curDir);
	CDirectoryIterator::MakeDirectory(curDir);
	CDirectoryIterator::SetCurrentDirectory(curDir);

	CDirectoryIterator::GetCurrentDirectory(curDir);

	while ( zipIt->Next() )
	{
		switch ( zipIt->GetType() )
		{
		case CArchiveIterator::ARCHIVE_FILE_REGULAR:
			{
				CStringBuffer tmp = zipIt->GetFileName();
				CFilePath fpath(tmp, CDirectoryIterator::UnixPathSeparatorString());
				CFilePath fpath1;

				COUT << _T("ARCHIVE_FILE_REGULAR: ") << tmp << endl;
				fpath.Normalize(curDir.GetString());

				fpath1 = fpath;
				fpath1.set_Filename(_T(""));
				CDirectoryIterator::MakeDirectory(fpath1);

				sqword crc32;
				sqword uncompressedsize;
				sqword lastmodfiletime;
				bool isNull;

				zipIt->GetProperty(_T("CRC32"), crc32, isNull);
				zipIt->GetProperty(_T("UNCOMPRESSEDSIZE"), uncompressedsize, isNull);
				zipIt->GetProperty(_T("DOSFILETIME"), lastmodfiletime, isNull);

				CDateTime plastmodfiletime(Cast(time_t, lastmodfiletime));

				CArchiveFile* afile = zipIt->GetFile();
				CFileFilterInput* pInput = OK_NEW_OPERATOR CFileFilterInput(afile);
				CFileFilterOutput* pOutput = OK_NEW_OPERATOR CFileFilterOutput(fpath);
				CZipDeCompressFilter* pFilter = OK_NEW_OPERATOR CZipDeCompressFilter(pInput, pOutput);

				pFilter->open();
				pFilter->do_filter();
				pFilter->close();

				if ( Castdword(crc32) != pFilter->get_crc32() )
					COUT << tmp << _T(" crc32 mismatch") << endl;
				if ( Castdword(uncompressedsize) != pFilter->get_unCompressedSize() )
					COUT << tmp << _T(" uncompressedsize mismatch") << endl;

				CWinDirectoryIterator::WriteFileTimes(fpath, plastmodfiletime, plastmodfiletime, plastmodfiletime);

				pFilter->release();
				pInput->release();
				pOutput->release();
				afile->release();
			}
			break;
		case CArchiveIterator::ARCHIVE_FILE_DIRECTORY:
			{
				CStringBuffer tmp = zipIt->GetFileName();
				CFilePath fpath(tmp, CDirectoryIterator::UnixPathSeparatorString());

				COUT << _T("ARCHIVE_FILE_DIRECTORY: ") << tmp << endl;
				fpath.Normalize(curDir.GetString());
				CDirectoryIterator::MakeDirectory(fpath);
			}
			break;
		default:
			COUT << _T("Unknown type") << endl;
			break;
		}
	}
	zipIt->release();
	pArchiveFile->release();
}


static void _TestZipArchive2(Ref(CZipArchive) zipArchive, ConstRef(CFilePath) dir, ConstRef(CStringBuffer) pattern, bool bIsFSNTFS)
{
	CDirectoryIterator it;
	CFilePath fpath(dir);
	CDateTime ftime;
	FILETIME cftime;
	FILETIME aftime;
	FILETIME mftime;
	CArchiveProperties fprops;

	fpath.set_Filename(pattern);
	it.Open(fpath);

	while ( it )
	{
		CFilePath fpath1(dir);

		if ( !(it.is_SubDir()) )
		{
			CDateTime mtime(it.get_LastWriteTime());
			time_t t0;

			mtime.GetTime(t0);
			fpath1.set_Filename(it.get_Name());
			fprops.ClearProperties();
			fprops.SetProperty(_T("FILESIZE"), Cast(sqword, it.get_FileSize()));
			fprops.SetProperty(_T("FILETIME"), Cast(sqword, t0));
			if (bIsFSNTFS)
			{
				CWinDirectoryIterator::_ReadFileTimes(fpath1, &cftime, &aftime, &mftime);
				fprops.SetProperty(_T("NTFSCRTIME"), DerefAnyPtr(sqword, &cftime));
				fprops.SetProperty(_T("NTFSLATIME"), DerefAnyPtr(sqword, &aftime));
				fprops.SetProperty(_T("NTFSLWTIME"), DerefAnyPtr(sqword, &mftime));
			}
			COUT << fpath1.GetString() << endl;
			zipArchive.AddFile(fpath1, fprops);
		}
		++it;
	}

	fpath.set_Filename(_T("*"));
	it.Open(fpath);

	while ( it )
	{
		CFilePath fpath1(dir);

		if ( it.is_SubDir() )
		{
			fpath1.append_Directory(it.get_Name());
			_TestZipArchive2(zipArchive, fpath1, pattern, bIsFSNTFS);
		}
		++it;
	}
}

static void _TestZipArchive1()
{
	CDirectoryIterator::SetCurrentDirectory(CFilePath(__FILE__LINE__ _T("UserLibTest")));

	CSecurityFile* pArchiveFile = OK_NEW_OPERATOR CSecurityFile();
	CFilePath fpath(__FILE__LINE__ _T("UserLibTest1.zip"));

	if (CDirectoryIterator::FileExists(fpath))
		CDirectoryIterator::RemoveFile(fpath);
	pArchiveFile->Create(fpath, false, CFile::BinaryFile_NoEncoding);

	CZipArchive zipArchive(pArchiveFile);

	CDirectoryIterator it;
	CDataVectorT<CStringBuffer> filePatterns(__FILE__LINE__ 16, 16);
	CDataVectorT<CStringBuffer>::Iterator itP;
	CDateTime ftime;
	FILETIME cftime;
	FILETIME aftime;
	FILETIME mftime;
	CArchiveProperties fprops;
	bool bIsFSNTFS = false;

	CDirectoryIterator::GetCurrentDirectory(fpath);
	bIsFSNTFS = CWinDirectoryIterator::FileSystemIsNTFS(fpath);

#ifdef OK_SYS_WINDOWS
	filePatterns.Split(CStringBuffer(__FILE__LINE__ _T("*.h *.c *.cpp *.ico *.rc *.sln *.vcxproj makefile Makefile.am configure.ac")), _T(" "));
#endif
#ifdef OK_SYS_UNIX
	filePatterns.Split(CStringBuffer(__FILE__LINE__ _T("*.h *.H *.c *.C *.cpp *.ico *.rc *.sln *.vcxproj makefile Makefile Makefile.am configure.ac")), _T(" "));
#endif
	itP = filePatterns.Begin();
	while ( itP )
	{
		it.Open(*itP);
		fpath.set_Path(__FILE__LINE__ _T(""));

		while ( it )
		{
			if ( !(it.is_SubDir()) )
			{
				CDateTime mtime(it.get_LastWriteTime());
				time_t t0;

				mtime.GetTime(t0);
				fpath.set_Filename(it.get_Name());
				fprops.ClearProperties();
				fprops.SetProperty(_T("FILESIZE"), Cast(sqword, it.get_FileSize()));
				fprops.SetProperty(_T("FILETIME"), Cast(sqword, t0));
				if (bIsFSNTFS)
				{
					CWinDirectoryIterator::_ReadFileTimes(fpath, &cftime, &aftime, &mftime);
					fprops.SetProperty(_T("NTFSCRTIME"), DerefAnyPtr(sqword, &cftime));
					fprops.SetProperty(_T("NTFSLATIME"), DerefAnyPtr(sqword, &aftime));
					fprops.SetProperty(_T("NTFSLWTIME"), DerefAnyPtr(sqword, &mftime));
				}
				COUT << fpath.GetString() << endl;
				zipArchive.AddFile(fpath, fprops);
			}
			++it;
		}

		it.Open(CFilePath(__FILE__LINE__ _T("*")));
		fpath.set_Path(__FILE__LINE__ _T(""));

		while ( it )
		{
			if ( it.is_SubDir() )
			{
				fpath.set_Directory(it.get_Name());
				_TestZipArchive2(zipArchive, fpath, *itP, bIsFSNTFS);
			}
			++it;
		}
		++itP;
	}
	zipArchive.AddClose();
	pArchiveFile->release();
}

void TestFileFilter()
{
	CFilePath curdir;

	CDirectoryIterator::GetCurrentDirectory(curdir);

	try
	{
		COUT << _T("********** _TestFilter ************") << endl;
		_TestFilter();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestFileFilter ************") << endl;
		_TestFileFilter();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestFilterPipe ************") << endl;
		_TestFilterPipe();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestFilterThreadedPipe ************") << endl;
		_TestFilterThreadedPipe();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestArchive ************") << endl;
		_TestArchive();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestLineCopyFilter ************") << endl;
		_TestLineCopyFilter();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestZipArchive ************") << endl;
		_TestZipArchive();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}

	CDirectoryIterator::SetCurrentDirectory(curdir);

	try
	{
		COUT << _T("********** _TestZipArchive1 ************") << endl;
		_TestZipArchive1();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}

	CDirectoryIterator::SetCurrentDirectory(curdir);

#ifdef OK_COMP_MSC
	try
	{
		COUT << _T("********** _TestEnCryptFilter ************") << endl;
		_TestEnCryptFilter();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestDeCryptFilter ************") << endl;
		_TestDeCryptFilter();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestEnCryptFilter2 ************") << endl;
		_TestEnCryptFilter2();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestDeCryptFilter2 ************") << endl;
		_TestDeCryptFilter2();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestEnCryptFilter3 ************") << endl;
		_TestEnCryptFilter3();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestDeCryptFilter3 ************") << endl;
		_TestDeCryptFilter3();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	
	CByteLinkedBuffer buf;
	
	try
	{
		COUT << _T("********** _TestEnCryptFilter4 ************") << endl;
		_TestEnCryptFilter4(buf);
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestDeCryptFilter4 ************") << endl;
		_TestDeCryptFilter4(buf);
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestEnCryptFilter5 ************") << endl;
		_TestEnCryptFilter5();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestDeCryptFilter5 ************") << endl;
		_TestDeCryptFilter5();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestEnCryptFilter6 ************") << endl;
		_TestEnCryptFilter6();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
	try
	{
		COUT << _T("********** _TestDeCryptFilter6 ************") << endl;
		_TestDeCryptFilter6();
	}
	catch (CBaseException* ex)
	{
		COUT << ex->GetExceptionMessage() << endl;
	}
#endif
	CSecurityContext_FreeInstance
}