#pragma once

namespace RE
{
	// This class is used to store a char* c-string.
	// It automatically handles allocations and deallocation of
	// stored c-string. The string memory may be externally or internally
	// allocated, the lowest bit of the pointer being used as a
	// should-deallocate flag. This simplifies destruction of objects
	// which may be allocated in a packfile for instance.
	class hkStringPtr
	{
	public:
		// member types
		using size_type = std::int32_t;

		hkStringPtr() = default;
		hkStringPtr(const char* a_data);
		hkStringPtr(const char* a_data, size_type len = -1);
		hkStringPtr(const hkStringPtr& other);
		~hkStringPtr();

		// member types
		using size_type = std::int32_t;

		hkStringPtr& operator=(const char* s);
		hkStringPtr& operator=(const hkStringPtr& s);

		// members access
		[[nodiscard]] const char* data() const noexcept;
		[[nodiscard]] const char* c_str() const noexcept;

		// capacity
		[[nodiscard]] bool      empty() const noexcept;
		[[nodiscard]] size_type size() const;
		[[nodiscard]] size_type length() const;

		void assign(const char* a_data, size_type len, bool copy);

	protected:
		enum
		{
			kManaged = 1 << 0
		};

		const char* _data{ nullptr };  // 0

	private:
		bool  should_deallocate() const;
		char* strDup(const char* a_data);
		char* strNdup(const char* a_data, size_type len);
	};
	static_assert(sizeof(hkStringPtr) == 0x8);

	bool operator==(const hkStringPtr& lhs, const hkStringPtr& rhs);
}
