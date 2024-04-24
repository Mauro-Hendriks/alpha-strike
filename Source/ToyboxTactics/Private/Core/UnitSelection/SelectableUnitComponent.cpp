// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UnitSelection//SelectableUnitComponent.h"

// Sets default values for this component's properties
USelectableUnitComponent::USelectableUnitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
}

void USelectableUnitComponent::SelectUnit_Implementation()
{
	if (!OnUnitSelected.IsBound()) return;

	OnUnitSelected.Broadcast();
}

void USelectableUnitComponent::DeselectUnit_Implementation()
{
	if (!OnUnitDeselected.IsBound()) return;

	OnUnitDeselected.Broadcast();
}
