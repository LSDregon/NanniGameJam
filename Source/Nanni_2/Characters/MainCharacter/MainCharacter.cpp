// Copyright © 2022 Last Second


#include "MainCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	CameraComponent->SetupAttachment(SpringArm);

	PerceptionEmitter = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Noise Emitter"));
	if (!PerceptionEmitter) {
		this->AddOwnedComponent(PerceptionEmitter);
	}

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForeward"), this, &AMainCharacter::MoveForeward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::TurnUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMainCharacter::TurnRight);
}

void AMainCharacter::MoveForeward(float AxisValue)
{
	if (AxisValue != 0.0f){
		AddMovementInput(GetActorForwardVector() * AxisValue);
		//UE_LOG(LogTemp, Warning, TEXT("FWD %f"), AxisValue);
	}
}

void AMainCharacter::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f){
		AddMovementInput(GetActorRightVector() * AxisValue);
		//UE_LOG(LogTemp, Warning, TEXT("RIGHT %f"), AxisValue);
	}
}

void AMainCharacter::TurnUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * MouseSensitivity);
}

void AMainCharacter::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * MouseSensitivity);
}
