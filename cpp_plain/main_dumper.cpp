#include <iostream>
#include "crash_handler_dump.h"

#include <Windows.h>
#include <DbgHelp.h>
#include <sstream>

int main(int argc, char *argv[])
{
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

	std::ostringstream oss;
	bool ok = crash_handler_dump(processId, threadId, exception, &oss);
	
	std::cout << "Stack Trace:\n" << oss.str() << std::endl;
	return 0;
}
