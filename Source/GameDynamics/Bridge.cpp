// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABridge::ABridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_speed = 100.0f;
	_currentWaypoint = 0;
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_mesh->SetupAttachment(RootComponent);
}

void ABridge::Move(float DeltaTime)
{
	//moves between two waypoints in the array, slowing down as it approaches one, using Simple Harmonic Motion
	if (_waypoints.Num() > 0)
	{
		FVector currentLocation = GetActorLocation();
		FVector targetLocation = _waypoints[_currentWaypoint]->GetActorLocation();
		FVector direction = targetLocation - currentLocation;
		float distance = direction.Size();
		direction.Normalize();
		float speed = _speed;
		if (distance < 100.0f)
		{
			speed = _speed * (distance / 100.0f);
		}
		FVector velocity = direction * speed;
		FVector newPosition = currentLocation + velocity * DeltaTime;
		SetActorLocation(newPosition);
		if (distance < 1.0f)
		{
			_currentWaypoint++;
			if (_currentWaypoint >= _waypoints.Num())
			{
				_currentWaypoint = 0;
			}
		}
	}
}

// Called when the game starts or when spawned
void ABridge::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

