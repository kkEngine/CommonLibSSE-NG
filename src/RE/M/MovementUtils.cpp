#include "RE/M/MovementUtils.h"

#include "RE/N/NiMath.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	namespace MovementUtils
	{
		namespace impl
		{
			float normalize_angle_single(float angle)
			{
				if (angle < -NI_PI)
					angle += NI_TWO_PI;
				if (angle > NI_PI)
					angle -= NI_TWO_PI;
				return angle;
			}
		}

		float ComputeRotationFromDelta(float delta_angle, float dtime)
		{
			if (dtime <= 0.0f)
				return 0.0f;

			return normalize_angle(delta_angle) / dtime;
		}

		float ComputeRotationFromDelta(float cur_angle, float target_angle, float dtime)
		{
			return ComputeRotationFromDelta(target_angle - cur_angle, dtime);
		}

		void ComputeDirectionFromEulerAngles(const NiPoint3& angles, NiPoint3& ans)
		{
			RE::NiMatrix3 M;
			ComputeRotationFromEulerAngles(angles.z, angles.x, angles.y, M);
			ans = { M.entry[0][1], M.entry[1][1], M.entry[2][1] };
		}

		void ComputeRotationFromEulerAngles(float Z, float X, float Y, NiMatrix3& ans)
		{
			if (Y == 0.0f) {
				float sin_Z = sinf(Z);
				float cos_Z = cosf(Z);
				if (X == 0.0f) {
					ans.entry[0][0] = cos_Z;
					ans.entry[0][1] = sin_Z;
					ans.entry[1][0] = -sin_Z;
					ans.entry[1][1] = cos_Z;
					ans.entry[0][2] = 0;
					ans.entry[1][2] = 0;
					ans.entry[2][0] = 0;
					ans.entry[2][1] = 0;
					ans.entry[2][2] = 1;
				} else {
					RE::NiMatrix3 _M1;
					_M1.entry[0][0] = cos_Z;
					_M1.entry[0][1] = sin_Z;
					_M1.entry[1][0] = -sin_Z;
					_M1.entry[1][1] = cos_Z;
					_M1.entry[0][2] = 0;
					_M1.entry[1][2] = 0;
					_M1.entry[2][0] = 0;
					_M1.entry[2][1] = 0;
					_M1.entry[2][2] = 1;

					RE::NiMatrix3 _M2;
					_M2.entry[1][2] = sinf(X);
					_M2.entry[2][2] = -sinf(X);
					_M2.entry[0][0] = 1;
					_M2.entry[0][1] = 0;
					_M2.entry[0][2] = 0;
					_M2.entry[1][0] = 0;
					_M2.entry[2][0] = 0;
					_M2.entry[1][1] = cosf(X);
					_M2.entry[2][2] = cosf(X);

					ans = _M1 * _M2;
				}
			} else {
				ans.EulerAnglesToAxesZXY(X, Y, Z);
			}
		}

		float ComputeHeadingFromVector(const NiPoint3& V)
		{
			return NiFastATan2(V.x, V.y);
		}

		float ComputePitchFromVector(const NiPoint3& V)
		{
			return NiFastATan2(V.z, std::sqrt(V.x * V.x + V.y * V.y));
		}

		void ComputeRotationBetweenDirectionVectors(const NiPoint3& A, const NiPoint3& B, NiMatrix3& ans)
		{
			auto      C = A.UnitCross({ 0, 0, 1 });
			auto      D = B.UnitCross({ 0, 0, 1 });
			NiMatrix3 M2(C, A, C.Cross(A));
			NiMatrix3 M1 = NiMatrix3(D, B, D.Cross(B)).Transpose();
			ans = M1 * M2;
		}

		float ComputeHeadingOffsetBetweenVectors(const NiPoint3& from, const NiPoint3& to)
		{
			float to_heading = ComputeHeadingFromVector(to);
			float from_heading = ComputeHeadingFromVector(from);
			return impl::normalize_angle_single(to_heading - from_heading);
		}

		float ComputePitchOffsetBetweenVectors(const NiPoint3& from, const NiPoint3& to)
		{
			float to_pitch = ComputePitchFromVector(to);
			float from_pitch = ComputePitchFromVector(from);
			return impl::normalize_angle_single(to_pitch - from_pitch);
		}

		void ComputeTimeAndDistanceToStop(float speed, float accel, float& time, float& distance)
		{
			if (accel <= 0) {
				time = std::numeric_limits<float>::max();
				distance = std::numeric_limits<float>::max();
			} else {
				time = std::abs(speed) / accel;
				distance = speed * 0.5f * fabs(speed) / accel;
			}
		}

		void DampenMovementVector(const MovementVector& MV_cur, const MovementVector& MV_target, float acc_denorm, float decel_denorm, float dtime, MovementVector& ans)
		{
			using func_t = void(const MovementVector& MV_cur, const MovementVector& MV_target, float acc_denorm, float decel_denorm, float dtime, MovementVector& ans);
			REL::Relocation<func_t> func{ RELOCATION_ID(89353, 91819) };
			return func(MV_cur, MV_target, acc_denorm, decel_denorm, dtime, ans);
		}

		void DampenMovementVector(const MovementVector& MV_cur, const MovementVector& MV_target, float acc_denorm, float decel_denorm, float max_rot_speed_denorm, float dtime, MovementVector& ans)
		{
			using func_t = void(const MovementVector& MV_cur, const MovementVector& MV_target, float acc_denorm, float decel_denorm, float max_rot_speed_denorm, float dtime, MovementVector& ans);
			REL::Relocation<func_t> func{ RELOCATION_ID(89354, 91820) };
			return func(MV_cur, MV_target, acc_denorm, decel_denorm, max_rot_speed_denorm, dtime, ans);
		}

		float DenormalizeAcceleration(float acc_norm, const Movement::MaxSpeeds& max_speeds)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			return acc_norm * max_speeds.speeds[DIR::kForward][MINMAX::kRun];
		}

		float DenormalizeAngleAcceleration(float angle_accel_norm, const Movement::MaxSpeeds& max_speeds)
		{
			return angle_accel_norm * max_speeds.rotateWhileMovingRun;
		}

		float DenormalizeRotateWhileMoving(float speed_norm, const Movement::MaxSpeeds& max_speeds)
		{
			return speed_norm * max_speeds.rotateWhileMovingRun * 0.5f;
		}

		float DenormalizeRotationSpeed(float rotspeed_norm, const Movement::MaxSpeeds& max_speeds)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			float rotspeed_dir = rotspeed_norm >= 0 ? 1.0f : -1.0f;
			float rotspeed_abs = std::abs(rotspeed_norm);

			float min = max_speeds.speeds[DIR::kRotations][MINMAX::kWalk];
			float max = max_speeds.speeds[DIR::kRotations][MINMAX::kRun];

			if (rotspeed_abs <= 1)
				return rotspeed_norm * min;
			else if (rotspeed_abs > 2)
				return (rotspeed_dir * max) * (rotspeed_abs - 1);
			else
				return ((2 - rotspeed_abs) * min + (rotspeed_abs - 1) * max) * rotspeed_dir;
		}

		float DenormalizeSpeed(float speed_norm, const Movement::MaxSpeeds& maxspeeds)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			float min = maxspeeds.speeds[DIR::kForward][MINMAX::kWalk];
			float max = maxspeeds.speeds[DIR::kForward][MINMAX::kRun];

			if (speed_norm <= 1)
				return speed_norm * min;

			if (speed_norm > 2)
				return (speed_norm - 1) * max;

			return (2 - speed_norm) * min + (speed_norm - 1) * max;
		}

		void EstimateTransitionDistance(float speed, float max_speed, float acc, float decel, float& ans_1, float& ans_2)
		{
			float speed_delta = max_speed - speed;
			if (speed_delta < 0)
				acc = decel;
			if (acc <= 0) {
				ans_2 = std::numeric_limits<float>::max();
				ans_1 = std::numeric_limits<float>::max();
			} else {
				ans_2 = std::abs(speed_delta) / acc;
				ans_1 = (speed_delta * 0.5f + speed) * (fabs(speed_delta) / acc);
			}
		}

		float NormalizeAcceleration(float acc_denorm, const Movement::MaxSpeeds& max_speeds)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			return acc_denorm / max_speeds.speeds[DIR::kForward][MINMAX::kRun];
		}

		float NormalizeAngleAcceleration(float angle_accel_denorm, const Movement::MaxSpeeds& max_speeds)
		{
			return angle_accel_denorm / max_speeds.rotateWhileMovingRun;
		}

		float NormalizeRotateWhileMoving(float speed_denorm, const Movement::MaxSpeeds& max_speeds)
		{
			return (speed_denorm * 2) / max_speeds.rotateWhileMovingRun;
		}

		float NormalizeRotationSpeed(float rotspeed_denorm, const Movement::MaxSpeeds& max_speeds)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			float rotspeed_dir = rotspeed_denorm >= 0 ? 1.0f : -1.0f;
			float rotspeed_abs = std::abs(rotspeed_denorm);

			float min = max_speeds.speeds[DIR::kRotations][MINMAX::kWalk];
			float max = max_speeds.speeds[DIR::kRotations][MINMAX::kRun];

			if (rotspeed_abs <= min) {
				return min > 0 ? rotspeed_denorm / min : 0;
			} else if (rotspeed_abs < max) {
				float d = max - min;
				return d <= 0 ? min * rotspeed_dir : ((rotspeed_abs - min) / d + 1) * rotspeed_dir;
			} else {
				return max <= 0 ? 0 : (rotspeed_abs / max + 1) * rotspeed_dir;
			}
		}

		float NormalizeSpeed(float speed_denorm, const Movement::MaxSpeeds& maxspeeds)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			float min = maxspeeds.speeds[DIR::kForward][MINMAX::kWalk];
			float max = maxspeeds.speeds[DIR::kForward][MINMAX::kRun];

			if (speed_denorm <= min) {
				return min > 0 ? speed_denorm / min : 1;
			} else if (speed_denorm < max) {
				float d = max - min;
				return d <= 0 ? min : (speed_denorm - min) / d + 1.0f;
			} else {
				return max <= 0 ? 1 : (speed_denorm / max) + 1.0f;
			}
		}

		float ComputeAngleBetweenVectors(const NiPoint3& from, const NiPoint3& to)
		{
			float dot_product = from.Dot(to);
			if (dot_product <= -1.0f)
				return NI_PI;
			if (dot_product >= 1.0f)
				return 0.0f;
			return std::acosf(dot_product);
		}

		float ComputeCurrentSpeedForNormalizedDirection(NiPoint3 direction_normalized, const Movement::MaxSpeeds& max_speeds)
		{
			float max_speed_walk;
			float max_speed_run;
			return ComputeCurrentSpeedForNormalizedDirection(std::move(direction_normalized), max_speeds, max_speed_walk, max_speed_run);
		}

		float ComputeCurrentSpeedForNormalizedDirection(NiPoint3 direction_normalized, const Movement::MaxSpeeds& max_speeds, float& max_speed_walk, float& max_speed_run)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			float dir_len = direction_normalized.Unitize();
			if (dir_len <= 0) {
				max_speed_walk = max_speeds.speeds[DIR::kForward][MINMAX::kWalk];
				max_speed_run = max_speeds.speeds[DIR::kForward][MINMAX::kRun];
				return 0;
			}

			float k1, k2;
			if (dir_len >= 2) {
				k1 = 1;
				k2 = 0;
			} else if (dir_len <= 1) {
				k1 = 0;
				k2 = dir_len;
			} else {
				k1 = dir_len - 1;
				k2 = 1 - k1;
			}

			float dir_Y_abs = std::abs(direction_normalized.y);
			float dir_X_abs = std::abs(direction_normalized.x);

			DIR dir_forward = (direction_normalized.y < 0) ? DIR::kBack : DIR::kForward;
			DIR dir_leftright = (direction_normalized.x >= 0) ? DIR::kRight : DIR::kLeft;

			float v17 = (max_speeds.speeds[dir_forward][MINMAX::kWalk] * k2 + k1 * max_speeds.speeds[dir_forward][MINMAX::kRun]) * dir_Y_abs;
			float v18 = (max_speeds.speeds[dir_leftright][MINMAX::kWalk] * k2 + k1 * max_speeds.speeds[dir_leftright][MINMAX::kRun]) * dir_X_abs;
			float v14 = 1.0f / (dir_Y_abs + dir_X_abs);

			max_speed_walk = (max_speeds.speeds[dir_leftright][MINMAX::kWalk] * dir_X_abs + max_speeds.speeds[dir_forward][MINMAX::kWalk] * dir_Y_abs) * v14;
			max_speed_run = (max_speeds.speeds[dir_leftright][MINMAX::kRun] * dir_X_abs + max_speeds.speeds[dir_forward][MINMAX::kRun] * dir_Y_abs) * v14;

			return (v17 + v18) * v14;
		}

		float ComputeCurrentSpeedForDirection(NiPoint3 V, const Movement::MaxSpeeds& max_speeds)
		{
			float V_len = V.Unitize();
			return ComputeCurrentSpeedForDirection(V, V_len, max_speeds);
		}

		float ComputeCurrentSpeedForDirection(const NiPoint3& V, float speed_denorm, const Movement::MaxSpeeds& max_speeds)
		{
			using DIR = Movement::SPEED_DIRECTION;
			using MINMAX = Movement::MaxSpeeds;

			DIR dir_forward = (V.y < 0) ? DIR::kBack : DIR::kForward;
			DIR dir_leftright = (V.x >= 0) ? DIR::kRight : DIR::kLeft;

			float abs_V_X = fabs(V.x);
			float abs_V_Y = fabs(V.y);
			float v6 = abs_V_Y + abs_V_X;
			if (v6 <= 0.0f)
				return 0.0f;

			float v7 = std::min(abs_V_X * speed_denorm, max_speeds.speeds[dir_leftright][MINMAX::kRun]);
			float v10 = std::min(abs_V_Y * speed_denorm, max_speeds.speeds[dir_forward][MINMAX::kRun]);

			return (v10 + v7) / v6;
		}

		bool CanStrafe(const Movement::MaxSpeeds& max_speeds)
		{
			return max_speeds.speeds[Movement::SPEED_DIRECTION::kLeft][Movement::MaxSpeeds::kWalk] > 0.0f &&
			       max_speeds.speeds[Movement::SPEED_DIRECTION::kLeft][Movement::MaxSpeeds::kRun] > 0.0f &&
			       max_speeds.speeds[Movement::SPEED_DIRECTION::kRight][Movement::MaxSpeeds::kWalk] > 0.0f &&
			       max_speeds.speeds[Movement::SPEED_DIRECTION::kRight][Movement::MaxSpeeds::kRun] > 0.0f;
		}

		void ComputeDirectionVector(const NiPoint3& angles, const NiPoint3& movement_rotation, NiPoint3& ans, bool anglesHeadingOnly)
		{
			if (angles.x == 0.0f && angles.y == 0.0f && movement_rotation.x == 0.0f && movement_rotation.y == 0.0f) {
				float Z = angles.z + movement_rotation.z;
				ans = { std::sin(Z), std::cos(Z), 0 };
			} else {
				RE::NiMatrix3 angles_1_M;
				if (anglesHeadingOnly) {
					MovementUtils::ComputeRotationFromEulerAngles(angles.z, 0, 0, angles_1_M);
				} else {
					MovementUtils::ComputeRotationFromEulerAngles(angles.z, angles.x, angles.y, angles_1_M);
				}

				RE::NiMatrix3 movement_rotation_M;
				MovementUtils::ComputeRotationFromEulerAngles(movement_rotation.z, movement_rotation.x, movement_rotation.y, movement_rotation_M);
				auto M = angles_1_M * movement_rotation_M;
				ans = M * RE::NiPoint3(0, 1, 0);
			}
		}
	}
}
