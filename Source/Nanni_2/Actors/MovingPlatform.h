// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Nanni_2/Miscellaneous/TriggerBoxCustom.h"
#include "MovingPlatform.generated.h"

class AMainCharacter;
UCLASS()
class NANNI_2_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> PlatformMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ATriggerBoxCustom> Trigger;
	
	UPROPERTY(EditAnywhere)
	bool IsDown;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> DownCurve;
	
	UPROPERTY(VisibleAnywhere)
	float InitialZValue;
	
	UPROPERTY(VisibleAnywhere)
	float DownValue;
	UPROPERTY(VisibleAnywhere)
	float CurveFloatValue;
	UPROPERTY(VisibleAnywhere)
	float TimelineValue;
	UPROPERTY(VisibleAnywhere)
	FVector PlatformPosition;
	UPROPERTY(VisibleAnywhere)
	FTimeline MyTimeline;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ControlMovement();
	
	UFUNCTION(BlueprintCallable)
	void SetState();
	
	UFUNCTION(BlueprintCallable)
	void StopMoving(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION(BlueprintCallable)
	void MovingOperation(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySound();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StopSound();

	UFUNCTION(BlueprintCallable)
	void StartPlaySound(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION(BlueprintCallable)
	void StopPlaySound(AActor* OverlappedActor, AActor* OtherActor);
	
private:
	
	UPROPERTY()
	bool ReadyState;
};
