#pragma once

#include "RE/N/NiPSysModifierFloatCtlr.h"

namespace RE
{
	class NiPSysFieldAttenuationCtlr : public NiPSysModifierFloatCtlr
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysFieldAttenuationCtlr;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysFieldAttenuationCtlr;

		~NiPSysFieldAttenuationCtlr() override;  // 00

		// override (NiPSysModifierFloatCtlr)
		const NiRTTI* GetRTTI() const override;                                            // 02
		NiObject*     CreateClone([[maybe_unused]] NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;                             // 18
		void          LinkObject(NiStream& a_stream) override;                             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                    // 1A
		void          SaveBinary(NiStream& a_stream) override;                             // 1B
		bool          IsEqual(NiObject* a_object) override;                                // 1C
		bool          IsValidInterpolatorTarget(NiObject* a_object) const override;        // 3C
		void          GetControlledValue(float& value) const override;                     // 3E
		void          SetControlledValue(float value) override;                            // 3F
	};
	static_assert(sizeof(NiPSysFieldAttenuationCtlr) == 0x60);
}
