#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\BmpFileShelter\CMyImage.h"
#include "..\BmpFileShelter\CMyFileEncryptor.h"
#include "..\BmpFileShelter\resource.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BmpFileShelterUnitTest
{		
constexpr auto SourceImageName = L"SourceImage.JPG";
constexpr auto TargetImageName = L"TargetImage.BMP";
constexpr auto SourceSecretFileName = L"SourceSecretFile.zip";
constexpr auto ResultSecretFileName = L"ResultSecretFile.zip";

constexpr auto TraceCodeStart = -1;
constexpr auto TraceCodeOK = 0;
constexpr auto TraceCodeLoadImage = 1;
constexpr auto TraceCodeEncryptData = 2;
constexpr auto TraceCodeHideData = 3;
constexpr auto TraceCodeSaveImage = 4;
constexpr auto TraceCodeExtractData = 5;
constexpr auto TraceCodeEncryptAndSaveData = 6;

CString key;
CString sourceImagePath;
CString targetImagePath;
CString sourceSecretFilePath;
CString resultSecretFilePath;

	TEST_CLASS(UnitTest1)
	{
	private:
		
		static void GetTestFileFullPath(CString &testFileFullPath, LPCTSTR testFileName)
		{
			CString tempStr;
			tempStr.Format(L"..\\..\\Test\\%s", testFileName);
			TCHAR fullPath[MAX_PATH];
			TCHAR** lppPart = { NULL };
			GetFullPathName(tempStr, MAX_PATH, fullPath, lppPart);
			testFileFullPath = fullPath;
		}

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			key = "hhf&Gr86>>oprtHT#6";
			GetTestFileFullPath(sourceImagePath, SourceImageName);
			GetTestFileFullPath(targetImagePath, TargetImageName);
			GetTestFileFullPath(sourceSecretFilePath, SourceSecretFileName);
			GetTestFileFullPath(resultSecretFilePath, ResultSecretFileName);

			if (PathFileExists(targetImagePath))
			{
				DeleteFile(targetImagePath);
			}

			if (PathFileExists(resultSecretFilePath))
			{
				DeleteFile(resultSecretFilePath);
			}
		}

		TEST_METHOD(EncryptAndHideFile)
		{
			int tc = TraceCodeStart;
			try
			{
				tc = TraceCodeLoadImage;
				CMyImage sourceImage;
				HRESULT hr = sourceImage.Load(sourceImagePath);
				if (hr == S_OK)
				{
					int bmpCapacity = sourceImage.GetCapacity();
					CString errorString;
					CMyFileEncryptor mfe;
					int encryptedSize;
					tc = TraceCodeEncryptData;
					byte * pB = mfe.Encrypt(sourceSecretFilePath, key, bmpCapacity, encryptedSize, errorString);
					if (pB != nullptr)
					{
						tc = TraceCodeHideData;
						sourceImage.HideByteArrayIntoBitmap(pB, encryptedSize);
						tc = TraceCodeSaveImage;
						hr = sourceImage.Save(targetImagePath);
						if (hr == S_OK)
						{
							tc = TraceCodeOK;
							Logger::WriteMessage(L"File encrypted a hiden with result OK");
						}
						delete pB;
					}
				}
			}
			catch (...)
			{
			}

			CString strMsg;
			strMsg.Format(L"Encrypt and hide data result: %i",  tc);
			Logger::WriteMessage(strMsg);
			Assert::AreEqual(tc, TraceCodeOK, strMsg);
		}

		TEST_METHOD(ExtractAndDecryptSecretFile)
		{
			int tc = TraceCodeStart;
			try
			{
				tc = TraceCodeLoadImage;
				CMyImage sourceImage;
				HRESULT hr = sourceImage.Load(targetImagePath);
				if (hr == S_OK)
				{
					tc = TraceCodeExtractData;
					int arrSize;
					byte *pB = sourceImage.ExtractByteArrayFromBitmap(arrSize);
					if (pB != nullptr)
					{
						tc = TraceCodeEncryptAndSaveData;
						CString errString;
						CMyFileEncryptor mfe;
						if (mfe.Decrypt(resultSecretFilePath, key, pB, arrSize, errString))
						{
							tc = TraceCodeOK;
						}
						delete pB;
					}
				}
			}
			catch (...)
			{
			}

			CString strMsg;
			strMsg.Format(L"Extract and decrypt data result: %i", tc);
			Logger::WriteMessage(strMsg);
			Assert::AreEqual(tc, TraceCodeOK, strMsg);
		}
	};
}