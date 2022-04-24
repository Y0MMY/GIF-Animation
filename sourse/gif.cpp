#include "../headers/gif.hpp"

RECT getAbsoluteRect(const RRECT relativeRect)
{
	RECT r;
	r.left = relativeRect.x;
	r.top = relativeRect.y;
	r.right = relativeRect.x + relativeRect.width;
	r.bottom = relativeRect.y + relativeRect.height;
	return r;
}
std::shared_ptr<CachedBitmap> createCachedBitmap(Bitmap* originalBitmap, HDC hdc)
{
	Graphics gt(hdc);
	return std::make_shared<CachedBitmap>(originalBitmap, &gt);

}
GIF::GIF(Bitmap* bit, HDC hdc, HWND hwnd)
{
	this->hwnd = hwnd;
	Graphics graphics(hdc);
	CurrentFrame = 0;
	this->position.width = bit->GetWidth();
	this->position.height = bit->GetHeight();
	GUID guid = FrameDimensionTime;
	UINT count = bit->GetFrameDimensionsCount();
	GUID* pDimensionIDs = new GUID[(sizeof(GUID) * count)];
	bit->GetFrameDimensionsList(pDimensionIDs, count);
	frameCount = bit->GetFrameCount(&pDimensionIDs[0]);
	for (int i = 0; i < frameCount; i++)
	{
		bit->SelectActiveFrame(&guid, i);
		CachedBitmaps.emplace_back(createCachedBitmap(bit, hdc));
	}
	// delete bit;
	delete[] pDimensionIDs;
}

void GIF::UpdateGif(HWND hWnd)
{
	RECT rect;
	GetClientRect(hwnd, &rect);
	InvalidateRect(hWnd, &rect, true);
}
void GIF::draw(HDC g)
{

	Graphics* graphics = new Graphics(g);
	CurrentCachedBitmap = CachedBitmaps[CurrentFrame];
	graphics->DrawCachedBitmap(CurrentCachedBitmap.get(), position.x, position.y);

	delete graphics;

}
RECT* GIF::GetRectPosition() {
	// rect = getAbsoluteRect(position);
	return &rect;
}
void GIF::SetPosition(int x, int y)
{
	this->position.x = x;
	this->position.x = y;
}

void GIF::Play(HDC hdc)
{

	++CurrentFrame;
	if (CurrentFrame > frameCount - 1) {
		CurrentFrame = 0;
	}
	UpdateGif(hwnd);
	draw(hdc);
}
