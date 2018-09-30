#pragma once
class CBmpFileShelterHelper
{
public:
	CBmpFileShelterHelper();
	~CBmpFileShelterHelper();

	void ErrorMessage(int strMessageID);

	static byte * CStringToByteArray(const CString & str, int & arrSize);
	static void ByteArrayToCString(const byte * pB, int arrSize, CString & str);
	static ULONG32 GetULONG32FromByteArray(byte * pB, int startPos);
	static void ULONG32ToByteArray(byte * pB, int startPos, ULONG32 ul);
};

