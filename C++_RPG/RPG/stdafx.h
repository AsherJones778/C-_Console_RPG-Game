// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<windows.h>
#include<iostream>
using namespace std;

enum 
{
	E_GAME_MENU,
	E_GAME_MAP,
	E_GAME_SELECT,
	E_GAME_STORE,
	E_GAME_BAG,
	E_GAME_PLAYERSTATE,
	E_GAME_BATTLE,
	E_GAME_DEAD,
	E_GAME_END,
	E_GAME_MISSIONSCENE,
	E_GAME_HANDINMISSION,
	E_GAME_WIN,
};
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define CC_SYNTHESIZE(typeName,valueName,funcName) \
public:\
	void set##funcName(typeName value)\
{\
	valueName = value; \
	}\
	typeName get##funcName()\
{\
	return valueName; \
	}\
protected:\
	typeName valueName; \

#define CC_SYNTHESIZE_READONLY(typeName,valueName,funcName)\
public:\
	typeName get##funcName()\
{\
	return valueName; \
	}\
protected:\
	typeName valueName; \

#define CC_SAFE_DELETE(p) if (p){delete p;p = nullptr;}

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
