#include "RE/B/BGSDefaultObjectManager.h"

using namespace REL;

namespace RE
{
	namespace
	{
		constexpr auto kInvalid = (std::numeric_limits<std::size_t>::max)();

		// DefaultObjectID uses the SE numbering, like DEFAULT_OBJECTS
		inline std::size_t MapIndex(std::underlying_type_t<DefaultObjectID> a_idx) noexcept
		{
			return BGSDefaultObjectManager::ToRuntimeIndex(static_cast<std::size_t>(a_idx));
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

	bool BGSDefaultObjectManager::SupportsSE(DefaultObjectID) noexcept
	{
		return true;  // every DefaultObjectID has an SE index
	}

	bool BGSDefaultObjectManager::SupportsCurrentRuntime(DefaultObjectID) noexcept
	{
		return true;
	}
}
