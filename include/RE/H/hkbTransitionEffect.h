#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbTransitionEffect : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbTransitionEffect;
		inline static constexpr auto VTABLE = VTABLE_hkbTransitionEffect;

		// These modes determine the behavior when the to-generator is already active when the transition begins.
		enum SelfTransitionMode : uint8_t
		{
			// If the to-generator is cyclic, it will be continued without interruption.  Otherwise, it will be
			// blended with itself using the echo feature.
			SELF_TRANSITION_MODE_CONTINUE_IF_CYCLIC_BLEND_IF_ACYCLIC,

			// Continue the to-generator without interruption.
			SELF_TRANSITION_MODE_CONTINUE,

			// Reset the to-generator to the beginning.
			SELF_TRANSITION_MODE_RESET,

			// Reset the to-generator to the beginning using the echo feature to blend.
			SELF_TRANSITION_MODE_BLEND,
		};

		enum EventMode : uint8_t
		{
			// Apply the event mode from m_defaultEventMode.
			EVENT_MODE_DEFAULT,

			// Don't ignore the events of either the from-generator or the to-generator.
			EVENT_MODE_PROCESS_ALL,

			// Ignore all events sent by or to the from-generator.
			EVENT_MODE_IGNORE_FROM_GENERATOR,

			// Ignore all events sent by or to the to-generator.
			EVENT_MODE_IGNORE_TO_GENERATOR,
		};

		hkbTransitionEffect() { stl::emplace_vtable(this); }
		~hkbTransitionEffect() override = default;  // 00

		// override (hkbNode)
		bool IsTransitionEffect() const { return true; }  // 13

		// add
		virtual bool  IsDone() = 0;                                 // 1C
		virtual void  SetFromGenerator(hkbGenerator* fromGen) = 0;  // 1D
		virtual void  SetToGenerator(hkbGenerator* toGen) = 0;      // 1E
		virtual float GetFromGeneratorBlendOutTime() = 0;           // 1F
		virtual float GetToGeneratorBlendInTime() = 0;              // 20

		bool      ComputeSelfTransitionMode(const hkbContext& ctx, hkbGenerator* gen);
		EventMode GetEventMode() const;

		// members
		SelfTransitionMode selfTransitionMode{ SelfTransitionMode ::SELF_TRANSITION_MODE_CONTINUE_IF_CYCLIC_BLEND_IF_ACYCLIC };  // 48 - What to do if the to-generator is already active when the transition activates it
		EventMode          eventMode;                                                                                            // 49 - How to process the events of the from- and to-generators.
		EventMode          defaultEventMode{ EventMode ::EVENT_MODE_IGNORE_FROM_GENERATOR };                                     // 4A - defaultEventMode?
		char               pad4B[5];                                                                                             // 4B
	};
	static_assert(sizeof(hkbTransitionEffect) == 0x50);
}
