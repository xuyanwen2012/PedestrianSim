// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "MyTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	AMyTriggerVolume();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
