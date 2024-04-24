// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTBuildingStats.h"
#include "TTBuildingState.h"
#include "TTBuildingType.h"
#include "Components/BoxComponent.h"
#include "Core/UnitSelection/TeamOwnable.h"
#include "GameFramework/Actor.h"
#include "BaseBuilding.generated.h"

class UDataTable;
class UHealthComponent;

UCLASS(Abstract)
class TOYBOXTACTICS_API ABaseBuilding : public AActor, public ITeamOwnable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	UHealthComponent* HealthComponent;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	UStaticMeshComponent* BuildingMesh;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Base Building")
	EBuildingState BuildingState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Base Building")
	FBuildingStats BuildingStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Base Building")
	EBuildingTypes BuildingType;

	UPROPERTY(EditDefaultsOnly, Category="Base Building")
	UDataTable* BuildingDataTable;
	
	void ChangeBuildingStateToHolo();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeBuildingStateToConstruction();

	virtual int GetTeamID_Implementation() const override;

	UPROPERTY(BlueprintReadWrite)
	bool CanBePlast;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> Overlap;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* Red;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TeamID;
};
