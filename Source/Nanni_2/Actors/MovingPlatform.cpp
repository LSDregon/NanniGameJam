// Copyright © 2022 Last Second


#include "MovingPlatform.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	SetRootComponent(PlatformMesh);

	IsDown = false;
	ReadyState = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	InitialZValue = GetActorLocation().Z;
	
	DownValue = 1.0f;
	if (DownCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlMovement"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetState"));

		MyTimeline.SetPlaybackPosition(0, false);
		MyTimeline.AddInterpFloat(DownCurve, TimelineCallback);
		MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
	
	TArray<AActor*> ChildActorList = TArray<AActor*>();
	GetAttachedActors(ChildActorList);
	
	for (AActor* ChildActor : ChildActorList)
	{
		if (ChildActor && UKismetMathLibrary::ClassIsChildOf(ChildActor->GetClass(), ATriggerBoxCustom::StaticClass()))
		{
			if (ATriggerBoxCustom* TriggerArea = Cast<ATriggerBoxCustom>(ChildActor))
			{
				Trigger = TriggerArea;
				Trigger->OnActorBeginOverlap.AddDynamic(this, &AMovingPlatform::MovingOperation);
				Trigger->OnActorBeginOverlap.AddDynamic(this, &AMovingPlatform::StartPlaySound);
				Trigger->OnActorEndOverlap.AddDynamic(this, &AMovingPlatform::StopMoving);;
				Trigger->OnActorEndOverlap.AddDynamic(this, &AMovingPlatform::StopPlaySound);
			}
		}
	}
}

void AMovingPlatform::StopMoving(AActor* OverlappedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hello"));
	MyTimeline.Stop();
	SetState();
	MovingOperation(OverlappedActor, OtherActor);
}
// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyTimeline.TickTimeline(DeltaTime);
	if (MyTimeline.GetPlaybackPosition() == 0)
	{
		FVector NewPosition = GetActorLocation();
		NewPosition.Z = InitialZValue;
		SetActorLocation(NewPosition);
	}
}

void AMovingPlatform::ControlMovement()
{
	TimelineValue = MyTimeline.GetPlaybackPosition();
	
	CurveFloatValue = DownValue * DownCurve->GetFloatValue(TimelineValue);
	
	PlatformPosition = GetActorLocation();
	PlatformPosition.Z = PlatformPosition.Z + CurveFloatValue;
	SetActorLocation(PlatformPosition);
}

void AMovingPlatform::SetState()
{
	ReadyState = true;
}

void AMovingPlatform::MovingOperation(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ReadyState)
	{
		if (!IsDown)
		{
			DownValue = -1.0f;	
			ReadyState = false;
			MyTimeline.Play();
		}
		else
		{
			DownValue = 1.0f;	
			ReadyState = false;
			MyTimeline.Reverse();			
		}
		IsDown = !IsDown;
	}
}

void AMovingPlatform::StartPlaySound(AActor* OverlappedActor, AActor* OtherActor)
{
	PlaySound();
}

void AMovingPlatform::StopPlaySound(AActor* OverlappedActor, AActor* OtherActor)
{
	StopSound();
}
