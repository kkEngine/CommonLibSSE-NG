#pragma once

#include "RE/I/IMovementHandlerAgent.h"
#include "RE/I/IMovementPathManagerAgent.h"
#include "RE/I/IMovementPlannerAgent.h"
#include "RE/I/IMovementQueryPathFollowing.h"
#include "RE/I/IMovementSetPathFollowing.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	class MovementAgentPathFollowerVirtual :
		public MovementAgent,
		public IMovementPlannerAgent,
		public IMovementPathManagerAgent,
		public IMovementQueryPathFollowing,
		public IMovementSetPathFollowing
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentPathFollowerVirtual;

		enum class State
		{
			NoPath = 0x0,
			PathInProgress = 0x1,
			PathComplete = 0x2,
			PathFailed = 0x3,
		};

		~MovementAgentPathFollowerVirtual() override;  // 00

		// override (MovementAgent)
		const BSFixedString& GetName() const override;                                            // 01
		MovementAgentType    GetType() override;                                                  // 02
		IMovementInterface*  GetInterfaceByName(BSFixedString* a_name) override;                  // 03
		void                 SetMovementController(MovementControllerAI* a_controller) override;  // 04
		void                 Activate() override;                                                 // 06
		void                 Initialize(BSPathingStreamSimpleBufferRead* a_buffer) override;      // 07
		void                 RemoveMovementController() override;                                 // 0A
		void                 OnSaveGame(BSPathingStreamWrite* a_a2) override;                     // 0B
		void                 OnLoadGame(BSPathingStreamRead* a_a2) override;                      // 0C

		// override (IMovementPlannerAgent)
		const BSFixedString& GetPlannerAgentName() override;                                        // 01
		void                 PlanMovement(float* a_deltaTime, PlannerContext& a_context) override;  // 02
		void                 PlanMovementVirtual(float* a_deltaTime, bool&) override;               // 03

		// override (IMovementPathManagerAgent)
		const BSFixedString& GetPathManagerAgentName() override;                                                                                                          // 01
		void                 OnNewPath(const BSTSmartPointer<BSPathingRequest>& a_pathingRequest, const BSTSmartPointer<BSPathingSolution>& a_pathingSolution) override;  // 02
		void                 ProcessPath(MovementArbitersContext& a_context, PathFollowingInfo& a_point) override;                                                        // 03
		void                 OnPathRestart(const BSTSmartPointer<BSPathingRequest>& a_pathingRequest) override;                                                           // 04
		void                 OnPathCleared() override;                                                                                                                    // 06

		// override (IMovementQueryPathFollowing)
		bool CanCompletePath() override;                                                           // 01
		bool IsPathFailed() override;                                                              // 02
		bool IsPathInProgress() override;                                                          // 03
		bool IsMovingAlongPath() override;                                                         // 04
		bool GetDestinationPositionAndWidth(NiPoint3& a_outPosition, float& a_outWidth) override;  // 05
		bool GetDistanceToGoal(float& a_outDistance) override;                                     // 06

		// override (IMovementSetPathFollowing)
		Result SetPathFollowing(bool a_isFollowing) override;  // 01

		// add
		virtual bool Unk_0D(void);  // 0D

		// members
		BSReadWriteLock                    lock;             // 38
		stl::enumeration<State, int32_t>   state;            // 40
		BSTSmartPointer<BSPathingRequest>  pathingRequest;   // 48
		BSTSmartPointer<BSPathingSolution> pathingSolution;  // 50
		MovementControllerAI*              controller;       // 58
	};
	static_assert(sizeof(MovementAgentPathFollowerVirtual) == 0x60);
}
