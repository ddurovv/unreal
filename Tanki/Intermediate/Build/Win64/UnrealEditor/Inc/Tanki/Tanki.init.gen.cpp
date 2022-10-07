// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTanki_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Tanki;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Tanki()
	{
		if (!Z_Registration_Info_UPackage__Script_Tanki.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Tanki",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x248ECB74,
				0xFF0D0CFD,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Tanki.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Tanki.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Tanki(Z_Construct_UPackage__Script_Tanki, TEXT("/Script/Tanki"), Z_Registration_Info_UPackage__Script_Tanki, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x248ECB74, 0xFF0D0CFD));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
