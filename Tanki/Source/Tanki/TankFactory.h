// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "TankPawn.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "TankFactory.generated.h"

UCLASS()
class TANKI_API ATankFactory : public AActor, public IIDamageTaker
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankFactory();

	UFUNCTION()
	virtual void TakeDamage(FDamageData DamageData) override;

protected:
	virtual void BeginPlay() override;
	void SpawnTank();
	
	UFUNCTION()
	void Die();

	UFUNCTION()
	void DamageTaked(float DamageValue);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* FactoryMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* TankSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn params")
	TSubclassOf<class ATankPawn> SpawnTankClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn params")
	float SpawnTankRate = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn params")
	TArray<ATargetPoint*> TankWayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLoader")
	class AMapLoader* MapLoader;	
};
