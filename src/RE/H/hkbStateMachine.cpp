#include "RE/H/hkbStateMachine.h"
#include "RE/H/hkMap.h"

namespace RE
{
	hkbStateMachine::TransitionInfo::TransitionInfo(int32_t a_eventId, int32_t a_toStateId, hkbTransitionEffect* a_transition, hkbCondition* condition) :
		triggerInterval(), initiateInterval(), transition(a_transition), condition(condition), eventId(a_eventId), toStateId(a_toStateId), fromNestedStateId(), toNestedStateId(), priority(), flags()
	{
	}

	//hkbStateMachine::~hkbStateMachine()
	//{
	//	for (auto& transition : activeTransitions) {
	//		transition.effect->RemoveReference();
	//	}
	//
	//	for (auto state : states) {
	//		state->RemoveReference();
	//	}
	//}

	void hkbStateMachine::AddState(int32_t stateId, hkbGenerator* generator, char const* stateName)
	{
		REL::Relocation<void(hkbStateMachine*, int32_t, hkbGenerator*, char const*)> func(RELOCATION_ID(58706, 59367));
		return func(this, stateId, generator, stateName);
	}

	int32_t hkbStateMachine::AddState(RE::hkbGenerator* generator, const char* stateName)
	{
		int32_t stateID = GetUnusedStateId();
		AddState(stateID, generator, stateName);
		return stateID;
	}

	hkbStateMachine::TransitionInfo* hkbStateMachine::AddTransition(int32_t eventId, int32_t fromStateId, int32_t toStateId, hkbTransitionEffect* transition, hkbCondition* condition)
	{
		auto& from_state = GetStateInfoById(fromStateId);
		if (!from_state.transitions)
			from_state.transitions = make_hkref<hkbStateMachine::TransitionInfoArray>();

		return AddTransitionInternal(eventId, toStateId, transition, condition, from_state.transitions->transitions);
	}

	hkbStateMachine::TransitionInfo* hkbStateMachine::AddTransitionInternal(int32_t eventId, int32_t toStateId, hkbTransitionEffect* transition, hkbCondition* condition, hkArray<TransitionInfo>& transitions)
	{
		transitions.push_back({ eventId, toStateId, transition, condition });
		return &transitions.back();
	}

	uint16_t hkbStateMachine::GetCurrentStateIndex() const
	{
		return currentStateIndexAndEntered >> 1;
	}

	hkbStateMachine* hkbStateMachine::GetNestedStateMachineClone(const hkbBehaviorGraph& behaviorGraph, int32_t stateIndex)
	{
		if (auto nodeTemplate = GetNestedStateMachineTemplate(behaviorGraph, stateIndex)) {
			return static_cast<hkbStateMachine*>(behaviorGraph.getNodeClone(nodeTemplate));
		} else {
			return nullptr;
		}
	}

	hkbBehaviorGraph::StateMachineInfo* hkbStateMachine::GetNestedStateMachineInfo(const hkbBehaviorGraph& behaviorGraph, int32_t stateIndex)
	{
		if (auto global_transition_data = behaviorGraph.globalTransitionData.get()) {
			auto     this_template = static_cast<hkbStateMachine*>(behaviorGraph.getNodeTemplate(this));
			uint64_t statemachine_info_ind = global_transition_data->stateMachineTemplateToIndexMap.getWithDefault(this_template, -1);
			if (statemachine_info_ind >= 0) {
				if (auto childStateMachineInfoIndices = global_transition_data->stateMachineInfos[static_cast<uint32_t>(statemachine_info_ind)].childStateMachineInfoIndices) {
					if (auto statemachine_infos_ind = (*childStateMachineInfoIndices)[stateIndex]; statemachine_infos_ind != -1) {
						return &global_transition_data->stateMachineInfos[statemachine_infos_ind];
					}
				}
			}
		}

		return nullptr;
	}

	hkbStateMachine* hkbStateMachine::GetNestedStateMachineTemplate(const hkbBehaviorGraph& behaviorGraph, int32_t stateIndex)
	{
		if (auto info = GetNestedStateMachineInfo(behaviorGraph, stateIndex)) {
			return info->stateMachineTemplate;
		} else {
			return nullptr;
		}
	}

	int32_t hkbStateMachine::GetStateIndex(int32_t stateID) const
	{
		if (stateID)
			return static_cast<int32_t>(stateIDToIndexMap->getWithDefault(stateID, -1));
		if (states.empty() || states[0]->id != 0)
			return -1;
		return 0;
	}

	hkbStateMachine::StateInfo& hkbStateMachine::GetStateInfoById(int32_t stateId)
	{
		return *states[GetStateIndex(stateId)];
	}

	const hkbStateMachine::StateInfo& hkbStateMachine::GetStateInfoById(int32_t stateId) const
	{
		return *states[GetStateIndex(stateId)];
	}

	hkbStateMachine::StateInfo& hkbStateMachine::GetStateInfoByIndex(int32_t stateIndex)
	{
		return *states[stateIndex];
	}

	const hkbStateMachine::StateInfo& hkbStateMachine::GetStateInfoByIndex(int32_t stateIndex) const
	{
		return *states[stateIndex];
	}

	int32_t hkbStateMachine::GetUnusedStateId() const
	{
		int32_t i = 0;
		while (GetStateIndex(i) != -1) ++i;
		return i;
	}

	hkbStateMachine::StateInfo::StateInfo()
	{
		stl::emplace_vtable(this);
	}

	hkbStateMachine::StateInfo::~StateInfo()
	{
		for (auto listener : listeners) {
			listener->RemoveReference();
		}
	}
}
