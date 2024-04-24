// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeamOwnable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTeamOwnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface is needed because base buildings are defined in C++
 * And units in blueprints.
 * This interface defines a contract to return a specific variable defined in either BP or CPP.
 * In our case this is needed for getting the TeamID of a unit.
 */
class TOYBOXTACTICS_API ITeamOwnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	int GetTeamID() const;
};
