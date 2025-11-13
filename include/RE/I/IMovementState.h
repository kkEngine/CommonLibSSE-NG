#pragma once

#include "RE/B/BSPathing.h"
#include "RE/I/IMovementInterface.h"
#include "RE/M/Movement.h"
#include "RE/M/MovementParameters.h"
#include "RE/N/NiMatrix3.h"
#include "RE/P/PathingPoint.h"

namespace RE
{
	class NiMatrix3;
	class NiPoint3;
	class NiTransform;

	class IMovementState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementState;

		// same as hkpCharacterStateType
		enum CHARACTER_STATE : uint32_t
		{
			ON_GROUND = 0,
			JUMPING = 1,
			IN_AIR = 2,
			CLIMBING = 3,
			FLYING = 4,
			USER_STATE_0 = 5,
			USER_STATE_1 = 6,
			USER_STATE_2 = 7,
			USER_STATE_3 = 8,
			USER_STATE_4 = 9,
			USER_STATE_5 = 10,

			MAX_STATE_ID = 11,
		};

		~IMovementState() override = default;  // 00

		// add
		virtual std::uint32_t        DoGetNumericID() const = 0;                                            // 01
		virtual void                 DoGetPathingLocation(BSPathingLocation& a_pathLoc) const = 0;          // 02
		virtual void                 DoGetLocation(NiPoint3& a_pos) const = 0;                              // 03
		virtual void                 DoGetEulerAngles(NiPoint3& a_angles) const = 0;                        // 04
		virtual float                DoGetMovementSpeed() const = 0;                                        // 05
		virtual float                DoGetRotationSpeed() const = 0;                                        // 06
		virtual void                 DoGetMovementRotation(NiPoint3& a_rotation) const = 0;                 // 07
		virtual bool                 DoGetCurrentMaxSpeeds(Movement::MaxSpeeds& a_maxSpeeds) const = 0;     // 08
		virtual float                DoGetMovementRadius() const = 0;                                       // 09
		virtual float                DoGetMovementWidth() const = 0;                                        // 0A
		virtual float                DoGetMovementLength() const = 0;                                       // 0B
		virtual float                DoGetMovementHeight() const = 0;                                       // 0C
		virtual float                DoGetLookingHeight() const = 0;                                        // 0D
		virtual bool                 DoMakeDefaultMovementParameters(MovementParameters& a_newParams) = 0;  // 0E
		virtual IMovementParameters* DoGetDefaultMovementParameters() const = 0;                            // 0F
		virtual bool                 DoGetCurSpeeds(Movement::CurrentSpeeds& a_curSpeed) const = 0;         // 10
		virtual CHARACTER_STATE      DoGetCharacterState() const = 0;                                       // 11
		virtual bool                 IsRiddenByPlayer() const = 0;                                          // 12
		virtual bool                 DoGetUseVelocityObstacles() const = 0;                                 // 13

		bool  CanStrafe() const;
		void  GetCCRotation(NiMatrix3& ans) const;
		void  GetCCTransform(NiTransform& ans) const;
		bool  GetCurrentWalkRunPercent(float& ans_walk, float& ans_run) const;  // 88497
		void  GetDirectionAngles(NiPoint3& ans) const;
		void  GetDirectionVector(NiPoint3& ans, bool anglesHeadingOnly = false) const;
		float GetMaxSpeed() const;
		float GetMinSpeed() const;
		float GetMovementHeading() const;
		float DenormalizeAcceleration(float acc_norm) const;
		float DenormalizeAngleAcceleration(float angle_accel_norm) const;
		float DenormalizeRotateWhileMoving(float speed_norm) const;
		float DenormalizeRotationSpeed(float rotspeed_norm) const;
		float DenormalizeSpeed(float speed_norm) const;
		float NormalizeAcceleration(float acc_denorm) const;
		float NormalizeAngleAcceleration(float angle_accel_denorm) const;
		float NormalizeRotateWhileMoving(float speed_denorm) const;
		float NormalizeRotationSpeed(float rotspeed_denorm) const;
		float NormalizeSpeed(float speed_denorm) const;
	};
	static_assert(sizeof(IMovementState) == 0x8);
}
