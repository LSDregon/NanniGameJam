// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_UpdateRotation.generated.h"

class AEnemyController;
UCLASS()
class NANNI_2_API UBTTask_UpdateRotation : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_UpdateRotation();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void ReciveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaTime);

	UFUNCTION()
		void Rotate(float DeltaTime, APawn* ControlledPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	FBlackboardKeySelector BBPlayer;
	
private:

	UPROPERTY()
	AEnemyController* AIOwnerController;
	
};
