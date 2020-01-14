// Fill out your copyright notice in the Description page of Project Settings.

#include "PedestrianAIController.h"
#include "PedestrianBTCharacter.h"

APedestrianAIController::APedestrianAIController()
{
   BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
   BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void APedestrianAIController::OnPossess(APawn* InPawn)
{
   Super::Possess(InPawn);

   APedestrianBTCharacter* Character = Cast<APedestrianBTCharacter>(InPawn);

   if (Character && Character->BotBehavior)
   {
      BlackboardComp->InitializeBlackboard(*Character->BotBehavior->BlackboardAsset);

      // Get the Key in the blackboard
      PedestrianKeyID = BlackboardComp->GetKeyID("Target");

      BehaviorTreeComp->StartTree(*Character->BotBehavior);
   }
}
