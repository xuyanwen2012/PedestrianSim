// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SplineComponent.h"

#include "Spline.generated.h"

// Forward Declarations
class ASplineCharacter;

UCLASS()
class SPAWNPEDESTRIAN_API ASpline : public AActor
{
   GENERATED_BODY()

public:
   // Sets default values for this actor's properties
   ASpline();

   UPROPERTY(EditAnywhere)
   class USplineComponent* SplineComponent;

   UPROPERTY(EditAnywhere)
   TArray<ASplineCharacter*> SpawnableSplineCharacters;

   UPROPERTY(EditAnywhere)
   int NumberOfCharacters;

protected:
   void BeginPlay() override;
};
