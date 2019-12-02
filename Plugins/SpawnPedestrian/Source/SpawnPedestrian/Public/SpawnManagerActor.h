// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Spline.h"
#include "SpawnManagerActor.generated.h"

UCLASS()
class SPAWNPEDESTRIAN_API ASpawnManagerActor : public AActor
{
   GENERATED_BODY()

public:
   ASpawnManagerActor();

   UPROPERTY(EditAnywhere)
   UTextRenderComponent* TextRenderComponent;

   UPROPERTY(EditAnywhere)
   TArray<ASpline*> SplineRef;

   UFUNCTION()
   void SpawnNextSplineCharacter();

   UFUNCTION()
   void InitializeDebugScene();

protected:
   void BeginPlay() override;

public:
   void Tick(float DeltaTime) override;
};
