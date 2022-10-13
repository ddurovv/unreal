// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "UObject/Interface.h"
#include "IDamageTaker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDamageTaker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANKI_API IIDamageTaker
{
	GENERATED_BODY()
public:
	virtual void TakeDamage(FDamageData DamageData) = 0;
};
