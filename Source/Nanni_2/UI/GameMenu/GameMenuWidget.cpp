// Copyright © 2022 Last Second


#include "GameMenuWidget.h"

#include "GameMenuAudioSettingsWidget.h"
#include "GameMenuControlSettingsWidget.h"
#include "GameMenuGameSettingsWidget.h"
#include "GameMenuMainPageWidget.h"
#include "GameMenuOptionsWidget.h"
#include "GameMenuVideoSettingsWidget.h"
#include "Components/Button.h"


bool UGameMenuWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!BackButton)
		{
			return false;
		}
		BackButton->OnClicked.AddDynamic(this, &UGameMenuWidget::BackPageOperation);
		InitializeSections();
		return true;
	}
	return false;
}

void UGameMenuWidget::BackPageOperation()
{
	if (BackButton)
	{
		BackFadeOutAnimationExec();
		// BackButton->SetIsEnabled(false);
		// BackButton->SetVisibility(ESlateVisibility::Hidden);
		BackButton->IsFocusable = false;
	}
	if (Credits)
	{
		Credits->FadeOutAnimationExec();
		// OptionMenu->SetIsEnabled(false);
		// OptionMenu->SetVisibility(ESlateVisibility::Hidden);
		Credits->bIsFocusable = false;
	}
	if (OptionMenu && OptionMenu->ActualOptionIdSelected > -2)
	{
		OptionMenu->FadeOutAnimationExec();
		// OptionMenu->SetIsEnabled(false);
		// OptionMenu->SetVisibility(ESlateVisibility::Hidden);
		OptionMenu->bIsFocusable = false;
	}
	if (GameSettings && OptionMenu && OptionMenu->ActualOptionIdSelected == 0)
	{
		GameSettings->FadeOutAnimationExec();
		// GameSettings->SetIsEnabled(false);
		// GameSettings->SetVisibility(ESlateVisibility::Hidden);
		GameSettings->bIsFocusable = false;
	}
	if (VideoSettings && OptionMenu && OptionMenu->ActualOptionIdSelected == 1)
	{
		VideoSettings->FadeOutAnimationExec();
		// VideoSettings->SetIsEnabled(false);
		// VideoSettings->SetVisibility(ESlateVisibility::Hidden);
		VideoSettings->bIsFocusable = false;
	}
	if (AudioSettings && OptionMenu && OptionMenu->ActualOptionIdSelected == 2)
	{
		AudioSettings->FadeOutAnimationExec();
		// AudioSettings->SetIsEnabled(false);
		// AudioSettings->SetVisibility(ESlateVisibility::Hidden);
		AudioSettings->bIsFocusable = false;
	}
	if (ControlSettings && OptionMenu &&OptionMenu->ActualOptionIdSelected == 3)
	{
		ControlSettings->FadeOutAnimationExec();
		// ControlSettings->SetIsEnabled(false);
		// ControlSettings->SetVisibility(ESlateVisibility::Hidden);
		ControlSettings->bIsFocusable = false;
	}
	if (MainPageMenu)
	{
		MainPageMenu->FadeInAnimationExec();
		// MainPageMenu->SetIsEnabled(true);
		MainPageMenu->SetVisibility(ESlateVisibility::Visible);
		MainPageMenu->bIsFocusable = true;
	}
	if(OptionMenu)
	{
		OptionMenu->ActualOptionIdSelected = -2;
	}
}

void UGameMenuWidget::InitializeSections()
{
	if (OptionMenu)
	{
		OptionMenu->GameSettings = GameSettings;
		OptionMenu->VideoSettings = VideoSettings;
		OptionMenu->AudioSettings = AudioSettings;
		OptionMenu->ControlSettings = ControlSettings;
	}
	if (MainPageMenu)
	{
		MainPageMenu->BackButton = BackButton;
		MainPageMenu->OptionMenu = OptionMenu;
		MainPageMenu->Credits = Credits;
		MainPageMenu->InGameMenuReference = this;
	}
}