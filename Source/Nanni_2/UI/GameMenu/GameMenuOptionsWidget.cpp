// Copyright © 2022 Last Second


#include "GameMenuOptionsWidget.h"

#include "GameMenuAudioSettingsWidget.h"
#include "GameMenuControlSettingsWidget.h"
#include "GameMenuGameSettingsWidget.h"
#include "GameMenuVideoSettingsWidget.h"
#include "Components/Button.h"


bool UGameMenuOptionsWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (//!GameSettingsButton ||
			!VideoSettingsButton ||!AudioSettingsButton ||!ControlSettingsButton)
		{
			return false;
		}
		//if (GameSettingsButton)		GameSettingsButton->OnClicked.AddDynamic(this, &UGameMenuOptionsWidget::GameSettingsSelected);
		if (VideoSettingsButton)	VideoSettingsButton->OnClicked.AddDynamic(this, &UGameMenuOptionsWidget::VideoSettingsSelected);
		if (AudioSettingsButton)	AudioSettingsButton->OnClicked.AddDynamic(this, &UGameMenuOptionsWidget::AudioSettingsSelected);
		if (ControlSettingsButton)	ControlSettingsButton->OnClicked.AddDynamic(this, &UGameMenuOptionsWidget::ControlSettingsSelected);		
		return true;
	}
	return false;
}

void UGameMenuOptionsWidget::GameSettingsSelected()
{
	ManageVisibility(0);
}
void UGameMenuOptionsWidget::VideoSettingsSelected()
{
	ManageVisibility(1);
}
void UGameMenuOptionsWidget::AudioSettingsSelected()
{
	ManageVisibility(2);
}
void UGameMenuOptionsWidget::ControlSettingsSelected()
{
	ManageVisibility(3);
}

void UGameMenuOptionsWidget::ManageVisibility(const int32 SettingId)
{
	// if (SettingId == 0)
	// {
	// 	GameSettings->FadeInAnimationExec();
	//	GameSettings->SetIsEnabled(true);
	// 	GameSettings->SetVisibility(ESlateVisibility::Visible);
	// 	
	// 	if (ActualOptionIdSelected == 1)
	// 	{
	// 		VideoSettings->FadeOutAnimationExec();
	//		VideoSettings->SetIsEnabled(false);
	//		VideoSettings->SetVisibility(ESlateVisibility::Hidden);
	// 	}
	// 	if (ActualOptionIdSelected == 2)
	// 	{
	// 		AudioSettings->FadeOutAnimationExec();
	//		AudioSettings->SetIsEnabled(false);
	//		AudioSettings->SetVisibility(ESlateVisibility::Hidden);
	// 	}
	// 	if (ActualOptionIdSelected == 3)
	// 	{
	// 		ControlSettings->FadeOutAnimationExec();
	//		ControlSettings->SetIsEnabled(false);
	//		ControlSettings->SetVisibility(ESlateVisibility::Hidden);
	// 	}
	// 	ActualOptionIdSelected = 0;
	// }
	if (SettingId == 1)
	{
		VideoSettings->ReloadSettings();
		VideoSettings->FadeInAnimationExec();
		// VideoSettings->SetIsEnabled(true);
		VideoSettings->SetVisibility(ESlateVisibility::Visible);
		VideoSettings->bIsFocusable = true;

		//if (ActualOptionIdSelected == 0)
		//{
		//	GameSettings->FadeOutAnimationExec();
		//	GameSettings->SetIsEnabled(false);
		//	GameSettings->SetVisibility(ESlateVisibility::Hidden);
		//}
		if (ActualOptionIdSelected == 2)
		{
			AudioSettings->FadeOutAnimationExec();
			// AudioSettings->SetIsEnabled(false);
			//AudioSettings->SetVisibility(ESlateVisibility::Hidden);
			AudioSettings->bIsFocusable = false;
		}
		if (ActualOptionIdSelected == 3)
		{
			ControlSettings->FadeOutAnimationExec();
			// ControlSettings->SetIsEnabled(false);
			//ControlSettings->SetVisibility(ESlateVisibility::Hidden);
			ControlSettings->bIsFocusable = false;
		}
		ActualOptionIdSelected = 1;
	}
	if (SettingId == 2)
	{
		AudioSettings->FadeInAnimationExec();
		// AudioSettings->SetIsEnabled(true);
		AudioSettings->SetVisibility(ESlateVisibility::Visible);
		AudioSettings->bIsFocusable = true;
		
		//if (ActualOptionIdSelected == 0)
		//{
		//	GameSettings->FadeOutAnimationExec();
		//	GameSettings->SetIsEnabled(false);
		//	GameSettings->SetVisibility(ESlateVisibility::Hidden);
		//}
		if (ActualOptionIdSelected == 1)
		{
			VideoSettings->FadeOutAnimationExec();
			// VideoSettings->SetIsEnabled(false);
			//VideoSettings->SetVisibility(ESlateVisibility::Hidden);
			VideoSettings->bIsFocusable = false;
		}
		if (ActualOptionIdSelected == 3)
		{
			ControlSettings->FadeOutAnimationExec();
			// ControlSettings->SetIsEnabled(false);
			//ControlSettings->SetVisibility(ESlateVisibility::Hidden);
			ControlSettings->bIsFocusable = false;
		}
		ActualOptionIdSelected = 2;
	}
	if (SettingId == 3)
	{
		ControlSettings->FadeInAnimationExec();
		// ControlSettings->SetIsEnabled(true);
		ControlSettings->SetVisibility(ESlateVisibility::Visible);
		ControlSettings->bIsFocusable = true;
		
		//if (ActualOptionIdSelected == 0)
		//{
		//	GameSettings->FadeOutAnimationExec();
		//	GameSettings->SetIsEnabled(false);
		//	GameSettings->SetVisibility(ESlateVisibility::Hidden);
		//}
		if (ActualOptionIdSelected == 1)
		{
			VideoSettings->FadeOutAnimationExec();
			// VideoSettings->SetIsEnabled(false);
			//VideoSettings->SetVisibility(ESlateVisibility::Hidden);
			VideoSettings->bIsFocusable = false;
		}
		if (ActualOptionIdSelected == 2)
		{
			AudioSettings->FadeOutAnimationExec();
			// AudioSettings->SetIsEnabled(false);
			//AudioSettings->SetVisibility(ESlateVisibility::Hidden);
			AudioSettings->bIsFocusable = false;
		}
		ActualOptionIdSelected = 3;
	}
}
