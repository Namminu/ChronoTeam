// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TeamChrono/TeamChronoGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTeamChronoGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	TEAMCHRONO_API UClass* Z_Construct_UClass_ATeamChronoGameMode();
	TEAMCHRONO_API UClass* Z_Construct_UClass_ATeamChronoGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_TeamChrono();
// End Cross Module References
	void ATeamChronoGameMode::StaticRegisterNativesATeamChronoGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATeamChronoGameMode);
	UClass* Z_Construct_UClass_ATeamChronoGameMode_NoRegister()
	{
		return ATeamChronoGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATeamChronoGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATeamChronoGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_TeamChrono,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATeamChronoGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATeamChronoGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TeamChronoGameMode.h" },
		{ "ModuleRelativePath", "TeamChronoGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATeamChronoGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATeamChronoGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATeamChronoGameMode_Statics::ClassParams = {
		&ATeamChronoGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATeamChronoGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ATeamChronoGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ATeamChronoGameMode()
	{
		if (!Z_Registration_Info_UClass_ATeamChronoGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATeamChronoGameMode.OuterSingleton, Z_Construct_UClass_ATeamChronoGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATeamChronoGameMode.OuterSingleton;
	}
	template<> TEAMCHRONO_API UClass* StaticClass<ATeamChronoGameMode>()
	{
		return ATeamChronoGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATeamChronoGameMode);
	ATeamChronoGameMode::~ATeamChronoGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_Y_Documents_Unreal_Projects_TeamChrono_Source_TeamChrono_TeamChronoGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Y_Documents_Unreal_Projects_TeamChrono_Source_TeamChrono_TeamChronoGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATeamChronoGameMode, ATeamChronoGameMode::StaticClass, TEXT("ATeamChronoGameMode"), &Z_Registration_Info_UClass_ATeamChronoGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATeamChronoGameMode), 1106035611U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Y_Documents_Unreal_Projects_TeamChrono_Source_TeamChrono_TeamChronoGameMode_h_4268025320(TEXT("/Script/TeamChrono"),
		Z_CompiledInDeferFile_FID_Users_Y_Documents_Unreal_Projects_TeamChrono_Source_TeamChrono_TeamChronoGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Y_Documents_Unreal_Projects_TeamChrono_Source_TeamChrono_TeamChronoGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
