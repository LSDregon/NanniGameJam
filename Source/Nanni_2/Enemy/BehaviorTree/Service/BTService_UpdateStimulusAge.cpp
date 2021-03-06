// Copyright © 2022 Last Second


#include "BTService_UpdateStimulusAge.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/Enemy/Nanni/EnemyNanniController.h"

UBTService_UpdateStimulusAge::UBTService_UpdateStimulusAge() 
{
	NodeName = TEXT("Update Nanni Activation");
}

void UBTService_UpdateStimulusAge::ReceiveTickAIImplementation(AAIController* OwnerController, APawn* ControlledPawn, float DeltaTime)
{
	if (!OwnerController)
	{
		ReceiveDeactivation(ControlledPawn);
		return;
	}
	AIOwnerController = Cast<AEnemyNanniController>(OwnerController);

	float UpdatedAge = AIOwnerController->GetBlackboardComponent()->GetValueAsFloat(BBStimulusAge.SelectedKeyName);
	
	if(AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIsBotActive.SelectedKeyName) || UpdatedAge < 60.0f)
	{
		UpdatedAge = UpdatedAge + DeltaTime;
		AIOwnerController->GetBlackboardComponent()->SetValueAsFloat(BBStimulusAge.SelectedKeyName, UpdatedAge);
		AIOwnerController->GetBlackboardComponent()->SetValueAsObject(BBPlayer.SelectedKeyName, AIOwnerController->GetMainCharacter());
	}
	else
	{
		AIOwnerController->GetBlackboardComponent()->SetValueAsFloat(BBStimulusAge.SelectedKeyName, 61.0f);
		AIOwnerController->GetBlackboardComponent()->SetValueAsObject(BBPlayer.SelectedKeyName, nullptr);
	}
}