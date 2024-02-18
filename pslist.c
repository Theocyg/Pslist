#include <tchar.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>

int _tmain(int argc, TCHAR *argv[])
{

    if (argc == 1)
    {
        // no arguments, show all processes
        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            // error
            _tprintf(_T("Pslist error \n"));
            exit(EXIT_FAILURE);
        }
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        _tprintf(_T("\t[Name] \t[PID]\t[ThreadID]\t[PPID] \n"));

        if (Process32First(hProcessSnap, &pe32))
        {
            // loop through all processes
            do
            {
                // print process stats
                _tprintf(_T("%25s %8d %8d %8d \n"),
                         pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID);
            } while (Process32Next(hProcessSnap, &pe32));
        }

        CloseHandle(hProcessSnap);
    }
    else if (argc == 3 && strcmp(argv[1], "-d") == 0)
    {
        // CODE DU <-d>
    }

    else if (argc >= 3 && _tcscmp(argv[1], _T("-d")) == 0)
    {
        // -d argument to show process stats for the specified PID
        int pid = _ttoi(argv[2]);

        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            // error
            _tprintf(_T("Pslist error \n"));
            exit(EXIT_FAILURE);
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hProcessSnap, &pe32))
        {
            // loop through all processes
            do
            {
                // print process stats for the specified PID
                if (pe32.th32ProcessID == pid)
                {
                    _tprintf(_T("\t[Name] \t[PID]\t[ThreadID]\t[PPID] \n"));
                    _tprintf(_T("%25s %8d %8d %8d \n"),
                             pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID);
                    break;
                }
            } while (Process32Next(hProcessSnap, &pe32));
        }

        CloseHandle(hProcessSnap);
    }

    // else if (argc >= 3 && _tcscmp(argv[1], _T("-n")) == 0)
    // {
    //     // -n argument to show process stats for the specified process name
    //     TCHAR *processName = argv[2];

    //     HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    //     if (hProcessSnap == INVALID_HANDLE_VALUE)
    //     {
    //         // error
    //         _tprintf(_T("Pslist error \n"));
    //         exit(EXIT_FAILURE);
    //     }

    //     PROCESSENTRY32 pe32;
    //     pe32.dwSize = sizeof(PROCESSENTRY32);

    //     if (!Process32First(hProcessSnap, &pe32))
    //     {
    //         // error
    //         _tprintf(_T("Pslist error \n"));
    //         CloseHandle(hProcessSnap);
    //         exit(EXIT_FAILURE);
    //     }

    //     do
    //     {
    //         if (_tcscmp(pe32.szExeFile, processName) == 0)
    //         {
    //             // print process info
    //             _tprintf(_T("Process Name: %s\n"), pe32.szExeFile);
    //             _tprintf(_T("Process ID: %d\n"), pe32.th32ProcessID);
    //             // add more info as needed
    //         }
    //     } while (Process32Next(hProcessSnap, &pe32));

    //     CloseHandle(hProcessSnap);
    // }

    else if (_tcscmp(argv[1], _T("-h")) == 0)
    {
        // -h argument to show all usable arguments for the program
        _tprintf(_T("Usable arguments:\n"));
        _tprintf(_T("-d <PID>: Show process stats for the specified PID\n"));
        _tprintf(_T("-h: Show all usable arguments for the program\n"));
    }
    else
    {
        // invalid arguments
        _tprintf(_T("Invalid arguments. Use -h to show all usable arguments.\n"));
    }

    return 0;
}