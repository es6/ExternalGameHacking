// ExternalGameHacking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int main()
{
    int varInt = 123456;
    string varString = "DefaultString";
    char arrChar[128] = "Long char array right there ->";
    int* ptr2int = &varInt;
    int** ptr2ptr = &ptr2int;
    int*** ptr2ptr2 = &ptr2ptr;

    do {
        cout << "Process ID: " << dec << GetCurrentProcessId() << endl;
        cout << "varInt (0x" << hex << &varInt << ") " << "= " << dec << varInt << endl;
        cout << "varString (0x" << hex << &varString << ") " << "= " << varString << endl;
        cout << "arrChar[128] (0x" << hex << &arrChar << ") " << "= " << arrChar << endl;
        cout << endl;
        cout << "ptr2int (0x" << hex << &ptr2int << ") " << "= " << "0x" << hex << ptr2int << endl;
        cout << "ptr2ptr (0x" << hex << &ptr2ptr << ") " << "= " << "0x" << hex << ptr2ptr << endl;
        cout << "ptr2ptr2 (0x" << hex << &ptr2ptr2 << ") " << "= " << "0x" << hex << ptr2ptr2 << endl;
        cout << endl;
        cout << "Press ENTER to print again." << endl;
        getchar();
        cout << endl << "---------------------------------------------------" << endl << endl;
    } while (true);
}