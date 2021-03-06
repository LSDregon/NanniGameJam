// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SensorComponent.generated.h"

class UEventListenerComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLaserDetected);
/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NANNI_2_API USensorComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	USensorComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnLaserDetected LaserDetected;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<AActor>> ActorToActivateList;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UEventListenerComponent> EventListener;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bIsAlwaysActive;

public:
	
	UFUNCTION(BlueprintCallable)
	void SensorActivated();

	UFUNCTION(BlueprintCallable)
	void SetEventListener(UEventListenerComponent* NewEventListener);
	
	UFUNCTION(BlueprintCallable)
	void CallSensorReceivers();
	
	UFUNCTION(BlueprintCallable)
	void TriggerTaskCompleted();
};
