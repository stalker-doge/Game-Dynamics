// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_visibleComponent = CreateDefaultSubobject<USceneComponent>(TEXT("VisibleComponent"));
	_collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	_collisionBox->SetupAttachment(_visibleComponent);
	_collisionBox->SetBoxExtent(FVector(5.f, 5.f, 5.f));
	_sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	_perceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	_attackDistance = 500.f;
	_sightConfig->SightRadius = _attackDistance;
	_sightConfig->LoseSightRadius = _attackDistance + 100.f;
	_sightConfig->PeripheralVisionAngleDegrees = 90.f;
	_sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	_sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	_sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	_perceptionComponent->ConfigureSense(*_sightConfig);
	_perceptionComponent->SetDominantSense(_sightConfig->GetSenseImplementation());
	_perceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemy::OnSeePlayer);
	_speed = 100.0f;
	_currentWaypoint = 0;
	_isPatrolling=true;
	_isAttacking = false;
	_damage = 10.f;
	_timeBeforeNextAttack = 3.f;
	_cooldown = 0.f;
}

void AEnemy::RotateTowards(FVector targetLocation)
{
	//rotate using interpolation
	FRotator newRotation = FRotationMatrix::MakeFromX(targetLocation - GetActorLocation()).Rotator();
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), newRotation, GetWorld()->GetDeltaSeconds(), 5.f));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = _speed;
	_waypoints = GetWaypoints();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_isPatrolling)
	{
		
		Patrol();
	}
	if (_isAttacking)
	{
		ChasePlayer();
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnSeePlayer(const TArray<AActor*>& _sensedActors)
{
	for (AActor* actor : _sensedActors)
	{
		if (actor->ActorHasTag("Player"))
		{
			_isPatrolling = false;
			_isAttacking = true;
			UE_LOG(LogTemp, Warning, TEXT("I see the player"));
			_target=actor;
		}
	}
}

void AEnemy::Patrol()
{
	//moves between the two waypoints
	if (_currentWaypoint == 0)
	{
		//move to waypoint 1
		FVector direction = _waypoints[1]->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		AddMovementInput(direction, _speed);
		//if the distance is less than 100, change the current waypoint to 1
		if (FVector::Dist(GetActorLocation(), _waypoints[1]->GetActorLocation()) < 100.f)
		{
			_currentWaypoint = 1;
		}
	}
	else if (_currentWaypoint == 1)
	{
		//move to waypoint 0
		FVector direction = _waypoints[0]->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		AddMovementInput(direction, _speed);
		//if the distance is less than 100, change the current waypoint to 0
		if (FVector::Dist(GetActorLocation(), _waypoints[0]->GetActorLocation()) < 100.f)
		{
			_currentWaypoint = 0;
		}
	}
}
void AEnemy::Attack()
{
	//if the cooldown is less than 0, attack the player
	if (_cooldown <= 0.f)
	{
		_target->TakeDamage(_damage, FDamageEvent(), GetController(), this);
		_cooldown = _timeBeforeNextAttack;
	}
	else
	{
		_cooldown -= GetWorld()->GetDeltaSeconds();
	}
}
void AEnemy::ChasePlayer()
{
	//moves towards the player
	FVector direction = _target->GetActorLocation() - GetActorLocation();
	direction.Normalize();
	AddMovementInput(direction, _speed);
	RotateTowards(_target->GetActorLocation());
	if (FVector::Dist(GetActorLocation(), _target->GetActorLocation()) < 100.f)
	{
		Attack();
	}
	//if the target is out of sight, patrol again
	if (FVector::Dist(GetActorLocation(), _target->GetActorLocation()) > _attackDistance)
	{
		_isPatrolling = true;
		_isAttacking = false;
		_target = nullptr;
	}
}
TArray<AActor*> AEnemy::GetWaypoints()
{
	for (TActorIterator<AActor> _actorItr(GetWorld()); _actorItr; ++_actorItr)
	{
		if (_actorItr->ActorHasTag("Waypoint"))
		{
			_waypoints.Add(*_actorItr);
		}
	}
	return _waypoints;
}

