#pragma once

#include "REL/ID.h"

namespace RE::Offset
{
	namespace Actor
	{
		constexpr auto AddSpell = REL::ID(38716);
		constexpr auto DispelWornItemEnchantments = REL::ID(34620);
		constexpr auto DoReset3D = REL::ID(40255);
		constexpr auto GetGhost = REL::ID(37275);
		constexpr auto GetHostileToActor = REL::ID(37537);
		constexpr auto GetLevel = REL::ID(37334);
		constexpr auto HasPerk = REL::ID(37698);
		constexpr auto IsRunning = REL::ID(37234);
		constexpr auto RequestDetectionLevel = REL::ID(37764);
		constexpr auto SwitchRace = REL::ID(37925);
		constexpr auto UpdateArmorAbility = REL::ID(38751);
		constexpr auto UpdateWeaponAbility = REL::ID(38752);
	}

	namespace ActorEquipManager
	{
		constexpr auto EquipObject = REL::ID(38894);
		constexpr auto Singleton = REL::ID(400636);
		constexpr auto UnequipObject = REL::ID(38901);
	}

	namespace ActorValueOwner
	{
		constexpr auto GetClampedActorValue = REL::ID(27284);
	}

	namespace AIProcess
	{
		constexpr auto SetBaseScale = REL::ID(39588);
		constexpr auto Update3DModel = REL::ID(39395);
	}

	namespace AnimationSetDataSingleton
	{
		constexpr auto Singleton = REL::ID(401554);
	}

	namespace BGSFootstepManager
	{
		constexpr auto Singleton = REL::ID(403553);
	}

	namespace BGSListForm
	{
		constexpr auto AddForm = REL::ID(20913);
	}

	namespace BGSSaveLoadManager
	{
		constexpr auto Save = REL::ID(35727);
		constexpr auto Singleton = REL::ID(403340);
		constexpr auto Load = REL::ID(35728);
	}

	namespace BGSSkillPerkTreeNode
	{
		constexpr auto Ctor = REL::ID(27263);
	}

	namespace BGSStoryEventManager
	{
		constexpr auto AddEvent = REL::ID(32359);
		constexpr auto GetSingleton = REL::ID(22790);
	}

	namespace BGSStoryTeller
	{
		constexpr auto BeginShutDownQuest = REL::ID(32486);
		constexpr auto BeginStartUpQuest = REL::ID(32485);
		constexpr auto Singleton = REL::ID(400476);
	}

	namespace BipedAnim
	{
		constexpr auto Dtor = REL::ID(15656);
		constexpr auto RemoveAllParts = REL::ID(15659);
	}

	namespace BSAudioManager
	{
		constexpr auto GetSingleton = REL::ID(67652);
		constexpr auto BuildSoundDataFromDescriptor = REL::ID(67666);
	}

	namespace BSInputDeviceManager
	{
		constexpr auto Singleton = REL::ID(402776);
	}

	namespace BSLightingShaderMaterialBase
	{
		constexpr auto CreateMaterial = REL::ID(106723);
	}

	namespace BSReadWriteLock
	{
		constexpr auto LockForRead = REL::ID(68233);
		constexpr auto LockForWrite = REL::ID(68234);
		constexpr auto UnlockForRead = REL::ID(68239);
		constexpr auto UnlockForWrite = REL::ID(68240);
	}

	namespace BSResourceNiBinaryStream
	{
		constexpr auto Ctor = REL::ID(71014);
		constexpr auto Dtor = REL::ID(71016);
		constexpr auto Seek = REL::ID(71018);
		constexpr auto SetEndianSwap = REL::ID(71021);
	}

	namespace BSScaleformTranslator
	{
		constexpr auto GetCachedString = REL::ID(443410);  // 69188 never existed in the AE libraries
	}

	namespace BSScript
	{
		namespace ObjectBindPolicy
		{
			constexpr auto BindObject = REL::ID(104184);
		}

		namespace NF_util
		{
			namespace NativeFunctionBase
			{
				constexpr auto Call = REL::ID(104651);
			}
		}

		namespace Stack
		{
			constexpr auto Dtor = REL::ID(104480);
		}
	}

	namespace BSSoundHandle
	{
		constexpr auto IsValid = REL::ID(67621);
		constexpr auto Play = REL::ID(67616);
		constexpr auto SetObjectToFollow = REL::ID(67636);
		constexpr auto SetPosition = REL::ID(67631);
		constexpr auto Pause = REL::ID(67618);
		constexpr auto Stop = REL::ID(67619);
	}

	namespace BSString
	{
		constexpr auto Set_CStr = REL::ID(11044);
	}

	namespace BSWaterShaderProperty
	{
		constexpr auto Ctor = REL::ID(106942);
	}

