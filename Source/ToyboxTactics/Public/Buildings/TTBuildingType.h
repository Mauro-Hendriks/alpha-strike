// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "TTBuildingType.generated.h"

/**
 * 
 */
UCLASS()
class TOYBOXTACTICS_API UTTBuildingType : public UUserDefinedEnum
{
	GENERATED_BODY()

};

UENUM(BlueprintType)
enum class EBuildingTypes : uint8
{
	None,
	
	Nexus UMETA(DisplayName="Nexus"),
	Barracks,
	Turret,
	PowerPilon UMETA(DisplayName="Power Pilon"),
};
