// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bridge.generated.h"

UCLASS()
class GAMEDYNAMICS_API ABridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABridge();
	
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		TArray<AActor*> _waypoints;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		int _currentWaypoint;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		float _speed;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		float _springConstant;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		float _dampingFactor;

	UPROPERTY(EditAnywhere, Category = "Bridge")
		class UStaticMeshComponent* _mesh;

	UFUNCTION()
		void Move(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
