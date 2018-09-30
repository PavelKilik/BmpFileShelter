#pragma once

class CMyLCG
{
private:
	ULONG64 aParamM;
	ULONG64 aParamA;
	ULONG64 aParamC;
	ULONG64 aValueX;

public:
	CMyLCG();
	CMyLCG(ULONG32 initParamA, ULONG32 initParamC);
	~CMyLCG();
	void InitializeParameters(ULONG32 initParamA, ULONG32 initParamC);
	void Start(ULONG32 seed);
	ULONG32 Next();
	CString ToString(bool hexFormat = false);
};


