// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "IDamageTaker.h"
#include "Scorable.h"
#include "Components/SphereComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollizion"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(SphereCollision);
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate, true, MoveRate);
	GetWorld()->GetTimerManager().SetTimer(DeactivateTimer,this,&AProjectile::Deactivate, DeactivateTime,false);
}

void AProjectile::Deactivate()
{
	bIsActivation = false;
	SetActorLocation(FVector{0.0f,0.0f,-50.0f});
	GetWorld()->GetTimerManager().ClearTimer(DeactivateTimer);
	GetWorld()->GetTimerManager().ClearTimer(MoveTimer);
	SetActorEnableCollision(false);
}

void AProjectile::Move()
{
	FVector movePosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(movePosition);
}

void AProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	
	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IIDamageTaker* DamageTakerActor = Cast<IIDamageTaker>(OtherActor);
		IScorable* ScorableActor = Cast<IScorable>(OtherActor);

		int32 ScoreValue = 0;

		if(ScorableActor)
		{
			ScoreValue = ScorableActor->GetPoints();
		}
		if (DamageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;

			DamageTakerActor->TakeDamage(damageData);
			
			if (OtherActor->IsActorBeingDestroyed() && ScoreValue != 0)
			{
				if (OnKilled.IsBound())
				{
					OnKilled.Broadcast(ScoreValue);
				}
			}
		}
		else
		{
			OtherActor->Destroy();
		}
	}
	//Deactivate(); //turn on if ProjectilePool will be fixed
	Destroy(); //turn off actually too
}
