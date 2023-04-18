// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"

void APlayerCharacter::MoveX(float xinput)
{
    if ((Controller != NULL) && (xinput != 0.0f))
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
        // Limit pitch when walking or falling
        if (GetCharacterMovement()->IsMovingOnGround()||GetCharacterMovement()->IsFalling())
        {
            Rotation.Pitch = 0.0f;
        }
        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        AddMovementInput(Direction, xinput);
    }
}

void APlayerCharacter::MoveY(float yinput)
{
    if ((Controller != NULL) && (yinput != 0.0f))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, yinput);
    }
}

void APlayerCharacter::Fire(float val)
{
	if (val > 0)
	{

		//Draw a raycast from the camera and print the hit actor
		FHitResult HitResult;
		FVector Start = _camera->GetComponentLocation();
		FVector ForwardVector = _camera->GetForwardVector();
		FVector End = ((ForwardVector * 1000.f) + Start);
		FCollisionQueryParams CollisionParams;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		if (bHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
			HitResult.GetActor()->SetActorLocation(_collisionBox->GetComponentLocation());
		}
	}
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
    AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_visibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("visibleComponent"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bEnableCameraLag = true;
	_camera->SetupAttachment(CameraBoom);
	_visibleComponent->SetupAttachment(RootComponent);
	_collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	_collisionBox->SetupAttachment(RootComponent);
	_collisionBox->SetBoxExtent(FVector(5.f, 5.f, 5.f));
	//sets it a bit infront of the player
	_collisionBox->SetRelativeLocation(FVector(30.f, 0.f, 0.f));
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveX);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveY);
	InputComponent->BindAxis("MouseX", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("MouseY", this, &APlayerCharacter::AddControllerPitchInput);
	InputComponent->BindAxis("Fire", this, &APlayerCharacter::Fire);
}

