// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "ThumbnailHelpers.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = sceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}
void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;

	for (uint8 Serial = 0; Serial < FireSerialAmount; Serial++)
	{
		//tut dolzhen bit' tol'ko timer, kotoriy zakomenchen dal'she
		if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace")));
	}

		//GetWorld()->GetTimerManager().SetTimer(SerialTimer, this, &ACannon::Shoot, 1 / (FireRate), false);
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, (1 / FireRate), false);
}
void ACannon::FireSpecial()
{
	if (!IsReadyToFire())
	{
	return;
	}
	bReadyToFire = false;
	
	for (uint8 Serial = 0; Serial < FireSpecialSerialAmount; Serial++)
	{
		//analogichno fire()
		if (CannonType == ECannonType::FireProjectile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Special Fire projectile")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Special Fire trace")));
		}
		
		//GetWorld()->GetTimerManager().SetTimer(SerialTimer, this, &ACannon::ShootSpecial, (1 / FireRate), false);
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / (FireRate * 2), false);
}

void ACannon::Reload()
{
	bReadyToFire = true;
}
bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}
void ACannon::Shoot()
{
	if (CannonType == ECannonType::FireProjectile)
	{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire projectile")));
	}
	else
	{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace")));
	}
}
void ACannon::ShootSpecial()
{
	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Special Fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Special Fire trace")));
	}
}