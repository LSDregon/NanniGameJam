// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_InformNanni.generated.h"

class AEnemyBotController;
class AMainCharacter;
UCLASS()
class NANNI_2_API UBTTask_InformNanni : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_InformNanni();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBPlayerActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBIsPlayerDetected;

	UFUNCTION()
		void Inform();
	
private:

	UPROPERTY()
		AEnemyBotController* AIOwnerController;

	UPROPERTY()
		AMainCharacter* MainCharacter;
	
};
