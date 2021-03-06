// Copyright © 2022 Last Second


#include "EnemyController.h"

#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	AIPerception = FindComponentByClass<UAIPerceptionComponent>();

	if (AIPerception)
	{
		SetPerceptionComponent(*AIPerception);
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnPawnDetected);
	}

	AICharacter = Cast<AEnemyCharacter>(GetPawn());
	if (AIBhavior)
	{
		RunBehaviorTree(AIBhavior);

		//to be checked why it does not work with standalone game
		//const APawn* AIPawn = GetPawn();
		if(AICharacter)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocationAI"), AICharacter->GetActorLocation());
		}
	}

	if(AICharacter)
	{
		TeamId = FGenericTeamId(AICharacter->ID);
	}
	
}

ETeamAttitude::Type AEnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (!OtherPawn)
	{
		return  ETeamAttitude::Neutral;
	}

	const auto PlayerTI = Cast<IGenericTeamAgentInterface>(&Other);
	const class IGenericTeamAgentInterface* BotTi = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if(BotTi && PlayerTI)
	{
		return  ETeamAttitude::Neutral;
	}

	FGenericTeamId OtherActorTeamID = NULL;
	if(BotTi)
	{
		OtherActorTeamID = BotTi->GetGenericTeamId();
	}
	else if (PlayerTI)
	{
		OtherActorTeamID = PlayerTI->GetGenericTeamId();
	}

	FGenericTeamId ThisId = GetGenericTeamId();
	if (OtherActorTeamID == 8)
	{
		return  ETeamAttitude::Neutral;
	}
	else if (OtherActorTeamID == ThisId)
	{
		return  ETeamAttitude::Friendly;
	}
	else
	{
		return  ETeamAttitude::Hostile;
	}
}

void AEnemyController::OnPawnDetected(AActor* Actor, FAIStimulus Stimulus)
{
	IsDetected = Stimulus.WasSuccessfullySensed();
	PlayerLocation = Stimulus.StimulusLocation;
	Player = Actor;

	StimulusAge = Stimulus.GetAge();
}

UBehaviorTree* AEnemyController::GetBehaviorTree() const
{
	if (AIBhavior)
	{
		return AIBhavior;
	}
	return nullptr;
}