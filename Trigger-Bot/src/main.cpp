#include "memory.h"
#include <iostream>
#include <thread>
#include <cstdint>


namespace offsets
{
	// client
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDEA98C;
	constexpr ::std::ptrdiff_t dwEntityList = 0x4DFFF7C;
	constexpr ::std::ptrdiff_t dwForceAttack = 0x322DDE8;

	// entity
	constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4;
	constexpr ::std::ptrdiff_t m_iCrosshairId = 0x11838;
	constexpr ::std::ptrdiff_t m_iHealth = 0x100;
}

int main()
{
	Memory mem { "csgo.exe" };
	const auto client = mem.getModuleAddress("client.dll");

	std::cout << "[+] Process ID -> " << mem.getProcessId() << '\n';
	std::cout << "[+] Client Dll -> 0x" << std::hex << client << std::dec << '\n';

	std::cout << "--------------------------------------------" << '\n';
	std::cout << "~ Starting The Cheat... ~" << '\n';
	
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// continue if shift key isn't down
		if (!GetAsyncKeyState(VK_SHIFT))
			continue;

	}

	return 0;
}
