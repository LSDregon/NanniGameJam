// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameMenuCreditsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Nanni_2/UI/ConfirmChoiceWidget.h"
#include "GameMenuMainPageWidget.generated.h"

class UGameMenuWidget;
class UGameMenuOptionsWidget;
class UButton;
/**
 * 
 */
UCLASS()
class NANNI_2_API UGameMenuMainPageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ResumeButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> OptionsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CreditsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UButton> BackButton;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameMenuOptionsWidget> OptionMenu;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameMenuCreditsWidget> Credits;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameMenuWidget> InGameMenuReference;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UConfirmChoiceWidget> WBPConfirmChoice;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInGameMenu = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!IsInGameMenu"))
	FString LevelToLoadName;
	
	UPROPERTY(EditAnywhere)
	FText ConfirmChoiceText;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UConfirmChoiceWidget> ConfirmChoiceWidget;
	
	virtual bool Initialize() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FadeInAnimationExec();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FadeOutAnimationExec();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CallOpenLevel();
	
	UFUNCTION(BlueprintCallable)
	void ResumeSelected();
	UFUNCTION(BlueprintCallable)
	void OptionsSelected();
	UFUNCTION(BlueprintCallable)
	void CreditsSelected();
	UFUNCTION(BlueprintCallable)
	void QuitSelected();
	
	UFUNCTION(BlueprintCallable)
	void YesSelected();
	UFUNCTION(BlueprintCallable)
	void NoSelected();
};
