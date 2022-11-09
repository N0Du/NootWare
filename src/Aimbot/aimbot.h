#pragma once
#include "../globals.h"
#include "../tools/vector.h"
#include "../tools/memory.h"
#include "../tools/csgo_offsets.h"

namespace aimbot {
	inline float smoothing = 3.f;
	constexpr Vector3 CalculateAngle(const Vector3& localPosition, const Vector3& ennemyPosition, const Vector3& viewAngles) noexcept;
	void aimbot();
}