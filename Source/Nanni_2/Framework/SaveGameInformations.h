// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameInformations.generated.h"

/**
 * 
 */
UCLASS()
class NANNI_2_API USaveGameInformations : public USaveGame
{
	GENERATED_BODY()

public:

	//Volume Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GlobalVolumeValue = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolumeValue = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectsVolumeValue = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnvironmentVolumeValue = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DialoguesVolumeValue = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSensitivity = 50.f;
	
};
