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
	UPROPERTY(VisibleAnywhere)
	float GlobalVolumeValue;
	UPROPERTY(VisibleAnywhere)
	float MusicVolumeValue;
	UPROPERTY(VisibleAnywhere)
	float EffectsVolumeValue;
	UPROPERTY(VisibleAnywhere)
	float EnvironmentVolumeValue;
	UPROPERTY(VisibleAnywhere)
	float DialoguesVolumeValue;
	
};
