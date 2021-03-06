// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BTDecorator_CheckSpiritFreedom.generated.h"

/**
 * 
 */
UCLASS()
class NANNI_2_API UBTDecorator_CheckSpiritFreedom : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckSpiritFreedom();

	UFUNCTION(BlueprintCallable, Category = "Check AI Perception")
		bool PerformConditionCheckAIImplementation(AAIController* OwnerController, APawn* ControlledPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBIsSpiritFree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIPerception")
		bool bCheck = false;
};
