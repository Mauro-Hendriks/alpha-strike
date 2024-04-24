// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UnitSelection/TTHUD.h"

void ATTHUD::DrawHUD()
{
	if (!bShouldDraw) return;
	
	Super::DrawHUD();

	const float RectWidth = CurrentMouseX - StartMouseX;
	const float RectHeight = CurrentMouseY - StartMouseY;

	DrawRect(RectangleColor, StartMouseX, StartMouseY, RectWidth, RectHeight);

	TArray<AActor*> AllActorsInRect;
	const FVector2D StartPosition(StartMouseX, StartMouseY);
	const FVector2D Size(CurrentMouseX, CurrentMouseY);
	GetActorsInSelectionRectangle(AActor::StaticClass(), StartPosition, Size, AllActorsInRect, false, false);
	
	if (OnUnitSelectUpdate.IsBound())
	{
		OnUnitSelectUpdate.Broadcast(AllActorsInRect);
	}
}

void ATTHUD::StartUnitSelectionRect_Implementation(float MouseX, float MouseY)
{
	IUnitSelectionRect::StartUnitSelectionRect_Implementation(MouseX, MouseY);

	StartMouseX = MouseX;
	StartMouseY = MouseY;
	CurrentMouseX = MouseX;
	CurrentMouseY = MouseY;

	if (OnUnitSelectionStart.IsBound())
	{
		OnUnitSelectionStart.Broadcast();	
	}
	bShouldDraw = true;
}

void ATTHUD::UpdateUnitSelectionRect_Implementation(float MouseX, float MouseY)
{
	IUnitSelectionRect::UpdateUnitSelectionRect_Implementation(MouseX, MouseY);

	CurrentMouseX = MouseX;
	CurrentMouseY = MouseY;
}

void ATTHUD::EndUnitSelectionRect_Implementation(float MouseX, float MouseY)
{
	IUnitSelectionRect::EndUnitSelectionRect_Implementation(MouseX, MouseY);

	CurrentMouseX = MouseX;
	CurrentMouseY = MouseY;
	bShouldDraw = false;
}


