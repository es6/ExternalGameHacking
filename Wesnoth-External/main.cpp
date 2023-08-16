#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

int main() {
	// Code to attach to process
	HWND wesnoth_window = FindWindow(NULL, L"The Battle for Wesnoth - 1.14.9");

	DWORD pid = 0;
	GetWindowThreadProcessId(wesnoth_window, &pid);

	HANDLE wesnoth_pid = OpenProcess(PROCESS_ALL_ACCESS, true, pid);

	DWORD gold_value = 0;
	SIZE_T bytes_read = 0;

	ReadProcessMemory(wesnoth_pid, (void*)0x017EED18, &gold_value, 4, &bytes_read);

	gold_value += 0xA90;
	ReadProcessMemory(wesnoth_pid, (void*)gold_value, &gold_value, 4, &bytes_read);

	gold_value += 4;

	// Writing over the gold value
	DWORD new_gold_value = 3321;
	SIZE_T bytes_written = 0;

	BOOL wpm = WriteProcessMemory(wesnoth_pid, (void*)gold_value, &new_gold_value, 4, &bytes_read);
	if (wpm == 0) {
		cout << "WPM Failed, GetLastError = " << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	system("pause > nul");
	return 0;
}