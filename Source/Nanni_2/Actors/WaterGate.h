// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "WaterGate.generated.h"

class UMaterialInstance;
class ATriggerBoxCustom;
UCLASS()
class NANNI_2_API AWaterGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterGate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Scene;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Scene2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> GateMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<ATriggerBoxCustom> DependentTrigger;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* WaterMaterialInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUpDownMovement;
	
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
	void MovingOperation(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION(BlueprintCallable)
	void ShowWater(AActor* OverlappedActor, AActor* OtherActor);

private:
	
	UPROPERTY()
	bool ReadyState;
};

