// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawBridge.generated.h"

UCLASS()
class GAMEDYNAMICS_API ADrawBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrawBridge();

	UPROPERTY(EditAnywhere)
		int _hitsNeeded;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* _mesh;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATargetOrb> _targetOrbClass;

	void ScoreHit();
	int _currentHits;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
