#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int HackProgram()
{
    int intRead = 0;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 27504);
    if (hProcess == NULL) {
        cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    BOOL rpm = ReadProcessMemory(hProcess, (LPCVOID)0x33AF1BFB40, &intRead, sizeof(int), NULL);

    cout << "intRead = " << dec << intRead << endl;
    cout << "Press ENTER to quit." << endl;
    getchar();
    return 0;
}