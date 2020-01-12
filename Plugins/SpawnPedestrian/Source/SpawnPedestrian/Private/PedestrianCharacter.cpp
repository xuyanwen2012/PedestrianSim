// Fill out your copyright notice in the Description page of Project Settings.


#include "PedestrianCharacter.h"
#include "Spline.h"
#include "SplineAIController.h"

APedestrianCharacter::APedestrianCharacter()
   : Super()
{
   AIControllerClass = ASplineAIController::StaticClass();
}

void APedestrianCharacter::Tick(const float DeltaTime)
{
   Super::Tick(DeltaTime);

   // Do updates
   // 
   UpdateLocationAndRotation();
   AddMovement();

   // Did we reach the end of the spline
   // 
   if (FMath::IsNearlyEqual(DistanceAloneSpline,
                            SplineRef->SplineComponent->GetSplineLength()))
   {
      DistanceAloneSpline = 0;
   }
}
