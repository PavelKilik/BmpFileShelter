#pragma once
#include <atlimage.h>
class CMyImage : public CImage
{

public:
	CMyImage();
	~CMyImage();

	int GetCapacity();
	bool HideByteArrayIntoBitmap(const byte * pB, int arrSize);
	byte * ExtractByteArrayFromBitmap(int & arrSize);

	void GetRGB(int x, int y, byte & R, byte & G, byte & B);
	void SetRGB(int x, int y, byte R, byte G, byte B);
};

