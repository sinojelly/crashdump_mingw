#ifndef CRASH_HANDLER_DUMP_H
#define CRASH_HANDLER_DUMP_H

#include <Windows.h>
#include <sstream>

bool crash_handler_dump(DWORD processId, DWORD threadId, LPEXCEPTION_POINTERS exception, std::ostringstream* pStackTraceStream);

#endif // CRASH_HANDLER_DUMP_H
