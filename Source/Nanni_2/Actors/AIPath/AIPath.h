// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPath.generated.h"

UCLASS()
class NANNI_2_API AAIPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPath();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Path
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Path", Meta = (MakeEditWidget = true))
		TArray<FVector> Spline;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
