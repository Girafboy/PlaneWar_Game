#pragma once

#include "Logic.h"
#include "Store.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qprogressbar.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qtimer.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qpushbutton.h>


//游戏窗口
class Game1942_Play : public QWidget
{
	friend class Store;
	Q_OBJECT
		
public:
	Game1942_Play(QWidget *parent = Q_NULLPTR,bool read=0);
	bool open=1;//标志游戏窗口是否关闭
private slots:
	void timercontrol_videowrite();
	void timercontrol_level();
	void timercontrol_move();
	void timercontrol_bulletown();
	void timercontrol_bulletson();
	void timercontrol_planesimple();
	void timercontrol_planesimplebullet();
	void timercontrol_planeboss();
	void timercontrol_planebossbullet();//计时器槽函数
	void storegame();//游戏存档
	void returnback();//返回主窗口
private:
	QFile *file;//文件流
	Logic *logic;//逻辑
	QLabel *score_label;
	QLabel *level_label;
	QLabel *life_label;
	QLabel *brave_label;
	QLineEdit *score_lineEdit;
	QLineEdit *level_lineEdit;
	QLineEdit *life_lineEdit;
	QLineEdit *brave_lineEdit;//标签和编辑框
	QProgressBar *progressbar;//进度条
	QPushButton *store;
	QPushButton *video;
	QPushButton *exitgame;//按钮
	Plane_Own *plane_own;
	PlaneGroup *plane_son;
	PlaneGroup *plane_enemy_simple[SIMPLE_PLANE_AMOUNT] = { NULL };
	Plane_Enemy_Boss *plane_enemy_boss[BOSS_PLANE_AMOUNT] = { NULL };
	BulletGroup *bullet_own[OWN_BULLET_AMOUNT] = { NULL };
	BulletGroup *bullet_enemy[ENEMY_BULLET_AMOUNT] = { NULL };
	Item *item= NULL;//飞机、子弹、奖励等

	QTimer *timer_video=NULL;
	QTimer *timer_level = NULL;
	QTimer *timer_move = NULL;
	QTimer *timer_bulletown = NULL;
	QTimer *timer_bulletson = NULL;
	QTimer *timer_enemy = NULL;
	QTimer *timer_bulletenemy = NULL;
	QTimer *timer_boss = NULL;
	QTimer *timer_bulletboss = NULL;//计时器
	int time=100;//进度条数值
	bool pause=0;//游戏暂停

	void paintEvent(QPaintEvent *event);//绘图事件
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);//键盘事件
	void mouseMoveEvent(QMouseEvent *event);//鼠标跟踪事件
};