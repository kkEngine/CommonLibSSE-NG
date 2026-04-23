#include "RE/H/hkbClipGenerator.h"

namespace RE
{
	void RE::hkbClipGenerator::AddTrigger(float atLocalTime, const hkbEventBase& event, bool relativeToEndOfClip, bool acyclic, bool isAnnotation)
	{
		REL::Relocation<decltype(&hkbClipGenerator::AddTrigger)> func(RELOCATION_ID(58614, 59264));
		return func(this, atLocalTime, event, relativeToEndOfClip, acyclic, isAnnotation);
	}

	float RE::hkbClipGenerator::GetDurationLocalTime() const
	{
		auto  animation = animationControl->binding ? animationControl->binding->animation.get() : nullptr;
		float duration = animation ? animation->duration : 0.01333f;
		return fmaxf(duration - (animationControl->cropEndAmountLocalTime + animationControl->cropStartAmountLocalTime), 0.0f);
	}

	const hkClass& hkbClipGenerator::StaticClass()
	{
		return *REL::Relocation<hkClass*>(RELOCATION_ID(521225, 407743));
	}

	hkbClipGenerator::hkbClipGenerator()
	{
		stl::emplace_vtable(this);
	}

	const hkClass* hkbClipGenerator::GetClassType() const
	{
		return &hkbClipGenerator::StaticClass();
	}

	void hkbClipGenerator::CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const
	{
		using func_t = decltype(&hkbClipGenerator::CalcContentStatistics);
		REL::Relocation<func_t> func{ RELOCATION_ID(58611, 59261) };
		return func(this, a_collector, a_class);
	}

	void hkbClipGenerator::Activate(const hkbContext& a_context)
	{
		using func_t = decltype(&hkbClipGenerator::Activate);
		REL::Relocation<func_t> func{ RELOCATION_ID(58602, 59252) };
		return func(this, a_context);
	}

	void hkbClipGenerator::Update(const hkbContext& a_context, float a_timestep)
	{
		using func_t = decltype(&hkbClipGenerator::Update);
		REL::Relocation<func_t> func{ RELOCATION_ID(58603, 59253) };
		return func(this, a_context, a_timestep);
	}

	void hkbClipGenerator::Deactivate(const hkbContext& a_context)
	{
		using func_t = decltype(&hkbClipGenerator::Deactivate);
		REL::Relocation<func_t> func{ RELOCATION_ID(58604, 59254) };
		return func(this, a_context);
	}

	bool hkbClipGenerator::IsValid(hkStringPtr& err) const
	{
		using func_t = decltype(&hkbClipGenerator::IsValid);
		REL::Relocation<func_t> func{ RELOCATION_ID(58605, 59255) };
		return func(this, err);
	}

	hkbNode* hkbClipGenerator::CloneNode(hkbBehaviorGraph& rootBehavior) const
	{
		using func_t = decltype(&hkbClipGenerator::CloneNode);
		REL::Relocation<func_t> func{ RELOCATION_ID(58606, 59256) };
		return func(this, rootBehavior);
	}

	hkReferencedObject* hkbClipGenerator::CreateInternalState()
	{
		using func_t = decltype(&hkbClipGenerator::CreateInternalState);
		REL::Relocation<func_t> func{ RELOCATION_ID(59329, 60002) };
		return func(this);
	}

	void hkbClipGenerator::GetInternalState(hkReferencedObject& internalState) const
	{
		using func_t = decltype(&hkbClipGenerator::GetInternalState);
		REL::Relocation<func_t> func{ RELOCATION_ID(59330, 60003) };
		return func(this, internalState);
	}

	void hkbClipGenerator::SetInternalState(const hkReferencedObject& internalState)
	{
		using func_t = decltype(&hkbClipGenerator::SetInternalState);
		REL::Relocation<func_t> func{ RELOCATION_ID(59331, 60004) };
		return func(this, internalState);
	}

	void hkbClipGenerator::Generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset) const
	{
		using func_t = decltype(&hkbClipGenerator::Generate);
		REL::Relocation<func_t> func{ RELOCATION_ID(58607, 59257) };
		return func(this, a_context, activeChildrenOutput, output, timeOffset);
	}

	void hkbClipGenerator::UpdateSync(const hkbContext& a_context, hkbNodeInfo& info)
	{
		using func_t = decltype(&hkbClipGenerator::UpdateSync);
		REL::Relocation<func_t> func{ RELOCATION_ID(58608, 59258) };
		return func(this, a_context, info);
	}

	void hkbClipGenerator::SetLocalTime(float a_time)
	{
		using func_t = decltype(&hkbClipGenerator::SetLocalTime);
		REL::Relocation<func_t> func{ RELOCATION_ID(58609, 59259) };
		return func(this, a_time);
	}

	void hkbClipGenerator::StartEcho()
	{
		using func_t = decltype(&hkbClipGenerator::StartEcho);
		REL::Relocation<func_t> func{ RELOCATION_ID(58610, 59260) };
		return func(this);
	}
}
