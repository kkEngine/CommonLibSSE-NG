#pragma once

#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiPlane.h"

namespace RE
{
	class BSWaterShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto VTABLE = VTABLE_BSWaterShaderProperty;
		inline static constexpr auto RTTI = RTTI_BSWaterShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSWaterShaderProperty;

		enum class WaterFlag
		{
			kNone = 0,
			kInitialized = 1 << 1,
			kUnderwater = 1 << 5,
			kUseReflections = 1 << 6,
			kUseCubemapReflections = 1 << 14,
			kEnableFlowmap = 1 << 15,
			kBlendNormals = 1 << 16
		};

		~BSWaterShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*          GetRTTI() const override;                                                                                                          // 02
		NiObject*              CreateClone(NiCloningProcess& a_cloning) override;                                                                                 // 17
		void                   LoadBinary(NiStream& a_stream) override;                                                                                           // 18
		void                   LinkObject(NiStream& a_stream) override;                                                                                           // 19
		bool                   RegisterStreamables(NiStream& a_stream) override;                                                                                  // 1A
		void                   SaveBinary(NiStream& a_stream) override;                                                                                           // 1B
		bool                   IsEqual(NiObject* a_object) override;                                                                                              // 1C - { return false; }
		void                   PostLinkObject(NiStream& a_stream) override;                                                                                       // 1E
		RenderPassArray*       GetRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator) override;                           // 2A
		RenderPassArray*       GetLocalMapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator) override;                   // 2C
		RenderPassArray*       GetPrecipitationOcclusionMapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator) override;  // 2D
		BSRenderPass*          GetDepthRenderPass(BSGeometry* geometry) override;                                                                                 // 2F
		std::int32_t           ForEachTexture(ForEachVisitor& a_visitor) override;                                                                                // 33
		void                   DoClearRenderPasses() override;                                                                                                    // 34
		std::int32_t           QShader() override;                                                                                                                // 35 - { return 17; }
		BSShaderMaterial::Type GetMaterialType() override;                                                                                                        // 3E - { return 3; }

		// members
		stl::enumeration<WaterFlag, std::uint32_t> waterFlags;            // 88
		std::uint32_t                              unk8C;                 // 8C
		std::uint32_t                              cellX;                 // 90
		std::uint32_t                              cellY;                 // 94
		std::uint32_t                              unk98;                 // 98
		std::uint32_t                              unk9C;                 // 9C
		NiPlane                                    plane;                 // A0
		std::uint64_t                              unkB0;                 // B0
		std::uint8_t                               unkB8;                 // B8
		std::uint8_t                               padB9;                 // B9
		std::uint16_t                              padBA;                 // BA
		std::uint16_t                              padBC;                 // BC
		BSRenderPass*                              unkC0;                 // C0
		RenderPassArray                            simpleRenderPassList;  // C8
		BSTArray<void*>                            unkD8;                 // D8
		std::int32_t                               unkF0;                 // F0
		std::uint32_t                              unkF4;                 // F4
		std::uint8_t                               unkF8;                 // F8
		std::uint8_t                               padF9;                 // F9
		std::uint16_t                              padFA;                 // FA
		std::uint16_t                              padFC;                 // FC

		static BSWaterShaderProperty* Create()
		{
			auto property = malloc<BSWaterShaderProperty>();
			std::memset(property, 0, sizeof(BSWaterShaderProperty));
			if (property) {
				property->Ctor();
			}
			return property;
		}

	private:
		BSWaterShaderProperty* Ctor()
		{
			using func_t = decltype(&BSWaterShaderProperty::Ctor);
			REL::Relocation<func_t> func{ Offset::BSWaterShaderProperty::Ctor };
			BSWaterShaderProperty*  property = func(this);
			stl::emplace_vtable<BSWaterShaderProperty>(property);
			return property;
		}
	};
	static_assert(sizeof(BSWaterShaderProperty) == 0x100);
}
