#include "Game1942.h"

//����������
Game1942::Game1942(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// ��������
	list = new QMediaPlaylist();
	list->addMedia(QMediaContent(QUrl("./Resources/BGM.mp3")));
	list->addMedia(QMediaContent(QUrl("./Resources/1.mp3")));
	list->addMedia(QMediaContent(QUrl("./Resources/BGM2.mp3")));
	list->setPlaybackMode(QMediaPlaylist::Loop);
	music = new QMediaPlayer();
	music->setMedia(list);
	music->setVolume(100);
	music->play();

	//��ʾ������
	this->show();
	this->resize(QSize(400, 600));
	this->setWindowTitle("Plane Wars     -by Girafboy");
	this->setWindowIcon(QIcon("./Resources/icon.png"));

	//�����������趨���ڣ��Է��ð�ť
	QWidget* widget = new QWidget();
	this->setCentralWidget(widget);

	//���Ʊ���
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap("./Resources/beijing1.jpg").scaled(this->size())));
	this->setPalette(palette);

	QFont ft("Microsoft YaHei", 20, 75);
	QPalette pa;
	pa.setColor(QPalette::ButtonText, Qt::white);
	//��ʼ��ť
	Start = new QPushButton(widget);
	Start->setIcon(QIcon("./Resources/start.png"));
	Start->setIconSize(QSize(300, 75));
	Start->setGeometry(QRect(75, 200, 250, 75));
	Start->setFlat(true);
	connect(Start, SIGNAL(clicked(bool)), this, SLOT(StartButton_Click()));

	//������ť
	Continue = new QPushButton(widget);
	Continue->setGeometry(QRect(100, 320, 200, 50));
	Continue->setFont(ft);
	Continue->setPalette(pa);
	Continue->setText("CONTINUE");
	Continue->setFlat(true);
	connect(Continue, SIGNAL(clicked(bool)), this, SLOT(ContinueButton_Click()));

	//�˳���ť
	Exit = new QPushButton(widget);
	Exit->setGeometry(QRect(100, 390, 200, 50));
	Exit->setFont(ft);
	Exit->setPalette(pa);
	Exit->setText("EXIT GAME");
	Exit->setFlat(true);
	connect(Exit, SIGNAL(clicked(bool)), this, SLOT(ExitButton_Click()));

	//¼��ť
	Video = new QPushButton(widget);
	Video->setGeometry(QRect(100, 460, 200, 50));
	Video->setFont(ft);
	Video->setPalette(pa);
	Video->setText("VIDEO");
	Video->setFlat(true);
	connect(Video, SIGNAL(clicked(bool)), this, SLOT(VideoButton_Click()));

	//�����ְ�ť
	Nextmusic = new QPushButton(widget);
	Nextmusic->setGeometry(QRect(0, 100, 200, 50));
	Nextmusic->setFont(ft);
	Nextmusic->setPalette(pa);
	Nextmusic->setText("NEXT MUSIC");
	Nextmusic->setFlat(true);
	connect(Nextmusic, SIGNAL(clicked(bool)), this, SLOT(MusicButton_Click()));

	Swapskin = new QPushButton(widget);
	Swapskin->setGeometry(QRect(200, 100, 200, 50));
	Swapskin->setFont(ft);
	Swapskin->setPalette(pa);
	Swapskin->setText("SWAP SKIN");
	Swapskin->setFlat(true);
	connect(Swapskin, SIGNAL(clicked(bool)), this, SLOT(SkinButton_Click()));
}

//����������
Game1942::~Game1942()
{
	if (GameWidget != NULL) delete GameWidget;
	delete Start;
	delete Continue;
	delete Exit;
	delete Video;
	delete Nextmusic;
	delete Swapskin;
	delete music;
	delete list;
	delete timer_video;
	delete file;
	delete in;
	delete this;
}

//��ť������ʼ
void Game1942::StartButton_Click()
{
	GameWidget = new Game1942_Play(this);
	GameWidget->show();
}

//��ť��������������Ϸ
void Game1942::ContinueButton_Click()
{
	GameWidget = new Game1942_Play(this);
	GameWidget->show();
	Store::read(GameWidget);
}

//��ť�����˳�
void Game1942::ExitButton_Click()
{
	
	if (QMessageBox::question(this, "TIP", "Are you sure to quit game?", QMessageBox::Yes, QMessageBox::No) 
		== QMessageBox::Yes)
	{
		this->close();
		delete this;
		exit(0);
	}
}

//��ť�����ۿ�¼��
void Game1942::VideoButton_Click()
{
	GameWidget = new Game1942_Play(this,1);
	GameWidget->show();
	timer_video = new QTimer(this);
	timer_video->start(20);
	file=new QFile("video");
	bool ok = file->open(QIODevice::Text | QIODevice::ReadOnly);
	if (ok) connect(timer_video, SIGNAL(timeout()), this, SLOT(timercontrol_videoread()));
	else 	QMessageBox::information(GameWidget, "ErrorBox", "file fail to read");
	in=new QTextStream(file);
}

//��ť�����л�����
void Game1942::MusicButton_Click()
{
	list->next();
}

//��ť�����л�Ƥ��
void Game1942::SkinButton_Click()
{
	static int skin = 1;
	QPalette palette;
	switch(skin)
	{
	case 0:		palette.setBrush(QPalette::Background, QBrush(QPixmap("./Resources/beijing1.jpg").scaled(this->size())));
		skin = 1; break;
	case 1:		palette.setBrush(QPalette::Background, QBrush(QPixmap("./Resources/background.jpg").scaled(this->size())));
		skin = 2; break;
	case 2:		palette.setBrush(QPalette::Background, QBrush(QPixmap("./Resources/liuxing.jpg").scaled(this->size())));
		skin = 3; break;
	case 3:		palette.setBrush(QPalette::Background, QBrush(QPixmap("./Resources/xingkong.jpg").scaled(this->size())));
		skin = 0; break;
	default:skin = 0;
		break;
	}
	this->setPalette(palette);
}

//��ʱ��������ȡ¼������
void Game1942::timercontrol_videoread()
{
	timer_video->stop();
	bool end = Store::videoread(GameWidget, *in);
	timer_video->start();
	if (end||GameWidget->open==0)
	{
		timer_video->stop();
		file->close();
		delete GameWidget;
		GameWidget = NULL;
	}
}
