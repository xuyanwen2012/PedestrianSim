// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SplineCharacter.h"
#include "SplineAIController.generated.h"

UCLASS()
class SPAWNPEDESTRIAN_API ASplineAIController : public AAIController
{
   GENERATED_BODY()

public:
   void Tick(float DeltaTime) override;

protected:
   UPROPERTY(EditAnywhere)
   ASplineCharacter* Player;
};
