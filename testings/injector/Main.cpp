#include "injector.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <fstream>

#include "bytes.h"

bool IsCorrectTargetArchitecture(HANDLE hProc) {
	BOOL bTarget = FALSE;
	if (!IsWow64Process(hProc, &bTarget)) {
	//	printf("Can't confirm target process architecture: 0x%X\n", GetLastError());
		return false;
	}

	BOOL bHost = FALSE;
	IsWow64Process(GetCurrentProcess(), &bHost);

	return (bTarget == bHost);
}

DWORD GetProcessIdByName(const std::wstring& name) {
	PROCESSENTRY32W entry;  
	entry.dwSize = sizeof(PROCESSENTRY32W);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32FirstW(snapshot, &entry) == TRUE) {
		while (Process32NextW(snapshot, &entry) == TRUE) {
			if (_wcsicmp(entry.szExeFile, name.c_str()) == 0) {
				CloseHandle(snapshot);
				return entry.th32ProcessID;
			}
		}
	}

	CloseHandle(snapshot);
	return 0;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::wstring processName = L"csgo.exe";

	DWORD PID = GetProcessIdByName(processName);

	if (PID == 0) {
		system("pause");
		return -1;
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (!hProc) {
		DWORD Err = GetLastError();
		system("pause");
		return -2;
	}

	if (!IsCorrectTargetArchitecture(hProc)) {
		CloseHandle(hProc);
		system("pause");
		return -3;
	}

	if (!ManualMapDll(hProc, Steam, sizeof(Steam))) {
		CloseHandle(hProc);
		system("pause");
		return -8;
	}

	CloseHandle(hProc);
	return 0;
}
