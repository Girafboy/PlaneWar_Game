#pragma once

#include "Plane.h"

enum BulletType { one, two, three_open };//�ӵ������ͣ������ӵ���

//�����ӵ���
class Bullet : public Object
{
public:
	Bullet() {};
	Bullet(Plane *plane, int x);
	void display(QPainter &painter);
};

//�з��ӵ�
class Bullet_Enemy :public Bullet
{
public:
	Bullet_Enemy(Plane *plane, int x) :Bullet(plane, x) {}
	void display(QPainter &painter);
};

//�����ӵ�
class Bullet_Own :public Bullet
{
public:
	Bullet_Own(){}
	Bullet_Own(Plane *plane, int x) :Bullet(plane, x) {
		this->getrect()->setWidth(5);
	}
	void display(QPainter &painter);
};

//�ӵ��飬��Ҫ���ڹ��첻ͬ���ͺ���ϵ��ӵ���
class BulletGroup
{
private:
	int amount = 3;//�ӵ�������
	Bullet * bullet[3] = { NULL };
public:
	BulletGroup() {};
	BulletGroup(Plane *plane, BulletType type, bool own = 0);
	BulletGroup(PlaneGroup *p, BulletType type);//���캯��
	void display(QPainter &painter);//��ͼ
	bool trash();//���Խ��
	int getamount();
	Bullet** getbullet();
	void move(Direction direction,int step);
	void move(Object* o, int step);//�����ӵ����ƶ�
};
