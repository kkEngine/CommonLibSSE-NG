#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/T/TESTexture.h"

namespace RE
{
	class ExtraCellWaterEnvMap : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCellWaterEnvMap;
		inline static auto           EXTRADATATYPE = ExtraDataType::kCellWaterEnvMap;

		~ExtraCellWaterEnvMap() override = default;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override
		{
			return EXTRADATATYPE;
		}  // 01 - { return kCellWaterEnvMap; }
		bool IsNotEqual(const BSExtraData* a_rhs) const override
		{
			return waterEnvMap.textureName != static_cast<const ExtraCellWaterEnvMap*>(a_rhs)->waterEnvMap.textureName;
		}  // 02

		// members
		TESTexture waterEnvMap;  // 10
	};
	static_assert(sizeof(ExtraCellWaterEnvMap) == 0x20);
}
