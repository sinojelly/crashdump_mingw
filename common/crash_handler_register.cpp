#include "crash_handler_register.h"

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace {

std::wstring CrashDumper_dumperProcessRelativePath;

LONG WINAPI exceptionHandler(LPEXCEPTION_POINTERS exception)
{
	wchar_t currentProcessPath[MAX_PATH + 1];

	DWORD written = GetModuleFileNameW(NULL, currentProcessPath, sizeof(currentProcessPath) / sizeof(currentProcessPath[0]));
	std::wstring currentProcessPath_ws(currentProcessPath);
	std::wstring dumperProcessPath_ws(currentProcessPath_ws, 0, currentProcessPath_ws.find_last_of(L'\\'));
	dumperProcessPath_ws += CrashDumper_dumperProcessRelativePath;

	wchar_t commandLine[32768];
	
	swprintf_s(commandLine, sizeof(commandLine) / sizeof(commandLine[0]), L"\"%ls\" %lu %lu %p", dumperProcessPath_ws.c_str(), GetCurrentProcessId(), GetCurrentThreadId(), exception);

	STARTUPINFOW startupInfo = { 0 };
	startupInfo.cb = sizeof(STARTUPINFOW);
	PROCESS_INFORMATION dumperProcessInfo;
	fprintf(stderr, "commandLine: %ls\n", commandLine);

	if (CreateProcessW(dumperProcessPath_ws.c_str(), commandLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &dumperProcessInfo) == 0)
	{
		std::cerr << "ERROR: Unable to run the dumper process" << std::endl;
		return FALSE;
	}

	// Wait to be terminated by dumper. This may look like it's resilient to the dumper crashing, but it isn't.
	// The dumper will have suspended this thread, so if it crashes without resuming it this process will stay stuck forever.
	WaitForSingleObject(dumperProcessInfo.hProcess, INFINITE);

	CloseHandle(dumperProcessInfo.hProcess);
	CloseHandle(dumperProcessInfo.hThread);

	return TRUE;
}

}

//void crash_handler_register(wchar_t dumperProcessRelativePath[])
void crash_handler_register(std::wstring dumperProcessRelativePath)
{
	CrashDumper_dumperProcessRelativePath = dumperProcessRelativePath;
	
	SetUnhandledExceptionFilter(exceptionHandler);
}
