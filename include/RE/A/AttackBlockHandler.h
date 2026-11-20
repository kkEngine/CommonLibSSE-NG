#pragma once

#include "RE/H/HeldStateHandler.h"

namespace RE
{
	struct AttackBlockHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_AttackBlockHandler;

		enum class AttackType : std::uint8_t
		{
			kRight = 0,
			kLeft = 1,
			kDual = 2
		};

		~AttackBlockHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                  // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
		void UpdateHeldStateActive(const ButtonEvent* a_event) override;                // 05
		void SetHeldStateActive(bool a_flag) override;                                  // 06

		// members
		// AE 1.7.99 put 0x40 bytes in front and 0x3C bytes before the flags (offsets checked in its vfuncs)
		std::uint8_t  unk18[0x40];                 // 18
		std::uint32_t heldTimeMs;                  // 18
		std::uint32_t unk1C;                       // 1C
		BSFixedString controlID;                   // 20
		AttackType    attackType;                  // 28
		std::uint8_t  pad29;                       // 29
		std::uint16_t pad2A;                       // 2A
		std::uint8_t  attackCount;                 // 2C
		float         initialPowerAttackDelay;     // 30
		std::uint32_t pad34;                       // 34
		float         subsequentPowerAttackDelay;  // 38
		std::uint8_t  unk7C[0x3C];                 // 7C
		bool          ignore;                      // 40
		bool          unk41;                       // 41
		bool          heldLeft;                    // 42
		bool          heldRight;                   // 43
		std::uint32_t unk44;                       // 44
	};
	static_assert(offsetof(AttackBlockHandler, heldTimeMs) == 0x58);
	static_assert(offsetof(AttackBlockHandler, controlID) == 0x60);
	static_assert(offsetof(AttackBlockHandler, ignore) == 0xB8);
	static_assert(sizeof(AttackBlockHandler) == 0xC0);
}
