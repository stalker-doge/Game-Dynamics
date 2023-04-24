// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "GameplayTagContainer.h"

void APlayerCharacter::ReceiveDamage(float damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		_health = 0;
		_isDead = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), _health);
}

void APlayerCharacter::MoveX(float xinput)
{
    if ((Controller != NULL) && (xinput != 0.0f))
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
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

void APlayerCharacter::Fire()
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
			//checks if the hitresult is movable
			if (HitResult.GetActor()->GetRootComponent()->IsSimulatingPhysics())
			{
				HitResult.GetActor()->SetActorLocation(_collisionBox->GetComponentLocation());
				_heldActor = HitResult.GetActor();
				_isHolding = true;
			}

		}
}

void APlayerCharacter::Release()
{
	if (_isHolding)
	{
		//throws the held actor away from the player using physics
		FVector ForwardVector = _camera->GetForwardVector();
		FVector ForceVector = ForwardVector * 1000.f;
		//grabs the held actors static mesh
		UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(_heldActor->GetRootComponent());
		StaticMesh->AddImpulse(ForceVector, NAME_None, true);
		StaticMesh->SetEnableGravity(true);
		StaticMesh = nullptr;
		_heldActor = nullptr;
		_isHolding = false;
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
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bUsePawnControlRotation = true;
	_camera->SetupAttachment(CameraBoom);
	_camera->bUsePawnControlRotation = true;
	_visibleComponent->SetupAttachment(RootComponent);
	_collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	_collisionBox->SetupAttachment(RootComponent);
	_collisionBox->SetBoxExtent(FVector(5.f, 5.f, 5.f));
	CameraBoom->SetupAttachment(_visibleComponent);

	//sets it a bit infront of the player
	_collisionBox->SetRelativeLocation(FVector(70.f, 0.f, 0.f));

	_isHolding = false;
	_heldActor = nullptr;
	_health = 100.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), UAISense_Sight::StaticClass(), this);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_isHolding)
	{
		_heldActor->SetActorLocation(_collisionBox->GetComponentLocation());
		//disable the held Actors gravity
		UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(_heldActor->GetRootComponent());
		StaticMesh->SetEnableGravity(false);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerCharacter::Fire);
	InputComponent->BindAction("PickUp", IE_Released, this, &APlayerCharacter::Release);
	
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveX);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveY);
	InputComponent->BindAxis("MouseX", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("MouseY", this, &APlayerCharacter::AddControllerPitchInput);
	
}

float APlayerCharacter::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ReceiveDamage(DamageAmount);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
