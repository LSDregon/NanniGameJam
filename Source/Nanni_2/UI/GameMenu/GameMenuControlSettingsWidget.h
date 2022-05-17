// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuControlSettingsWidget.generated.h"

class USlider;
class UProgressBar;
/**
 * 
 */
UCLASS()
class NANNI_2_API UGameMenuControlSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> SensibilityProgrBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> SensibilitySlider;
	
	UPROPERTY(BlueprintReadWrite)
	FText SensibilityText;
	
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void FadeInAnimationExec();
	UFUNCTION(BlueprintImplementableEvent)
	void FadeOutAnimationExec();
	/*
	UFUNCTION(BlueprintCallable)
	bool InitializeValuesFromSave();
	*/
	UFUNCTION(BlueprintCallable)
	void SetSensibilityVolumeValue(const FText NewVolumeValue){ SensibilityText = NewVolumeValue; }
	
	UFUNCTION(BlueprintCallable)
	void SensibilitySliderChanged(float Value);
};
