// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericButton.generated.h"

class AMainCharacter;
class UEventListenerComponent;
class UInteractionComponent;
UCLASS()
class NANNI_2_API AGenericButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenericButton();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Scene;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> OpeningMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", Instanced)
	TObjectPtr<UEventListenerComponent> EventListener; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bIsAlwaysInteractable;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void TriggerTaskCompleted(AMainCharacter* Character);
};
