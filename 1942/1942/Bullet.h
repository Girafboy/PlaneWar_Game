#pragma once

#include "Plane.h"

enum BulletType { one, two, three_open };//子弹的类型，用于子弹组

//抽象子弹类
class Bullet : public Object
{
public:
	Bullet() {};
	Bullet(Plane *plane, int x);
	void display(QPainter &painter);
};

//敌方子弹
class Bullet_Enemy :public Bullet
{
public:
	Bullet_Enemy(Plane *plane, int x) :Bullet(plane, x) {}
	void display(QPainter &painter);
};

//己方子弹
class Bullet_Own :public Bullet
{
public:
	Bullet_Own(){}
	Bullet_Own(Plane *plane, int x) :Bullet(plane, x) {
		this->getrect()->setWidth(5);
	}
	void display(QPainter &painter);
};

//子弹组，主要用于构造不同类型和组合的子弹组
class BulletGroup
{
private:
	int amount = 3;//子弹的数量
	Bullet * bullet[3] = { NULL };
public:
	BulletGroup() {};
	BulletGroup(Plane *plane, BulletType type, bool own = 0);
	BulletGroup(PlaneGroup *p, BulletType type);//构造函数
	void display(QPainter &painter);//绘图
	bool trash();//检测越界
	int getamount();
	Bullet** getbullet();
	void move(Direction direction,int step);
	void move(Object* o, int step);//控制子弹组移动
};
