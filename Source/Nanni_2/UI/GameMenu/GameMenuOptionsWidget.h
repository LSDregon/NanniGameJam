// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuOptionsWidget.generated.h"

class UButton;
class UGameMenuGameSettingsWidget;
class UGameMenuControlSettingsWidget;
class UGameMenuAudioSettingsWidget;
class UGameMenuVideoSettingsWidget;
/**
 * 
 */
UCLASS()
class NANNI_2_API UGameMenuOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<UButton> GameSettingsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> VideoSettingsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AudioSettingsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ControlSettingsButton;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameMenuGameSettingsWidget> GameSettings;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameMenuVideoSettingsWidget> VideoSettings;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameMenuAudioSettingsWidget> AudioSettings;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameMenuControlSettingsWidget> ControlSettings;
	
	virtual bool Initialize() override;

	UFUNCTION(BlueprintImplementableEvent)
	void FadeInAnimationExec();
	UFUNCTION(BlueprintImplementableEvent)
	void FadeOutAnimationExec();
	
	UFUNCTION(BlueprintCallable)
	void GameSettingsSelected();
	UFUNCTION(BlueprintCallable)
	void VideoSettingsSelected();
	UFUNCTION(BlueprintCallable)
	void AudioSettingsSelected();
	UFUNCTION(BlueprintCallable)
	void ControlSettingsSelected();
	UFUNCTION(BlueprintCallable)
	void ManageVisibility(const int32 SettingId);

	int32 ActualOptionIdSelected;
};
