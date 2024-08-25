#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MovementData.h"
#include "RE/M/MovementVector.h"

namespace RE
{
	struct MovementControllerContext
	{
		BSScrapArray<void> unk00;                        // 00
		BSScrapArray<void> unk20;                        // 20
		MovementVector     plannedMovementVector;        // 40
		NiPoint3           plannedAngle;                 // 50
		bool               isMovingAlongPath;            // 5C
		float              leftDistance;                 // 60
		float              targetSpeed;                  // 64
		bool               zeroTargetSpeedAllowed;       // 68
		float              deltaTime;                    // 6C
		float              forwardAcceleration;          // 70
		float              deceleration;                 // 74
		float              minExpectedRotationSpeed;     // 78
		float              normalExpectedRotationSpeed;  // 7C
		float              angularAcceleration;          // 80
		float              unk84;                        // 84
		MovementData       handledMovementData;          // 88
		float              unkA4;                        // A4
		MovementData       finalMovementData;            // A8
	};
	static_assert(sizeof(MovementControllerContext) == 0xC8);

	struct MovementArbitersContext
	{
		uint32_t                  unk00;              // 00
		uint32_t                  unk04;              // 04
		float                     deltaTime;          // 08
		MovementControllerContext controllerContext;  // 10
	};
	static_assert(sizeof(MovementArbitersContext) == 0xD8);
}
