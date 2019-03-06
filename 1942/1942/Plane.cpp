#include "Plane.h"

//��ҷɻ�����
Plane_Own::Plane_Own()
{
	if (this->getrect() == NULL) this->setrect(200, 400, 50, 50);
}//����

void Plane_Own::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/feijiown.png"));
}//����

void Plane_Own::move(Direction direction,int step)
{
	if (this->getrect()->x() >= 0 && this->getrect()->x() <= 350 && this->getrect()->y() >= 0 && this->getrect()->y() <= 550)
		switch (direction)
		{
		case UP:	this->getrect()->moveTop(this->getrect()->y() - step);	break;
		case DOWN:	this->getrect()->moveTop(this->getrect()->y() + step); break;
		case RIGHT:	this->getrect()->moveLeft(this->getrect()->x() + step); break;
		case LEFT:	this->getrect()->moveLeft(this->getrect()->x() - step); break;
		}
	else
		switch (direction)//��ֹ��ҷɻ��ܳ���Ļ��
		{
		case UP:	this->getrect()->moveTop(2);	break;
		case DOWN:	this->getrect()->moveTop(548); break;
		case RIGHT:	this->getrect()->moveLeft(348); break;
		case LEFT:	this->getrect()->moveLeft(2); break;
		}
}//�ƶ�

//��ͨ�л�����
Plane_Enemy::Plane_Enemy()
{
	if (this->getrect() == NULL) this->setrect(qrand() % 350, -qrand()%50, 50, 50);
}//����

void Plane_Enemy::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/feijienemy.png"));
}//����

//Boss����
Plane_Enemy_Boss::Plane_Enemy_Boss(int hp):HP(hp)
{
	if (this->getrect() == NULL) this->setrect(qrand() % 300, 0, 100, 50);
}//����

void Plane_Enemy_Boss::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/feijiboss.png"));
	if(HP>15&&HP<20)
		painter.drawPixmap(this->getx(),this->gety()-75,100,75, QPixmap("./Resources/tiaoxing1.png"));
	if(HP>6&&HP<14)
		painter.drawPixmap(this->getx(), this->gety() - 75, 100, 75, QPixmap("./Resources/tiaoxing2.png"));
	if(HP<5)
		painter.drawPixmap(this->getx(), this->gety() - 75, 100, 75, QPixmap("./Resources/tiaoxing3.png"));
}//����

bool Plane_Enemy_Boss::HP_cut()
{
	HP--;
	if (HP == 0)	return true;
	else return false;
}//�������٣����ж��Ƿ�����

//�ӻ�����
Plane_Son::Plane_Son(Plane * father, bool left)
{
	if (left == true)
		if (this->getrect() == NULL) this->setrect(father->getx() - 30, father->gety() + 50, 20, 20);
	if (left == false)
		if (this->getrect() == NULL) this->setrect(father->getx() + 60, father->gety() + 50, 20, 20);
}//����

void Plane_Son::display(QPainter & painter)
{
	painter.drawImage(*(this->getrect()), QImage("./Resources/feijiown.png"));
}//����

//�ɻ��鲿��
PlaneGroup::PlaneGroup( PlaneType type, Plane * p)
{
	father = p;
	switch (type)
	{
	case SON:
		break;
	case ENEMY:
		for (int j = 0; j<3; j++)
			for (int i = 0; i<amount; i++)
				if (plane[i] == NULL)
				{
					plane[i] = new Plane_Enemy();
					break;
				}
		break;
	}
}//����

void PlaneGroup::display(QPainter & painter, PlaneType type)
{
	switch (type)
	{
	case SON:
		for (int i = 0; i < 2; i++)
			if (son[i] != NULL)
				son[i]->display(painter);
		break;
	case ENEMY:
		for (int i = 0; i<amount; i++)
			if (plane[i] != NULL)
				plane[i]->display(painter);
		break;
	}
}//����

void PlaneGroup::move(PlaneType type,int step)
{
	switch (type)
	{
	case SON:
		if (son[0] != NULL)	son[0]->setrect(father->getx() - 30, father->gety() + 50, 20, 20);
		if (son[1] != NULL)	son[1]->setrect(father->getx() + 60, father->gety() + 50, 20, 20);

		break;
	case ENEMY:
		for (int i = 0; i < amount; i++)
			if (plane[i] != NULL)
				plane[i]->move(DOWN,step);
		break;
	}
}//�ƶ�

Plane ** PlaneGroup::getplane()
{
	return plane;
}

Plane_Son ** PlaneGroup::getson()
{
	return son;
}

int PlaneGroup::getamount()
{
	return amount;
}//�õ��ɻ�����

bool PlaneGroup::trash()
{
	for (int i = 0; i < amount; i++)
		if (plane[i] != NULL)
			if (plane[i]->trash())	plane[i] = NULL;
	for (int i = 0; i < amount; i++)
		if (plane[i] != NULL)	return false;
	delete this;
	return true;
}//���ɻ���Խ��
