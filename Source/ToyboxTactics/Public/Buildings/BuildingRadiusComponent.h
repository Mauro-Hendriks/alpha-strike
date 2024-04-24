// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingRadiusComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOYBOXTACTICS_API UBuildingRadiusComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float Radius;
	
public:
	// Sets default values for this component's properties
	UBuildingRadiusComponent();

	UFUNCTION(BlueprintCallable)
	bool IsInRange(FVector Location);
};
