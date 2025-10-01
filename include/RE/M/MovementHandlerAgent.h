#pragma once

#include "RE/I/IMovementHandlerAgent.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	class MovementHandlerAgent :
		public MovementAgent,         // 000
		public IMovementHandlerAgent  // 001
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgent;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgent;

		MovementHandlerAgent();

		~MovementHandlerAgent() override = default;  // 00

		// override (MovementAgent)
		IPipelineStageInterface* GetPipelineStageInterface(const BSFixedString& a_stage) override;  // 03

		// override (IMovementHandlerAgent)
		const BSFixedString& GetHandlerAgentName() const override;  // 01
	};
	static_assert(sizeof(MovementHandlerAgent) == 0x20);
}
