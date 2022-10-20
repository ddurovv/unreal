// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "Projectile.h"
#include "ThumbnailHelpers.h"
#include "TimerManager.h"
#include "IDamageTaker.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = sceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);

	ShootSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootSound"));
	ShootSound->SetAutoActivate(false);
	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect"));
	ShootEffect->SetAutoActivate(false);
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);
}
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	BulletMax = Bullets;
	CreateProjectilePool();
//	SetupAmmo(Bullets);
}

void ACannon::CreateProjectilePool()
{
	if (ProjectilePoolClass)
		ProjectilePool = GetWorld()->SpawnActor<AProjectilePool>(ProjectilePoolClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
}

void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}
	if (Bullets <= 0) //u turreli net IsReadyToFire
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Can't shooting")));
		return;
	}
	bReadyToFire = false;
	Bullets--;

	ShootEffect->Activate();
	ShootSound->Play();
	if (CameraShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CameraShake);
	}
	
	if (CannonType == ECannonType::FireProjectile)
	{
		FireProjectile();
	}
	else
	{
		FireTrace();
	} 
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, (1 / FireRate), false);
}
void ACannon::Reload()
{
	bReadyToFire = true;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Bullets by %s: %d"), *GetName(), Bullets));
}
bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

void ACannon::SetupAmmo(uint8 Ammo)
{
	if (Ammo > 0) {
		Bullets = Ammo;
	}
	else GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Get full ammo stack")));
}

void ACannon::FireProjectile()
{
	if (ProjectilePool)
	{
		ProjectilePool->GetProjectile(ProjectileSpawnPoint->GetComponentLocation(),ProjectileSpawnPoint->GetComponentRotation());
	}
	else
	{
		FActorSpawnParameters spawnParam;
		spawnParam.Owner = this;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), spawnParam);
		if (projectile)
		{
			projectile->OnKilled.AddUObject(this, &ACannon::AddScore);
			projectile->SetOwner(this);
			projectile->Start();
		}
	}
}

void ACannon::FireTrace()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace")));
	FHitResult hitResult;
	IIDamageTaker* DamageTakerActor;
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
			DamageTakerActor = Cast<IIDamageTaker>(hitResult.GetActor());
			if (DamageTakerActor)
			{
				FDamageData damageData;
				damageData.DamageValue = FireDamage;
				damageData.Instigator = GetOwner();
				damageData.DamageMaker = this;

				DamageTakerActor->TakeDamage(damageData);
			}
			else
			{
				hitResult.GetActor()->Destroy();
			}
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), start, end, FColor::Blue, false, 2.0f, 0, 4.0f);
	}
}
void ACannon::AddScore(int32 ScoreValue)
{
	Score = ScoreValue; //ne ponyal zachem score v Cannon.h
	if (ScoreChanged.IsBound())
	{
		ScoreChanged.Broadcast(ScoreValue);
	}
}
/*void ACannon::Shoot()
{
	if (currentShootCounter == BulletMax)
	{
		GetWorld()->GetTimerManager().ClearTimer(SerialTimer);
		bReadyToFire = true;
		currentShootCounter = 0;
		Bullets--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Bullets: %d"), Bullets));
		return;
	}
	currentShootCounter++;

	if (CannonType == ECannonType::FireProjectile)
	{
	FireProjectile();
	}
	else
	{
	FireTrace();
	} 
}*/

/*void ACannon::FireSpecial()
{
	if (!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;
	
	for (uint8 Serial = 0; Serial < FireSerialAmount; Serial++)
	{
		GetWorld()->GetTimerManager().SetTimer(SerialTimer, this, &ACannon::Shoot, 1/FireRate, true, 0.0f);
	}
}*/