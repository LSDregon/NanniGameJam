// Copyright © 2022 Last Second


#include "BTDecorator_CheckSpiritFreedom.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckSpiritFreedom::UBTDecorator_CheckSpiritFreedom()
{
	NodeName = TEXT("Check if Spirit Is Free");
}

bool UBTDecorator_CheckSpiritFreedom::PerformConditionCheckAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		return false;
	}

	return bCheck == OwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsSpiritFree.SelectedKeyName);
}
