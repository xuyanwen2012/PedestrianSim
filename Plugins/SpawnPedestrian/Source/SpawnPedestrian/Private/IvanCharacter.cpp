// Fill out your copyright notice in the Description page of Project Settings.


#include "IvanCharacter.h"
#include "Animation/AnimBlueprint.h"
#include "ConstructorHelpers.h"


AIvanCharacter::AIvanCharacter()
{
   static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
      TEXT("SkeletalMesh'/SpawnPedestrian/BasePedestrian/Mesh/SK_Pedestrian.SK_Pedestrian'"));

   static ConstructorHelpers::FObjectFinder<UClass> AnimBP(
      TEXT(
         "AnimBlueprint'/SpawnPedestrian/BasePedestrian/Blueprints/PedestrianAnimBlueprint.PedestrianAnimBlueprint_C'"));

   MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));

   if (MeshAsset.Succeeded() && AnimBP.Succeeded())
   {
      USkeletalMesh* Asset = MeshAsset.Object;

      // Set mesh
      MeshComponent->SetSkeletalMesh(Asset);
      MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0, -90.0f));
      MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

      UClass* AnimBPAsset = AnimBP.Object;

      // Set Animation
      MeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
      MeshComponent->SetAnimInstanceClass(AnimBPAsset);
      MeshComponent->InitializeAnimScriptInstance(true);
   }
}
