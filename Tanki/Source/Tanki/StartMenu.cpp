// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu.h"

#include "Components/Button.h"

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameBtn) //must, cause we indicate BindWidgetOptional
	{
		NewGameBtn->OnPressed.AddDynamic(this, &ThisClass::UStartMenu::OnNewGameClicked);
	}

	if (LoadGameBtn) //must, cause we indicate BindWidgetOptional
	{
		LoadGameBtn->OnPressed.AddDynamic(this, &ThisClass::UStartMenu::OnLoadGameClicked);
	}

	if (SettingsBtn) //must, cause we indicate BindWidgetOptional
	{
		SettingsBtn->OnPressed.AddDynamic(this, &ThisClass::UStartMenu::OnSettingsClicked);
	}
	
	if (QuitGameBtn) //optionally, cause we indicate BindWidget; UE is not create widget without this button
	{
		QuitGameBtn->OnPressed.AddDynamic(this, &ThisClass::UStartMenu::UStartMenu::OnQuitGameClicked);
	}
}

void UStartMenu::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (NewGameBtn)
	{
		NewGameBtn->OnPressed.RemoveAll(this);
	}
	
	if (QuitGameBtn)
	{
		QuitGameBtn->OnPressed.RemoveAll(this);
	}
}

void UStartMenu::OnNewGameClicked()
{
	if (NewGameAnimation)
	{
		PlayAnimation(NewGameAnimation);
	}
	OnButtonSelected.Broadcast(0);
}

void UStartMenu::OnLoadGameClicked()
{
	OnButtonSelected.Broadcast(1);
}

void UStartMenu::OnSettingsClicked()
{
	OnButtonSelected.Broadcast(2);
}

void UStartMenu::OnQuitGameClicked()
{
	//GEngine->Exec(GetWorld(), TEXT("Quit"));
	OnButtonSelected.Broadcast(3);
}