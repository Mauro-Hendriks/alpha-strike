// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOYBOXTACTICS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(ExposeOnSpawn=true))
	int MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int CurrentHealth;

	UFUNCTION(BlueprintCallable)
	void ChangeHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float Amount);

	UFUNCTION(BlueprintCallable) 
	float GetNormalizedHealth() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdated OnHealthUpdated;
};