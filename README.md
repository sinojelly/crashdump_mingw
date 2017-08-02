# crashdump_mingw
Based on an Visual Studio example by Arnavion: https://github.com/Arnavion/crashdump, who described it well on his project's page.

This repository is only a bit modified with example projects for MinGW and qt.

## How it Works
1. Your application crashes, runs your dumper.exe process and waits
2. The dumper process gets a callstack trace of your crashed process
3. You can save it to a file or send it to your server for further analysis. _(Not implemented in these examples)_

## To Do
* The call stack contains only raw addresses, not symbol names,
  but if you have the original unstripped exe file with debug symbols included,
  you can easily use gdb to map addresses to source code lines.
* Saving minidumps is commented out
* There is a lot of code for parsing variables and data which doesn't seem to work with GCC/MinGW debug symbols

## License

APL 2.0 (Apache License, Version 2.0), same as the original Arnavion's code.

