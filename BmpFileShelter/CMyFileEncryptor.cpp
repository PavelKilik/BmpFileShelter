#include "stdafx.h"
#include "CMyFileEncryptor.h"
#include "Resource.h"
#include "CBmpFileShelterHelper.h"

CMyFileEncryptor::CMyFileEncryptor()
{
}


CMyFileEncryptor::~CMyFileEncryptor()
{
}

bool CMyFileEncryptor::InitializeEncryptor(const CString & key)
{
	bool retValue = false;

	const int hashSize = 2 * sizeof(byte) + 6 * sizeof(ULONG32);
	byte bHash[hashSize];

	int bKeySize;
	byte *pBKey = CBmpFileShelterHelper::CStringToByteArray(key, bKeySize);

	if (pBKey != nullptr)
	{
		if (HashData(pBKey, bKeySize, bHash, hashSize) == S_OK)
		{
			int pos = 0;
			aSeedAdd1 = bHash[pos];
			pos += sizeof(byte);
			aSeedAdd2 = bHash[pos];
			pos += sizeof(byte);
			aSeedLcg1 = CBmpFileShelterHelper::GetULONG32FromByteArray(bHash, pos);
			pos += sizeof(ULONG32);
			aSeedLcg2 = CBmpFileShelterHelper::GetULONG32FromByteArray(bHash, pos);
			pos += sizeof(ULONG32);
			ULONG32 a1 = CBmpFileShelterHelper::GetULONG32FromByteArray(bHash, pos);
			pos += sizeof(ULONG32);
			ULONG32 c1 = CBmpFileShelterHelper::GetULONG32FromByteArray(bHash, pos);
			pos += sizeof(ULONG32);
			ULONG32 a2 = CBmpFileShelterHelper::GetULONG32FromByteArray(bHash, pos);
			pos += sizeof(ULONG32);
			ULONG32 c2 = CBmpFileShelterHelper::GetULONG32FromByteArray(bHash, pos);
			retValue = true;

			aLcg1.InitializeParameters(a1, c1);
			aLcg2.InitializeParameters(a2, c2);
		}
		delete pBKey;
	}

	return retValue;
}

inline byte CMyFileEncryptor::ByteAdd(byte b1, byte b2)
{
	return (byte)((b1 + b2) % 0x100);
}

inline byte CMyFileEncryptor::ByteSub(byte b1, byte b2)
{
	int sub = b1 - b2;
	return (byte)(sub < 0 ? sub + 0x100 : sub);
}

byte * CMyFileEncryptor::Encrypt(LPCTSTR filePath, LPCTSTR key, int maxLength, int & realLength, CString & errorString)
{
	if (!InitializeEncryptor(key))
	{
		errorString.Format(IDS_STRING_ERR_ERROR_INIT_ENCRYPTOR);
		return nullptr;
	}

	CFile fil;
	CFileException ex;
	if (!fil.Open(filePath, CFile::modeRead, &ex))
	{
		TCHAR errorMesage[2048];
		ex.GetErrorMessage(errorMesage, 2048);
		errorString.Format(IDS_STRING_ERR_HIDDEN_FILE_READING, errorMesage);
		return nullptr;
	}

	if (fil.GetLength() > maxLength)
	{
		errorString.Format(IDS_STRING_ERR_HIDDEN_FILE_TOO_LONG, maxLength, fil.GetLength());
		fil.Close();
		return nullptr;
	}

	int fileLength = (int)fil.GetLength();
	DWORD dwRead;
	byte * pbRead = new byte[fileLength];

	dwRead = fil.Read(pbRead, fileLength);
	fil.Close();

	byte * pbEncrypted = Encrypt(pbRead, dwRead, realLength);

	delete pbRead;
	return pbEncrypted;
}

bool CMyFileEncryptor::Decrypt(LPCTSTR filePath, LPCTSTR key, byte * pB, int arrSize, CString & errorString)
{
	if (!InitializeEncryptor(key))
	{
		errorString.Format(IDS_STRING_ERR_ERROR_INIT_ENCRYPTOR);
		return false;
	}

	bool retValue = false;

	int realCount;
	byte * pbDecrypted = Decrypt(pB, arrSize, realCount);
	if (pbDecrypted != nullptr)
	{
		if (realCount > 0)
		{
			CFile fil;
			CFileException ex;
			if (fil.Open(filePath, CFile::modeWrite | CFile::modeCreate, &ex))
			{
				fil.Write(pbDecrypted, realCount);
				fil.Close();
				retValue = true;
			}
			else
			{
				TCHAR errorMesage[2048];
				ex.GetErrorMessage(errorMesage, 2048);
				errorString.Format(IDS_STRING_ERR_CREATE_RESULT_FILE, errorMesage);
			}
		}
		delete pbDecrypted;
	}
	else
	{
		errorString.LoadString(IDS_STRING_ERR_DATA_OR_KEY);
	}

	return retValue;
}

