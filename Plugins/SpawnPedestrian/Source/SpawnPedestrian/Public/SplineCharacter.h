// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "SplineCharacter.generated.h"

// Forward Deceleration
class ASpline;

UCLASS()
class SPAWNPEDESTRIAN_API ASplineCharacter : public ACharacter
{
   GENERATED_BODY()

public:
   ASplineCharacter();

   UPROPERTY(EditAnywhere)
   float WalkSpeed;

   UPROPERTY(EditAnywhere)
   ASpline* SplineRef;

   UFUNCTION()
   void AddMovement();

   UFUNCTION()
   void UpdateLocationAndRotation();

protected:
   void BeginPlay() override;

   UPROPERTY()
      float DistanceAloneSpline;

   UPROPERTY()
      float PlayerAcceleration;

   UPROPERTY()
      float CharacterSpeed;

   UPROPERTY()
      float AxisValue;

public:
   void Tick(float DeltaTime) override;

   void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
