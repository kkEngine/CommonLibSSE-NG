#pragma once

#include "RE/H/hkbGeneratorSyncInfo.h"

namespace RE
{
	class hkbBehaviorGraph;
	class hkbNode;

	/// Information about a node in a behavior graph.
	struct hkbNodeInfo
	{
		hkbGeneratorSyncInfo syncInfo;         // 00
		hkbNode*             nodeTemplate;     // 50
		hkbNode*             nodeClone;        // 58
		hkbBehaviorGraph*    behavior;         // 60
		int32_t              some_ind;         // 68
		int32_t              parents_count;    // 6C
		int32_t              childs_count;     // 70
		int32_t              first_child_ind;  // 74 - activeNodes[ activeNodesChildrenIndices[first_child_ind .. +childs_count] ] -- childs (when this's ind == parentInd_v2)
		int32_t              syncParentInd;    // 78 - when childinfo.syncToParent == syncToParent == true
		int32_t              parentInd;        // 7C - first visited parent->child
		int32_t              unk80;            // 80 - usually 0
		bool                 ignoreEvents;     // 84
		bool                 isGenerator;      // 85
		bool                 syncToParent;     // 86
		bool                 stopped;          // 87 - usually 0
		bool                 activated;        // 88
		bool                 use_some_ind;     // 89 - true <=> some_ind > 0
		char                 pad8A[6];         // 8A
	};
	static_assert(sizeof(hkbNodeInfo) == 0x90);
}
