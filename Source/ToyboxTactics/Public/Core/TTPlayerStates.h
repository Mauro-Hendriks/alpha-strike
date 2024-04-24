// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "TTPlayerStates.generated.h"

/**
 * 
 */
UCLASS()
class TOYBOXTACTICS_API UTTPlayerStates : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EPlayerStates
{
	Default,
	Building
};
