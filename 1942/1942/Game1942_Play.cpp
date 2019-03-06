#include <Game1942_Play.h>

//游戏窗口
Game1942_Play::Game1942_Play(QWidget *parent,bool read)
	:QWidget(parent)
{
	//设置窗口
	this->setAutoFillBackground(true);
	this->resize(400, 600);

	//逻辑初始化
	logic = new Logic();

	//存档按钮
	store = new QPushButton(this);
	store->setIcon(QIcon("./Resources/baocun.png"));
	store->setIconSize(QSize(30, 30));
	store->setGeometry(QRect(360, 15, 30, 30));
	store->setFlat(true);
	connect(store, SIGNAL(clicked(bool)), this, SLOT(storegame()));

	//录像按钮
	video = new QPushButton(this);
	video->setIcon(QIcon("./Resources/luxiang.png"));
	video->setIconSize(QSize(30, 30));
	video->setGeometry(QRect(360, 50, 30, 30));
	video->setFlat(true);
	connect(video, SIGNAL(clicked(bool)), this, SLOT(timercontrol_videowrite()));

	//退出游戏按钮
	exitgame = new QPushButton(this);
	exitgame->setIcon(QIcon("./Resources/tuichu.png"));
	exitgame->setIconSize(QSize(30, 30));
	exitgame->setGeometry(QRect(360, 85, 30, 30));
	exitgame->setFlat(true);
	connect(exitgame, SIGNAL(clicked(bool)), this, SLOT(returnback()));

	//分数、关卡、生命、无敌标签
	QFont ft("Microsoft YaHei", 14, 75);
	QPalette pa;
	pa.setColor(QPalette::Text, Qt::white);
	pa.setColor(QPalette::WindowText, Qt::white);
	score_label = new QLabel("Score:", this);
	score_label->setGeometry(50, 30, 100, 30);
	score_label->setFont(ft);
	score_label->setPalette(pa);
	score_lineEdit = new QLineEdit(this);
	score_lineEdit->setGeometry(130, 30, 70, 30);
	score_lineEdit->setFont(ft);
	score_lineEdit->setPalette(pa);
	score_lineEdit->setReadOnly(true);
	score_lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	level_label = new QLabel("Level:", this);
	level_label->setGeometry(250, 30, 100, 30);
	level_label->setFont(ft);
	level_label->setPalette(pa);
	level_lineEdit = new QLineEdit(this);
	level_lineEdit->setGeometry(340, 30, 40, 30);
	level_lineEdit->setFont(ft);
	level_lineEdit->setPalette(pa);
	level_lineEdit->setReadOnly(true);
	level_lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	life_label = new QLabel("Life:       x", this);
	life_label->setGeometry(50, 550, 100, 30);
	life_label->setFont(ft);
	life_label->setPalette(pa);
	life_lineEdit = new QLineEdit(this);
	life_lineEdit->setGeometry(150, 550, 50, 30);
	life_lineEdit->setFont(ft);
	life_lineEdit->setPalette(pa);
	life_lineEdit->setReadOnly(true);
	life_lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	brave_label = new QLabel("Brave:    x", this);
	brave_label->setGeometry(250, 550, 100, 30);
	brave_label->setFont(ft);
	brave_label->setPalette(pa);
	brave_lineEdit = new QLineEdit(this);
	brave_lineEdit->setGeometry(350, 550, 50, 30);
	brave_lineEdit->setFont(ft);
	brave_lineEdit->setPalette(pa);
	brave_lineEdit->setReadOnly(true);
	brave_lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");

	//进度条
	progressbar = new QProgressBar(this);
	progressbar->setGeometry(20, 20, 345, 10);
	progressbar->setStyleSheet("/QProgressBar::chunk{ background - color: #CD96CD; width: 10px; margin: 0.5px }");
	progressbar->setRange(0, 100);
	progressbar->setValue(100);

	//初始化己方飞机
	plane_own = new Plane_Own();
	plane_son = new PlaneGroup( SON, plane_own);

	pause = 1;//暂停
	//计时器
	if (!read)
	{
		file = new QFile();
		file->setFileName("video");
		timer_video = new QTimer(this);//录像
		connect(timer_video, SIGNAL(timeout()), this, SLOT(timercontrol_videowrite()));

		timer_level = new QTimer(this);//进度条
		connect(timer_level, SIGNAL(timeout()), this, SLOT(timercontrol_level()));
		timer_level->start(200);

		timer_move = new QTimer(this);//移动
		connect(timer_move, SIGNAL(timeout()), this, SLOT(timercontrol_move()));
		timer_move->start(20);

		timer_bulletown = new QTimer(this);//己方子弹
		connect(timer_bulletown, SIGNAL(timeout()), this, SLOT(timercontrol_bulletown()));

		timer_bulletson = new QTimer(this);//子机子弹
		connect(timer_bulletson, SIGNAL(timeout()), this, SLOT(timercontrol_bulletson()));
		timer_bulletson->start(200);

		timer_enemy = new QTimer(this);//简单敌机
		connect(timer_enemy, SIGNAL(timeout()), this, SLOT(timercontrol_planesimple()));
		timer_enemy->start(5000 / logic->getlevel());

		timer_bulletenemy = new QTimer(this);//简单敌机子弹
		connect(timer_bulletenemy, SIGNAL(timeout()), this, SLOT(timercontrol_planesimplebullet()));
		timer_bulletenemy->start(4000);

		timer_boss = new QTimer(this);//Boss
		connect(timer_boss, SIGNAL(timeout()), this, SLOT(timercontrol_planeboss()));
		timer_boss->start(20000 / logic->getlevel());

		timer_bulletboss = new QTimer(this);//Boss子弹
		connect(timer_bulletboss, SIGNAL(timeout()), this, SLOT(timercontrol_planebossbullet()));
		timer_bulletboss->start(5000);

		setMouseTracking(true);  //设置鼠标追踪
		setFocus();//设置键盘焦点
		pause = 0;//取消暂停
	}
}

