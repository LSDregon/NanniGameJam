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
	ActualOptionIdSelected = -2;
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
	// 	GameSettings->SetVisibility(ESlateVisibility::Visible);
	//	GameSettings->bIsFocusable = true;
	// 	
	// 	if (ActualOptionIdSelected == 1)
	// 	{
	// 		VideoSettings->FadeOutAnimationExec();
	//		VideoSettings->bIsFocusable = false;
	// 	}
	// 	if (ActualOptionIdSelected == 2)
	// 	{
	// 		AudioSettings->FadeOutAnimationExec();
	//		AudioSettings->bIsFocusable = false;
	// 	}
	// 	if (ActualOptionIdSelected == 3)
	// 	{
	// 		ControlSettings->FadeOutAnimationExec();
	//		ControlSettings->bIsFocusable = false;
	// 	}
	// 	ActualOptionIdSelected = 0;
	// }
	if (SettingId == 1)
	{
		VideoSettings->ReloadSettings();
		VideoSettings->FadeInAnimationExec();
		VideoSettings->SetVisibility(ESlateVisibility::Visible);
		VideoSettings->bIsFocusable = true;

		//if (ActualOptionIdSelected == 0)
		//{
		//	GameSettings->FadeOutAnimationExec();
		//	GameSettings->bIsFocusable = false;
		//}
		if (ActualOptionIdSelected == 2)
		{
			AudioSettings->FadeOutAnimationExec();
			AudioSettings->bIsFocusable = false;
		}
		if (ActualOptionIdSelected == 3)
		{
			ControlSettings->FadeOutAnimationExec();
			ControlSettings->bIsFocusable = false;
		}
		ActualOptionIdSelected = 1;
	}
	if (SettingId == 2)
	{
		AudioSettings->FadeInAnimationExec();
		AudioSettings->SetVisibility(ESlateVisibility::Visible);
		AudioSettings->bIsFocusable = true;
		
		//if (ActualOptionIdSelected == 0)
		//{
		//	GameSettings->FadeOutAnimationExec();
		//	GameSettings->bIsFocusable = false;
		//}
		if (ActualOptionIdSelected == 1)
		{
			VideoSettings->FadeOutAnimationExec();
			VideoSettings->bIsFocusable = false;
		}
		if (ActualOptionIdSelected == 3)
		{
			ControlSettings->FadeOutAnimationExec();
			ControlSettings->bIsFocusable = false;
		}
		ActualOptionIdSelected = 2;
	}
	if (SettingId == 3)
	{
		ControlSettings->FadeInAnimationExec();
		ControlSettings->SetVisibility(ESlateVisibility::Visible);
		ControlSettings->bIsFocusable = true;
		
		//if (ActualOptionIdSelected == 0)
		//{
		//	GameSettings->FadeOutAnimationExec();
		//	GameSettings->bIsFocusable = false;
		//}
		if (ActualOptionIdSelected == 1)
		{
			VideoSettings->FadeOutAnimationExec();
			VideoSettings->bIsFocusable = false;
		}
		if (ActualOptionIdSelected == 2)
		{
			AudioSettings->FadeOutAnimationExec();
			AudioSettings->bIsFocusable = false;
		}
		ActualOptionIdSelected = 3;
	}
	
}
