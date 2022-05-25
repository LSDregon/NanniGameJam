// Copyright © 2022 Last Second


#include "BTTask_InformNanni.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/Enemy/Bot/EnemyBotController.h"

UBTTask_InformNanni::UBTTask_InformNanni()
{
	NodeName = TEXT("Inform Nanni");
}

void UBTTask_InformNanni::ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		FinishExecute(false);
	}
	AIOwnerController = Cast<AEnemyBotController>(OwnerController);
	MainCharacter = Cast<AMainCharacter>(AIOwnerController->GetBlackboardComponent()->GetValueAsObject(BBPlayerActor.SelectedKeyName));
	if(AIOwnerController->GetIslandNum() == 1)
	{
		MainCharacter->CheckNanni1 = true;
	}
	else if(AIOwnerController->GetIslandNum() == 2)
	{
		MainCharacter->CheckNanni2 = true;
	}
	else if(AIOwnerController->GetIslandNum() == 3)
	{
		MainCharacter->CheckNanni3 = true;
	}
	FinishExecute(true);
}