#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSTempEffect;

	class BGSDecalNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSDecalNode;
		inline static auto           Ni_RTTI = NiRTTI_BGSDecalNode;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	BSTArray<NiPointer<BSTempEffect>> decals;    /* 00 */ \
	bool                              isSkinned; /* 18 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		~BGSDecalNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                            // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;   // 17
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D
		void OnVisible(NiCullingProcess& a_process) override;  // 34

		// add
		virtual std::uint8_t Unk_3E();                                               // 3E - { return 1; }
		virtual void         AttachDecal(BSTempEffect* a_decal, bool a_firstAvail);  // 3F

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128);
		}

		// members
		RUNTIME_DATA_CONTENT  // 128, 150
	};
	static_assert(sizeof(BGSDecalNode) == 0x148);
}
#undef RUNTIME_DATA_CONTENT
