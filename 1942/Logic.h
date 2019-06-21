#pragma once

#include "Bullet.h"
#include "Item.h"

#define ENEMY_BULLET_AMOUNT 1000
#define OWN_BULLET_AMOUNT 200
#define SIMPLE_PLANE_AMOUNT 1000
#define BOSS_PLANE_AMOUNT 50

//逻辑类
class Logic
{
private:
	int score=0;
	int level=1;
	int life=3;
	int brave=3;//分数、关卡、生命、大招等
	BulletType btype = one;//玩家子弹类型
	bool isCollision(Object *p, Object *b);
	bool isCollision(PlaneGroup *p, Object *b);
	bool isCollision(PlaneGroup *p, PlaneGroup *b);
	bool isCollision(PlaneGroup *p, BulletGroup *b);
	bool isCollision(Object *p, BulletGroup *b);//检测不同性质类之间的碰撞
public:
	int getscore();
	int getlevel();
	int getlife();
	int getbrave();//获取分数、关卡、生命、大招等
	void setscore(int x);
	void setlevel(int x);
	void setlife(int x);
	void setbrave(int x);//设定分数、关卡、生命、大招等，用于文件读取设定
	void scoreadd();//加分
	void leveladd();//增加关卡
	void lifeadd();//增加生命
	void lifesub();//减少生命
	void braveadd();//增加大招
	void bravesub();//减少大招
	BulletType gettype();//获取子弹类型
	void settype(BulletType type);//设置子弹类型
	void doCollision(BulletGroup ** bown, BulletGroup ** benemy, Plane_Own * pown, PlaneGroup * son,
		PlaneGroup ** penemy, Plane_Enemy_Boss ** boss, Item* &i);//检测画面一系列实体之间的碰撞
	void clearenemy(PlaneGroup **p, BulletGroup **b);//清除普通敌人

};
