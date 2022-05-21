// Copyright © 2022 Last Second


#include "SensorComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Sensor Reached"));
	if (ActorToActivateList.Num() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ActorToActivateList.Num"));
		for (const TSoftObjectPtr<AActor> ActorToActivate : ActorToActivateList)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ActorToActivate"));
			if (ActorToActivate)
			{
				//UE_LOG(LogTemp, Warning, TEXT("ActorToActivate ok"));
				if (const USensorReceiverComponent* SensorReceiverComponent = Cast<USensorReceiverComponent>(
					ActorToActivate->GetComponentByClass(USensorReceiverComponent::StaticClass())))
				{
					//UE_LOG(LogTemp, Warning, TEXT("Object Found"));
					SensorReceiverComponent->SignalReceived.Broadcast();
				}
			}
		}
	}
}