//绘图事件
void Game1942_Play::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	//绘制数据
	score_lineEdit->setText(QString::number(logic->getscore()));
	level_lineEdit->setText(QString::number(logic->getlevel()));
	life_lineEdit->setText(QString::number(logic->getlife()));
	brave_lineEdit->setText(QString::number(logic->getbrave()));

	//判断碰撞
	if(!pause)
	logic->doCollision(bullet_own, bullet_enemy, plane_own, plane_son,
		plane_enemy_simple, plane_enemy_boss,item);

	//画工具包
	if (item != NULL)
	{
		item->display(painter);
		if (item->trash())	item = NULL;
	}

	//画己方飞机
	plane_own->display(painter);
	plane_son->display(painter, SON);

	//画己方子弹
	for (int i = 0; i < OWN_BULLET_AMOUNT; i++)
		if (bullet_own[i] != NULL)
		{
			bullet_own[i]->display(painter);
			if (bullet_own[i]->trash()) bullet_own[i] = NULL;
		}

	//画简单敌机
	for (int i = 0; i <SIMPLE_PLANE_AMOUNT; i++)
		if (plane_enemy_simple[i] != NULL)
		{
			plane_enemy_simple[i]->display(painter, ENEMY);
			if (plane_enemy_simple[i]->trash())	plane_enemy_simple[i] = NULL;
		}

	//画Boss
	for (int i = 0; i <BOSS_PLANE_AMOUNT; i++)
		if (plane_enemy_boss[i] != NULL)
		{
			plane_enemy_boss[i]->display(painter);
			if (plane_enemy_boss[i]->trash())	plane_enemy_boss[i] = NULL;
		}

	//画敌机子弹
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
		if (bullet_enemy[i] != NULL)
		{
			bullet_enemy[i]->display(painter);
			if (bullet_enemy[i]->trash()) bullet_enemy[i] = NULL;
		}

	//游戏是否结束
	if (logic->getlife() <= 0)//失败
	{
		returnback();
		QMessageBox::warning(this, "Game Over!", tr("Your score :%1").arg(logic->getscore()), QMessageBox::Ok);
	}
	if (logic->getlevel() > 17)//胜利
	{
		QFile *f = new QFile();
		f->setFileName("score");
		f->open(QIODevice::Text | QIODevice::ReadOnly);
		QTextStream in(f);
		int x;
		in >> x;
		f->close();//写入分数

		returnback();
		if(x>=logic->getscore())
			QMessageBox::information(this, "Congratulation!", tr("You Win!   Your score : %1   The Highest Score of History : %2").arg(logic->getscore()).arg(x), QMessageBox::Ok);
		else
		{
			f->open(QIODevice::Text | QIODevice::WriteOnly);
			QTextStream out(f);
			out << logic->getscore();
			f->close();
			QMessageBox::information(this, "Congratulation!", tr("You Win!   Refresh Record!   Your score : %1").arg(logic->getscore()), QMessageBox::Ok);
		}//刷新纪录
	}

}

