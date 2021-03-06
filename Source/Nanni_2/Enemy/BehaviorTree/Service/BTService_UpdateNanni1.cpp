// Copyright © 2022 Last Second


#include "BTService_UpdateNanni1.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/Enemy/Nanni/EnemyNanniController.h"

UBTService_UpdateNanni1::UBTService_UpdateNanni1() 
{
	NodeName = TEXT("Update Nanni Activation");
}

void UBTService_UpdateNanni1::ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		ReceiveDeactivation(ControlledPawn);
		return;
	}
	AIOwnerController = Cast<AEnemyNanniController>(OwnerController);
	if(AIOwnerController->GetMainCharacter())
	{
		
		if(AIOwnerController->GetIslandNum() == 1)
		{
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsBotActive.SelectedKeyName, AIOwnerController->GetMainCharacter()->CheckNanni1);
			AIOwnerController->GetBlackboardComponent()->SetValueAsVector(BBPlayerLocation.SelectedKeyName, AIOwnerController->GetMainCharacter()->PlayerLocation);
			AIOwnerController->GetBlackboardComponent()->SetValueAsFloat(BBStimulusAge.SelectedKeyName, AIOwnerController->GetMainCharacter()->AgePlayerLocation);
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsDetected.SelectedKeyName, AIOwnerController->GetIsDetected());
		}
		else if(AIOwnerController->GetIslandNum() == 2)
		{
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsBotActive.SelectedKeyName,AIOwnerController->GetMainCharacter()->CheckNanni2);
			AIOwnerController->GetBlackboardComponent()->SetValueAsVector(BBPlayerLocation.SelectedKeyName, AIOwnerController->GetMainCharacter()->PlayerLocation);
			AIOwnerController->GetBlackboardComponent()->SetValueAsFloat(BBStimulusAge.SelectedKeyName, AIOwnerController->GetMainCharacter()->AgePlayerLocation);
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsDetected.SelectedKeyName, AIOwnerController->GetIsDetected());
		}
		else if(AIOwnerController->GetIslandNum() == 3)
		{
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsBotActive.SelectedKeyName,AIOwnerController->GetMainCharacter()->CheckNanni3);
			AIOwnerController->GetBlackboardComponent()->SetValueAsVector(BBPlayerLocation.SelectedKeyName, AIOwnerController->GetMainCharacter()->PlayerLocation);
			AIOwnerController->GetBlackboardComponent()->SetValueAsFloat(BBStimulusAge.SelectedKeyName, AIOwnerController->GetMainCharacter()->AgePlayerLocation);
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsDetected.SelectedKeyName, AIOwnerController->GetIsDetected());
		}
	}
}