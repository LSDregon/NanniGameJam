// Copyright © 2022 Last Second


#include "SensorReceiverComponent.h"

// Sets default values for this component's properties
USensorReceiverComponent::USensorReceiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SignalReceived.AddDynamic(this, &USensorReceiverComponent::ActivateSomething);
	// ...
}


// Called when the game starts
void USensorReceiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USensorReceiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USensorReceiverComponent::ActivateSomething()
{
	//
	//UE_LOG(LogTemp, Warning, TEXT("Object Activated"));
}

