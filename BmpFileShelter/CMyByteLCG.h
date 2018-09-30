#pragma once

#include "CMyLCG.h"

class CMyByteLCG
{
private:
	CMyLCG aLcg;
	int aBytePos;
	ULONG32 aLcg32Value;

public:
	CMyByteLCG();
	~CMyByteLCG();
	void InitializeParameters(ULONG32 initParamA, ULONG32 initParamC);
	void Start(ULONG32 seed);
	byte Next();
	CString ToString(bool hexFormat = false);
};




