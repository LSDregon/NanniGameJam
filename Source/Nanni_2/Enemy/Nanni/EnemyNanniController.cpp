// Copyright © 2022 Last Second


#include "EnemyNanniController.h"

#include "Kismet/GameplayStatics.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"

void AEnemyNanniController::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}
