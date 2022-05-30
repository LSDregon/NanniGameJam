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
	float GlobalVolumeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolumeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectsVolumeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnvironmentVolumeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DialoguesVolumeValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSensitivity;
	
};
