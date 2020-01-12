// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVolume.h"
#include "Components/BrushComponent.h"

AMyVolume::AMyVolume(const FObjectInitializer& ObjectInitializer)
   : Super(ObjectInitializer)
{
   GetBrushComponent()->Mobility = EComponentMobility::Static;

   BrushColor = FColor(255, 255, 255, 255);
   bColored = true;

   UpdateBounds();
}

void AMyVolume::BeginPlay()
{
   UpdateBounds();
}

void AMyVolume::UpdateBounds()
{
   // Get bounds and extent
   const FBox Bounds = GetComponentsBoundingBox(true);
   Bounds.GetCenterAndExtents(MyOrigin, MyExtent);
}
