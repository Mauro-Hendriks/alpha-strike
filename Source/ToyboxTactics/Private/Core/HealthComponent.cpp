// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100;
	CurrentHealth = 100;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthComponent::ChangeHealth(float Amount)
{
	CurrentHealth = CurrentHealth - Amount;

	if (CurrentHealth<= 0)
	{
		GetOwner()->Destroy();
	}
	OnHealthUpdated.Broadcast();
}

void UHealthComponent::SetMaxHealth(float Amount)
{
	MaxHealth = Amount;
	CurrentHealth = MaxHealth;
}

float UHealthComponent::GetNormalizedHealth() const
{
	return float(CurrentHealth) / float(MaxHealth);
}


