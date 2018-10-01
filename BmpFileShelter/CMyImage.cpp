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

	int rgbRotation;
	int bPos = 0;
	for (int i = 0; i < bmpWidth; i++)
	{
		rgbRotation = i % 3;
		for (int j = 0; j < bmpHeight; j++)
		{
			if (bPos == arrSize)
			{
				srand((unsigned)time(NULL));
			}
			byte byteAdd = bPos >= arrSize ? (byte)rand() : pB[bPos];
			byte rOrig;
			byte gOrig;
			byte bOrig;
			byte rNew;
			byte gNew;
			byte bNew;
			this->GetRGB(i, j, rOrig, gOrig, bOrig);
			switch (rgbRotation % 3)
			{
			case 0:
				rNew = (rOrig & 0xF8) | (byteAdd & 0x7);
				gNew = (gOrig & 0xF8) | ((byteAdd >> 3) & 0x7);
				bNew = (bOrig & 0xFC) | ((byteAdd >> 6) & 0x3);
				break;
			case 1:
				rNew = (rOrig & 0xF8) | ((byteAdd >> 3) & 0x7);
				gNew = (gOrig & 0xFC) | ((byteAdd >> 6) & 0x3);
				bNew = (bOrig & 0xF8) | (byteAdd & 0x7);
				break;
			case 2:
				rNew = (rOrig & 0xFC) | ((byteAdd >> 6) & 0x3);
				gNew = (gOrig & 0xF8) | (byteAdd & 0x7);
				bNew = (bOrig & 0xF8) | ((byteAdd >> 3) & 0x7);
				break;
			}
			this->SetRGB(i, j, rNew, gNew, bNew);
			rgbRotation++;
			bPos++;
		}
	}

	return true;
}

byte * CMyImage::ExtractByteArrayFromBitmap(int & arrSize)
{
	int rgbRotation;
	int bPos = 0;
	int bmpHeight = this->GetHeight();
	int bmpWidth = this->GetWidth();
	arrSize = bmpHeight * bmpWidth;
	byte *pB = new byte[arrSize];
	for (int i = 0; i < bmpWidth; i++)
	{
		rgbRotation = i % 3;
		for (int j = 0; j < bmpHeight; j++)
		{
			byte r;
			byte g;
			byte b;
			byte rPart;
			byte gPart;
			byte bPart;
			this->GetRGB(i, j, r, g, b);
			switch (rgbRotation % 3)
			{
			case 0:
				rPart = r & 0x07;
				gPart = g & 0x07;
				bPart = b & 0x03;
				pB[bPos] = (bPart << 6) + (gPart << 3) + rPart;
				break;
			case 1:
				rPart = r & 0x07;
				gPart = g & 0x03;
				bPart = b & 0x07;
				pB[bPos] = (gPart << 6) + (rPart << 3) + bPart;
				break;
			case 2:
				rPart = r & 0x03;
				gPart = g & 0x07;
				bPart = b & 0x07;
				pB[bPos] = (rPart << 6) + (bPart << 3) + gPart;
				break;
			}
			rgbRotation++;
			bPos++;
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
