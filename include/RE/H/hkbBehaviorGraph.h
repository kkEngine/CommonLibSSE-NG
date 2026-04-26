#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkPointerMap.h"
#include "RE/H/hkRefVariant.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbBehaviorGraphData;
	class hkPseudoRandomGenerator;
	class hkbStateListener;
	class hkbStateMachine;
	class hkbSymbolIdMap;
	class hkbVariableValueSet;
	class hkbGeneratorOutput;

	class hkbBehaviorGraph : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBehaviorGraph;
		inline static constexpr auto VTABLE = VTABLE_hkbBehaviorGraph;

		// How to deal with variables when the behavior is inactive
		enum class VariableMode
		{
			// Throw away the variable values and memory on deactivate().
			// In this mode, variable memory is allocated and variable values are
			// reset each time activate() is called.
			kDiscardWhenActive = 0,

			// Don't discard the variable memory on deactivate(), and don't
			// reset the variable values on activate() (except the first time).
			kMaintainValuesWhenInactive = 1,
		};

		// Stores the relationships between state machines and which behavior graph contains each state machine
		struct StateMachineInfo
		{
			hkbStateMachine*                stateMachineTemplate;          // 00 - A pointer to a node which is a state machine.
			hkbBehaviorGraph*               behaviorTemplate;              // 08 - The behavior graph to which the state machine belongs. For the state machines in root behavior graph this would be set to null.
			hkArray<int16_t>*               eventlessGlobalTransitions;    // 10 - All the global wildcard transitions for a state machine with only conditions. If they have different priorities than the one with higher priority comes first. The index of the transition in hkbStateMachine::m_wildcardTransitions is stored.
			hkPointerMap<int32_t, int16_t>* eventToGlobalTransitionMap;    // 18 - A map from events to global transition. The index of the transition in hkbStateMachine::m_wildcardTransitions is stored.
			hkArray<int32_t>*               childStateMachineInfoIndices;  // 20 - The child state machine info indices
			uint32_t                        parentStateMachineInfoIndex;   // 28 - The state machine info index which contains the parent state machine of this state machine.
			uint32_t                        stateIndexInParent;            // 2C - The index of the state in the parent state machine that contains this state machine.
		};
		static_assert(sizeof(StateMachineInfo) == 0x30);

		class GlobalTransitionData : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbBehaviorGraph__GlobalTransitionData;

			~GlobalTransitionData() override;  // 00

			hkArray<StateMachineInfo>                stateMachineInfos;                             // 10 - All the state machines in the entire behavior graph.
			hkArray<int>                             eventlessGlobalTransitionStateMachineIndices;  // 20 - Indices (into the m_stateMachineInfos) of the state machine infos that have global wildcard transitions with only conditions.
			hkPointerMap<hkbStateMachine*, int>      stateMachineTemplateToIndexMap;                // 30 - A map from state machines to indices in the m_stateMachineInfos
			hkPointerMap<int, hkArray<int>*>         eventToStateMachineInfoIndices;                // 40 - A map from event IDs to arrays of indices into the m_stateMachineInfos. This map tells us which state machines have global wildcard transitions defined for each event ID.
			hkPointerMap<uint16_t, hkbStateMachine*> idToStateMachineTemplateMap;                   // 50 - A map from ids to state machine templates. This is used for looking up global transitions.
		};
		static_assert(sizeof(GlobalTransitionData) == 0x60);

		~hkbBehaviorGraph() override;  // 00

		// override (hkbNode)
		hkClass* GetClassType() const override;                                                                                        // 01
		void     CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;                     // 02
		void     Activate(const hkbContext& a_context) override;                                                                       // 04
		void     Update(const hkbContext& a_context, float a_timestep) override;                                                       // 05
		void     HandleEvent(const hkbContext& a_context, hkbEvent a_event) override;                                                  // 06
		void     Deactivate(const hkbContext& a_context) override;                                                                     // 07
		void     GetChildren(stl::enumeration<GetChildrenFlagBits, std::int32_t> a_flags, hkbNodeChildInfo& a_childrenInfo) override;  // 09
		hkbNode* CloneNode(hkbBehaviorGraph& a_rootBehavior) const override;                                                           // 0C
		bool     IsBehaviorGraph() const override;                                                                                     // 16 - { return 1; }

		// override (hkbGenerator)
		void Generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const override;  // 17
		bool CanRecycleOutput() const override;                                                                                                                           // 18
		void UpdateSync(const hkbContext& a_context, hkbNodeInfo& info) override;                                                                                         // 19

		hkbNodeInfo&       accessNodeInfoByClone(hkbNode* nodeClone);
		hkbNodeInfo&       accessNodeInfoByTemplate(hkbNode* nodeTemplate);
		hkbNodeInfo&       adjust_info_usesomeind(hkbNodeInfo& info) const;
		const hkbNodeInfo& adjust_info_usesomeind(const hkbNodeInfo& info) const;
		hkbBehaviorGraph*  cloneDeep(bool copyAnimationBindings = true, bool copyIdMappers = true, bool copyReferencedBehaviors = true, void* vtableClassRegistry = nullptr, void* finishLoadedObjectRegistry = nullptr, hkbGenerator* replacementRootGenerator = nullptr, void* behaviorToCloneMap = nullptr);
		hkbNode*           getNodeClone(hkbNode* nodeTemplate) const;
		const hkbNodeInfo& getNodeInfoByClone(hkbNode* nodeClone) const;
		const hkbNodeInfo& getNodeInfoByTemplate(hkbNode* nodeTemplate) const;
		hkbNode*           getNodeTemplate(hkbNode* nodeClone) const;

		// members
		stl::enumeration<VariableMode, std::uint8_t>        variableMode;                     // 048 - How do deal with variables when the behavior is inactive
		char                                                pad49[7];                         // 049
		hkArray<uint16_t>                                   uniqueIDPool;                     // 050 - A pool of unique IDs to be used for hkbTransitionEffects (all other nodes have static unique IDs)
		hkPointerMap<std::uint16_t, hkbStateMachine*>*      idToStateMachineTemplateMap;      // 060 - A map from ids to state machine templates. This is used for looking up global transitions
		hkArray<int>                                        mirroredExternalIDMap;            // 068 - The mapper between external Id's and mirrored external Id's
		hkPseudoRandomGenerator*                            pseudoRandomGenerator;            // 078
		hkRefPtr<hkbGenerator>                              rootGenerator;                    // 080
		hkRefPtr<hkbBehaviorGraphData>                      data;                             // 088 - The constant data associated with the behavior
		hkbGenerator*                                       rootGeneratorClone;               // 090 - If this is a clone, this pointer points to the original root of the cloned behavior graph
		hkArray<hkbNodeInfo>*                               activeNodes;                      // 098 - The current active nodes in the behavior
		hkPointerMap<hkbNode*, int>*                        activeNodeTemplateToIndexMap;     // 0A0
		hkArray<int32_t>*                                   activeNodesChildrenIndices;       // 0A8
		hkRefPtr<GlobalTransitionData>                      globalTransitionData;             // 0B0 - A member for storing all the information required for doing global transitions
		hkRefPtr<hkbSymbolIdMap>                            eventIDMap;                       // 0B8 - A mapper between internal event IDs and external event IDs
		hkRefPtr<hkbSymbolIdMap>                            attributeIDMap;                   // 0C0 - A mapper between internal attribute IDs and external attribute IDs
		hkRefPtr<hkbSymbolIdMap>                            variableIDMap;                    // 0C8 - A mapper between internal variable IDs and external variable IDs
		hkRefPtr<hkbSymbolIdMap>                            characterPropertyIDMap;           // 0D0 - A mapper between internal character property IDs and those in the character (external)
		hkRefPtr<hkbVariableValueSet>                       variableValueSet;                 // 0D8 - The current value of the behavior variables
		hkPointerMap<hkbNode*, hkbNode*>*                   nodeTemplateToCloneMap;           // 0E0 - A map from template nodes to cloned nodes
		hkPointerMap<hkbNode*, hkbNode*>*                   nodeCloneToTemplateMap;           // 0E8
		hkPointerMap<hkbStateListener*, hkbStateListener*>* stateListenerTemplateToCloneMap;  // 0F0 - A map from template state listeners to clones
		hkRefVariant                                        nodePartitionInfo;                // 0F8
		std::int32_t                                        numIntermediateOutputs;           // 100 - The number of intermediate outputs needed to process the partitioned graph
		std::uint32_t                                       pad104;                           // 104
		hkArray<hkRefVariant>                               jobs;                             // 108 - The jobs for partition that can run on SPUs
		hkArray<hkRefVariant>                               allPartitionMemory;               // 118 - The memory required for all the partitions
		std::int16_t                                        numStaticNodes;                   // 128
		std::int16_t                                        nextUniqueID;                     // 12A - The next unique ID to use if m_uniqueIdPool is empty
		bool                                                isActive;                         // 12C - Whether or not the behavior has been activated
		bool                                                isLinked;                         // 12D - Whether or not the behavior graph has been linked (see hkbBehaviorLinkingUtils)
		bool                                                updateActiveNodes;                // 12E - If this is set to true then we update the active nodes at the next opportunity
		bool                                                stateOrTransitionChanged;         // 12F - If this is set to true then we need to go through the nodes and process any nodes whose m_enable has changed
	};
	static_assert(sizeof(hkbBehaviorGraph) == 0x130);
}
