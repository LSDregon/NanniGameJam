// Copyright © 2022 Last Second


#include "BTDecorator_CheckSpiritFreedom.h"

#include "AIController.h"
#include "SpiritController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"

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

	const ASpiritController* AIOwnerController = Cast<ASpiritController>(OwnerController);
	if (!AIOwnerController)
	{
		return false;
	}
	return bCheck == AIOwnerController->GetMainCharacter()->IsSpiritFree;
}
