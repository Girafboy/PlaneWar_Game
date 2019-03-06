#include "Logic.h"

//获得分数、关卡、生命、大招
int Logic::getscore()
{
	return score;
}

int Logic::getlevel()
{
	return level;
}

int Logic::getlife()
{
	return life;
}

int Logic::getbrave()
{
	return brave;
}

//设置分数、关卡、生命、大招
void Logic::setscore(int x)
{
	score = x;
}

void Logic::setlevel(int x)
{
	level = x;
}

void Logic::setlife(int x)
{
	life = x;
}

void Logic::setbrave(int x)
{
	brave = x;
}

//分数+1
void Logic::scoreadd()
{
	score += 50;
}

//关卡+1
void Logic::leveladd()
{
	level++;
}

//生命+1
void Logic::lifeadd()
{
	life++;
}

//生命-1
void Logic::lifesub()
{
	life--;
}

//大招+1
void Logic::braveadd()
{
	brave++;
}

//大招-1
void Logic::bravesub()
{
	brave--;
}

//获得子弹类型
BulletType Logic::gettype()
{
	return btype;
}

//设置子弹类型
void Logic::settype(BulletType type)
{
	btype = type;
}

//清除所有普通敌人
void Logic::clearenemy(PlaneGroup **p, BulletGroup **b)
{
	for (int i = 0; i < SIMPLE_PLANE_AMOUNT; i++)
		if (p[i] != NULL)
			for (int j = 0; j < p[i]->getamount(); j++)
				if (p[i]->getplane()[j] != NULL)
				{
					delete p[i]->getplane()[j];
					p[i]->getplane()[j] = NULL;
				}
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
		if (b[i] != NULL)
			for (int j = 0; j < b[i]->getamount(); j++)
				if (b[i]->getbullet()[j] != NULL)
				{
					delete b[i]->getbullet()[j];
					b[i]->getbullet()[j] = NULL;
				}
}

//检测不同物体碰撞
bool Logic::isCollision(Object * p, Object * b)
{
	if (((p->getx() + p->getrect()->width()) > b->getx())
		&& ((b->getx() + b->getrect()->width()) > p->getx())
		&& ((p->gety() + p->getrect()->height()) > b->gety())
		&& ((b->gety() + b->getrect()->height()) > p->gety()))
		return true;
	else
		return false;
}

bool Logic::isCollision(PlaneGroup * p, Object * b)
{
	for (int i = 0; i < p->getamount(); i++)
		if (p->getplane()[i] != NULL && b != NULL)
			if (isCollision(p->getplane()[i], b))
			{
				p->getplane()[i]->disappear();
				p->getplane()[i] = NULL;
				return true;
			}
	return false;
}

bool Logic::isCollision(Object * p, BulletGroup * b)
{
	for (int i = 0; i < b->getamount(); i++)
		if ((b->getbullet()[i] != NULL) && (p != NULL))
			if (isCollision(b->getbullet()[i], p))
			{
				b->getbullet()[i]->disappear();
				b->getbullet()[i] = NULL;
				return true;
			}
	return false;
}

bool Logic::isCollision(PlaneGroup * p, PlaneGroup * b)
{
	for (int i = 0; i < p->getamount(); i++)
		for (int j = 0; j < 2; j++)
			if (p->getplane()[i] != NULL && b->getson()[j] != NULL)
				if (isCollision(p->getplane()[i], b->getson()[j]))
				{
					p->getplane()[i]->disappear();
					p->getplane()[i] = NULL;
					b->getson()[j]->disappear();
					b->getson()[j] = NULL;
					return true;
				}
	for (int i = 0; i < b->getamount(); i++)
		for (int j = 0; j < 2; j++)
			if (b->getplane()[i] != NULL && p->getson()[j] != NULL)
				if (isCollision(b->getplane()[i], p->getson()[j]))
				{
					b->getplane()[i]->disappear();
					b->getplane()[i] = NULL;
					p->getson()[j]->disappear();
					p->getson()[j] = NULL;
					return true;
				}
	return false;
}

