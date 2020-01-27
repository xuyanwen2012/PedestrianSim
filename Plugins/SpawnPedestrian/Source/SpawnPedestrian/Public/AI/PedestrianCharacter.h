// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PedestrianCharacter.generated.h"

UCLASS()
class SPAWNPEDESTRIAN_API APedestrianCharacter : public ACharacter
{
   GENERATED_BODY()

public:
   // Sets default values for this character's properties
   APedestrianCharacter();

protected:
   // Called when the game starts or when spawned
   void BeginPlay() override;

public:
   // Called every frame
   void Tick(float DeltaTime) override;

   // Called to bind functionality to input
   void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
