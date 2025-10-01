#pragma once

#include "RE/B/BSTSingleton.h"
#include "RE/I/IMovementState.h"

namespace RE
{
	struct NullMovementState : public IMovementState, public BSTSingletonImplicit<NullMovementState>
	{
		static NullMovementState& QInstance();

		~NullMovementState() override = default;

		// override (IMovementState)
		std::uint32_t        DoGetNumericID() const override { return 0; };                                                // 01
		void                 DoGetPathingLocation(BSPathingLocation& a_pathLoc) const override {};                         // 02
		void                 DoGetLocation(NiPoint3& a_pos) const override;                                                // 03
		void                 DoGetEulerAngles(NiPoint3& a_angles) const override;                                          // 04
		float                DoGetMovementSpeed() const override { return 0; };                                            // 05
		float                DoGetRotationSpeed() const override { return 0; };                                            // 06
		void                 DoGetMovementRotation(NiPoint3& a_rotation) const override {};                                // 07
		bool                 DoGetCurrentMaxSpeeds(Movement::MaxSpeeds& a_maxSpeeds) const override { return false; };     // 08
		float                DoGetMovementRadius() const override { return 0; };                                           // 09
		float                DoGetMovementWidth() const override { return 0; };                                            // 0A
		float                DoGetMovementLength() const override { return 0; };                                           // 0B
		float                DoGetMovementHeight() const override { return 0; };                                           // 0C
		float                DoGetLookingHeight() const override { return 0; };                                            // 0D
		bool                 DoMakeDefaultMovementParameters(MovementParameters& a_newParams) override { return false; };  // 0E
		IMovementParameters* DoGetDefaultMovementParameters() const override;                                              // 0F
		bool                 DoGetCurSpeeds(Movement::CurrentSpeeds& a_curSpeed) const override { return false; };         // 10
		CHARACTER_STATE      DoGetCharacterState() const override { return CHARACTER_STATE::ON_GROUND; };                  // 11
		bool                 IsRiddenByPlayer() const override { return false; };                                          // 12
		bool                 DoGetUseVelocityObstacles() const override { return false; };                                 // 13
	};
	static_assert(sizeof(NullMovementState) == 0x8);
}
