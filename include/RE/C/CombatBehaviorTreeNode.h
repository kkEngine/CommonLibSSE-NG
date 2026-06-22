#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class CombatBehaviorThread;

	class CombatBehaviorTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTreeNode;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTreeNode;

		virtual ~CombatBehaviorTreeNode() = default;  // 00

		virtual const char*          GetName() const;                                      // 01
		virtual void                 Enter(CombatBehaviorThread* a_thread);                // 02
		virtual void                 Exit(CombatBehaviorThread*);                          // 03
		virtual void                 Update(CombatBehaviorThread* thread);                 // 04
		virtual void                 Abort(CombatBehaviorThread* thread);                  // 05
		virtual void                 SaveGame(CombatBehaviorThread*, BGSSaveFormBuffer*);  // 06
		virtual void                 LoadGame(CombatBehaviorThread*, BGSLoadFormBuffer*);  // 07
		virtual bool                 Validate(CombatBehaviorTreeNode*) const;              // 08
		virtual const BSFixedString& GetType() const;                                      // 09

		// members
		BSFixedString                          name;      // 08
		CombatBehaviorTreeNode*                parent;    // 10
		BSStaticArray<CombatBehaviorTreeNode*> children;  // 18
	};
	static_assert(sizeof(CombatBehaviorTreeNode) == 0x28);
}
