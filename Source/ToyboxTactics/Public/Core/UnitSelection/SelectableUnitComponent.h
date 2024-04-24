// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectableUnitComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnitSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnitDeselected);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOYBOXTACTICS_API USelectableUnitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelectableUnitComponent();
	
	UFUNCTION(BlueprintNativeEvent)
	void SelectUnit();

	UFUNCTION(BlueprintNativeEvent)
	void DeselectUnit();

private:

	UPROPERTY(BlueprintAssignable)
	FOnUnitSelected OnUnitSelected;

	UPROPERTY(BlueprintAssignable)
	FOnUnitDeselected OnUnitDeselected;
};
