#include "MSS.h"
#include <cstdio>

MSS::MSS(const MSS::Rect& rect)
	: mRect(rect)
{
	mSrcDC = get_srcdc();
	mMemDC = CreateCompatibleDC(mSrcDC);

	mBMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mBMI.bmiHeader.biPlanes = 1; // always 1
	mBMI.bmiHeader.biBitCount = 32;
	mBMI.bmiHeader.biCompression = 0; // no compression
	mBMI.bmiHeader.biClrUsed = 0;
	mBMI.bmiHeader.biClrImportant = 0;

	mBMI.bmiHeader.biWidth = mRect.width;
	mBMI.bmiHeader.biHeight = -mRect.height;

	// 32bit padding
	mRGBX = std::vector<MSS::RGBX>(mRect.width * mRect.height);

	mBMP = CreateCompatibleBitmap(mSrcDC, mRect.width, mRect.height);
	SelectObject(mMemDC, mBMP);
}

void MSS::grab()
{
	BitBlt(
		mMemDC, 0, 0,
		mRect.width, mRect.height, mSrcDC,
		mRect.left, mRect.top,
		SRCCOPY | CAPTUREBLT);
	
	int bits = GetDIBits(
		mMemDC, mBMP,
		0, mRect.height, reinterpret_cast<uint8_t*>(mRGBX.data()),
		&mBMI, DIB_RGB_COLORS);

	if (bits != mRect.height) {
		fprintf(stderr, "Mismatch in calculated heights got %d expected %d\n", bits, mRect.height);
		exit(1);
	}

}

HDC MSS::get_srcdc()
{
	return GetWindowDC(0);
}