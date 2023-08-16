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

		// check if ctrl key is down
		if (!GetAsyncKeyState(VK_CONTROL))
			continue;

		const auto localPlayer = mem.Read<uintptr_t>(client + offsets::dwLocalPlayer);

		// check if player is dead
		if (!mem.Read<int32_t>(localPlayer + offsets::m_iHealth)) 
			continue;

		const auto crosshairId = mem.Read<int32_t>(localPlayer + offsets::m_iCrosshairId);

		/*	Ids 1 through 64 are reserved for players
			if id is more than 64 player isn't looking at other players
		*/
		if (!crosshairId || crosshairId > 64)
			continue;

		// * entities have a size of 0x10 in memory
		const auto target = mem.Read<uintptr_t>(client + offsets::dwEntityList + (crosshairId - 1) * 0x10);

		// check if target is dead
		if (!mem.Read<int32_t>(target + offsets::m_iHealth)) 
			continue;

		const auto playerTeam = mem.Read<int32_t>(localPlayer + offsets::m_iTeamNum);

		// check if target is an ally
		if (mem.Read<int32_t>(target + offsets::m_iTeamNum) == playerTeam)
			continue;

		mem.Write<uintptr_t>(client + offsets::dwForceAttack, 6);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		mem.Write<uintptr_t>(client + offsets::dwForceAttack, 4);
	}

	return 0;
}
