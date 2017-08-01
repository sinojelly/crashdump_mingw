#include "mainwindow.h"
#include <QApplication>

#include "crash_dumper.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <sstream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	if (argc < 3)
	{
		return false;
	}

	char* processIdString = argv[1];
	char* threadIdString = argv[2];
	char* exceptionPointersString = argv[3];

	DWORD processId;
	DWORD threadId;
	LPEXCEPTION_POINTERS exception;

	sscanf_s(processIdString, "%lu", &processId);
	sscanf_s(threadIdString, "%lu", &threadId);
	sscanf_s(exceptionPointersString, "%p", &exception);

	CrashDumper dumper;
	std::ostringstream oss;
	bool ok = dumper.Dump(processId, threadId, exception, &oss);
	
	w.SetDumpStr(QString::fromUtf8(oss.str().c_str()));
	
	return a.exec();
}
