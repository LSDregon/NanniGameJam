// Copyright © 2022 Last Second


#include "WaterGate.h"

#include "Components/LightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Nanni_2/Miscellaneous/TriggerBoxCustom.h"

// Sets default values
AWaterGate::AWaterGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	
	Scene2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scene2"));
	Scene2->SetupAttachment(GetRootComponent());
	
	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gate Mesh"));
	GateMesh->SetupAttachment(Scene2);
	
	bIsUpDownMovement = true;
	IsDown = false;
	ReadyState = true;
}

// Called when the game starts or when spawned
void AWaterGate::BeginPlay()
{
	Super::BeginPlay();

	InitialZValue = Scene2->GetComponentLocation().Z;
    
	if (DownCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlMovement"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetState"));

		MyTimeline.AddInterpFloat(DownCurve, TimelineCallback);
		MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
	
	if (DependentTrigger)
	{
		DependentTrigger->OnActorBeginOverlap.AddDynamic(this, &AWaterGate::MovingOperation);
		DependentTrigger->OnActorBeginOverlap.AddDynamic(this, &AWaterGate::ShowWater);
	}
}

// Called every frame
void AWaterGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyTimeline.TickTimeline(DeltaTime);
}

void AWaterGate::ControlMovement()
{
	TimelineValue = MyTimeline.GetPlaybackPosition();
	
	CurveFloatValue = DownValue * DownCurve->GetFloatValue(TimelineValue);

	if (bIsUpDownMovement)
	{
		PlatformPosition = GetActorLocation();
		PlatformPosition.Z = PlatformPosition.Z + CurveFloatValue;
		Scene2->SetWorldLocation(PlatformPosition);
	}
	else
	{
		const FQuat NewRotation = FQuat(FRotator(0.0f, CurveFloatValue, 0.0f));
		Scene2->SetRelativeRotation(NewRotation);
	}
}

void AWaterGate::SetState()
{
	ReadyState = true;
}

void AWaterGate::MovingOperation(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ReadyState)
	{
		if (!IsDown)
		{
			DownValue = 1.0f;	
			ReadyState = false;
			MyTimeline.Play();
		}	
	}
}

void AWaterGate::ShowWater(AActor* OverlappedActor, AActor* OtherActor)
{
	TArray<AActor*> ChildActorList = TArray<AActor*>();
	GetAttachedActors(ChildActorList);
	for (const AActor* ChildActor : ChildActorList)
	{
		if (UStaticMeshComponent* ChildActorStaticMeshComponent = Cast<UStaticMeshComponent>(ChildActor->GetComponentByClass(UStaticMeshComponent::StaticClass())))
		{
			ChildActorStaticMeshComponent->SetMaterial(0, WaterMaterialInstance);
		}
	}
	DependentTrigger->OnActorBeginOverlap.RemoveDynamic(this, &AWaterGate::MovingOperation);
	DependentTrigger->OnActorBeginOverlap.RemoveDynamic(this, &AWaterGate::ShowWater);
}