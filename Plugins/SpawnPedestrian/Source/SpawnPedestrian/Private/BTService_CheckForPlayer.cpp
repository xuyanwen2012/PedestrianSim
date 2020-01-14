// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckForPlayer.h"
#include "PedestrianAIController.h"
#include "PedestrianBTCharacter.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
   bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
   APedestrianAIController* PedestrianAI = Cast<APedestrianAIController>(OwnerComp.GetAIOwner());

   if (PedestrianAI)
   {
      APedestrianBTCharacter* Pedestrian = Cast<APedestrianBTCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

      if (Pedestrian)
      {
         OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(PedestrianAI->PedestrianKeyID, Pedestrian);
         GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "I exist");
      }
   }
}
