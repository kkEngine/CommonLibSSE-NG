#pragma once

#include "REL/Module.h"

namespace REL
{
	class Offset
	{
	public:
		constexpr Offset() noexcept = default;

		explicit constexpr Offset(std::size_t a_offset) noexcept:
			_offset(a_offset)
		{}

		constexpr Offset& operator=(std::size_t a_offset) noexcept
		{
			_offset = a_offset;
			return *this;
		}

		[[nodiscard]] std::uintptr_t address() const { return base() + offset(); }

		[[nodiscard]] constexpr std::size_t offset() const noexcept { return _offset; }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::size_t _offset{0};
	};

	class VariantOffset
	{
	public:
		constexpr VariantOffset() noexcept = default;

		explicit constexpr VariantOffset(
			[[maybe_unused]] std::size_t a_seOffset,
			[[maybe_unused]] std::size_t a_aeOffset,
			[[maybe_unused]] std::size_t a_vrOffset) noexcept
		{
			_aeOffset = a_aeOffset;
		}

		[[nodiscard]] std::uintptr_t address() const
		{
			auto thisOffset = offset();
			return thisOffset ? base() + thisOffset : 0;
		}

		[[nodiscard]] constexpr std::size_t offset() const noexcept
		{
			switch (Module::GetRuntime()) {
				case Module::Runtime::AE:
					return _aeOffset;
				default:
					return 0;
			}
		}

		[[nodiscard]] constexpr explicit operator Offset() const noexcept { return Offset(offset()); }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::size_t _aeOffset{0};
	};
}
