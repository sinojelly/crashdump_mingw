#include "mainwindow.h"
#include <QApplication>

#include <Windows.h>

LONG WINAPI exceptionHandler(LPEXCEPTION_POINTERS exception)
{
	wchar_t currentProcessPath[MAX_PATH + 1];
	wchar_t dumperProcessPath[MAX_PATH + 1];

	DWORD written = GetModuleFileNameW(NULL, currentProcessPath, sizeof(currentProcessPath) / sizeof(currentProcessPath[0]));
	for (DWORD i = written - 1; i >= 0; i--)
	{
		if (currentProcessPath[i] == L'\\')
		{
			memcpy_s(dumperProcessPath, sizeof(dumperProcessPath), currentProcessPath, i * sizeof(i));
			wchar_t dumperProcessName[] = L"\\dumper.exe";
			memcpy_s(dumperProcessPath + i, sizeof(dumperProcessPath) - i * sizeof(i), dumperProcessName, sizeof(dumperProcessName));
			break;
		}
	}

	wchar_t applicationName[MAX_PATH + 3];
	wchar_t commandLine[32768];
	swprintf_s(applicationName, sizeof(applicationName) / sizeof(applicationName[0]), L"\"%ls\"", dumperProcessPath);
	swprintf_s(commandLine, sizeof(commandLine) / sizeof(commandLine[0]), L"\"%ls\" %lu %lu %p", dumperProcessPath, GetCurrentProcessId(), GetCurrentThreadId(), exception);

	STARTUPINFOW startupInfo = { 0 };
	startupInfo.cb = sizeof(STARTUPINFOW);
	PROCESS_INFORMATION dumperProcessInfo;
	if (CreateProcessW(dumperProcessPath, commandLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &dumperProcessInfo) == 0)
	{
		return FALSE;
	}

	// Wait to be terminated by dumper. This may look like it's resilient to the dumper crashing, but it isn't.
	// The dumper will have suspended this thread, so if it crashes without resuming it this process will stay stuck forever.
	WaitForSingleObject(dumperProcessInfo.hProcess, INFINITE);

	CloseHandle(dumperProcessInfo.hProcess);
	CloseHandle(dumperProcessInfo.hThread);

	return TRUE;
}

int main(int argc, char *argv[])
{
	SetUnhandledExceptionFilter(exceptionHandler);
	*((int*)argc + 1) = 5;
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	return a.exec();
}
