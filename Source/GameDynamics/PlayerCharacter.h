// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GAMEDYNAMICS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
		


public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UPROPERTY(EditAnywhere)
		USceneComponent* _visibleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* _camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float _speed;
	//sets up a dummy collision box for the player
	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* _collisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float _health;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void ReceiveDamage(float damage);
	
	AActor* _heldActor;
	bool _isHolding;
	bool _isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FString _UIMessage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		int _score;
	
	void MoveX(float xinput);
	void MoveY(float yinput);
	void Fire();
	void Release();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
