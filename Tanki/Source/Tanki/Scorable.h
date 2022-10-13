// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Scorable.generated.h"

UINTERFACE(MinimalAPI)
class UScorable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANKI_API IScorable
{
	GENERATED_BODY()

public:
	virtual int32 GetPoints() = 0;
};
