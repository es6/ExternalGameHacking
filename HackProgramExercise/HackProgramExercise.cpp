#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int main()
{
    int intRead = 0;
    // Launch Hack Program first to get updated PID
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 27504);
    if (hProcess == NULL) {
        cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    // Retrieve current varInt address from Dummy Program
    BOOL rpm = ReadProcessMemory(hProcess, (LPCVOID)0x33AF1BFB40, &intRead, sizeof(int), NULL);

    cout << "intRead = " << dec << intRead << endl;
    cout << "Press ENTER to quit." << endl;
    getchar();
    return 0;
}