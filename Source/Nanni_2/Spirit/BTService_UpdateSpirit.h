// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_UpdateSpirit.generated.h"

class ASpiritController;
UCLASS()
class NANNI_2_API UBTService_UpdateSpirit : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTService_UpdateSpirit();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBIsSpiritFree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBPlayer;

private:

	UPROPERTY()
	ASpiritController* AIOwnerController;
	
};
