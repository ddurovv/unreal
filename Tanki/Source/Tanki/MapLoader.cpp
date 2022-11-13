// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLoader.h"

#include "TankPawn.h"
#include "Components/SceneCaptureComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/Core/Connection/NetResult.h"

// Sets default values
AMapLoader::AMapLoader()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = SceneComp;

	LevelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LevelMesh"));
	LevelMesh->SetupAttachment(SceneComp);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ActivatedLight"));
	ActivatedLight->SetupAttachment(SceneComp);

	DeactivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("DeactivatedLight"));
	DeactivatedLight->SetupAttachment(SceneComp);
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(LevelMesh);
//	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMapLoader::OnMeshOverlapBegin);
}

void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	bIsActivated = NewIsActivated;
	SetActivatedLights();
}

void AMapLoader::BeginPlay()
{
	Super::BeginPlay();
	
	SetActivatedLights();
}

void AMapLoader::SetActivatedLights()
{
	ActivatedLight->SetHiddenInGame(!bIsActivated);
	DeactivatedLight->SetHiddenInGame(bIsActivated);
}

void AMapLoader::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsActivated)
	{
		return;
	}

	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}
}
