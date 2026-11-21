#include "RE/H/hkbBehaviorGraph.h"
#include "RE/H/hkbNodeInfo.h"

namespace RE
{
	hkbNodeInfo& hkbBehaviorGraph::accessNodeInfoByClone(hkbNode* nodeClone)
	{
		return const_cast<hkbNodeInfo&>(std::as_const(*this).getNodeInfoByClone(nodeClone));
	}

	hkbNodeInfo& hkbBehaviorGraph::accessNodeInfoByTemplate(hkbNode* nodeTemplate)
	{
		return const_cast<hkbNodeInfo&>(std::as_const(*this).getNodeInfoByTemplate(nodeTemplate));
	}

	hkbBehaviorGraph* hkbBehaviorGraph::cloneDeep(bool copyAnimationBindings, bool copyIdMappers, bool copyReferencedBehaviors, void* vtableClassRegistry, void* finishLoadedObjectRegistry, hkbGenerator* replacementRootGenerator, void* behaviorToCloneMap)
	{
		using func_t = decltype(&hkbBehaviorGraph::cloneDeep);
		REL::Relocation<func_t> func{ RELOCATION_ID(57770, 58341) };
		return func(this, copyAnimationBindings, copyIdMappers, copyReferencedBehaviors, vtableClassRegistry, finishLoadedObjectRegistry, replacementRootGenerator, behaviorToCloneMap);
	}

	hkbNode* hkbBehaviorGraph::getNodeClone(hkbNode* nodeTemplate) const
	{
		if (nodeTemplate->cloneState == RE::hkbNode::CloneState::kClone || !nodeTemplateToCloneMap)
			return nodeTemplate;

		hkbNode* ans = nodeTemplateToCloneMap->getWithDefault(nodeTemplate, nullptr);

		return ans ? ans : nodeTemplate;
	}

	const hkbNodeInfo& hkbBehaviorGraph::getNodeInfoByClone(hkbNode* nodeClone) const
	{
		auto nodeTemplate = getNodeTemplate(nodeClone);
		return getNodeInfoByTemplate(nodeTemplate);
	}

	const hkbNodeInfo& hkbBehaviorGraph::getNodeInfoByTemplate(hkbNode* nodeTemplate) const
	{
		assert(activeNodeTemplateToIndexMap);
		assert(activeNodes);
		int32_t ind = activeNodeTemplateToIndexMap->getWithDefault(nodeTemplate, 0);
		return (*activeNodes)[ind];
	}

	hkbNode* hkbBehaviorGraph::getNodeTemplate(hkbNode* nodeClone) const
	{
		if (nodeClone->cloneState == RE::hkbNode::CloneState::kClone && nodeCloneToTemplateMap)
			return nodeCloneToTemplateMap->getWithDefault(nodeClone, nullptr);
		else
			return nodeClone;
	}

	hkbNodeInfo& hkbBehaviorGraph::adjust_info_usesomeind(hkbNodeInfo& info) const
	{
		assert(activeNodes);
		return info.use_some_ind ? (*activeNodes)[info.some_ind] : info;
	}

	const hkbNodeInfo& hkbBehaviorGraph::adjust_info_usesomeind(const hkbNodeInfo& info) const
	{
		assert(activeNodes);
		return info.use_some_ind ? (*activeNodes)[info.some_ind] : info;
	}
}
