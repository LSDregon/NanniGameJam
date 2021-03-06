// Copyright © 2022 Last Second


#include "SensorComponent.h"

#include "EventListenerComponent.h"
#include "SensorReceiverComponent.h"

// Sets default values for this component's properties
USensorComponent::USensorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	LaserDetected.AddDynamic(this, &USensorComponent::SensorActivated);
	// ...
}

void USensorComponent::SensorActivated()
{
	CallSensorReceivers();
}

void USensorComponent::SetEventListener(UEventListenerComponent* NewEventListener)
{
	EventListener = NewEventListener;
	if (EventListener)
	{
		LaserDetected.AddDynamic(this, &USensorComponent::TriggerTaskCompleted);
	}
	
}

void USensorComponent::CallSensorReceivers()
{
	if (ActorToActivateList.Num() > 0)
	{
		for (const TSoftObjectPtr<AActor> ActorToActivate : ActorToActivateList)
		{
			if (ActorToActivate)
			{
				if (const USensorReceiverComponent* SensorReceiverComponent = Cast<USensorReceiverComponent>(
					ActorToActivate->GetComponentByClass(USensorReceiverComponent::StaticClass())))
				{
					SensorReceiverComponent->SignalReceived.Broadcast();
				}
			}
		}
	}
}

void USensorComponent::TriggerTaskCompleted()
{
	if (EventListener)
	{
		if (EventListener->bIsInAEventTask && !EventListener->bIsActorEnable && !(EventListener->bIsTaskDone && bIsAlwaysActive))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Do Nothing"));
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Sensor Reached"));
			EventListener->TaskCompleted(GetOwner());
		}
	}
}
