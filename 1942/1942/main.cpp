#include "Game1942.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Game1942 w;
	w.show();//չʾ����
	
	return a.exec();
}
