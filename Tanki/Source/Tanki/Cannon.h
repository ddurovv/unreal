// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "IDamageTaker.h"
#include "ProjectilePool.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UCLASS()
class TANKI_API ACannon : public AActor
{
	GENERATED_BODY()
	DECLARE_EVENT_OneParam(ACannon, FChangeScore, int32);
public:	
	// Sets default values for this actor's properties
	ACannon();
	void Reload();
	bool IsReadyToFire();
	
	void Fire();
	void FireProjectile();
	void FireTrace();
	//void SpecialShoot();
	//void FireSpecial();
	FTimerHandle ReloadTimer;
	FTimerHandle SerialTimer;
	
	void CreateProjectilePool();

	//Scorable
	int32 Score = 0.0f;
	UFUNCTION()
	void AddScore(int32 ScoreValue);
	FChangeScore ScoreChanged;
	
	void SetupAmmo(uint8 Ammo);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Params")
	uint8 Bullets = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<AProjectilePool> ProjectilePoolClass;

	UPROPERTY()
	AProjectilePool* ProjectilePool;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	ECannonType CannonType = ECannonType::FireProjectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Params")
	float FireRate = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Params")
	float FireRange = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Params")
	float FireDamage = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Params")
	uint8 FireSerialAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Params")
	uint8 FireSpecialSerialAmount = 1;
//effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* ShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* ShootEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UCameraShakeBase> CameraShake;	
private:
	bool bReadyToFire = false;
	uint8 currentShootCounter = 0;
	uint8 BulletMax = 0;
};
