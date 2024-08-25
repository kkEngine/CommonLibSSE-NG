#pragma once

#include "RE/I/IPathFollowerState.h"

namespace RE
{
	class IPathFollowerAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPathFollowerAction;

		virtual ~IPathFollowerAction();  // 00

		// add
		virtual bool OnStartSlowingDown(IPathFollowerState::Context& a_context, float a_pathParameter, float& a_outPathParameter);  // 01
		virtual bool OnStopSlowingDown(IPathFollowerState::Context& a_context, float& a_outPathSpeed) = 0;                          // 02
		virtual bool OnStopMovingAlongPath(IPathFollowerState::Context& a_context, float& a_outPathParameter) = 0;                  // 03
	};
	static_assert(sizeof(IPathFollowerAction) == 0x8);
}
