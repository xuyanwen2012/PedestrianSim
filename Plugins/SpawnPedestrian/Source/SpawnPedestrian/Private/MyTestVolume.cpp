// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestVolume.h"
#include "DrawDebugHelpers.h"

AMyTestVolume::AMyTestVolume()
{
}

void AMyTestVolume::BeginPlay()
{
   DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Cyan, true, -1, 0, 5);
}
