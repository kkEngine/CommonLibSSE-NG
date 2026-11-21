#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	bool hkbTransitionEffect::ComputeSelfTransitionMode(const hkbContext& ctx, hkbGenerator* gen)
	{
		using func_t = decltype(&hkbTransitionEffect::ComputeSelfTransitionMode);
		REL::Relocation<func_t> func{ RELOCATION_ID(58829, 59492) };
		return func(this, ctx, gen);
	}

	hkbTransitionEffect::EventMode hkbTransitionEffect::GetEventMode() const
	{
		if (eventMode != EventMode::EVENT_MODE_DEFAULT)
			return eventMode;
		else
			return defaultEventMode;
	}
}
