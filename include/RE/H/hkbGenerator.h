#pragma once

#include "RE/H/hkbNode.h"

namespace RE
{
	struct hkbGeneratorOutput;
	struct hkbNodeInfo;

	class hkbGenerator : public hkbNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbGenerator;

		hkbGenerator() { stl::emplace_vtable(this); }
		~hkbGenerator() override = default;  // 00

		HK_HEAP_REDEFINE_NEW();

		// override (hkbNode)
		bool IsGenerator() const override { return 1; };  // 15 - { return 1; }

		// add
		virtual void Generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const = 0;  // 17
		virtual bool CanRecycleOutput() const { return false; }                                                                                                              // 18
		virtual void UpdateSync(const hkbContext& a_context, hkbNodeInfo& info) = 0;                                                                                         // 19
		virtual void SetLocalTime([[maybe_unused]] float time) {};                                                                                                           // 1A
		virtual void StartEcho() {};                                                                                                                                         // 1B
	};
	static_assert(sizeof(hkbGenerator) == 0x48);
}
