# Plist.exe

Plist is used to List the process of your windows machine by listing them,  sorted by name, PID, threadID, PPID.

To use it, use the command gcc -o pslist.exe pslist.c and execute it from your cmd by using `./<PATH TO THE EXE>`

By default, without arguments, the program will list every process

## Arguments:
* `-d <PID>`: Will list process with the PID you used as argument
* `-n <ProcessName>`: Will list process with the name you used as argument (🚧 Work in progress... 🚧)
* `-h`: Will show the arguments you can use 