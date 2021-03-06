// Copyright © 2022 Last Second


#include "SpiritController.h"

#include "SpiritCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"

void ASpiritController::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	Spirit = Cast<ASpiritCharacter>(GetPawn());
	if (AIBhavior)
	{
		RunBehaviorTree(AIBhavior);
	}
}
