// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_UpdateAIPerception.generated.h"

class AEnemyController;
UCLASS()
class NANNI_2_API UBTService_UpdateAIPerception : public UBTService_BlueprintBase
{
	GENERATED_BODY()
public:

	UBTService_UpdateAIPerception();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn);

	UFUNCTION()
		void GetActiveSenses() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBIsDetected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBPlayerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBPlayerRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBPlayerActor;

private:

	UPROPERTY()
	AEnemyController* AIOwnerController;
};
