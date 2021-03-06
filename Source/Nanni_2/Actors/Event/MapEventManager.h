// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapEventManager.generated.h"

class UEventListenerComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTaskFinished, AActor*, ActorListener, UEventListenerComponent*, ListenerComponent);

UCLASS()
class NANNI_2_API AMapEventManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapEventManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, TSoftObjectPtr<AActor>> ListenerList;

	UPROPERTY(EditAnywhere)
	FOnTaskFinished OnTaskFinished;

	UPROPERTY(VisibleAnywhere)
	int32 ActualTask;
		
	UFUNCTION(BlueprintCallable)
	void EventManager(AActor* ActorListener, UEventListenerComponent* ListenerComponent);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
