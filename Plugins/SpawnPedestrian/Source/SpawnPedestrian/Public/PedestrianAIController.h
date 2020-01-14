// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "PedestrianAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API APedestrianAIController : public AAIController
{
   GENERATED_BODY()

   UPROPERTY(Transient)
   class UBlackboardComponent* BlackboardComp;

   UPROPERTY(Transient)
   class UBehaviorTreeComponent* BehaviorTreeComp;

public:

   APedestrianAIController();

   void OnPossess(APawn* InPawn) override;

   uint8 PedestrianKeyID;
};
