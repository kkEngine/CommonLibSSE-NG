#include "RE/B/BGSCreatedObjectManager.h"

namespace RE
{
	BGSCreatedObjectManager* BGSCreatedObjectManager::GetSingleton()
	{
		REL::Relocation<BGSCreatedObjectManager**> singleton{ REL::ID(400320) };
		return *singleton;
	}

	EnchantmentItem* BGSCreatedObjectManager::AddArmorEnchantment(BSTArray<Effect>& a_effects)
	{
		using func_t = decltype(&BGSCreatedObjectManager::AddArmorEnchantment);
		REL::Relocation<func_t> func{ REL::ID(36166) };
		return func(this, a_effects);
	}

	EnchantmentItem* BGSCreatedObjectManager::AddWeaponEnchantment(BSTArray<Effect>& a_effects)
	{
		using func_t = decltype(&BGSCreatedObjectManager::AddWeaponEnchantment);
		REL::Relocation<func_t> func{ REL::ID(36165) };
		return func(this, a_effects);
	}
}
