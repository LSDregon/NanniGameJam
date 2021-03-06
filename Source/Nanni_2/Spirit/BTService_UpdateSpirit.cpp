// Copyright © 2022 Last Second


#include "BTService_UpdateSpirit.h"

#include "SpiritController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"

UBTService_UpdateSpirit::UBTService_UpdateSpirit()
{
	NodeName = TEXT("Update Spirit");
}

void UBTService_UpdateSpirit::ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		ReceiveDeactivation(ControlledPawn);
		return;
	}
	AIOwnerController = Cast<ASpiritController>(OwnerController);

	if(AIOwnerController)
	{
		AIOwnerController->GetBlackboardComponent()->SetValueAsObject(BBPlayer.SelectedKeyName, AIOwnerController->GetMainCharacter());
		AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsSpiritFree.SelectedKeyName, AIOwnerController->GetMainCharacter()->IsSpiritFree);
	}
}
