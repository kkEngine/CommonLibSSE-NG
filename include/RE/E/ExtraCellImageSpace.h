#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESImageSpace;

	class ExtraCellImageSpace : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCellImageSpace;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCellImageSpace;

		~ExtraCellImageSpace() override = default;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override
		{
			return EXTRADATATYPE;
		}  // 01 - { return kCellImageSpace; }
		bool IsNotEqual(const BSExtraData* a_rhs) const override
		{
			return imageSpace != static_cast<const ExtraCellImageSpace*>(a_rhs)->imageSpace;
		}  // 02 - { return imageSpace != a_rhs->imageSpace; }

		// members
		TESImageSpace* imageSpace = nullptr;  // 10
	};
	static_assert(sizeof(ExtraCellImageSpace) == 0x18);
}
