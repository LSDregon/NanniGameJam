// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuAudioSettingsWidget.generated.h"

class USaveGameInformations;
class USlider;
class UProgressBar;
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
	TObjectPtr<UProgressBar> EnvironmentProgrBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> EnvironmentSlider;
	
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
	FText EnvironmentText;
	UPROPERTY(BlueprintReadWrite)
	FText DialoguesText;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USaveGameInformations> SavedGame;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundMix> MasterSoundMix;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundClass> GlobalSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundClass> MusicSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundClass> EffectsSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundClass> EnvironmentSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundClass> DialoguesSoundClass;
	
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void FadeInAnimationExec();
	UFUNCTION(BlueprintImplementableEvent)
	void FadeOutAnimationExec();
	
	UFUNCTION(BlueprintCallable)
	bool InitializeValuesFromSave();
	UFUNCTION(BlueprintCallable)
	bool SaveAudioInfos();
	
	UFUNCTION(BlueprintCallable)
	void SetGlobalVolumeValue(const FText NewVolumeValue){ GlobalText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetMusicVolumeValue(const FText NewVolumeValue){ MusicText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetEffectsVolumeValue(const FText NewVolumeValue){ EffectsText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetEnvironmentVolumeValue(const FText NewVolumeValue){ EnvironmentText = NewVolumeValue; }
	UFUNCTION(BlueprintCallable)
	void SetDialoguesVolumeValue(const FText NewVolumeValue){ DialoguesText = NewVolumeValue; }
	
	UFUNCTION(BlueprintCallable)
	void GlobalSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void MusicSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void EffectsSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void EnvironmentSliderChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void DialoguesSliderChanged(float Value);
	
};
