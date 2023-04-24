// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveTargets.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawBridge.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectiveTargets::AObjectiveTargets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	_collisionBox->SetupAttachment(_mesh);
	_collisionBox->SetCollisionProfileName(TEXT("Trigger"));
	_mesh->SetupAttachment(RootComponent);
	_mesh->SetCollisionProfileName(TEXT("NoCollison"));
	
	_collisionBox->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveTargets::OnOverlapBegin);

}

void AObjectiveTargets::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Toggle();
}

void AObjectiveTargets::Toggle()
{
	UE_LOG(LogTemp, Warning, TEXT("Toggle"));
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADrawBridge::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		ADrawBridge* DrawBridge = Cast<ADrawBridge>(Actor);
		DrawBridge->ScoreHit();
	}
}

// Called when the game starts or when spawned
void AObjectiveTargets::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectiveTargets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

