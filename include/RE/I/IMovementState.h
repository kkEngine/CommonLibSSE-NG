#pragma once

#include "RE/I/IMovementInterface.h"
#include "RE/M/MovementParameters.h"

namespace RE
{
	class NiPoint3;

	class IMovementState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementState;

		~IMovementState() override;  // 00

		// add
		virtual FormID              Unk_01(void) = 0;                                 // 01
		virtual void                Unk_02(void) = 0;                                 // 02
		virtual void                GetPosition(NiPoint3* a_out) = 0;                 // 03
		virtual void                GetRotation(NiPoint3* a_out) = 0;                 // 04
		virtual float               DoGetMovementSpeed() = 0;                         // 05
		virtual float               DoGetRotationSpeed() = 0;                         // 06
		virtual void                Unk_07(NiPoint3* a_out) = 0;                      // 07 - used by IsMoving; possibly a velocity getter?
		virtual bool                Unk_08(std::uint32_t a_unk) = 0;                  // 08
		virtual float               DoGetMovementRotation(NiPoint3& a_rotation) = 0;  // 09
		virtual void                Unk_0A(void) = 0;                                 // 0A
		virtual void                Unk_0B(void) = 0;                                 // 0B
		virtual float               GetComputedHeight() = 0;                          // 0C
		virtual float               Unk_0D(void) = 0;                                 // 0D - returns computed height * 0.75
		virtual bool                Unk_0E(MovementParameters* a_newParams) = 0;      // 0E - decrements the refcount on p, and then replaces it with a new MovementParameters*
		virtual MovementParameters* Unk_0F(void) = 0;                                 // 0F
		virtual void                Unk_10(void) = 0;                                 // 10
		virtual void                Unk_11(void) = 0;                                 // 11
		virtual void                Unk_12(void) = 0;                                 // 12
		virtual bool                Unk_13(void) = 0;                                 // 13 - checks flags in the actor's race
	};
	static_assert(sizeof(IMovementState) == 0x8);
}
