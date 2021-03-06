// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_NextPatrolPoint.generated.h"

class AEnemyBotController;
UCLASS()
class NANNI_2_API UBTTask_NextPatrolPoint : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_NextPatrolPoint();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBNextPatrolPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBIndexPatrolPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBStartLocationAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBIndexCheck;
	
	UFUNCTION()
		void NextPatrolPoint() const;
	
private:

	UPROPERTY()
		AEnemyBotController* AIOwnerController;
};
