// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "Projectile.h"
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
	SetupAmmo(3);
}
void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;

	if (Bullets > 0)
	{
		for (uint8 Serial = 0; Serial < FireSerialAmount; Serial++)
		{
			if (CannonType == ECannonType::FireProjectile)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire projectile")));
				FActorSpawnParameters spawnParam;
				spawnParam.Owner = this;
				AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), spawnParam);
				if (projectile)
				{
					projectile->Start();
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace")));
				FHitResult hitResult;
				FCollisionQueryParams traceParams;
				traceParams.bTraceComplex = true;
				traceParams.bReturnPhysicalMaterial = false;

				FVector start = ProjectileSpawnPoint->GetComponentLocation();
				FVector end = start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

				if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_GameTraceChannel1, traceParams))
				{
					DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Purple, false, 2.0f, 0, 4.0f);
					if (hitResult.GetActor())
					{
						UE_LOG(LogTemp, Warning, TEXT("Projectile overlap : %s"), *hitResult.GetActor()->GetName());
						hitResult.GetActor()->Destroy();
					}
				}
				else
				{
					DrawDebugLine(GetWorld(), start, end, FColor::Blue, false, 2.0f, 0, 4.0f);
				}
			} 

			//GetWorld()->GetTimerManager().SetTimer(SerialTimer, this, &ACannon::Shoot, 1 / (FireRate), false);
		}
		Bullets-= 1;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Out of ammo!!!")));
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, (1 / FireRate), false);
}

void ACannon::Reload()
{
	bReadyToFire = true;
}
bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}
/*void ACannon::Shoot()
{
	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire projectile")));
		FActorSpawnParameters spawnParam;
		spawnParam.Owner = this;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), spawnParam);
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace")));
		FHitResult hitResult;
		FCollisionQueryParams traceParams;
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_GameTraceChannel1, traceParams))
		{
			DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Purple, false, 2.0f, 0, 4.0f);
			if (hitResult.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("Projectile overlap : %s"), *hitResult.GetActor()->GetName());
				hitResult.GetActor()->Destroy();
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), start, end, FColor::Blue, false, 2.0f, 0, 4.0f);
		}
	} 
}*/

void ACannon::SetupAmmo(uint8 Ammo)
{
	if (Ammo > 0) {
		Bullets = Ammo;
	}
	else GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Ammo is null")));
}
/*void ACannon::ShootSpecial()
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
}*/
/*void ACannon::FireSpecial()
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
}*/