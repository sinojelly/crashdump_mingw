#ifndef CRASH_DUMPER_H
#define CRASH_DUMPER_H

#include <Windows.h>
#include <sstream>

class CrashDumper
{
	public:
		CrashDumper();
		bool Dump(DWORD processId, DWORD threadId, LPEXCEPTION_POINTERS exception, std::ostringstream* pStackTraceStream);
};

#endif // CRASH_DUMPER_H
