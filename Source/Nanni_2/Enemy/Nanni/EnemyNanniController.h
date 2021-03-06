// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Nanni_2/Enemy/EnemyController.h"
#include "EnemyNanniController.generated.h"

class AMainCharacter;
UCLASS()
class NANNI_2_API AEnemyNanniController : public AEnemyController
{
	GENERATED_BODY()

public:
	AMainCharacter* GetMainCharacter() const {return MainCharacter;}
	
private:
	AMainCharacter* MainCharacter= nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
