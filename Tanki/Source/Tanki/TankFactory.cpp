// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"

#include "MapLoader.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATankFactory::ATankFactory()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;
	
	FactoryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FactoryMesh"));
	FactoryMesh->SetupAttachment(RootComponent);
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(FactoryMesh);
	
	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TankSpawnPoint"));
	TankSpawnPoint->SetupAttachment(FactoryMesh);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankFactory::DamageTaked);
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	if (MapLoader)
	{
		MapLoader->SetIsActivated(false);
	}
	
	FTimerHandle SpawnTimer;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ATankFactory::SpawnTank, SpawnTankRate, true, SpawnTankRate);
}

void ATankFactory::SpawnTank()
{
	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform,this,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	newTank->SetPatrollingPoints(TankWayPoints);

	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
	
}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankFactory::Die()
{
	Destroy();

	if (MapLoader)
	{
		MapLoader->SetIsActivated(true);
	}
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s take damage: %f, Health: %f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}
