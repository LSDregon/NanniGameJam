// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "SpiritCharacter.generated.h"

UCLASS()
class NANNI_2_API ASpiritCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpiritCharacter();

		//Team Interface
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
		int32 ID = 0;

	virtual FGenericTeamId GetGenericTeamId() const {return TeamId;}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FGenericTeamId TeamId;

};
