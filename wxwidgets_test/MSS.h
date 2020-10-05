#pragma once

#include <windows.h>
#include <wingdi.h>

#include <vector>

class MSS 
{
public:
	typedef struct {
		int left, top, width, height;
	} Rect;

	typedef struct {
		uint8_t R, G, B, X;
	} RGBX;
public:
	MSS(const Rect& rect);
	void grab();
	std::vector<RGBX>& get_data() {
		return mRGBX;
	};
	const Rect& get_rect() { return mRect; };
private:
	const Rect mRect;
	HBITMAP mBMP;
	HDC mSrcDC;
	HDC mMemDC;
	std::vector<RGBX> mRGBX;
	BITMAPINFO mBMI;
private:
	HDC get_srcdc();
};