// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TTPlayerPawnBase.h"
#include "Core/UnitSelection/SelectedUnitsListComponent.h"
#include "Core/UnitSelection/TTHUD.h"

// Sets default values
ATTPlayerPawnBase::ATTPlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectedUnitListComponent = CreateDefaultSubobject<USelectedUnitsListComponent>(TEXT("AC_SelectedUnitList"));
}

// Called when the game starts or when spawned
void ATTPlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATTPlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTPlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

