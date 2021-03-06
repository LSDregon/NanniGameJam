// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "FieldImpactActor.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class NANNI_2_API AFieldImpactActor : public AFieldSystemActor
{
	GENERATED_BODY()

public:

	AFieldImpactActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URadialFalloff> RadioFalloff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URadialVector> RadialVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCullingField> CullingField;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StrainMagnitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MagnitudeForce;
	
	UFUNCTION(BlueprintCallable)
	void Explode();
	
};
