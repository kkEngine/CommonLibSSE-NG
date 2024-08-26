#pragma once

#include "RE/H/hkbStateMachine.h"

namespace RE
{
	class hkbStateMachineInternalState : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateMachineInternalState;

		~hkbStateMachineInternalState() override;  // 00

		hkArray<hkbStateMachine::ActiveTransitionInfo>  activeTransitions;                // 10
		hkArray<uint8_t>                                transitionFlags;                  // 20
		hkArray<uint8_t>                                wildcardTransitionFlags;          // 30
		hkArray<hkbStateMachine::DelayedTransitionInfo> delayedTransitions;               // 40
		float                                           timeInState;                      // 50
		float                                           lastLocalTime;                    // 54
		int32_t                                         currentStateId;                   // 58
		int32_t                                         previousStateId;                  // 5C
		int32_t                                         nextStartStateIndexOverride;      // 60
		bool                                            stateOrTransitionChanged;         // 64
		bool                                            echoNextUpdate;                   // 65
		bool                                            hasEventlessWildcardTransitions;  // 66
	};
	static_assert(sizeof(hkbStateMachineInternalState) == 0x68);
}
