// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "MainCharacter.generated.h"

class AGrabActor;
class USpringArmComponent;
class UCameraComponent;
class UAIPerceptionStimuliSourceComponent;

USTRUCT()
struct FInteractionData
{

	GENERATED_BODY()

	FInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0.f;
		bInteractHelf = false;
	}

	//Component for interaction
	UPROPERTY()
	class UInteractionComponent* ViewedInteractionComponent;

	//last time we check for an interactable
	UPROPERTY()
	float LastInteractionCheckTime;

	//if player is holding the action
	UPROPERTY()
	bool bInteractHelf;
	//test
};

UCLASS()
class NANNI_2_API AMainCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Spring Arm for Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;
	
	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RespawnPoint;
	//Grabbed Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> GrabbedMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> ThrowDirection;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AGrabActor> GrabbedActorRef;

	//Perception Emitter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionStimuliSourceComponent* PerceptionEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThrowingVelocity;

	bool HasSomthingToThrow;
	//if we are interacting with an item that has an interaction time
	UFUNCTION()
	bool IsInteracting() const;

	//get the time until we interact with the current interactable
	UFUNCTION()
	float GetRemainingInteractTime() const;

	//Team Interface
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
		int32 ID = 0;

	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MouseSensitivity = 0.5f;
	
	UFUNCTION()
		float GetMouseSensitivity() const {return MouseSensitivity;}

	UFUNCTION()
		void SetMouseSensitivity(float Value) {this->MouseSensitivity = Value;}

	//Variables to pass from BOT to NANNI
	bool CheckNanni1;
	bool CheckNanni2;
	bool CheckNanni3;
	FVector PlayerLocation;
	float AgePlayerLocation;
	//

	//Variables for Spirit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSpiritFree = false;
	//


private:
	//Base Movement Functions
	UFUNCTION()
		void MoveForeward(float AxisValue);
	UFUNCTION()
		void MoveRight(float AxisValue);
	UFUNCTION()
		void TurnUp(float AxisValue);
	UFUNCTION()
		void TurnRight(float AxisValue);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//How often we have to check if there is a interactable object in our range
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckFrequency;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckDistance;

	//check if there is an interactable object
	UFUNCTION()
	void PerformInteractionCheck();

	UFUNCTION()
	void CouldntFindInteractable();
	UFUNCTION()
	void FounddNewInteractable(UInteractionComponent* Interactable);

	//Start End Interaction checks
	UFUNCTION()
	void BeginInteract();
	UFUNCTION()
	void EndInteract();

	UFUNCTION()
	void Interact();
	
	UFUNCTION()
	void ThrowItem();
	
	//All the information for see the player interaction state
	UPROPERTY()
	FInteractionData InteractionData;

	//Helper function to make grabbing interactable faster
	FORCEINLINE UInteractionComponent* GetInteractable() const { return InteractionData.ViewedInteractionComponent; }

	FTimerHandle TimerHandle_Interact;

	FGenericTeamId TeamId;

};
