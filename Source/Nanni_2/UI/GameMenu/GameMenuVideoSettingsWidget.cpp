// Copyright © 2022 Last Second


#include "GameMenuVideoSettingsWidget.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

bool UGameMenuVideoSettingsWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!ScreenResolutionButton_m || !ScreenResolutionButton_p ||
			!FullScreenButton_m || !FullScreenButton_p ||
			!FrameRateButton_m || !FrameRateButton_p ||
			!VSyncCheckBox ||
			!AntiAliasingButton_m || !AntiAliasingButton_p ||
			!PostProcessButton_m || !PostProcessButton_p ||
			!TexturesButton_m || !TexturesButton_p ||
			!ShadowsButton_m || !ShadowsButton_p ||
			!FoliageButton_m || !FoliageButton_p ||
			!EffectsButton_m || !EffectsButton_p ||
			!ApplySettingsButton)
		{
			return false;
		}
		if (ScreenResolutionButton_m) 	ScreenResolutionButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseScreenResolution);
		if (ScreenResolutionButton_p) 	ScreenResolutionButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseScreenResolution);
		if (FullScreenButton_m) 		FullScreenButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseFullScreenMode);
		if (FullScreenButton_p) 		FullScreenButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseFullScreenMode);
		if (FrameRateButton_m)			FrameRateButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseFrameRate);
		if (FrameRateButton_p)			FrameRateButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseFrameRate);
		if (VSyncCheckBox)				VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UGameMenuVideoSettingsWidget::VSyncManager);
		
		if (AntiAliasingButton_m) 	AntiAliasingButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseAntiAliasing);
		if (AntiAliasingButton_p) 	AntiAliasingButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseAntiAliasing);
		if (PostProcessButton_m) 	PostProcessButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreasePostProcess);
		if (PostProcessButton_p) 	PostProcessButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreasePostProcess);
		if (TexturesButton_m) 		TexturesButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseTextures);
		if (TexturesButton_p) 		TexturesButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseTextures);
		if (ShadowsButton_m) 		ShadowsButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseShadows);
		if (ShadowsButton_p) 		ShadowsButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseShadows);
		if (FoliageButton_m) 		FoliageButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseFoliage);
		if (FoliageButton_p) 		FoliageButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseFoliage);
		if (EffectsButton_m) 		EffectsButton_m->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::DecreaseEffects);
		if (EffectsButton_p) 		EffectsButton_p->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::IncreaseEffects);
		
		if (ApplySettingsButton) ApplySettingsButton->OnClicked.AddDynamic(this, &UGameMenuVideoSettingsWidget::ApplySettings);
		return true;
	}
	return false;
}

FText UGameMenuVideoSettingsWidget::GetQualityText(int32 QualityId)
{
	switch (QualityId)
	{
	case 1: return FText::FromString(TEXT("Low"));
	case 2: return FText::FromString(TEXT("Medium"));
	case 3: return FText::FromString(TEXT("High"));
	case 4: return FText::FromString(TEXT("Epic"));
	default: return FText::FromString(TEXT("UNKNOWN"));
	}
}

