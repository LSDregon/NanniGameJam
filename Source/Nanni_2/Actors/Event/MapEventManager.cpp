// Copyright © 2022 Last Second


#include "MapEventManager.h"

#include "Kismet/KismetStringLibrary.h"
#include "Nanni_2/GeneralComponents/EventListenerComponent.h"
#include "Nanni_2/GeneralComponents/SensorComponent.h"

// Sets default values
AMapEventManager::AMapEventManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActualTask = 1;
}

// Called when the game starts or when spawned
void AMapEventManager::BeginPlay()
{
	Super::BeginPlay();
	
	OnTaskFinished.AddDynamic(this, &AMapEventManager::EventManager);

	for (const TTuple<int32, TSoftObjectPtr<AActor>> ActorTask : ListenerList)
	{
		if (ActorTask.Value)
		{
			if (UEventListenerComponent* EventListenerComponent = Cast<UEventListenerComponent>(
				ActorTask.Value->GetComponentByClass(UEventListenerComponent::StaticClass())))
			{
				EventListenerComponent->EventManager = this;
				EventListenerComponent->bIsInAEventTask = true;
				EventListenerComponent->PositionInTaskList = ActorTask.Key;
				if (ActorTask.Key == 1)
				{
					EventListenerComponent->bIsActorEnable = true;
				}
				if (USensorComponent* SensorComponent = Cast<USensorComponent>(
					ActorTask.Value->GetComponentByClass(USensorComponent::StaticClass())))
				{
					SensorComponent->SetEventListener(EventListenerComponent);
				}
			} else if (USensorComponent* SensorComponent = Cast<USensorComponent>(
					ActorTask.Value->GetComponentByClass(USensorComponent::StaticClass())))
			{
				SensorComponent->SetEventListener(NewObject<UEventListenerComponent>());
				SensorComponent->EventListener->EventManager = this;
				SensorComponent->EventListener->SetIsInAEventTask(true);
				SensorComponent->EventListener->PositionInTaskList = ActorTask.Key;
				if (ActorTask.Key == 1)
				{
					SensorComponent->EventListener->bIsActorEnable = true;
				}
			}
		}
	}
}

// Called every frame
void AMapEventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMapEventManager::EventManager(AActor* ActorListener, UEventListenerComponent* EventListenerComponent)
{
	//UE_LOG(LogTemp, Warning, TEXT("EventManager"));
	//UE_LOG(LogTemp, Warning, TEXT("ActualTask: %d"), ActualTask);
	ActualTask++;
	//UE_LOG(LogTemp, Warning, TEXT("ActualTask: %d"), ActualTask);
	if (ListenerList.Contains(ActualTask))
	{
		if (const AActor* NextActor = ListenerList.Find(ActualTask)->Get())
		{
			//UE_LOG(LogTemp, Warning, TEXT("NextActor"));
			if(Cast<UEventListenerComponent>(NextActor->GetComponentByClass(UEventListenerComponent::StaticClass())))
			{
				//UE_LOG(LogTemp, Warning, TEXT("EventListenerComponent"));
				Cast<UEventListenerComponent>(NextActor->GetComponentByClass(UEventListenerComponent::StaticClass()))->SetIsActorEnable(true);
			} else if (const USensorComponent* SensorComponent = Cast<USensorComponent>(
					NextActor->GetComponentByClass(USensorComponent::StaticClass())))
			{
				//UE_LOG(LogTemp, Warning, TEXT("SensorComponent"));
				SensorComponent->EventListener->SetIsActorEnable(true);
			}
		}
	}
}

