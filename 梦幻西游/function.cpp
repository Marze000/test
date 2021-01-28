#include "head.h"


struct {
	int		NowMp;		//��ǰ����
	int		NowHp;		//��ǰ��Ѫ
	int		MaxMp;		//������
	int		MaxHp;		//�����Ѫ
	int		level;		//�ȼ�
	int		strength;	//����
	int		Intell;		//����
	int		Agility;	//����
}Boss, Hero;

//***********ȫ�ֱ�������***********
HDC			g_hdc, g_memdc, g_bufdc;		//�����豸�ֲ����ڴ��豸���,�ڴ��豸���
DWORD g_tPre, g_tNow;						//��ʱ�����ڼ�ʱ
ActionType	HeroAction, BossAction;			//ö�����͵� hero��boss����
wchar_t		text[8][100];					//����洢���ֵ��ַ�������
int			g_bossnum = 0;					//����bossͼƬ����
int			g_heronum = 0;					//����Ӣ��ͼƬ����
int			g_iTextNum = 0;					//���ָ���
int			g_frame;						//֡��

RECT		g_rect;							//��һ������������ʾ����
BOOL		g_bCanAttack;					//Ӣ���Ƿ���Թ���
BOOL		g_bGameOver;					//��Ϸ�Ƿ����


HBITMAP		g_heroskill1, g_heroskill2, g_heroskill3;	//Ӣ�ۼ���
HBITMAP		g_bossskill1, g_bossskill2, g_bossskill3;	// boss ����
HBITMAP		g_recover;									//�ָ�
HBITMAP		g_bmp;										//��λͼ
HBITMAP		g_backbmp, g_skillbutton1, g_skillbutton2, g_skillbutton3, g_skillbutton4;		//����ͼƬ
HBITMAP		g_hero, g_boss;								//Ӣ�ۣ�����
HBITMAP		g_hGameOver, g_hVictor;						//��Ϸʤ������Ϸ����

