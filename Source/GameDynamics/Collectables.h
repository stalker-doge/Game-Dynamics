// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectables.generated.h"

UCLASS()
class GAMEDYNAMICS_API ACollectables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectables();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectables")
		int32 CollectableValue;
	
	UPROPERTY(EditAnywhere, Category = "Collectables")
		class UStaticMeshComponent* CollectableMesh;
	UPROPERTY(EditAnywhere, Category = "Collectable")
		class USphereComponent* Orb;

	UFUNCTION()
		void OnCollectableOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
