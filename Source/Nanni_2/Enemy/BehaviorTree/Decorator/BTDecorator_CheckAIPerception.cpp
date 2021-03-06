// Copyright © 2022 Last Second


#include "BTDecorator_CheckAIPerception.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckAIPerception::UBTDecorator_CheckAIPerception() {

	NodeName = TEXT("Check AI Perception");

}

bool UBTDecorator_CheckAIPerception::PerformConditionCheckAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		return false;
	}
	return bCheck == OwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsAIPerceptionActive.SelectedKeyName);
}