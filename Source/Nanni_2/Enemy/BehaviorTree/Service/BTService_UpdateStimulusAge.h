// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_UpdateStimulusAge.generated.h"

class AEnemyNanniController;
UCLASS()
class NANNI_2_API UBTService_UpdateStimulusAge : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:

	UBTService_UpdateStimulusAge();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void ReceiveTickAIImplementation(AAIController* OwnerController, APawn* ControlledPawn, float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBIsBotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBStimulusAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
		FBlackboardKeySelector BBPlayer;

private:

	UPROPERTY()
		AEnemyNanniController* AIOwnerController;
	
};
