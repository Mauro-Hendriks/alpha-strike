// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IUnitSelectionRect.h"
#include "GameFramework/HUD.h"
#include "TTHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnitSelectionStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitSelectUpdate, TArray<AActor*>, AllActorsInRect);

/**
 * 
 */
UCLASS()
class TOYBOXTACTICS_API ATTHUD : public AHUD, public IUnitSelectionRect
{
	GENERATED_BODY()

public:
	
	virtual void StartUnitSelectionRect_Implementation(float MouseX, float MouseY) override;
	virtual void UpdateUnitSelectionRect_Implementation(float MouseX, float MouseY) override;
	virtual void EndUnitSelectionRect_Implementation(float MouseX, float MouseY) override;
	
	FOnUnitSelectionStart OnUnitSelectionStart;
	FOnUnitSelectUpdate OnUnitSelectUpdate;
	
private:
	virtual void DrawHUD() override;

private:
	UPROPERTY(EditDefaultsOnly)
	FLinearColor RectangleColor;
	

	
	bool bShouldDraw = false;
	float StartMouseX; float StartMouseY;
	float CurrentMouseX; float CurrentMouseY;
};
