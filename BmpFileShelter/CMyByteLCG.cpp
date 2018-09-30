#include "stdafx.h"
#include "CMyByteLCG.h"


CMyByteLCG::CMyByteLCG()
{
}


CMyByteLCG::~CMyByteLCG()
{
}

void CMyByteLCG::InitializeParameters(ULONG32 initParamA, ULONG32 initParamC)
{
	aLcg.InitializeParameters(initParamA, initParamC);
}

void CMyByteLCG::Start(ULONG32 seed)
{
	aLcg.Start(seed);
	aBytePos = 4;
}

byte CMyByteLCG::Next()
{
	if (aBytePos == 4)
	{
		aLcg32Value = aLcg.Next();
		aBytePos = 0;
	}

	byte retValue = aLcg32Value % 0x100;
	aLcg32Value /= 0x100;
	aBytePos++;

	return retValue;
}

CString CMyByteLCG::ToString(bool hexFormat)
{
	return aLcg.ToString(hexFormat);
}
