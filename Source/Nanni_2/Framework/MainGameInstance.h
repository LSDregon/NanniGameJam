// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "SaveGameInformations.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NANNI_2_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FString SaveGameNameSlot = "DefaultSaveSlot";
	
	UPROPERTY()
	TObjectPtr<USaveGameInformations> SaveGameSlot;

	virtual void Init() override;

	UFUNCTION()
	void InitializeSaveGameSlot();
	
	UFUNCTION()
	USaveGameInformations* LoadSaveGameSlot();
	
	UFUNCTION()
	bool SaveSaveGameSlot(USaveGameInformations* SaveGameSlotRef) const;
	
	
};
