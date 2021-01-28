#include "head.h"


struct {
	int		NowMp;		//当前的蓝
	int		NowHp;		//当前气血
	int		MaxMp;		//最大的蓝
	int		MaxHp;		//最大气血
	int		level;		//等级
	int		strength;	//力量
	int		Intell;		//智力
	int		Agility;	//敏捷
}Boss, Hero;

//***********全局变量定义***********
HDC			g_hdc, g_memdc, g_bufdc;		//窗口设备局部，内存设备句柄,内存设备句柄
DWORD g_tPre, g_tNow;						//计时器用于计时
ActionType	HeroAction, BossAction;			//枚举类型的 hero和boss技能
wchar_t		text[8][100];					//定义存储文字的字符串数组
int			g_bossnum = 0;					//计算boss图片数量
int			g_heronum = 0;					//计算英雄图片数量
int			g_iTextNum = 0;					//文字个数
int			g_frame;						//帧数

RECT		g_rect;							//做一个矩形区域显示文字
BOOL		g_bCanAttack;					//英雄是否可以攻击
BOOL		g_bGameOver;					//游戏是否结束


HBITMAP		g_heroskill1, g_heroskill2, g_heroskill3;	//英雄技能
HBITMAP		g_bossskill1, g_bossskill2, g_bossskill3;	// boss 技能
HBITMAP		g_recover;									//恢复
HBITMAP		g_bmp;										//空位图
HBITMAP		g_backbmp, g_skillbutton1, g_skillbutton2, g_skillbutton3, g_skillbutton4;		//背景图片
HBITMAP		g_hero, g_boss;								//英雄，怪物
HBITMAP		g_hGameOver, g_hVictor;						//游戏胜利和游戏结束

