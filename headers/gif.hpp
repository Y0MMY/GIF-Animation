#ifndef __GIFANIMATION_H__
#define __GIFANIMATION_H__
#include <iostream>
#include <vector>
#include <memory>
#include <Windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
typedef struct
{
	int x, y, width, height;
} RRECT;

class GIF
{
public:
	GIF(Bitmap* bit, HDC, HWND hwnd);
	void SetPosition(int x, int y);
	void Play(HDC hdc);
	void draw(HDC g);
	RECT rect;
	RECT* GetRectPosition();
	RRECT position;
	~GIF();
private:
	void UpdateGif(HWND hWnd);
	UINT CurrentFrame;
	std::shared_ptr<CachedBitmap> CurrentCachedBitmap;
	::std::vector<::std::shared_ptr<CachedBitmap>> CachedBitmaps{};
	UINT frameCount;
	HWND hwnd;
	//void Hello();
};
#endif // __GIFANIMATION_H__