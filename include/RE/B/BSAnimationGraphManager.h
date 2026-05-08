#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/H/hkbVariableValue.h"
#include "SKSE/Version.h"

namespace RE
{
	class BSAnimationGraphChannel;
	class BShkbAnimationGraph;
	struct BSAnimationGraphEvent;

	struct AnimVariableCacheInfo
	{
	public:
		// members
		BSFixedString     variableName;  // 00
		hkbVariableValue* variable;      // 08
	};
	static_assert(sizeof(AnimVariableCacheInfo) == 0x10);

	struct BSAnimationGraphVariableCache
	{
	public:
		[[nodiscard]] BSSpinLock* GetGraphLock() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version() >= SKSE::RUNTIME_SSE_1_6_629) {
					return &REL::RelocateMember<BSSpinLock>(this, 0x20);
				}
			}
			return nullptr;
		}

		[[nodiscard]] BSTSmartPointer<BShkbAnimationGraph>& GetAnimationGraph() noexcept
		{
			return REL::RelocateMemberIfNewer<BSTSmartPointer<BShkbAnimationGraph>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x20, 0x28);
		}

		[[nodiscard]] const BSTSmartPointer<BShkbAnimationGraph>& GetAnimationGraph() const noexcept
		{
			return REL::RelocateMemberIfNewer<BSTSmartPointer<BShkbAnimationGraph>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x20, 0x28);
		}

		// members
		BSTArray<AnimVariableCacheInfo> variableCache;  // 00
		mutable BSSpinLock              updateLock;     // 18
#if !defined(ENABLE_SKYRIM_AE)
		BSTSmartPointer<BShkbAnimationGraph> animationGraph;  // 20, 28 - smart ptr
#endif
	};
#if !defined(ENABLE_SKYRIM_AE)
	static_assert(sizeof(BSAnimationGraphVariableCache) == 0x28);
#endif

	BSSmartPointer(BSAnimationGraphManager);

	class BSAnimationGraphManager :
		public BSTEventSink<BSAnimationGraphEvent>,  // 00
		public BSIntrusiveRefCounted                 // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSAnimationGraphManager;

		struct AnimationVariable
		{
		public:
			union Value
			{
				bool         b;
				std::int32_t i;
				float        f;
			};
			static_assert(sizeof(Value) == 0x4);

			// members
			BSFixedString name;   // 00
			Value*        value;  // 08
		};
		static_assert(sizeof(AnimationVariable) == 0x10);

		class ClipData
		{
		public:
			// members
			BSFixedString clipName;       // 00
			float         playbackSpeed;  // 08
			float         field_C;        // 0C
			float         weight;         // 10
			float         field_14;       // 14
			bool          isMirror;       // 18
			uint8_t       pad19[7];       // 19
		};
		static_assert(sizeof(ClipData) == 0x20);

		~BSAnimationGraphManager() override;  // 00

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent* a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override;  // 01

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	mutable BSSpinLock updateLock;           /* 98, A0 */ \
	mutable BSSpinLock dependentManagerLock; /* A0 */     \
	std::uint32_t      activeGraph;          /* A8 */     \
	std::uint32_t      generateDepth;        /* A8 */

			RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		bool QueryAnimations(float mb_from_time, BSFixedString& projectName, BSScrapArray<ClipData>& array, int activeGraph_ind)
		{
			using func_t = bool(BSAnimationGraphManager*, float, BSFixedString&, BSScrapArray<ClipData>&, int);
			REL::Relocation<func_t> func{ RELOCATION_ID(62431, 63373) };
			return func(this, mb_from_time, projectName, array, activeGraph_ind);
		}

		bool QueryAnimations(const BSScrapArray<BSFixedString>& events, int activeGraph_ind, BSFixedString& projectName, BSScrapArray<ClipData>& clips)
		{
			using func_t = bool(BSAnimationGraphManager*, const BSScrapArray<BSFixedString>&, int, BSFixedString&, BSScrapArray<ClipData>&);
			REL::Relocation<func_t> func{ RELOCATION_ID(62432, 63374) };
			return func(this, events, activeGraph_ind, projectName, clips);
		}

		// This func doesn't check bounds
		inline BSAnimationGraphManager* GetBSAnimationGraphManagerByIndex(BSTArray<BSAnimationGraphManager*>::size_type a_index)
		{
			// Zero the last bit (or & 0xFFFFFFFFFFFFFFFEui64)
			auto ptr = reinterpret_cast<std::uintptr_t>(subManagers[a_index]) & ~1;
			return reinterpret_cast<BSAnimationGraphManager*>(ptr);
		}

		using SubManagersVisitFn = std::function<void(BSAnimationGraphManager*)>;
		inline void VisitSubManagers(SubManagersVisitFn&& a_visitor)
		{
			RE::BSSpinLockGuard locker(GetRuntimeData().dependentManagerLock);
			for (BSTArray<BSAnimationGraphManager*>::size_type i = 0; i < subManagers.size(); ++i) {
				a_visitor(GetBSAnimationGraphManagerByIndex(i));
			}
		}

		// members
		std::uint32_t                                       pad0C;           // 0C
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>>  boundChannels;   // 10
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>>  bumpedChannels;  // 28
		BSTSmallArray<BSTSmartPointer<BShkbAnimationGraph>> graphs;          // 40
		BSTArray<BSAnimationGraphManager*>                  subManagers;     // 58
		BSAnimationGraphVariableCache                       variableCache;   // 70

#ifndef ENABLE_SKYRIM_AE
		RUNTIME_DATA_CONTENT
#endif
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(BSAnimationGraphManager) == 0xB0);
#endif
}
#undef RUNTIME_DATA_CONTENT
