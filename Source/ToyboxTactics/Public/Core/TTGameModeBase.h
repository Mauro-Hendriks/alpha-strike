// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/BuildingRadiusComponent.h"
#include "GameFramework/GameModeBase.h"
#include "TTGameModeBase.generated.h"

class ABaseBuilding;
/**
 * 
 */
UCLASS()
class TOYBOXTACTICS_API ATTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Blueprintable, BlueprintReadWrite)
	TArray<UBuildingRadiusComponent*> AllBuildingComponents;

	UFUNCTION(BlueprintImplementableEvent, BlueprintAuthorityOnly)
	void CreatedBuilding(ABaseBuilding* NewBuilding, int TeamID);

	UFUNCTION(BlueprintImplementableEvent, BlueprintAuthorityOnly)
	void DestroyedBuilding(ABaseBuilding* DestroyedBuilding, int TeamID);

};
