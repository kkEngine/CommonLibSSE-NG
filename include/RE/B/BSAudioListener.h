#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	// Adapted from Fallout3 RE. May contain errors.
	class BSAudioListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSAudioListener;

		BSAudioListener();
		virtual ~BSAudioListener();  // 00

		// Add
		virtual void      Unk_01();                                                           // 01
		virtual void      SetOriginWorldPos(NiPoint3& a_arPos);                               // 02
		virtual NiPoint3* GetOriginWorldPos();                                                // 03
		virtual void      UpdatePositionAndOrientation();                                     // 04
		virtual void      SetFrontAndTopOrientation(NiPoint3& a_arTop, NiPoint3& a_arFront);  // 05
		virtual uint32_t  GetUnk06();                                                         // 06
		virtual uint32_t  GetUnk07();                                                         // 07
		virtual void      SetVelocity(NiPoint3& a_arVelocity);                                // 08
		virtual void      SetFlt044(float);                                                   // 09
		virtual void      SetEnvironmentType(uint32_t a_aeType);                              // 0A
		virtual uint32_t  GetEnvironmentType();                                               // 0B
		virtual void      SetRolloffFactor(float a_afValue);                                  // 0C

		// members
		NiPoint3 originWorldPos;   // 08
		uint32_t unk14;            // 14
		uint32_t unk18;            // 18
		uint32_t unk1C;            // 1C
		uint32_t unk20;            // 20
		uint32_t unk24;            // 24
		uint32_t unk28;            // 28
		NiPoint3 velocity;         // 2C
		uint32_t sysTime;          // 38
		float    flt3C;            // 3C
		float    rollOffFactor;    // 40
		float    flt44;            // 44
		uint32_t environmentType;  // 48
		uint32_t pad4C;            // 4C
	};
	static_assert(sizeof(BSAudioListener) == 0x50);
}
