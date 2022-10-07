// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"

#include "TankPawn.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	AmmoMesh->SetupAttachment(SceneComp);
	AmmoMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
	AmmoMesh->SetCollisionProfileName("OverlapAll");
	AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AmmoMesh->SetGenerateOverlapEvents(true);
}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile overlap : %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Projectile overlap : %s"), *OtherComp->GetName());
	
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn->GetbDefaultCannon()) //v positivnom sluchae bDefaultCannon = false;
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("You're using DefaultCannon")));
		return;
	}
	else
	{
		if (TankPawn)
		{
			TankPawn->SetupCannon(CannonClass);
			TankPawn->SetupAmmoCannon(Ammo);
		}
		Destroy();
	}
}


