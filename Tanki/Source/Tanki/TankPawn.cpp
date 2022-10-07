// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

#include "TankPlayerController.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATankPawn::ATankPawn()
{
 	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpingArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());
	SetupCannon(CannonClass);
	SetupDefaultCannon();
	SetupAmmoCannon(3);
}

void ATankPawn::MoveForward(float Value)
{
	ForwardMoveAxisValue = Value;
}

void ATankPawn::MoveRight(float Value)
{
	RightMoveAxisValue = Value;
}

void ATankPawn::RotateTank(float Value)
{
	RotateRightAxisValue = Value;
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannon)
{
	if (!newCannon)
	{
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters SpawnParam;
	SpawnParam.Instigator = this;
	SpawnParam.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(newCannon, SpawnParam);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ATankPawn::SetupDefaultCannon()
{
	if (!DefaultCannonClass)
	{
		return;
	}
	if (DefaultCannon)
	{
		DefaultCannon->Destroy();
	}
	FActorSpawnParameters SpawnParam;
	SpawnParam.Instigator = this;
	SpawnParam.Owner = this;
	DefaultCannon = GetWorld()->SpawnActor<ACannon>(DefaultCannonClass, SpawnParam);
	DefaultCannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

}


void ATankPawn::SetupAmmoCannon(uint8 Ammo)
{
	if (Cannon && DefaultCannon && !bDefaultCannon) { //v positivnom sluchae bDefaultCannon = false
		Cannon->SetupAmmo(Ammo);
		DefaultCannon->SetupAmmo(DefaultCannonAmmo);
	}
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

/*void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}*/

void ATankPawn::ChangeCannon()
{
	if (Cannon && DefaultCannon)
	{
		TempCannon = Cannon;
		Cannon = DefaultCannon;
		DefaultCannon = TempCannon;
		bDefaultCannon = !bDefaultCannon;
	}
}

bool ATankPawn::GetbDefaultCannon() const
{
	return bDefaultCannon;
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//movement
	FVector currentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector movePosicion = currentLocation + (ForwardVector * ForwardMoveAxisValue * MovementSpeed * DeltaTime) + (RightVector * RightMoveAxisValue * MovementSpeed * DeltaTime);
	SetActorLocation(movePosicion);
	//tank rotation
	CurrentRightRotationAxis = FMath::Lerp(CurrentRightRotationAxis,RotateRightAxisValue,RotateInterpolationKey);
	float yawRotation = CurrentRightRotationAxis * RotationSpeed * DeltaTime;
	FRotator currentRotation = GetActorRotation();

	yawRotation += currentRotation.Yaw;
	FRotator newRotation = FRotator(0.0f, yawRotation, 0.0f);
	SetActorRotation(newRotation);

	//turret rotation
	if (TankController)
	{
		FVector MousePos = TankController->GetMousePos();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePos); //in which side to rotate
		FRotator turretRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = turretRotation.Pitch;
		targetRotation.Roll = turretRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(targetRotation, turretRotation, TurretInterpolationKey));
	}
}

