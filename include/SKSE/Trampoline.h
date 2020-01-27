#pragma once

#include <mutex>
#include <string>
#include <type_traits>


namespace SKSE
{
	namespace Impl
	{
		class TrampolineLogger;
	}


	class Trampoline
	{
	public:
		Trampoline();
		Trampoline(const Trampoline&) = delete;
		Trampoline(Trampoline&& a_rhs);
		explicit Trampoline(std::string_view a_name);

		Trampoline& operator=(const Trampoline&) = delete;
		Trampoline& operator=(Trampoline&& a_rhs);

		bool Create(std::size_t a_size);
		bool Create(std::size_t a_size, void* a_module);

		void SetTrampoline(void* a_trampoline, std::size_t a_size, bool a_takeOwnership = false);

		[[nodiscard]] void* Allocate(std::size_t a_size);
		template <class T> [[nodiscard]] T* Allocate() { return static_cast<T*>(Allocate(sizeof(T))); }

		[[nodiscard]] void* StartAlloc();
		template <class T> [[nodiscard]] T* StartAlloc() { return static_cast<T*>(StartAlloc()); }
		void EndAlloc(std::size_t a_size);
		void EndAlloc(const void* a_end);

		[[nodiscard]] std::size_t Capacity() const;
		[[nodiscard]] std::size_t AllocatedSize() const;
		[[nodiscard]] std::size_t FreeSize() const;

		bool Write5Branch(std::uintptr_t a_src, std::uintptr_t a_dst);
		bool Write5Call(std::uintptr_t a_src, std::uintptr_t a_dst);
		bool Write6Branch(std::uintptr_t a_src, std::uintptr_t a_dst);
		bool Write6Call(std::uintptr_t a_src, std::uintptr_t a_dst);

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		bool Write5Branch(std::uintptr_t a_src, F* a_dst) { return Write5Branch(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		bool Write5Call(std::uintptr_t a_src, F* a_dst) { return Write5Call(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		bool Write6Branch(std::uintptr_t a_src, F* a_dst) { return Write6Branch(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		bool Write6Call(std::uintptr_t a_src, F* a_dst) { return Write6Call(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write5BranchEx(std::uintptr_t a_src, std::uintptr_t a_dst) { return Write5BranchEx_Impl<F>(a_src, a_dst, static_cast<std::uint8_t>(0xE9)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write5BranchEx(std::uintptr_t a_src, F* a_dst) { return Write5BranchEx<F>(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write5CallEx(std::uintptr_t a_src, std::uintptr_t a_dst) { return Write5BranchEx_Impl<F>(a_src, a_dst, static_cast<std::uint8_t>(0xE8)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write5CallEx(std::uintptr_t a_src, F* a_dst) { return Write5CallEx<F>(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write6BranchEx(std::uintptr_t a_src, std::uintptr_t a_dst) { return Write6BranchEx_Impl<F>(a_src, a_dst, static_cast<std::uint8_t>(0x25)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write6BranchEx(std::uintptr_t a_src, F* a_dst) { return Write6BranchEx<F>(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write6CallEx(std::uintptr_t a_src, std::uintptr_t a_dst) { return Write6BranchEx_Impl<F>(a_src, a_dst, static_cast<std::uint8_t>(0x15)); }

		template <class F, typename std::enable_if_t<std::is_function<F>::value, int> = 0>
		F* Write6CallEx(std::uintptr_t a_src, F* a_dst) { return Write6CallEx<F>(a_src, unrestricted_cast<std::uintptr_t>(a_dst)); }

	private:
		friend class Impl::TrampolineLogger;


		using Lock = std::recursive_mutex;
		using Locker = std::lock_guard<Lock>;


		void* Create_Impl(std::size_t a_size, std::uintptr_t a_address);

		[[nodiscard]] void* Allocate_Impl(std::size_t a_size);

		[[nodiscard]] void* StartAlloc_Impl();
		void EndAlloc_Impl(std::size_t a_size);

		[[nodiscard]] std::size_t Capacity_Impl() const;
		[[nodiscard]] std::size_t AllocatedSize_Impl() const;
		[[nodiscard]] std::size_t FreeSize_Impl() const;

		bool Write5Branch_Impl(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_opcode);
		bool Write6Branch_Impl(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_modrm);

		void LogStats() const;
		void TryRelease();
		bool IsDisplacementInRange(std::ptrdiff_t a_disp) const;

		template <class F>
		F* Write5BranchEx_Impl(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_opcode)
		{
			auto disp = reinterpret_cast<std::int32_t*>(a_src + 1);
			auto nextOp = a_src + 5;
			auto func = unrestricted_cast<F*>(nextOp + *disp);
			return Write5Branch_Impl(a_src, a_dst, a_opcode) ? func : 0;
		}

		template <class F>
		F* Write6BranchEx_Impl(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_modrm)
		{
			auto disp = reinterpret_cast<std::int32_t*>(a_src + 2);
			auto nextOp = a_src + 6;
			auto func = unrestricted_cast<F*>(nextOp + *disp);
			return Write6Branch_Impl(a_src, a_dst, a_modrm) ? func : 0;
		}


		static constexpr auto END_ALLOC_TAG = static_cast<std::size_t>(0);

		mutable Lock _lock;
		std::string _name;
		std::uint8_t* _data;
		std::size_t _capacity;
		std::size_t _size;
		bool _allocating;
		bool _freeAlloc;
	};
}