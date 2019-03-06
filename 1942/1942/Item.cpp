#include "Item.h"
#include "qmessagebox.h"

//���캯��
Item::Item(ItemType t)
{
	type = t;
}

Item::Item(Plane_Enemy_Boss * boss)
{
	switch (qrand()%6)
	{
	case 0:type = Pow_blank_addbullet; break;
	case 1:type = Pow_red_clearenemy; break;
	case 2:type = Pow_white_sonplane; break;
	case 3:type = Pow_Brave; break;
	case 4:type = Pow_Score_add1000; break;
	case 5:type = Pow_HP_add; break;
	}
	this->setrect(boss->getrect()->center().x(), boss->getrect()->center().y(),20,20);
}

//��������
void Item::display(QPainter & painter)
{
	switch (type)
	{
	case Pow_blank_addbullet:	
		painter.drawImage(*(this->getrect()), QImage("./Resources/jiazidan.jpg"));//�ӵ���ǿ
		break;
	case Pow_red_clearenemy:
		painter.drawImage(*(this->getrect()), QImage("./Resources/cleardijun.jpg"));//�������
		break;
	case Pow_white_sonplane:
		painter.drawImage(*(this->getrect()), QImage("./Resources/jiaziji.jpg"));//�����ӻ�
		break;
	case Pow_Brave:
		painter.drawImage(*(this->getrect()), QImage("./Resources/jiapower.jpg"));//���Ӵ���
		break;
	case Pow_Score_add1000:
		painter.drawImage(*(this->getrect()), QImage("./Resources/jiafen.jpg"));//��1000��
		break;
	case Pow_HP_add:
		painter.drawImage(*(this->getrect()), QImage("./Resources/jiaming.jpg"));//��������
		break;
	}
}

//��ý�������
ItemType Item::getItemtype()
{
	return type;
}
