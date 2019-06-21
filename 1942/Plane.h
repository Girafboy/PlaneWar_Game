#pragma once

#include "Object.h"

enum PlaneType { SON, ENEMY };//飞机类型，用于飞机组

//抽象飞机类
class Plane : public Object
{
};

//普通敌机
class Plane_Enemy :public Plane
{
public:
	Plane_Enemy();
	void display(QPainter &painter);
};

//玩家飞机
class Plane_Own :public Plane
{
public:
	Plane_Own();
	void display(QPainter &painter);
	void move(Direction direction,int step);
};

//子机
class Plane_Son :public Plane
{
public:
	Plane_Son(Plane *p, bool left);
	void display(QPainter &painter);
};

//Boss飞机
class Plane_Enemy_Boss :public Plane
{
private:
	int HP;
public:
	Plane_Enemy_Boss(int HP = 1);
	void display(QPainter &painter);
	bool HP_cut();
};

//飞机组，主要用于构造不同类型和组合的飞机组
class PlaneGroup
{
private:
	Plane * father;//子机依附的对象
	int amount = 3;//普通敌机数量
	Plane * plane[3] = { NULL };
	Plane_Son * son[2] = { NULL };
public:
	PlaneGroup(PlaneType type, Plane *p = NULL);
	void display(QPainter &painter, PlaneType type);//绘图
	void move(PlaneType type, int step);//移动
	Plane ** getplane();
	Plane_Son **getson();
	int getamount();//获取飞机数量
	bool trash();//检测越界
};