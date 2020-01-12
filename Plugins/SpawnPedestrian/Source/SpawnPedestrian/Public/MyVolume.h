// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "MyVolume.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API AMyVolume : public AVolume
{
   GENERATED_BODY()

public:
   AMyVolume(const FObjectInitializer& ObjectInitializer);

   void BeginPlay() override;

private:
   FVector MyOrigin;
   FVector MyExtent;

   void UpdateBounds();
};