	namespace BucketTable
	{
		constexpr auto GetSingleton = REL::ID(69200);
	}

	namespace BSWin32SaveDataSystemUtility
	{
		constexpr auto GetSingleton = REL::ID(109278);
	}

	namespace Calendar
	{
		constexpr auto Singleton = REL::ID(400447);
	}

	namespace Console
	{
		constexpr auto SelectedRef = REL::ID(504099);
		constexpr auto SetSelectedRef = REL::ID(51093);
		constexpr auto SelectReference = REL::ID(51089);
	}

	namespace ConsoleLog
	{
		constexpr auto Singleton = REL::ID(401203);
		constexpr auto VPrint = REL::ID(51110);
	}

	namespace ControlMap
	{
		constexpr auto Singleton = REL::ID(400863);
	}

	namespace CraftingSubMenus
	{
		namespace EnchantConstructMenu
		{
			constexpr auto RenameItem = REL::ID(51415);
			constexpr auto UpdateInterface = REL::ID(51459);
		}
	}

	namespace CRC32Calculator
	{
		constexpr auto SizeOf32 = REL::ID(12141);
		constexpr auto SizeOf64 = REL::ID(68221);
		constexpr auto SizeOfSize = REL::ID(68219);
	}

	namespace ExtraDataList
	{
		constexpr auto Add = REL::ID(12315);
		constexpr auto SetCount = REL::ID(11617);
		constexpr auto SetExtraFlags = REL::ID(12042);
		constexpr auto SetInventoryChanges = REL::ID(11600);
	}

	namespace GameSettingCollection
	{
		constexpr auto Singleton = REL::ID(400782);
	}

	namespace GASActionBufferData
	{
		constexpr auto Vtbl = REL::ID(242366);
	}

	namespace GASDoAction
	{
		constexpr auto Vtbl = REL::ID(242413);
	}

	namespace GASDoInitAction
	{
		constexpr auto Vtbl = REL::ID(242414);
	}

	namespace GFxInitImportActions
	{
		constexpr auto Vtbl = REL::ID(244866);
	}

	namespace GFxLoader
	{
		constexpr auto CreateMovie = REL::ID(84640);
	}

	namespace GFxMovieView
	{
		constexpr auto InvokeNoReturn = REL::ID(82665);
	}

	namespace GFxPlaceObject2
	{
		constexpr auto Vtbl = REL::ID(242592);
	}

	namespace GFxPlaceObject3
	{
		constexpr auto Vtbl = REL::ID(242593);
	}

	namespace GFxRemoveObject
	{
		constexpr auto Vtbl = REL::ID(244863);
	}

	namespace GFxRemoveObject2
	{
		constexpr auto Vtbl = REL::ID(244864);
	}

	namespace GFxSetBackgroundColor
	{
		constexpr auto Vtbl = REL::ID(244865);
	}

	namespace GFxValue
	{
		namespace ObjectInterface
		{
			constexpr auto AttachMovie = REL::ID(82219);
			constexpr auto DeleteMember = REL::ID(82230);
			constexpr auto GetArraySize = REL::ID(82237);
			constexpr auto GetCxform = REL::ID(82238);
			constexpr auto GetDisplayInfo = REL::ID(82239);
			constexpr auto GetDisplayMatrix = REL::ID(82240);
			constexpr auto GetElement = REL::ID(82241);
			constexpr auto GetMember = REL::ID(82245);
			constexpr auto GotoAndPlay = REL::ID(82253);
			constexpr auto HasMember = REL::ID(82254);
			constexpr auto Invoke = REL::ID(82256);
			constexpr auto ObjectAddRef = REL::ID(82269);
			constexpr auto ObjectRelease = REL::ID(82270);
			constexpr auto PushBack = REL::ID(82273);
			constexpr auto RemoveElements = REL::ID(82280);
			constexpr auto SetArraySize = REL::ID(82285);
			constexpr auto SetCxform = REL::ID(82286);
			constexpr auto SetDisplayInfo = REL::ID(82287);
			constexpr auto SetDisplayMatrix = REL::ID(82288);
			constexpr auto SetElement = REL::ID(82289);
			constexpr auto SetMember = REL::ID(82292);
			constexpr auto SetText = REL::ID(82293);
			constexpr auto VisitMembers = REL::ID(82302);
		}
	}

	namespace GMemory
	{
		constexpr auto GlobalHeap = REL::ID(412058);
	}

	namespace hkReferencedObject
	{
		constexpr auto AddReference = REL::ID(57010);
		constexpr auto RemoveReference = REL::ID(57011);
	}

	namespace ImageSpaceEffectManager
	{
		constexpr auto Singleton = REL::ID(414660);
	}

