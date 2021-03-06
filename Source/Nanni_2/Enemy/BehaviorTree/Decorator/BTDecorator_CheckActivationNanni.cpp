// Copyright © 2022 Last Second


#include "BTDecorator_CheckActivationNanni.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckActivationNanni::UBTDecorator_CheckActivationNanni() {

	NodeName = TEXT("Check Nanni Activation");

}

bool UBTDecorator_CheckActivationNanni::PerformConditionCheckAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		return false;
	}
	
	bool FinalBool;
	
	const bool IsBOTActive = OwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsBotActive.SelectedKeyName);
	const bool IsNanniActive = OwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsDetected.SelectedKeyName);
	const FVector PlayerLocation = OwnerController->GetBlackboardComponent()->GetValueAsVector(BBPlayerLocation.SelectedKeyName);
	const float AgeStimulus = OwnerController->GetBlackboardComponent()->GetValueAsFloat(BBStimulusAge.SelectedKeyName);
	
	if(IsBOTActive || (PlayerLocation.X != 0.0f && PlayerLocation.Y != 0.0f && PlayerLocation.Z != 0.0f && AgeStimulus < 60.0f) || IsNanniActive)
	{
		FinalBool = true;
	}
	else
	{
		FinalBool = false;
	}
	
	return bCheck == FinalBool;
}