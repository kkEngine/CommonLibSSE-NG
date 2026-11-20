#include "RE/T/TESFile.h"

namespace RE
{
	bool TESFile::CloseTES(bool a_force)
	{
		using func_t = decltype(&TESFile::CloseTES);
		REL::Relocation<func_t> func{ REL::ID(13933) };
		return func(this, a_force);
	}

	TESFile* TESFile::Duplicate(std::uint32_t a_cacheSize)
	{
		using func_t = decltype(&TESFile::Duplicate);
		REL::Relocation<func_t> func{ Offset::TESFile::Duplicate };
		return func(this, a_cacheSize);
	}

	std::uint32_t TESFile::GetCurrentSubRecordType()
	{
		using func_t = decltype(&TESFile::GetCurrentSubRecordType);
		REL::Relocation<func_t> func{ Offset::TESFile::GetCurrentSubRecordType };
		return func(this);
	}

	FormType TESFile::GetFormType()
	{
		using func_t = decltype(&TESFile::GetFormType);
		REL::Relocation<func_t> func{ Offset::TESFile::GetFormType };
		return func(this);
	}

	bool TESFile::IsFormInMod(FormID a_formID) const
	{
		if (!IsLight() && (a_formID >> 24) == compileIndex) {
			return true;
		}
		if (IsLight() && (a_formID >> 24) == 0xFE && ((a_formID & 0x00FFF000) >> 12) == smallFileCompileIndex) {
			return true;
		}
		return false;
	}

	bool TESFile::OpenTES(NiFile::OpenMode a_accessMode, bool a_lock)
	{
		using func_t = decltype(&TESFile::OpenTES);
		REL::Relocation<func_t> func{ REL::ID(13931) };
		return func(this, a_accessMode, a_lock);
	}

	bool TESFile::ReadData(void* a_buf, std::uint32_t a_size)
	{
		using func_t = decltype(&TESFile::ReadData);
		REL::Relocation<func_t> func{ Offset::TESFile::ReadData };
		return func(this, a_buf, a_size);
	}

	bool TESFile::Seek(std::uint32_t a_offset)
	{
		using func_t = decltype(&TESFile::Seek);
		REL::Relocation<func_t> func{ Offset::TESFile::Seek };
		return func(this, a_offset);
	}

	bool TESFile::SeekNextForm(bool a_skipIgnored)
	{
		// AE 1.7.99 reads a third argument (r8b), pass false like the game's own callers
		constexpr bool kSkipFirstSubrecordRead = false;

		using func_t = bool (*)(TESFile*, bool, bool);
		REL::Relocation<func_t> func{ REL::ID(13979) };
		return func(this, a_skipIgnored, kSkipFirstSubrecordRead);
	}

	bool TESFile::SeekNextSubrecord()
	{
		using func_t = decltype(&TESFile::SeekNextSubrecord);
		REL::Relocation<func_t> func{ Offset::TESFile::SeekNextSubrecord };
		return func(this);
	}
}