	namespace INIPrefSettingCollection
	{
		constexpr auto Singleton = REL::ID(410219);
	}

	namespace INISettingCollection
	{
		constexpr auto Singleton = REL::ID(411155);
	}

	namespace InterfaceStrings
	{
		constexpr auto Singleton = REL::ID(400446);
	}

	namespace Inventory
	{
		constexpr auto GetEventSource = REL::ID(16225);
	}

	namespace InventoryChanges
	{
		constexpr auto GetNextUniqueID = REL::ID(16148);
		constexpr auto SendContainerChangedEvent = REL::ID(16149);
		constexpr auto SetUniqueID = REL::ID(16149);
		constexpr auto TransferItemUID = REL::ID(16149);
	}

	namespace ItemCrafted
	{
		constexpr auto GetEventSource = REL::ID(51403);
	}

	namespace ItemList
	{
		constexpr auto Update = REL::ID(51031);
	}

	namespace ItemsPickpocketed
	{
		constexpr auto GetEventSource = REL::ID(51183);
	}

	namespace LocalMapCamera
	{
		constexpr auto Ctor = REL::ID(16325);
		constexpr auto SetNorthRotation = REL::ID(16330);
	}

	namespace MagicFavorites
	{
		constexpr auto Singleton = REL::ID(403337);
	}

	namespace MagicItem
	{
		constexpr auto CalculateCost = REL::ID(11321);
		constexpr auto GetCostliestEffectItem = REL::ID(11335);
	}

	namespace MagicTarget
	{
		constexpr auto HasMagicEffect = REL::ID(34517);
	}

	namespace Main
	{
		constexpr auto Singleton = REL::ID(403449);
	}

	namespace MenuControls
	{
		constexpr auto Singleton = REL::ID(401263);
	}

	namespace MessageDataFactoryManager
	{
		constexpr auto GetSingleton = REL::ID(52875);
	}

	namespace NiAVObject
	{
		constexpr auto SetMotionType = REL::ID(77866);
		constexpr auto Update = REL::ID(70251);
	}

	namespace NiCamera
	{
		constexpr auto WorldPtToScreenPt3 = REL::ID(70640);
	}

	namespace NiMemManager
	{
		constexpr auto Singleton = REL::ID(410319);
	}

	namespace NiNode
	{
		constexpr auto Ctor = REL::ID(70287);
	}

	namespace NiPoint3
	{
		constexpr auto Zero = REL::ID(410468);
	}

	namespace NiRefObject
	{
		constexpr auto TotalObjectCount = REL::ID(410493);
	}

	namespace NiSkinInstance
	{
		constexpr auto Ctor = REL::ID(71227);
	}

	namespace PlayerCamera
	{
		constexpr auto Singleton = REL::ID(400802);
		constexpr auto UpdateThirdPerson = REL::ID(50841);
	}

	namespace PlayerCharacter
	{
		namespace PlayerSkills
		{
			constexpr auto AdvanceLevel = REL::ID(41567);
		}

		constexpr auto ActivatePickRef = REL::ID(40548);
		constexpr auto GetArmorValue = REL::ID(40249);
		constexpr auto GetDamage = REL::ID(40253);
		constexpr auto GetNumTints = REL::ID(40700);
		constexpr auto GetTintMask = REL::ID(40698);
		constexpr auto PlayPickupEvent = REL::ID(40456);
		constexpr auto Singleton = REL::ID(403521);
		constexpr auto StartGrabObject = REL::ID(40552);
	}

	namespace PlayerControls
	{
		constexpr auto Ctor = REL::ID(42336);
		constexpr auto Singleton = REL::ID(400864);
	}

	namespace RaceSexMenu
	{
		constexpr auto ChangeName = REL::ID(52415);
	}

	namespace ReferenceEffectController
	{
		constexpr auto Start = REL::ID(34761);
	}

	namespace Script
	{
		constexpr auto CompileAndRun = REL::ID(441582);
		constexpr auto GetProcessScripts = REL::ID(21921);
		constexpr auto SetProcessScripts = REL::ID(21920);
	}

	namespace SCRIPT_FUNCTION
	{
		constexpr auto FirstConsoleCommand = REL::ID(365650);
		constexpr auto FirstScriptCommand = REL::ID(361120);
	}

	namespace Sky
	{
		constexpr auto GetSingleton = REL::ID(13878);
		constexpr auto SetWeather = REL::ID(26241);
		constexpr auto ForceWeather = REL::ID(26243);
		constexpr auto ResetWeather = REL::ID(26242);
		constexpr auto SunriseBeginTime = REL::ID(401655);
		constexpr auto SunriseEndTime = REL::ID(401656);
		constexpr auto SunsetBeginTime = REL::ID(401657);
		constexpr auto SunsetEndTime = REL::ID(401658);
		constexpr auto DayBeginTime = REL::ID(401659);
		constexpr auto NightBeginTime = REL::ID(401660);
	}

