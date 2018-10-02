#include "stdafx.h"
#include "afxdialogex.h"
#include "CBmpFileShelterHelper.h"


CBmpFileShelterHelper::CBmpFileShelterHelper()
{
}


CBmpFileShelterHelper::~CBmpFileShelterHelper()
{
}

void CBmpFileShelterHelper::ErrorMessage(int strMessageID)
{
	CString errMsg;
	errMsg.LoadString(strMessageID);

	MessageBox(nullptr, errMsg, L"Error", MB_OK | MB_ICONERROR);
}

byte * CBmpFileShelterHelper::CStringToByteArray(const CString & str, int & arrSize)
{
	int strLength = str.GetLength();
	arrSize = strLength * 2;

	if (strLength < 1)
	{
		arrSize = 0;
		return nullptr;
	}

	byte * pResultByteArr = new byte[arrSize];
	for (int i = 0; i < strLength; i++)
	{
		wchar_t ch = str.GetAt(i);
		pResultByteArr[2 * i] = ch & 0xFF;
		pResultByteArr[2 * i + 1] = (ch & 0xFF00) >> 8;
	}

	return pResultByteArr;
}

void CBmpFileShelterHelper::ByteArrayToCString(const byte * pB, int arrSize, CString & str)
{
	str = "";
	for (int i = 0; i < arrSize / 2; i++)
	{
		str.AppendChar(pB[2 * i] + (pB[2 * i + 1] << 8));
	}
}

ULONG32 CBmpFileShelterHelper::GetULONG32FromByteArray(byte * pB, int startPos)
{
	return pB[startPos] + (pB[startPos + 1] << 8) + (pB[startPos + 2] << 16) + (pB[startPos + 3] << 24);
}

void CBmpFileShelterHelper::ULONG32ToByteArray(byte * pB, int startPos, ULONG32 ul)
{
	pB[startPos] = ul;
	pB[startPos + 1] = ul >> 8;
	pB[startPos + 2] = ul >> 16;
	pB[startPos + 3] = ul >> 24;
}

bool CBmpFileShelterHelper::CheckImageExtension(LPCTSTR filePath, bool onlyBmp)
{
	TCHAR ext[MAX_PATH];
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[MAX_PATH];
	TCHAR filename[MAX_PATH];

	_tsplitpath_s(filePath, drive, dir, filename, ext);

	CString strExt(ext);
	if (onlyBmp)
	{
		return strExt.CompareNoCase(L".BMP") == 0;
	}
	else
	{
		return strExt.CompareNoCase(L".JPG") == 0 ||
			strExt.CompareNoCase(L".JPEG") == 0 ||
			strExt.CompareNoCase(L".PNG") == 0 ||
			strExt.CompareNoCase(L".BMP") == 0;
	}
}
