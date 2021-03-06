// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class ATriggerArea;
UCLASS()
class NANNI_2_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshPressure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> ActivatedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActivatedMaterialIndex;
	
	UFUNCTION(BlueprintCallable)
	void ActionToExecute(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySound();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
