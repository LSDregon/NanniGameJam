// Copyright © 2022 Last Second


#include "EventListenerComponent.h"

// Sets default values for this component's properties
UEventListenerComponent::UEventListenerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bIsInAEventTask = false;
	bIsTaskDone = false;
	bIsActorEnable = false;
	// ...
}

void UEventListenerComponent::TaskCompleted(AActor* ActorListener)
{
	UE_LOG(LogTemp, Warning, TEXT("TaskCompleted"))
	if (bIsInAEventTask)
	{
		UE_LOG(LogTemp, Warning, TEXT("bIsInAEventTask"))
		if (EventManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("EventManager ok"))
			SetIsActorEnable(false);
			SetIsTaskDone(true);
			EventManager->OnTaskFinished.Broadcast(ActorListener, this);
		}
	}
}

// Called when the game starts
void UEventListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UEventListenerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}
