// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Orbs.h"
#include "OrbSpawner.generated.h"

UCLASS()
class GAMEDYNAMICS_API AOrbSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbSpawner();

	UPROPERTY(EditAnywhere, Category = "Orb")
		TSubclassOf<class AOrbs> OrbClass;

	UPROPERTY(EditAnywhere, Category = "Orb")
		int32 _maxOrbs = 10;

	UPROPERTY(EditAnywhere, Category = "Orb")
		int32 _currentOrbs = 0;

	UPROPERTY(EditAnywhere, Category = "Orb")
		float _spawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Orb")
		float _spawnRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Orb")
		float OrbMinScale = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Orb")
		float OrbMaxScale = 1.5f;

	UFUNCTION()
		void SpawnOrb();

	UPROPERTY(EditAnywhere, Category = "Orb")
		FTimerHandle SpawnTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
