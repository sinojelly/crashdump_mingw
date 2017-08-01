#ifndef CRASH_DUMPER_H
#define CRASH_DUMPER_H

#include <Windows.h>

class CrashDumper
{
	public:
		CrashDumper();
		bool Dump(DWORD processId, DWORD threadId, LPEXCEPTION_POINTERS exception);
};

#endif // CRASH_DUMPER_H