//窗口过程函数:主要针对用户的不同指令给出不同的响应
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
	switch (message)
	{
	case WM_LBUTTONDOWN://鼠标左键按下
		if (!g_bCanAttack){
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);

			if (x >= 600 && x <= 640 && y >= 200 && y <= 240){
				g_bCanAttack = true;
				HeroAction = NORMAL;
			}
			else if (x >= 600 && x <= 640 && y >= 250 && y <= 290){
				g_bCanAttack = true;
				HeroAction = MAGIC;
			}
			else if (x >= 600 && x <= 640 && y >= 300 && y <= 340){
				g_bCanAttack = true;
				HeroAction = RECOVER;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}


//游戏初始化
BOOL GameInit(HWND hwnd){
	srand((unsigned int)time(NULL));
	//工具
	g_hdc = GetDC(hwnd);
	g_memdc = CreateCompatibleDC(g_hdc); //创建对窗口兼容的设备
	g_bufdc = CreateCompatibleDC(g_hdc);
	g_bmp = CreateCompatibleBitmap(g_hdc, WND_WIDTH, WND_HEIGHT);//创建兼容空位图
	SelectObject(g_memdc, g_bmp);//空位图选入memdc

	// 素材
	g_backbmp = (HBITMAP)LoadImage(NULL, L"./res/bg.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
	g_skillbutton1 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton1.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_skillbutton2 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton2.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_skillbutton3 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton3.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_skillbutton4 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton4.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);

	g_hero = (HBITMAP)LoadImage(NULL, L"./res/1001.bmp", IMAGE_BITMAP, 3500, 250, LR_LOADFROMFILE);
	g_boss = (HBITMAP)LoadImage(NULL, L"./res/BOSS.bmp", IMAGE_BITMAP, 4000, 250, LR_LOADFROMFILE);

	g_heroskill1 = (HBITMAP)LoadImage(NULL, L"./res/heroslash.bmp", IMAGE_BITMAP, 364, 140, LR_LOADFROMFILE);	//普通攻击
	g_heroskill2 = (HBITMAP)LoadImage(NULL, L"./res/herocritical.bmp", IMAGE_BITMAP, 574, 306, LR_LOADFROMFILE);//暴击
	g_heroskill3 = (HBITMAP)LoadImage(NULL, L"./res/heromagic.bmp", IMAGE_BITMAP, 100, 77, LR_LOADFROMFILE);	//魔法攻击

	g_bossskill1 = (HBITMAP)LoadImage(NULL, L"./res/monsterslash.bmp", IMAGE_BITMAP, 150, 120, LR_LOADFROMFILE);
	g_bossskill2 = (HBITMAP)LoadImage(NULL, L"./res/monstercritical.bmp", IMAGE_BITMAP, 249, 231, LR_LOADFROMFILE);
	g_bossskill3 = (HBITMAP)LoadImage(NULL, L"./res/monstermagic.bmp", IMAGE_BITMAP, 200, 131, LR_LOADFROMFILE);

	g_recover = (HBITMAP)LoadImage(NULL, L"./res/recover.bmp", IMAGE_BITMAP, 150, 150, LR_LOADFROMFILE);

	g_hGameOver = (HBITMAP)LoadImage(NULL, L"./res/gameover.bmp", IMAGE_BITMAP, 1086, 396, LR_LOADFROMFILE);
	g_hVictor = (HBITMAP)LoadImage(NULL, L"./res/victory.bmp", IMAGE_BITMAP, 294, 147, LR_LOADFROMFILE);


	//播放添加到资源的.wav文件，IDR_DENG代表音频资源res/wav/1.wav的编号，SND_RESOURCE代表使用资源，SND_ASYNC代表异步播放，SND_LOOP代表循环播放
	PlaySound(_T("./res/梦幻西游原声-战斗1-森林.wav"), NULL, SND_ASYNC | SND_LOOP);


	//初始英雄化数据
	Hero.Agility = 20;
	Hero.Intell = 10;
	Hero.level = 6;
	Hero.strength = 10;
	Hero.MaxHp = 1000;
	Hero.NowHp = 1000;
	Hero.MaxMp = 60;
	Hero.NowMp = 60;
	//初始化Boss数据
	Boss.Agility = 10;
	Boss.Intell = 10;
	Boss.level = 10;
	Boss.strength = 10;
	Boss.MaxHp = 2000;
	Boss.NowHp = 2000;

	GetClientRect(hwnd, &g_rect);

	HFONT hfont = CreateFont(20, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(g_memdc, hfont);
	SetBkMode(g_memdc, 0);

	return TRUE;
}

//绘制函数
VOID GamePaint(HWND hwnd){
	wchar_t str[100];					//保存血量
	//贴背景图片
	//2.backbmp->memdc
	SelectObject(g_bufdc, g_backbmp);	//把图片选入 memdc

	//3.g_bufdc->g_memdc
	BitBlt(g_memdc,						//目标设备
		0, 0, 800, 600,					//目标设备的范围
		g_bufdc,						//源设备
		0, 0,							//源设备的起始值
		SRCCOPY);						//拷贝	

	//显示战斗信息
	SetTextColor(g_memdc, RGB(255, 0, 0));
	for (int i = 0; i < g_iTextNum; ++i){
		TextOut(g_memdc, 20, 20 + i * 20, text[i], wcslen(text[i]));
	}

	//贴boss和英雄
	if (Boss.NowHp > 0){
		SelectObject(g_bufdc, g_boss);
		//BitBlt(g_memdc, 100, 120, 250, 250, g_bufdc, 0, 0, SRCCOPY);
		TransparentBlt(g_memdc, 100, 120, 250, 250, g_bufdc, g_bossnum * 250, 0, 250, 250, RGB(0, 0, 0));//去掉黑背景，透明绘图
		if (g_bossnum++ >= 15){
			g_bossnum = 0;
		}
		//显示血量
		swprintf_s(str, L"%d/%d", Boss.NowHp, Boss.MaxHp);
		SetTextColor(g_memdc, RGB(255, 0, 0));
		TextOut(g_memdc, 180, 310, str, wcslen(str));
	}


	if (Hero.NowHp > 0){
		SelectObject(g_bufdc, g_hero);
		//BitBlt(g_memdc, 350, 250, 250, 250, g_bufdc, 0, 0, SRCCOPY);
		TransparentBlt(g_memdc, 350, 250, 250, 250, g_bufdc, g_heronum * 250, 0, 250, 250, RGB(0, 0, 0));//去掉黑背景，透明绘图
		if (g_heronum++ >= 13){
			g_heronum = 0;
		}
		//显示血量
		swprintf_s(str, L"%d/%d", Hero.NowHp, Hero.MaxHp);
		SetTextColor(g_memdc, RGB(255, 0, 0));
		TextOut(g_memdc, 450, 465, str, wcslen(str));
		//显示蓝
		swprintf_s(str, L"%d/%d", Hero.NowMp, Hero.MaxMp);
		SetTextColor(g_memdc, RGB(0, 0, 255));
		TextOut(g_memdc, 465, 480, str, wcslen(str));
	}

	if (g_bGameOver){
		if (Hero.NowHp <= 0){
			//英雄败,
			SelectObject(g_bufdc, g_hGameOver);

			BitBlt(g_memdc, 120, 150, 543, 396, g_bufdc, 543, 0, SRCAND);
			BitBlt(g_memdc, 120, 150, 543, 396, g_bufdc, 0, 0, SRCPAINT);
		}
		else{
			SelectObject(g_bufdc, g_hVictor);
			//BitBlt(g_memdc, 240, 195, 294, 147, g_bufdc, 0, 0, SRCCOPY);
			TransparentBlt(g_memdc, 240, 195, 294, 147, g_bufdc, 0, 0, 294, 147, RGB(0, 0, 0));
		}
	}
	else if (!g_bCanAttack){
		//贴技能图标
		SelectObject(g_bufdc, g_skillbutton1);
		BitBlt(g_memdc, 600, 200, 40, 40, g_bufdc, 0, 0, SRCCOPY);

		SelectObject(g_bufdc, g_skillbutton2);
		BitBlt(g_memdc, 600, 250, 40, 40, g_bufdc, 0, 0, SRCCOPY);

		SelectObject(g_bufdc, g_skillbutton3);
		BitBlt(g_memdc, 600, 300, 40, 40, g_bufdc, 0, 0, SRCCOPY);

		SelectObject(g_bufdc, g_skillbutton4);
		BitBlt(g_memdc, 600, 350, 40, 40, g_bufdc, 0, 0, SRCCOPY);


	}
	else{
		g_frame++;//消息循环，每一次循环就是一帧
		if (g_frame >= 5 && g_frame <= 10){
			if (g_frame == 5){
				//根据不同的技能，贴上对应的技能图
				HeroAction_Logic();
				DieCheck(Boss.NowHp, false);
			}
			//hero的技能图片
			HeroActionPaint();
		}
		if (g_frame == 15){
			//怪物逻辑
			BossAction_Logic();
		}

		if (g_frame >= 16 && g_frame <= 30){
			//显示怪物的攻击图片
			BossActionPaint();
		}
		//第三十帧，回合结束
		if (g_frame == 30){
			g_bCanAttack = false;
			g_frame = 0;
			int MpRecover = 2 * rand() % Hero.Intell + 6; //这个回合需要回复的蓝
			Hero.NowMp += MpRecover;
			if (Hero.NowMp >= Hero.MaxMp){
				Hero.NowMp = Hero.MaxMp;
			}
		}
	}


	//4.g_memdc -> hdc
	BitBlt(g_hdc, 0, 0, 800, 600, g_memdc, 0, 0, SRCCOPY);
	g_tPre = GetTickCount();
}

//玩家的逻辑代码
VOID HeroAction_Logic(){
	int damage = 0;
	wchar_t str[100];
	switch (HeroAction){
	case NORMAL:
		//暴击几率
		if (rand() % 4 == 1){ //暴击率25%
			HeroAction = CRITICAL;
			damage = 4 * (3 * (rand() % Hero.Agility) + Hero.level*Hero.strength + 20);
			Boss.NowHp -= damage;

			swprintf_s(str, L"神天兵暴击了魔龙圣使造成[%d]点伤害..", damage);
			Message_Insert(str);
		}
		else{
			//普通攻击
			damage = 3 * (rand() % Hero.Agility) + Hero.level*Hero.strength + 20;//80~107
			Boss.NowHp -= damage;

			swprintf_s(str, L"神天兵使用普通攻击对魔龙圣使造成[%d]点伤害..", damage);
			Message_Insert(str);
		}
		break;
	case MAGIC://消耗30蓝
		if (Hero.NowMp >= 30){
			damage = 5 * (2 * (rand() % Hero.Agility) + Hero.level*Hero.Intell);
			Boss.NowHp -= damage;
			Hero.NowMp -= 30;

			swprintf_s(str, L"神天兵使用魔法攻击对魔龙造成[%d]点伤害..", damage);
			Message_Insert(str);

		}
		else{
			HeroAction = MISS;
		}
		break;

	case RECOVER://消耗40蓝
		if (Hero.NowMp >= 40){
			Hero.NowMp -= 40;
			int HpRecover = 3 * (rand() % Hero.Intell) + 13; //0-27
			Hero.NowHp += HpRecover;
			swprintf_s(str, L"神天兵恢复了[%d]点气血..", HpRecover);
			Message_Insert(str);

			if (Hero.NowHp >= Hero.MaxHp){
				Hero.NowHp = Hero.MaxHp;
			}
		}
		else{
			HeroAction = MISS;
		}
		break;
	}
}

//绘制英雄的技能
VOID HeroActionPaint(){
	switch (HeroAction){
	case NORMAL:
		SelectObject(g_bufdc, g_heroskill1);
		TransparentBlt(g_memdc, 50, 150, 364, 140, g_bufdc, 0, 0, 364, 140, RGB(0, 0, 0));
		break;
	case CRITICAL:
		SelectObject(g_bufdc, g_heroskill2);
		TransparentBlt(g_memdc, 50, 60, 574, 306, g_bufdc, 0, 0, 574, 306, RGB(0, 0, 0));
		break;
	case MAGIC:
		SelectObject(g_bufdc, g_heroskill3);
		TransparentBlt(g_memdc, 50, 60, 100, 77, g_bufdc, 0, 0, 100, 77, RGB(0, 0, 0));
		break;
	case RECOVER:
		SelectObject(g_bufdc, g_recover);
		TransparentBlt(g_memdc, 380, 340, 150, 150, g_bufdc, 0, 0, 150, 150, RGB(0, 0, 0));
		break;
	default:
		break;
	}
}

//Boss的逻辑代码
VOID BossAction_Logic(){
	srand((unsigned int)time(NULL));
	//血量重足的时候
	if (Boss.NowHp >= (Boss.MaxHp / 2)){
		switch (rand() % 3)
		{
		case 0:
			BossAction = NORMAL;
			break;
		case 1:
			BossAction = CRITICAL;
			break;
		case 2:
			BossAction = MAGIC;
			break;
		default:
			break;
		}
	}
	else{ //血量比较低的时候,进入狂暴状态
		switch (rand() % 3)
		{
		case 0:
			BossAction = CRITICAL;
			break;
		case 1:
			BossAction = MAGIC;
			break;
		case 2:
			BossAction = RECOVER;
			break;
		default:
			break;
		}
	}
}

//绘制Boss的技能
VOID BossActionPaint(){
	int damage = 0;
	int recover = 0;
	wchar_t str[100];
	switch (BossAction){
	case NORMAL:
		SelectObject(g_bufdc, g_bossskill1);
		TransparentBlt(g_memdc, 360, 390, 150, 120, g_bufdc, 0, 0, 150, 120, RGB(0, 0, 0));
		if (g_frame == 30){
			damage = rand() % Boss.Agility + (Boss.level*Boss.strength);
			Hero.NowHp -= damage;

			swprintf_s(str, L"魔龙圣使 释放幽冥鬼火.. 对神天兵造成[%d]伤害", damage);
			Message_Insert(str);

			DieCheck(Hero.NowHp, true);
		}
		break;
	case CRITICAL:
		SelectObject(g_bufdc, g_bossskill2);
		TransparentBlt(g_memdc, 360, 390, 249, 231, g_bufdc, 0, 0, 249, 231, RGB(0, 0, 0));
		if (g_frame == 30){
			damage = 2 * (rand() % Boss.Agility + (Boss.level*Boss.strength));
			Hero.NowHp -= damage;

			swprintf_s(str, L"魔龙圣使 脾性大发对神天兵造成[%d]伤害..", damage);
			Message_Insert(str);

			DieCheck(Hero.NowHp, true);
		}
		break;
	case MAGIC:
		SelectObject(g_bufdc, g_bossskill3);
		TransparentBlt(g_memdc, 50, 60, 574, 306, g_bufdc, 0, 0, 574, 306, RGB(0, 0, 0));
		if (g_frame == 30){
			damage = 2 * (2 * (rand() % Boss.Agility) + Boss.strength*Boss.Intell);
			Hero.NowHp -= damage;

			swprintf_s(str, L"魔龙圣使使用魔法攻击对神天兵造成[%d]伤害..", damage);
			Message_Insert(str);

			recover = (int)((double)damage*0.2);
			Boss.NowHp += recover;
			DieCheck(Hero.NowHp, true);
		}
		break;
	case RECOVER:
		SelectObject(g_bufdc, g_recover);
		TransparentBlt(g_memdc, 150, 150, 150, 150, g_bufdc, 0, 0, 150, 150, RGB(0, 0, 0));
		if (g_frame == 30){
			recover = 2 * Boss.Intell * Boss.Intell;
			Hero.NowHp += recover;

			swprintf_s(str, L"魔龙圣使恢复了[%d]点气血..", recover);
			Message_Insert(str);

			if (Boss.NowHp > Boss.MaxHp){
				Boss.NowHp = Boss.MaxHp;
			}
		}
		break;
	default:
		break;
	}
}

//判断死亡
VOID DieCheck(int nowhp, bool ishero){
	wchar_t str[100];
	if (nowhp <= 0){
		g_bGameOver = true;
		if (ishero){
			swprintf_s(str, L"胜败乃兵家常事,大侠请不要气馁!");
			Message_Insert(str);
			PlaySound(L"./res/failure.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else{
			swprintf_s(str, L"长江后浪推前浪,大侠武功盖世!");
			Message_Insert(str);
			PlaySound(L"./res/victory.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
	}
}

//插入信息栏
VOID Message_Insert(wchar_t* str){
	if (g_iTextNum < 6){
		swprintf_s(text[g_iTextNum], str);
		g_iTextNum++;
	}
	else{
		for (int i = 1; i < g_iTextNum; ++i){
			swprintf_s(text[i - 1], text[i]);
		}
		swprintf_s(text[g_iTextNum - 1], str);
	}
}

BOOL Timer(){
	g_tNow = GetTickCount();
	if (g_tNow - g_tPre >= 80){ //间隔大于80ms
		return true;
	}
	return false;
}