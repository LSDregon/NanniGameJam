// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractionComponent.generated.h"

class AMainCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginInteract, AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndInteract, AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, AMainCharacter*, Character);

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NANNI_2_API UInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public :
	UInteractionComponent();

	//How much time is needed to take the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionTime;

	//From how far the player can interact with the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	float InteractionDistance;

	//Name of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionObjectName;

	//Action of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionObjectAction;

	UFUNCTION(BluePrintCallable, Category = "Interaction")
	void SetInteractableNameText(const FText& NewNameText);

	UFUNCTION(BluePrintCallable, Category = "Interaction")
	void SetInteractableActionText(const FText& NewActionText);

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginInteract OnBeginInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndInteract OnEndInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginFocus OnBeginFocus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndFocus OnEndFocus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnInteract OnInteract;

	UPROPERTY()
	bool IsInteractionActive;
	
	//called when the player trace hit the object
	UFUNCTION()
	void BeginFocus(AMainCharacter* Character);
	UFUNCTION()
	void EndFocus(AMainCharacter* Character);

	//called when the player start/end to interact with the object
	UFUNCTION()
	void BeginInteract(AMainCharacter* Character);
	UFUNCTION()
	void EndInteract(AMainCharacter* Character);

	UFUNCTION()
	void Interact(AMainCharacter* Character) const;

	//how far we are to complete the interaction, will return a value from 0 to 1
	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetInteractPercentage() const;

	UFUNCTION()
	void RefreshWidget();

	UPROPERTY()
	TObjectPtr<AMainCharacter> Interactor = nullptr;

protected:
	
	virtual void Deactivate() override;

};
