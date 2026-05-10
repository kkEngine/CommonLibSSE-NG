#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTexture.h"

struct ID3D11Resource;
struct ID3D11UnorderedAccessView;

namespace RE
{
	namespace BSGraphics
	{
		class Texture
		{
		public:
			ID3D11Resource*            texture;       // 00 - can be ID3D11Texture1D/ID3D11Texture2D/ID3D11Texture3D
			ID3D11UnorderedAccessView* UAV;           // 08
			ID3D11ShaderResourceView*  resourceView;  // 10
			uint16_t                   height;        // 18
			uint16_t                   width;         // 1A
			uint8_t                    mips;          // 1C
			uint8_t                    format;        // 1D
			uint16_t                   unk1E;         // 1E
			std::uint32_t              refCount;      // 20
			std::uint32_t              pad24;         // 24
		};
		static_assert(sizeof(Texture) == 0x28);
	}

	namespace BSResource
	{
		class Stream;
	}

	NiSmartPointer(NiSourceTexture);

	class NiSourceTexture : public NiTexture
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiSourceTexture;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiSourceTexture;

		static void Load(const BSFixedString& path, bool unk01, NiPointer<NiSourceTexture>& texture, bool isCubemap)
		{
			using func_t = decltype(&NiSourceTexture::Load);
			REL::Relocation<func_t> func{ RELOCATION_ID(98986, 105640) };
			func(path, unk01, texture, isCubemap);
		}

		~NiSourceTexture() override;  // 00

		// override (NiTexture)
		const NiRTTI* GetRTTI() const override;  // 02
		void          Unk_25(void) override;     // 25 - { return 0; }
		void          Unk_26(void) override;     // 26 - { return 0; }
		void          Unk_27(void) override;     // 27
		void          Unk_28(void) override;     // 28
		void          Unk_29(void) override;     // 29 - { return; }
		void          Unk_2A(void) override;     // 2A - { return; }

		// members
		BSResource::Stream*  unk40;            // 40
		BSGraphics::Texture* rendererTexture;  // 48
		std::uint8_t         flags;            // 50
		std::uint8_t         pad51;            // 51
		std::uint16_t        pad52;            // 52
		std::uint32_t        pad54;            // 54
	};
	static_assert(sizeof(NiSourceTexture) == 0x58);
}
