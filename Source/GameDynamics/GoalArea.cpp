// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalArea.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "TargetOrb.h"
#include "PlayerCharacter.h"

// Sets default values
AGoalArea::AGoalArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Goal = CreateDefaultSubobject<UBoxComponent>(TEXT("Goal"));
	Goal->SetCollisionProfileName(TEXT("Trigger"));
	Goal->SetGenerateOverlapEvents(true);
	Goal->OnComponentBeginOverlap.AddDynamic(this, &AGoalArea::OnOverlapBegin);
	RootComponent = Goal;
	
	GoalMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	GoalMesh->SetupAttachment(RootComponent);
	GoalMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	
	WinSound = CreateDefaultSubobject<USoundBase>(TEXT("SoundBase"));

}

void AGoalArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	ATargetOrb* TargetOrb = Cast<ATargetOrb>(OtherActor);
	if (TargetOrb)
	{
		if (WinSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, WinSound, GetActorLocation());
			APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
			Player->_UIMessage = "You won!";
			TargetOrb->Win();
		}
	}
}

// Called when the game starts or when spawned
void AGoalArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

