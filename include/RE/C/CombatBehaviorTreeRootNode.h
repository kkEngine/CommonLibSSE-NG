#pragma once

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	class CombatBehaviorTreeRootNode : public CombatBehaviorTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTreeRootNode;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTreeRootNode;

		// override (CombatBehaviorTreeNode)
		~CombatBehaviorTreeRootNode() override = default;  // 00

		void                 Enter(CombatBehaviorThread* thread) override;                             // 02
		void                 Update(CombatBehaviorThread* thread) override;                            // 04
		void                 Abort(CombatBehaviorThread* thread) override;                             // 05
		void                 SaveGame(CombatBehaviorThread* thread, BGSSaveFormBuffer* buf) override;  // 06
		void                 LoadGame(CombatBehaviorThread* thread, BGSLoadFormBuffer* buf) override;  // 07
		bool                 Validate(CombatBehaviorTreeNode* node) const override;                    // 08
		const BSFixedString& GetType() const override;                                                 // 09
	};
	static_assert(sizeof(CombatBehaviorTreeRootNode) == 0x28);
}
