// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TTDesktopPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "VectorTypes.h"
#include "Buildings/BaseBuilding.h"
#include "Buildings/BuildingRadiusComponent.h"
#include "Buildings/TTNexusSpawnLocation.h"
#include "Core/TTGameModeBase.h"
#include "Core/TTPlayerState.h"
#include "Core/TTPlayerStates.h"
#include "Core/UnitSelection/IUnitSelectionRect.h"
#include "Core/UnitSelection/SelectedUnitsListComponent.h"
#include "GameFramework/HUD.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void ATTDesktopPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController == nullptr) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr) return;

	if (ensure(DefaultMappingContext))
	{
		SwitchInputMappingContext(DefaultMappingContext, false);
	}

	PlayerController->SetShowMouseCursor(true);


	GameModeBase = Cast<ATTGameModeBase>(GetWorld()->GetAuthGameMode());
}

void ATTDesktopPlayerPawn::SwitchInputMappingContext(UInputMappingContext* InputMappingContext, bool BuildingMode)
{
	if (CurrentInputMappingContext == nullptr)
	{
		CurrentInputMappingContext = InputMappingContext;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController == nullptr) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr) return;

	Subsystem->RemoveMappingContext(CurrentInputMappingContext);
	Subsystem->AddMappingContext(InputMappingContext, 0);
	CurrentInputMappingContext = InputMappingContext;
}

void ATTDesktopPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent == nullptr) return;

	EnhancedInputComponent->BindAction(SelectUnitAction, ETriggerEvent::Started, this,
	                                   &ATTDesktopPlayerPawn::StartUnitSelection);
	EnhancedInputComponent->BindAction(SelectUnitAction, ETriggerEvent::Ongoing, this,
	                                   &ATTDesktopPlayerPawn::UpdateUnitSelection);
	EnhancedInputComponent->BindAction(SelectUnitAction, ETriggerEvent::Completed, this,
	                                   &ATTDesktopPlayerPawn::EndUnitSelection);

	EnhancedInputComponent->BindAction(OrderUnitAction, ETriggerEvent::Started, this, &ATTDesktopPlayerPawn::OrderUnit);
	EnhancedInputComponent->BindAction(BuildingAction, ETriggerEvent::Started, this,
	                                   &ATTDesktopPlayerPawn::PlaceBuilding);
}

// These three functions break dry, should be refactored some way...
void ATTDesktopPlayerPawn::StartUnitSelection(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	float MouseX;
	float MouseY;
	if (PlayerController->GetMousePosition(MouseX, MouseY))
	{
		IUnitSelectionRect::Execute_StartUnitSelectionRect(PlayerController->GetHUD(), MouseX, MouseY);
	}
}

void ATTDesktopPlayerPawn::UpdateUnitSelection(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	float MouseX;
	float MouseY;
	if (PlayerController->GetMousePosition(MouseX, MouseY))
	{
		IUnitSelectionRect::Execute_UpdateUnitSelectionRect(PlayerController->GetHUD(), MouseX, MouseY);
	}
}

void ATTDesktopPlayerPawn::EndUnitSelection(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	float MouseX;
	float MouseY;
	if (PlayerController->GetMousePosition(MouseX, MouseY))
	{
		IUnitSelectionRect::Execute_EndUnitSelectionRect(PlayerController->GetHUD(), MouseX, MouseY);
	}
}

void ATTDesktopPlayerPawn::OrderUnit(const FInputActionValue& Value)
{
	if (!SelectedUnitListComponent->HasUnitsSelected()) return;

	OrderUnitEvent();
}


