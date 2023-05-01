// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetOrb.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATargetOrb::ATargetOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = OrbMesh;
	
	Orb = CreateDefaultSubobject<USphereComponent>(TEXT("Orb"));
	Orb->SetupAttachment(RootComponent);


}

void ATargetOrb::Win()
{
	Destroy();
}

// Called when the game starts or when spawned
void ATargetOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

