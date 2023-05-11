// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Orbs.generated.h"

UCLASS()
class GAMEDYNAMICS_API AOrbs : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbs();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class UStaticMeshComponent* _mesh;
	UPROPERTY(EditAnywhere)
		class USphereComponent* _collisionSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
