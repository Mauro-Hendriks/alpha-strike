// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BaseBuilding.h"
#include "core/HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/TTGameModeBase.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerState.h"

// Sets default values
ABaseBuilding::ABaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	SetRootComponent(BuildingMesh);
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	/*APlayerState ps = ;

	TeamID=ps.GetPlayerId();*/
	
	if (BuildingDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTable not set"));
	}
	else
	{
		for (auto& itr : BuildingDataTable->GetRowNames())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *itr.ToString());
			FBuildingStats* Tester = BuildingDataTable->FindRow<FBuildingStats>(*itr.ToString(), "");
		}
		FBuildingStats* Tester = BuildingDataTable->FindRow<FBuildingStats>(FName("Nexus"), "");
		UE_LOG(LogTemp, Warning, TEXT("%d"), Tester->Health);
	}
}
 void ABaseBuilding::ChangeBuildingStateToHolo()
 {
	 BuildingState = EBuildingState::Hologram;
	
 }

int ABaseBuilding::GetTeamID_Implementation() const
 {
	return TeamID;
 	//return ITeamOwnable::GetTeamID_Implementation();
 }


// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBuilding::Destroyed()
{
	Super::Destroyed();

	ATTGameModeBase* GM = Cast<ATTGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->DestroyedBuilding(this, TeamID);
	}
	else
	{
		// NOTE: Not in play mode. This code is also called in the editor! There is no game mode active in the editor outside of play mode! (Peter Verzijl 24/10/2023)
	}
}