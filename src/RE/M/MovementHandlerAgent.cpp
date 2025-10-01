#include "RE/M/MovementHandlerAgent.h"

namespace RE
{
	MovementHandlerAgent::MovementHandlerAgent() :
		MovementAgent()
	{
		stl::emplace_vtable(this);
	}

	IPipelineStageInterface* MovementHandlerAgent::GetPipelineStageInterface(const BSFixedString& a_stage)
	{
		if (a_stage == QPipelineStage())
			return this;
		else
			return nullptr;
	}

	const BSFixedString& MovementHandlerAgent::GetHandlerAgentName() const
	{
		return GetName();
	}
}
