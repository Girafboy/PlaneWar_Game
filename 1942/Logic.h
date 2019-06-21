#pragma once

#include "Bullet.h"
#include "Item.h"

#define ENEMY_BULLET_AMOUNT 1000
#define OWN_BULLET_AMOUNT 200
#define SIMPLE_PLANE_AMOUNT 1000
#define BOSS_PLANE_AMOUNT 50

//�߼���
class Logic
{
private:
	int score=0;
	int level=1;
	int life=3;
	int brave=3;//�������ؿ������������е�
	BulletType btype = one;//����ӵ�����
	bool isCollision(Object *p, Object *b);
	bool isCollision(PlaneGroup *p, Object *b);
	bool isCollision(PlaneGroup *p, PlaneGroup *b);
	bool isCollision(PlaneGroup *p, BulletGroup *b);
	bool isCollision(Object *p, BulletGroup *b);//��ⲻͬ������֮�����ײ
public:
	int getscore();
	int getlevel();
	int getlife();
	int getbrave();//��ȡ�������ؿ������������е�
	void setscore(int x);
	void setlevel(int x);
	void setlife(int x);
	void setbrave(int x);//�趨�������ؿ������������еȣ������ļ���ȡ�趨
	void scoreadd();//�ӷ�
	void leveladd();//���ӹؿ�
	void lifeadd();//��������
	void lifesub();//��������
	void braveadd();//���Ӵ���
	void bravesub();//���ٴ���
	BulletType gettype();//��ȡ�ӵ�����
	void settype(BulletType type);//�����ӵ�����
	void doCollision(BulletGroup ** bown, BulletGroup ** benemy, Plane_Own * pown, PlaneGroup * son,
		PlaneGroup ** penemy, Plane_Enemy_Boss ** boss, Item* &i);//��⻭��һϵ��ʵ��֮�����ײ
	void clearenemy(PlaneGroup **p, BulletGroup **b);//�����ͨ����

};
