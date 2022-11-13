// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "HealthComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATurret::ATurret()
{	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
	{
		BodyMesh->SetStaticMesh(bodyMeshTemp);
	}

	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
	{
		TurretMesh->SetStaticMesh(turretMeshTemp);
	}
	HealthComponent->OnDie.AddUObject(this, &ATurret::Die);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	//SetupCannon();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(targetingTimerHandle,this, &ATurret::Targeting,TargetingRate,true,TargetingRate);
}

void ATurret::Targeting()
{
	if (!PlayerPawn){ return; }
	if (IsPlayerInRange() && IsPlayerSeen())
 	{
		RotateToPlayer();
		if (CanFire())
		{
			Fire();
		}
	}
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator currentRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currentRotation,targetRotation,TargetingSpeed));
}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(),GetActorLocation()) <= TargetingRange;
}

bool ATurret::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams params;
	params.bTraceComplex = true;
	params.AddIgnoredActor(this);
	params.bReturnPhysicalMaterial = false;

	if(GetWorld()->LineTraceSingleByChannel(HitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, params))
	{
		AActor* hitActor = HitResult.GetActor();
		if (hitActor)
		{
			if (hitActor == PlayerPawn)
			{
				DrawDebugLine(GetWorld(),eyesPos,HitResult.Location, FColor::Red, false, 0.5f, 0, 10.0f);
				return true;
			}
			else
			{
				DrawDebugLine(GetWorld(),eyesPos,HitResult.Location, FColor::Green, false, 0.5f, 0, 10.0f);
				return false;
			}
		}
	}
	DrawDebugLine(GetWorld(),eyesPos,playerPos, FColor::Black, false, 0.5f, 0, 10.0f);
	return false;
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float AimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir,dirToPlayer)));
	return AimAngle <= Accurency;
}

void ATurret::Die()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
	ActivateDestroyedEffect();
	Destroy();
}
