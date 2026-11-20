#include "RE/B/BGSDefaultObjectManager.h"

using namespace REL;

namespace RE
{
	namespace
	{
		constexpr auto kInvalid = (std::numeric_limits<std::size_t>::max)();

		inline std::size_t MapIndex(std::underlying_type_t<DefaultObjectID> a_idx) noexcept
		{
			if (a_idx <= std::to_underlying(DefaultObjectID::kKeywordActivatorFurnitureNoPlayer)) {
				return a_idx;
			}
			// the low 16 bits hold the SE index, 0 for forms the flat runtimes don't have
			const std::size_t result = 0x0000FFFF & a_idx;
			return result ? BGSDefaultObjectManager::ToRuntimeIndex(result) : kInvalid;
		}
	}

	TESForm** BGSDefaultObjectManager::GetObject(DefaultObjectID a_object) noexcept
	{
		auto idx = MapIndex(std::to_underlying(a_object));
		if (idx == kInvalid) {
			return nullptr;
		}
		return IsObjectInitialized(idx) ?
                   &RelocateMember<TESForm**>(this, 0x20)[idx] :
                   nullptr;
	}

	bool BGSDefaultObjectManager::IsObjectInitialized(DefaultObjectID a_object) const noexcept
	{
		return IsObjectInitialized(MapIndex(std::to_underlying(a_object)));
	}

	bool BGSDefaultObjectManager::SupportsCurrentRuntime(DefaultObjectID a_object) noexcept
	{
		return MapIndex(std::to_underlying(a_object)) != kInvalid;
	}
}
