// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "MyTestVolume.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API AMyTestVolume : public AVolume
{
   GENERATED_BODY()

public:
   AMyTestVolume();

protected:
   void BeginPlay() override;
};
