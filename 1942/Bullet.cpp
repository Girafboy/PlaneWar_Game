#include "Bullet.h"

//�����ӵ�����
Bullet::Bullet(Plane * plane, int x)
{
	if (this->getrect() == NULL) this->setrect((*plane->getrect()).center().x() + x, (*plane->getrect()).center().y(), 10, 10);
}//����

void Bullet::display(QPainter &painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/zidan.png"));
}//����

//�����ӵ�����
void Bullet_Own::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/zijizidan.png"));
}//����

//�з��ӵ�����
void Bullet_Enemy::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/zidan.png"));
}//����

//�ӵ��鲿��
BulletGroup::BulletGroup(Plane * plane, BulletType type,bool own)
{
	if(!own)
		switch (type)
		{
		case one://�����ӵ�
			for (int i = 0; i < amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet(plane, 0);
					break;
				}
			break;
		case two://˫���ӵ�
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
		case three_open://�����ӵ�
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
		case one://�����ӵ�
			for (int i = 0; i < amount; i++)
				if (bullet[i] == NULL)
				{
					bullet[i] = new Bullet_Own(plane, 0);
					break;
				}
			break;
		case two://˫���ӵ�
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
		case three_open://�����ӵ�
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
			case one://�����ӵ�
				for (int i = 0; i < amount; i++)
					if (bullet[i] == NULL)
					{
						bullet[i] = new Bullet(p->getplane()[j], 0);
						break;
					}
				break;
			case two://˫���ӵ�
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
			case three_open://�����ӵ�
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
}//����

void BulletGroup::display(QPainter & painter)
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
		{
			bullet[i]->display(painter);
		}
}//����

bool BulletGroup::trash()
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
			if (bullet[i]->trash())	bullet[i] = NULL;
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)	return false;
	delete this;
	return true;
}//�������Խ��

int BulletGroup::getamount()
{
	return amount;
}//��ȡ�ӵ�����

Bullet** BulletGroup::getbullet()
{
	return bullet;
}

void BulletGroup::move(Direction direction,int step)
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
			bullet[i]->move(direction,step);
}//�ƶ�������ͨ

void BulletGroup::move(Object * o, int step)
{
	for (int i = 0; i < amount; i++)
		if (bullet[i] != NULL)
			bullet[i]->move(o, step);
}//�ƶ�����׷��

