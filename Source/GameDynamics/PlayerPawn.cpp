// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"



// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_visibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("visibleComponent"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	_camera->SetupAttachment(CameraBoom);
	_visibleComponent->SetupAttachment(RootComponent);
	_speed = 500.0f;
}
void APlayerPawn::MoveX(float xinput)
{
	currentVelocity.X = FMath::Clamp(xinput, -1.0f, 1.0f) * _speed;
}

void APlayerPawn::MoveY(float yinput)
{
	currentVelocity.Y = FMath::Clamp(yinput, -1.0f, 1.0f) * _speed;
}

void APlayerPawn::CameraYaw(float Yaw)
{
	cameraRotator.Yaw += Yaw;
}

void APlayerPawn::CameraPitch(float Pitch)
{
	cameraRotator.Pitch += Pitch;
}


// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Makes it so that the player moves in the direction they are facing
	FVector forward = GetActorForwardVector();
	FVector right = GetActorRightVector();
	FVector move = (right * currentVelocity.Y + forward * currentVelocity.X) * DeltaTime;
	AddActorWorldOffset(move, true);
	//Makes it so that the camera rotates with the player
	FRotator rot = GetActorRotation();
	rot.Yaw += cameraRotator.Yaw;
	rot.Pitch += FMath::Clamp(cameraRotator.Pitch, -80.0f, 80.0f);
	SetActorRotation(rot);
	cameraRotator = FRotator::ZeroRotator;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveX);
	InputComponent->BindAxis("MoveRight", this,& APlayerPawn::MoveY);
	InputComponent->BindAxis("MouseX", this, &APlayerPawn::CameraYaw);
	InputComponent->BindAxis("MouseY", this, &APlayerPawn::CameraPitch);
}

