// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbSpawner.h"

// Sets default values
AOrbSpawner::AOrbSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	

}

void AOrbSpawner::SpawnOrb()
{
	
	if (_currentOrbs < _maxOrbs)
	{
		FVector spawnLocation = GetActorLocation();
		spawnLocation.X += FMath::RandRange(-_spawnRadius, _spawnRadius);
		spawnLocation.Y = 10;
		spawnLocation.Z += FMath::RandRange(-_spawnRadius, _spawnRadius);
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOrbs* orb = GetWorld()->SpawnActor<AOrbs>(OrbClass, spawnLocation, FRotator::ZeroRotator, spawnParams);
		_currentOrbs++;
	}
}

// Called when the game starts or when spawned
void AOrbSpawner::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AOrbSpawner::SpawnOrb, _spawnDelay, true, 0.0f);
	
}

// Called every frame
void AOrbSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

