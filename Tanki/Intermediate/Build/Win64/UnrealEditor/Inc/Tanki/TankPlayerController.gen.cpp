// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Tanki/TankPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTankPlayerController() {}
// Cross Module References
	TANKI_API UClass* Z_Construct_UClass_ATankPlayerController_NoRegister();
	TANKI_API UClass* Z_Construct_UClass_ATankPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_Tanki();
// End Cross Module References
	void ATankPlayerController::StaticRegisterNativesATankPlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATankPlayerController);
	UClass* Z_Construct_UClass_ATankPlayerController_NoRegister()
	{
		return ATankPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ATankPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATankPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_Tanki,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATankPlayerController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "TankPlayerController.h" },
		{ "ModuleRelativePath", "TankPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATankPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATankPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATankPlayerController_Statics::ClassParams = {
		&ATankPlayerController::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATankPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATankPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATankPlayerController()
	{
		if (!Z_Registration_Info_UClass_ATankPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATankPlayerController.OuterSingleton, Z_Construct_UClass_ATankPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATankPlayerController.OuterSingleton;
	}
	template<> TANKI_API UClass* StaticClass<ATankPlayerController>()
	{
		return ATankPlayerController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATankPlayerController);
	struct Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATankPlayerController, ATankPlayerController::StaticClass, TEXT("ATankPlayerController"), &Z_Registration_Info_UClass_ATankPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATankPlayerController), 1438342614U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankPlayerController_h_3370983341(TEXT("/Script/Tanki"),
		Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Tanki_Source_Tanki_TankPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
