// RPG.cpp : �������̨Ӧ�ó������ڵ㡣
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

	//// ��ȡĬ�ϱ�׼��ʾ���������
	//HANDLE hOutput;
	//COORD coord = { 0, 0 };
	//hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	////�����µĻ�����
	//HANDLE hOutBuf = CreateConsoleScreenBuffer(
	//	GENERIC_READ | GENERIC_WRITE,
	//	FILE_SHARE_READ | FILE_SHARE_WRITE,
	//	NULL,
	//	CONSOLE_TEXTMODE_BUFFER,
	//	NULL
	//	);
	////�����µĻ�����Ϊ���ʾ����
	//SetConsoleActiveScreenBuffer(hOutBuf);

	////���������������Ĺ��
	//CONSOLE_CURSOR_INFO cci;
	//cci.bVisible = 0;
	//cci.dwSize = 1;
	//SetConsoleCursorInfo(hOutput, &cci);
	//SetConsoleCursorInfo(hOutBuf, &cci);

	////˫���崦����ʾ
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