void ATTDesktopPlayerPawn::PlaceBuilding()
{
	if (HoloBuilding != NULL)
	{
		if (ChosenBuildingClass == Nexus)
		{
			for (int i = 0; i < GameModeBase->AllBuildingComponents.Num(); i++)
			{
				if (b_CanBuy && GameModeBase->AllBuildingComponents[i]->IsInRange(NexusSpawn) && HoloBuilding->Overlap.
					Num() == NULL)
				{
					AActor* NewBuilding = GetWorld()->SpawnActor(ChosenBuildingClass);
					NewBuilding->SetActorLocationAndRotation(NexusSpawn, FQuat::Identity);
					Cast<ABaseBuilding>(NewBuilding)->ChangeBuildingStateToConstruction();
					const APlayerState* InPlayerState = GetLocalViewingPlayerController()->PlayerState;
					int playerID = InPlayerState->GetPlayerId();
					Cast<ABaseBuilding>(NewBuilding)->TeamID=playerID;
					ChosenBuildingClass = nullptr;
					HoloBuilding->Destroy();
					HoloBuilding = nullptr;

					GameModeBase->CreatedBuilding(Cast<ABaseBuilding>(NewBuilding), playerID);
					
					break;
				}
			}
		}
		else
		{
			FVector MousePos, MouseDir;
			FHitResult GroundHit;
			Cast<APlayerController>(GetController())->DeprojectMousePositionToWorld(MousePos, MouseDir);
			Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECC_WorldStatic, true, GroundHit);

			int x;
			int y;
			float z;

			x = FMath::GridSnap(GroundHit.Location.X, 100);
			y = FMath::GridSnap(GroundHit.Location.Y, 100);
			z = GroundHit.Location.Z + 10.0f;

			const FVector SpawnPosition = FVector(x, y, z);


			for (int i = 0; i < GameModeBase->AllBuildingComponents.Num(); i++)
			{
				if (b_CanBuy && GameModeBase->AllBuildingComponents[i]->IsInRange(SpawnPosition) && HoloBuilding->Overlap.Num() == NULL && HoloBuilding->GetTransform().GetLocation().Z <=15)
				{
					AActor* NewBuilding = GetWorld()->SpawnActor(ChosenBuildingClass);
					NewBuilding->SetActorLocationAndRotation(SpawnPosition, FQuat::Identity);
					Cast<ABaseBuilding>(NewBuilding)->ChangeBuildingStateToConstruction();
					const APlayerState* InPlayerState = GetLocalViewingPlayerController()->PlayerState;
					int playerID = InPlayerState->GetPlayerId();
					Cast<ABaseBuilding>(NewBuilding)->TeamID=playerID;
					ChosenBuildingClass = nullptr;
					HoloBuilding->Destroy();
					HoloBuilding = nullptr;

					GameModeBase->CreatedBuilding(Cast<ABaseBuilding>(NewBuilding), playerID);
					SwitchMode(false);
					break;
				}
			}
		}
	}
}

void ATTDesktopPlayerPawn::SwitchMode(bool bShouldShowHolo)
{
	if (PlayerState == EPlayerStates::Default)
	{
		PlayerState = EPlayerStates::Building;
		SwitchInputMappingContext(BuildingMappingContext, true);
		InBuildMode = true;
		if (bShouldShowHolo)
			ShowHologram(HoloBuilding);
	}
	else
	{
		PlayerState = EPlayerStates::Default;
		SwitchInputMappingContext(DefaultMappingContext, false);
		InBuildMode = false;
		
		// NOTE: Call player switch state
		if (OnBuildModeExited.IsBound())
		{
			OnBuildModeExited.Broadcast();
		}
	}
}

void ATTDesktopPlayerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PlayerState == EPlayerStates::Building && HoloBuilding != NULL && ChosenBuildingClass != Nexus)
	{
		FVector MousePos, MouseDir;
		FHitResult GroundHit;
		Cast<APlayerController>(GetController())->DeprojectMousePositionToWorld(MousePos, MouseDir);
		Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECC_WorldStatic, true, GroundHit);

		int x;
		int y;
		float z;

		x = FMath::GridSnap(GroundHit.Location.X, 100);
		y = FMath::GridSnap(GroundHit.Location.Y, 100);
		z = GroundHit.Location.Z + 10.0f;

		const FVector SpawnPosition = FVector(x, y, z);
		HoloBuilding->SetActorLocationAndRotation(SpawnPosition, FQuat::Identity);

		for (int i = 0; i < GameModeBase->AllBuildingComponents.Num(); i++)
		{
			if (b_CanBuy && GameModeBase->AllBuildingComponents[i]->IsInRange(SpawnPosition) && HoloBuilding->Overlap.Num() == NULL && HoloBuilding->GetTransform().GetLocation().Z <=12)
			{
				HoloBuilding->BuildingMesh->SetMaterial(0, HoloBuilding->Green);
			}
			else
			{
				HoloBuilding->BuildingMesh->SetMaterial(0, HoloBuilding->Red);
			}
		}
	}

	if (!InBuildMode && HoloBuilding != NULL)
	{
		HoloBuilding->Destroy();
	}

	if (ChosenBuildingClass == Nexus)
	{
		TArray<AActor*> NexusSpawnLocations;
		TArray<float> DistanceToMouse;
		int64 Item = MAX_int64;
		int Key = -1;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATTNexusSpawnLocation::StaticClass(), NexusSpawnLocations);
		for (int i = 0; i < NexusSpawnLocations.Num(); i++)
		{
			if (Cast<ATTNexusSpawnLocation>(NexusSpawnLocations[i])->IsActive)
			{
				FHitResult GroundHit;
				Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECC_WorldStatic, true, GroundHit);
				DistanceToMouse.Add(
					UE::Geometry::Distance(GroundHit.Location, NexusSpawnLocations[i]->GetActorLocation()));
			}
		}

		for (int i = 0; i < DistanceToMouse.Num(); i++)
		{
			if (DistanceToMouse[i] < Item)
			{
				Item = DistanceToMouse[i];
			}
		}
		for (int i = 0; i < DistanceToMouse.Num(); i++)
		{
			int k;
			k = DistanceToMouse[i];
			if (k == Item)
			{
				Key = i;
			}
		}

		if (Key != -1)
		{
			HoloBuilding->SetActorLocationAndRotation(NexusSpawnLocations[Key]->GetActorLocation(), FQuat::Identity);
			NexusSpawn = NexusSpawnLocations[Key]->GetActorLocation();


			for (int i = 0; i < GameModeBase->AllBuildingComponents.Num(); i++)
			{
				if (b_CanBuy && GameModeBase->AllBuildingComponents[i]->IsInRange(
						NexusSpawnLocations[Key]->GetActorLocation()) && HoloBuilding->Overlap.
					Num() == NULL)
				{
					HoloBuilding->BuildingMesh->SetMaterial(0, HoloBuilding->Green);
				}
				else
				{
					HoloBuilding->BuildingMesh->SetMaterial(0, HoloBuilding->Red);
				}
			}
		}
	}
}

void ATTDesktopPlayerPawn::ShowHologram(ABaseBuilding*& ReturnBuilding)
{

	FVector MousePos, MouseDir;
	FHitResult GroundHit;
	Cast<APlayerController>(GetController())->DeprojectMousePositionToWorld(MousePos, MouseDir);
	Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECC_WorldStatic, true, GroundHit);

	ChosenBuildingClass = BuildingClassMap[ChosenBuildingType];
	if (ChosenBuildingClass)
	{
		AActor* tempBuilding = GetWorld()->SpawnActor(ChosenBuildingClass);

		ReturnBuilding = Cast<ABaseBuilding>(tempBuilding);
		ReturnBuilding->BuildingMesh->SetCollisionProfileName(CollisionProfile.Name);
		ReturnBuilding->ChangeBuildingStateToHolo();

		// datatable met alle gebouwen uitlezen
		for (int i=0; i < BuildingDataTable->GetRowNames().Num() ; i++)
		{
			TArray<FName> rownames = BuildingDataTable->GetRowNames();
			FName rowname = rownames[i];
			FBuildingStats* BuildingStats = BuildingDataTable->FindRow<FBuildingStats>(rowname, "");
			if(BuildingStats->BuildingTypes == ChosenBuildingType)
			{
				ReturnBuilding->BuildingStats = *BuildingStats;
				printf("%p", BuildingStats);
				CanBuy(&ReturnBuilding->BuildingStats);
				break;
			}
		}
		// van elk gebouw de naam uitprinten in een forloop en ook de ID

		// in een forloop checken of de chosenbuildingtype overeenkomt met de id in de datatable

		// zo ja, toewijzen aan de buildingstats van return building
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unassigned building type in blueprint class! (%d)"), ChosenBuildingType);
	}
}

void ATTDesktopPlayerPawn::CanBuy(FBuildingStats* Buildingstats)
{
	const ATTPlayerState* InPlayerState = Cast<ATTPlayerState>(GetLocalViewingPlayerController()->PlayerState);

	if (InPlayerState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState is nullptr"));
		return;
	}
	b_CanBuy = InPlayerState->GoldAmount >= Buildingstats->GoldCost;
}

void ATTDesktopPlayerPawn::UpdateHoloBuiling()
{
	if (HoloBuilding != NULL)
	{
		HoloBuilding->BuildingMesh->SetStaticMesh(ChosenBuildingClass.GetDefaultObject()->BuildingMesh->GetStaticMesh());
	}
	else
	{
		ShowHologram(HoloBuilding);
	}
}
