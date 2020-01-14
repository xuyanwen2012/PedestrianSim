// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PedestrianBTCharacter.generated.h"

UCLASS()
class SPAWNPEDESTRIAN_API APedestrianBTCharacter : public ACharacter
{
   GENERATED_BODY()

public:
   APedestrianBTCharacter();

   UPROPERTY(EditAnywhere, Category = Behaviour)
   class UBehaviorTree* BotBehavior;

protected:
   void BeginPlay() override;

public:
   void Tick(float DeltaTime) override;

   void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
