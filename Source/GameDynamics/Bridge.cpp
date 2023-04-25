// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABridge::ABridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_speed = 100.0f;
	_springConstant = 100.0f;
	_dampingFactor = 10.0f;
	_currentWaypoint = 0;
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_mesh->SetupAttachment(RootComponent);
}

void ABridge::Move(float DeltaTime)
{
	//moves between two waypoints in the array, slowing down as it approaches one, using Simple Harmonic Motion
	if (_waypoints.Num() > 0)
	{
		float distance = FVector::Distance(_waypoints[_currentWaypoint]->GetActorLocation(), GetActorLocation());
		//if the distance is less than 1, move to the next waypoint
		if (distance < 1.0f)
		{
			_currentWaypoint++;
			if (_currentWaypoint >= _waypoints.Num())
			{
				_currentWaypoint = 0;
			}
		}

		//calculate the distance to the next waypoint
		FVector direction = _waypoints[_currentWaypoint]->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		FVector _velocity = direction * _speed;

		//calculate the distance to the next waypoint
		FVector displacement = _waypoints[_currentWaypoint]->GetActorLocation() - GetActorLocation();
		float distanceToTarget = displacement.Size();

		//calculate the spring force
		float springForce = distanceToTarget * _springConstant;

		//calculate the damping force
		float dampingForce = _dampingFactor * FVector::DotProduct(_velocity, displacement);

		//calculate the total force
		float totalForce = springForce + dampingForce;

		//calculate the acceleration
		FVector acceleration = totalForce * direction;

		//update the velocity
		_velocity += acceleration * DeltaTime;

		//update the position
		SetActorLocation(GetActorLocation() + _velocity * DeltaTime);
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

