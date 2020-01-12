// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineCharacter.h"
#include "Spline.h"

ASplineCharacter::ASplineCharacter()
   : Super()
{
   PrimaryActorTick.bCanEverTick = true;
   DistanceAloneSpline = 0;
}

void ASplineCharacter::AddMovement()
{
   PlayerAcceleration = CharacterSpeed * AxisValue;

   DistanceAloneSpline += PlayerAcceleration * GetWorld()->DeltaTimeSeconds;
}

void ASplineCharacter::UpdateLocationAndRotation()
{
   const auto NewRotation = SplineRef->SplineComponent->GetRotationAtDistanceAlongSpline(
      DistanceAloneSpline, ESplineCoordinateSpace::World);

   auto NewLocation = SplineRef->SplineComponent->GetLocationAtDistanceAlongSpline(
      DistanceAloneSpline, ESplineCoordinateSpace::World);

   NewLocation.Z = GetActorLocation().Z;

   SetActorLocationAndRotation(NewLocation, NewRotation);
}

void ASplineCharacter::BeginPlay()
{
   Super::BeginPlay();

   // Setting up default values
   //
   CharacterSpeed = WalkSpeed;
}

void ASplineCharacter::Tick(const float DeltaTime)
{
   Super::Tick(DeltaTime);
}

void ASplineCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
   Super::SetupPlayerInputComponent(PlayerInputComponent);
}
