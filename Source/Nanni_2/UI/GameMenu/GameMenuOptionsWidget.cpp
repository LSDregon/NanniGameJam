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
		if (!GameSettingsButton || !VideoSettingsButton ||!AudioSettingsButton ||!ControlSettingsButton)
		{
			return false;
		}
		if (GameSettingsButton)		GameSettingsButton->OnClicked.AddDynamic(this, &UGameMenuOptionsWidget::GameSettingsSelected);
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

void UGameMenuOptionsWidget::ManageVisibility(const int32 SettingId) const
{
	if (GameSettings)		GameSettings->SetVisibility((SettingId == 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (VideoSettings)
	{
		if (SettingId == 1)
		{
			VideoSettings->ReloadSettings();
		}
		VideoSettings->SetVisibility((SettingId == 1) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
	if (AudioSettings)		AudioSettings->SetVisibility((SettingId == 2) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (ControlSettings)	ControlSettings->SetVisibility((SettingId == 3) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
