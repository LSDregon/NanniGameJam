// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

#include "EnemyController.generated.h"

class UAIPerceptionComponent;
class AEnemyCharacter;
UCLASS()
class NANNI_2_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	//AI Perception
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		UAIPerceptionComponent* AIPerception;

	UFUNCTION()
		UBehaviorTree* GetBehaviorTree() const;

	UFUNCTION()
		void OnPawnDetected(AActor* Actor, FAIStimulus Stimulus);

	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;}

	//Get Stimulus informations
	UFUNCTION()
		bool GetIsDetected() const {return IsDetected;}

	UFUNCTION()
		FVector GetPlayerLocation() const {return PlayerLocation;}

	UFUNCTION()
		FRotator GetPlayerRotation() const {return PlayerRotation;}

	UFUNCTION()
		AActor* GetPlayer() const {return Player;}

	UFUNCTION()
		float GetStimulusAge() const {return StimulusAge;}

private:
	UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBhavior;

	UPROPERTY()
		bool IsDetected = false;

	UPROPERTY()
		FVector PlayerLocation;

	UPROPERTY()
		FRotator PlayerRotation;

	UPROPERTY()
		AActor* Player;
	
	UPROPERTY()
		float StimulusAge;

	UPROPERTY()
		const AEnemyCharacter* AICharacter;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FGenericTeamId TeamId;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
};
