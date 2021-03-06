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
	Inform();
	FinishExecute(true);
	
}

void UBTTask_InformNanni::Inform()
{
	MainCharacter = Cast<AMainCharacter>(AIOwnerController->GetBlackboardComponent()->GetValueAsObject(BBPlayerActor.SelectedKeyName));
	if(AIOwnerController->GetIslandNum() == 1 && MainCharacter)
	{
		MainCharacter->CheckNanni1 = AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsPlayerDetected.SelectedKeyName);
		MainCharacter->PlayerLocation = AIOwnerController->GetPlayerLocation();
		if (AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsPlayerDetected.SelectedKeyName))
		{
			MainCharacter->AgePlayerLocation = AIOwnerController->GetStimulusAge();
		}
	}
	else if(AIOwnerController->GetIslandNum() == 2 && MainCharacter)
	{
		MainCharacter->CheckNanni2 = AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsPlayerDetected.SelectedKeyName);
		MainCharacter->PlayerLocation = AIOwnerController->GetPlayerLocation();
		if (AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsPlayerDetected.SelectedKeyName))
		{
			MainCharacter->AgePlayerLocation = AIOwnerController->GetStimulusAge();
		}
	}
	else if(AIOwnerController->GetIslandNum() == 3 && MainCharacter)
	{
		MainCharacter->CheckNanni3 = AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsPlayerDetected.SelectedKeyName);
		MainCharacter->PlayerLocation = AIOwnerController->GetPlayerLocation();
		if (AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsPlayerDetected.SelectedKeyName))
		{
			MainCharacter->AgePlayerLocation = AIOwnerController->GetStimulusAge();
		}
	}
}