//键盘事件
void Game1942_Play::keyPressEvent(QKeyEvent * event) 
{
	switch (event->key()) 
	{
	case Qt::Key_W:	 plane_own->move(UP,10);	plane_son->move(SON,10);	break;//上
	case Qt::Key_S:	 plane_own->move(DOWN,10);	plane_son->move(SON,10);	break;//下
	case Qt::Key_D:  plane_own->move(RIGHT,10); plane_son->move(SON,10);	break;//左
	case Qt::Key_A:	 plane_own->move(LEFT,10);	plane_son->move(SON,10);	break;//右
	case Qt::Key_J:
		if(!event->isAutoRepeat())
			timer_bulletown->start(150);
		break;//普通攻击
	case Qt::Key_K:	
		if (!event->isAutoRepeat())
			if (logic->getbrave() >0)
			{
				logic->bravesub();
				logic->clearenemy(plane_enemy_simple,bullet_enemy);
			}
		break;//释放大招
	case Qt::Key_Space:
		pause = !pause;
		if (pause)
		{
			timer_move->stop(); 
			timer_level->stop();
			timer_bulletson->stop();
			timer_enemy->stop();
			timer_bulletenemy->stop();
			timer_boss->stop();
			timer_bulletboss->stop();//暂停计时
			this->setCursor(Qt::ArrowCursor);  //重现光标
			update();
		}
		else
		{
			timer_move->start();
			timer_level->start();
			timer_bulletson->start();
			timer_enemy->start();
			timer_bulletenemy->start();
			timer_boss->start();
			timer_bulletboss->start();//恢复计时
			this->setCursor(Qt::BlankCursor);  //隐藏光标
		}
	}
	update();
}

void Game1942_Play::keyReleaseEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_W:	 plane_own->move(UP, 10);	plane_son->move(SON, 10);	break;//上
	case Qt::Key_S:	 plane_own->move(DOWN, 10);	plane_son->move(SON, 10);	break;//下
	case Qt::Key_D:  plane_own->move(RIGHT, 10); plane_son->move(SON, 10);	break;//左
	case Qt::Key_A:	 plane_own->move(LEFT, 10);	plane_son->move(SON, 10);	break;//右
	case Qt::Key_J:
		if (!event->isAutoRepeat())
			timer_bulletown->stop();
		break;//普通攻击
	}
	update();
}

//鼠标事件
void Game1942_Play::mouseMoveEvent(QMouseEvent * event)
{
	if (!pause)
	{
		plane_own->setrect(event->x()-25, event->y()-25, 50, 50);
		plane_son->move(SON, 10);
	}//不是暂停状态，飞机追随鼠标
}

//返回主窗口
void Game1942_Play::returnback()
{
	if (timer_video != NULL)	timer_video->stop();
	if (this != NULL)	this->close();
	open = 0;
}

//计时器——控制己方子弹的生成
void Game1942_Play::timercontrol_bulletown()
{
	timer_bulletown->stop();
	for (int i = 0; i<OWN_BULLET_AMOUNT; i++)
		if (bullet_own[i] == NULL)
		{
			bullet_own[i] = new BulletGroup(plane_own, logic->gettype(), true);
			break;
		}
	update();
	timer_bulletown->start();
}

