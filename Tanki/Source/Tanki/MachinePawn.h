// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "Scorable.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Pawn.h"
#include "MachinePawn.generated.h"

UCLASS()
class TANKI_API AMachinePawn : public APawn, public IIDamageTaker, public IScorable
{
	GENERATED_BODY()

public:
	AMachinePawn();

	virtual void TakeDamage(FDamageData DamageData) override;
	
	void Fire();
	void SetupCannon(TSubclassOf<ACannon> newCannonClass);
	
	//Scorable
	virtual int32 GetPoints() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scorable")
	int32 ScoreValue = 0;//how much points by gets for destroy

	UFUNCTION()
	void ShowScore(int32 Value);	

	int32 Score = 0;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<ACannon> EquippedCannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent*  HealthComponent;
	
	UPROPERTY()
	ACannon* Cannon;
	
	void Die();
	void DamageTaked(float Value);
	
};