void UGameMenuVideoSettingsWidget::DecreaseScreenResolution()
{
	const int32 NewValue = FMath::Clamp(GetScreenResolutionValues() - 1, 0, 8);
	ScreenResolutionManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseScreenResolution()
{
	const int32 NewValue = FMath::Clamp(GetScreenResolutionValues() + 1, 0, 8);
	ScreenResolutionManager(NewValue);
}
void UGameMenuVideoSettingsWidget::ScreenResolutionManager(int32 Value)
{
	SetScreenResolutionValues(Value);

	if (ScreenResolutionText) ScreenResolutionText->SetText(ScreenResolutionInText(GetScreenResolutionValues()));
}
FText UGameMenuVideoSettingsWidget::ScreenResolutionInText(int32 ScreenResolutionValueID)
{
	switch (ScreenResolutionValueID)
	{
		case 0: return FText::FromString(TEXT("640×480"));
		case 1: return FText::FromString(TEXT("720×480"));
		case 2: return FText::FromString(TEXT("1280×720"));
		case 3: return FText::FromString(TEXT("1600×900"));
		case 4: return FText::FromString(TEXT("1920×1080"));
		case 5: return FText::FromString(TEXT("2560×1080"));
		case 6: return FText::FromString(TEXT("2560×1440"));
		case 7: return FText::FromString(TEXT("3440×1440"));
		case 8: return FText::FromString(TEXT("3840×2160"));
		default: return FText::FromString(TEXT("1920×1080"));
	}
}
FIntPoint UGameMenuVideoSettingsWidget::ScreenResolutionInFIntPoint(int32 ScreenResolutionValueID)
{
	switch (ScreenResolutionValueID)
	{
		case 0: return FIntPoint(640, 480);
		case 1: return FIntPoint(720, 480);
		case 2: return FIntPoint(1280, 720);
		case 3: return FIntPoint(1600, 900);
		case 4: return FIntPoint(1920, 1080);
		case 5: return FIntPoint(2560, 1080);
		case 6: return FIntPoint(2560, 1440);
		case 7: return FIntPoint(3440, 1440);
		case 8: return FIntPoint(3840, 2160);
		default: return FIntPoint(1920, 1080);
	}
}
int32 UGameMenuVideoSettingsWidget::ScreenResolutionFromFIntPointToId(FIntPoint ScreenResolutionValueRow)
{
	if (ScreenResolutionValueRow == FIntPoint(640, 480)) return 0;
	if (ScreenResolutionValueRow == FIntPoint(720, 480)) return 1;
	if (ScreenResolutionValueRow == FIntPoint(1280, 720)) return 2;
	if (ScreenResolutionValueRow == FIntPoint(1600, 900)) return 3;
	if (ScreenResolutionValueRow == FIntPoint(1920, 1080)) return 4;
	if (ScreenResolutionValueRow == FIntPoint(2560, 1080)) return 5;
	if (ScreenResolutionValueRow == FIntPoint(2560, 1440)) return 6;
	if (ScreenResolutionValueRow == FIntPoint(3440, 1440)) return 7;
	if (ScreenResolutionValueRow == FIntPoint(3840, 2160)) return 8;
	return -1;
}

void UGameMenuVideoSettingsWidget::DecreaseFullScreenMode()
{
	const int32 NewValue = FMath::Clamp(GetFullScreenModeValue() - 1, 0, 2);
	FullScreenModeManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseFullScreenMode()
{
	const int32 NewValue = FMath::Clamp(GetFullScreenModeValue() + 1, 0, 2);
	FullScreenModeManager(NewValue);
}
void UGameMenuVideoSettingsWidget::FullScreenModeManager(int32 Value)
{
	SetFullScreenModeValue(Value);
	if (FullScreenText) FullScreenText->SetText(FText::FromString(LexToString(EWindowMode::ConvertIntToWindowMode(GetFullScreenModeValue()))));

	if (EWindowMode::ConvertIntToWindowMode(GetFullScreenModeValue()) == EWindowMode::Type::Fullscreen)
	{
		if (ScreenResolutionButton_m) ScreenResolutionButton_m->SetIsEnabled(false);
		if (ScreenResolutionButton_p) ScreenResolutionButton_p->SetIsEnabled(false);
		if (ScreenResolutionText) ScreenResolutionText->SetIsEnabled(false);
		
		const UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();
		SetScreenResolutionValues(ScreenResolutionFromFIntPointToId(GameSettings->GetDesktopResolution()));
		
		if (ScreenResolutionText) ScreenResolutionText->SetText(ScreenResolutionInText(GetScreenResolutionValues()));
	}
	else 
	{
		if (ScreenResolutionButton_m) ScreenResolutionButton_m->SetIsEnabled(true);
		if (ScreenResolutionButton_p) ScreenResolutionButton_p->SetIsEnabled(true);
		if (ScreenResolutionText) ScreenResolutionText->SetIsEnabled(true);
	}
}
int32 UGameMenuVideoSettingsWidget::FullScreenModeFromEnumToId(EWindowMode::Type FullScreenModeType)
{
	switch (FullScreenModeType)
	{
		case EWindowMode::Type::Fullscreen: return 0;
		case EWindowMode::Type::WindowedFullscreen: return 1;
		case EWindowMode::Type::Windowed: return 2;
		default: return -1;
	}
}

void UGameMenuVideoSettingsWidget::DecreaseFrameRate()
{
	const int32 NewValue = FMath::Clamp(GetFrameRateValue() - 1, -1, 4);
	FrameRateManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseFrameRate()
{
	const int32 NewValue = FMath::Clamp(GetFrameRateValue() + 1, -1, 4);
	FrameRateManager(NewValue);
}
void UGameMenuVideoSettingsWidget::FrameRateManager(int32 Value)
{
	SetFrameRateValue(Value);

	if (FrameRateText) FrameRateText->SetText(FrameRateValuesInText(GetFrameRateValue()));
}
FText UGameMenuVideoSettingsWidget::FrameRateValuesInText(int32 FrameRateValueID)
{
	switch (FrameRateValueID)
	{
		case 0: return FText::FromString(TEXT("30 FPS"));
		case 1: return FText::FromString(TEXT("60 FPS"));
		case 2: return FText::FromString(TEXT("90 FPS"));
		case 3: return FText::FromString(TEXT("120 FPS"));
		case 4: return FText::FromString(TEXT("144 FPS"));
		default: return FText::FromString(TEXT("UNLIMITED"));
	}
}
float UGameMenuVideoSettingsWidget::FrameRateValuesInFloat(int32 FrameRateValueID)
{
	switch (FrameRateValueID)
	{
		case 0: return 30.f;
		case 1: return 60.f;
		case 2: return 90.f;
		case 3: return 120.f;
		case 4: return 144.f;
		default: return 0.f;
	}
}
int32 UGameMenuVideoSettingsWidget::FrameRateFromFloatToId(float FrameRateValueRaw)
{
	if (FrameRateValueRaw == 30.f) return 0;
	if (FrameRateValueRaw == 60.f) return 1;
	if (FrameRateValueRaw == 90.f) return 2;
	if (FrameRateValueRaw == 120.f) return 3;
	if (FrameRateValueRaw == 144.f) return 4;
	return -1;
}

void UGameMenuVideoSettingsWidget::VSyncManager(bool bIsChecked)
{
	bVSyncEnable = bIsChecked;
	SetVSyncEnable(bVSyncEnable);
	
	if (VSyncCheckBox) VSyncCheckBox->SetIsChecked(bVSyncEnable);
	
	if (FrameRateButton_m) FrameRateButton_m->SetIsEnabled(!bVSyncEnable);
	if (FrameRateButton_p) FrameRateButton_p->SetIsEnabled(!bVSyncEnable);
	if (FrameRateText) FrameRateText->SetIsEnabled(!bVSyncEnable);
	
	if (bVSyncEnable)
	{
		SetFrameRateValue(FrameRateFromFloatToId(60.f));
		if (FrameRateText) FrameRateText->SetText(FrameRateValuesInText(GetFrameRateValue()));
	}
}

void UGameMenuVideoSettingsWidget::DecreaseAntiAliasing()
{
	const int32 NewValue = FMath::Clamp(GetAntiAliasingQualityValue() - 1, 1, 4);
	AntiAliasingManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseAntiAliasing()
{
	const int32 NewValue = FMath::Clamp(GetAntiAliasingQualityValue() + 1, 1, 4);
	AntiAliasingManager(NewValue);
}
void UGameMenuVideoSettingsWidget::AntiAliasingManager(int32 Value)
{
	SetAntiAliasingQualityValue(Value);

	if (AntiAliasingText) AntiAliasingText->SetText(GetQualityText(GetAntiAliasingQualityValue()));
}

void UGameMenuVideoSettingsWidget::DecreasePostProcess()
{
	const int32 NewValue = FMath::Clamp(GetPostProcessQualityValue() - 1, 1, 4);
	PostProcessManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreasePostProcess()
{
	const int32 NewValue = FMath::Clamp(GetPostProcessQualityValue() + 1, 1, 4);
	PostProcessManager(NewValue);
}
void UGameMenuVideoSettingsWidget::PostProcessManager(int32 Value)
{
	SetPostProcessQualityValue(Value);

	if (PostProcessText) PostProcessText->SetText(GetQualityText(GetPostProcessQualityValue()));
}

void UGameMenuVideoSettingsWidget::DecreaseTextures()
{
	const int32 NewValue = FMath::Clamp(GetTexturesQualityValue() - 1, 1, 4);
	TexturesManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseTextures()
{
	const int32 NewValue = FMath::Clamp(GetTexturesQualityValue() + 1, 1, 4);
	TexturesManager(NewValue);
}
void UGameMenuVideoSettingsWidget::TexturesManager(int32 Value)
{
	SetTexturesQualityValue(Value);

	if (TexturesText) TexturesText->SetText(GetQualityText(GetTexturesQualityValue()));
}

void UGameMenuVideoSettingsWidget::DecreaseShadows()
{
	const int32 NewValue = FMath::Clamp(GetShadowsQualityValue() - 1, 1, 4);
	ShadowsManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseShadows()
{
	const int32 NewValue = FMath::Clamp(GetShadowsQualityValue() + 1, 1, 4);
	ShadowsManager(NewValue);
}
void UGameMenuVideoSettingsWidget::ShadowsManager(int32 Value)
{
	SetShadowsQualityValue(Value);

	if (ShadowsText) ShadowsText->SetText(GetQualityText(GetShadowsQualityValue()));
}

void UGameMenuVideoSettingsWidget::DecreaseFoliage()
{
	const int32 NewValue = FMath::Clamp(GetFoliageQualityValue() - 1, 1, 4);
	FoliageManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseFoliage()
{
	const int32 NewValue = FMath::Clamp(GetFoliageQualityValue() + 1, 1, 4);
	FoliageManager(NewValue);
}
void UGameMenuVideoSettingsWidget::FoliageManager(int32 Value)
{
	SetFoliageQualityValue(Value);
	
	if (FoliageText) FoliageText->SetText(GetQualityText(GetFoliageQualityValue()));
}

void UGameMenuVideoSettingsWidget::DecreaseEffects()
{
	const int32 NewValue = FMath::Clamp(GetEffectsQualityValue() - 1, 1, 4);
	EffectsManager(NewValue);
}
void UGameMenuVideoSettingsWidget::IncreaseEffects()
{
	const int32 NewValue = FMath::Clamp(GetEffectsQualityValue() + 1, 1, 4);
	EffectsManager(NewValue);
}
void UGameMenuVideoSettingsWidget::EffectsManager(int32 Value)
{
	SetEffectsQualityValue(Value);

	if (EffectsText) EffectsText->SetText(GetQualityText(GetEffectsQualityValue()));
}

void UGameMenuVideoSettingsWidget::ApplySettings()
{
	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();
	
	GameSettings->SetScreenResolution(ScreenResolutionInFIntPoint(GetScreenResolutionValues()));
	GameSettings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(GetFullScreenModeValue()));
	GameSettings->SetFrameRateLimit(FrameRateValuesInFloat(GetFrameRateValue()));
	GameSettings->SetVSyncEnabled(IsVSyncEnable());
	GameSettings->SetAntiAliasingQuality(GetAntiAliasingQualityValue());
	GameSettings->SetPostProcessingQuality(GetPostProcessQualityValue());
	GameSettings->SetTextureQuality(GetTexturesQualityValue());
	GameSettings->SetShadowQuality(GetShadowsQualityValue());
	GameSettings->SetFoliageQuality(GetFoliageQualityValue());
	GameSettings->SetVisualEffectQuality(GetEffectsQualityValue());

	GameSettings->ApplySettings(true);
	GameSettings->SaveSettings();
}

void UGameMenuVideoSettingsWidget::ReloadSettings()
{
	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();
	GameSettings->LoadSettings();
	
	ScreenResolutionManager(ScreenResolutionFromFIntPointToId(GameSettings->GetScreenResolution()));
	FullScreenModeManager(FullScreenModeFromEnumToId(GameSettings->GetFullscreenMode()));
	FrameRateManager(FrameRateFromFloatToId(GameSettings->GetFrameRateLimit()));
	VSyncManager(GameSettings->IsVSyncEnabled());
	
	AntiAliasingManager(GameSettings->GetAntiAliasingQuality());
	PostProcessManager(GameSettings->GetPostProcessingQuality());
	TexturesManager(GameSettings->GetTextureQuality());
	ShadowsManager(GameSettings->GetShadingQuality());
	FoliageManager(GameSettings->GetFoliageQuality());
	EffectsManager(GameSettings->GetVisualEffectQuality());
}
