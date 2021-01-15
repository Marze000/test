#pragma once
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#pragma comment (lib, "Winmm.lib")//导入Winmm.lib库


enum my{
	WIDTH = 591,		// 窗口宽度
	HEIGHT = 664,		// 窗口高度
	BULLLET_NUM = 1,	// 子弹数量
	ENEMY_NUM = 15,		// 敌机数量
	BIG,				// 敌机类型大
	SMALL,				// 敌机类型小
};

// 飞机、子弹状态
struct Plance{
	int x;		// x 坐标
	int y;		// y 坐标
	bool live;	// 是否存活
	int width;	// 飞机宽度
	int height;	// 飞机高度
	int hp;		// 血量值
	int type;	// 敌机类型
};


void loadImg();					//加载资源
bool Timer(size_t ms, int id);	//定时器
void enemyHp(int i);			//敌机生命值
void gameInit();				//游戏初始化
void  createBullet();			//创建子弹
void createEnemy();				//创建敌机
void enemyMove();				//敌机移动 
void bulletMove();				//子弹移动
void gameDraw();				//游戏图片绘制
void playerMove(int speed);		//监听角色移动
void playPlance();				//碰撞检测
void startGame();				//启动游戏