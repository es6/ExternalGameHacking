#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

int main() {
	DWORD pid = 0;
	cout << "PID: ";
	cin >> dec >> pid;

	HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE, FALSE, pid);
	if (hProcess == NULL) {
		cout << "OpenProcess failed. GetLastError = " << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	uintptr_t varIntAddress = 0x0;
	cout << "Enter varInt address: 0x";
	cin >> hex >> varIntAddress;

	int intToWrite = 0;
	cout << "Enter integer to overwrite with: ";
	cin >> dec >> intToWrite;

	BOOL writeInt = WriteProcessMemory(hProcess, (LPVOID)varIntAddress, &intToWrite, sizeof(int), NULL);
	if (!writeInt) {
		cout << "WriteProcessMemory failed, GetLastError = " << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	cout << "Overwritten successfully" << endl;
	
	cout << "Press ENTER to quit." << endl;
	BOOL closeHandle = CloseHandle(hProcess);
	if (closeHandle == 0) {
		cout << "CloseHandle failed, GetLastError() = " << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	system("pause > nul");
	return EXIT_SUCCESS;
}