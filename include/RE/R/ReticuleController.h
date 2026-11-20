#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	struct ReticuleController
	{
	public:
		static ReticuleController& GetSingleton()
		{
			REL::Relocation<ReticuleController*> singleton{ REL::ID(380335) };
			return *singleton;
		}

		// members
		BSTSmallArray<MagicSystem::CastingSource> data;        // 00
		std::uint64_t                             nextUpdate;  // 18
	};
	static_assert(sizeof(ReticuleController) == 0x20);
}
