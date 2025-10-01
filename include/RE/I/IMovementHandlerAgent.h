#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IPipelineStageInterface.h"
#include "RE/M/MovementControllerContext.h"
#include "RE/M/MovementData.h"

namespace RE
{
	class IMovementHandlerAgent : public IPipelineStageInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementHandlerAgent;
		inline static constexpr auto VTABLE = VTABLE_IMovementHandlerAgent;

		struct HandlerContext
		{
			MovementControllerContext* controllerContext;    // 00
			MovementData*              handledMovementData;  // 08
		};
		static_assert(sizeof(HandlerContext) == 0x10);

		static const BSFixedString& QPipelineStage();

		IMovementHandlerAgent();

		~IMovementHandlerAgent() override = default;  // 00

		// add
		virtual const BSFixedString& GetHandlerAgentName() const = 0;              // 01
		virtual void                 HandleMovement(HandlerContext& context) = 0;  // 02
		virtual void                 HandleMovementVirtual(float* deltaTime) = 0;  // 03 - empty in all implementations
	};
	static_assert(sizeof(IMovementHandlerAgent) == 0x8);
}
