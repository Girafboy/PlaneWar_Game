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


//��Ϸ����
class Game1942_Play : public QWidget
{
	friend class Store;
	Q_OBJECT
		
public:
	Game1942_Play(QWidget *parent = Q_NULLPTR,bool read=0);
	bool open=1;//��־��Ϸ�����Ƿ�ر�
private slots:
	void timercontrol_videowrite();
	void timercontrol_level();
	void timercontrol_move();
	void timercontrol_bulletown();
	void timercontrol_bulletson();
	void timercontrol_planesimple();
	void timercontrol_planesimplebullet();
	void timercontrol_planeboss();
	void timercontrol_planebossbullet();//��ʱ���ۺ���
	void storegame();//��Ϸ�浵
	void returnback();//����������
private:
	QFile *file;//�ļ���
	Logic *logic;//�߼�
	QLabel *score_label;
	QLabel *level_label;
	QLabel *life_label;
	QLabel *brave_label;
	QLineEdit *score_lineEdit;
	QLineEdit *level_lineEdit;
	QLineEdit *life_lineEdit;
	QLineEdit *brave_lineEdit;//��ǩ�ͱ༭��
	QProgressBar *progressbar;//������
	QPushButton *store;
	QPushButton *video;
	QPushButton *exitgame;//��ť
	Plane_Own *plane_own;
	PlaneGroup *plane_son;
	PlaneGroup *plane_enemy_simple[SIMPLE_PLANE_AMOUNT] = { NULL };
	Plane_Enemy_Boss *plane_enemy_boss[BOSS_PLANE_AMOUNT] = { NULL };
	BulletGroup *bullet_own[OWN_BULLET_AMOUNT] = { NULL };
	BulletGroup *bullet_enemy[ENEMY_BULLET_AMOUNT] = { NULL };
	Item *item= NULL;//�ɻ����ӵ���������

	QTimer *timer_video=NULL;
	QTimer *timer_level = NULL;
	QTimer *timer_move = NULL;
	QTimer *timer_bulletown = NULL;
	QTimer *timer_bulletson = NULL;
	QTimer *timer_enemy = NULL;
	QTimer *timer_bulletenemy = NULL;
	QTimer *timer_boss = NULL;
	QTimer *timer_bulletboss = NULL;//��ʱ��
	int time=100;//��������ֵ
	bool pause=0;//��Ϸ��ͣ

	void paintEvent(QPaintEvent *event);//��ͼ�¼�
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);//�����¼�
	void mouseMoveEvent(QMouseEvent *event);//�������¼�
};