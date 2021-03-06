// Copyright © 2022 Last Second


#include "BTService_UpdateAIPerception.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Nanni_2/Enemy/EnemyController.h"

UBTService_UpdateAIPerception::UBTService_UpdateAIPerception() 
{
	NodeName = TEXT("Get AI Active Perception");
}

void UBTService_UpdateAIPerception::ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		ReceiveDeactivation(ControlledPawn);
		return;
	}
	AIOwnerController = Cast<AEnemyController>(OwnerController);
	GetActiveSenses();
}

void UBTService_UpdateAIPerception::GetActiveSenses() const
{
	const FVector PlayerLocation = AIOwnerController->GetPlayerLocation();
	AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIsDetected.SelectedKeyName, AIOwnerController->GetIsDetected());
	AIOwnerController->GetBlackboardComponent()->SetValueAsVector(BBPlayerLocation.SelectedKeyName, PlayerLocation);
	AIOwnerController->GetBlackboardComponent()->SetValueAsRotator(BBPlayerRotator.SelectedKeyName, AIOwnerController->GetPlayerRotation());
	AIOwnerController->GetBlackboardComponent()->SetValueAsObject(BBPlayerActor.SelectedKeyName, AIOwnerController->GetPlayer());
	//bool IsDetected = AIOwnerController->GetIsDetected();
}