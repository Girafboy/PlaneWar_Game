#include "Object.h"

//���������ƶ�
void Object::move(Direction direction,int step)
{
	switch (direction)
	{
	case UP:	rect->moveTop(rect->y() - step);	break;
	case DOWN:	rect->moveTop(rect->y() + step); break;
	case RIGHT:	rect->moveLeft(rect->x() + step); break;
	case LEFT:	rect->moveLeft(rect->x() - step); break;
	}
}

void Object::move(Object * o, int step)
{
	int dx = rect->x() - o->rect->x();
	int dy = rect->y() - o->rect->y();
	int d = sqrt(dx*dx + dy*dy);
	if (rect->y()< 350 && dy < 0)
	{
		int stepx = step * dx / d;
		int stepy = step * dy / d;
		this->move(LEFT, stepx);
		this->move(UP, stepy);
	}
	else
		this->move(DOWN, 5);
}

//��ʧ����
void Object::disappear()
{
	delete this;
}

//�������Խ������
bool Object::trash()
{
	if ((this->gety() < -100 )|| (this->gety() > 700))
	{
		delete this;
		return true;
	}
	else
		return false;
}

//��������x����
int Object::getx()
{
	return rect->x();
}

//��������y����
int Object::gety()
{
	return rect->y();
}

//����������
QRect* Object::getrect()
{
	return rect;
}

//�����������
void Object::setrect(int x, int y, int wide, int height)
{
	rect = new QRect(x, y, wide, height);
}

