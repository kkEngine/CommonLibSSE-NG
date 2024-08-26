#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IPipelineStageInterface.h"
#include "RE/M/MovementControllerContext.h"
#include "RE/M/MovementVector.h"

namespace RE
{
	class MovementParameters;

	class IMovementPlannerAgent : public IPipelineStageInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerAgent;

		template <typename ValueType>
		struct WeightedValue
		{
			float     weight;
			ValueType value;
		};

		struct PlannerContext
		{
			WeightedValue<MovementVector>                      movementVector;      // 00
			WeightedValue<NiPoint3>                            angle;               // 14
			WeightedValue<BSTSmartPointer<MovementParameters>> movementParameters;  // 28
			MovementControllerContext*                         controllerContext;   // 38
			BSScrapArray<void*>*                               unk40;               // 40
			uint64_t                                           unk48;               // 48
			uint16_t                                           unk50;               // 50
		};
		static_assert(sizeof(PlannerContext) == 0x58);

		~IMovementPlannerAgent() override;  // 00

		// add
		virtual const BSFixedString& GetPlannerAgentName() = 0;                                        // 01
		virtual void                 PlanMovement(float* a_deltaTime, PlannerContext& a_context) = 0;  // 02
		virtual void                 PlanMovementVirtual(float* a_deltaTime, bool&) = 0;               // 03 - nonempty only in MovementAgentPathFollowerFlight and MovementAgentPathFollowerVirtual
	};
	static_assert(sizeof(IMovementPlannerAgent) == 0x8);
}
