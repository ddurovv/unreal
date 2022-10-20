// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

#include "TankPawn.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITankPawn = Cast<ATankPawn>(GetPawn());
	if (!AITankPawn)
	{
	return;
	}
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	FVector pawnLocation = AITankPawn->GetActorLocation();
	MovementAccurency = AITankPawn->GetMovementAccurency();
	TArray<FVector> points = AITankPawn->GetPatrollingPoints();
	for (FVector point: points)
	{
		PatrollingPoints.Add(point + pawnLocation); // pozitsiya tochki vozvraschaetsya local'no
	}
	PatrollingIndex = 0;
}
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AITankPawn->MoveForward(1);

	float rotationValue = GetRotationValue(); // mozhno prosche: ->RotateTank(GetRotationValue())
	AITankPawn->RotateTank(rotationValue);

	Targeting();
}

float ATankAIController::GetRotationValue()
{
	FVector currentPoint = PatrollingPoints[PatrollingIndex];
	FVector pawnLocation = AITankPawn->GetActorLocation();
	float distance = FVector::Distance(currentPoint, pawnLocation);
	if (distance <= MovementAccurency)
	{
		PatrollingIndex++;
		if (PatrollingIndex >= PatrollingPoints.Num())
		{
			PatrollingIndex = 0;
		}
	}
	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = AITankPawn->GetActorForwardVector();
	FVector rightDirection = AITankPawn->GetActorRightVector();

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection,moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct( rightDirection,moveDirection)));

	float rotationValue = 0;
	if (forwardAngle > 5)
		rotationValue = 1;
	if (rightAngle > 90)
		rotationValue = -rotationValue;
	return rotationValue;
}

void ATankAIController::Targeting()
{
	if(!AITankPawn){ return; }
	if (IsPlayerInRange() && IsPlayerSeen())
	{
		if (CanFire())
		{
			Fire();
		}
		else
		{
			RotateToPlayer();
		}
	}
}

void ATankAIController::RotateToPlayer()
{
	AITankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

void ATankAIController::Fire()
{
	AITankPawn->Fire();
}

bool ATankAIController::IsPlayerInRange()
{
	return FVector::Distance(AITankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
}

bool ATankAIController::CanFire()
{
	FVector	targetDir = AITankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - AITankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float AimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetDir, dirToPlayer)));
	return AimAngle <= Accurency;
}

bool ATankAIController::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = AITankPawn->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams params;
	params.bTraceComplex = true;
	params.AddIgnoredActor(AITankPawn);
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