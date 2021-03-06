// Copyright © 2022 Last Second


#include "TriggerBoxCustom.h"

#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/GeneralComponents/EventListenerComponent.h"

ATriggerBoxCustom::ATriggerBoxCustom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Shape"));
	SetRootComponent(CollisionComponent);
	
	EventListener = CreateDefaultSubobject<UEventListenerComponent>(TEXT("Event Listener"));
	if (EventListener) this->AddOwnedComponent(EventListener);

	bIsAlwaysInteractable = true;
}

// Called when the game starts or when spawned
void ATriggerBoxCustom::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxCustom::TriggerTaskCompleted);
}

// Called every frame
void ATriggerBoxCustom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EventListener->bIsInAEventTask && !EventListener->bIsActorEnable && !(EventListener->bIsTaskDone && bIsAlwaysInteractable))
	{
		CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}

void ATriggerBoxCustom::TriggerTaskCompleted(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		if (EventListener->IsIsInAEventTask())
		{
			EventListener->TaskCompleted(this);
			OnActorBeginOverlap.RemoveDynamic(this, &ATriggerBoxCustom::TriggerTaskCompleted);
		}
	}
}

