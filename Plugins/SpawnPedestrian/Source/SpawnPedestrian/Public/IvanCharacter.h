// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PedestrianCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "IvanCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API AIvanCharacter : public APedestrianCharacter
{
   GENERATED_BODY()

public:
   AIvanCharacter();

   UPROPERTY(EditAnywhere)
   USkeletalMeshComponent* MeshComponent;
};
