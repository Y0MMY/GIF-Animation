#include <iostream>
#include <windows.h>
using namespace std;
ULONG_PTR gdiplusToken; // for shutting down gdi+
#include <gdiplus.h>
#include "headers/gif.hpp"
using namespace Gdiplus;
#define TIMER1 1001


void shutdown()
{
    // Exit
    GdiplusShutdown(gdiplusToken);
}
//===========================================================================

//===========================================================================
BOOL play;
HWND hWnd;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
GIF* gif;
void LoadRes(HWND hWnd) {
    Bitmap* bitmap = new Bitmap(L"..\\resoureses\\Sample.gif");
    gif = new GIF(bitmap, (HDC)GetDC(hWnd), hWnd);
    gif->position.x = 150;
    gif->position.y = 150;
    gif->position.width = bitmap->GetWidth();
    gif->position.height = bitmap->GetHeight();
    delete bitmap;
}
int WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR    lpCmdLine,
    int       nCmdShow)
{
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    const auto pClassName = "WinMainClass";
    WNDCLASSEX wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 3;
    wc.hInstance = hInstance;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpfnWndProc = WndProc;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "WinMainClass";
    if (!RegisterClassEx(&wc))
    {
        std::cout << "Error create window\n";
        cout << "Error: " << GetLastError() << endl;
        exit(1);
    }
    hWnd = CreateWindowEx(0, pClassName, "Window!", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 200, 200, 640, 480, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hWnd, SW_SHOW);
    LoadRes(hWnd);
    MSG msg;
    SetTimer(hWnd,             // handle to main window 
    	TIMER1,            // timer identifier 
    	40,
    	NULL);     // no timer callback 
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    shutdown();
    return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    PAINTSTRUCT ps;
    HDC hdc, mem_dc;
    HBRUSH color;
    RECT r;
    HBITMAP mem_bitmap;
    r.left = 0;
    r.top = 0;
    r.right = 640;
    r.bottom = 480;
    switch (msg)
    {
    case WM_CREATE:
    {

        break;
    }
    case WM_KEYDOWN: {
        switch (wparam) {
        case VK_F1: {

            play = !play;
            break;
        }
        
        }
        break;
    }
    case WM_DESTROY:
    {
        std::cout << "Closing app...";
        PostQuitMessage(0);

        break;
    }
    case WM_TIMER:
    {
        if (wparam == TIMER1)
        {
           if(play) gif->Play(reinterpret_cast<HDC>(wparam));
        }
        break;
    }
    case WM_ERASEBKGND:
    {
       
        return 1;
        //DefWindowProc(hwnd, Message, wParam, lParam);
    }
    case WM_PAINT:
    {
  

        hdc = BeginPaint(hwnd, &ps);
        mem_dc = CreateCompatibleDC(hdc);
        mem_bitmap = CreateCompatibleBitmap(hdc, 640, 480);
        SelectObject(mem_dc, mem_bitmap);


        color = CreateSolidBrush(RGB(255, 0, 0));
        FillRect(mem_dc, &r, (HBRUSH)color);
        gif->draw(mem_dc);
        BitBlt(hdc, 0, 0, 640, 480, mem_dc, 0, 0, SRCCOPY);
        DeleteObject(color);
        DeleteDC(mem_dc);
        DeleteObject(mem_bitmap);
        EndPaint(hwnd, &ps);



        break;

    }
    break;

    default: return DefWindowProc(hwnd, msg, wparam, lparam);

    }
    return 0;
}