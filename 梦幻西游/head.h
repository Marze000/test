#pragma once
//***********头文件***************
#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Msimg32.lib") //tranparent
#define WND_WIDTH 800
#define WND_HEIGHT 600
//枚举技能
enum ActionType{
	NORMAL = 0,	//普通攻击
	CRITICAL = 1,	//暴击
	MAGIC = 2,	//魔法攻击
	MISS = 3,	//MISS
	RECOVER = 4		//恢复
};

//***********函数声明***************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
VOID GamePaint(HWND hwnd);
BOOL GameInit(HWND hwnd);
VOID HeroActionPaint();
VOID HeroAction_Logic();
VOID BossActionPaint();
VOID BossAction_Logic();
VOID DieCheck(int nowhp, bool ishero);
VOID Message_Insert(wchar_t* str);
BOOL Timer();