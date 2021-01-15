#pragma once
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#pragma comment (lib, "Winmm.lib")//����Winmm.lib��


enum my{
	WIDTH = 591,		// ���ڿ��
	HEIGHT = 664,		// ���ڸ߶�
	BULLLET_NUM = 1,	// �ӵ�����
	ENEMY_NUM = 15,		// �л�����
	BIG,				// �л����ʹ�
	SMALL,				// �л�����С
};

// �ɻ����ӵ�״̬
struct Plance{
	int x;		// x ����
	int y;		// y ����
	bool live;	// �Ƿ���
	int width;	// �ɻ����
	int height;	// �ɻ��߶�
	int hp;		// Ѫ��ֵ
	int type;	// �л�����
};


void loadImg();					//������Դ
bool Timer(size_t ms, int id);	//��ʱ��
void enemyHp(int i);			//�л�����ֵ
void gameInit();				//��Ϸ��ʼ��
void  createBullet();			//�����ӵ�
void createEnemy();				//�����л�
void enemyMove();				//�л��ƶ� 
void bulletMove();				//�ӵ��ƶ�
void gameDraw();				//��ϷͼƬ����
void playerMove(int speed);		//������ɫ�ƶ�
void playPlance();				//��ײ���
void startGame();				//������Ϸ