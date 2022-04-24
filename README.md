<h1 align="center">Custom GIF Animation Player
  </h1>

**Stack:**
- C++
- GDI+
- CMake

<h2 align="center">Build</h2>

**Windows:**
- cd .\build\
- cmake --build .
- .\main.exe

**Linux:**
- cd build/
- make .
- .\main.exe

<h2 align="center">Using</h2>

<div align ="center"><img align="center" src="https://s7.gifyu.com/images/Sample.gif" alt="gif"></div>

Использование: 
- F1 - Начать и поставить на паузу воспроиведение 

```
void LoadRes(HWND hWnd) {
    Bitmap* bitmap = new Bitmap(L"..\\resoureses\\Sample.gif"); // Путь к вашему gif файлу
    gif = new GIF(bitmap, (HDC)GetDC(hWnd), hWnd);
    gif->position.x = 150;
    gif->position.y = 150;
    gif->position.width = bitmap->GetWidth();
    gif->position.height = bitmap->GetHeight();
    delete bitmap;
}
```

```
SetTimer(hWnd,            
    	TIMER1,            
    	40, // FPS
    	NULL);     
```
