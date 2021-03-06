// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerBoxCustom.generated.h"

class UEventListenerComponent;
UCLASS()
class NANNI_2_API ATriggerBoxCustom : public AActor
{
	GENERATED_BODY()

public:

	ATriggerBoxCustom();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UEventListenerComponent> EventListener;

	UPROPERTY(EditAnywhere)
	bool bIsAlwaysInteractable;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TriggerTaskCompleted(AActor* OverlappedActor, AActor* OtherActor);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
