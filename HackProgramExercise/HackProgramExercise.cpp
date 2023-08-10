#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int main()
{
    DWORD pid = 0;
    cout << "PID: ";
    cin >> dec >> pid;

    int intRead = 0;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    // Prompt for address
    uintptr_t address = 0x0;
    cout << "Memory Address: 0x";
    cin >> hex >> address;
    getchar();

    BOOL rpm = ReadProcessMemory(hProcess, (LPCVOID)address, &intRead, sizeof(int), NULL);
    if (rpm == FALSE) {
        cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    cout << "intRead = " << dec << intRead << endl;
    cout << "Press ENTER to quit." << endl;
    system("pause > nul");
    return 0;
}