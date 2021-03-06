// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SensorReceiverComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSignalReceived);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NANNI_2_API USensorReceiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USensorReceiverComponent();

	UPROPERTY(BlueprintAssignable)
	FOnSignalReceived SignalReceived;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void ActivateSomething();
		
};
