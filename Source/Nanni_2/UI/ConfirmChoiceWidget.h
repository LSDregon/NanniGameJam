// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmChoiceWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYesButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoButtonClicked);

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class NANNI_2_API UConfirmChoiceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ChoiceText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> YesButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> NoButton;
	
	UPROPERTY(BlueprintAssignable)
	FOnYesButtonClicked OnYesButtonClicked;
	
	UPROPERTY(BlueprintAssignable)
	FOnNoButtonClicked OnNoButtonClicked;

	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable)
	void YesButtonClicked();
	UFUNCTION(BlueprintCallable)
	void NoButtonClicked();

	UFUNCTION(BlueprintCallable)
	void SetChoiceText(FText NewText) const;
};
