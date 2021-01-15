#include "flane.h"
IMAGE bk;				//������Դ
IMAGE img_role[2];		//ս��ͼƬ
IMAGE img_bull[2];		//�ӵ�ͼƬ
IMAGE img_enemy[2][2];	//�л�ͼƬ
struct Plance player, bull[BULLLET_NUM], enemy[ENEMY_NUM];

void loadImg(){
	loadimage(&bk, "./images/background.jpg");
	loadimage(&img_role[0], "./images/planeNormal_1.jpg");
	loadimage(&img_role[1], "./images/planeNormal_2.jpg");
	
	loadimage(&img_bull[0], "./images/bullet1.jpg");
	loadimage(&img_bull[1], "./images/bullet2.jpg");

	//���صл�ͼƬ
	loadimage(&img_enemy[0][0], "./images/enemy_1.jpg");
	loadimage(&img_enemy[0][1], "./images/enemy_2.jpg");
	loadimage(&img_enemy[1][0], "./images/enemyPlane1.jpg");
	loadimage(&img_enemy[1][1], "./images/enemyPlane2.jpg");

	mciSendString("open \"./images/game_music.mp3\" alias mymusic", NULL, 0, NULL);
	mciSendString("play mymusic repeat", NULL, 0, NULL);

}

bool Timer(size_t ms, int id){
	static DWORD t[10];
	if (clock() - t[id] > ms){
		t[id] = clock();
		return true;
	}
	return false;
}

void enemyHp(int i){
	if (rand() % 10 == 0){
		enemy[i].type = BIG;
		enemy[i].hp = 3;
		enemy[i].width = 104;
		enemy[i].height = 148;
	}
	else{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].width = 52;
		enemy[i].height = 39;
	}
}
void gameInit(){
	initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);	// ������Ϸ����
	srand((int)time(NULL)); // �������
	HWND hWnd = GetHWnd(); // ��ȡ���ھ��
	SetWindowText(hWnd, "�ɻ���ս"); // ���ñ���

	loadImg(); // ������Դ

	player.x = WIDTH / 2;
	player.y = HEIGHT - 120;
	player.live = true;
	// ��ʼ���ӵ�
	for (size_t i = 0; i < BULLLET_NUM; ++i){
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live = false;
	}
	// ��ʼ���л�
	for (size_t i = 0; i < ENEMY_NUM; ++i){
		enemy[i].live = false;
		enemyHp(i);
	}
}

void  createBullet(){
	for (size_t i = 0; i < BULLLET_NUM; ++i){
		if (!bull[i].live){
			bull[i].x = player.x + 45;
			bull[i].y = player.y - 10;
			bull[i].live = true;
			break;
		}
	}
}

void createEnemy(){
	for (size_t i = 0; i < ENEMY_NUM; ++i){
		if (!enemy[i].live){
			enemy[i].x = rand() % (WIDTH - 104);
			enemy[i].y = 0;
			enemy[i].live = true;
			enemyHp(i);
			break;
		}
	}
}

void enemyMove(){
	for (size_t i = 0; i < ENEMY_NUM; ++i){
		if (enemy[i].live){
			enemy[i].y += 1;
			if (enemy[i].y > HEIGHT){
				enemy[i].live = false;
			}
		}
	}
}

void bulletMove(){
	for (size_t i = 0; i < BULLLET_NUM; ++i){
		if (bull[i].live){
			bull[i].y -= 1;
			if (bull[i].y < 0){
				bull[i].live = false;
			}
		}
	}
}

// ��ϷͼƬ����
void gameDraw(){
	putimage(0, 0, &bk);
	putimage(player.x, player.y, &img_role[0], NOTSRCERASE);
	putimage(player.x, player.y, &img_role[1], SRCINVERT);

	for (size_t i = 0; i < BULLLET_NUM; ++i){
		if (bull[i].live){
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bull[1], SRCINVERT);
		}
	}

	for (size_t i = 0; i < ENEMY_NUM; ++i){
		if (enemy[i].live){
			if (enemy[i].type == BIG){
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][1], SRCINVERT);
			}
			else{
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][1], SRCINVERT);
			}
		}
	}
}

// ��ɫ�ƶ�
void playerMove(int speed){

	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')){
		if (player.y > 0){
			player.y -= speed;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')){
		if (player.y + 60< HEIGHT){
			player.y += speed;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')){
		if (player.x + 60> 0){
			player.x -= speed;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')){
		if (player.x + 60< WIDTH){
			player.x += speed;
		}
	}
	if (GetAsyncKeyState(VK_SPACE) && Timer(100, 2)){
		createBullet();
	}

}

//  ��ײ���
void playPlance(){
	for (int i = 0; i < ENEMY_NUM; ++i){
		if (!enemy[i].live){
			continue;
		}
		//�ӵ�
		for (int k = 0; k < BULLLET_NUM; ++k){
			if (!bull[i].live){
				continue;
			}
			// ��ײ���
			if (bull[k].x >= enemy[i].x && bull[k].x <= enemy[i].x + enemy[i].width
				&&  bull[k].y >= enemy[i].y && bull[k].y <= enemy[i].y + enemy[i].height){
				bull[k].live = false;
				enemy[i].hp -= 1;
			}
		}
		if (enemy[i].hp <= 0){
			enemy[i].live = false;
		}
	}
}

void startGame(){
	gameInit();
	BeginBatchDraw();//˫�����ͼ
	// ��Ϸ��ѭ��
	while (1){
		gameDraw();
		FlushBatchDraw();
		playerMove(1);
		bulletMove();
		if (Timer(500, 0)){
			createEnemy();
		}
		if (Timer(1, 1)){
			enemyMove();
		}
		playPlance();
	}
	EndBatchDraw();

}