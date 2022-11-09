#pragma once
#include "tools/memory.h"
#include "tools/csgo_offsets.h"

namespace global {
	inline const auto memory = Memory{"csgo.exe"};

	inline const auto client = memory.GetModuleAddress("client.dll");
	inline const auto engine = memory.GetModuleAddress("engine.dll");

	inline const auto localPlayer = memory.Read<std::uintptr_t>(client + offsets::dwLocalPlayer);
	inline const auto localTeam = memory.Read<std::int32_t>(localPlayer + offsets::m_iTeamNum);
}

