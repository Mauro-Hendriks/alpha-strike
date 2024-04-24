// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TTPlayerPawnBase.generated.h"

class USelectedUnitsListComponent;

UCLASS()
class TOYBOXTACTICS_API ATTPlayerPawnBase : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATTPlayerPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USelectedUnitsListComponent> SelectedUnitListComponent;

};
