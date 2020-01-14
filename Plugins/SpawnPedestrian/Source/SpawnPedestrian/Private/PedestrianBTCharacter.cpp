// Fill out your copyright notice in the Description page of Project Settings.


#include "PedestrianBTCharacter.h"

APedestrianBTCharacter::APedestrianBTCharacter()
{
   PrimaryActorTick.bCanEverTick = true;
}

void APedestrianBTCharacter::BeginPlay()
{
   Super::BeginPlay();
}

void APedestrianBTCharacter::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
}

void APedestrianBTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
   Super::SetupPlayerInputComponent(PlayerInputComponent);
}
