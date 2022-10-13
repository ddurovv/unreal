// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "ProjectilePool.generated.h"

UCLASS()
class TANKI_API AProjectilePool : public AActor
{
	GENERATED_BODY()
public:
	void GetProjectile(FVector spawnLocation, FRotator spawnRotation);
protected:
	virtual void BeginPlay() override;

	void SpawnProjectile(FVector spawnLocation, FRotator spawnRotation, bool bIsActive = false);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")
	int32 PoolSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")
	TSubclassOf<AProjectile> ProjectileClass;

	TArray<AProjectile*> ProjectilePool;
public:
	void InitializePool();

	bool bHaveActiveProjectile = false;
};
