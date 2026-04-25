#include "RE/B/BShkbUtils.h"

namespace RE
{
	namespace BShkbUtils
	{
		hkbBehaviorGraph* CloneRootGraph(hkbCharacter& hchar, hkbBehaviorGraph& graph)
		{
			using func_t = decltype(CloneRootGraph);
			REL::Relocation<func_t> func{ RELOCATION_ID(62924, 63847) };
			return func(hchar, graph);
		}

		void CreateStateArrayFromVariables(hkbBehaviorGraph* graph, const BSTHashMap<BSFixedString, int32_t>& variableNamesToIds, BSTArray<BSFixedString>& stateNames)
		{
			using func_t = decltype(CreateStateArrayFromVariables);
			REL::Relocation<func_t> func{ RELOCATION_ID(62929, 63852) };
			return func(graph, variableNamesToIds, stateNames);
		}

		bool GetActiveClips(hkbCharacter* hkbChar, float time, BSScrapArray<BSAnimationGraphManager::ClipData>& ans)
		{
			using func_t = decltype(GetActiveClips);
			REL::Relocation<func_t> func{ RELOCATION_ID(62935, 63858) };
			return func(hkbChar, time, ans);
		}

		bool GraphInspection(const GraphInspectionConfiguration& cfg, hkbCharacter& hkbChar, GraphInspectionFunctor& functor)
		{
			using func_t = decltype(GraphInspection);
			REL::Relocation<func_t> func{ RELOCATION_ID(64198, 65232) };
			return func(cfg, hkbChar, functor);
		}

		// hkbBehaviorGraph* LoadBehaviorProject(const char* folder, const char* name, hkbCharacter& hchar, RE::hkbHkxDBHandle& project_data_handle, BSFixedString& filename, RE::BSScrapArray<hkbBehaviorGraph*>& hgraphs)
		// {
		// 	using func_t = decltype(LoadBehaviorProject);
		// 	REL::Relocation<func_t> func{ RELOCATION_ID(62921, 63844) };
		// 	return func(folder, name, hchar, project_data_handle, filename, hgraphs);
		// }

		hkbSymbolIdMap* PerformOncePerLoadBehaviorOperations(hkbBehaviorGraph* graph, BSScrapArray<hkbBehaviorGraph*>& hgraphs, const char* folder, hkbCharacter& hchar, hkbSymbolLinker& linkBehaviorEvents, hkbSymbolLinker& linkBehaviorVariables)
		{
			using func_t = decltype(PerformOncePerLoadBehaviorOperations);
			REL::Relocation<func_t> func{ RELOCATION_ID(62922, 63845) };
			return func(graph, hgraphs, folder, hchar, linkBehaviorEvents, linkBehaviorVariables);
		}

		void RetrieveEventNamesAndIDsFromSymbolLinker(const hkbSymbolLinker& linker, BSTHashMap<BSFixedString, int32_t>& eventNamesToIds, BSTArray<BSFixedString>& eventNames, const BSFixedString* projectName_unused)
		{
			using func_t = decltype(RetrieveEventNamesAndIDsFromSymbolLinker);
			REL::Relocation<func_t> func{ RELOCATION_ID(62925, 63848) };
			return func(linker, eventNamesToIds, eventNames, projectName_unused);
		}

		void RetrieveVariableNamesAndIDsFromSymbolLinker(const hkbSymbolLinker& linker, BSTHashMap<BSFixedString, int32_t>& variableNamesToIds, const BSFixedString* projectName_unused)
		{
			using func_t = decltype(RetrieveVariableNamesAndIDsFromSymbolLinker);
			REL::Relocation<func_t> func{ RELOCATION_ID(62926, 63849) };
			return func(linker, variableNamesToIds, projectName_unused);
		}

		GraphTraverser* GraphTraverser::ctor(GraphTraverser* _this, GET_CHILDREN_FLAGS flags, hkbNode* root)
		{
			using func_t = decltype(&GraphTraverser::ctor);
			REL::Relocation<func_t> func{ RELOCATION_ID(62942, 63865) };
			return func(_this, flags, root);
		}

		GraphTraverser::~GraphTraverser()
		{
			using funcs_t = void(void*);
			{
				REL::Relocation<funcs_t> func{ RELOCATION_ID(66854, 68109) };
				func(buffer);
			}
			{
				REL::Relocation<funcs_t> func{ RELOCATION_ID(32072, 63895) };
				func(arena);
			}
		}

		hkbNode* GraphTraverser::Next()
		{
			using func_t = decltype(&GraphTraverser::Next);
			REL::Relocation<func_t> func{ RELOCATION_ID(62944, 63867) };
			return func(this);
		}
	}
}
