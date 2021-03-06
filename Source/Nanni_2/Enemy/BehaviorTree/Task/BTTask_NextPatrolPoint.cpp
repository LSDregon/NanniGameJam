// Copyright © 2022 Last Second


#include "BTTask_NextPatrolPoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Nanni_2/Actors/AIPath/AIPath.h"
#include "Nanni_2/Enemy/Bot/EnemyBotController.h"
#include "Containers/Array.h"

UBTTask_NextPatrolPoint::UBTTask_NextPatrolPoint()
{
	NodeName = TEXT("Next Patrol Point");
}

void UBTTask_NextPatrolPoint::ReceiveExecuteAIImplementation(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (!OwnerController)
	{
		FinishExecute(false);
	}
	AIOwnerController = Cast<AEnemyBotController>(OwnerController);
	NextPatrolPoint();
	FinishExecute(true);
}

void UBTTask_NextPatrolPoint::NextPatrolPoint() const
{
	const int32 Index = AIOwnerController->GetBlackboardComponent()->GetValueAsInt(BBIndexPatrolPoint.SelectedKeyName);
	AIOwnerController->GetBlackboardComponent()->SetValueAsVector(BBStartLocationAI.SelectedKeyName, AIOwnerController->GetPawn()->GetActorLocation());

	if(AIOwnerController->AIPath)
	{
		AIOwnerController->GetBlackboardComponent()->SetValueAsVector(BBNextPatrolPoint.SelectedKeyName, AIOwnerController->AIPath->Spline[Index]);
	}

	if(AIOwnerController->AIPath)
	{
		if(Index == AIOwnerController->AIPath->Spline.Num() - 1)
		{
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIndexCheck.SelectedKeyName, true);
		}
		else if(Index == 0)
		{
			AIOwnerController->GetBlackboardComponent()->SetValueAsBool(BBIndexCheck.SelectedKeyName, false);
		}
	}
	
	if(AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIndexCheck.SelectedKeyName))
	{
		AIOwnerController->GetBlackboardComponent()->SetValueAsInt(BBIndexPatrolPoint.SelectedKeyName, Index - 1);
	}
	else if (!AIOwnerController->GetBlackboardComponent()->GetValueAsBool(BBIndexCheck.SelectedKeyName))
	{
		AIOwnerController->GetBlackboardComponent()->SetValueAsInt(BBIndexPatrolPoint.SelectedKeyName, Index + 1);
	}
}
