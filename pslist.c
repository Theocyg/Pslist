#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>
#include<windows.h>
#include<tlhelp32.h>

int _tmain(int argc, TCHAR *argv[]) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	//snapshot all process
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("Pslist error \n"));
		exit(EXIT_FAILURE);
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	//retrieve the process information
	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error ! \n"));
		CloseHandle(hProcessSnap);
		exit(EXIT_FAILURE);
	}

	_tprintf(_T("\t[Name] \t[PID]\t[ThreadID]\t[PPID]\t[CPUTime]\t[UserTime] \n"));

	if (_tcscmp(argv[1], _T("-h")) == 0) {
		_tprintf(_T("Usage: pslist [option] \n"));
		exit(EXIT_FAILURE);
	} else if (argc > 2 && _tcscmp(argv[1], _T("-d")) == 0) {
		DWORD targetPID = _ttoi(argv[2]);
		do {
			if (pe32.th32ProcessID == targetPID) {
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
				if (hProcess != NULL) {
					FILETIME ftCreation, ftExit, ftKernel, ftUser;
					if (GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser)) {
						// Convert FILETIME to ULONGLONG
						ULONGLONG ullKernel = (((ULONGLONG)ftKernel.dwHighDateTime) << 32) + ftKernel.dwLowDateTime;
						ULONGLONG ullUser = (((ULONGLONG)ftUser.dwHighDateTime) << 32) + ftUser.dwLowDateTime;

						// Convert to seconds
						double dKernel = ullKernel * 1e-7;
						double dUser = ullUser * 1e-7;

						_tprintf(_T("\t%s\t%d\t%d\t%d\t%f\t%f\n"),
							pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID, dKernel, dUser);
					} else {
						_tprintf(_T("GetProcessTimes error ! \n"));
					}
					CloseHandle(hProcess);
				}
				break;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	} else if (argv[1] == NULL){
		//print all process information
		do {
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
			if (hProcess != NULL) {
				FILETIME ftCreation, ftExit, ftKernel, ftUser;
				if (GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser)) {
					// Convert FILETIME to ULONGLONG
					ULONGLONG ullKernel = (((ULONGLONG)ftKernel.dwHighDateTime) << 32) + ftKernel.dwLowDateTime;
					ULONGLONG ullUser = (((ULONGLONG)ftUser.dwHighDateTime) << 32) + ftUser.dwLowDateTime;

					// Convert to seconds
					double dKernel = ullKernel * 1e-7;
					double dUser = ullUser * 1e-7;

					_tprintf(_T("\t%s\t%d\t%d\t%d\t%f\t%f\n"),
						pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID, dKernel, dUser);
				} else {
					_tprintf(_T("GetProcessTimes error ! \n"));
				}
				CloseHandle(hProcess);
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}

	CloseHandle(hProcessSnap);
	return 0;
}