	namespace SkyrimVM
	{
		constexpr auto QueuePostRenderCall = REL::ID(53955);
		constexpr auto RelayEvent = REL::ID(54033);
		constexpr auto Singleton = REL::ID(400475);
	}

	namespace TES
	{
		constexpr auto Singleton = REL::ID(403450);
	}

	namespace TESCamera
	{
		constexpr auto SetState = REL::ID(33026);
	}

	namespace TESDataHandler
	{
		constexpr auto LoadScripts = REL::ID(13766);
		constexpr auto Singleton = REL::ID(400269);
	}

	namespace TESDescription
	{
		constexpr auto GetDescription = REL::ID(14552);
	}

	namespace TESFile
	{
		constexpr auto Duplicate = REL::ID(14018);
		constexpr auto GetCurrentSubRecordType = REL::ID(13988);
		constexpr auto GetFormType = REL::ID(13982);
		constexpr auto ReadData = REL::ID(13991);
		constexpr auto Seek = REL::ID(13984);
		constexpr auto SeekNextSubrecord = REL::ID(13990);
	}

	namespace TESHavokUtilities
	{
		constexpr auto FindCollidableRef = REL::ID(26003);
	}

	namespace TESNPC
	{
		constexpr auto ChangeHeadPart = REL::ID(24750);
		constexpr auto GetBaseOverlays = REL::ID(24791);
		constexpr auto GetNumBaseOverlays = REL::ID(24792);
		constexpr auto HasOverlays = REL::ID(24790);
		constexpr auto SetSkinFromTint = REL::ID(24710);
		constexpr auto UpdateNeck = REL::ID(24711);
	}

	namespace TESObjectREFR
	{
		constexpr auto FindReferenceFor3D = REL::ID(19750);
		constexpr auto GetDisplayFullName = REL::ID(19781);
		constexpr auto GetLock = REL::ID(20223);
		constexpr auto GetOwner = REL::ID(20194);
		constexpr auto GetStealValue = REL::ID(16045);
		constexpr auto InitInventoryIfRequired = REL::ID(16038);
		constexpr auto MoveTo = REL::ID(56626);
		constexpr auto PlayAnimation = REL::ID(14297);
		constexpr auto SetScale = REL::ID(19665);
		constexpr auto Enable = REL::ID(19800);
	}

	namespace TESQuest
	{
		constexpr auto EnsureQuestStarted = REL::ID(25003);
		constexpr auto ResetQuest = REL::ID(25014);
	}

	namespace TESWaterForm
	{
		constexpr auto FillMaterial = REL::ID(20373);
	}

	namespace UI
	{
		constexpr auto Singleton = REL::ID(400327);
	}

	namespace UIBlurManager
	{
		constexpr auto DecrementBlurCount = REL::ID(52777);
		constexpr auto IncrementBlurCount = REL::ID(52776);
		constexpr auto Singleton = REL::ID(403350);
	}

	namespace UIMessageQueue
	{
		constexpr auto AddMessage = REL::ID(13631);
		constexpr auto CreateUIMessageData = REL::ID(82169);
		constexpr auto ProcessCommands = REL::ID(82167);
		constexpr auto Singleton = REL::ID(400445);
	}

	namespace UserEvents
	{
		constexpr auto Singleton = REL::ID(402638);
	}

	constexpr auto CreateRefHandle = REL::ID(12326);
	constexpr auto DebugNotification = REL::ID(52933);
	constexpr auto LookupReferenceByHandle = REL::ID(12332);
	constexpr auto PlaySound = REL::ID(52939);
	constexpr auto TlsIndex = REL::ID(415542);
	constexpr auto VisibilityFlag = REL::ID(400942);
	constexpr auto ImageSpaceEOFEffectsEnabledFlag = REL::ID(391055);
	constexpr auto Texture3dAccumulationVolumetricLightingEnabledFlag = REL::ID(414913);
	constexpr auto ScreenRaymarchingVolumetricLightingEnabledFlag = REL::ID(415135);
	constexpr auto SAOApplyFogEnabledFlag = REL::ID(415070);
	constexpr auto HDREnabledFlag = REL::ID(391301);
	constexpr auto OnQuitGame = REL::ID(36551);
	constexpr auto WinMain = REL::ID(36544);
	constexpr auto D3D11Device = REL::ID(411348);
	constexpr auto D3D11DeviceContext = REL::ID(524729);
	constexpr auto RendererStateInstance = REL::ID(388819);
	constexpr auto NiObjectConstructorRegistry = REL::ID(410484);
	constexpr auto GlobalStateCounter = REL::ID(400305);
}
