// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/DelegateCombinations.h"
#include "StartMenu.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartMenuDelegate, int32, SelectedButton);

UCLASS(Abstract)
class TANKI_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override; // analog by BeginPlay and constructor
	virtual void NativeDestruct() override;
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UButton* NewGameBtn;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UButton* LoadGameBtn;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UButton* SettingsBtn;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget)) // BindWidget is used to description of logic into blueprints only
	UButton* QuitGameBtn;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetAnim), Transient) //transient meant temp, var is not be saved in ReflectionSystem
	UWidgetAnimation* NewGameAnimation;

	UPROPERTY(BlueprintAssignable) //for subscribe to event into blueprint
	FStartMenuDelegate OnButtonSelected; //actually only Dynamic_Multicast are used in blueprints delegates

	UFUNCTION() //cause it's dynamic (AddDynamic) and we need to subscribe into ReflectionSystem
	void OnNewGameClicked();

	UFUNCTION()
	void OnLoadGameClicked();
	
	UFUNCTION()
	void OnSettingsClicked();

	UFUNCTION()
	void OnQuitGameClicked();
};
