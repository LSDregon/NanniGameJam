// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "GameMenuAudioSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class NANNI_2_API UGameMenuAudioSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> GlobalProgrBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> GlobalSlider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> MusicProgrBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> MusicSlider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> EffectsProgrBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> EffectsSlider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> EnviromentProgrBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> EnviromentSlider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> DialoguesProgrBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> DialoguesSlider;
	
	UPROPERTY(BlueprintReadWrite)
	FText GlobalText;
	UPROPERTY(BlueprintReadWrite)
	FText MusicText;
	UPROPERTY(BlueprintReadWrite)
	FText EffectsText;
	UPROPERTY(BlueprintReadWrite)
	FText EnviromentText;
	UPROPERTY(BlueprintReadWrite)
	FText DialoguesText;
	
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable)
	void SetGlobalVolumeValue(FText NewVolumeValue){ GlobalText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetMusicVolumeValue(FText NewVolumeValue){ MusicText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetEffectsVolumeValue(FText NewVolumeValue){ EffectsText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetEnviromentVolumeValue(FText NewVolumeValue){ EnviromentText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetDialoguesVolumeValue(FText NewVolumeValue){ DialoguesText = NewVolumeValue; }
	
	UFUNCTION(BlueprintCallable)
	void GlobalSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void MusicSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void EffectsSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void EnviromentSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void DialoguesSliderChanged(float Value);
	
};
