// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterZone.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"

// Sets default values
AWaterZone::AWaterZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_triggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	_triggerVolume->SetCollisionProfileName(TEXT("Trigger"));
	_triggerVolume->SetGenerateOverlapEvents(true);
	_triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AWaterZone::OnOverlapBegin);
	_triggerVolume->SetupAttachment(RootComponent);
	_damage = 5.0f;
	

}

void AWaterZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			Player->TakeDamage(_damage, FDamageEvent(), nullptr, this);
			Player->Respawn();
		}
	}
}


// Called when the game starts or when spawned
void AWaterZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

