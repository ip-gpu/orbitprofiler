//-----------------------------------
// Copyright Pierric Gimmig 2013-2017
//-----------------------------------

#include "Diff.h"
#include "Core.h"
#include "Path.h"
#include "Params.h"

#include <fstream>
#include <Shellapi.h>

//-----------------------------------------------------------------------------
void Diff::Exec( const std::string & a_A, const std::string & a_B )
{
    std::wstring fileNameA = Path::GetTmpPath() + L"A.txt";
    std::wstring fileNameB = Path::GetTmpPath() + L"B.txt";

    std::ofstream fileA;
    std::ofstream fileB;

    fileA.open( fileNameA );
    fileB.open( fileNameB );

    if( fileA.fail() || fileB.fail() )
    {
        fileA.close();
        fileB.close();
        return;
    }

    fileA << a_A;
    fileB << a_B;

    fileA.close();
    fileB.close();

    std::wstring args = s2ws(GParams.m_DiffArgs);
    ReplaceStringInPlace( args, L"%1", fileNameA );
    ReplaceStringInPlace( args, L"%2", fileNameB );

    ShellExecute( 0, nullptr, s2ws(GParams.m_DiffExe).c_str(), args.c_str(), 0, SW_HIDE );
}

