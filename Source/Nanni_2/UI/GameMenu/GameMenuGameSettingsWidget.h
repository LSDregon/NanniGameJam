// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuGameSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class NANNI_2_API UGameMenuGameSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void FadeInAnimationExec();
	UFUNCTION(BlueprintImplementableEvent)
	void FadeOutAnimationExec();
};
