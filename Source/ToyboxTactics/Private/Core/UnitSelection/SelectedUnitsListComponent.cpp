// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UnitSelection/SelectedUnitsListComponent.h"

#include "Core/UnitSelection/SelectableUnitComponent.h"
#include "Core/UnitSelection/TeamOwnable.h"
#include "Core/UnitSelection/TTHUD.h"
#include "GameFramework/PlayerState.h"

// Sets default values for this component's properties
USelectedUnitsListComponent::USelectedUnitsListComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USelectedUnitsListComponent::BeginPlay()
{
	Super::BeginPlay();

	const APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if (PlayerPawn == nullptr) return;
	
	const APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->Controller);
	if (PlayerController == nullptr) return;
	
	ATTHUD* HUD = Cast<ATTHUD>(PlayerController->GetHUD());
	if (HUD == nullptr) return;

	HUD->OnUnitSelectionStart.AddDynamic(this, &USelectedUnitsListComponent::ClearSelectedUnits);
	HUD->OnUnitSelectUpdate.AddDynamic(this, &USelectedUnitsListComponent::UpdateSelectedUnits);
}

void USelectedUnitsListComponent::UpdateSelectedUnits(TArray<AActor*> ActorsInSelectionRect)
{
	// Filter all actors based on the Selectable Component and add them to an array
	TArray<USelectableUnitComponent*> SelectableComponentsInRect;
	for (auto* Actor : ActorsInSelectionRect)
	{
		USelectableUnitComponent* SelectableUnitComponent = Cast<USelectableUnitComponent>(Actor->GetComponentByClass(USelectableUnitComponent::StaticClass()));
		if (SelectableUnitComponent != nullptr && IsPlayerOwned(Actor))
		{
			SelectableComponentsInRect.AddUnique(SelectableUnitComponent);
		}
	}

	// Check if a unit is already selected or not and add it to the selected list of not already selected
	for (auto* SelectableUnitComponent : SelectableComponentsInRect)
	{
		if (!CurrentlySelectedUnits.Contains(SelectableUnitComponent))
		{
			CurrentlySelectedUnits.AddUnique(SelectableUnitComponent);
			SelectableUnitComponent->SelectUnit();
		}
	}

	// Check if there are units in the currently selected list which are not in the selection anymore
	// Aka a player resized the selectiongrid during a single input action
	TArray<USelectableUnitComponent*> UnitsToDeselect;
	for (auto* SelectedUnit : CurrentlySelectedUnits)
	{
		if (!SelectableComponentsInRect.Contains(SelectedUnit))
		{
			UnitsToDeselect.AddUnique(SelectedUnit);
		}
	}

	// Remove Units from the CurrentSelectedUnits
	for (auto* Unit : UnitsToDeselect)
	{
		Unit->DeselectUnit();
		CurrentlySelectedUnits.Remove(Unit);
	}
}

void USelectedUnitsListComponent::ClearSelectedUnits()
{
	for (auto* SelectedUnitComponent : CurrentlySelectedUnits)
	{
		SelectedUnitComponent->DeselectUnit();
	}
	CurrentlySelectedUnits.Empty();
}

bool USelectedUnitsListComponent::IsPlayerOwned(AActor* Actor) const
{
	// player ID opvragen uit playerstate
	
	APawn* PlayerPawn = Cast<APawn>(GetOwner());
	APlayerState* PlayerState = PlayerPawn->GetPlayerState();
	const int PlayerID = PlayerState->GetPlayerId();

	int ActorID = -1;
	// Interface aanroepen op acto;
	if (Actor->GetClass()->ImplementsInterface(UTeamOwnable::StaticClass()))
	{
		ActorID = ITeamOwnable::Execute_GetTeamID(Actor);
		UE_LOG(LogTemp, Warning, TEXT("ID: %d"), ActorID);
	}

	return ActorID == PlayerID;
}

