#pragma once

#include "Plane.h"

enum ItemType{Pow_blank_addbullet, Pow_red_clearenemy, Pow_white_sonplane,
	Pow_Brave, Pow_Score_add1000, Pow_HP_add};//奖励的类型

//奖励类
class Item : public Object
{
private:
	ItemType type;
public:
	Item(ItemType t);
	Item(Plane_Enemy_Boss* boss);
	void display(QPainter &painter);
	ItemType getItemtype();
};
