#include "Store.h"

//写文件
void Store::outT(Game1942_Play * GameWidget, QTextStream & out)
{
	out << GameWidget->logic->getscore() << " ";
	out << GameWidget->logic->getlevel() << " ";
	out << GameWidget->logic->getlife() << " ";
	out << GameWidget->logic->getbrave() << " ";//分数、关卡、生命、大招
	out << GameWidget->plane_own->getx() << " ";
	out << GameWidget->plane_own->gety() << " ";//玩家飞机位置
	out << GameWidget->time << endl;//时间进度
	if (GameWidget->plane_son->getson()[0] == NULL) out << 0 << endl;
	else out << 1 << endl;
	if (GameWidget->plane_son->getson()[1] == NULL) out << 0 << endl;
	else out << 1 << endl;//子机状态
	out << GameWidget->logic->gettype() << endl;//子弹类型
	if (GameWidget->item == NULL) out << -1 << endl;
	else
	{
		switch (GameWidget->item->getItemtype())
		{
		case  Pow_blank_addbullet:out << 0 << " "; break;
		case  Pow_red_clearenemy:out << 1 << " "; break;
		case  Pow_white_sonplane:out << 2 << " "; break;
		case  Pow_Brave:out << 3 << " "; break;
		case  Pow_Score_add1000:out << 4 << " "; break;
		case  Pow_HP_add:out << 5 << " "; break;
		}
		out << GameWidget->item->getx() << " " << GameWidget->item->gety() << endl;
	}//奖励

	//飞机
	for (int i = 0; i < BOSS_PLANE_AMOUNT; i++)
		if (GameWidget->plane_enemy_boss[i] == NULL)
			out << 0 << endl;
		else out << 1 << " " << GameWidget->plane_enemy_boss[i]->getx()
			<< " " << GameWidget->plane_enemy_boss[i]->gety() 
			<<" " << GameWidget->plane_enemy_boss[i]->getrect()->width()
			<<" " << GameWidget->plane_enemy_boss[i]->getrect()->height()<< endl;

	for (int i = 0; i < SIMPLE_PLANE_AMOUNT; i++)
		if (GameWidget->plane_enemy_simple[i] == NULL) out << 0 << endl;
		else
		{
			out << 1 << " ";
			for (int j = 0; j < GameWidget->plane_enemy_simple[i]->getamount(); j++)
				if (GameWidget->plane_enemy_simple[i]->getplane()[j] == NULL)	out << 0 << " ";
				else out << 1 << " " << GameWidget->plane_enemy_simple[i]->getplane()[j]->getx()
					<< " " << GameWidget->plane_enemy_simple[i]->getplane()[j]->gety() << endl;
		}

	//子弹
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
		if (GameWidget->bullet_enemy[i] == NULL) out << 0 << endl;
		else
		{
			out << 1 << " ";
			for (int j = 0; j < GameWidget->bullet_enemy[i]->getamount(); j++)
				if (GameWidget->bullet_enemy[i]->getbullet()[j] == NULL)	out << 0 << endl;
				else out << 1 << " " << GameWidget->bullet_enemy[i]->getbullet()[j]->getx()
					<< " " << GameWidget->bullet_enemy[i]->getbullet()[j]->gety() << endl;
		}

	for (int i = 0; i < OWN_BULLET_AMOUNT; i++)
		if (GameWidget->bullet_own[i] == NULL) out << 0 << endl;
		else
		{
			out << 1 << " ";
			for (int j = 0; j < GameWidget->bullet_own[i]->getamount(); j++)
				if (GameWidget->bullet_own[i]->getbullet()[j] == NULL)	out << 0 << endl;
				else out << 1 << " " << GameWidget->bullet_own[i]->getbullet()[j]->getx()
					<< " " << GameWidget->bullet_own[i]->getbullet()[j]->gety() << endl;
		}


}

