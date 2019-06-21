#include "Object.h"

//控制物体移动
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

//消失物体
void Object::disappear()
{
	delete this;
}

//检查消除越界物体
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

//获得物体的x坐标
int Object::getx()
{
	return rect->x();
}

//获得物体的y坐标
int Object::gety()
{
	return rect->y();
}

//获得物体矩形
QRect* Object::getrect()
{
	return rect;
}

//设置物体矩形
void Object::setrect(int x, int y, int wide, int height)
{
	rect = new QRect(x, y, wide, height);
}

