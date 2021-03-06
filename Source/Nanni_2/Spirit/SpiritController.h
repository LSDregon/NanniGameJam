// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SpiritController.generated.h"

class AMainCharacter;
class ASpiritCharacter;
UCLASS()
class NANNI_2_API ASpiritController : public AAIController
{
	GENERATED_BODY()

public:

	UFUNCTION()
		AMainCharacter* GetMainCharacter() const {return MainCharacter;}
	
private:
	
	UPROPERTY(EditAnywhere, Category="AI")
		UBehaviorTree* AIBhavior;

	UPROPERTY()
		AMainCharacter* MainCharacter = nullptr;

	UPROPERTY()
		ASpiritCharacter* Spirit = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
