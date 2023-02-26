// RPG.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "GameMgr.h"
void gotoxy(int x, int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}


int _tmain(int argc, _TCHAR* argv[])
{

	//// 获取默认标准显示缓冲区句柄
	//HANDLE hOutput;
	//COORD coord = { 0, 0 };
	//hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	////创建新的缓冲区
	//HANDLE hOutBuf = CreateConsoleScreenBuffer(
	//	GENERIC_READ | GENERIC_WRITE,
	//	FILE_SHARE_READ | FILE_SHARE_WRITE,
	//	NULL,
	//	CONSOLE_TEXTMODE_BUFFER,
	//	NULL
	//	);
	////设置新的缓冲区为活动显示缓冲
	//SetConsoleActiveScreenBuffer(hOutBuf);

	////隐藏两个缓冲区的光标
	//CONSOLE_CURSOR_INFO cci;
	//cci.bVisible = 0;
	//cci.dwSize = 1;
	//SetConsoleCursorInfo(hOutput, &cci);
	//SetConsoleCursorInfo(hOutBuf, &cci);

	////双缓冲处理显示
	//DWORD bytes = 0;
	//char data[3200];
	CLoad::load();
	while (true)
	{
		system("cls");
		CGameMgr::getInstance()->update();
		CGameMgr::getInstance()->render();
		/*ReadConsoleOutputCharacterA(hOutput, data, 3200, coord, &bytes);
		WriteConsoleOutputCharacterA(hOutBuf, data, 3200, coord, &bytes);*/
		gotoxy(0, 0);
	}
	return 0;
}

