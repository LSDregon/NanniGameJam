// Copyright © 2022 Last Second


#include "BTTask_UpdateRotation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Nanni_2/Enemy/EnemyController.h"

UBTTask_UpdateRotation::UBTTask_UpdateRotation()
{
	NodeName = TEXT("Rotate to Player");
}
void UBTTask_UpdateRotation::ReciveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaTime)
{
	if (!OwnerController)
	{
		FinishExecute(false);
	}
	AIOwnerController = Cast<AEnemyController>(OwnerController);
	Rotate(DeltaTime, ControlledPawn);
	FinishExecute(true);
}

void UBTTask_UpdateRotation::Rotate(float DeltaTime, APawn* ControlledPawn)
{
	AActor* Player = Cast<AActor>(AIOwnerController->GetBlackboardComponent()->GetValueAsObject(BBPlayer.SelectedKeyName));
	const float Yaw = UKismetMathLibrary::FindLookAtRotation(AIOwnerController->GetPawn()->GetActorLocation(), Player->GetActorLocation()).Yaw;
	FRotator PlayerRotation;
	PlayerRotation.Yaw = Yaw;
	PlayerRotation.Pitch = 0.0f;
	PlayerRotation.Roll = 0.0f;

	PlayerRotation.Roll = PlayerRotation.Roll * DeltaTime;
	PlayerRotation.Pitch = PlayerRotation.Pitch * DeltaTime;
	PlayerRotation.Yaw = PlayerRotation.Yaw * DeltaTime;
	
	ControlledPawn->SetActorRotation(PlayerRotation);
}