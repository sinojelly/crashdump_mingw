#include <iostream>

#define CRASH_HANDLER_REGISTER_DUMPER_RELATIVE_PATH L"\\dumper.exe"
#include "crash_handler_register.h"

void crashme()
{
	*((int*)1) = 5;
}

int main(int argc, char *argv[])
{
	crash_handler_register(std::wstring(L"\\dumper.exe"));
	
	crashme();
}
