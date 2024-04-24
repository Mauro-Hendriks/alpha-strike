// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TTPlayerPawnBase.h"
#include "InputActionValue.h"
#include "TTGameModeBase.h"
#include "TTPlayerStates.h"
#include "Buildings/TTBuildingType.h"
#include "TTDesktopPlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOrderUnit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildModeExited);

class UDataTable;
class UEnhancedInputLocalPlayerSubsystem;
class USphereComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
class ABaseBuilding;
struct FBuildingStats;

/**
 * TODO: Add Camera to desktop player
 */
UCLASS()
class TOYBOXTACTICS_API ATTDesktopPlayerPawn : public ATTPlayerPawnBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=( AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=( AllowPrivateAccess = "true"))
	UInputAction* SelectUnitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=( AllowPrivateAccess = "true"))
	UInputAction* OrderUnitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=( AllowPrivateAccess = "true"))
	UInputMappingContext* BuildingMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=( AllowPrivateAccess = "true"))
	UInputAction* BuildingAction;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	void StartUnitSelection(const FInputActionValue& Value);
	void UpdateUnitSelection(const FInputActionValue& Value);
	void EndUnitSelection(const FInputActionValue& Value);
	
	void OrderUnit(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OrderUnitEvent();

	UFUNCTION(BlueprintCallable)
	void SwitchInputMappingContext(UInputMappingContext* InputMappingContext, bool BuildingMode);
	
	UInputMappingContext* CurrentInputMappingContext;
	
	//TEnumAsByte<EPlayerStates> PlayerState;
	EPlayerStates PlayerState;

	/**
	 * Event called when the player state switches
	 */
	UPROPERTY(BlueprintAssignable)
	FOnBuildModeExited OnBuildModeExited;

	void PlaceBuilding();

	/**
	 * Turns the building mode on / off and switches the input mapping context accordingly.
	 * @param bShouldShowHolo The new building state (on/off)
	 */
	UFUNCTION(BlueprintCallable)
	void SwitchMode(bool bShouldShowHolo);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> BuildingList;

	//TODO: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Building)
	TSubclassOf<ABaseBuilding> ChosenBuildingClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Base Building")
	EBuildingTypes ChosenBuildingType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Base Building")
	TMap<EBuildingTypes, TSubclassOf<ABaseBuilding>> BuildingClassMap;

	UPROPERTY(EditDefaultsOnly, Category="Base Building")
	UDataTable* BuildingDataTable;	

	void CanBuy(FBuildingStats* Buildingstats);

	bool b_CanBuy;
	
	ATTGameModeBase* GameModeBase;

	UFUNCTION(BlueprintCallable)
	void ShowHologram(ABaseBuilding*& ReturnBuilding);

	ABaseBuilding* HoloBuilding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"),  Category=Builing)
	FCollisionProfileName CollisionProfile;

	UPROPERTY(BlueprintReadOnly)
	bool InBuildMode;

	UFUNCTION(BlueprintCallable)
	void UpdateHoloBuiling();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Building)
	TSubclassOf<ABaseBuilding> Nexus;

	FVector NexusSpawn;
};
