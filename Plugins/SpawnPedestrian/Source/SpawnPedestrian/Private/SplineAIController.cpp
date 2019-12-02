// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineAIController.h"

void ASplineAIController::Tick(const float DeltaTime)
{
   if (!IsValid(Player))
   {
      Player = Cast<ASplineCharacter>(GetPawn());
      Player->AxisValue = 1;

      // Do other things here
   }
}
