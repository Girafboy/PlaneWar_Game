#pragma once

#include <qfile.h>
#include "Game1942_Play.h"
#include <qtextstream.h>

class Game1942_Play;

class Store
{
private:
	static void outT(Game1942_Play *GameWidget, QTextStream &out);//д�ļ�
	static void inT(Game1942_Play *GameWidget, QTextStream &in);//���ļ�
public:
	static void videowrite(Game1942_Play *GameWidget);//¼��
	static bool videoread(Game1942_Play *GameWidget,QTextStream &in);//�ط�
	static void save(Game1942_Play *GameWidget);//�浵
	static void read(Game1942_Play *GameWidget);//����
};

