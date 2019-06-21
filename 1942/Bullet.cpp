#include "Bullet.h"

//抽象子弹部分
Bullet::Bullet(Plane * plane, int x)
{
	if (this->getrect() == NULL) this->setrect((*plane->getrect()).center().x() + x, (*plane->getrect()).center().y(), 10, 10);
}//构造

void Bullet::display(QPainter &painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/zidan.png"));
}//绘制

//己方子弹部分
void Bullet_Own::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/zijizidan.png"));
}//绘制

//敌方子弹部分
void Bullet_Enemy::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/zidan.png"));
}//绘制

//子弹组部分
BulletGroup::BulletGroup(Plane * plane, BulletType type,bool own)
{
	if(!own)
		switch (type)
		{
		case one://单个子弹
			for (int i = 0; i < amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet(plane, 0);
					break;
				}
			break;
		case two://双发子弹
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet(plane, 10);
					break;
				}
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet(plane, -10);
					break;
				}
			break;
		case three_open://三发子弹
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet(plane, 50);
					break;
				}
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet(plane, -50);
					break;
				}
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet(plane, 0);
					break;
				}
			break;
		}
	else
		switch (type)
		{
		case one://单个子弹
			for (int i = 0; i < amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet_Own(plane, 0);
					break;
				}
			break;
		case two://双发子弹
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet_Own(plane, 10);
					break;
				}
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet_Own(plane, -10);
					break;
				}
			break;
		case three_open://三发子弹
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet_Own(plane, 20);
					break;
				}
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet_Own(plane, -20);
					break;
				}
			for (int i = 0; i<amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet_Own(plane, 0);
					break;
				}
			break;
		}
}

BulletGroup::BulletGroup(PlaneGroup * p, BulletType type)
{
	for (int j = 0; j < p->getamount(); j++)
		if(p->getplane()[j]!=NULL)
			switch (type)
			{
			case one://单发子弹
				for (int i = 0; i < amount; i++)
					if (bullet[i] == NULL)
					{
						bullet[i] = new Bullet(p->getplane()[j], 0);
						break;
					}
				break;
			case two://双发子弹
				for (int i = 0; i < amount; i++)
					if (bullet[i] == NULL)
					{
						bullet[i] = new Bullet(p->getplane()[j], 10);
						break;
					}
				for (int i = 0; i < amount; i++)
					if (bullet[i] == NULL)
					{
						bullet[i] = new Bullet(p->getplane()[j], -10);
						break;
					}
				break;
			case three_open://三发子弹
				for (int i = 0; i < amount; i++)
					if (bullet[i] == NULL)
					{
						bullet[i] = new Bullet(p->getplane()[j], 50);
						break;
					}
				for (int i = 0; i < amount; i++)
					if (bullet[i] == NULL)
					{
						bullet[i] = new Bullet(p->getplane()[j], -50);
						break;
					}
				for (int i = 0; i < amount; i++)
					if (bullet[i] == NULL)
					{
						bullet[i] = new Bullet(p->getplane()[j], 0);
						break;
					}
				break;
			}
}//构造

void BulletGroup::display(QPainter & painter)
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
		{
			bullet[i]->display(painter);
		}
}//绘制

bool BulletGroup::trash()
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
			if (bullet[i]->trash())	bullet[i] = NULL;
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)	return false;
	delete this;
	return true;
}//检测消除越界

int BulletGroup::getamount()
{
	return amount;
}//获取子弹数量

Bullet** BulletGroup::getbullet()
{
	return bullet;
}

void BulletGroup::move(Direction direction,int step)
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
			bullet[i]->move(direction,step);
}//移动——普通

void BulletGroup::move(Object * o, int step)
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
			bullet[i]->move(o, step);
}//移动——追踪

