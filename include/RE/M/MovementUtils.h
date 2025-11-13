#pragma once

#include "RE/M/Movement.h"

namespace RE
{
	class NiMatrix3;
	class NiPoint3;
	struct MovementVector;

	namespace MovementUtils
	{
		bool  CanReachGoalAtCurrentSpeed(const NiPoint3& cur_pos, const NiPoint3& target_pos, float cur_heading, float speed, const Movement::MaxSpeeds& max_speeds);  // 89337
		bool  CanStrafe(const Movement::MaxSpeeds& max_speeds);
		float ComputeAngleBetweenVectors(const NiPoint3& from, const NiPoint3& to);
		float ComputeCurrentSpeedForDirection(NiPoint3 V, const Movement::MaxSpeeds& max_speeds);
		float ComputeCurrentSpeedForDirection(const NiPoint3& V, float speed_denorm, const Movement::MaxSpeeds& max_speeds);
		float ComputeCurrentSpeedForNormalizedDirection(NiPoint3 direction_normalized, const Movement::MaxSpeeds& max_speeds);
		float ComputeCurrentSpeedForNormalizedDirection(NiPoint3 direction_normalized, const Movement::MaxSpeeds& max_speeds, float& max_speed_walk, float& max_speed_run);
		void  ComputeDirectionFromEulerAngles(const NiPoint3& angles, NiPoint3& ans);
		void  ComputeDirectionVector(const NiPoint3& angles, const NiPoint3& movement_rotation, NiPoint3& ans, bool anglesHeadingOnly);
		float ComputeHeadingFromVector(const NiPoint3& V);
		float ComputeHeadingOffsetBetweenVectors(const NiPoint3& from, const NiPoint3& to);
		float ComputePitchFromVector(const NiPoint3& V);
		void  ComputeRotationBetweenDirectionVectors(const NiPoint3& A, const NiPoint3& B, NiMatrix3& ans);
		float ComputeRotationFromDelta(float delta_angle, float dtime);
		float ComputeRotationFromDelta(float cur_angle, float target_angle, float dtime);
		void  ComputeRotationFromEulerAngles(float Z, float X, float Y, NiMatrix3& ans);
		float ComputePitchOffsetBetweenVectors(const NiPoint3& from, const NiPoint3& to);
		bool  ComputeSpeedForDistanceAndTargetSpeed(float acc, float decel, float speedNorm, float a4, float a5, float& a6, float& a7);  // 89341
		bool  ComputeSpeedForSlowDownDistance(float a1, float a2, float a3, float& a4, float& a5);                                       // 89340
		void  ComputeTimeAndDistanceToStop(float speed, float accel, float& time, float& distance);
		void  DampenMovementVector(const MovementVector& MV_cur, const MovementVector& MV_target, float acc_denorm, float decel_denorm, float dtime, MovementVector& ans);
		void  DampenMovementVector(const MovementVector& MV_cur, const MovementVector& MV_target, float acc_denorm, float decel_denorm, float max_rot_speed_denorm, float dtime, MovementVector& ans);
		float DenormalizeAcceleration(float acc_norm, const Movement::MaxSpeeds& max_speeds);
		float DenormalizeAngleAcceleration(float angle_accel_norm, const Movement::MaxSpeeds& max_speeds);
		float DenormalizeRotateWhileMoving(float speed_norm, const Movement::MaxSpeeds& max_speeds);
		float DenormalizeRotationSpeed(float rotspeed_norm, const Movement::MaxSpeeds& max_speeds);
		float DenormalizeSpeed(float speed_norm, const Movement::MaxSpeeds& maxspeeds);
		void  EstimateTransitionDistance(float speed, float max_speed, float acc, float decel, float& ans_1, float& ans_2);
		float NormalizeAcceleration(float acc_denorm, const Movement::MaxSpeeds& max_speeds);
		float NormalizeAngleAcceleration(float angle_accel_denorm, const Movement::MaxSpeeds& max_speeds);
		float NormalizeRotateWhileMoving(float speed_denorm, const Movement::MaxSpeeds& max_speeds);
		float NormalizeRotationSpeed(float rotspeed_denorm, const Movement::MaxSpeeds& max_speeds);
		float NormalizeSpeed(float speed_denorm, const Movement::MaxSpeeds& maxspeeds);
	}
}
