// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTriggerVolume.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define PRINT_FSTRING(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

void AMyTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Cyan, true, -1, 0, 5);
}

AMyTriggerVolume::AMyTriggerVolume()
{
	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerVolume::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyTriggerVolume::OnOverlapEnd);
}

void AMyTriggerVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		// print to screen using above defined method when actor enters trigger volume
		PRINT("Overlap Begin");
		PRINT_FSTRING("Other Actor = %s", *OtherActor->GetName());
	}
}

void AMyTriggerVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		PRINT("Overlap Ended");
		PRINT_FSTRING("%s has left the Trigger Volume", *OtherActor->GetName());
	}
}
