// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "IDamageTaker.h"
#include "MachinePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"

UCLASS()
class TANKI_API ATankPawn : public AMachinePawn
{
	GENERATED_BODY()

public:
	ATankPawn();
	
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateTank(float Value);

//	void GetCannon() const { return Cannon; }
	void SetupDefaultCannon();
	void SetupAmmoCannon(uint8 Ammo);
	//void FireSpecial();
	void ChangeCannon();
	bool GetBeDefaultCannon();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	TSubclassOf<ACannon> DefaultCannonClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cannon")
	ACannon* DefaultCannon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	uint8 DefaultCannonAmmo = 10;

private:
	ACannon* TempCannon;
	class ATankPlayerController* TankController;
	float ForwardMoveAxisValue = 0.0f;
	float RightMoveAxisValue = 0.0f;
	float RotateRightAxisValue =  0.0f;
	float CurrentRightRotationAxis = 0.0f;
	float RotateInterpolationKey = 0.1f;
	float TurretInterpolationKey = 0.1f;
	bool bDefaultCannon = false;
};