//计时器——控制子机子弹的生成
void Game1942_Play::timercontrol_bulletson()
{
	timer_bulletson->stop();
	for (int i = 0; i < 2; i++)
		if (plane_son->getson()[i] != NULL)
			for (int j = 0; j<OWN_BULLET_AMOUNT; j++)
				if (bullet_own[j] == NULL)
				{
					bullet_own[j] = new BulletGroup(plane_son->getson()[i], one,true);
					break;
				}
	update();
	timer_bulletson->start();
}

//计时器——控制游戏关卡进程
void  Game1942_Play::timercontrol_level()
{
	timer_level->stop();
	--time;
	progressbar->setValue(time);
	if (time == 0)
	{
		logic->leveladd();
		time = 100;
	}
	timer_level->start(200);
}

//计时器——控制简单敌机的生成
void Game1942_Play::timercontrol_planesimple()
{
	timer_enemy->stop();
	for (int i = 0; i <SIMPLE_PLANE_AMOUNT; i++)
		if (plane_enemy_simple[i] == NULL)
		{
			plane_enemy_simple[i] = new PlaneGroup(ENEMY);
			break;
		}
	update();
	timer_enemy->start(5000 / logic->getlevel());
}

//计时器——控制简单敌机子弹的生成
void Game1942_Play::timercontrol_planesimplebullet()
{
	timer_bulletenemy->stop();
	for (int i = 0; i < SIMPLE_PLANE_AMOUNT; i++)
		if (plane_enemy_simple[i] != NULL)
			for(int j=0;j<ENEMY_BULLET_AMOUNT;j++)
				if (bullet_enemy[j] == NULL)
				{
					bullet_enemy[j] = new BulletGroup(plane_enemy_simple[i] ,one);
					break;
				}
	update();
	timer_bulletenemy->start();
}

//计时器——控制Boss的生成
void Game1942_Play::timercontrol_planeboss()
{
	timer_boss->stop();
	for (int i = 0; i <BOSS_PLANE_AMOUNT; i++)
		if (plane_enemy_boss[i] == NULL)
		{
			plane_enemy_boss[i] = new Plane_Enemy_Boss(20);
			break;
		}
	update();
	timer_boss->start(20000 / logic->getlevel());
}

//计时器——控制Boss子弹的生成
void Game1942_Play::timercontrol_planebossbullet()
{
	timer_bulletboss->stop();
	for (int i = 0; i < BOSS_PLANE_AMOUNT; i++)
		if (plane_enemy_boss[i] != NULL)
		{
			for (int j = 0; j<ENEMY_BULLET_AMOUNT; j++)
				if (bullet_enemy[j] == NULL)
				{
					bullet_enemy[j] = new BulletGroup (plane_enemy_boss[i], three_open);
					break;
				}
		}
	update();
	timer_bulletboss->start();
}

//计时器——控制移动
void Game1942_Play::timercontrol_move()
{
	timer_move->stop();
	for (int i = 0; i<OWN_BULLET_AMOUNT; i++)
		if (bullet_own[i] != NULL)	bullet_own[i]->move(UP,20);
	for (int i = 0; i<ENEMY_BULLET_AMOUNT; i++)
		if (bullet_enemy[i] != NULL)	bullet_enemy[i]->move(plane_own,5);
	for (int i = 0; i<SIMPLE_PLANE_AMOUNT; i++)
		if (plane_enemy_simple[i] != NULL)	plane_enemy_simple[i]->move(ENEMY,2);
	for (int i = 0; i<BOSS_PLANE_AMOUNT; i++)
		if (plane_enemy_boss[i] != NULL)	plane_enemy_boss[i]->move(DOWN,1);
	if(item!=NULL)	item->move(DOWN, 3);
	update();
	timer_move->start();
}

//计时器——控制录像写文件
void Game1942_Play::timercontrol_videowrite()
{
	static bool first = 1;
	if (first)
	{
		if (file->exists()) file->remove();
		first = 0;
		QMessageBox::information(this, "Tip", "Start video!");
		setFocus();//设置键盘焦点
	}
	timer_video->stop();
	Store::videowrite(this);
	timer_video->start(20);
}

//按钮——储存游戏
void Game1942_Play::storegame()
{
	Store::save(this);
	setFocus();//设置键盘焦点
}

