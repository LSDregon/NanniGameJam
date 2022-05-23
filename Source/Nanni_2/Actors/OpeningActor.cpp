// Fill out your copyright notice in the Description page of Project Settings.


#include "OpeningActor.h"

#include "Kismet/GameplayStatics.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/GeneralComponents/EventListenerComponent.h"
#include "Nanni_2/GeneralComponents/InteractionComponent.h"

// Sets default values
AOpeningActor::AOpeningActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;
	
	OpeningMesh = CreateDefaultSubobject<UStaticMeshComponent>("OpeningMesh");
	OpeningMesh->SetupAttachment(Scene);
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InteractionComponent->SetupAttachment(OpeningMesh);

	EventListener = CreateDefaultSubobject<UEventListenerComponent>(TEXT("Event Listener"));
	if (EventListener) this->AddOwnedComponent(EventListener);

	bIsAlwaysInteractable = true;
	OpenFront = true;
	IsClosed = true;
	ReadyState = true;
}

// Called when the game starts or when spawned
void AOpeningActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &AOpeningActor::StopOpening);
	InteractionComponent->OnInteract.AddDynamic(this, &AOpeningActor::OpeningOperation);
	InteractionComponent->OnInteract.AddDynamic(this, &AOpeningActor::TriggerTaskCompleted);

	if (const UWorld* World = GetWorld())
	{
		MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
	}

	RotateValue = 1.0f;
	if (DoorCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlRotation"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetState"));

		MyTimeline.AddInterpFloat(DoorCurve, TimelineCallback);
		MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}	
}
void AOpeningActor::StopOpening(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hello"));

	if (DotProductOnInteraction > 0 || IsClosed)
	{
		MyTimeline.Stop();
		SetState();		
	}
}
// Called every frame
void AOpeningActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EventListener->bIsInAEventTask && !EventListener->bIsActorEnable && !(EventListener->bIsTaskDone && bIsAlwaysInteractable))
	{
		OpeningMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		OpeningMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	}
	MyTimeline.TickTimeline(DeltaTime);
}

void AOpeningActor::ControlRotation()
{
	TimelineValue = MyTimeline.GetPlaybackPosition();
	if (RotateValue > 0)
	{
		CurveFloatValue = RotateValue * DoorCurve->GetFloatValue(TimelineValue);
	}
	else
	{
		CurveFloatValue = RotateValue * DoorCurve->GetFloatValue(TimelineValue) - 180.0f;
	}
	
	const FQuat NewRotation = FQuat(FRotator(0.0f, CurveFloatValue, 0.0f));
	OpeningMesh->SetRelativeRotation(NewRotation);
}

void AOpeningActor::SetState()
{
	ReadyState = true;
}

void AOpeningActor::OpeningOperation(AMainCharacter* Character)
{
	DotProductOnInteraction = GetDotProduct();
	if (ReadyState)
	{
		IsClosed = !IsClosed;

		if (!IsClosed)
		{
			RotateValue = 1.0f;		

			if (!OpenFront)
			{
				RotateValue = -1.0f;
			}
			else
			{
				RotateValue = 1.0f;
			}
			ReadyState = false;
			MyTimeline.Play();
		}
		else
		{
			ReadyState = false;
			MyTimeline.Reverse();			
		}
	}
}


float AOpeningActor::GetDotProduct() const
{
	if (!MainCharacter)
	{
		return 0;
	}
	const FVector MainCharacterLocation = MainCharacter->GetActorLocation();
	const FVector OpeningActorLocation = GetRootComponent()->GetComponentLocation();
	const FVector VectorDifference = OpeningActorLocation - MainCharacterLocation;

	const FVector NormalizedVector = VectorDifference.GetSafeNormal(0.0001);
	const FVector OpeningActorForward = GetRootComponent()->GetForwardVector();
	
	return FVector::DotProduct(NormalizedVector, OpeningActorForward);
}

void AOpeningActor::TriggerTaskCompleted(AMainCharacter* Character)
{
	EventListener->TaskCompleted(this);
}