bool Logic::isCollision(PlaneGroup * p, BulletGroup * b)
{
	for (int j = 0; j < p->getamount(); j++)
		for (int i = 0; i < b->getamount(); i++)
			if ((b->getbullet()[i] != NULL) && (p->getplane()[j] != NULL))
				if (isCollision(b->getbullet()[i], p->getplane()[j]))
				{
					b->getbullet()[i]->disappear();
					b->getbullet()[i] = NULL;
					p->getplane()[j]->disappear();
					p->getplane()[j] = NULL;
					scoreadd();
				}
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < b->getamount(); i++)
			if ((b->getbullet()[i] != NULL) && (p->getson()[j] != NULL))
				if (isCollision(b->getbullet()[i], p->getson()[j]))
				{
					b->getbullet()[i]->disappear();
					b->getbullet()[i] = NULL;
					p->getson()[j]->disappear();
					p->getson()[j] = NULL;
					return true;
				}
	return false;
}

//检测整个画面实体群碰撞
void Logic::doCollision(BulletGroup ** bown, BulletGroup ** benemy, Plane_Own * pown,
	PlaneGroup * son, PlaneGroup ** penemy, Plane_Enemy_Boss ** boss,Item* &it)
{
	for (int i = 0; i < OWN_BULLET_AMOUNT; i++)//己方子弹和敌机碰撞
		for (int j = 0; j < SIMPLE_PLANE_AMOUNT; j++)
			if (bown[i] != NULL && penemy[j] != NULL)
				isCollision(penemy[j], bown[i]);

	for (int i = 0; i < OWN_BULLET_AMOUNT; i++)//己方子弹和Boss碰撞
		for (int j = 0; j < BOSS_PLANE_AMOUNT; j++)
			if (bown[i] != NULL && boss[j] != NULL)
				if (isCollision(boss[j], bown[i]))
				{
					boss[j]->setrect(boss[j]->getx() - 1, boss[j]->gety() - 1, boss[j]->getrect()->width() + 2, boss[j]->getrect()->height() + 2);
					if (boss[j]->HP_cut())
					{
						if (it == NULL) it = new Item(boss[j]);//释放奖励
						boss[j]->disappear();
						boss[j] = NULL;
						scoreadd();
						scoreadd();
					}
				}

	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)//敌机子弹和自己碰撞
		if (benemy[i] != NULL)
			if (isCollision(pown, benemy[i]))
				lifesub();

	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)//敌机子弹和子机碰撞
		for (int j = 0; j < 2; j++)
			if (benemy[i] != NULL && son != NULL)
				isCollision(son, benemy[i]);

	for (int i = 0; i < SIMPLE_PLANE_AMOUNT; i++)//敌机和子机碰撞
		for (int j = 0; j < 2; j++)
			if (penemy[i] != NULL && son != NULL)
				if(isCollision(penemy[i], son))
					scoreadd();

	for (int i = 0; i < SIMPLE_PLANE_AMOUNT; i++)//敌机和自己碰撞
		if (penemy[i] != NULL)
			if (isCollision(penemy[i],pown))
				lifesub();
	if (it!=NULL)//检测拾取奖励
		if (isCollision(it, pown))
		{
			switch (it->getItemtype())
			{
			case Pow_blank_addbullet:
				if (btype == two) btype = three_open;
				if (btype == one) btype = two;
				break;
			case Pow_red_clearenemy:
				clearenemy(penemy,benemy);
				break;
			case Pow_white_sonplane:
				if (son->getson()[0] == NULL)	son->getson()[0] = new Plane_Son(pown, true);
				else if(son->getson()[1] == NULL)	son->getson()[1] = new Plane_Son(pown, false);
				break;
			case Pow_Brave:
				braveadd();
				break;
			case Pow_Score_add1000:
				for (int i = 0; i < 20; i++) scoreadd();
				break;
			case Pow_HP_add:
				lifeadd();
				break;
			}
			delete it;
			it = NULL;
		}
}


