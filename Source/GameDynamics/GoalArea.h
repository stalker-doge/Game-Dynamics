// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalArea.generated.h"

UCLASS()
class GAMEDYNAMICS_API AGoalArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalArea();

	UPROPERTY(EditAnywhere,Category="Goal")
		class UStaticMeshComponent* GoalMesh;
	UPROPERTY(EditAnywhere, Category = "Goal")
		class UBoxComponent* Goal;
	UPROPERTY(EditAnywhere, Category = "Goal")
		class USoundBase* WinSound;
	
	UFUNCTION()
		void OnGoalOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
