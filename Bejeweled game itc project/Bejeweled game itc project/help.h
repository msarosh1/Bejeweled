#include <windows.h>

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void myLine(int x1, int y1, int x2, int y2, int R, int G, int B) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen =CreatePen(PS_SOLID,2,RGB(R,G,B)); //2 is the width of the pen
    SelectObject(device_context,pen);
	MoveToEx(device_context,x1,y1,NULL);
    LineTo(device_context,x2, y2);
	ReleaseDC(console_handle, device_context);  
	DeleteObject(pen);
	
}

/* This function checks if any of the 4 cursor keys are pressed. 
 If any cursor key is pressed, then the function returns true, and whichKey identifies which of the 4 cursor keys is pressed.
 whichkey is assigned following values if any cursor key is pressed. 1 for left, 2 for up, 3 for right and 4 for left.*/
bool isCursorKeyPressed(int& whickKey)   //whichKey passed as reference.... 
{
	char key;
	key = GetAsyncKeyState(37);
	if (key == 1)
	{
		whickKey = 1;		// 1 if left key is pressed 
		return true;
	}
	key = GetAsyncKeyState(38);
	if (key == 1)
	{

		whickKey = 2;		// 2 if up key is pressed
		return true;
	}
	
	key = GetAsyncKeyState(39);
	if (key == 1)
	{
		whickKey = 3;	// 3 if right key is pressed
		return true;
	}
	key = GetAsyncKeyState(40);
	if (key == 1)
	{

		whickKey = 4;   // 4 if down key is pressed
		return true;
	}
	key = GetAsyncKeyState(13);
	if (key == 1)
	{
		whickKey = 5;   // 5 if enter key is pressed
		return true;
	}
	key = GetAsyncKeyState(83);
	if (key == 1)
	{
		whickKey = 6;   // 6 if S key is pressed
		return true;
	}
	key = GetAsyncKeyState(76);
	if (key == 1)
	{
		whickKey = 7;   // 7 if L key is pressed
		return true;
	}
	return false;
}
void myRect(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB )
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
    HPEN pen =CreatePen(PS_SOLID,2,RGB(R,G,B)); 
    SelectObject(device_context,pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR,FG,FB)); //Fill color is passed as parameter to the function!!!
	
	SelectObject(device_context,brush);
	
	Rectangle(device_context,x1,y1,x2,y2);
	ReleaseDC(console_handle, device_context); 
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
    HPEN pen =CreatePen(PS_SOLID,2,RGB(R,G,B)); 
    SelectObject(device_context,pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB));  //Fill color is black
	SelectObject(device_context,brush);
	Ellipse(device_context,x1,y1,x2,y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myDiamond(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB)); //Fill color is passed as parameter to the function!!
	SelectObject(device_context, brush);
	MoveToEx(device_context, x1 + ((x2 - x1) / 4), y1, NULL);
	LineTo(device_context, x1 + (((x2 - x1) / 4) * 3), y1);
	LineTo(device_context, x2, (y1 + (y2 - y1) / 4));
	LineTo(device_context, (x1 + (x2 - x1) / 2), y2);
	LineTo(device_context, x1, y1 + (y2 - y1) / 4);
	LineTo(device_context, x1 + ((x2 - x1) / 4), y1);
	MoveToEx(device_context, (x1 + x2) / 2, (y1 + y2) / 2, NULL);
	FloodFill(device_context, (x1 + x2) / 2, (y1 + y2) / 2, RGB(R, G, B));
	ReleaseDC(console_handle, device_context);

	DeleteObject(pen);
	DeleteObject(brush);
}
void myRhombus(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB)); //Fill color is passed as parameter to the function!!
	SelectObject(device_context, brush);
	MoveToEx(device_context, (x1 + x2) / 2, y1, NULL);
	LineTo(device_context, x1, (y1 + y2) / 2);
	LineTo(device_context, (x1 + x2) / 2, y2);
	LineTo(device_context, x2, (y1 + y2) / 2);
	LineTo(device_context, (x1 + x2) / 2, y1);
	MoveToEx(device_context, (x1 + x2) / 2, (y1 + y2) / 2, NULL);
	FloodFill(device_context, (x1 + x2) / 2, (y1 + y2) / 2, RGB(R, G, B));
	ReleaseDC(console_handle, device_context);

	DeleteObject(pen);
	DeleteObject(brush);
}
void myTriangle(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB)); //Fill color is passed as parameter to the function!!
	SelectObject(device_context, brush);
	MoveToEx(device_context, (x1 + x2) / 2, y1, NULL);
	LineTo(device_context, x1, y2);
	LineTo(device_context, x2, y2);
	LineTo(device_context, (x1 + x2) / 2, y1);

	MoveToEx(device_context, (x1 + x2) / 2, (y1 + y2) / 2, NULL);
	FloodFill(device_context, (x1 + x2) / 2, (y1 + y2) / 2, RGB(R, G, B));
	ReleaseDC(console_handle, device_context);

	DeleteObject(pen);
	DeleteObject(brush);
}
void myCube(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(255, 105, 180)); //Fill color is passed as parameter to the function!!
	SelectObject(device_context, brush);
	MoveToEx(device_context, x1 + ((x2 - x1) / 4), y1, NULL);
	LineTo(device_context, x1, (y1 + (y2 - y1) / 4));
	LineTo(device_context, (x2 - ((x2 - x1) / 4)), (y1 + (y2 - y1) / 4));
	LineTo(device_context, (x2 - ((x2 - x1) / 4)), y2);
	LineTo(device_context, x2, y2 - ((y2 - y1) / 4));
	LineTo(device_context, x2, y1);
	LineTo(device_context, (x2 - ((x2 - x1) / 4)), (y1 + (y2 - y1) / 4));
	LineTo(device_context, x1, (y1 + (y2 - y1) / 4));
	LineTo(device_context, x1, y2);
	LineTo(device_context, (x2 - ((x2 - x1) / 4)), y2);
	LineTo(device_context, (x2 - ((x2 - x1) / 4)), (y1 + (y2 - y1) / 4));
	LineTo(device_context, x2, y1);
	LineTo(device_context, x1 + ((x2 - x1) / 4), y1);
	MoveToEx(device_context, x1 + ((x2 - x1) / 4), y1, NULL);
	FloodFill(device_context, (x1 + x2) / 2, (y1 + y2) / 2, RGB(R, G, B));
	ReleaseDC(console_handle, device_context);

	DeleteObject(pen);
	//DeleteObject(brush);
}
