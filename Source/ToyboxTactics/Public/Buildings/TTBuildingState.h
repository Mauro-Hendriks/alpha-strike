// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "TTBuildingState.generated.h"

/**
 * 
 */
UCLASS()
class TOYBOXTACTICS_API UTTBuildingState : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EBuildingState
{
	Hologram,
	UnderConstruction,
	Build,
};
