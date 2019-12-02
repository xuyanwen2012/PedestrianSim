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

   UPROPERTY()
   float DistanceAloneSpline;

   UPROPERTY()
   float AxisValue;

   UFUNCTION()
   void AddMovement();

   UFUNCTION()
   void UpdateLocationAndRotation();

protected:
   void BeginPlay() override;

   UPROPERTY()
   float PlayerAcceleration;

   UPROPERTY()
   float CharacterSpeed;

public:
   void Tick(float DeltaTime) override;

   void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
