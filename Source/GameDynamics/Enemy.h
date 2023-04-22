// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class GAMEDYNAMICS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	UPROPERTY(EditAnywhere)
		USceneComponent* _visibleComponent;
	
	UPROPERTY(EditAnywhere)
		float _speed;
	
	UPROPERTY(EditAnywhere)
		class UBoxComponent* _collisionBox;
	
	UPROPERTY(EditAnywhere)
		class UBoxComponent* _attackBox;
	
	
	//waypoint system variables
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		TArray<AActor*> _waypoints;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		int _currentWaypoint;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		float _waypointDistance;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		bool _isPatrolling;
	UPROPERTY(EditAnywhere, Category = "Waypoints")
		bool _isAttacking;

	//AI stuff
	UPROPERTY(EditAnywhere)
		AActor* _target;
	UPROPERTY(EditAnywhere)
		float _attackDistance;
	UPROPERTY(EditAnywhere, Category = "AI")
		class UAIPerceptionComponent* _perceptionComponent;
	UPROPERTY(EditAnywhere, Category = "AI")
		class UAISenseConfig_Sight* _sightConfig;

	UFUNCTION()
		void OnSeePlayer(const TArray<AActor*>& _sensedActors);
	
	UFUNCTION()
		void Patrol();

	UFUNCTION()
		void Attack();

	UFUNCTION()
		TArray<AActor*> GetWaypoints();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
