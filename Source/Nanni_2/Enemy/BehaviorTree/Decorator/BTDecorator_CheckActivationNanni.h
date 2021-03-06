// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BTDecorator_CheckActivationNanni.generated.h"

/**
 * 
 */
UCLASS()
class NANNI_2_API UBTDecorator_CheckActivationNanni : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()

public:

	UBTDecorator_CheckActivationNanni();

	UFUNCTION(BlueprintCallable, Category = "Check AI Perception")
		bool PerformConditionCheckAIImplementation(AAIController* OwnerController, APawn* ControlledPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIPerception")
		FBlackboardKeySelector BBIsBotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIPerception")
		FBlackboardKeySelector BBPlayerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIPerception")
		FBlackboardKeySelector BBStimulusAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIPerception")
		FBlackboardKeySelector BBIsDetected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIPerception")
		bool bCheck = false;
	
};
