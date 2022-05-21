// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Nanni_2/GeneralComponents/InteractionComponent.h"
#include "OpeningActor.generated.h"

class AMainCharacter;
class UInteractionComponent;
UCLASS()
class NANNI_2_API AOpeningActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpeningActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* OpeningMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UInteractionComponent* InteractionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool OpenFront;
	
	UPROPERTY(EditAnywhere)
	bool IsClosed;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat *DoorCurve;
	
	UPROPERTY()
	float DotProductOnInteraction;
	UPROPERTY()
	float RotateValue;
	UPROPERTY()
	float CurveFloatValue;
	UPROPERTY()
	float TimelineValue;
	UPROPERTY()
	FRotator DoorRotation;
	UPROPERTY()
	FTimeline MyTimeline;
	
	UFUNCTION()
	void ControlRotation();
	
	UFUNCTION()
	float GetDotProduct() const;
	
	UFUNCTION()
	void SetState();
	
	UFUNCTION(BlueprintCallable)
	void OpeningOperation(AMainCharacter* MainCharacter);
	
	UFUNCTION(BlueprintCallable)
	void StopOpening(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

protected:

	UPROPERTY()
	AMainCharacter* MainCharacter;

private:
	
	UPROPERTY()
	bool ReadyState;
};
