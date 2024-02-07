// #include<stdio.h>
// #include<stdlib.h>
// #include<tchar.h>
// #include<windows.h>
// #include<tlhelp32.h>
// int _tmain(int argc, TCHAR *argv[]) {
// 	HANDLE hProcessSnap =
// 		CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

// 	//snapshot all process
// 	if (hProcessSnap == INVALID_HANDLE_VALUE) {
// 		_tprintf(_T("Pslist error \n"));
// 		exit(EXIT_FAILURE);
// 	}
// 	PROCESSENTRY32 pe32;
// 	pe32.dwSize = sizeof(PROCESSENTRY32);

// 	//retrieve the process information
// 	if (!Process32First(hProcessSnap, &pe32)) {
// 		_tprintf(_T("Process32First error ! \n"));
// 		CloseHandle(hProcessSnap);
// 		exit(EXIT_FAILURE);
// 	}
		
// 	_tprintf(_T("\t[Name] \t[PID]\t[ThreadID]\t[PPID] \n")); // https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32
// 	//print all process information
// 	do {
// 		_tprintf(_T("%25s %8d %8d %8d \n"),
// 			pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID);
// 	} while (Process32Next(hProcessSnap, &pe32));
// 	return 0;
// }