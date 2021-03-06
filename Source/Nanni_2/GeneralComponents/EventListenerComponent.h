// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Nanni_2/Actors/Event/MapEventManager.h"
#include "EventListenerComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NANNI_2_API UEventListenerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEventListenerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AMapEventManager> EventManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PositionInTaskList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInAEventTask;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActorEnable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTaskDone;

	UFUNCTION(BlueprintCallable)
	void TaskCompleted(AActor* ActorListener);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	bool IsIsInAEventTask() const{return bIsInAEventTask;}
	UFUNCTION(BlueprintCallable)
	void SetIsInAEventTask(bool NewValue){this->bIsInAEventTask = NewValue;}
	UFUNCTION(BlueprintCallable)
	bool IsIsActorEnable() const {return bIsActorEnable;}
	UFUNCTION(BlueprintCallable)
	void SetIsActorEnable(bool NewValue){this->bIsActorEnable = NewValue;}
	UFUNCTION(BlueprintCallable)
	bool IsIsTaskDone() const{return bIsTaskDone;}
	UFUNCTION(BlueprintCallable)
	void SetIsTaskDone(bool NewValue){this->bIsTaskDone = NewValue;}
};
