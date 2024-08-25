#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiPSysGrowFadeModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysGrowFadeModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysGrowFadeModifier;

		~NiPSysGrowFadeModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25

		// members
		float    growTime;        // 30
		uint16_t growGeneration;  // 34
		float    fadeTime;        // 38
		uint16_t fadeGeneration;  // 3C
		float    baseScale;       // 40
	};
	static_assert(sizeof(NiPSysGrowFadeModifier) == 0x48);
}
