// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slate/SlateBrushAsset.h"
#include "InteractionWidget.generated.h"

class UInteractionComponent;
/**
 * 
 */
UCLASS( ClassGroup=(Custom))
class NANNI_2_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> CircularMaterialInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstanceDynamic> CircularMaterialInstanceDynamicInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FSlateBrush CircularBrash;
	
	UPROPERTY(BlueprintReadOnly, Category = "Interaction", meta = (ExposeOnSpawn))
	TObjectPtr<UInteractionComponent> OwningInteractionComponent;
	
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void UpdateInteractionWidget(UInteractionComponent* InteractionComponent);

	
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateInteractionWidget();

	UFUNCTION(BlueprintCallable)
	float GetInteractPercent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FSlateBrush GetDynamicBrush();
};