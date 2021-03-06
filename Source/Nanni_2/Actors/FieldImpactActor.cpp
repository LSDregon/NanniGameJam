// Copyright © 2022 Last Second


#include "FieldImpactActor.h"

#include "Components/SphereComponent.h"

AFieldImpactActor::AFieldImpactActor()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	
	RadioFalloff = CreateDefaultSubobject<URadialFalloff>(TEXT("Radio Falloff"));
	if (!RadioFalloff)this->AddOwnedComponent(RadioFalloff);
	RadialVector = CreateDefaultSubobject<URadialVector>(TEXT("Radio Vector"));
	if (!RadialVector)this->AddOwnedComponent(RadialVector);
	CullingField = CreateDefaultSubobject<UCullingField>(TEXT("Culling Field"));
	if (!CullingField)this->AddOwnedComponent(CullingField);
	
	StrainMagnitude = 10000;
	MagnitudeForce = 1000;
}

void AFieldImpactActor::Explode()
{
	RadioFalloff->SetRadialFalloff(StrainMagnitude, 0, 1, 0, Sphere->GetScaledSphereRadius(), Sphere->K2_GetComponentLocation(),
	                               EFieldFalloffType::Field_FallOff_None);
	GetFieldSystemComponent()->ApplyPhysicsField(true, EFieldPhysicsType::Field_ExternalClusterStrain, nullptr, RadioFalloff);

	RadialVector->SetRadialVector(MagnitudeForce, Sphere->K2_GetComponentLocation());
	CullingField->SetCullingField(RadioFalloff, RadialVector, EFieldCullingOperationType::Field_Culling_Outside);
	GetFieldSystemComponent()->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearVelocity, nullptr, CullingField);
}
