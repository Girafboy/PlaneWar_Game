#pragma once

#include <qfile.h>
#include "Game1942_Play.h"
#include <qtextstream.h>

class Game1942_Play;

class Store
{
private:
	static void outT(Game1942_Play *GameWidget, QTextStream &out);//写文件
	static void inT(Game1942_Play *GameWidget, QTextStream &in);//读文件
public:
	static void videowrite(Game1942_Play *GameWidget);//录像
	static bool videoread(Game1942_Play *GameWidget,QTextStream &in);//回放
	static void save(Game1942_Play *GameWidget);//存档
	static void read(Game1942_Play *GameWidget);//读档
};

