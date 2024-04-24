// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectedUnitsListComponent.generated.h"


class USelectableUnitComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOYBOXTACTICS_API USelectedUnitsListComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USelectedUnitsListComponent();

	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateSelectedUnits(TArray<AActor*> ActorsInSelectionRect);

	UFUNCTION()
	void ClearSelectedUnits();

	UFUNCTION(BlueprintCallable)
	bool HasUnitsSelected() const { return !CurrentlySelectedUnits.IsEmpty(); }

	UFUNCTION(BlueprintCallable)
	TArray<USelectableUnitComponent*> GetCurrentlySelectedUnits() { return CurrentlySelectedUnits; }

private:
	TArray<USelectableUnitComponent*> CurrentlySelectedUnits;

	bool IsPlayerOwned(AActor* Actor) const;
};
