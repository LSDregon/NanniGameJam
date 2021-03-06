// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DeathBoxVolume.generated.h"

/**
 * 
 */
UCLASS()
class NANNI_2_API ADeathBoxVolume : public ATriggerBox
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<AActor> RespawnPoint; 
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void DeathEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                bool bFromSweep, const FHitResult& SweepResult);
};
