// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class GAMEDYNAMICS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere)
		USceneComponent* _visibleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* _camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float _speed;


	void MoveX(float xinput);
	void MoveY(float yinput);
	void CameraYaw(float Yaw);
	void CameraPitch(float Pitch);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector currentVelocity;
	FRotator cameraRotator;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
