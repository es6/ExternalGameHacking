#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

uintptr_t pointerChainFollowing(vector<uintptr_t> addressOffsets, HANDLE hProcess) {
    uintptr_t BASE = addressOffsets[0];
    uintptr_t buffer = 0;
    for (int i = 1; i < addressOffsets.size(); i++) {
        BOOL derefAddy = ReadProcessMemory(hProcess, (LPCVOID)BASE, &buffer, sizeof(int) * 2, NULL);
        buffer += addressOffsets[i];
        cout << "Buffer: " << hex << buffer << endl;
        BASE = buffer;
    }
    DWORD finalBuffer = 0;
    BOOL readAddyValue = ReadProcessMemory(hProcess, (LPCVOID)BASE, &finalBuffer, sizeof(int) * 2, NULL);
    return finalBuffer;
}

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

    // Reading a pointer exercise
    uintptr_t ptr2intAddress = 0x0;
    cout << "ptr2int Memory Address: 0x";
    cin >> hex >> ptr2intAddress;
    getchar();

    uintptr_t ptr2intBuffer = 0;
    BOOL readPointer = ReadProcessMemory(hProcess, (LPCVOID)ptr2intAddress, &ptr2intBuffer, sizeof(int) * 2, NULL);
    cout << "ptr2intBuffer = 0x" << hex << uppercase << ptr2intBuffer << endl;

    DWORD ptr2intFinalRead = 0;
    BOOL readAddyValue = ReadProcessMemory(hProcess, (LPCVOID)ptr2intBuffer, &ptr2intFinalRead, sizeof(int) * 2, NULL);
    cout << "ptr2intFinalRead = " << dec << ptr2intFinalRead << endl;

    // Following a pointer chain
    vector<uintptr_t> addressOffsets;

    uintptr_t ptr2ptr2Address = 0x0;
    cout << "ptr2ptr2 Memory Address: 0x";
    cin >> hex >> ptr2ptr2Address;
    getchar();

    addressOffsets.push_back(ptr2ptr2Address);
    addressOffsets.push_back(0);
    addressOffsets.push_back(0);
    addressOffsets.push_back(0);

    uintptr_t deferencedPointerChain = pointerChainFollowing(addressOffsets, hProcess);
    cout << "ptr2ptr2 deferenced chain: " << dec << deferencedPointerChain << endl;

    // Ending stuff
    cout << "Press ENTER to quit." << endl;
    system("pause > nul");
    return 0;
}