// Fill out your copyright notice in the Description page of Project Settings.


#include "Spline.h"

// Sets default values
ASpline::ASpline()
{
   PrimaryActorTick.bCanEverTick = true;

   SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
   RootComponent = SplineComponent;
}

void ASpline::BeginPlay()
{
   Super::BeginPlay();
}

void ASpline::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
}
