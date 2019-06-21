#pragma once

#include <qrect.h>
#include <qpainter.h>
#include <cmath>

enum Direction { UP, DOWN, RIGHT, LEFT };//�ƶ�����

//����ʵ����
class Object
{
private:
	QRect *rect=NULL;
public:
	void move(Direction direction,int step);
	void move(Object* o, int step);//�ƶ�
	virtual void display(QPainter &painter)=0;//����
	void disappear();//��ʧ����
	bool trash();//���Խ��
	int getx();
	int gety();
	QRect* getrect();
	void setrect(int x,int y,int wide,int height);//λ�ô�С
};
