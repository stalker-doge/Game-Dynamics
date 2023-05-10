// Fill out your copyright notice in the Description page of Project Settings.


#include "Orbs.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AOrbs::AOrbs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _mesh;
	_mesh->SetSimulatePhysics(true);
	_collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	_collisionSphere->SetupAttachment(_mesh);
	_collisionSphere->SetSphereRadius(50.f);
	_collisionSphere->SetCollisionProfileName(TEXT("Trigger"));
	

}

// Called when the game starts or when spawned
void AOrbs::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrbs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

