#include <Windows.h>

DWORD ret_address = 0xCCAF90;
DWORD* player_base;
DWORD* game_base;
DWORD* gold;

__declspec(naked) void codeCave() {
	__asm {
		pushad
	}

	// modify gold
	player_base = (DWORD*)0x017EED18;
	game_base = (DWORD*)(*player_base + 0xA90);
	gold = (DWORD*)(*game_base + 4);
	*gold = 888;

	__asm {
		popad
		mov eax, dword ptr ds : [ecx]
		lea esi, dword ptr ds : [esi]
		jmp ret_address
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	unsigned char* hook_location = (unsigned char*)0x00CCAF8A;

	if (fdwReason == DLL_PROCESS_ATTACH) {
		VirtualProtect((void*)hook_location, 6, PAGE_EXECUTE_READWRITE, NULL);
		*hook_location = 0xE9;
		*(DWORD*)(hook_location + 1) = (DWORD)&codeCave - ((DWORD)hook_location + 5);
		*(hook_location + 5) = 0x90;


		/*
		* CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);
		* 
		* We use CreateThread to attach our injected_thread function into the code which runs in
		* an infinite loop checking for the key M to be pressed. If M is pressed, our simple gold
		* hack is executed.
		*/
	}

	return true;
}

void simpleGoldHack() {
	player_base = (DWORD*)0x017EED18;
	game_base = (DWORD*)(*player_base + 0xA90);
	gold = (DWORD*)(*game_base + 4);
	*gold = 999;
}

void injected_thread() {
	while (true) {
		if (GetAsyncKeyState('M')) {
			simpleGoldHack();
		}
		Sleep(1);
	}
}