//读文件
void Store::inT(Game1942_Play * GameWidget, QTextStream & in)
{
	int x;
	in >> x; GameWidget->logic->setscore(x);
	in >> x; GameWidget->logic->setlevel(x);
	in >> x; GameWidget->logic->setlife(x);
	in >> x; GameWidget->logic->setbrave(x);//分数、关卡、生命、大招
	in >> x; GameWidget->plane_own->getrect()->setX(x);
	in >> x; GameWidget->plane_own->getrect()->setY(x);
	GameWidget->plane_own->getrect()->setWidth(50);
	GameWidget->plane_own->getrect()->setHeight(50);//玩家飞机位置
	in >> x; GameWidget->progressbar->setValue(x);//进度条
	in >> x; if (x == 1)
		GameWidget->plane_son->getson()[0] = new Plane_Son(GameWidget->plane_own, true);
			else if (GameWidget->plane_son->getson()[0] != NULL)
			{
				delete GameWidget->plane_son->getson()[0];
				GameWidget->plane_son->getson()[0] = NULL;
			}
	in >> x; if (x == 1)
		GameWidget->plane_son->getson()[1] = new Plane_Son(GameWidget->plane_own, false);
			else if (GameWidget->plane_son->getson()[1] != NULL)
			{
				delete GameWidget->plane_son->getson()[1];
				GameWidget->plane_son->getson()[1] = NULL;
			}//子机
	in >> x; if (x == 1)
		GameWidget->logic->settype(two);
			if (x == 2)
		GameWidget->logic->settype(three_open);//子弹类型
	in >> x;
	if (x != -1)
	{
		switch (x)
		{
		case 0:GameWidget->item= new Item(Pow_blank_addbullet); break;
		case 1:GameWidget->item = new Item(Pow_red_clearenemy); break;
		case 2:GameWidget->item = new Item(Pow_white_sonplane); break;
		case 3:GameWidget->item = new Item(Pow_Brave); break;
		case 4:GameWidget->item = new Item(Pow_Score_add1000); break;
		case 5:GameWidget->item = new Item(Pow_HP_add); break;
		}
		int y;
		in >> x;
		in >> y;
		GameWidget->item->setrect(x, y, 20, 20);
	}
	else 
	{
		delete GameWidget->item;
		GameWidget->item = NULL;
	}//奖励

	//飞机
	for (int i = 0; i < BOSS_PLANE_AMOUNT; i++)
	{
		in >> x;
		if (x == 1)
		{
			GameWidget->plane_enemy_boss[i] = new Plane_Enemy_Boss(20);
			int y;
			int w;
			int h;
			in >> x >> y>>w>>h;
			GameWidget->plane_enemy_boss[i]->setrect(x, y, w, h);
		}
		else
		{
			if (GameWidget->plane_enemy_boss[i] != NULL)
			{
				delete GameWidget->plane_enemy_boss[i];
				GameWidget->plane_enemy_boss[i] = NULL;
			}
		}
	}


	for (int i = 0; i < SIMPLE_PLANE_AMOUNT; i++)
	{
		in >> x;
		if (x == 1)
		{
			GameWidget->plane_enemy_simple[i] = new PlaneGroup(ENEMY);
			for (int j = 0; j < GameWidget->plane_enemy_simple[i]->getamount(); j++)
			{
				in >> x;
				if (x == 1)
				{
					GameWidget->plane_enemy_simple[i]->getplane()[j] = new Plane_Enemy();
					int y;
					in >> x >> y;
					GameWidget->plane_enemy_simple[i]->getplane()[j]->setrect(x, y, 50, 50);
				}
				else
				{
					if (GameWidget->plane_enemy_simple[i]->getplane()[j] != NULL)
					{
						delete GameWidget->plane_enemy_simple[i]->getplane()[j];
						GameWidget->plane_enemy_simple[i]->getplane()[j] = NULL;
					}
				}
			}
		}
		else
		{
			if (GameWidget->plane_enemy_simple[i] != NULL)
			{
				delete GameWidget->plane_enemy_simple[i];
				GameWidget->plane_enemy_simple[i] = NULL;
			}
		}

	}

	//子弹
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{
		in >> x;
		if (x == 1)
		{
			GameWidget->bullet_enemy[i] = new BulletGroup();
			for (int j = 0; j < GameWidget->bullet_enemy[i]->getamount(); j++)
			{
				in >> x;
				if (x == 1)
				{
					GameWidget->bullet_enemy[i]->getbullet()[j] = new Bullet();
					int y;
					in >> x >> y;
					GameWidget->bullet_enemy[i]->getbullet()[j]->setrect(x, y, 10, 10);
				}
				else
				{
					if (GameWidget->bullet_enemy[i]->getbullet()[j] != NULL)
					{
						delete GameWidget->bullet_enemy[i]->getbullet()[j];
						GameWidget->bullet_enemy[i]->getbullet()[j] = NULL;
					}
				}

			}
		}
		else
		{
			if (GameWidget->bullet_enemy[i] != NULL)
			{
				delete GameWidget->bullet_enemy[i];
				GameWidget->bullet_enemy[i] = NULL;
			}
		}

	}

	for (int i = 0; i < OWN_BULLET_AMOUNT; i++)
	{
		in >> x;
		if (x == 1)
		{
			GameWidget->bullet_own[i] = new BulletGroup();
			for (int j = 0; j < GameWidget->bullet_own[i]->getamount(); j++)
			{
				in >> x;
				if (x == 1)
				{
					GameWidget->bullet_own[i]->getbullet()[j] = new Bullet_Own();
					int y;
					in >> x >> y;
					GameWidget->bullet_own[i]->getbullet()[j]->setrect(x, y, 5, 10);
				}
				else
				{
					if (GameWidget->bullet_own[i]->getbullet()[j] != NULL)
					{
						delete GameWidget->bullet_own[i]->getbullet()[j];
						GameWidget->bullet_own[i]->getbullet()[j] = NULL;
					}
				}

			}
		}
		else
		{
			if (GameWidget->bullet_own[i] != NULL)
			{
				delete GameWidget->bullet_own[i];
				GameWidget->bullet_own[i] = NULL;
			}
		}

	}

}

