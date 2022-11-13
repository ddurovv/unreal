// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapLoader.generated.h"

UCLASS()
class TANKI_API AMapLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapLoader();

	void SetIsActivated(bool NewIsActivated);
	
protected:
	virtual void BeginPlay() override;

	void SetActivatedLights();

	void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* LevelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UPointLightComponent* ActivatedLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UPointLightComponent* DeactivatedLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	FName LoadLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bIsActivated = false;

};