//���ڹ��̺���:��Ҫ����û��Ĳ�ָͬ�������ͬ����Ӧ
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
	switch (message)
	{
	case WM_LBUTTONDOWN://����������
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


//��Ϸ��ʼ��
BOOL GameInit(HWND hwnd){
	srand((unsigned int)time(NULL));
	//����
	g_hdc = GetDC(hwnd);
	g_memdc = CreateCompatibleDC(g_hdc); //�����Դ��ڼ��ݵ��豸
	g_bufdc = CreateCompatibleDC(g_hdc);
	g_bmp = CreateCompatibleBitmap(g_hdc, WND_WIDTH, WND_HEIGHT);//�������ݿ�λͼ
	SelectObject(g_memdc, g_bmp);//��λͼѡ��memdc

	// �ز�
	g_backbmp = (HBITMAP)LoadImage(NULL, L"./res/bg.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
	g_skillbutton1 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton1.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_skillbutton2 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton2.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_skillbutton3 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton3.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_skillbutton4 = (HBITMAP)LoadImage(NULL, L"./res/skillbutton4.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);

	g_hero = (HBITMAP)LoadImage(NULL, L"./res/1001.bmp", IMAGE_BITMAP, 3500, 250, LR_LOADFROMFILE);
	g_boss = (HBITMAP)LoadImage(NULL, L"./res/BOSS.bmp", IMAGE_BITMAP, 4000, 250, LR_LOADFROMFILE);

	g_heroskill1 = (HBITMAP)LoadImage(NULL, L"./res/heroslash.bmp", IMAGE_BITMAP, 364, 140, LR_LOADFROMFILE);	//��ͨ����
	g_heroskill2 = (HBITMAP)LoadImage(NULL, L"./res/herocritical.bmp", IMAGE_BITMAP, 574, 306, LR_LOADFROMFILE);//����
	g_heroskill3 = (HBITMAP)LoadImage(NULL, L"./res/heromagic.bmp", IMAGE_BITMAP, 100, 77, LR_LOADFROMFILE);	//ħ������

	g_bossskill1 = (HBITMAP)LoadImage(NULL, L"./res/monsterslash.bmp", IMAGE_BITMAP, 150, 120, LR_LOADFROMFILE);
	g_bossskill2 = (HBITMAP)LoadImage(NULL, L"./res/monstercritical.bmp", IMAGE_BITMAP, 249, 231, LR_LOADFROMFILE);
	g_bossskill3 = (HBITMAP)LoadImage(NULL, L"./res/monstermagic.bmp", IMAGE_BITMAP, 200, 131, LR_LOADFROMFILE);

	g_recover = (HBITMAP)LoadImage(NULL, L"./res/recover.bmp", IMAGE_BITMAP, 150, 150, LR_LOADFROMFILE);

	g_hGameOver = (HBITMAP)LoadImage(NULL, L"./res/gameover.bmp", IMAGE_BITMAP, 1086, 396, LR_LOADFROMFILE);
	g_hVictor = (HBITMAP)LoadImage(NULL, L"./res/victory.bmp", IMAGE_BITMAP, 294, 147, LR_LOADFROMFILE);


	//������ӵ���Դ��.wav�ļ���IDR_DENG������Ƶ��Դres/wav/1.wav�ı�ţ�SND_RESOURCE����ʹ����Դ��SND_ASYNC�����첽���ţ�SND_LOOP����ѭ������
	PlaySound(_T("./res/�λ�����ԭ��-ս��1-ɭ��.wav"), NULL, SND_ASYNC | SND_LOOP);


	//��ʼӢ�ۻ�����
	Hero.Agility = 20;
	Hero.Intell = 10;
	Hero.level = 6;
	Hero.strength = 10;
	Hero.MaxHp = 1000;
	Hero.NowHp = 1000;
	Hero.MaxMp = 60;
	Hero.NowMp = 60;
	//��ʼ��Boss����
	Boss.Agility = 10;
	Boss.Intell = 10;
	Boss.level = 10;
	Boss.strength = 10;
	Boss.MaxHp = 2000;
	Boss.NowHp = 2000;

	GetClientRect(hwnd, &g_rect);

	HFONT hfont = CreateFont(20, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, L"΢���ź�");
	SelectObject(g_memdc, hfont);
	SetBkMode(g_memdc, 0);

	return TRUE;
}

//���ƺ���
VOID GamePaint(HWND hwnd){
	wchar_t str[100];					//����Ѫ��
	//������ͼƬ
	//2.backbmp->memdc
	SelectObject(g_bufdc, g_backbmp);	//��ͼƬѡ�� memdc

	//3.g_bufdc->g_memdc
	BitBlt(g_memdc,						//Ŀ���豸
		0, 0, 800, 600,					//Ŀ���豸�ķ�Χ
		g_bufdc,						//Դ�豸
		0, 0,							//Դ�豸����ʼֵ
		SRCCOPY);						//����	

	//��ʾս����Ϣ
	SetTextColor(g_memdc, RGB(255, 0, 0));
	for (int i = 0; i < g_iTextNum; ++i){
		TextOut(g_memdc, 20, 20 + i * 20, text[i], wcslen(text[i]));
	}

	//��boss��Ӣ��
	if (Boss.NowHp > 0){
		SelectObject(g_bufdc, g_boss);
		//BitBlt(g_memdc, 100, 120, 250, 250, g_bufdc, 0, 0, SRCCOPY);
		TransparentBlt(g_memdc, 100, 120, 250, 250, g_bufdc, g_bossnum * 250, 0, 250, 250, RGB(0, 0, 0));//ȥ���ڱ�����͸����ͼ
		if (g_bossnum++ >= 15){
			g_bossnum = 0;
		}
		//��ʾѪ��
		swprintf_s(str, L"%d/%d", Boss.NowHp, Boss.MaxHp);
		SetTextColor(g_memdc, RGB(255, 0, 0));
		TextOut(g_memdc, 180, 310, str, wcslen(str));
	}


	if (Hero.NowHp > 0){
		SelectObject(g_bufdc, g_hero);
		//BitBlt(g_memdc, 350, 250, 250, 250, g_bufdc, 0, 0, SRCCOPY);
		TransparentBlt(g_memdc, 350, 250, 250, 250, g_bufdc, g_heronum * 250, 0, 250, 250, RGB(0, 0, 0));//ȥ���ڱ�����͸����ͼ
		if (g_heronum++ >= 13){
			g_heronum = 0;
		}
		//��ʾѪ��
		swprintf_s(str, L"%d/%d", Hero.NowHp, Hero.MaxHp);
		SetTextColor(g_memdc, RGB(255, 0, 0));
		TextOut(g_memdc, 450, 465, str, wcslen(str));
		//��ʾ��
		swprintf_s(str, L"%d/%d", Hero.NowMp, Hero.MaxMp);
		SetTextColor(g_memdc, RGB(0, 0, 255));
		TextOut(g_memdc, 465, 480, str, wcslen(str));
	}

	if (g_bGameOver){
		if (Hero.NowHp <= 0){
			//Ӣ�۰�,
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
		//������ͼ��
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
		g_frame++;//��Ϣѭ����ÿһ��ѭ������һ֡
		if (g_frame >= 5 && g_frame <= 10){
			if (g_frame == 5){
				//���ݲ�ͬ�ļ��ܣ����϶�Ӧ�ļ���ͼ
				HeroAction_Logic();
				DieCheck(Boss.NowHp, false);
			}
			//hero�ļ���ͼƬ
			HeroActionPaint();
		}
		if (g_frame == 15){
			//�����߼�
			BossAction_Logic();
		}

		if (g_frame >= 16 && g_frame <= 30){
			//��ʾ����Ĺ���ͼƬ
			BossActionPaint();
		}
		//����ʮ֡���غϽ���
		if (g_frame == 30){
			g_bCanAttack = false;
			g_frame = 0;
			int MpRecover = 2 * rand() % Hero.Intell + 6; //����غ���Ҫ�ظ�����
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

//��ҵ��߼�����
VOID HeroAction_Logic(){
	int damage = 0;
	wchar_t str[100];
	switch (HeroAction){
	case NORMAL:
		//��������
		if (rand() % 4 == 1){ //������25%
			HeroAction = CRITICAL;
			damage = 4 * (3 * (rand() % Hero.Agility) + Hero.level*Hero.strength + 20);
			Boss.NowHp -= damage;

			swprintf_s(str, L"�����������ħ��ʥʹ���[%d]���˺�..", damage);
			Message_Insert(str);
		}
		else{
			//��ͨ����
			damage = 3 * (rand() % Hero.Agility) + Hero.level*Hero.strength + 20;//80~107
			Boss.NowHp -= damage;

			swprintf_s(str, L"�����ʹ����ͨ������ħ��ʥʹ���[%d]���˺�..", damage);
			Message_Insert(str);
		}
		break;
	case MAGIC://����30��
		if (Hero.NowMp >= 30){
			damage = 5 * (2 * (rand() % Hero.Agility) + Hero.level*Hero.Intell);
			Boss.NowHp -= damage;
			Hero.NowMp -= 30;

			swprintf_s(str, L"�����ʹ��ħ��������ħ�����[%d]���˺�..", damage);
			Message_Insert(str);

		}
		else{
			HeroAction = MISS;
		}
		break;

	case RECOVER://����40��
		if (Hero.NowMp >= 40){
			Hero.NowMp -= 40;
			int HpRecover = 3 * (rand() % Hero.Intell) + 13; //0-27
			Hero.NowHp += HpRecover;
			swprintf_s(str, L"������ָ���[%d]����Ѫ..", HpRecover);
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

//����Ӣ�۵ļ���
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

//Boss���߼�����
VOID BossAction_Logic(){
	srand((unsigned int)time(NULL));
	//Ѫ�������ʱ��
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
	else{ //Ѫ���Ƚϵ͵�ʱ��,�����״̬
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

//����Boss�ļ���
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

			swprintf_s(str, L"ħ��ʥʹ �ͷ���ڤ���.. ����������[%d]�˺�", damage);
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

			swprintf_s(str, L"ħ��ʥʹ Ƣ�Դ󷢶���������[%d]�˺�..", damage);
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

			swprintf_s(str, L"ħ��ʥʹʹ��ħ����������������[%d]�˺�..", damage);
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

			swprintf_s(str, L"ħ��ʥʹ�ָ���[%d]����Ѫ..", recover);
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

//�ж�����
VOID DieCheck(int nowhp, bool ishero){
	wchar_t str[100];
	if (nowhp <= 0){
		g_bGameOver = true;
		if (ishero){
			swprintf_s(str, L"ʤ���˱��ҳ���,�����벻Ҫ����!");
			Message_Insert(str);
			PlaySound(L"./res/failure.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else{
			swprintf_s(str, L"����������ǰ��,�����书����!");
			Message_Insert(str);
			PlaySound(L"./res/victory.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
	}
}

//������Ϣ��
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
	if (g_tNow - g_tPre >= 80){ //�������80ms
		return true;
	}
	return false;
}