#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class TANKI_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AAmmoBox();
protected:

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* AmmoMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<class ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Params")
	uint8 Ammo = 3;
};
