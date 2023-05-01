// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"


// Sets default values
ACollectables::ACollectables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollectableMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = CollectableMesh;
	CollectableMesh->SetCollisionProfileName(TEXT("NoCollision"));

	Orb = CreateDefaultSubobject<USphereComponent>(TEXT("Orb"));
	Orb->SetupAttachment(CollectableMesh);

	Orb->OnComponentBeginOverlap.AddDynamic(this, &ACollectables::OnCollectableOverlap);
	CollectableValue = 1;
}

void ACollectables::OnCollectableOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		Player->_score += CollectableValue;
		Destroy();
	}
}

// Called when the game starts or when spawned
void ACollectables::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

