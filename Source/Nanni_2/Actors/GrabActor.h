// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "GrabActor.generated.h"

class UInteractionComponent;
UCLASS()
class NANNI_2_API AGrabActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> GrabbMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInteractionComponent> InteractionComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnImpactField(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	                      UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void GrabItem (AMainCharacter* MainCharacter);

};
