// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTBuildingState.h"
#include "TTBuildingType.h"
#include "Engine/DataTable.h"
#include "Engine/UserDefinedStruct.h"
#include "TTBuildingStats.generated.h"

/**
 * 
 */

UCLASS()
class TOYBOXTACTICS_API UTTBuildingStats : public UUserDefinedStruct
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType, Blueprintable)
struct FBuildingStats : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingTypes BuildingTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingState BuildingState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GoldCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuildTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BuildRange;
};

