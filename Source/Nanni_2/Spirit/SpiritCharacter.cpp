// Copyright © 2022 Last Second


#include "SpiritCharacter.h"

// Sets default values
ASpiritCharacter::ASpiritCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpiritCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpiritCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpiritCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

