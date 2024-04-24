// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingRadiusComponent.h"

// Sets default values for this component's properties
UBuildingRadiusComponent::UBuildingRadiusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Radius = 1500;
}

bool UBuildingRadiusComponent::IsInRange(FVector Location)
{
	const FVector OwnerLocation = GetOwner()->GetActorLocation();
	const float Distance = FVector::Dist2D(OwnerLocation, Location);
	
	return Distance <= Radius;
}

