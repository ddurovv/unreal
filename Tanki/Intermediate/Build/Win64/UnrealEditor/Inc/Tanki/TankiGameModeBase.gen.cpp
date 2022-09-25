// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Tanki/TankiGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTankiGameModeBase() {}
// Cross Module References
	TANKI_API UClass* Z_Construct_UClass_ATankiGameModeBase_NoRegister();
	TANKI_API UClass* Z_Construct_UClass_ATankiGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Tanki();
// End Cross Module References
	void ATankiGameModeBase::StaticRegisterNativesATankiGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATankiGameModeBase);
	UClass* Z_Construct_UClass_ATankiGameModeBase_NoRegister()
	{
		return ATankiGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ATankiGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATankiGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Tanki,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATankiGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TankiGameModeBase.h" },
		{ "ModuleRelativePath", "TankiGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATankiGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATankiGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATankiGameModeBase_Statics::ClassParams = {
		&ATankiGameModeBase::StaticClass,
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
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATankiGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATankiGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATankiGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ATankiGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATankiGameModeBase.OuterSingleton, Z_Construct_UClass_ATankiGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATankiGameModeBase.OuterSingleton;
	}
	template<> TANKI_API UClass* StaticClass<ATankiGameModeBase>()
	{
		return ATankiGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATankiGameModeBase);
	struct Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankiGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankiGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATankiGameModeBase, ATankiGameModeBase::StaticClass, TEXT("ATankiGameModeBase"), &Z_Registration_Info_UClass_ATankiGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATankiGameModeBase), 1258132226U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankiGameModeBase_h_1480799624(TEXT("/Script/Tanki"),
		Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankiGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankiGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
