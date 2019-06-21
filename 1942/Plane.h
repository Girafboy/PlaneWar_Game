#pragma once

#include "Object.h"

enum PlaneType { SON, ENEMY };//�ɻ����ͣ����ڷɻ���

//����ɻ���
class Plane : public Object
{
};

//��ͨ�л�
class Plane_Enemy :public Plane
{
public:
	Plane_Enemy();
	void display(QPainter &painter);
};

//��ҷɻ�
class Plane_Own :public Plane
{
public:
	Plane_Own();
	void display(QPainter &painter);
	void move(Direction direction,int step);
};

//�ӻ�
class Plane_Son :public Plane
{
public:
	Plane_Son(Plane *p, bool left);
	void display(QPainter &painter);
};

//Boss�ɻ�
class Plane_Enemy_Boss :public Plane
{
private:
	int HP;
public:
	Plane_Enemy_Boss(int HP = 1);
	void display(QPainter &painter);
	bool HP_cut();
};

//�ɻ��飬��Ҫ���ڹ��첻ͬ���ͺ���ϵķɻ���
class PlaneGroup
{
private:
	Plane * father;//�ӻ������Ķ���
	int amount = 3;//��ͨ�л�����
	Plane * plane[3] = { NULL };
	Plane_Son * son[2] = { NULL };
public:
	PlaneGroup(PlaneType type, Plane *p = NULL);
	void display(QPainter &painter, PlaneType type);//��ͼ
	void move(PlaneType type, int step);//�ƶ�
	Plane ** getplane();
	Plane_Son **getson();
	int getamount();//��ȡ�ɻ�����
	bool trash();//���Խ��
};