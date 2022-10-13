// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::TakeDamage(FDamageData DamageData)
{
	float TakeDamageValue = DamageData.DamageValue;
	CurrentHealth -= TakeDamageValue;

	if (CurrentHealth <= 0)
	{
		if (OnDie.IsBound())
			OnDie.Broadcast();
	}
	else
	{
		if (OnHealthChanged.IsBound())
			OnHealthChanged.Broadcast(TakeDamageValue);
	}
}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

void UHealthComponent::AddHealth(float newHealth)
{
	CurrentHealth += newHealth;
	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

float UHealthComponent::GetHealthState()
{
	return CurrentHealth/MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
	
}
