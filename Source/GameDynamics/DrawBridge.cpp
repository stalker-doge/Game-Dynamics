// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawBridge.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADrawBridge::ADrawBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_hitsNeeded = 3;
	_currentHits = 0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_mesh->SetupAttachment(RootComponent);

}

void ADrawBridge::ScoreHit()
{
	_currentHits++;
	if (_currentHits >= _hitsNeeded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bridge is down"));
	}
}

// Called when the game starts or when spawned
void ADrawBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrawBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

