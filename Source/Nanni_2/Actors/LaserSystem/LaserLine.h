// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "LaserLine.generated.h"

UCLASS()
class NANNI_2_API ALaserLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserLine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> Scene;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UNiagaraComponent> NiagaraLaser;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UNiagaraComponent> NiagaraLaserImpact;

	UFUNCTION()
	void SetColorLaser(FColor Color) const;
	UFUNCTION()
	void SetColorLaserImpact(FColor Color) const;
	UFUNCTION()
	void SetLaser(FVector EndVector) const;
	UFUNCTION()
	void SetLaserImpact(FVector EndVector) const;
	
	UFUNCTION()
	void SetActiveStateLaser(bool IsActive) const;
	UFUNCTION()
	void SetActiveStateLaserImpact(bool IsActive) const;

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySound();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
