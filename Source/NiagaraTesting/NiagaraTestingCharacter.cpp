// Copyright Epic Games, Inc. All Rights Reserved.

#include "NiagaraTestingCharacter.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Camera/CameraComponent.h"
#include "Characters/AI/Stag.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Environment/Boulder.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/Logger.h"

ANiagaraTestingCharacter::ANiagaraTestingCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ANiagaraTestingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("PlaceBoulder", IE_Pressed, this, &ANiagaraTestingCharacter::PlaceBoulder);
	PlayerInputComponent->BindAction("PickUpBoulder", IE_Pressed, this, &ANiagaraTestingCharacter::PickUpBoulder);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ANiagaraTestingCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ANiagaraTestingCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
}

void ANiagaraTestingCharacter::PlaceBoulder()
{
	const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	const FVector StartPosition = PlayerCameraManager->K2_GetActorLocation();
	const FVector EndPosition = StartPosition + PlayerCameraManager->GetActorForwardVector() * FVector(InteractDistance, InteractDistance, InteractDistance);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Visibility, Params))
	{
	    GetWorld()->SpawnActor(BoulderClass, &HitResult.ImpactPoint);

		NiagaraComponent->SetNiagaraVariablePosition("BoulderPosition", HitResult.ImpactPoint);

		for (UNiagaraComponent* SavedNiagaraComponent : SavedNiagaraComponents)
		{
			SavedNiagaraComponent->SetNiagaraVariablePosition("BoulderPosition", HitResult.ImpactPoint);
		}
	}
}

void ANiagaraTestingCharacter::PickUpBoulder()
{
	const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	const FVector StartPosition = PlayerCameraManager->K2_GetActorLocation();
	const FVector EndPosition = StartPosition + PlayerCameraManager->GetActorForwardVector() * FVector(InteractDistance, InteractDistance, InteractDistance);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Visibility, Params))
	{
	    if (ABoulder* Boulder = Cast<ABoulder>(HitResult.GetActor()))
	    {
			Boulder->PickUpBoulder();
			SavedNiagaraComponents.Add(Boulder->GetNiagaraComponent());
	    }
	}
}

void ANiagaraTestingCharacter::BeginPlay()
{
    Super::BeginPlay();

	FLogger::CheckAndLogIsPropertySet(this, BoulderClass, GET_MEMBER_NAME_CHECKED(ANiagaraTestingCharacter, BoulderClass));

	if (FLogger::CheckAndLogIsPropertySet(this, NiagaraSystem, GET_MEMBER_NAME_CHECKED(ANiagaraTestingCharacter, NiagaraSystem)))
	{
		const FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 10.0f);	// 10.0f, so that beetles can land on the ground, which sets their rotation correctly.
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, SpawnLocation);
		NiagaraComponent->SetNiagaraVariablePosition("PlayerPosition", GetActorLocation());
	}
}

void ANiagaraTestingCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (GetVelocity().SizeSquared() > 0.0f)	// Is Player moving?
	{
		if (FLogger::CheckAndLogIsValidPtr(NiagaraComponent, __FUNCTION__))
		{
			NiagaraComponent->SetNiagaraVariablePosition("PlayerPosition", GetActorLocation());
		}
	}
}

void ANiagaraTestingCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANiagaraTestingCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
