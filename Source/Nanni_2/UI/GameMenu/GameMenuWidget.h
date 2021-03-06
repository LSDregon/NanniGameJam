// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameMenuCreditsWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuWidget.generated.h"

class UGameMenuGameSettingsWidget;
class UGameMenuControlSettingsWidget;
class UGameMenuAudioSettingsWidget;
class UGameMenuVideoSettingsWidget;
class UGameMenuOptionsWidget;
class UGameMenuMainPageWidget;
class UButton;
/**
 * 
 */
UCLASS()
class NANNI_2_API UGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BackButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGameMenuMainPageWidget> MainPageMenu;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGameMenuOptionsWidget> OptionMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGameMenuCreditsWidget> Credits;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGameMenuGameSettingsWidget> GameSettings;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGameMenuVideoSettingsWidget> VideoSettings;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGameMenuAudioSettingsWidget> AudioSettings;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGameMenuControlSettingsWidget> ControlSettings;
	
	virtual bool Initialize() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BackFadeInAnimationExec();
	UFUNCTION(BlueprintImplementableEvent)
	void BackFadeOutAnimationExec();
	
	UFUNCTION(BlueprintCallable)
	void BackPageOperation();
	UFUNCTION(BlueprintCallable)
	void InitializeSections();
};
