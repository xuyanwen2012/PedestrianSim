// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SplineCharacter.h"
#include "PedestrianCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API APedestrianCharacter : public ASplineCharacter
{
   GENERATED_BODY()

public:
   APedestrianCharacter();

   void Tick(float DeltaTime) override;
};
