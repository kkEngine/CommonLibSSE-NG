#include "RE/I/IMovementHandlerAgent.h"

namespace RE
{
	const BSFixedString& IMovementHandlerAgent::QPipelineStage()
	{
		return *REL::Relocation<BSFixedString*>(REL::ID(412320));
	}

	IMovementHandlerAgent::IMovementHandlerAgent()
	{
		stl::emplace_vtable(this);
	}
}
