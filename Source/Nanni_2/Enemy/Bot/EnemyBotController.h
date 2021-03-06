// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Nanni_2/Enemy/EnemyController.h"
#include "EnemyBotController.generated.h"

class AAIPath;
UCLASS()
class NANNI_2_API AEnemyBotController : public AEnemyController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
		TSoftObjectPtr<AAIPath> AIPath;
	
};
