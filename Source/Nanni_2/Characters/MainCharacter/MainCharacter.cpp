// Copyright © 2022 Last Second


#include "MainCharacter.h"

#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Nanni_2/Actors/GrabActor.h"
#include "Nanni_2/GeneralComponents/InteractionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	CameraComponent->SetupAttachment(SpringArm);

	GrabbedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grabbed Mesh"));
	GrabbedMesh->SetupAttachment(CameraComponent);
	ThrowDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ThrowDirection Mesh"));
	ThrowDirection->SetupAttachment(GrabbedMesh);

	PerceptionEmitter = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Noise Emitter"));
	if (!PerceptionEmitter) {
		this->AddOwnedComponent(PerceptionEmitter);
	}
	
	ThrowingVelocity = 100.f;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionCheckFrequency = 0.f;
	InteractionCheckDistance = 1000.f;
	HasSomthingToThrow = false;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PerformInteractionCheck();
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForeward"), this, &AMainCharacter::MoveForeward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::TurnUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMainCharacter::TurnRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AMainCharacter::BeginInteract);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &AMainCharacter::EndInteract);
	
	PlayerInputComponent->BindAction(TEXT("Throw"), IE_Pressed, this, &AMainCharacter::ThrowItem);
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

void AMainCharacter::ThrowItem()
{
	if (HasSomthingToThrow)
	{
		if (AGrabActor* ThrownActor = GetWorld()->SpawnActor<AGrabActor>(AGrabActor::StaticClass(), GrabbedMesh->K2_GetComponentToWorld()))
		{
			ThrownActor->SetGrabActor(GrabbedActorRef);

			ThrownActor->GrabbMesh->SetSimulatePhysics(true);
			ThrownActor->GrabbMesh->SetStaticMesh(GrabbedMesh->GetStaticMesh());
			ThrownActor->GrabbMesh->SetMaterial(0, GrabbedMesh->GetMaterial(0));
			ThrownActor->SetActorEnableCollision(true);
			ThrownActor->SetActorHiddenInGame(false);
			ThrownActor->GrabbMesh->SetSimulatePhysics(true);
			const FVector test = ThrowDirection->GetForwardVector() * ThrowingVelocity;
			ThrownActor->GrabbMesh->SetPhysicsLinearVelocity(test * ThrowingVelocity);
		}
		
		GrabbedMesh->SetStaticMesh(nullptr);
		HasSomthingToThrow = false;
		GrabbedActorRef = nullptr;
	}
}

void AMainCharacter::TurnUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * MouseSensitivity);
	//UE_LOG(LogTemp, Warning, TEXT("RIGHT %f"), AxisValue);
}

void AMainCharacter::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * MouseSensitivity);
	//UE_LOG(LogTemp, Warning, TEXT("RIGHT %f"), AxisValue);
}

#pragma region Interaction System

void AMainCharacter::PerformInteractionCheck()
{

	if(GetController() == nullptr){
		return;
	}

	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector EyesLoc;
	FRotator EyesRot;

	GetController()->GetPlayerViewPoint(EyesLoc, EyesRot);

	FVector TraceStart = EyesLoc;
	FVector TraceEnd = (EyesRot.Vector() * InteractionCheckDistance) + TraceStart;
	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if(TraceHit.GetActor())
		{
			if(UInteractionComponent* InteractionComponent = Cast<UInteractionComponent>(TraceHit.GetActor()->GetComponentByClass(UInteractionComponent::StaticClass())))
			{
				float Distance = (TraceStart - TraceHit.ImpactPoint).Size();

				if(InteractionComponent != GetInteractable() && Distance <= InteractionComponent->InteractionDistance)
				{
					FounddNewInteractable(InteractionComponent);
				}
				else if (Distance > InteractionComponent->InteractionDistance && GetInteractable())
				{
					CouldntFindInteractable();
				}

				return;

			}
		}
	}

	CouldntFindInteractable();

}

void AMainCharacter::CouldntFindInteractable()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_Interact))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	}

	if(UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndFocus(this);

		if (InteractionData.bInteractHelf)
		{
			EndInteract();
		}
	}

	InteractionData.ViewedInteractionComponent = nullptr;
}

void AMainCharacter::FounddNewInteractable(UInteractionComponent* Interactable)
{
	EndInteract();

	if(UInteractionComponent* OldInteractable = GetInteractable())
	{
		OldInteractable->EndFocus(this);
	}

	InteractionData.ViewedInteractionComponent = Interactable;
	Interactable->BeginFocus(this);
}

void AMainCharacter::BeginInteract()
{
	InteractionData.bInteractHelf = true;

	if (UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->BeginInteract(this);

		if (FMath::IsNearlyZero(Interactable->InteractionTime))
		{
			Interact();
		}
		else
		{
			GetWorldTimerManager().SetTimer(TimerHandle_Interact, this, &AMainCharacter::Interact, Interactable->InteractionTime, false);
		}
	}
}

void AMainCharacter::EndInteract()
{
	InteractionData.bInteractHelf = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if (UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndInteract(this);
	}
}

void AMainCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if(const UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->Interact(this);
	}
}

bool AMainCharacter::IsInteracting() const
{
	return GetWorldTimerManager().IsTimerActive(TimerHandle_Interact);
}

float AMainCharacter::GetRemainingInteractTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(TimerHandle_Interact);
}

#pragma endregion 