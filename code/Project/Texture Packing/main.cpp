#include "TexturePacking.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TexturePacking w;
	w.show();
	return a.exec();
}