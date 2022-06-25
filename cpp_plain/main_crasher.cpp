#include <iostream>

#define CRASH_HANDLER_REGISTER_DUMPER_RELATIVE_PATH L"\\dumper.exe"
#include "crash_handler_register.h"

void crashme()
{
	*((int*)1) = 5;
}

/*
 *  Usage: run crasher.exe, it calls dumper.exe to dump stack trace.
 * 
 *  Use cv2pdb crasher.exe to generate crasher.pdb, then can output function name.
 *  And If you found "Can not load PDB DLL" while running cv2pdb command, 
 *  You can install Visual Studio and run the command in Developer Command Prompt.
 *  Download cv2pdb here: https://github.com/rainers/cv2pdb
 *
 *  D:\code\crashdump_mingw\cpp_plain\cmake-build-debug>crasher.exe
    commandLine: "D:\code\crashdump_mingw\cpp_plain\cmake-build-debug\dumper.exe" 38652 3172 000000000063EE80
    Stack Trace:
    >00: 0x00401555 ?
    >01: 0x004015c6 ?
    >02: 0x004013c7 ?
    >03: 0x004014fb ?
    >04: 0x7ffad8ea70200xfc5cb4 ()
    >05: 0x7ffadae826300xfc5cb4 ()
 * */

int main(int argc, char *argv[])
{
	crash_handler_register(std::wstring(L"\\dumper.exe"));
	
	crashme();
}
