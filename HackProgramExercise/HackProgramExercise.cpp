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
        BASE = buffer;
    }
    DWORD finalBuffer = 0;
    BOOL readAddyValue = ReadProcessMemory(hProcess, (LPCVOID)BASE, &finalBuffer, sizeof(int) * 2, NULL);
    return finalBuffer;
}

int main()
{
    // PID Prompt
    // Opening the process via PID input and running OpenProcess function

    DWORD pid = 0;
    cout << "PID: ";
    cin >> dec >> pid;

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    if (hProcess == NULL) {
        cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    // Simple RPM exercise
    // Prompt user to input an address which will be read by RPM function and stored into "intRead"

    uintptr_t address = 0x0;
    cout << "Memory Address: 0x";
    cin >> hex >> address;
    getchar();

    int intRead = 0;

    BOOL rpm = ReadProcessMemory(hProcess, (LPCVOID)address, &intRead, sizeof(int), NULL);
    if (rpm == FALSE) {
        cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    cout << "intRead = " << dec << intRead << endl;

    // Reading a pointer

    // Read the address of "ptr2int" and stored it into a variable. Then RPM'd to get the value of "ptr2int", then RPM'd
    // the value to get the value of "varInt"

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

    // Created a function, pointerChainFollowing, to deference our "ptr2ptr2" all the way down to
    // varInt and print that value

    vector<uintptr_t> addressOffsets;

    uintptr_t ptr2ptr2Address = 0x0;
    cout << "ptr2ptr2 Memory Address: 0x";
    cin >> hex >> ptr2ptr2Address;
    getchar();

    addressOffsets.push_back(ptr2ptr2Address);

    // Push back 0 as offsets as we don't have offsets in this dummy program
    addressOffsets.push_back(0);
    addressOffsets.push_back(0);
    addressOffsets.push_back(0);

    uintptr_t deferencedPointerChain = pointerChainFollowing(addressOffsets, hProcess);
    cout << "ptr2ptr2 deferenced chain: " << dec << deferencedPointerChain << endl;

    // Reading text from varString

    uintptr_t varStringAddress = 0x0;
    cout << "varString Memory Address: 0x";
    cin >> hex >> varStringAddress;
    getchar();

    string stringBuffer = "";
    BOOL stringRPM = ReadProcessMemory(hProcess, (LPCVOID)varStringAddress, &stringBuffer, sizeof(stringBuffer), NULL);
    if (stringRPM == FALSE) {
        cout << "stringRPM failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }
    cout << "varString: " << stringBuffer << endl;

    // Reading text from arrChar
    uintptr_t arrCharAddress = 0x0;
    cout << "arrCharAddress = 0x";
    cin >> hex >> arrCharAddress;
    getchar();

    char arrBuffer[128];
    BOOL arrRPM = ReadProcessMemory(hProcess, (LPCVOID)arrCharAddress, &arrBuffer, sizeof(arrBuffer), NULL);
    if (arrRPM == FALSE) {
        cout << "arrRPM failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }
    cout << "arrBuffer: " << arrBuffer << endl;

    // Ending stuff
    cout << "Press ENTER to quit." << endl;
    BOOL closeHandle = CloseHandle(hProcess);
    if (closeHandle == 0) {
        cout << "CloseHandle failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }
    system("pause > nul");
    return 0;
}