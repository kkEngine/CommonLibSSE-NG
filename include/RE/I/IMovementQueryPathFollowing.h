#pragma once

#include "RE/B/BSPathingSolution.h"
#include "RE/I/IMovementInterface.h"

namespace RE
{
	class MovementMessage;
	class NiPoint3;

	struct PathingPoint;

	class IMovementQueryPathFollowing : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementQueryPathFollowing;

		class INodeVisitor
		{
			inline static constexpr auto RTTI = RTTI_IMovementQueryPathFollowing__INodeVisitor;

			virtual ~INodeVisitor();  // 00

			// add
			virtual bool Visit(const BSPathingSolution::DetailedPathingPoint& point) = 0;
		};

		~IMovementQueryPathFollowing() override;  // 00

		// add
		virtual bool CanCompletePath() = 0;                                                                                                                               // 01
		virtual bool IsPathFailed() = 0;                                                                                                                                  // 02
		virtual bool IsPathInProgress() = 0;                                                                                                                              // 03
		virtual bool IsMovingAlongPath() = 0;                                                                                                                             // 04
		virtual bool GetDestinationPositionAndWidth(NiPoint3& a_outPosition, float& a_outWidth) = 0;                                                                      // 05
		virtual bool GetDistanceToGoal(float& a_outDistance) = 0;                                                                                                         // 06
		virtual bool GetTargetAngle(NiPoint3& a_outAngle);                                                                                                                // 07
		virtual bool HasMovementTarget();                                                                                                                                 // 08
		virtual bool GetPathPositionByTime(float a_deltaTime, NiPoint3& a_outPosition);                                                                                   // 09
		virtual bool GetPathPositionAndDirectionByTime(float a_deltaTime, NiPoint3& a_outPosition, NiPoint3& a_outDirection);                                             // 0A
		virtual bool GetMaxPathSpeed(float a_rotationSpeedZ, float a_angularAcceleration, float a_deceleration, float a_rotateWhileMovingRun, float& a_outSpeed);         // 0B
		virtual bool GetPathPositionAndDirectionByDistance(float a_distance, NiPoint3& a_outPosition, NiPoint3& a_outDirection);                                          // 0C
		virtual bool GetPathPositionByDistance(float a_distance, NiPoint3& a_outPosition);                                                                                // 0D
		virtual bool GetClosestPathPositionAndDirection(const NiPoint3& a_targetPosition, float& a_outPathParameter, NiPoint3& a_outPosition, NiPoint3& a_outDirection);  // 0E
		virtual bool GetPathDistanceToParameter(float a_pathParameter, float& a_outDistance);                                                                             // 0F
		virtual bool GetPathDistanceLeft(float& a_outDistance);                                                                                                           // 10
		virtual bool GetPathDistanceLeftAndFinalPosition(NiPoint3& a_outPosition, float& a_outDistance);                                                                  // 11
		virtual bool GetPathDoor(BSTSmartPointer<MovementMessage>& a_outDoorMovementMessage, uint32_t& a_outDoorPathingPointIndex, PathingPoint& a_outDoorPathingPoint);  // 12
		virtual bool AcceptNodeVisitor(const INodeVisitor& a_visitor);                                                                                                    // 13
		virtual bool GetDirectionAlongPath(NiPoint3& a_outDirection);                                                                                                     // 14
	};
	static_assert(sizeof(IMovementQueryPathFollowing) == 0x8);
}
