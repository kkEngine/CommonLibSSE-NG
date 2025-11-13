#include "RE/I/IMovementState.h"

#include "RE/M/MovementUtils.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	void IMovementState::GetDirectionVector(NiPoint3& ans, bool anglesHeadingOnly) const
	{
		RE::NiPoint3 angles;
		DoGetEulerAngles(angles);

		RE::NiPoint3 movement_rotation;
		DoGetMovementRotation(movement_rotation);
		MovementUtils::ComputeDirectionVector(angles, movement_rotation, ans, anglesHeadingOnly);
	}

	float IMovementState::GetMaxSpeed() const
	{
		using DIR = Movement::SPEED_DIRECTION;
		using MINMAX = Movement::MaxSpeeds;

		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MaxSpeeds.speeds[DIR::kForward][MINMAX::kRun];
	}

	float IMovementState::GetMinSpeed() const
	{
		using DIR = Movement::SPEED_DIRECTION;
		using MINMAX = Movement::MaxSpeeds;

		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MaxSpeeds.speeds[DIR::kForward][MINMAX::kWalk];
	}

	float IMovementState::GetMovementHeading() const
	{
		NiPoint3 angles;
		DoGetEulerAngles(angles);
		if (angles.x == 0) {
			NiPoint3 movement_rot;
			DoGetMovementRotation(movement_rot);
			return movement_rot.z + angles.z;
		} else {
			RE::NiPoint3 dir_angles;
			GetDirectionAngles(dir_angles);
			return dir_angles.z;
		}
	}

	float IMovementState::DenormalizeAcceleration(float acc_norm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::DenormalizeAcceleration(acc_norm, MaxSpeeds);
	}

	float IMovementState::DenormalizeAngleAcceleration(float angle_accel_norm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::DenormalizeAngleAcceleration(angle_accel_norm, MaxSpeeds);
	}

	float IMovementState::DenormalizeRotateWhileMoving(float speed_norm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::DenormalizeRotateWhileMoving(speed_norm, MaxSpeeds);
	}

	float IMovementState::DenormalizeRotationSpeed(float rotspeed_norm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::DenormalizeRotationSpeed(rotspeed_norm, MaxSpeeds);
	}

	float IMovementState::DenormalizeSpeed(float speed_norm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::DenormalizeSpeed(speed_norm, MaxSpeeds);
	}

	float IMovementState::NormalizeAcceleration(float acc_denorm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::NormalizeAcceleration(acc_denorm, MaxSpeeds);
	}

	float IMovementState::NormalizeAngleAcceleration(float angle_accel_denorm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::NormalizeAngleAcceleration(angle_accel_denorm, MaxSpeeds);
	}

	float IMovementState::NormalizeRotateWhileMoving(float speed_denorm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::NormalizeRotateWhileMoving(speed_denorm, MaxSpeeds);
	}

	float IMovementState::NormalizeRotationSpeed(float rotspeed_denorm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::NormalizeRotationSpeed(rotspeed_denorm, MaxSpeeds);
	}

	float IMovementState::NormalizeSpeed(float speed_denorm) const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return 0;

		return MovementUtils::NormalizeSpeed(speed_denorm, MaxSpeeds);
	}

	void IMovementState::GetCCRotation(NiMatrix3& ans) const
	{
		RE::NiPoint3 angles;
		DoGetEulerAngles(angles);
		MovementUtils::ComputeRotationFromEulerAngles(angles.z, angles.x, angles.y, ans);
	}

	void IMovementState::GetCCTransform(NiTransform& ans) const
	{
		DoGetLocation(ans.translate);
		RE::NiPoint3 angles;
		DoGetEulerAngles(angles);
		MovementUtils::ComputeRotationFromEulerAngles(angles.z, angles.x, angles.y, ans.rotate);
		ans.scale = 1.0f;
	}

	void IMovementState::GetDirectionAngles(NiPoint3& ans) const
	{
		NiPoint3 angles;
		DoGetEulerAngles(angles);
		NiPoint3 movement_rot;
		DoGetMovementRotation(movement_rot);

		NiMatrix3 angles_M;
		angles_M.EulerAnglesToAxesZXY(angles);

		NiMatrix3 movement_rot_M;
		movement_rot_M.EulerAnglesToAxesZXY(movement_rot);

		auto M = angles_M * movement_rot_M;
		M.ToEulerAnglesZXY(ans);
	}

	bool IMovementState::CanStrafe() const
	{
		Movement::MaxSpeeds MaxSpeeds;
		if (!DoGetCurrentMaxSpeeds(MaxSpeeds))
			return false;

		return MovementUtils::CanStrafe(MaxSpeeds);
	}
}
