// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAIPerceptionStimuliSourceComponent;
UCLASS()
class NANNI_2_API AMainCharacter : public ACharacter
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
		USpringArmComponent* SpringArm;
	
	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComponent;
	
	//Noise Emitter
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UAIPerceptionStimuliSourceComponent* PerceptionEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MouseSensitivity = 0.5f;
	
	UFUNCTION()
		float GetMouseSensitivity() const {return MouseSensitivity;}

	UFUNCTION()
		void SetMouseSensitivity(float Value) {this->MouseSensitivity = Value;}


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
	
};
