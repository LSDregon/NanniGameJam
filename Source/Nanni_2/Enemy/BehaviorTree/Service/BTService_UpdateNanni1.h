// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_UpdateNanni1.generated.h"

class AEnemyNanniController;
UCLASS()
class NANNI_2_API UBTService_UpdateNanni1 : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:

	UBTService_UpdateNanni1();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	FBlackboardKeySelector BBIsBotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	FBlackboardKeySelector BBPlayerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	FBlackboardKeySelector BBStimulusAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	FBlackboardKeySelector BBIsDetected;

private:

	UPROPERTY()
	AEnemyNanniController* AIOwnerController;
	
};
