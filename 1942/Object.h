#pragma once

#include <qrect.h>
#include <qpainter.h>
#include <cmath>

enum Direction { UP, DOWN, RIGHT, LEFT };//移动方向

//抽象实体类
class Object
{
private:
	QRect *rect=NULL;
public:
	void move(Direction direction,int step);
	void move(Object* o, int step);//移动
	virtual void display(QPainter &painter)=0;//绘制
	void disappear();//消失物体
	bool trash();//检测越界
	int getx();
	int gety();
	QRect* getrect();
	void setrect(int x,int y,int wide,int height);//位置大小
};
