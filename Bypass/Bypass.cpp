#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;


class Bypass {
public:
    Bypass();
    ~Bypass();
    BOOL attach(DWORD pid);
    BOOL read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize);
    BOOL write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize);
private:
    HANDLE m_hProcess = NULL;
};

Bypass::Bypass() {
    // empty Constructor
}

Bypass::~Bypass() {
    if (m_hProcess != NULL) CloseHandle(m_hProcess);
}

BOOL Bypass::attach(DWORD pid) {
    m_hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if (m_hProcess == NULL) {
        return false;
    }
    else {
        return true;
    }
}

BOOL Bypass::read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize) {
    BOOL rpm = ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, NULL);
    if (rpm == FALSE) {
        return false;
    }
    else {
        return true;
    }
}

BOOL Bypass::write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize) {
    BOOL wpm = WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, NULL);
    if (wpm == FALSE) {
        return false;
    }
    else {
        return true;
    }
}