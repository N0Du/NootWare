#include "aimbot.h"

constexpr Vector3 aimbot::CalculateAngle(
	const Vector3& localPosition,
	const Vector3& enemyPosition,
	const Vector3& viewAngles) noexcept
{
	return ((enemyPosition - localPosition).ToAngle() - viewAngles);
}

void aimbot::aimbot() {
	if (!GetAsyncKeyState(VK_LBUTTON)) {
		return;
	}

	// eye position = origin + viewOffset
	const auto localEyePosition = global::memory.Read<Vector3>(global::localPlayer + offsets::m_vecOrigin) +
		global::memory.Read<Vector3>(global::localPlayer + offsets::m_vecViewOffset);

	const auto clientState = global::memory.Read<std::uintptr_t>(global::engine + offsets::dwClientState);

	const auto localPlayerId =
		global::memory.Read<std::int32_t>(clientState + offsets::dwClientState_GetLocalPlayer);

	const auto viewAngles = global::memory.Read<Vector3>(clientState + offsets::dwClientState_ViewAngles);
	const auto aimPunch = global::memory.Read<Vector3>(global::localPlayer + offsets::m_aimPunchAngle) * 2;

	// aimbot fov
	auto bestFov = 100.f;
	auto bestAngle = Vector3{ };

	for (auto i = 1; i <= 32; ++i)
	{
		const auto player = global::memory.Read<std::uintptr_t>(global::client + offsets::dwEntityList + i * 0x10);

		if (global::memory.Read<std::int32_t>(player + offsets::m_iTeamNum) == global::localTeam)
			continue;

		if (global::memory.Read<bool>(player + offsets::m_bDormant))
			continue;

		if (global::memory.Read<std::int32_t>(player + offsets::m_lifeState))
			continue;

		if (global::memory.Read<std::int32_t>(player + offsets::m_bSpottedByMask) & (1 << localPlayerId))
		{
			const auto boneMatrix = global::memory.Read<std::uintptr_t>(player + offsets::m_dwBoneMatrix);

			// pos of player head in 3d space
			// 8 is the head bone index :)
			const auto playerHeadPosition = Vector3{
				global::memory.Read<float>(boneMatrix + 0x30 * 8 + 0x0C),
				global::memory.Read<float>(boneMatrix + 0x30 * 8 + 0x1C),
				global::memory.Read<float>(boneMatrix + 0x30 * 8 + 0x2C)
			};

			const auto angle = aimbot::CalculateAngle(
				localEyePosition,
				playerHeadPosition,
				viewAngles + aimPunch
			);

			const auto fov = std::hypot(angle.x, angle.y);

			if (fov < bestFov)
			{
				bestFov = fov;
				bestAngle = angle;
			}
		}
	}

	//do aimbot
	if (!bestAngle.IsZero()) {
		if (smoothing) {
			global::memory.Write<Vector3>(clientState + offsets::dwClientState_ViewAngles, viewAngles + bestAngle / smoothing);
		}
		else {
			global::memory.Write<Vector3>(clientState + offsets::dwClientState_ViewAngles, viewAngles + bestAngle);
		}
	}
}