#pragma once

#include "CMyByteLCG.h"

class CMyFileEncryptor
{
private:
	ULONG32 aSeedLcg1;
	ULONG32 aSeedLcg2;
	byte aSeedAdd1;
	byte aSeedAdd2;

	CMyByteLCG aLcg1;
	CMyByteLCG aLcg2;

	bool InitializeEncryptor(const CString &key);
	inline byte ByteAdd(byte b1, byte b2);
	inline byte ByteSub(byte b1, byte b2);

public:
	CMyFileEncryptor();
	~CMyFileEncryptor();

	static const int MinKeySize = 7;

	byte * Encrypt(LPCTSTR filePath, LPCTSTR key, int maxLength, int & realLength, CString & errorString);
	bool Decrypt(LPCTSTR filePath, LPCTSTR key, byte * pB, int arrSize, CString & errorString);
	byte * Encrypt(byte * pB, int nCount, int & realCount);
	byte * Decrypt(byte * pB, int nMaxCount, int & realCount);
};

