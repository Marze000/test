#pragma once
//***********ͷ�ļ�***************
#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Msimg32.lib") //tranparent
#define WND_WIDTH 800
#define WND_HEIGHT 600
//ö�ټ���
enum ActionType{
	NORMAL = 0,	//��ͨ����
	CRITICAL = 1,	//����
	MAGIC = 2,	//ħ������
	MISS = 3,	//MISS
	RECOVER = 4		//�ָ�
};

//***********��������***************
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