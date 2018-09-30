#include "stdafx.h"
#include "CMyLCG.h"


CMyLCG::CMyLCG()
{
}

CMyLCG::CMyLCG(ULONG32 initParamA, ULONG32 initParamC)
{
	InitializeParameters(initParamA, initParamC);
}

CMyLCG::~CMyLCG()
{
}

void CMyLCG::InitializeParameters(ULONG32 initParamA, ULONG32 initParamC)
{
	aParamM = MAXULONG32;
	aParamM++;

	ULONG64 tempA = initParamA % (aParamM / 4);
	if (tempA == 0)
	{
		tempA = 1;
	}
	aParamA = tempA * 4 + 1;

	ULONG64 tempC = initParamC % (aParamM / 2);
	aParamC = tempC * 2 + 1;
}

void CMyLCG::Start(ULONG32 seed)
{
	aValueX = seed;
}

ULONG32 CMyLCG::Next()
{
	aValueX = (aParamA * aValueX + aParamC) % aParamM;
	return (ULONG32)aValueX;
}

CString CMyLCG::ToString(bool hexFormat)
{
	if (hexFormat)
	{
		CString paramString("");
		paramString.Format((LPCTSTR)L"M = 0x%x\r\nA = 0x%x\r\nC = 0x%x", aParamM, aParamA, aParamC);
		return paramString;
	}
	else
	{
		CString paramString("");
		paramString.Format((LPCTSTR)L"M = %li\r\nA = %li\r\nC = %li", aParamM, aParamA, aParamC);
		return paramString;
	}
}