byte * CMyFileEncryptor::Encrypt(byte * pB, int nCount, int & realCount)
{
	int ulSize = sizeof(ULONG32);
	int encryptedCount = nCount + 2 * ulSize;
	
	byte bWithCount[32];
	CBmpFileShelterHelper::ULONG32ToByteArray(bWithCount, 0, nCount);

	byte * pbEncrypted = new byte[encryptedCount];
	aLcg1.Start(aSeedLcg1);
	aLcg2.Start(aSeedLcg2);
	realCount = 0;

	byte bx1 = aSeedAdd1;
	byte bx2 = aSeedAdd2;

	for (int i = 0; i < ulSize; i++)
	{
		pbEncrypted[realCount] = ByteAdd(bWithCount[i], aLcg1.Next());

		pbEncrypted[realCount] = ByteAdd(pbEncrypted[realCount], bx1);
		bx1 = pbEncrypted[realCount];

		pbEncrypted[realCount] ^= aLcg2.Next();

		pbEncrypted[realCount] = ByteAdd(pbEncrypted[realCount], bx2);
		bx2 = pbEncrypted[realCount];

		realCount++;
	}

	for (int i = 0; i < nCount; i++)
	{
		pbEncrypted[realCount] = ByteAdd(pB[i], aLcg1.Next());

		pbEncrypted[realCount] = ByteAdd(pbEncrypted[realCount], bx1);
		bx1 = pbEncrypted[realCount];

		pbEncrypted[realCount] ^= aLcg2.Next();

		pbEncrypted[realCount] = ByteAdd(pbEncrypted[realCount], bx2);
		bx2 = pbEncrypted[realCount];

		realCount++;
	}

	for (int i = 0; i < ulSize; i++)
	{
		pbEncrypted[realCount] = ByteAdd(bWithCount[i], aLcg1.Next());

		pbEncrypted[realCount] = ByteAdd(pbEncrypted[realCount], bx1);
		bx1 = pbEncrypted[realCount];

		pbEncrypted[realCount] ^= aLcg2.Next();

		pbEncrypted[realCount] = ByteAdd(pbEncrypted[realCount], bx2);
		bx2 = pbEncrypted[realCount];

		realCount++;
	}

	return pbEncrypted;
}

byte * CMyFileEncryptor::Decrypt(byte * pB, int nMaxCount, int & realCount)
{
	int ulSize = sizeof(ULONG32);

	aLcg1.Start(aSeedLcg1);
	aLcg2.Start(aSeedLcg2);

	byte bx1 = aSeedAdd1;
	byte by1;
	byte bx2 = aSeedAdd2;
	byte by2;


	byte * pbDecrypted = new byte[nMaxCount];

	for (int i = 0; i < nMaxCount; i++)
	{
		by2 = pB[i];
		pB[i] = ByteSub(pB[i], bx2);
		bx2 = by2;

		pbDecrypted[i] = pB[i] ^ aLcg2.Next();

		by1 = pbDecrypted[i];
		pbDecrypted[i] = ByteSub(pbDecrypted[i], bx1);
		bx1 = by1;

		pbDecrypted[i] = ByteSub(pbDecrypted[i], aLcg1.Next());
	}

	byte * pbDecryptedResult = nullptr;
	realCount = -1;
	int realCount1 = CBmpFileShelterHelper::GetULONG32FromByteArray(pbDecrypted, 0);
	int realCount2 = -1;
	if (realCount1 > 0 && realCount1 + 2 * ulSize <= nMaxCount)
	{
		realCount2 = CBmpFileShelterHelper::GetULONG32FromByteArray(pbDecrypted, realCount1 + ulSize);
	}
	if (realCount1 > 0 && realCount1 == realCount2)
	{
		realCount = realCount1;
		pbDecryptedResult = new byte[realCount];
		memcpy(pbDecryptedResult, pbDecrypted + ulSize, realCount);
	}

	delete pbDecrypted;
	return pbDecryptedResult;
}
