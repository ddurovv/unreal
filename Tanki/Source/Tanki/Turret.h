// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "IDamageTaker.h"
#include "MachinePawn.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class TANKI_API ATurret : public AMachinePawn
{
	GENERATED_BODY()
	
public:	
	ATurret();

protected:
	virtual void BeginPlay() override;
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool IsPlayerSeen();
	bool CanFire();
	
	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float TargetingRange = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float TargetingSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float TargetingRate = 0.005f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float Accurency = 10.0f;

	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";
};
