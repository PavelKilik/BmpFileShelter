#include "stdafx.h"
#include "CMyImage.h"


CMyImage::CMyImage()
{
}

CMyImage::~CMyImage()
{
}

int CMyImage::GetCapacity()
{
	return this->GetHeight() * this->GetWidth() - 2 * sizeof(ULONG32);
}

bool CMyImage::HideByteArrayIntoBitmap(const byte * pB, int arrSize)
{
	int bmpHeight = this->GetHeight();
	int bmpWidth = this->GetWidth();

	if (arrSize > bmpHeight * bmpWidth)
	{
		return false;
	}

	int bPos = 0;
	for (int i = 0; i < bmpWidth; i++)
	{
		for (int j = 0; j < bmpHeight; j++)
		{
			if (bPos == arrSize)
			{
				srand((unsigned)time(NULL));
			}
			byte byteAdd = bPos >= arrSize ? (byte)rand() : pB[bPos];
			byte rCorrection = byteAdd & 0x7;
			byte gCorrection = (byteAdd >> 3) & 0x7;
			byte bCorrection = (byteAdd >> 6) & 0x3;
			byte rOrig;
			byte gOrig;
			byte bOrig;
			this->GetRGB(i, j, rOrig, gOrig, bOrig);
			byte rNew = (rOrig & 0xF8) | rCorrection;
			byte gNew = (gOrig & 0xF8) | gCorrection;
			byte bNew = (bOrig & 0xFC) | bCorrection;
			this->SetRGB(i, j, rNew, gNew, bNew);
			bPos++;
		}
	}

	return true;
}

byte * CMyImage::ExtractByteArrayFromBitmap(int & arrSize)
{
	int bPos = 0;
	int bmpHeight = this->GetHeight();
	int bmpWidth = this->GetWidth();
	arrSize = bmpHeight * bmpWidth;
	byte *pB = new byte[arrSize];
	for (int i = 0; i < bmpWidth; i++)
	{
		for (int j = 0; j < bmpHeight; j++)
		{
			byte r;
			byte g;
			byte b;
			this->GetRGB(i, j, r, g, b);
			byte rPart = r & 0x07;
			byte gPart = g & 0x07;
			byte bPart = b & 0x03;
			pB[bPos++] = (bPart << 6) + (gPart << 3) + rPart;
		}
	}

	return pB;
}

void CMyImage::GetRGB(int x, int y, byte & R, byte & G, byte & B)
{
	COLORREF clr = this->GetPixel(x, y);
	B = (clr >> 16) & 0xFF;
	G = (clr >> 8) & 0xFF;
	R = clr & 0xFF;
}

void CMyImage::SetRGB(int x, int y, byte R, byte G, byte B)
{
	COLORREF clr = (B << 16) + (G << 8) + R;
	this->SetPixel(x, y, clr);
}
