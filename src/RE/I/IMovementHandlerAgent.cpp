#include "RE/I/IMovementHandlerAgent.h"

namespace RE
{
	const BSFixedString& IMovementHandlerAgent::QPipelineStage()
	{
		return *REL::Relocation<BSFixedString*>(RELOCATION_ID(525843, 412320));
	}

	IMovementHandlerAgent::IMovementHandlerAgent()
	{
		stl::emplace_vtable(this);
	}
}
