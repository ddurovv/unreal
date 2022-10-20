// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePawn.h"

#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

AMachinePawn::AMachinePawn()
{

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComponent;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);
	
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &AMachinePawn::Die);
	HealthComponent->OnHealthChanged.AddUObject(this, &AMachinePawn::DamageTaked);

	DestroyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect"));
	DestroyEffect->SetAutoActivate(false);
	DestroyEffect->SetupAttachment(BodyMesh);
}

void AMachinePawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void AMachinePawn::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(EquippedCannonClass);
}

void AMachinePawn::Die()
{
	if (Cannon)
	{
	Cannon->Destroy();
	}
	DestroyEffect->Activate();
	Destroy();
}

void AMachinePawn::DamageTaked(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Object %s taked damage: %f, his health: %f"), *GetName(), Value, HealthComponent->GetHealth());
}

void AMachinePawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void AMachinePawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}

	EquippedCannonClass = newCannonClass;
	
	FActorSpawnParameters SpawnParam;
	SpawnParam.Instigator = this;
	SpawnParam.Owner = this;
	
	Cannon = GetWorld()->SpawnActor<ACannon>(EquippedCannonClass, SpawnParam);
	Cannon->SetOwner(this);
	Cannon->ScoreChanged.AddUObject(this, &AMachinePawn::ShowScore);
	
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

int32 AMachinePawn::GetPoints()
{
	return ScoreValue;
}

void AMachinePawn::ShowScore(int32 Value)
{
	Score += Value;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Score: %d"), Score));
}