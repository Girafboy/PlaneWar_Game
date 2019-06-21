#pragma once

#include "Game1942_Play.h"
#include "ui_Game1942.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <qpushbutton.h>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <qfile.h>

//Ö÷´°¿Ú
class Game1942 : public QMainWindow
{
	Q_OBJECT
		
public:
	Game1942(QWidget *parent = Q_NULLPTR);
	~Game1942();
private:
	Ui::Game1942Class ui;
	Game1942_Play *GameWidget = NULL;
	QPushButton *Start;
	QPushButton *Continue;
	QPushButton *Exit;
	QPushButton *Video;
	QPushButton *Nextmusic;
	QPushButton *Swapskin;
	QMediaPlayer *music;
	QMediaPlaylist *list;
	QTimer *timer_video;
	QFile* file;
	QTextStream *in;
private slots:
	void StartButton_Click();
	void ContinueButton_Click();
	void ExitButton_Click();
	void VideoButton_Click();
	void MusicButton_Click();
	void SkinButton_Click();
	void timercontrol_videoread();
};


