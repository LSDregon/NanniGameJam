// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuVideoSettingsWidget.generated.h"

class UCheckBox;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class NANNI_2_API UGameMenuVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//Video Section
	//Screen Resolution
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ScreenResolutionButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScreenResolutionText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ScreenResolutionButton_p;
	
	//Full Screen
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> FullScreenButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> FullScreenText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> FullScreenButton_p;
	
	//Frame Rate
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> FrameRateButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> FrameRateText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> FrameRateButton_p;
	
	//VSync
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCheckBox> VSyncCheckBox;
	
	//Video Quality Section
	//Anti Aliasing
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AntiAliasingButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AntiAliasingText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AntiAliasingButton_p;
	
	//Post Process
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> PostProcessButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PostProcessText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> PostProcessButton_p;
	
	//Textures
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> TexturesButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TexturesText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> TexturesButton_p;
	
	//Shadows
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ShadowsButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ShadowsText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ShadowsButton_p;
	
	//Foliage
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> FoliageButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> FoliageText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> FoliageButton_p;
	
	//Effects
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> EffectsButton_m;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> EffectsText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> EffectsButton_p;

	//Apply Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ApplySettingsButton;
	
	UFUNCTION(BlueprintCallable)
	int32 GetScreenResolutionValues() const { return ScreenResolutionValues; }
	UFUNCTION(BlueprintCallable)
	void SetScreenResolutionValues(const int32 ScreenResolutionValuesNew) { this->ScreenResolutionValues = ScreenResolutionValuesNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetFullScreenModeValue() const { return FullScreenModeValue; }
	UFUNCTION(BlueprintCallable)
	void SetFullScreenModeValue(int32 FullScreenModeValueNew) { this->FullScreenModeValue = FullScreenModeValueNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetFrameRateValue() const { return FrameRateValue; }
	UFUNCTION(BlueprintCallable)
	void SetFrameRateValue(int32 FrameRateValueNew) { this->FrameRateValue = FrameRateValueNew; }

	UFUNCTION(BlueprintCallable)
	bool IsVSyncEnable() const { return bVSyncEnable; }
	UFUNCTION(BlueprintCallable)
	void SetVSyncEnable(bool bVSyncEnableNew) { this->bVSyncEnable = bVSyncEnableNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetAntiAliasingQualityValue() const { return AntiAliasingQualityValue; }
	UFUNCTION(BlueprintCallable)
	void SetAntiAliasingQualityValue(int32 AntiAliasingQualityValueNew) { this->AntiAliasingQualityValue = AntiAliasingQualityValueNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetPostProcessQualityValue() const { return PostProcessQualityValue; }
	UFUNCTION(BlueprintCallable)
	void SetPostProcessQualityValue(int32 PostProcessQualityValueNew) { this->PostProcessQualityValue = PostProcessQualityValueNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetTexturesQualityValue() const { return TexturesQualityValue; }
	UFUNCTION(BlueprintCallable)
	void SetTexturesQualityValue(int32 TexturesQualityValueNew) { this->TexturesQualityValue = TexturesQualityValueNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetShadowsQualityValue() const { return ShadowsQualityValue; }
	UFUNCTION(BlueprintCallable)
	void SetShadowsQualityValue(int32 ShadowsQualityValueNew) { this->ShadowsQualityValue = ShadowsQualityValueNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetFoliageQualityValue() const { return FoliageQualityValue; }
	UFUNCTION(BlueprintCallable)
	void SetFoliageQualityValue(int32 FoliageQualityValueNew) { this->FoliageQualityValue = FoliageQualityValueNew; }

	UFUNCTION(BlueprintCallable)
	int32 GetEffectsQualityValue() const { return EffectsQualityValue; }
	UFUNCTION(BlueprintCallable)
	void SetEffectsQualityValue(int32 EffectsQualityValueNew) { this->EffectsQualityValue = EffectsQualityValueNew; }

public:
	
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void FadeInAnimationExec();
	UFUNCTION(BlueprintImplementableEvent)
	void FadeOutAnimationExec();
	
	UFUNCTION(BlueprintCallable)
	static FText GetQualityText(int32 QualityId);
	
	//Screen Resolution
	UFUNCTION(BlueprintCallable)
	void DecreaseScreenResolution();
	UFUNCTION(BlueprintCallable)
	void IncreaseScreenResolution();
	UFUNCTION(BlueprintCallable)
	void ScreenResolutionManager(int32 Value);
	UFUNCTION(BlueprintCallable)
	static FText ScreenResolutionInText(int32 ScreenResolutionValueID);
	UFUNCTION(BlueprintCallable)
	static FIntPoint ScreenResolutionInFIntPoint(int32 ScreenResolutionValueID);
	UFUNCTION(BlueprintCallable)
	static int32 ScreenResolutionFromFIntPointToId(FIntPoint ScreenResolutionValueRow);
	
	//Full Screen Mode
	UFUNCTION(BlueprintCallable)
	void DecreaseFullScreenMode();
	UFUNCTION(BlueprintCallable)
	void IncreaseFullScreenMode();
	UFUNCTION(BlueprintCallable)
	void FullScreenModeManager(int32 Value);
	UFUNCTION(BlueprintCallable)
	static int32 FullScreenModeFromEnumToId(EWindowMode::Type FullScreenModeType);

	//Frame Rate
	UFUNCTION(BlueprintCallable)
	void DecreaseFrameRate();
	UFUNCTION(BlueprintCallable)
	void IncreaseFrameRate();
	UFUNCTION(BlueprintCallable)
	void FrameRateManager(int32 Value);
	UFUNCTION(BlueprintCallable)
	static FText FrameRateValuesInText(int32 FrameRateValueID);
	UFUNCTION(BlueprintCallable)
	static float FrameRateValuesInFloat(int32 FrameRateValueID);
	UFUNCTION(BlueprintCallable)
	static int32 FrameRateFromFloatToId(float FrameRateValueRaw);

	//VSync
	UFUNCTION(BlueprintCallable)
	void VSyncManager(bool bIsChecked);

	//Anti Aliasing
	UFUNCTION(BlueprintCallable)
	void IncreaseAntiAliasing();
	UFUNCTION(BlueprintCallable)
	void DecreaseAntiAliasing();
	UFUNCTION(BlueprintCallable)
	void AntiAliasingManager(int32 Value);
	
	//Post Process
	UFUNCTION(BlueprintCallable)
	void DecreasePostProcess();
	UFUNCTION(BlueprintCallable)
	void IncreasePostProcess();
	UFUNCTION(BlueprintCallable)
	void PostProcessManager(int32 Value);
	
	//Textures
	UFUNCTION(BlueprintCallable)
	void DecreaseTextures();
	UFUNCTION(BlueprintCallable)
	void IncreaseTextures();
	UFUNCTION(BlueprintCallable)
	void TexturesManager(int32 Value);
	
	//Shadows
	UFUNCTION(BlueprintCallable)
	void DecreaseShadows();
	UFUNCTION(BlueprintCallable)
	void IncreaseShadows();
	UFUNCTION(BlueprintCallable)
	void ShadowsManager(int32 Value);
	
	//Foliage
	UFUNCTION(BlueprintCallable)
	void DecreaseFoliage();
	UFUNCTION(BlueprintCallable)
	void IncreaseFoliage();
	UFUNCTION(BlueprintCallable)
	void FoliageManager(int32 Value);
	
	//Effects
	UFUNCTION(BlueprintCallable)
	void DecreaseEffects();
	UFUNCTION(BlueprintCallable)
	void IncreaseEffects();
	UFUNCTION(BlueprintCallable)
	void EffectsManager(int32 Value);
	
	UFUNCTION(BlueprintCallable)
	void ApplySettings();
	UFUNCTION(BlueprintCallable)
	void ReloadSettings();

private:

	int32 ScreenResolutionValues;
	int32 FullScreenModeValue;
	int32 FrameRateValue;
	bool bVSyncEnable;
	int32 AntiAliasingQualityValue;
	int32 PostProcessQualityValue;
	int32 TexturesQualityValue;
	int32 ShadowsQualityValue;
	int32 FoliageQualityValue;
	int32 EffectsQualityValue;
	
};
