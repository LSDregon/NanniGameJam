// Copyright © 2022 Last Second


#include "LaserLine.h"

#include "Kismet/KismetStringLibrary.h"

// Sets default values
ALaserLine::ALaserLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;
	
	NiagaraLaser = CreateDefaultSubobject<UNiagaraComponent>("NiagaraLaser");
	NiagaraLaser->SetupAttachment(Scene);
	
	NiagaraLaserImpact = CreateDefaultSubobject<UNiagaraComponent>("NiagaraLaserImpact");
	NiagaraLaserImpact->SetupAttachment(Scene);
}

void ALaserLine::BeginPlay()
{
	Super::BeginPlay();
	PlaySound();
}
void ALaserLine::SetColorLaser(FColor Color) const
{
	if (NiagaraLaser) NiagaraLaser->SetColorParameter(UKismetStringLibrary::Conv_StringToName("Color"), Color);
}
void ALaserLine::SetColorLaserImpact(FColor Color) const
{
	if (NiagaraLaserImpact) NiagaraLaserImpact->SetColorParameter(UKismetStringLibrary::Conv_StringToName("Color"), Color);
}

void ALaserLine::SetLaser(FVector EndVector) const
{
	if (NiagaraLaser) NiagaraLaser->SetVectorParameter(UKismetStringLibrary::Conv_StringToName("LaserEnd"), EndVector);
}
void ALaserLine::SetLaserImpact(FVector EndVector) const
{
	if (NiagaraLaserImpact) NiagaraLaserImpact->SetWorldLocation(EndVector);
}

void ALaserLine::SetActiveStateLaser(bool IsActive) const
{
	if (IsActive)
	{
		if (NiagaraLaser)
		{
			NiagaraLaser->SetIntParameter(UKismetStringLibrary::Conv_StringToName("ParticleCount"), 2);
			NiagaraLaser->Activate();
		}
	}
	else
	{
		if (NiagaraLaser)
		{
			NiagaraLaser->SetIntParameter(UKismetStringLibrary::Conv_StringToName("ParticleCount"), 0);
			NiagaraLaser->Deactivate();
		}
	}
}

void ALaserLine::SetActiveStateLaserImpact(bool IsActive) const
{
	if (IsActive)
	{
		if (NiagaraLaserImpact)
		{
			NiagaraLaser->SetIntParameter(UKismetStringLibrary::Conv_StringToName("ParticleCount"), 10);
			NiagaraLaserImpact->Activate();
		}
	}
	else
	{
		if (NiagaraLaserImpact)
		{
			NiagaraLaser->SetIntParameter(UKismetStringLibrary::Conv_StringToName("ParticleCount"), 0);
			NiagaraLaserImpact->Deactivate();
		}
	}
}