//写录像
void Store::videowrite(Game1942_Play * GameWidget)
{
	GameWidget->file->open(QIODevice::Text | QIODevice::Append);
	QTextStream out(GameWidget->file);
	out << 'a';//一帧开始标志
	outT(GameWidget, out);
	GameWidget->file->close();

}

//读录像
bool Store::videoread(Game1942_Play * GameWidget, QTextStream &in)
{
	char start;
	in >> start;
	if (start == '\n')	in >> start;//跳过空行
	if (start == 'a')
	{
		inT(GameWidget, in);

		GameWidget->pause = 1;
		GameWidget->update();
		return false;
	}
	else
	{
		GameWidget->returnback();
		return true;
	}
}

//储存游戏
void Store::save(Game1942_Play *GameWidget)
{
	QFile *file = new QFile;
	file->setFileName("store");
	bool ok = file->open(QIODevice::Text | QIODevice::WriteOnly);
	if (ok)
	{
		QTextStream out(file);
		outT(GameWidget, out);
		file->close();
		delete(file);
		QMessageBox::information(GameWidget, "Tip", "Save Successfully");
	}
	else
	{
		QMessageBox::information(GameWidget, "ErrorBox", "File fail to save");
	}
}

//读档游戏
void Store::read(Game1942_Play *GameWidget)
{
	QFile *file = new QFile;
	file->setFileName("store");
	bool ok = file->open(QIODevice::Text | QIODevice::ReadOnly);
	if (ok)
	{
		QTextStream in(file);
		inT(GameWidget, in);
		GameWidget->pause = 1;
		file->close();
		delete(file);
	}
	else
	{
		QMessageBox::information(GameWidget, "ErrorBox", "File fail to read");
	}
}
