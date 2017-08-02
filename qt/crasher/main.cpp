#include "mainwindow.h"
#include <QApplication>
#include "crash_handler_register.h"

void crashme()
{
	*((int*)1) = 5;
}

int main(int argc, char *argv[])
{
	crash_handler_register(L"\\..\\..\\dumper\\release\\dumper.exe");
	
	crashme();
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	return a.exec();
}
